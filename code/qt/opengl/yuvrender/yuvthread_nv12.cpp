#include "yuvthread_nv12.h"
#include <QDebug>
#include <QDateTime>
#include <QElapsedTimer>
YuvThreadNV12::YuvThreadNV12(QString fileName, int w, int h):QThread()
{
    m_fileName = fileName;
    m_pYuvFile = NULL;
    m_nVideoH = h;
    m_nVideoW = w;
    m_pBufYuv420p = NULL;
    m_bStop = false;
}

YuvThreadNV12::~YuvThreadNV12()
{
    if( m_pYuvFile ){
        fclose(m_pYuvFile);
        m_pYuvFile = NULL;
    }

    delete m_pBufYuv420p;
    m_pBufYuv420p = NULL;
}

void YuvThreadNV12::run()
{
    while(!m_bStop){
        PlayOneFrame();
        if(feof(m_pYuvFile)){
            fseek(m_pYuvFile,0,0);
        }
        msleep(10);
    }
}


void YuvThreadNV12::PlayOneFrame()
{
    if(NULL == m_pYuvFile)
    {
        //打开yuv视频文件 注意修改文件路径
        m_pYuvFile = fopen(m_fileName.toUtf8().data(), "rb");
        // m_pYuvFile = fopen("/home/administrator/yuv", "rb");
        //根据yuv视频数据的分辨率设置宽高,demo当中是1080p，这个地方要注意跟实际数据分辨率对应上
//        m_nVideoW = 1280;
//        m_nVideoH = 720;
    }
    //申请内存存一帧yuv图像数据,其大小为分辨率的1.5倍
    int nLen = m_nVideoW*m_nVideoH*3/2;
    if(NULL == m_pBufYuv420p)
    {
        m_pBufYuv420p = new unsigned char[nLen];
        qDebug("CPlayWidget::PlayOneFrame new data memory. Len=%d width=%d height=%d\n",
               nLen, m_nVideoW, m_nVideoH);
    }
    //将一帧yuv图像读到内存中
    if(NULL == m_pYuvFile)
    {
        qFatal("read yuv file err.may be path is wrong!\n");
        return;
    }
    fread(m_pBufYuv420p, 1, nLen, m_pYuvFile);

//    int look_up[256];
//      for (int i = 0; i < 256; i++) {
//        int val = i + 30;
//        look_up[i] = ((((val < 0) ? 0 : val) > 255) ? 255 : val);
//      }

//      unsigned char* temp_ptr = m_pBufYuv420p;

//      for (int i = 0; i < m_nVideoW*m_nVideoH; i++) {
//        *temp_ptr = static_cast<unsigned char>(look_up[*temp_ptr]);
//        temp_ptr++;
//      }

//    if( _pCallback ){
//        _pCallback->onRenderFrame(m_pBufYuv420p,m_nVideoW,m_nVideoH);
//    }
    emit newFrame(m_pBufYuv420p);
}

