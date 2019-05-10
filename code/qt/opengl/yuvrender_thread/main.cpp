#include <QApplication>
#include <QTimer>
#include "yuvthread.h"
#include "threadopenglwidget.h"
#include "ropengltexture.h"
#include <QElapsedTimer>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(format);

    YuvThread* t1 = new YuvThread("F://yuvfiles//InToTree_1920x1080.yuv",1920,1080);
    YuvThread* t2 = new YuvThread("F://yuvfiles//CrowdRun_1280x720.yuv",1280,720);
    ThreadOpenglWidget * cpw1= new ThreadOpenglWidget(NULL);
    cpw1->setWH(1920,1080);
    cpw1->setWWHH(1280,720);
    cpw1->resize(1280,720);
    cpw1->show();

    ThreadOpenglWidget * cpw2= new ThreadOpenglWidget(NULL);
    cpw2->setWH(1920,1080);
    cpw2->setWWHH(1280,720);
    cpw2->resize(1920,1080);
    cpw2->show();


    QObject::connect(t1,&YuvThread::newFrame,cpw1,&ThreadOpenglWidget::updateFrame);
    QObject::connect(t2,&YuvThread::newFrame,cpw1,&ThreadOpenglWidget::updateFrame1);
    QObject::connect(t1,&YuvThread::newFrame,cpw2,&ThreadOpenglWidget::updateFrame);
    QObject::connect(t2,&YuvThread::newFrame,cpw2,&ThreadOpenglWidget::updateFrame1);

    t1->start();
    t2->start();

    return a.exec();
}
