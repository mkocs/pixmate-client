#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QPixmap>
#include <QString>

class Screenshot
{
 public:
  Screenshot();

  // Returns the screenshot pixmap
  QPixmap *get_pixmap();
  QString get_pixmap_title();
  void set_pixmap(QPixmap pixmap);
  void take_screenshot();

 private:
  QPixmap original_pixmap_;
  QString pixmap_title_;
};

#endif // SCREENSHOT_H
