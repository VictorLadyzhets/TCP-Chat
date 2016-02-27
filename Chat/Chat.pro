#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T21:31:14
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    server.h \
    commandcodes.h


FORMS    += mainwindow.ui
