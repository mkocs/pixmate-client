#include "gkeys.h"
#include <QHotkey>

namespace GKeys
{
    void set_hotkeys(MainWindow *mwin)
    {
        QHotkey *hotkey_reg = new QHotkey(Qt::Key_1, Qt::ControlModifier | Qt::ShiftModifier, true, mwin);
        QObject::connect(hotkey_reg, &QHotkey::activated, mwin, &MainWindow::hk_reg_screenshot);

        QHotkey *hotkey_area = new QHotkey(Qt::Key_2, Qt::ControlModifier | Qt::ShiftModifier, true, mwin);
        QObject::connect(hotkey_area, &QHotkey::activated, mwin, &MainWindow::hk_area_screenshot);
    }
}
