/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "gplaywidget.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    CPlayWidget *wdg1;
    CPlayWidget *wdg2;
    CPlayWidget *wdg3;
    CPlayWidget *wdg4;
    CPlayWidget *wdg5;
    CPlayWidget *wdg6;
    CPlayWidget *wdg7;
    CPlayWidget *wdg8;
    CPlayWidget *wdg9;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1072, 707);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        wdg1 = new CPlayWidget(Widget);
        wdg1->setObjectName(QStringLiteral("wdg1"));

        gridLayout->addWidget(wdg1, 0, 0, 1, 1);

        wdg2 = new CPlayWidget(Widget);
        wdg2->setObjectName(QStringLiteral("wdg2"));

        gridLayout->addWidget(wdg2, 0, 1, 1, 1);

        wdg3 = new CPlayWidget(Widget);
        wdg3->setObjectName(QStringLiteral("wdg3"));

        gridLayout->addWidget(wdg3, 0, 2, 1, 1);

        wdg4 = new CPlayWidget(Widget);
        wdg4->setObjectName(QStringLiteral("wdg4"));

        gridLayout->addWidget(wdg4, 1, 0, 1, 1);

        wdg5 = new CPlayWidget(Widget);
        wdg5->setObjectName(QStringLiteral("wdg5"));

        gridLayout->addWidget(wdg5, 1, 1, 1, 1);

        wdg6 = new CPlayWidget(Widget);
        wdg6->setObjectName(QStringLiteral("wdg6"));

        gridLayout->addWidget(wdg6, 1, 2, 1, 1);

        wdg7 = new CPlayWidget(Widget);
        wdg7->setObjectName(QStringLiteral("wdg7"));

        gridLayout->addWidget(wdg7, 2, 0, 1, 1);

        wdg8 = new CPlayWidget(Widget);
        wdg8->setObjectName(QStringLiteral("wdg8"));

        gridLayout->addWidget(wdg8, 2, 1, 1, 1);

        wdg9 = new CPlayWidget(Widget);
        wdg9->setObjectName(QStringLiteral("wdg9"));

        gridLayout->addWidget(wdg9, 2, 2, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
