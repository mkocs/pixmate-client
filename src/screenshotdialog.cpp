#include "src/screenshotdialog.h"
#include "ui_screenshotdialog.h"
#include "src/centralize.h"
#include <QDesktopWidget>
#include <QString>
#include <QDir>
#include <QFileDialog>
#define TTL_TIME_DEFAULT 80640 
#define TTL_VIEWS_DEFAULT -1

ScreenshotDialog::ScreenshotDialog(QWidget *parent, Screenshot* screenshot) :
  QDialog(parent),
  ui(new Ui::ScreenshotDialog)
{
  ui->setupUi(this);

  parent_ = parent;

  Centralize::center_window(this);

  ui->screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui->screenshotLabel->setAlignment(Qt::AlignCenter);
  ui->screenshotLabel->setMinimumSize(240, 160);

  connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(save_screenshot()));
  connect(ui->shareButton, SIGNAL(clicked()), this, SLOT(share_screenshot()));

  screenshot_ = screenshot;
  set_label_pixmap();
}

ScreenshotDialog::~ScreenshotDialog()
{
  delete ui;
}

void ScreenshotDialog::closeEvent(QCloseEvent *event)
{
  parent_->show();
  emit dialogClosed();
  event->accept();
}

void ScreenshotDialog::set_label_pixmap()
{
  QPixmap *pixmap = screenshot_->get_pixmap();
  if(!pixmap->isNull())
    ui->screenshotLabel->setPixmap(pixmap->scaled(ui->screenshotLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ScreenshotDialog::save_screenshot()
{
  QString format = "png";
  QString initialPath = QDir::homePath() + tr("/%1.").arg(screenshot_->get_pixmap_title()) + format;
  QFileDialog fdiag;
  fdiag.selectFile(screenshot_->get_pixmap_title() + format);
  QString fileName = fdiag.getSaveFileName(this, tr("Save as"), initialPath, tr("%1 Files (*.%2);;All Files (*)").arg(format.toUpper()).arg(format));
  if(!fileName.isEmpty())
    screenshot_->get_pixmap()->save(fileName, format.toLatin1().constData());
}

void ScreenshotDialog::share_screenshot()
{
  share_ = new Share(this, screenshot_);
  int ttl_time, ttl_views;
  if(ui->ttlTimeCheckBox->isChecked())
  {
    ttl_time = ui->ttlTimeSpinBox->value();
  }
  else
  {
    ttl_time = TTL_TIME_DEFAULT;
  }

  if (ui->ttlViewsCheckBox->isChecked())
  {
    ttl_views = ui->ttlViewsSpinBox->value();
  }
  else
  {
    ttl_views = TTL_VIEWS_DEFAULT;
  }

  if (ui->customTitleLineEdit->text().length() > 0)
  {
    screenshot_->set_pixmap_title(ui->customTitleLineEdit->text());
  }
  share_->share_screenshot(screenshot_->get_pixmap(), ttl_time, ttl_views);
}
