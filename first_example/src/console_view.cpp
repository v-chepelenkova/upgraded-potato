#include "console_view.h"

void ConsoleView::Refresh(const std::vector<Product> &context) {
  for (auto & product : context) {
    product.Show();
  }
}