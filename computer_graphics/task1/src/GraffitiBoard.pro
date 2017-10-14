#-------------------------------------------------
#
# Project created by QtCreator 2017-10-13T18:24:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraffitiBoard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG  += c++11

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        tools/Log.cpp \
        tools/Utils.cpp \
        view/MainWindow.cpp \
        view/BoardView.cpp \
        model/Board.cpp \
        model/figures/Figure.cpp \
        model/figures/Line.cpp \
        model/figures/Ellipse.cpp \
        model/figures/Polygon.cpp \
        model/figures/FreeDraw.cpp

HEADERS += \
        Constants.h \
        tools/Log.h \
        tools/Utils.h \
        view/MainWindow.h \
        view/BoardView.h \
        model/Board.h \
        model/figures/Figure.h \
        model/figures/Line.h \
        model/figures/Ellipse.h \
        model/figures/Polygon.h \
        model/figures/FreeDraw.h

FORMS += \
        MainWindow.ui \
        BoardView.ui
