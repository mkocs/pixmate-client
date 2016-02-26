#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/screenshot.h"
#include "src/regionselectiondialog.h"
#include "src/screenshotdialog.h"
#include <QMainWindow>
#include <QDialog>
#include <QWidget>
#include <QDesktopWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSpinBox>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
#ifdef _WIN32
  bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#endif
  public slots:
    void new_screenshot(int sel = -1);
  private slots:
    void take_regular_screenshot();
    void take_region_screenshot();

    void update_checkbox();
    void on_quitButton_clicked();
    void on_screenshotButton_clicked();

    void on_screenRadioButton_clicked();

    void on_selectionRadioButton_clicked();

    void on_windowRadioButton_clicked();

    void on_delaySpinBox_valueChanged(int arg1);

  private:
    Ui::MainWindow *ui;
    QPixmap original_pixmap_;
    int selected_mode_;
    RegionSelectionDialog *selection_dialog_;
    ScreenshotDialog *screenshot_dialog_;
    Screenshot *screenshot_;
    int res_;
};

#endif // MAINWINDOW_H
