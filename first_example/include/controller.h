#pragma once

#include "product.h"
#include "storage.h"
#include "console_view.h"
#include "interface/observer.h"

class Observer;
class Storage;
class ConsoleView;

class Controller : public Observer {
 public:
  Controller();
  ~Controller();
  void Start(const std::string &input_path);
  void Update(const std::vector<Product> &context);
 private:
  Storage* model_;
  ConsoleView* view_;
};