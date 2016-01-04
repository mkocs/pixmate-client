#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <src/screenshot.h>
#include <src/regionselect.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void resizeEvent(QResizeEvent *);
  private slots:
    void newScreenshot();
    void saveScreenshot();
    void shootScreen();
    void shootSelection();
    void resetAfterShoot();

    void updateCheckBox();
    void updateScreenshotLabel();
    void on_quitButton_clicked();
    void on_screenshotButton_clicked();
    void on_saveButton_clicked();

    void on_screenRadioButton_clicked();

    void on_selectionRadioButton_clicked();

    void on_windowRadioButton_clicked();

    void on_delaySpinBox_valueChanged(int arg1);

private:
      Ui::MainWindow *ui;
      QPixmap originalPixmap;
      void initRadioButtons();
      void newSelection();
      int selectedMode;
      RegionSelect *selector;
      int res;
      void delay(int milliSec);
};

#endif // MAINWINDOW_H
