#ifndef ROPENGLTEXTURE_H
#define ROPENGLTEXTURE_H

#include <QOpenGLTexture>
#include <QOpenGLWidget>

class ROpenglTexture : public QObject
{
    Q_OBJECT
public:
    ROpenglTexture(QOpenGLWidget* parent=0);
    ~ROpenglTexture();

    static QOpenGLTexture *createGLTexture(QOpenGLTexture::Target target);
};

#endif // ROPENGLTEXTURE_H
