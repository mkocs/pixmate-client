#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui->screenshotLabel->setAlignment(Qt::AlignCenter);
  ui->screenshotLabel->setMinimumSize(240, 160);

  ui->saveButton->setDisabled(true);
  ui->screenRadioButton->setChecked(true);

  QMenu *screenMenu = new QMenu("Screen", this);
  QAction *newAction = new QAction("New Screenshot", this);
  QAction *saveAction = new QAction("Save Screenshot", this);
  screenMenu->addAction(newAction);
  screenMenu->addAction(saveAction);
  ui->menuBar->addMenu(screenMenu);

  ui->delaySpinBox->setSuffix(" s");
  ui->delaySpinBox->setMaximum(120);

  QDesktopWidget *widget;
  widget = new QDesktopWidget();
  move((widget->screenGeometry(0).width()/2-this->width()/2), (widget->screenGeometry(0).height()/2-this->height()/2));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *) {
  QSize scaledSize = original_pixmap_.size();
  scaledSize.scale(ui->screenshotLabel->size(), Qt::KeepAspectRatio);
  if(!ui->screenshotLabel->pixmap() || scaledSize != ui->screenshotLabel->pixmap()->size())
    update_screenshot_label();
}

void MainWindow::new_screenshot() {
  if(ui->hideCheckBox->isChecked())
    hide();
  ui->screenshotButton->setDisabled(true);
  switch(selected_mode_)
  {
    case 0:
    {
      QTimer::singleShot(ui->delaySpinBox->value() * 1000, this, SLOT(shoot_screen()));
      break;
    }
    case 1:
    {
      QTimer::singleShot(300, this, SLOT(shoot_selection()));
      break;
    }
    case 2:
    {
      break;
    }
    default:
    {
      QTimer::singleShot(ui->delaySpinBox->value() * 1000, this, SLOT(shoot_screen()));
      break;
    }
  }
}

void MainWindow::save_screenshot() {
  QString format = "png";
  QString initialPath = QDir::currentPath() + tr("/Screenshot.") + format;
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), initialPath, tr("%1 Files (*.%2);;All Files (*)").arg(format.toUpper()).arg(format));

  if(!fileName.isEmpty())
    original_pixmap_.save(fileName, format.toLatin1().constData());
}

void MainWindow::reset_ui()
{
  update_screenshot_label();

  ui->screenshotButton->setDisabled(false);
  ui->saveButton->setDisabled(false);
  if(ui->hideCheckBox->isChecked())
    show();
}

void MainWindow::shoot_screen() {
  if(ui->delaySpinBox->value() != 0) {
    qApp->beep();
  }
  QScreen *screen = QGuiApplication::primaryScreen();
  if(screen)
    original_pixmap_ = screen->grabWindow(0);
  reset_ui();
}

void MainWindow::shoot_selection()
{
  selection_dialog_ = new RegionSelectionDialog();
  res_ = selection_dialog_->exec();
  if(res_ == QDialog::Accepted)
    original_pixmap_ = selection_dialog_->get_selection_pixmap();
  reset_ui();
  delete selection_dialog_;
}

void MainWindow::update_screenshot_label() {
  if(!original_pixmap_.isNull())
    ui->screenshotLabel->setPixmap(original_pixmap_.scaled(ui->screenshotLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::update_checkbox() {
  if(ui->delaySpinBox->value() == 0) {
    ui->hideCheckBox->setDisabled(true);
    ui->hideCheckBox->setChecked(false);
  } else {
    ui->hideCheckBox->setDisabled(false);
  }
}

void MainWindow::on_screenshotButton_clicked()
{
  new_screenshot();
}

void MainWindow::on_saveButton_clicked()
{
  save_screenshot();
}

void MainWindow::on_quitButton_clicked()
{
  close();
}

void MainWindow::on_screenRadioButton_clicked()
{
  selected_mode_ = 0;
  ui->delaySpinBox->setDisabled(false);
  ui->delaySpinBox->setValue(1);
  ui->hideCheckBox->setChecked(true);
}

void MainWindow::on_selectionRadioButton_clicked()
{
  selected_mode_ = 1;
  ui->delaySpinBox->setDisabled(true);
  ui->delaySpinBox->setValue(0);
  ui->hideCheckBox->setChecked(true);
}

void MainWindow::on_windowRadioButton_clicked()
{
  selected_mode_ = 2;
  ui->delaySpinBox->setDisabled(false);
  ui->delaySpinBox->setValue(1);
  ui->hideCheckBox->setChecked(true);
}

void MainWindow::on_delaySpinBox_valueChanged(int arg1)
{
  if(arg1 == 0)
  {
    ui->hideCheckBox->setDisabled(true);
    ui->hideCheckBox->setChecked(false);
  }
  else
  {
    ui->hideCheckBox->setDisabled(false);
  }
}
