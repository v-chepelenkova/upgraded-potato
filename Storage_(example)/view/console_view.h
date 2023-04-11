#pragma once

#include <vector>

#include "product.h"
#include "storage_event.h"
#include "view.h"

class View;

class ConsoleView : public View {
 public:
  void Refresh(EventHandler &context);
};