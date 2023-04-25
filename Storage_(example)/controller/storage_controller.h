#pragma once

#include "controller.h"
#include "console_view.h"
#include "observer.h"

#include "../timer.h"
#include "storage_model.h"

class Observer;
class Storage;
class ConsoleView;

class StorageController : public Controller {
 public:
  StorageController(const std::string &programAbsPath);
  ~StorageController();
  void Start();
  void Update(EventVariant &context);
 private:
  Storage* model_;
  ConsoleView* view_;
  Timer timer_;
  std::map<std::string, nlohmann::json> objectToRefresh_;
};