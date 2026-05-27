#include "annotationwindow.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

AnnotationWindow::AnnotationWindow(QWidget* parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_NoSystemBackground, true);

    m_overlay = new AnnotationOverlay(this);
    m_overlay->setGeometry(rect());
    m_overlay->raise();

    auto* toolbarWidget = new QWidget(this);
    toolbarWidget->setStyleSheet("background: rgba(30,30,30,180); border-radius: 8px;");
    toolbarWidget->move(20, 20);

    auto* toolbarLayout = new QHBoxLayout(toolbarWidget);
    toolbarLayout->setContentsMargins(10, 10, 10, 10);
    toolbarLayout->setSpacing(8);

    auto makeColorButton = [toolbarWidget](const QString& colorStyle) {
        auto* button = new QPushButton(toolbarWidget);
        button->setFixedSize(24, 24);
        button->setStyleSheet(QString("background-color: %1; border: 1px solid #dddddd; border-radius: 12px;")
                                  .arg(colorStyle));
        return button;
    };

    auto* redButton = makeColorButton("#ff2d2d");
    auto* blueButton = makeColorButton("#2f7dff");
    auto* yellowButton = makeColorButton("#ffd21f");
    auto* greenButton = makeColorButton("#2ecc71");

    auto* widthSlider = new QSlider(Qt::Horizontal, toolbarWidget);
    widthSlider->setRange(1, 10);
    widthSlider->setValue(3);
    widthSlider->setFixedWidth(120);

    auto* clearButton = new QPushButton(QStringLiteral("清除"), toolbarWidget);
    auto* exitButton = new QPushButton(QStringLiteral("退出"), toolbarWidget);

    toolbarLayout->addWidget(redButton);
    toolbarLayout->addWidget(blueButton);
    toolbarLayout->addWidget(yellowButton);
    toolbarLayout->addWidget(greenButton);
    toolbarLayout->addWidget(widthSlider);
    toolbarLayout->addWidget(clearButton);
    toolbarLayout->addWidget(exitButton);

    connect(redButton, &QPushButton::clicked, this, [this]() { m_overlay->setPenColor(Qt::red); });
    connect(blueButton, &QPushButton::clicked, this, [this]() { m_overlay->setPenColor(Qt::blue); });
    connect(yellowButton, &QPushButton::clicked, this, [this]() { m_overlay->setPenColor(Qt::yellow); });
    connect(greenButton, &QPushButton::clicked, this, [this]() { m_overlay->setPenColor(Qt::green); });
    connect(widthSlider, &QSlider::valueChanged, this, [this](int value) { m_overlay->setPenWidth(value); });
    connect(clearButton, &QPushButton::clicked, m_overlay, &AnnotationOverlay::clearAll);
    connect(exitButton, &QPushButton::clicked, this, [this]() {
        emit closed();
        close();
    });
    connect(m_overlay, &AnnotationOverlay::strokeFinished, this, [](const Stroke& stroke) {
        qDebug() << "[strokeFinished] points:" << stroke.points.size();
    });

    showFullScreen();

    m_overlay->setGeometry(rect());
    m_overlay->raise();
    toolbarWidget->raise();
}

void AnnotationWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        emit closed();
        close();
        return;
    }
    QWidget::keyPressEvent(event);
}
