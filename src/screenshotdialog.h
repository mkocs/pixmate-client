#ifndef SCREENSHOTDIALOG_H
#define SCREENSHOTDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QPixmap>
#include "src/screenshot.h"

namespace Ui {
class ScreenshotDialog;
}

class ScreenshotDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ScreenshotDialog(QWidget *parent = 0, Screenshot* screenshot = 0);
  ~ScreenshotDialog();
  void closeEvent(QCloseEvent *event);
private slots:
  void save_screenshot();

signals:
  void dialogClosed();

private:
  void set_label_pixmap();
  Ui::ScreenshotDialog *ui;
  QWidget *parent_;
  Screenshot *screenshot_;
};

#endif // SCREENSHOTDIALOG_H
