#ifndef SHARE_H
#define SHARE_H

#include <QPixmap>
#include <QByteArray>
#include <QNetworkReply>
#include <QObject>

class Share : public QObject{
  Q_OBJECT

 public:
  Share();
  ~Share();
  void share_screenshot(QPixmap *pixmap);

 private slots:
  void reply_finished(QNetworkReply *);
  
 private:
  QByteArray convert_pxm_to_bytearray(QPixmap *pixmap);
  void upload(QByteArray *data);
};

#endif
