#include "widget.h"
#include <QApplication>
#include "gplaywidget.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QSurfaceFormat format ;
    format.setRenderableType(QSurfaceFormat::OpenGLES);
    QSurfaceFormat::setDefaultFormat(format);

    QTimer timer;

    CPlayWidget * cpw= new CPlayWidget();
    cpw->show();

    QObject::connect(&timer,&QTimer::timeout,cpw,&CPlayWidget::PlayOneFrame);
    timer.start(1000/24);
    return a.exec();
}
