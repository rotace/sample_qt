TEMPLATE = app

QT += core gui widgets qml quick 3dcore 3drenderer 3dinput 3dquick
CONFIG += c++11

SOURCES += main.cpp \
    window.cpp \
    mainwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    window.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

