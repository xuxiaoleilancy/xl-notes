#ifndef THREADOPENGLWIDGET_H
#define THREADOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QFile>
#include <QLabel>
#include <QElapsedTimer>
#include "yuvthread.h"

#define ATTRIB_VERTEX 3
#define ATTRIB_TEXTURE 4
class ThreadOpenglWidget:public QOpenGLWidget,protected QOpenGLFunctions,public RenderCallback
{
    Q_OBJECT
public:
    ThreadOpenglWidget(QWidget* parent,int iFlag=0);
    ~ThreadOpenglWidget();
    void PlayOneFrame();
    void setWH(int w, int h){ m_nVideoW = w;m_nVideoH = h;}
    void setWWHH(int w, int h){ m_nVideoWW = w;m_nVideoHH = h;}
    void updateFrame(unsigned char* pData);
    void updateFrame1(unsigned char* pData);

    void setEnableScissor(bool b){ m_bEnableScissor = b;}

     virtual void onRenderFrame(unsigned char* pData,int w, int h);
protected:
    void initializeGL() ;
    void resizeGL(int w, int h) ;
    void paintGL() ;
    void timerEvent(QTimerEvent* e);
    void render_new();
    void render_new1();
    GLuint getId_y();
    GLuint getId_u();
    GLuint getId_v();
    void new_texture(GLuint* textures);
private:

    void updateTexture();
     void updateTexture1();
    GLuint textureUniformY; //y纹理数据位置
    GLuint textureUniformU; //u纹理数据位置
    GLuint textureUniformV; //v纹理数据位置
    GLuint id_y; //y纹理对象ID
    GLuint id_u; //u纹理对象ID
    GLuint id_v; //v纹理对象ID
    GLuint id_yy; //y纹理对象ID
    GLuint id_uu; //u纹理对象ID
    GLuint id_vv; //v纹理对象ID
    QOpenGLTexture* m_pTextureY;  //y纹理对象
    QOpenGLTexture* m_pTextureU;  //u纹理对象
    QOpenGLTexture* m_pTextureV;  //v纹理对象
    QOpenGLTexture* m_pTextureYY;  //y纹理对象
    QOpenGLTexture* m_pTextureUU;  //u纹理对象
    QOpenGLTexture* m_pTextureVV;  //v纹理对象
    QOpenGLShader *m_pVSHader;  //顶点着色器程序对象
    QOpenGLShader *m_pFSHader;  //片段着色器对象
    QOpenGLShaderProgram *m_pShaderProgram; //着色器程序容器
    int m_nVideoW; //视频分辨率宽
    int m_nVideoH; //视频分辨率高
    int m_nVideoWW; //视频分辨率宽
    int m_nVideoHH; //视频分辨率高
    unsigned char* m_pBufYuv420p;
    unsigned char* m_pBufYuv420p1;
    FILE* m_pYuvFile;
    QRect viewPortRect(QRectF rectf, int frameW, int frameH, bool bAspect=false);

    bool m_bEnableScissor;

    bool m_bInit;
    QLabel* _pLabel;
    QElapsedTimer _timer;
    int _iFrame;
    int _iFlag;
};

#endif // THREADOPENGLWIDGET_H
