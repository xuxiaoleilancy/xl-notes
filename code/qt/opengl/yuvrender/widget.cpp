#include "widget.h"
#include "ui_widget.h"
#include "gplaywidget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pYuvFile = NULL;
    m_nVideoH = 0;
    m_nVideoW = 0;
    m_pBufYuv420p = NULL;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::PlayOneFrame()
{
    if(NULL == m_pYuvFile)
    {
        //打开yuv视频文件 注意修改文件路径
        m_pYuvFile = fopen("F://yuvfiles//CrowdRun_1280x720.yuv", "rb");
        // m_pYuvFile = fopen("/home/administrator/yuv", "rb");
//         m_nVideoW = 320;
//         m_nVideoH = 180;
        //根据yuv视频数据的分辨率设置宽高,demo当中是1080p，这个地方要注意跟实际数据分辨率对应上
        m_nVideoW = 1280;
        m_nVideoH = 720;
    }
    //申请内存存一帧yuv图像数据,其大小为分辨率的1.5倍
    int nLen = m_nVideoW*m_nVideoH*3/2;
    if(NULL == m_pBufYuv420p)
    {
        m_pBufYuv420p = new unsigned char[nLen];
        qDebug("CPlayWidget::PlayOneFrame new data memory. Len=%d width=%d height=%d\n",
               nLen, m_nVideoW, m_nVideoW);
    }
    //将一帧yuv图像读到内存中
    if(NULL == m_pYuvFile)
    {
        qFatal("read yuv file err.may be path is wrong!\n");
        return;
    }
    fread(m_pBufYuv420p, 1, nLen, m_pYuvFile);
    if(feof(m_pYuvFile)){
        fseek(m_pYuvFile,0,0);
    }
    //刷新界面,触发paintGL接口

    QList<CPlayWidget*> wdgs;
    wdgs.append(ui->wdg1);
    wdgs.append(ui->wdg2);
    wdgs.append(ui->wdg3);
    wdgs.append(ui->wdg4);
    wdgs.append(ui->wdg5);
    wdgs.append(ui->wdg6);
    wdgs.append(ui->wdg7);
    wdgs.append(ui->wdg8);
    wdgs.append(ui->wdg9);

    for(int i=0;i<wdgs.size();i++){
        wdgs[i]->updateFrame(m_pBufYuv420p);
    }
    //resize(size());
}
