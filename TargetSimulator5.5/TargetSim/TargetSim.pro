#-------------------------------------------------
#
# Project created by QtCreator 2022-03-11T00:38:12
#
#-------------------------------------------------

QT       += widgets network sql 3dcore 3drenderer 3dinput 3dquick

TARGET = TargetSim
TEMPLATE = lib

CONFIG += c++11

DEFINES += TARGETSIM_LIBRARY

SOURCES += targetsim.cpp \
    basemodel.cpp \
    simulatormodel.cpp \
    basetarget.cpp \
    baseview.cpp \
    mapview.cpp \
    mapviewtarget.cpp \
    cameraview.cpp \
    camerawindow.cpp

HEADERS += targetsim.h\
        targetsim_global.h \
    basemodel.h \
    simulatormodel.h \
    basetarget.h \
    baseview.h \
    mapview.h \
    mapviewtarget.h \
    cameraview.h \
    camerawindow.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    qml.qrc
