#ifndef SCREENSHOT_H
#define SCREENSHOT_H

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

class Screenshot
{
public:
    Screenshot();
    static void newScreenshot(bool hideWindow, QWidget *parent, QPushButton *newScreenshotButton, QSpinBox *delaySpinBox);
    static void saveScreenshot();
    static void shootScreen();

    static void updateCheckBox();
    static void updateScreenshotLabel();

    static QPixmap originalPixmap;

    static void initPixMap();
};

#endif // SCREENSHOT_H
