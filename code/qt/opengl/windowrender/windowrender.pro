#-------------------------------------------------
#
# Project created by QtCreator 2019-03-18T18:25:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = windowRender
TEMPLATE = app


SOURCES += main.cpp\
    openglwindow.cpp \
    yuvthread.cpp

HEADERS  += openglwindow.h \
			yuvthread.h

