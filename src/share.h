#ifndef SHARE_H
#define SHARE_H

#include "src/screenshot.h"
#include <QPixmap>
#include <QByteArray>
#include <QNetworkReply>
#include <QObject>
#include <QDialog>

class Share : public QObject{
  Q_OBJECT

 public:
  Share(QDialog* sender, Screenshot* screen_shot);
  ~Share();
  void share_screenshot(QPixmap *pixmap);

 private slots:
  void reply_finished(QNetworkReply *);

 private:
  QDialog *sender_;
  Screenshot* screenshot_;
  QByteArray convert_pxm_to_bytearray(QPixmap *pixmap);
  void upload(const QByteArray &data);
  void copy_url_to_clipboard(QNetworkReply *reply);
};

#endif
