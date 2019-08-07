#ifndef NV12RENDERWIDGET_H
#define NV12RENDERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#define ATTRIB_VERTEX 3
#define ATTRIB_TEXTURE 4
class NV12RenderWidget:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    NV12RenderWidget(QWidget* parent=0);
    ~NV12RenderWidget();
    void PlayOneFrame();
    void setWH(int w, int h){ m_nVideoW = w;m_nVideoH = h;}
    void my_repaint();
public slots:
    void updateFrame(unsigned char* pData);
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
private:
    GLuint id_y; //y纹理对象ID
    GLuint id_uv; //uv纹理对象ID
    QOpenGLTexture* m_pTextureY;  //y纹理对象
    QOpenGLTexture* m_pTextureUV;  //u纹理对象
    QOpenGLShader *m_pVSHader;  //顶点着色器程序对象
    QOpenGLShader *m_pFSHader;  //片段着色器对象
    QOpenGLShaderProgram *m_pShaderProgram; //着色器程序容器
    QOpenGLBuffer* m_pVbo;
    int m_nVideoW; //视频分辨率宽
    int m_nVideoH; //视频分辨率高
    unsigned char* m_pBufYuv420p;
};

#endif // NV12RENDERWIDGET_H
