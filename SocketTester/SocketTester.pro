#-------------------------------------------------
#
# Project created by QtCreator 2022-04-12T21:16:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocketTester
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractsocketwidget.cpp \
    tcpsocketwidget.cpp \
    udpsocketwidget.cpp

HEADERS  += mainwindow.h \
    abstractsocketwidget.h \
    tcpsocketwidget.h \
    udpsocketwidget.h

FORMS    += mainwindow.ui
