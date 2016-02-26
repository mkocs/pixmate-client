#include "gkeys.h"
#ifdef _WIN32
#include <QGuiApplication>
#endif

namespace GKeys {
#ifdef __APPLE__
  void set_osx_keys(MainWindow *mwin) {
    /*
      * Register the hotkey
      */
    EventHotKeyRef g_hotkey_reference;
    EventHotKeyID g_hotkey_id;
    EventTypeSpec event_type;
    event_type.eventClass = kEventClassKeyboard;
    event_type.eventKind = kEventHotKeyPressed;
    InstallApplicationEventHandler(&osx_key_handler, 1, &event_type, mwin, NULL);
    g_hotkey_id.signature = 'htk0';
    g_hotkey_id.id = 0;
    RegisterEventHotKey(kVK_ANSI_1 /*0x12*/, cmdKey /*0x37*/ + shiftKey /*0x38*/, g_hotkey_id,
                        GetApplicationEventTarget(), 0, &g_hotkey_reference);

    g_hotkey_id.signature = 'htk1';
    g_hotkey_id.id = 1;
    RegisterEventHotKey(kVK_ANSI_2 /*0x13*/, cmdKey /*0x37*/ + shiftKey /*0x38*/, g_hotkey_id,
                        GetApplicationEventTarget(), 0, &g_hotkey_reference);

    g_hotkey_id.signature = 'htk2';
    g_hotkey_id.id = 2;
    RegisterEventHotKey(kVK_ANSI_O /*0x13*/, cmdKey /*0x37*/ + shiftKey /*0x38*/, g_hotkey_id,
                        GetApplicationEventTarget(), 0, &g_hotkey_reference);


  }

  OSStatus osx_key_handler(EventHandlerCallRef next_handler,EventRef the_event, void *user_data)
  {
    EventHotKeyID hk_com;
    GetEventParameter(the_event, kEventParamDirectObject, typeEventHotKeyID, NULL,
                      sizeof(hk_com), NULL, &hk_com);
    switch (hk_com.id) {
    case 0:
      static_cast<MainWindow *>(user_data)->new_screenshot(0);
      break;
    case 1:
      static_cast<MainWindow *>(user_data)->new_screenshot(1);
      break;
    case 2:
      static_cast<MainWindow *>(user_data)->show();
      static_cast<MainWindow *>(user_data)->raise();
      break;
    default:
      static_cast<MainWindow*>(user_data)->new_screenshot(0);
      break;
    }
    return noErr;
  }

#elif defined _WIN32
  void set_win32_keys(MainWindow *mwin) {
    /*See https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx for virtual key codes*/
    HWND main_hwnd = (HWND)mwin->winId();
    RegisterHotKey(main_hwnd, 2, MOD_CONTROL | MOD_SHIFT, 0x32 /*2 key*/);
  /*https://msdn.microsoft.com/en-us/library/windows/desktop/ms646327(v=vs.85).aspx for unregistering*/
  }
#endif
}
