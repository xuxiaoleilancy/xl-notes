#include "ropengltexture.h"


QOpenGLTexture *ROpenglTexture::createGLTexture(QOpenGLTexture::Target target)
{
    QOpenGLTexture* pTexture = new QOpenGLTexture(target);
    pTexture->create();

    return pTexture;
}
