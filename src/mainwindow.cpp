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
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *) {
  QSize scaledSize = originalPixmap.size();
  scaledSize.scale(ui->screenshotLabel->size(), Qt::KeepAspectRatio);
  if(!ui->screenshotLabel->pixmap() || scaledSize != ui->screenshotLabel->pixmap()->size())
    updateScreenshotLabel();
}

void MainWindow::newScreenshot() {
  if(ui->hideCheckBox->isChecked())
    hide();
  ui->screenshotButton->setDisabled(true);
  switch(selectedMode)
  {
    case 0:
    {
      QTimer::singleShot(ui->delaySpinBox->value() * 1000, this, SLOT(shootScreen()));
      break;
    }
    case 1:
    {
      QTimer::singleShot(ui->delaySpinBox->value() * 1000, this, SLOT(shootSelection()));
      break;
    }
    case 2:
    {
      break;
    }
    default:
    {
      QTimer::singleShot(ui->delaySpinBox->value() * 1000, this, SLOT(shootScreen()));
      break;
    }
  }
}

void MainWindow::saveScreenshot() {
  QString format = "png";
  QString initialPath = QDir::currentPath() + tr("/Screenshot.") + format;
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), initialPath, tr("%1 Files (*.%2);;All Files (*)").arg(format.toUpper()).arg(format));

  if(!fileName.isEmpty())
    originalPixmap.save(fileName, format.toLatin1().constData());
}

void MainWindow::resetAfterShoot()
{
  updateScreenshotLabel();

  ui->screenshotButton->setDisabled(false);
  ui->saveButton->setDisabled(false);
  if(ui->hideCheckBox->isChecked())
    show();
}

void MainWindow::shootScreen() {
  /*if(ui->delaySpinBox->value() != 0) {
    qApp->beep();
  }*/
  QScreen *screen = QGuiApplication::primaryScreen();
  if(screen)
    originalPixmap = screen->grabWindow(0);
  resetAfterShoot();
}

void MainWindow::shootSelection()
{
  selector = new RegionSelect();
  res = selector->exec();
  if(res == QDialog::Accepted)
    originalPixmap = selector->getSelection();
  resetAfterShoot();
  delete selector;
}

void MainWindow::updateScreenshotLabel() {
  if(!originalPixmap.isNull())
    ui->screenshotLabel->setPixmap(originalPixmap.scaled(ui->screenshotLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::updateCheckBox() {
  if(ui->delaySpinBox->value() == 0) {
    ui->hideCheckBox->setDisabled(true);
    ui->hideCheckBox->setChecked(false);
  } else {
    ui->hideCheckBox->setDisabled(false);
  }
}

void MainWindow::on_screenshotButton_clicked()
{
  newScreenshot();
}

void MainWindow::on_saveButton_clicked()
{
  saveScreenshot();
}

void MainWindow::on_quitButton_clicked()
{
  close();
}

void MainWindow::on_screenRadioButton_clicked()
{
  selectedMode = 0;
  ui->delaySpinBox->setDisabled(false);
  ui->delaySpinBox->setValue(1);
  ui->hideCheckBox->setChecked(true);
}

void MainWindow::on_selectionRadioButton_clicked()
{
  selectedMode = 1;
  ui->delaySpinBox->setDisabled(true);
  ui->delaySpinBox->setValue(0);
  ui->hideCheckBox->setChecked(true);
}

void MainWindow::on_windowRadioButton_clicked()
{
  selectedMode = 2;
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
