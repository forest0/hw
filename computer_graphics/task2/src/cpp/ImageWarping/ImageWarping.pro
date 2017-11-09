#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T20:31:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Imagewarping
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

CONFIG  += c++11

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    view/ImageView.cpp \
    view/MainWindow.cpp \
    warping/ImageWarper.cpp \
    warping/Mapper.cpp \
    warping/IDWMapper.cpp \
    warping/RBFMapper.cpp \
    tools/Log.cpp \
    tools/Utils.cpp

HEADERS += \
    view/ImageView.h \
    view/MainWindow.h \
    warping/ImageWarper.h \
    warping/Mapper.h \
    warping/IDWMapper.h \
    warping/RBFMapper.h \
    tools/Log.h \
    tools/Utils.h

FORMS += \
    view/MainWindow.ui
