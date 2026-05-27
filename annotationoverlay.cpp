#include "annotationoverlay.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QtGlobal>

namespace {
void drawStroke(QPainter& painter, const Stroke& stroke)
{
    if (stroke.points.isEmpty()) {
        return;
    }

    QPen pen(stroke.color, stroke.width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    if (stroke.points.size() == 1) {
        painter.drawPoint(stroke.points.first());
        return;
    }

    for (int i = 1; i < stroke.points.size(); ++i) {
        painter.drawLine(stroke.points.at(i - 1), stroke.points.at(i));
    }
}
}

AnnotationOverlay::AnnotationOverlay(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setMouseTracking(true);
}

void AnnotationOverlay::setPenColor(const QColor& color)
{
    m_penColor = color;
}

void AnnotationOverlay::setPenWidth(int width)
{
    m_penWidth = qMax(1, width);
}

void AnnotationOverlay::clearAll()
{
    m_strokes.clear();
    m_currentStroke.points.clear();
    m_drawing = false;
    update();
}

void AnnotationOverlay::addStroke(const Stroke& stroke)
{
    if (stroke.points.isEmpty()) {
        return;
    }
    m_strokes.append(stroke);
    update();
}

void AnnotationOverlay::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (const Stroke& stroke : m_strokes) {
        drawStroke(painter, stroke);
    }

    if (m_drawing) {
        drawStroke(painter, m_currentStroke);
    }
}

void AnnotationOverlay::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(event);
        return;
    }

    m_currentStroke.points.clear();
    m_currentStroke.color = m_penColor;
    m_currentStroke.width = m_penWidth;
    m_currentStroke.points.append(event->pos());
    m_drawing = true;
    update();
}

void AnnotationOverlay::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_drawing) {
        QWidget::mouseMoveEvent(event);
        return;
    }

    if (m_currentStroke.points.isEmpty() || m_currentStroke.points.last() != event->pos()) {
        m_currentStroke.points.append(event->pos());
        update();
    }
}

void AnnotationOverlay::mouseReleaseEvent(QMouseEvent* event)
{
    if (!m_drawing || event->button() != Qt::LeftButton) {
        QWidget::mouseReleaseEvent(event);
        return;
    }

    if (m_currentStroke.points.isEmpty() || m_currentStroke.points.last() != event->pos()) {
        m_currentStroke.points.append(event->pos());
    }

    if (!m_currentStroke.points.isEmpty()) {
        m_strokes.append(m_currentStroke);
        emit strokeFinished(m_currentStroke);
    }

    m_currentStroke.points.clear();
    m_drawing = false;
    update();
}
