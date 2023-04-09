#pragma once

#include "controller.h"
#include "console_view.h"
#include "observer.h"
#include "product.h"
#include "storage_model.h"

class Observer;
class Storage;
class ConsoleView;

class StorageController : public Controller {
 public:
  StorageController(const std::string &input_path);
  ~StorageController();
  void Start();
  void Update(StorageEvent &context);
 private:
  Storage* model_;
  ConsoleView* view_;
};