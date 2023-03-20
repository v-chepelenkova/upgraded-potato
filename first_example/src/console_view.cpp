#include "console_view.h"

#include "interface/inhabitant.h"

void ConsoleView::Refresh(const std::vector<Inhabitant *> &context) {
  for (auto & item : context) {
    item->Show();
  }
}