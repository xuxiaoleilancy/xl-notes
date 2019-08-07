#-------------------------------------------------
#
# Project created by QtCreator 2019-03-18T18:25:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengldemo
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    gplaywidget.cpp \
    yuvthread.cpp \
    threadopenglwidget.cpp \
    ropengltexture.cpp \
    yuvthread_nv12.cpp \
    nv12renderwidget.cpp

HEADERS  += widget.h \
    gplaywidget.h \
    yuvthread.h \
    threadopenglwidget.h \
    ropengltexture.h \
    yuvthread_nv12.h \
    nv12renderwidget.h

FORMS    += widget.ui

