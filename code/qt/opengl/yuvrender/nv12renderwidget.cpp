#include "nv12renderwidget.h"
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QtMath>
NV12RenderWidget::NV12RenderWidget(QWidget *parent):QOpenGLWidget(parent)
{
    id_y = 0;
    id_uv = 0;
    m_pBufYuv420p = NULL;
    m_pShaderProgram = NULL;
    m_pTextureY = NULL;
    m_pTextureUV = NULL;
    m_nVideoH = 0;
    m_nVideoW = 0;

}
NV12RenderWidget::~NV12RenderWidget()
{
}
void NV12RenderWidget::PlayOneFrame()
{//函数功能读取一张yuv图像数据进行显示,每单击一次，就显示一张图片

}

void NV12RenderWidget::updateFrame(unsigned char *pData)
{
    m_pBufYuv420p = pData;
    update();
}

void NV12RenderWidget::my_repaint()
{
    update();
    //QApplication::processEvents();
}
void NV12RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    const char *vsrc =
            "attribute vec4 vertexIn; \
             attribute vec4 textureIn; \
             varying vec4 textureOut;  \
             void main(void)           \
             {                         \
    gl_Position = vertexIn; \
    textureOut = textureIn; \
}";

    const char *fsrc =
            "varying mediump vec4 textureOut;\n"
            "uniform sampler2D textureY;\n"
            "uniform sampler2D textureUV;\n"
            "void main(void)\n"
            "{\n"
            "vec3 yuv; \n"
            "vec3 rgb; \n"
            "yuv.x = texture2D(textureY, textureOut.st).r - 0.0625; \n"
            "yuv.y = texture2D(textureUV, textureOut.st).r - 0.5; \n"
            "yuv.z = texture2D(textureUV, textureOut.st).g - 0.5; \n"
            "rgb = mat3( 1,       1,         1, \n"
                        "0,       -0.39465,  2.03211, \n"
                        "1.13983, -0.58060,  0) * yuv; \n"
            "gl_FragColor = vec4(rgb, 1); \n"
            "}\n";

    m_pShaderProgram = new QOpenGLShaderProgram;
    m_pShaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    m_pShaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,fsrc);
    m_pShaderProgram->link();

    GLfloat points[]{
        -1.0f, 1.0f,
         1.0f, 1.0f,
         1.0f, -1.0f,
        -1.0f, -1.0f,

        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f
    };
    m_pVbo = new QOpenGLBuffer;
    m_pVbo->create();
    m_pVbo->bind();
    m_pVbo->allocate(points,sizeof(points));

    m_pTextureY = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_pTextureUV = new QOpenGLTexture(QOpenGLTexture::Target2D);

    m_pTextureY->create();
    m_pTextureUV->create();

    id_y = m_pTextureY->textureId();
    //获取返回u分量的纹理索引值
    id_uv = m_pTextureUV->textureId();
    glClearColor(0.3,0.3,0.3,0.0);//设置背景色
}
void NV12RenderWidget::resizeGL(int w, int h)
{
    if(h == 0)// 防止被零除
    {
        h = 1;// 将高设为1
    }
    //设置视口
    glViewport(0,0, w,h);
}
 void NV12RenderWidget::paintGL()
 {
     if(!m_pBufYuv420p)return;

     glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glDisable(GL_DEPTH_TEST);

     m_pShaderProgram->bind();
     m_pVbo->bind();
     m_pShaderProgram->enableAttributeArray("vertexIn");
     m_pShaderProgram->enableAttributeArray("textureIn");
     m_pShaderProgram->setAttributeBuffer("vertexIn",GL_FLOAT, 0, 2, 2*sizeof(GLfloat));
     m_pShaderProgram->setAttributeBuffer("textureIn",GL_FLOAT,2 * 4 * sizeof(GLfloat),2,2*sizeof(GLfloat));
     int iCount = 9;
     int iTmp = qSqrt(iCount);
     int x = 10;
         int y = 10;
         int w = width() / iTmp - iTmp *4 ;
         int h = height() / iTmp - iTmp *4 ;

     for(int i=0;i<iTmp;i++){
for(int j=0;j<iTmp;j++){
         x = i*w + (i+1)*2;
         y = j*h + (j+1)*2;
//         if( i==0) {
//             x =0;
//             y = 0;
//         }
//         if( i==1) {
//             x = w;
//             y = 0;
//         }

//         if(i ==2 ){
//             x = 0;
//             y = h;
//         }
//         if( i==3){
//             x = w;
//             y = h;
//         }
         glViewport(x,y,w,h);
         glActiveTexture(GL_TEXTURE0 + 1);
         glBindTexture(GL_TEXTURE_2D,id_y);
         glTexImage2D(GL_TEXTURE_2D,0,GL_RED,m_nVideoW,m_nVideoH,0,GL_RED,GL_UNSIGNED_BYTE,m_pBufYuv420p);
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

         glActiveTexture(GL_TEXTURE0 + 0);
         glBindTexture(GL_TEXTURE_2D,id_uv);
         glTexImage2D(GL_TEXTURE_2D,0,GL_RG,m_nVideoW >> 1,m_nVideoH >> 1,0,GL_RG,GL_UNSIGNED_BYTE,m_pBufYuv420p + m_nVideoW*m_nVideoH);
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

         m_pShaderProgram->setUniformValue("textureUV",0);
         m_pShaderProgram->setUniformValue("textureY",1);
         glDrawArrays(GL_QUADS,0,4);
     }
     }
     m_pShaderProgram->disableAttributeArray("vertexIn");
     m_pShaderProgram->disableAttributeArray("textureIn");
     m_pShaderProgram->release();
 }

