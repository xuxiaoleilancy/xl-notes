#-------------------------------------------------
#
# Project created by QtCreator 2019-03-18T18:25:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yuvrender_thread
TEMPLATE = app


SOURCES += main.cpp\
    yuvthread.cpp \
    threadopenglwidget.cpp \
    ropengltexture.cpp

HEADERS  += yuvthread.h \
    threadopenglwidget.h \
    ropengltexture.h

