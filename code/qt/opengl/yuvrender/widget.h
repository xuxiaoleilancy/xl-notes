#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void PlayOneFrame();
private:
    Ui::Widget *ui;

    int m_nVideoW; //视频分辨率宽
    int m_nVideoH; //视频分辨率高
    unsigned char* m_pBufYuv420p;
    FILE* m_pYuvFile;
};

#endif // WIDGET_H
