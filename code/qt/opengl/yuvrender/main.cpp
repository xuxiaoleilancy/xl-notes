#include <QApplication>
#include <QTimer>
#include "nv12renderwidget.h"
#include "yuvthread_nv12.h"
#include "yuvthread.h"
#include "threadopenglwidget.h"
#include <QElapsedTimer>

void test_nv12(){
    YuvThreadNV12* t1 = new YuvThreadNV12("F://yuvfiles//OldTownCross_1920x1080_nv12.yuv",1920,1080);
    NV12RenderWidget * cpw1= new NV12RenderWidget(NULL);
    cpw1->setWH(1920,1080);
    cpw1->resize(1920,1080);
    cpw1->show();
    QObject::connect(t1,&YuvThreadNV12::newFrame,cpw1,&NV12RenderWidget::updateFrame);
    t1->start();
}
void test_yuvthread(){
 //   YuvThreadNV12* t1 = new YuvThreadNV12("F://yuvfiles//OldTownCross_1920x1080_nv12.yuv",1920,1080);
    YuvThread* t1 = new YuvThread("F://yuvfiles//InToTree_1920x1080.yuv",1920,1080);
    ThreadOpenglWidget * cpw1= new ThreadOpenglWidget(NULL);
    cpw1->setWH(1920,1080);
    cpw1->resize(1920,1080);
    cpw1->show();
    QObject::connect(t1,&YuvThread::newFrame,cpw1,&ThreadOpenglWidget::updateFrame);
    t1->start();
}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

//    QSurfaceFormat format;
//    //format.setSamples(16);
//    format.setSwapInterval(0);
//    QSurfaceFormat::setDefaultFormat(format);


    test_nv12();
    //test_yuvthread();

    return a.exec();
}
