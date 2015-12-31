#include <QtWidgets>
#include "src/screenshot.h"
#include "src/mainwindow.h"

Screenshot::Screenshot() {
}

void Screenshot::newScreenshot(bool hideWindow, QWidget *parent, QPushButton *newScreenshotButton, QSpinBox *delaySpinBox) {
    if(hideWindow)
        parent->hide();
    newScreenshotButton->setDisabled(true);
    QTimer::singleShot(delaySpinBox->value() * 1000, parent, SLOT(shootScreen()));
}

void Screenshot::updateScreenshotLabel() {

}
