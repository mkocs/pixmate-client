#include "gkeys.h"

namespace GKeys {
#ifdef __APPLE__
  void setOSXKeys(MainWindow *mwin) {
    //Register the Hotkeys
    EventHotKeyRef gMyHotKeyRef;
    EventHotKeyID gMyHotKeyID;
    EventTypeSpec eventType;
    eventType.eventClass=kEventClassKeyboard;
    eventType.eventKind=kEventHotKeyPressed;
    InstallApplicationEventHandler(&MyOSXHotKeyHandler,1,&eventType,mwin,NULL);
    gMyHotKeyID.signature='htk1';
    gMyHotKeyID.id=1;
    RegisterEventHotKey(kVK_Tab, shiftKey, gMyHotKeyID,
                        GetApplicationEventTarget(), 0, &gMyHotKeyRef);
  }

  OSStatus MyOSXHotKeyHandler(EventHandlerCallRef nextHandler,EventRef theEvent, void *userData)
  {
    static_cast<MainWindow*>(userData)->new_screenshot();
    return noErr;
  }
#endif
}

