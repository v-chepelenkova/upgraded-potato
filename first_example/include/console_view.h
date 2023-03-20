#pragma once

#include <vector>

#include "product.h"
#include "../src/interface/view.h"

class View;

class ConsoleView : public View {
 public:
  void Refresh(const std::vector<Inhabitant *> &context);
};