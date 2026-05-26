#include "screencapturer.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QDebug>

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
