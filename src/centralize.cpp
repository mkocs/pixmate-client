#include "centralize.h"
#include <QDesktopWidget>
#include <QCursor>

namespace Centralize {
  void center_window(QWidget *widget) {
    QDesktopWidget *desktop_widget;
    desktop_widget = new QDesktopWidget();
    if (desktop_widget->screenCount() > 1) {
      int start_x = 0, start_y = 0;
      int end_x = 0, end_y = 0;
      int cursor_x = QCursor::pos().x();
      int cursor_y = QCursor::pos().y();
      for(int i = 0; i < desktop_widget->screenCount(); i++) {
        if (i > 0) {
          start_x += end_x;
          end_x += desktop_widget->screenGeometry(i).width();
          end_y += desktop_widget->screenGeometry(i).height();
        } else {
          start_x = 0;
          end_x = desktop_widget->screenGeometry(i).width();
          end_y = desktop_widget->screenGeometry(i).height();
        }
        if (cursor_x >= start_x && cursor_x <= end_x &&
            cursor_y >= start_y && cursor_y <= end_y) {
          widget->move(start_x + (desktop_widget->screenGeometry(i).width()/2-(widget->width()/2)),
                       desktop_widget->screenGeometry(i).height()/2-widget->height()/2);
        }
      }
    } else {
      widget->move((desktop_widget->screenGeometry(0).width()/2-widget->width()/2),
                   (desktop_widget->screenGeometry(0).height()/2-widget->height()/2));
    }
  }
}
