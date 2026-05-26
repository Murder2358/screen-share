#include "mainwindow.h"
#include <QStatusBar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_previewLabel(new QLabel(this))
    , m_capturer(new ScreenCapturer(this))
{
    setWindowTitle("ScreenCapturer 预览（调试用）");
    resize(1280, 720);

    m_previewLabel->setAlignment(Qt::AlignCenter);
    m_previewLabel->setScaledContents(true);
    setCentralWidget(m_previewLabel);

    connect(m_capturer, &ScreenCapturer::frameCaptured,
            this,       &MainWindow::onFrameCaptured);
    connect(m_capturer, &ScreenCapturer::captureError,
            this,       &MainWindow::onCaptureError);

    m_capturer->start(30);
    statusBar()->showMessage("采集中... 30fps | 输出: 1280×720 | 格式: RGB32");
}

MainWindow::~MainWindow()
{
    m_capturer->stop();
}

void MainWindow::onFrameCaptured(const QImage& frame)
{
    m_previewLabel->setPixmap(QPixmap::fromImage(frame));
}

void MainWindow::onCaptureError(const QString& msg)
{
    statusBar()->showMessage("错误: " + msg);
}
