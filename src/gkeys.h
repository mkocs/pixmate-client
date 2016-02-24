#include <Carbon/Carbon.h>
#include "mainwindow.h"

namespace GKeys {
  void setOSXKeys(MainWindow *mwin);
  OSStatus MyOSXHotKeyHandler(EventHandlerCallRef nextHandler, EventRef theEvent, void *userData);
}

