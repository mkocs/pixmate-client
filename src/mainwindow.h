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
#include <src/regionselectiondialog.h>

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
    void new_screenshot();
    void save_screenshot();
    void shoot_screen();
    void shoot_selection();
    void reset_ui();

    void update_checkbox();
    void update_screenshot_label();
    void on_quitButton_clicked();
    void on_screenshotButton_clicked();
    void on_saveButton_clicked();

    void on_screenRadioButton_clicked();

    void on_selectionRadioButton_clicked();

    void on_windowRadioButton_clicked();

    void on_delaySpinBox_valueChanged(int arg1);

private:
      Ui::MainWindow *ui;
      QPixmap original_pixmap_;
      int selected_mode_;
      RegionSelectionDialog *selection_dialog_;
      int res_;
};

#endif // MAINWINDOW_H
