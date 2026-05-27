#include "annotationoverlay.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QResizeEvent>
#include <QtGlobal>

// ──────────────────────────────────────────────
// Helper: build a smooth cubic-Bezier path from points
// ──────────────────────────────────────────────

QPainterPath AnnotationOverlay::buildSmoothPath(const QList<QPointF>& pts)
{
    QPainterPath path;
    if (pts.isEmpty())
        return path;
    if (pts.size() == 1) {
        path.moveTo(pts[0]);
        path.lineTo(pts[0]);
        return path;
    }
    if (pts.size() == 2) {
        path.moveTo(pts[0]);
        path.lineTo(pts[1]);
        return path;
    }
    path.moveTo(pts[0]);
    for (int i = 0; i < pts.size() - 1; ++i) {
        QPointF p0 = pts[qMax(i - 1, 0)];
        QPointF p1 = pts[i];
        QPointF p2 = pts[i + 1];
        QPointF p3 = pts[qMin(i + 2, pts.size() - 1)];
        QPointF ctrl1 = p1 + (p2 - p0) / 6.0;
        QPointF ctrl2 = p2 - (p3 - p1) / 6.0;
        path.cubicTo(ctrl1, ctrl2, p2);
    }
    return path;
}

// ──────────────────────────────────────────────
// Render a stroke onto an existing QPainter
// ──────────────────────────────────────────────

void AnnotationOverlay::renderStroke(QPainter& painter, const Stroke& stroke)
{
    if (stroke.points.isEmpty())
        return;

    painter.setRenderHint(QPainter::Antialiasing, true);

    if (stroke.isEraser) {
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        QPen pen(Qt::transparent,
                 stroke.width * 3,
                 Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
    } else {
        QPen pen(stroke.color, stroke.width,
                 Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
    }

    painter.setBrush(Qt::NoBrush);
    painter.drawPath(buildSmoothPath(stroke.points));

    // Reset composition mode in case eraser was used
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

// ──────────────────────────────────────────────
// Render a finished stroke into the offscreen cache
// ──────────────────────────────────────────────

void AnnotationOverlay::renderStrokeToCache(const Stroke& stroke)
{
    if (stroke.points.isEmpty())
        return;

    if (m_cachedPixmap.isNull() || m_cachedPixmap.size() != size()) {
        m_cachedPixmap = QPixmap(size());
        m_cachedPixmap.fill(Qt::transparent);
    }

    QPainter p(&m_cachedPixmap);
    renderStroke(p, stroke);
}

// ──────────────────────────────────────────────
// Rebuild cache from scratch (used after undo)
// ──────────────────────────────────────────────

void AnnotationOverlay::rebuildCache()
{
    m_cachedPixmap = QPixmap(size());
    m_cachedPixmap.fill(Qt::transparent);
    for (const Stroke& s : m_strokes)
        renderStrokeToCache(s);
}

// ──────────────────────────────────────────────
// Constructor
// ──────────────────────────────────────────────

AnnotationOverlay::AnnotationOverlay(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setStyleSheet("background: transparent;");
    setMouseTracking(true);
}

// ──────────────────────────────────────────────
// Public slots
// ──────────────────────────────────────────────

void AnnotationOverlay::setPenColor(const QColor& color)
{
    m_penColor = color;
    m_isEraser = false;
}

void AnnotationOverlay::setPenWidth(float width)
{
    m_penWidth = qMax(1.0f, width);
}

void AnnotationOverlay::setEraserMode(bool on)
{
    m_isEraser = on;
}

void AnnotationOverlay::setToolbarExcludeRect(const QRect& r)
{
    m_toolbarExcludeRect = r;
}

void AnnotationOverlay::clearAll()
{
    m_strokes.clear();
    m_undoStack.clear();
    m_currentStroke.points.clear();
    m_drawing = false;
    if (!m_cachedPixmap.isNull())
        m_cachedPixmap.fill(Qt::transparent);
    update();
    emit undoRedoChanged();

    StrokePacket pkt;
    pkt.type = StrokeEventType::Clear;
    emit strokePacketReady(pkt);
}

void AnnotationOverlay::undo()
{
    if (m_strokes.isEmpty())
        return;
    m_undoStack.append(m_strokes.takeLast());
    rebuildCache();
    update();
    emit undoRedoChanged();

    StrokePacket pkt;
    pkt.type = StrokeEventType::Undo;
    emit strokePacketReady(pkt);
}

void AnnotationOverlay::redo()
{
    if (m_undoStack.isEmpty())
        return;
    Stroke s = m_undoStack.takeLast();
    renderStrokeToCache(s);
    m_strokes.append(s);
    update();
    emit undoRedoChanged();
}

void AnnotationOverlay::addStroke(const Stroke& stroke)
{
    if (stroke.points.isEmpty())
        return;
    renderStrokeToCache(stroke);
    m_strokes.append(stroke);
    m_undoStack.clear();
    update();
    emit undoRedoChanged();
}

void AnnotationOverlay::applyRemotePacket(const StrokePacket& pkt)
{
    switch (pkt.type) {
    case StrokeEventType::Begin: {
        Stroke s;
        s.color    = pkt.color;
        s.width    = pkt.width;
        s.isEraser = pkt.isEraser;
        s.points.append(pkt.point);
        m_remoteStrokes[pkt.strokeId] = s;
        break;
    }
    case StrokeEventType::Point: {
        if (m_remoteStrokes.contains(pkt.strokeId)) {
            m_remoteStrokes[pkt.strokeId].points.append(pkt.point);
            update();
        }
        break;
    }
    case StrokeEventType::End: {
        if (m_remoteStrokes.contains(pkt.strokeId)) {
            Stroke s = m_remoteStrokes.take(pkt.strokeId);
            if (!pkt.point.isNull())
                s.points.append(pkt.point);
            renderStrokeToCache(s);
            m_strokes.append(s);
            m_undoStack.clear();
            update();
            emit undoRedoChanged();
            emit strokeFinished(s);
        }
        break;
    }
    case StrokeEventType::Undo: {
        if (!m_strokes.isEmpty()) {
            m_undoStack.append(m_strokes.takeLast());
            rebuildCache();
            update();
            emit undoRedoChanged();
        }
        break;
    }
    case StrokeEventType::Clear: {
        m_strokes.clear();
        m_undoStack.clear();
        m_remoteStrokes.clear();
        if (!m_cachedPixmap.isNull())
            m_cachedPixmap.fill(Qt::transparent);
        update();
        emit undoRedoChanged();
        break;
    }
    }
}

// ──────────────────────────────────────────────
// Paint
// ──────────────────────────────────────────────

void AnnotationOverlay::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), QColor(0, 0, 0, 1));

    if (!m_cachedPixmap.isNull())
        painter.drawPixmap(0, 0, m_cachedPixmap);

    // Draw in-progress remote strokes
    for (const Stroke& s : m_remoteStrokes)
        renderStroke(painter, s);

    if (m_drawing)
        renderStroke(painter, m_currentStroke);
}

// ──────────────────────────────────────────────
// Mouse events
// ──────────────────────────────────────────────

void AnnotationOverlay::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(event);
        return;
    }

    // Don't draw inside the toolbar area
    if (m_toolbarExcludeRect.isValid() && m_toolbarExcludeRect.contains(event->pos())) {
        QWidget::mousePressEvent(event);
        return;
    }

    // A new stroke clears the redo stack
    m_undoStack.clear();

    m_currentStroke.points.clear();
    m_currentStroke.color    = m_penColor;
    m_currentStroke.width    = m_penWidth;
    m_currentStroke.isEraser = m_isEraser;
    m_currentStroke.points.append(event->position());
    m_drawing = true;

    ++m_strokeIdCounter;
    StrokePacket pkt;
    pkt.type     = StrokeEventType::Begin;
    pkt.strokeId = m_strokeIdCounter;
    pkt.point    = event->position();
    pkt.color    = m_penColor;
    pkt.width    = m_penWidth;
    pkt.isEraser = m_isEraser;
    emit strokePacketReady(pkt);

    update();
}

void AnnotationOverlay::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_drawing) {
        QWidget::mouseMoveEvent(event);
        return;
    }

    QPointF pos = event->position();
    if (m_currentStroke.points.isEmpty() || m_currentStroke.points.last() != pos) {
        m_currentStroke.points.append(pos);

        StrokePacket pkt;
        pkt.type     = StrokeEventType::Point;
        pkt.strokeId = m_strokeIdCounter;
        pkt.point    = pos;
        emit strokePacketReady(pkt);

        // Only repaint the bounding rect of the last two points for performance
        if (m_currentStroke.points.size() >= 2) {
            QPointF prev = m_currentStroke.points[m_currentStroke.points.size() - 2];
            float hw = m_currentStroke.isEraser
                           ? m_currentStroke.width * 3 / 2.0f + 2
                           : m_currentStroke.width / 2.0f + 2;
            QRectF dirty = QRectF(prev, pos).normalized().adjusted(-hw, -hw, hw, hw);
            update(dirty.toRect());
        } else {
            update();
        }
    }
}

void AnnotationOverlay::mouseReleaseEvent(QMouseEvent* event)
{
    if (!m_drawing || event->button() != Qt::LeftButton) {
        QWidget::mouseReleaseEvent(event);
        return;
    }

    QPointF pos = event->position();
    if (m_currentStroke.points.isEmpty() || m_currentStroke.points.last() != pos)
        m_currentStroke.points.append(pos);

    if (!m_currentStroke.points.isEmpty()) {
        renderStrokeToCache(m_currentStroke);
        m_strokes.append(m_currentStroke);
        emit strokeFinished(m_currentStroke);
        emit undoRedoChanged();

        StrokePacket pkt;
        pkt.type     = StrokeEventType::End;
        pkt.strokeId = m_strokeIdCounter;
        pkt.point    = pos;
        pkt.color    = m_currentStroke.color;
        pkt.width    = m_currentStroke.width;
        pkt.isEraser = m_currentStroke.isEraser;
        emit strokePacketReady(pkt);
    }

    m_currentStroke.points.clear();
    m_drawing = false;
    update();
}

// ──────────────────────────────────────────────
// Resize: rebuild offscreen cache at new size
// ──────────────────────────────────────────────

void AnnotationOverlay::resizeEvent(QResizeEvent* e)
{
    QWidget::resizeEvent(e);
    rebuildCache();
}
