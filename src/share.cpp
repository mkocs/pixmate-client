#include "src/share.h"
#include <QBuffer>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>

Share::Share() {}

Share::~Share() {}

void Share::share_screenshot(QPixmap *pixmap) {
  QByteArray byte_array = convert_pxm_to_bytearray(pixmap);
  upload(&byte_array);
}

QByteArray Share::convert_pxm_to_bytearray(QPixmap *pixmap) {
  QByteArray byte_array;
  QBuffer buffer(&byte_array);
  buffer.open(QIODevice::WriteOnly);
  pixmap->save(&buffer, "PNG");
  return byte_array;
}

void Share::upload(QByteArray *data) {
  QNetworkAccessManager *am = new QNetworkAccessManager();
  QNetworkRequest request(QUrl("http://localhost:8000/api/upload"));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "image/ief");
  qDebug() << data;
  connect(am, SIGNAL(finished(QNetworkReply *)), this, SLOT(reply_finished(QNetworkReply *)));
  am->post(request, *data);
}

void Share::reply_finished(QNetworkReply *) {
  
}
