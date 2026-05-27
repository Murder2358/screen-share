#include "mainwindow.h"
#include "annotationwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto* w = new AnnotationWindow();
    w->show();
    hide();
}

MainWindow::~MainWindow() {}

#include "mainwindow.moc"
