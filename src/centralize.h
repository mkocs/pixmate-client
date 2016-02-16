#include "regionselectiondialog.h"
#include <QWidget>

namespace Centralize {
  void center_window(QWidget *widget);
  void center_rs_dialog(RegionSelectionDialog *rs, int &start_x, int &start_y, int &end_x, int &end_y, bool &multi_screen);
}
