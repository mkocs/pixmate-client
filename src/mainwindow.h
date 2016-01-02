#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void updateCheckBox();
    void updateScreenshotLabel();

    private slots:
      void on_quitButton_clicked();

      void on_screenshotButton_clicked();

      void on_saveButton_clicked();

 private:
      Ui::MainWindow *ui;
      QPixmap originalPixmap;
};

#endif // MAINWINDOW_H
