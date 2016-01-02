/********************************************************************************
 ** Form generated from reading UI file 'mainwindow.ui'
 **
 ** Created by: Qt User Interface Compiler version 4.8.7
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
 public:
  QWidget *centralWidget;
  QPushButton *screenshotButton;
  QPushButton *saveButton;
  QPushButton *quitButton;
  QLabel *screenshotLabel;
  QGroupBox *optionsGroupBox;
  QCheckBox *hideCheckBox;
  QSpinBox *delaySpinBox;
  QLabel *delayLabel;
  QMenuBar *menuBar;

  void setupUi(QMainWindow *MainWindow)
  {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(361, 360);
    MainWindow->setMinimumSize(QSize(361, 360));
    MainWindow->setMaximumSize(QSize(361, 360));
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    screenshotButton = new QPushButton(centralWidget);
    screenshotButton->setObjectName(QString::fromUtf8("screenshotButton"));
    screenshotButton->setGeometry(QRect(10, 310, 131, 32));
    saveButton = new QPushButton(centralWidget);
    saveButton->setObjectName(QString::fromUtf8("saveButton"));
    saveButton->setGeometry(QRect(140, 310, 131, 32));
    quitButton = new QPushButton(centralWidget);
    quitButton->setObjectName(QString::fromUtf8("quitButton"));
    quitButton->setGeometry(QRect(270, 310, 81, 32));
    screenshotLabel = new QLabel(centralWidget);
    screenshotLabel->setObjectName(QString::fromUtf8("screenshotLabel"));
    screenshotLabel->setGeometry(QRect(10, 10, 59, 16));
    optionsGroupBox = new QGroupBox(centralWidget);
    optionsGroupBox->setObjectName(QString::fromUtf8("optionsGroupBox"));
    optionsGroupBox->setGeometry(QRect(10, 180, 341, 131));
    hideCheckBox = new QCheckBox(optionsGroupBox);
    hideCheckBox->setObjectName(QString::fromUtf8("hideCheckBox"));
    hideCheckBox->setGeometry(QRect(10, 90, 131, 20));
    hideCheckBox->setChecked(true);
    delaySpinBox = new QSpinBox(optionsGroupBox);
    delaySpinBox->setObjectName(QString::fromUtf8("delaySpinBox"));
    delaySpinBox->setGeometry(QRect(10, 50, 61, 24));
    delaySpinBox->setValue(3);
    delayLabel = new QLabel(optionsGroupBox);
    delayLabel->setObjectName(QString::fromUtf8("delayLabel"));
    delayLabel->setGeometry(QRect(10, 30, 59, 16));
    MainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 361, 22));
    menuBar->setStyleSheet(QString::fromUtf8("padding: 0px;"));
    MainWindow->setMenuBar(menuBar);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
  } // setupUi

  void retranslateUi(QMainWindow *MainWindow)
  {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "pixmate", 0));
    screenshotButton->setText(QApplication::translate("MainWindow", "New Screenshot", 0));
    saveButton->setText(QApplication::translate("MainWindow", "Save Screenshot", 0));
    quitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
    screenshotLabel->setText(QString());
    optionsGroupBox->setTitle(QApplication::translate("MainWindow", "Options", 0));
    hideCheckBox->setText(QApplication::translate("MainWindow", "Hide this window", 0));
    delayLabel->setText(QApplication::translate("MainWindow", "Delay", 0));
  } // retranslateUi

};

namespace Ui {
  class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
