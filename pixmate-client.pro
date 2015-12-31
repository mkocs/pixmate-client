#-------------------------------------------------
#
# Project created by QtCreator 2015-12-31T11:30:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pixmate
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/screenshot.cpp

HEADERS  += src/mainwindow.h \
    src/screenshot.h

FORMS    += ui/mainwindow.ui
