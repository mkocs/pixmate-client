#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // On OSX devices there is no menubar on the top
  // of the window, which is why there is a lot of
  // room on the bottom.
  // To avoid so much space being wasted, the window
  // size has to be reduced on Apple devices.
  #ifdef __APPLE__
  this->setMinimumHeight(height()-25);
  this->setMaximumHeight(height()-25);
  resize(width(), height()-25);
  #endif

  ui->windowRadioButton->setDisabled(true);
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
  center_window(widget);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::new_screenshot() {
  if (ui->hideCheckBox->isChecked())
    hide();
  switch (selected_mode_) {
    case 0:
    {
      QTimer::singleShot(ui->delaySpinBox->value() * 1000, this, SLOT(take_regular_screenshot()));
      break;
    }
    case 1:
    {
      QTimer::singleShot(300, this, SLOT(take_region_screenshot()));
      break;
    }
    default:
    {
      QTimer::singleShot(ui->delaySpinBox->value() * 1000, this, SLOT(take_regular_screenshot()));
      break;
    }
  }
}

void MainWindow::take_regular_screenshot() {
  screenshot_ = new Screenshot();
  screenshot_->take_screenshot();
  if (!screenshot_->get_pixmap()->isNull()) {
    screenshot_dialog_ = new ScreenshotDialog(this, screenshot_);
    screenshot_dialog_->show();
  }
}

void MainWindow::take_region_screenshot() {
  screenshot_ = new Screenshot();
  selection_dialog_ = new RegionSelectionDialog();
  res_ = selection_dialog_->exec();
  if (res_ == QDialog::Accepted) {
    if (!selection_dialog_->get_selection_pixmap().isNull()) {
      screenshot_->set_pixmap(selection_dialog_->get_selection_pixmap());
      screenshot_dialog_ = new ScreenshotDialog(this, screenshot_);
      screenshot_dialog_->show();
    } else {
      show();
    }
  } else {
    show();
  }
  delete selection_dialog_;
}

void MainWindow::center_window(QDesktopWidget *widget) {
  if (widget->screenCount() > 1) {
    int start_x = 0, start_y = 0;
    int end_x = 0, end_y = 0;
    int cursor_x = QCursor::pos().x();
    int cursor_y = QCursor::pos().y();
    for(int i = 0; i < widget->screenCount(); i++) {
      if (i > 0) {
        start_x += end_x;
        end_x += widget->screenGeometry(i).width();
        end_y += widget->screenGeometry(i).height();
      } else {
        start_x = 0;
        end_x = widget->screenGeometry(i).width();
        end_y = widget->screenGeometry(i).height();
      }
      if (cursor_x >= start_x && cursor_x <= end_x &&
          cursor_y >= start_y && cursor_y <= end_y) {
        move(start_x + (widget->screenGeometry(i).width()/2-(width()/2)), widget->screenGeometry(i).height()/2-height()/2);
      }
    }
  } else {
    move((widget->screenGeometry(0).width()/2-this->width()/2), (widget->screenGeometry(0).height()/2-this->height()/2));
  }
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
