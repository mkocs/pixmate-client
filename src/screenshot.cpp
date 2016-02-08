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
    original_pixmap_ = screen->grabWindow(0);
}

QPixmap *Screenshot::get_pixmap() {
  return &original_pixmap_;
}

QString Screenshot::get_pixmap_title() {
  return pixmap_title_;
}

void Screenshot::set_pixmap(QPixmap pixmap) {
  original_pixmap_ = pixmap;
  QDateTime *date_time = new QDateTime();
  QDate date = date_time->date();
  QTime time = date_time->time();
  pixmap_title_ = QObject::tr("Screenshot-%1%2%3%4%5%6").arg(date.year()).arg(date.month()).arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second());
}
