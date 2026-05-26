#pragma once

#include <QMainWindow>
#include <QLabel>
#include "screencapturer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onFrameCaptured(const QImage& frame);
    void onCaptureError(const QString& msg);

private:
    QLabel*         m_previewLabel;
    ScreenCapturer* m_capturer;
};
