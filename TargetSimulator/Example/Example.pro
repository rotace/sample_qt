#-------------------------------------------------
#
# Project created by QtCreator 2022-03-11T00:53:47
#
#-------------------------------------------------

QT       += core gui widgets network sql 3dcore 3drenderer 3dinput 3dquick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$OUT_PWD/../TargetSim/ -lTargetSim

INCLUDEPATH += $$PWD/../TargetSim
DEPENDPATH += $$PWD/../TargetSim
