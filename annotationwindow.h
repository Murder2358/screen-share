#pragma once
#include <QMainWindow>
#include "annotationoverlay.h"

class QLabel;

class AnnotationWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AnnotationWindow(QWidget* parent = nullptr);
};
