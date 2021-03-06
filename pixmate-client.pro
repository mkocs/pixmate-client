QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pixmate
TEMPLATE = app

CONFIG += c++11

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/screenshot.cpp \
    src/regionselectiondialog.cpp \
    src/screenshotdialog.cpp \
    src/share.cpp \
    src/messagedialog.cpp \
    src/centralize.cpp \
    src/gkeys.cpp

HEADERS  += src/mainwindow.h \
    src/screenshot.h \
    src/regionselectiondialog.h \
    src/screenshotdialog.h \
    src/share.h \
    src/messagedialog.h \
    src/centralize.h \
    src/gkeys.h

FORMS    += ui/mainwindow.ui \
    ui/screenshotdialog.ui \
    ui/messagedialog.ui

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

include(./lib/QHotkey/qhotkey.pri)

macx {
    ICON = img/pixmate.icns
}

win32 {
    ICON = img/pixmate.ico
}

unix:!macx {
    isEmpty(PREFIX): PREFIX = /usr
    target.files = pixmate
    target.path = $$PREFIX/bin
    INSTALLS = target

    appicons256.files=img/256/pixmate.png
    appicons256.path=$$PREFIX/share/applications/hicolor/256x256/apps
    appicons128.files=img/128/pixmate.png
    appicons128.path=$$PREFIX/share/applications/hicolor/128x128/apps

    desktop.files = pixmate.desktop
    desktop.path = $$PREFIX/share/applications
    INSTALLS += appicons256 appicons128 desktop
}

