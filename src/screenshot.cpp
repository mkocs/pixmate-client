#include <QtWidgets>
#include <QApplication>
#include <QScreen>
#include <QDateTime>
#include <QDate>
#include <QCoreApplication>
#include <QObject>
#include "src/screenshot.h"
#include "src/mainwindow.h"

Screenshot::Screenshot() {
}

void Screenshot::take_screenshot() {
  QScreen *screen = QGuiApplication::primaryScreen();
  if (screen)
    set_pixmap(screen->grabWindow(0));
}

QPixmap *Screenshot::get_pixmap() {
  return &original_pixmap_;
}

QString Screenshot::get_pixmap_title() {
  return pixmap_title_;
}

void Screenshot::set_pixmap_title(QString title) {
  pixmap_title_ = title;
}

void Screenshot::set_pixmap(QPixmap pixmap) {
  original_pixmap_ = pixmap;
  QDateTime date_time = QDateTime::currentDateTime();
  QString date_time_string = date_time.toString("yyyy-MM-dd hh.mm.ss");
  set_pixmap_title(QObject::tr("Screenshot-%1 at %2").arg(date_time_string.split(' ')[0]).arg(date_time_string.split(' ')[1]));
}
