#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T20:05:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SurfaceParameterization
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG  += c++11

DEFINES += FALSE=false TRUE=true

SOURCES += \
        main.cpp \
        model/ArcBall.cpp \
        model/HE_mesh/Mesh3D.cpp \
        view/MainWindow.cpp \
        view/RenderingWidget.cpp \
        utils/Utils.cpp

HEADERS += \
#        libs/triangle/triangle.h
        model/ArcBall.h \
        view/MainWindow.h \
        view/RenderingWidget.h \
        GlobalFunctions.h \
        model/HE_mesh/Mesh3D.h \
        model/HE_mesh/Vec.h \
        utils/Logger.h \
        Utils/Utils.h

LIBS += -lglut -lGLU

FORMS += \
        view/MainWindow.ui

RESOURCES += \
        MainWindow.qrc
