#include <QtWidgets>
#include <QApplication>
#include <QScreen>
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

void Screenshot::set_pixmap(QPixmap pixmap) {
  original_pixmap_ = pixmap;
}
