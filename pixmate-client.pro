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
    src/screenshot.cpp \
    src/regionselectiondialog.cpp \
    src/screenshotdialog.cpp

HEADERS  += src/mainwindow.h \
    src/screenshot.h \
    src/regionselectiondialog.h \
    src/screenshotdialog.h

FORMS    += ui/mainwindow.ui \
    ui/screenshotdialog.ui

DISTFILES += \
    img/ic_alarm_black_24dp.ico \
    img/ic_camera_black_24dp.ico \
    img/ic_close_black_24dp.ico \
    img/ic_cloud_upload_black_24dp.ico \
    img/ic_crop_black_24dp.ico \
    img/ic_desktop_windows_black_24dp.ico \
    img/ic_done_black_24dp.ico \
    img/ic_error_outline_black_24dp.ico

RESOURCES += \
    resources.qrc
