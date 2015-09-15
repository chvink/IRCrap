#-------------------------------------------------
#
# Project created by QtCreator 2015-09-13T23:19:04
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ircrap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ircmessage.cpp \
    ircmanager.cpp \
    channeldisplay.cpp

HEADERS  += mainwindow.h \
    ircmessage.h \
    ircmanager.h \
    channeldisplay.h \
    enum.h

FORMS    += mainwindow.ui \
    channeldisplay.ui
