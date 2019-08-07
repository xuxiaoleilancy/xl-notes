#ifndef YUVTHREADNV12_H
#define YUVTHREADNV12_H

#include <QThread>
#include <QWidget>

class YuvThreadNV12 : public QThread
{
    Q_OBJECT

public:
    explicit YuvThreadNV12(QString fileName,int w,int h);
    ~YuvThreadNV12();
    void PlayOneFrame();

    void run();
    int width(){return m_nVideoW;}
    int height(){return m_nVideoH;}
signals:
    void newFrame(unsigned char* pData);
private:

    int m_nVideoW; //视频分辨率宽
    int m_nVideoH; //视频分辨率高
    unsigned char* m_pBufYuv420p;
    FILE* m_pYuvFile;
    QString m_fileName;
    bool m_bStop;
};


#endif // YUVTHREAD_H
