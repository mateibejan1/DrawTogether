#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T20:47:08
#
#-------------------------------------------------

QT       += core gui \
         printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToucyTree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp \
    paintdata.cpp \
    drawboard.cpp \
    updateframe.cpp \
    winclient.cpp

HEADERS  += mainwindow.h \
    treeitem.h \
    treemodel.h \
    paintdata.h \
    drawboard.h \
    winclient.h \
    request.h

FORMS    += mainwindow.ui

RESOURCES += \
    treemodel.qrc

LIBS += -lws2_32
