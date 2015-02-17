#-------------------------------------------------
#
# Project created by QtCreator 2014-10-12T23:08:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectOne5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mapeditor.cpp \
    bd_api.cpp \
    BDObjects/objects.cpp \
    showmap.cpp \
    objectinfo.cpp \
    objquestion.cpp \
    newmap.cpp

HEADERS  += mainwindow.h \
    mapeditor.h \
    bd_api.h \
    BDObjects/Error.h \
    BDObjects/objects.h \
    BDObjects/TypeConst.h \
    showmap.h \
    objectinfo.h \
    objquestion.h \
    newmap.h

FORMS    += mainwindow.ui \
    showmap.ui \
    objectinfo.ui \
    objquestion.ui \
    newmap.ui
