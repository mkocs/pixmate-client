#ifdef __APPLE__
#include <Carbon/Carbon.h>
#elif defined _WIN32
#include <windows.h>
#include <QWindow>
#endif
#include "mainwindow.h"

namespace GKeys {
#ifdef __APPLE__
  void set_osx_keys(MainWindow *mwin);
  OSStatus osx_key_handler(EventHandlerCallRef next_handler, EventRef the_event, void *user_data);
#elif defined _WIN32
  void set_win32_keys(MainWindow *mwin);
#endif
}


