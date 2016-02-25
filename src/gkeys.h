#ifdef __APPLE__
#include <Carbon/Carbon.h>
#endif
#include "mainwindow.h"

namespace GKeys {
#ifdef __APPLE__
  void set_osx_keys(MainWindow *mwin);
  OSStatus osx_key_handler(EventHandlerCallRef next_handler, EventRef the_event, void *user_data);
#endif
}

