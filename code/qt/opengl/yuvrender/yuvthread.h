#ifndef YUVTHREAD_H
#define YUVTHREAD_H

#include <QThread>
#include <QWidget>

class RenderCallback
{
public:
    virtual void onRenderFrame(unsigned char* pData,int w, int h) =0 ;
};

class YuvThread : public QThread
{
    Q_OBJECT

public:
    explicit YuvThread(QString fileName,int w,int h);
    ~YuvThread();
    void PlayOneFrame();

    void run();
    int width(){return m_nVideoW;}
    int height(){return m_nVideoH;}
    void setCallback(RenderCallback* pCallback);
signals:
    void newFrame(unsigned char* pData);
private:

    int m_nVideoW; //视频分辨率宽
    int m_nVideoH; //视频分辨率高
    unsigned char* m_pBufYuv420p;
    FILE* m_pYuvFile;
    QString m_fileName;
    bool m_bStop;
    RenderCallback* _pCallback;
};
class UpdateThread : public QThread
{
    Q_OBJECT

public:
    explicit UpdateThread(QWidget* pWdg);
    ~UpdateThread();

    void run();
signals:
    void repaint();
private:
    QWidget* _pWdg;
};

#endif // YUVTHREAD_H
