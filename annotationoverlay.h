#pragma once
#include <QWidget>
#include <QColor>
#include <QPoint>
#include <QList>

struct Stroke {
    QList<QPoint> points;
    QColor        color;
    int           width;
};

class AnnotationOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit AnnotationOverlay(QWidget* parent = nullptr);

    void setPenColor(const QColor& color);
    void setPenWidth(int width);
    void clearAll();
    void addStroke(const Stroke& stroke);

    QList<Stroke> strokes() const { return m_strokes; }

signals:
    void strokeFinished(const Stroke& stroke);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QList<Stroke> m_strokes;
    Stroke        m_currentStroke;
    bool          m_drawing = false;
    QColor        m_penColor = Qt::red;
    int           m_penWidth = 3;
};
