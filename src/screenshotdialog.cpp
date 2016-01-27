#include "src/screenshotdialog.h"
#include "ui_screenshotdialog.h"
#include <QDesktopWidget>
#include <QString>
#include <QDir>
#include <QFileDialog>

ScreenshotDialog::ScreenshotDialog(QWidget *parent, Screenshot* screenshot) :
  QDialog(parent),
  ui(new Ui::ScreenshotDialog)
{
  ui->setupUi(this);

  parent_ = parent;

  QDesktopWidget *widget;
  widget = new QDesktopWidget();
  move((widget->screenGeometry(0).width()/2-this->width()/2), (widget->screenGeometry(0).height()/2-this->height()/2));

  ui->screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui->screenshotLabel->setAlignment(Qt::AlignCenter);
  ui->screenshotLabel->setMinimumSize(240, 160);

  connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(save_screenshot()));

  screenshot_ = screenshot;
  set_label_pixmap();
}

ScreenshotDialog::~ScreenshotDialog()
{
  delete ui;
}

void ScreenshotDialog::closeEvent(QCloseEvent *event) {
  parent_->show();
  emit dialogClosed();
  event->accept();
}

void ScreenshotDialog::set_label_pixmap() {
  QPixmap *pixmap = screenshot_->get_pixmap();
  if(!pixmap->isNull())
    ui->screenshotLabel->setPixmap(pixmap->scaled(ui->screenshotLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ScreenshotDialog::save_screenshot() {
  QString format = "png";
  QString initialPath = QDir::currentPath() + tr("/Screenshot.") + format;
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), initialPath, tr("%1 Files (*.%2);;All Files (*)").arg(format.toUpper()).arg(format));

  if(!fileName.isEmpty())
    screenshot_->get_pixmap()->save(fileName, format.toLatin1().constData());
}
