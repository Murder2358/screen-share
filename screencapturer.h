#pragma once

#include <QObject>
#include <QImage>
#include <QSize>
#include <QTimer>

class ScreenCapturer : public QObject
{
    Q_OBJECT

public:
    explicit ScreenCapturer(QObject* parent = nullptr);
    ~ScreenCapturer();

    void start(int fps = 30);
    void stop();
    bool isRunning() const { return m_running; }

    void setOutputSize(const QSize& size) { m_outputSize = size; }
    QSize outputSize() const { return m_outputSize; }

signals:
    void frameCaptured(const QImage& frame);
    void captureError(const QString& msg);

private slots:
    void captureFrame();

private:
    QTimer* m_timer;
    QSize   m_outputSize{1280, 720};
    bool    m_running{false};
};
