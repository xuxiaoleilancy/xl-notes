#-------------------------------------------------
#
# Project created by QtCreator 2019-03-18T18:25:37
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengldemo
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    gplaywidget.cpp

HEADERS  += widget.h \
    gplaywidget.h

FORMS    += widget.ui
