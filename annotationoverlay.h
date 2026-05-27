#pragma once
#include <QWidget>
#include <QColor>
#include <QPointF>
#include <QList>
#include <QPixmap>
#include <QMap>
#include <QRect>

// ──────────────────────────────────────────────
// Data structures
// ──────────────────────────────────────────────

struct Stroke {
    QList<QPointF> points;
    QColor         color;
    float          width    = 3.0f;
    bool           isEraser = false;
};

enum class StrokeEventType { Begin, Point, End, Undo, Clear };

struct StrokePacket {
    StrokeEventType type;
    quint32         strokeId = 0;
    QPointF         point;
    QColor          color;
    float           width    = 3.0f;
    bool            isEraser = false;
};

// ──────────────────────────────────────────────
// AnnotationOverlay
// ──────────────────────────────────────────────

class AnnotationOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit AnnotationOverlay(QWidget* parent = nullptr);

    bool canUndo() const { return !m_strokes.isEmpty(); }
    bool canRedo() const { return !m_undoStack.isEmpty(); }

    QList<Stroke> strokes() const { return m_strokes; }

public slots:
    void setPenColor(const QColor& color);
    void setPenWidth(float width);
    void setEraserMode(bool on);
    void setToolbarExcludeRect(const QRect& r);
    void clearAll();
    void undo();
    void redo();
    void addStroke(const Stroke& stroke);
    void applyRemotePacket(const StrokePacket& pkt);

signals:
    void strokePacketReady(const StrokePacket& pkt);
    void strokeFinished(const Stroke& stroke);
    void undoRedoChanged();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    static QPainterPath buildSmoothPath(const QList<QPointF>& pts);
    void renderStroke(QPainter& painter, const Stroke& stroke);
    void renderStrokeToCache(const Stroke& stroke);
    void rebuildCache();

    QPixmap        m_cachedPixmap;
    QList<Stroke>  m_strokes;
    QList<Stroke>  m_undoStack;
    Stroke         m_currentStroke;
    bool           m_drawing = false;
    QColor         m_penColor = Qt::red;
    float          m_penWidth = 3.0f;
    bool           m_isEraser = false;
    QRect          m_toolbarExcludeRect;
    quint32        m_strokeIdCounter = 0;

    // Remote strokes in progress, keyed by strokeId
    QMap<quint32, Stroke> m_remoteStrokes;
};
