#pragma once

#include "../../CORE/mvc/controller.h"
#include "console_view.h"
#include "../../CORE/mvc/observer.h"

#include "../../CORE/utils/timer/timer.h"
#include "storage_model.h"

class Observer;
class Storage;
class StorageConsoleView;

class StorageController : public Controller {
 public:
  explicit StorageController(const std::string &programAbsPath);
  ~StorageController() override;
  void Start() override;
  void Update() override;
 private:
  Storage* model_;
  StorageConsoleView* view_;
  Timer timer_;
  std::map<std::string, nlohmann::json> objectToRefresh_;
};