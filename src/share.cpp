#include "src/share.h"
#include <QBuffer>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QFile>
#include <QHttpPart>
#include <QVariant>

Share::Share() {}

Share::~Share() {}

void Share::share_screenshot(QPixmap *pixmap) {
  QByteArray byte_array = convert_pxm_to_bytearray(pixmap);
  upload(byte_array);
}

QByteArray Share::convert_pxm_to_bytearray(QPixmap *pixmap) {
  QByteArray byte_array;
  QBuffer buffer(&byte_array);
  buffer.open(QIODevice::WriteOnly);
  pixmap->save(&buffer, "PNG");
  return byte_array;
}

void Share::upload(const QByteArray &data) {
  QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  QHttpPart text_part;
  text_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\"\""));
  text_part.setBody("Screenshot.png");
  QHttpPart image_part;
  image_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
  image_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"Screenshot.png\""));
  image_part.setBody(data);
  multi_part->append(text_part);
  multi_part->append(image_part);
  QNetworkRequest request(QUrl("http://localhost:8000/api/upload"));
  QNetworkAccessManager *manager = new QNetworkAccessManager();
  connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(reply_finished(QNetworkReply *)));
  manager->post(request, multi_part);
}

void Share::reply_finished(QNetworkReply *) {
}
