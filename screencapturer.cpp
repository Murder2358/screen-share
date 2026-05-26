#include "screencapturer.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QDebug>
#include <cstring>
#include <algorithm>

#ifdef Q_OS_WIN
#include <dxgi1_2.h>
#endif

ScreenCapturer::ScreenCapturer(QObject* parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &ScreenCapturer::captureFrame);
}

ScreenCapturer::~ScreenCapturer()
{
    stop();
}

void ScreenCapturer::start(int fps)
{
    if (m_running) return;
    int interval = (fps > 0) ? (1000 / fps) : 33;
    m_timer->start(interval);
    m_running = true;
    qDebug() << "[ScreenCapturer] started, interval =" << interval << "ms";
}

void ScreenCapturer::stop()
{
    if (!m_running) return;
    m_timer->stop();
    m_running = false;
    qDebug() << "[ScreenCapturer] stopped";
}

void ScreenCapturer::captureFrame()
{
#ifdef Q_OS_WIN
    if (m_useDXGI) {
        if (captureWithDXGI()) return;
        // DXGI 失败，自动降级
        m_useDXGI = false;
        qDebug() << "[ScreenCapturer] DXGI unavailable, fallback to grabWindow";
    }
#endif
    captureWithGrabWindow();
}

bool ScreenCapturer::captureWithDXGI()
{
#ifdef Q_OS_WIN
    HRESULT hr = S_OK;

    if (!m_d3dDevice || !m_d3dContext || !m_duplication) {
        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0
        };

        hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            featureLevels,
            static_cast<UINT>(sizeof(featureLevels) / sizeof(featureLevels[0])),
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
        );
        if (FAILED(hr)) {
            return false;
        }

        Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
        hr = m_d3dDevice.As(&dxgiDevice);
        if (FAILED(hr)) {
            return false;
        }

        Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
        hr = dxgiDevice->GetAdapter(adapter.GetAddressOf());
        if (FAILED(hr)) {
            return false;
        }

        Microsoft::WRL::ComPtr<IDXGIOutput> output;
        hr = adapter->EnumOutputs(0, output.GetAddressOf());
        if (FAILED(hr)) {
            return false;
        }

        Microsoft::WRL::ComPtr<IDXGIOutput1> output1;
        hr = output.As(&output1);
        if (FAILED(hr)) {
            return false;
        }

        hr = output1->DuplicateOutput(m_d3dDevice.Get(), m_duplication.ReleaseAndGetAddressOf());
        if (FAILED(hr)) {
            return false;
        }
    }

    DXGI_OUTDUPL_FRAME_INFO frameInfo{};
    Microsoft::WRL::ComPtr<IDXGIResource> desktopResource;
    hr = m_duplication->AcquireNextFrame(0, &frameInfo, desktopResource.GetAddressOf());
    if (hr == DXGI_ERROR_WAIT_TIMEOUT) {
        return false;
    }
    if (FAILED(hr)) {
        if (hr == DXGI_ERROR_ACCESS_LOST) {
            m_duplication.Reset();
            m_stagingTexture.Reset();
            m_captureWidth = 0;
            m_captureHeight = 0;
        }
        return false;
    }

    bool frameAcquired = true;
    auto releaseFrame = [&]() {
        if (frameAcquired && m_duplication) {
            m_duplication->ReleaseFrame();
            frameAcquired = false;
        }
    };

    Microsoft::WRL::ComPtr<ID3D11Texture2D> desktopTexture;
    hr = desktopResource.As(&desktopTexture);
    if (FAILED(hr)) {
        releaseFrame();
        return false;
    }

    D3D11_TEXTURE2D_DESC desc{};
    desktopTexture->GetDesc(&desc);
    if (desc.Width == 0 || desc.Height == 0) {
        releaseFrame();
        return false;
    }

    if (!m_stagingTexture || m_captureWidth != desc.Width || m_captureHeight != desc.Height) {
        D3D11_TEXTURE2D_DESC stagingDesc = desc;
        stagingDesc.Usage = D3D11_USAGE_STAGING;
        stagingDesc.BindFlags = 0;
        stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        stagingDesc.MiscFlags = 0;
        stagingDesc.ArraySize = 1;
        stagingDesc.MipLevels = 1;
        stagingDesc.SampleDesc.Count = 1;
        stagingDesc.SampleDesc.Quality = 0;

        hr = m_d3dDevice->CreateTexture2D(&stagingDesc, nullptr, m_stagingTexture.ReleaseAndGetAddressOf());
        if (FAILED(hr)) {
            releaseFrame();
            return false;
        }
        m_captureWidth = desc.Width;
        m_captureHeight = desc.Height;
    }

    m_d3dContext->CopyResource(m_stagingTexture.Get(), desktopTexture.Get());

    D3D11_MAPPED_SUBRESOURCE mapped{};
    hr = m_d3dContext->Map(m_stagingTexture.Get(), 0, D3D11_MAP_READ, 0, &mapped);
    if (FAILED(hr)) {
        releaseFrame();
        return false;
    }

    QImage frame(static_cast<int>(desc.Width), static_cast<int>(desc.Height), QImage::Format_RGB32);
    if (frame.isNull()) {
        m_d3dContext->Unmap(m_stagingTexture.Get(), 0);
        releaseFrame();
        return false;
    }

    const int srcBytesPerLine = static_cast<int>(mapped.RowPitch);
    const int dstBytesPerLine = frame.bytesPerLine();
    const int copyBytes = std::min(srcBytesPerLine, dstBytesPerLine);
    const auto* src = static_cast<const unsigned char*>(mapped.pData);
    for (int y = 0; y < frame.height(); ++y) {
        std::memcpy(frame.scanLine(y), src + (static_cast<size_t>(y) * mapped.RowPitch), static_cast<size_t>(copyBytes));
    }

    m_d3dContext->Unmap(m_stagingTexture.Get(), 0);
    releaseFrame();

    QImage output = frame.scaled(m_outputSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                         .convertToFormat(QImage::Format_RGB32);
    emit frameCaptured(output);
    return true;
#else
    return false;
#endif
}

void ScreenCapturer::captureWithGrabWindow()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    if (!screen) {
        emit captureError("No primary screen found");
        return;
    }

    QPixmap pixmap = screen->grabWindow(0);
    if (pixmap.isNull()) {
        emit captureError("grabWindow() returned null pixmap");
        return;
    }

    QImage frame = pixmap.toImage()
                         .scaled(m_outputSize,
                                 Qt::IgnoreAspectRatio,
                                 Qt::SmoothTransformation)
                         .convertToFormat(QImage::Format_RGB32);

    emit frameCaptured(frame);
}
