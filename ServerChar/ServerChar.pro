#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T09:05:04
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerChar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    server.h \
    commands.h

FORMS    += mainwindow.ui
