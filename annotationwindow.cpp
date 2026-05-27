#include "annotationwindow.h"

#include <QAction>
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QPixmap>
#include <QScreen>
#include <QSlider>
#include <QStackedLayout>
#include <QToolBar>
#include <QWidget>

AnnotationWindow::AnnotationWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Annotation 测试窗口");
    resize(1280, 720);

    QPixmap screenshot;
    if (QScreen* screen = QGuiApplication::primaryScreen()) {
        screenshot = screen->grabWindow(0);
    }

    auto* container = new QWidget(this);
    auto* stackedLayout = new QStackedLayout(container);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);
    stackedLayout->setContentsMargins(0, 0, 0, 0);

    auto* backgroundLabel = new QLabel(container);
    backgroundLabel->setAlignment(Qt::AlignCenter);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setPixmap(screenshot);

    auto* overlay = new AnnotationOverlay(container);

    stackedLayout->addWidget(backgroundLabel);
    stackedLayout->addWidget(overlay);
    setCentralWidget(container);

    QToolBar* toolbar = addToolBar("Annotation Tools");
    QAction* redAction = toolbar->addAction("红");
    QAction* blueAction = toolbar->addAction("蓝");
    QAction* yellowAction = toolbar->addAction("黄");

    auto* widthSlider = new QSlider(Qt::Horizontal, toolbar);
    widthSlider->setRange(1, 10);
    widthSlider->setValue(3);
    toolbar->addWidget(widthSlider);

    QAction* clearAction = toolbar->addAction("清除");

    connect(redAction, &QAction::triggered, this, [overlay]() {
        overlay->setPenColor(Qt::red);
    });
    connect(blueAction, &QAction::triggered, this, [overlay]() {
        overlay->setPenColor(Qt::blue);
    });
    connect(yellowAction, &QAction::triggered, this, [overlay]() {
        overlay->setPenColor(Qt::yellow);
    });
    connect(widthSlider, &QSlider::valueChanged, this, [overlay](int value) {
        overlay->setPenWidth(value);
    });
    connect(clearAction, &QAction::triggered, overlay, &AnnotationOverlay::clearAll);

    connect(overlay, &AnnotationOverlay::strokeFinished, this, [](const Stroke& stroke) {
        qDebug() << "[Annotation] stroke points:" << stroke.points.size();
    });
}
