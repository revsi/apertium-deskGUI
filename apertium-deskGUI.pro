#-------------------------------------------------
#
# Project created by QtCreator 2015-02-20T23:57:14
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = apertium-deskGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
DEFINES += CURL_STATICLIB
INCLUDEPATH += /usr/include/curl
LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lcurl

DISTFILES += \
    apertium-deskGUI.pro.user \
    Readme.md

