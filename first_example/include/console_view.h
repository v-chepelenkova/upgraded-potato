#pragma once

#include <vector>

#include "product.h"
#include "view.h"

class View;

class ConsoleView : public View {
 public:
  void Refresh(const std::vector<Inhabitant *> &context);
};