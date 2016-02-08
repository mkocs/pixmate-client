#include "src/share.h"
#include "src/messagedialog.h"
#include <QBuffer>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QFile>
#include <QHttpPart>
#include <QVariant>
#include <QApplication>
#include <QTextCodec>
#include <QClipboard>

Share::Share(QDialog *sender, Screenshot *screenshot) {
  sender_ = sender;
  screenshot_ = screenshot;
}

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
  text_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"title\"\""));
  QTextCodec *codec = QTextCodec::codecForName("UTF-16");
  QTextEncoder *encoderWithoutBom = codec->makeEncoder(QTextCodec::IgnoreHeader);
  QByteArray bytes  = encoderWithoutBom ->fromUnicode(screenshot_->get_pixmap_title());
  text_part.setBody(bytes);
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

// Documentation for QNetworkReply error codes: http://doc.qt.io/qt-5/qnetworkreply.html#NetworkError-enum
void Share::reply_finished(QNetworkReply *reply) {
  MessageDialog *mdiag;
  switch (reply->error()) {
  case QNetworkReply::NoError:
    {
      copy_url_to_clipboard(reply);
      mdiag = new MessageDialog(sender_, ("Upload successful.\nThe URL is in your clipboard."));
      break;
    }
  case QNetworkReply::ConnectionRefusedError:
    {
      mdiag = new MessageDialog(sender_, "The remote server refused the connection.");
      break;
    }
  case QNetworkReply::TimeoutError:
    {
      mdiag = new MessageDialog(sender_, "The connection timed out.");
      break;
    }
  default:
    {
      mdiag = new MessageDialog(sender_, "I'm sorry. An error occured and I could not finish the upload.");
      break;
    }
  }
  mdiag->exec();
}

// Server returns the ID for the uploaded image
// This ID is copied to the clipboard, so it can
// easily be shared.
void Share::copy_url_to_clipboard(QNetworkReply *reply) {
  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText("http://localhost:8000/" + reply->readAll());
}

