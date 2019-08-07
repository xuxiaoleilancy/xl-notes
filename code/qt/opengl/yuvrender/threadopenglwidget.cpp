#include "threadopenglwidget.h"

#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>

#include <QElapsedTimer>

#include "ropengltexture.h"

ThreadOpenglWidget::ThreadOpenglWidget(QWidget *parent,int iFlag):QOpenGLWidget(parent),_iFlag(iFlag)
{
    setWindowTitle(QString::number(_iFlag));
    textureUniformY = 0;
    textureUniformU = 0;
    textureUniformV = 0;
    id_y = 0;
    id_u = 0;
    id_v = 0;
    id_yy = 0;
    id_uu = 0;
    id_vv = 0;
m_pBufYuv420p1 = NULL;
    m_pBufYuv420p = NULL;
    m_pVSHader = NULL;
    m_pFSHader = NULL;
    m_pShaderProgram = NULL;
    m_pTextureY = NULL;
    m_pTextureU = NULL;
    m_pTextureV = NULL;
    m_pTextureYY = NULL;
    m_pTextureUU = NULL;
    m_pTextureVV = NULL;
    m_pYuvFile = NULL;
    m_nVideoH = 0;
    m_nVideoW = 0;
    m_nVideoHH = 0;
    m_nVideoWW = 0;
    m_bEnableScissor = false;
    m_bInit = false;

    _pLabel = new QLabel("test",this);
    _pLabel->setGeometry(geometry());
    _pLabel->show();


    _iFrame = 0;
}
ThreadOpenglWidget::~ThreadOpenglWidget()
{
}
void ThreadOpenglWidget::PlayOneFrame()
{//函数功能读取一张yuv图像数据进行显示,每单击一次，就显示一张图片
    if(NULL == m_pYuvFile)
    {
        //打开yuv视频文件 注意修改文件路径
        m_pYuvFile = fopen("F://yuvfiles//InToTree_1920x1080.yuv", "rb");
        // m_pYuvFile = fopen("/home/administrator/yuv", "rb");
//         m_nVideoW = 320;
//         m_nVideoH = 180;
        //根据yuv视频数据的分辨率设置宽高,demo当中是1080p，这个地方要注意跟实际数据分辨率对应上
        m_nVideoW = 1920;
        m_nVideoH = 1080;
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
    //刷新界面,触发paintGL接口
    update();
    return;
}

void ThreadOpenglWidget::initializeGL()
{
    ThreadOpenglWidget::initializeOpenGLFunctions();
    //glEnable(GL_DEPTH_TEST);
    //现代opengl渲染管线依赖着色器来处理传入的数据
    //着色器：就是使用openGL着色语言(OpenGL Shading Language, GLSL)编写的一个小函数,
    //       GLSL是构成所有OpenGL着色器的语言,具体的GLSL语言的语法需要读者查找相关资料
    //初始化顶点着色器 对象
    m_pVSHader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    //顶点着色器源码
    const char *vsrc = "attribute vec4 vertexIn; \
    attribute vec2 textureIn; \
    varying vec2 textureOut;  \
    void main(void)           \
    {                         \
        gl_Position = vertexIn; \
        textureOut = textureIn; \
    }";
    //编译顶点着色器程序
    bool bCompile = m_pVSHader->compileSourceCode(vsrc);
    if(!bCompile)
    {
    }
    //初始化片段着色器 功能gpu中yuv转换成rgb
    m_pFSHader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    //片段着色器源码
    const char *fsrc = "varying vec2 textureOut; \
    uniform sampler2D tex_y; \
    uniform sampler2D tex_u; \
    uniform sampler2D tex_v; \
    void main(void) \
    { \
        vec3 yuv; \
        vec3 rgb; \
        yuv.x = texture2D(tex_y, textureOut).r; \
        yuv.y = texture2D(tex_u, textureOut).r - 0.5; \
        yuv.z = texture2D(tex_v, textureOut).r - 0.5; \
        rgb = mat3( 1,       1,         1, \
                    0,       -0.39465,  2.03211, \
                    1.13983, -0.58060,  0) * yuv; \
        gl_FragColor = vec4(rgb, 1); \
    }";
    //将glsl源码送入编译器编译着色器程序
    bCompile = m_pFSHader->compileSourceCode(fsrc);
    if(!bCompile)
    {
    }
#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
    //创建着色器程序容器
    m_pShaderProgram = new QOpenGLShaderProgram;
    //将片段着色器添加到程序容器
    m_pShaderProgram->addShader(m_pFSHader);
    //将顶点着色器添加到程序容器
    m_pShaderProgram->addShader(m_pVSHader);
    //绑定属性vertexIn到指定位置ATTRIB_VERTEX,该属性在顶点着色源码其中有声明
    m_pShaderProgram->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    //绑定属性textureIn到指定位置ATTRIB_TEXTURE,该属性在顶点着色源码其中有声明
    m_pShaderProgram->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    //链接所有所有添入到的着色器程序
    m_pShaderProgram->link();
    //激活所有链接
    m_pShaderProgram->bind();
    //读取着色器中的数据变量tex_y, tex_u, tex_v的位置,这些变量的声明可以在
    //片段着色器源码中可以看到
    textureUniformY = m_pShaderProgram->uniformLocation("tex_y");
    textureUniformU =  m_pShaderProgram->uniformLocation("tex_u");
    textureUniformV =  m_pShaderProgram->uniformLocation("tex_v");
    // 顶点矩阵
    static const GLfloat vertexVertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         -1.0f, 1.0f,
         1.0f, 1.0f,
    };
    //纹理矩阵
    static const GLfloat textureVertices[] = {
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
    };
    //设置属性ATTRIB_VERTEX的顶点矩阵值以及格式
    glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, vertexVertices);
    //设置属性ATTRIB_TEXTURE的纹理矩阵值以及格式
    glVertexAttribPointer(ATTRIB_TEXTURE, 2, GL_FLOAT, 0, 0, textureVertices);
    //启用ATTRIB_VERTEX属性的数据,默认是关闭的
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    //启用ATTRIB_TEXTURE属性的数据,默认是关闭的
    glEnableVertexAttribArray(ATTRIB_TEXTURE);
    //分别创建y,u,v纹理对象
    m_pTextureY = ROpenglTexture::createGLTexture(QOpenGLTexture::Target2D);
    m_pTextureU = ROpenglTexture::createGLTexture(QOpenGLTexture::Target2D);
    m_pTextureV = ROpenglTexture::createGLTexture(QOpenGLTexture::Target2D);
//    m_pTextureY->create();
//    m_pTextureU->create();
//    m_pTextureV->create();
    m_pTextureYY = ROpenglTexture::createGLTexture(QOpenGLTexture::Target2D);
    m_pTextureUU = ROpenglTexture::createGLTexture(QOpenGLTexture::Target2D);
    m_pTextureVV = ROpenglTexture::createGLTexture(QOpenGLTexture::Target2D);
//    m_pTextureYY->create();
//    m_pTextureUU->create();
//    m_pTextureVV->create();
//    m_pTextureY->setMinificationFilter(QOpenGLTexture::Linear);
//    m_pTextureY->setMagnificationFilter(QOpenGLTexture::Linear);
//    m_pTextureY->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
//    m_pTextureY->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
//    m_pTextureY->setSize(1920,1080);
//    m_pTextureY->allocateStorage(QOpenGLTexture::Red,QOpenGLTexture::UInt8);
//    m_pTextureU->setMinificationFilter(QOpenGLTexture::Linear);
//    m_pTextureU->setMagnificationFilter(QOpenGLTexture::Linear);
//    m_pTextureU->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
//    m_pTextureU->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
//    m_pTextureY->setSize(1920/2,1080/2);
//    m_pTextureU->allocateStorage(QOpenGLTexture::Red,QOpenGLTexture::UInt8);
//    m_pTextureV->setMinificationFilter(QOpenGLTexture::Linear);
//    m_pTextureV->setMagnificationFilter(QOpenGLTexture::Linear);
//    m_pTextureV->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
//    m_pTextureV->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
//    m_pTextureY->setSize(1920/2,1080/2);
//    m_pTextureV->allocateStorage(QOpenGLTexture::Red,QOpenGLTexture::UInt8);
    //获取返回y分量的纹理索引值

    id_y = m_pTextureY->textureId();
    id_u = m_pTextureU->textureId();
    id_v = m_pTextureV->textureId();
    id_yy = m_pTextureYY->textureId();
    id_uu = m_pTextureUU->textureId();
    id_vv = m_pTextureVV->textureId();
//    new_texture(&id_y);
//    new_texture(&id_u);
//    new_texture(&id_v);
   glClearColor(0.3,0.3,0.3,0.0);//设置背景色 gl
    //glClearColor(0.3,0.3,0.3,0.0);//设置背景色
    //qDebug("addr=%x id_y = %d id_u=%d id_v=%d\n", this, id_y, id_u, id_v);

}
void ThreadOpenglWidget::resizeGL(int w, int h)
{
    if(h == 0)// 防止被零除
    {
        h = 1;// 将高设为1
    }

    QOpenGLWidget::resizeGL(w,h);
    //设置视口
    glViewport(0,0, w,h);
}


QRect ThreadOpenglWidget::viewPortRect(QRectF rectf, int frameW, int frameH, bool bAspect /*= true*/)
{
    int winW = this->width();
    int winH = this->height();

    int x = winW *rectf.left();
    int y = winH *rectf.top();
    int w = winW * rectf.width();
    int h = winH * rectf.height();


    QRect tmpRect = this->rect();

    //保持宽高比计算
    if (frameH == 0)
    {
        frameH = 1;
    }
    float fAspect = 1.0 * frameW / frameH;
    if (h == 0)
    {
        h = 1;
    }
    QRect viewPortRect(x, y, w, h);
    return viewPortRect;
    float videoRenderAspect = 1.0 * w / h;

    if (videoRenderAspect > fAspect)
    {
        w = h * fAspect;
        x += 0.5 * (viewPortRect.width() - w);
    }
    else{
        h = viewPortRect.width() / fAspect;
        y += 0.5 * (viewPortRect.height() - h);
    }

    return QRect(x + 1, y + 1, w - 2, h - 2);
}
 void ThreadOpenglWidget::paintGL()
 {
//     if( !m_pBufYuv420p )return;
//     QOpenGLWidget::paintGL();

     //glViewport(width()/2,0, width()/2,height()/2);

     if( _iFrame == 0 ){
         _timer.start();
     }
     ++_iFrame;
     if( _iFrame == 900){
         double fElapsed = _timer.elapsed()/1000.0;
         qDebug()<<"900 frames took="<<fElapsed<<",fps="<<1.0*_iFrame/fElapsed<<endl;
         _iFrame = 0;
         _timer.restart();
     }
     int winW = this->width();
     int winH = this->height();

     glViewport(0,0,winW,winH);
     render_new();
     return;

    if( m_bEnableScissor )     glEnable(GL_SCISSOR_TEST);

     QList<QPoint> topLefts;
     topLefts.append(QPoint(0,0));
     topLefts.append(QPoint(width()/2,0));
     topLefts.append(QPoint(0,height()/2));
     topLefts.append(QPoint(width()/2,height()/2));

     QList<QPoint> bottomRight;
     bottomRight.append(QPoint(width()/2,height()/2));
     bottomRight.append(QPoint(width(),height()/2));
     bottomRight.append(QPoint(width()/2,height()));
     bottomRight.append(QPoint(width(),height()));

     QList<QRectF> rectFs;
     //rectFs.append(QRectF(0,0,0.5,0.5));
     rectFs.append(QRectF(0,0,1.0,1.0));
     rectFs.append(QRectF(0.5,0,0.5,0.5));
     rectFs.append(QRectF(0,0.5,0.5,0.5));
     rectFs.append(QRectF(0.5,0.5,0.5,0.5));


//    context()->makeCurrent(context()->surface());
    for(int i = 0;i<1;i++){
           QRectF tmpRectF = rectFs[i];
           GLint x = winW *tmpRectF.topLeft().x();
           GLint y = winH *tmpRectF.topLeft().y();
           GLsizei w = winW *tmpRectF.width();
           GLsizei h = winH * tmpRectF.height();
           GLint tmpY = winH - (y + h);
           if( m_bEnableScissor )
               glScissor(x, winH-(y+h), w, h);
//           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//           switch(i){
//           case 0:glClearColor(1.0 ,0.0,0.0,0);break;
//           case 1:glClearColor(0.0 ,1.0,0.0,0);break;
//           case 2:glClearColor(0.0 ,0.0,1.0,0);break;
//           defaul:glClearColor(1.0 ,0.0,0.0,0);break;
//           }


//           glViewport(x + 5, tmpY + 5  ,w - 10,h - 10);


           if( i == 0 ){
               glViewport(0,0,winW,winH);
               render_new();
           }else{
               render_new1();
           }

//           const GLfloat vertices[] = {

//                   -1,-1, 0, // 左下，黑色

//               -1, 1, 0, // 左上，蓝色

//               1, 1, 0, // 右上，绿色
//               1,-1, 0, // 右下，红色
//               1,-1, 0, // 右下，红色

//                   -1, 1, 0, // 左上，蓝色
//               };
//               const GLfloat colors[] = {
//                   0,0,0,1, // 左下，黑色
//                   1,0,0,1, // 右下，红色
//                   0,0,1,1, // 左上，蓝色

//                   1,0,0,1, // 右下，红色
//                   0,0,1,1, // 左上，蓝色
//                   0,1,0,1, // 右上，绿色
//               };

//               glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
//               glEnableVertexAttribArray(0);

//               glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, colors);
//               glEnableVertexAttribArray(0);
//           glDrawArrays(GL_LINE_LOOP, 0, 4);
    }


//    context()->doneCurrent();
    if( m_bEnableScissor )
        glDisable(GL_SCISSOR_TEST);
 }

 void ThreadOpenglWidget::timerEvent(QTimerEvent *e)
 {
     update();
 }

 void ThreadOpenglWidget::render_new1()
 {
     if( !m_pBufYuv420p1 ) return;
          glActiveTexture(GL_TEXTURE0);//激活纹理单元GL_TEXTURE0
          glBindTexture(GL_TEXTURE_2D,id_yy);
          //使用内存中m_pBufYuv420p数据创建真正的y数据纹理
          //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoWW, m_nVideoHH, 0, GL_RED, GL_UNSIGNED_BYTE, m_pBufYuv420p1);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

          //加载u数据纹理
          glActiveTexture(GL_TEXTURE1);//激活纹理单元GL_TEXTURE1
          glBindTexture(GL_TEXTURE_2D, id_uu);
          //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoWW/2, m_nVideoHH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p1+m_nVideoWW*m_nVideoHH);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          //加载v数据纹理
          glActiveTexture(GL_TEXTURE2);//激活纹理单元GL_TEXTURE2
          glBindTexture(GL_TEXTURE_2D, id_vv);
          //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoWW/2, m_nVideoHH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p1+m_nVideoWW*m_nVideoHH*5/4);

          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

          glUniform1i(textureUniformY, 0);
          glUniform1i(textureUniformU, 1);
          glUniform1i(textureUniformV, 2);
          //使用顶点数组方式绘制图形
          glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 }
 void ThreadOpenglWidget::render_new()
 {

     if( !m_pBufYuv420p ) return;
          glActiveTexture(GL_TEXTURE0);//激活纹理单元GL_TEXTURE0
          glBindTexture(GL_TEXTURE_2D,getId_y());
          //使用内存中m_pBufYuv420p数据创建真正的y数据纹理
          //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoW, m_nVideoH, 0, GL_RED, GL_UNSIGNED_BYTE, m_pBufYuv420p);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

          //加载u数据纹理
          glActiveTexture(GL_TEXTURE1);//激活纹理单元GL_TEXTURE1
          glBindTexture(GL_TEXTURE_2D, getId_u());
          //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoW/2, m_nVideoH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p+m_nVideoW*m_nVideoH);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          //加载v数据纹理
          glActiveTexture(GL_TEXTURE2);//激活纹理单元GL_TEXTURE2
          glBindTexture(GL_TEXTURE_2D, getId_v());
          //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoW/2, m_nVideoH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p+m_nVideoW*m_nVideoH*5/4);

          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

          glUniform1i(textureUniformY, 0);
          glUniform1i(textureUniformU, 1);
          glUniform1i(textureUniformV, 2);
          //使用顶点数组方式绘制图形
          glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 }

 GLuint ThreadOpenglWidget::getId_y()
 {
     return id_y;
 }
 GLuint ThreadOpenglWidget::getId_u()
 {
     return id_u;
 }
 GLuint ThreadOpenglWidget::getId_v()
 {
     return id_v;
 }

 void ThreadOpenglWidget::new_texture(GLuint *textures)
 {
     glGenTextures(1,textures);
 }
 void ThreadOpenglWidget::updateFrame(unsigned char *pData)
 {
     m_pBufYuv420p = pData;
     updateTexture();
     update();
 }

 void ThreadOpenglWidget::updateFrame1(unsigned char *pData)
 {
     m_pBufYuv420p1 = pData;
     updateTexture1();
     update();
 }

#include <QApplication>

 void ThreadOpenglWidget::onRenderFrame(unsigned char *pData, int w, int h)
 {
    
     moveToThread(qApp->thread()->currentThread());
     m_nVideoW = w;
     m_nVideoW = h;
     updateFrame(pData);
 }

 void ThreadOpenglWidget::updateTexture()
 {
    glBindTexture(GL_TEXTURE_2D,getId_y());
         //m_pTextureY->bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoW, m_nVideoH, 0, GL_RED, GL_UNSIGNED_BYTE, m_pBufYuv420p);

    glBindTexture(GL_TEXTURE_2D,getId_u());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoW/2, m_nVideoH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p+m_nVideoW*m_nVideoH);

    glBindTexture(GL_TEXTURE_2D,getId_v());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoW/2, m_nVideoH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p+m_nVideoW*m_nVideoH*5/4);

 }

 void ThreadOpenglWidget::updateTexture1()
 {
     glBindTexture(GL_TEXTURE_2D,id_yy);
          //m_pTextureY->bind();
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoWW, m_nVideoHH, 0, GL_RED, GL_UNSIGNED_BYTE, m_pBufYuv420p1);

     glBindTexture(GL_TEXTURE_2D,id_uu);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoWW/2, m_nVideoHH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p1+m_nVideoWW*m_nVideoHH);

     glBindTexture(GL_TEXTURE_2D,id_vv);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_nVideoWW/2, m_nVideoHH/2, 0, GL_RED, GL_UNSIGNED_BYTE, (char*)m_pBufYuv420p1+m_nVideoWW*m_nVideoHH*5/4);
 }

