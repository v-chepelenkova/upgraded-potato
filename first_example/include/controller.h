#pragma once

#include "product.h"
#include "storage.h"
#include "console_view.h"
#include "../src/interface/observer.h"

class Observer;
class Storage;
class ConsoleView;

class Controller : public Observer {
 public:
  Controller();
  ~Controller();
  void Start();
  void Update(const std::vector<Inhabitant *> &context);
 private:
  Storage* model_;
  ConsoleView* view_;
};