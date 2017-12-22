#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T20:05:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinimalSurfaces
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

# to use triangle library
#       1. build triangle.o with the following command(*some options may need to change according to your project*):
#            g++ -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib -DTRILIBRARY \
#                 -c -o ./triangle.o -m64 -pipe -g -std=c++0x -Wall -W -D_REENTRANT \
#                 -DANSI_DECLARATORS -fPIE ./triangle.c
#       2. copy the generated triangle.o in step 1 to where your objective files locate
#       3. add the following two lines to the qt project's pro file(this file)
# DEFINES += ANSI_DECLARATORS REAL=double VOID=void
# LIBS += triangle.o

DEFINES += FALSE=false TRUE=true

SOURCES += \
        main.cpp \
        view/MainWindow.cpp \
        view/RenderingWidget.cpp \
        model/HE_mesh/Mesh3D.cpp \
        model/ArcBall.cpp

HEADERS += \
#        libs/triangle/triangle.h
        view/MainWindow.h \
        view/RenderingWidget.h \
        GlobalFunctions.h \
        model/HE_mesh/Mesh3D.h \
        model/HE_mesh/Vec.h \
        model/ArcBall.h

LIBS += -lglut -lGLU

FORMS += \
        view/MainWindow.ui

RESOURCES += \
        MainWindow.qrc
