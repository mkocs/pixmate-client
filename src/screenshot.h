#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QPixmap>

class Screenshot
{
 public:
  Screenshot();

  // Returns the screenshot pixmap
  QPixmap *get_pixmap();
  void set_pixmap(QPixmap pixmap);
  void take_screenshot();

 private:
  QPixmap original_pixmap_;
};

#endif // SCREENSHOT_H
