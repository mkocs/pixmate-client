#ifdef __APPLE__
#include <Carbon/Carbon.h>
#endif
#include "mainwindow.h"

namespace GKeys {
#ifdef __APPLE__
  void setOSXKeys(MainWindow *mwin);
  OSStatus MyOSXHotKeyHandler(EventHandlerCallRef nextHandler, EventRef theEvent, void *userData);
#endif
}

