#include "widget.h"
#include <QApplication>
#include "gplaywidget.h"
#include <QTimer>
#include "yuvthread.h"
#include "threadopenglwidget.h"
#include "ropengltexture.h"
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CPlayWidget * cpw2= new CPlayWidget(NULL);
    cpw2->resize(640,480);

    QElapsedTimer timer;
    timer.start();

    while(!timer.hasExpired(1000)){
        cpw2->show();
    }

    UpdateThread* ut = new UpdateThread(cpw2);
    QObject::connect(ut,&UpdateThread::repaint,cpw2,&CPlayWidget::my_repaint);
    ut->start();
    return a.exec();
}
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    YuvThread* t1 = new YuvThread("F://yuvfiles//InToTree_1920x1080.yuv",1920,1080);
//    YuvThread* t2 = new YuvThread("F://yuvfiles//CrowdRun_1280x720.yuv",1280,720);
//    ThreadOpenglWidget * cpw1= new ThreadOpenglWidget(NULL);
//    cpw1->setWH(1920,1080);
//    cpw1->setWWHH(1280,720);
//    cpw1->resize(640,480);
//    cpw1->show();

//    ThreadOpenglWidget * cpw2= new ThreadOpenglWidget(NULL);
//    cpw2->setWH(1920,1080);
//    cpw2->setWWHH(1280,720);
//    cpw2->resize(640,480);
//    cpw2->show();


//    QObject::connect(t1,&YuvThread::newFrame,cpw1,&ThreadOpenglWidget::updateFrame);
//    QObject::connect(t2,&YuvThread::newFrame,cpw1,&ThreadOpenglWidget::updateFrame1);
//    QObject::connect(t1,&YuvThread::newFrame,cpw2,&ThreadOpenglWidget::updateFrame);
//    QObject::connect(t2,&YuvThread::newFrame,cpw2,&ThreadOpenglWidget::updateFrame1);

//    t1->start();
//    t2->start();

//    return a.exec();
//}
