#pragma once

#include "console_view.h"
#include "observer.h"
#include "product.h"
#include "storage_model.h"

class Observer;
class Storage;
class ConsoleView;

class Controller : public Observer {
 public:
  Controller(const std::string &input_path);
  ~Controller();
  void Start();
  void Update(StorageEvent &context);
 private:
  Storage* model_;
  ConsoleView* view_;
};