#include <QApplication>
#include "annotationwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    AnnotationWindow w;
    w.show();
    return app.exec();
}