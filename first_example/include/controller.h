#pragma once

#include "product.h"
#include "storage.h"
#include "console_view.h"
#include "observer.h"

class Observer;
class Storage;
class ConsoleView;

class Controller : public Observer {
 public:
  Controller(const std::string &input_path);
  ~Controller();
  void Start();
  void Update(const std::vector<Inhabitant *> &context);
 private:
  Storage* model_;
  ConsoleView* view_;
};