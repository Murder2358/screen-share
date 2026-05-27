#pragma once
#include <QWidget>
#include "annotationoverlay.h"

class QKeyEvent;
class QToolBar;

class AnnotationWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AnnotationWindow(QWidget* parent = nullptr);

signals:
    void closed();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    AnnotationOverlay* m_overlay = nullptr;
};
