#ifndef SHARE_H
#define SHARE_H

#include "src/screenshot.h"
#include <QPixmap>
#include <QByteArray>
#include <QNetworkReply>
#include <QObject>
#include <QDialog>
#define TTL_TIME_DEFAULT 80640 
#define TTL_VIEWS_DEFAULT -1

class Share : public QObject
{
  Q_OBJECT

public:
    Share(QWidget* sender, Screenshot* screenshot, bool show_f_dialog = true);
    ~Share();
    void share_screenshot(int ttlTime = TTL_TIME_DEFAULT, int ttlViews = TTL_VIEWS_DEFAULT);

private slots:
    void reply_finished(QNetworkReply *);

private:
    QWidget *sender_;
    Screenshot* screenshot_;
    QByteArray convert_pxm_to_bytearray(QPixmap *pixmap);
    void upload(const QByteArray &data, int ttlTime, int ttlViews);
    void copy_url_to_clipboard(QNetworkReply *reply);
    bool show_f_dialog_;
};

#endif
