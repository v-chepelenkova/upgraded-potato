#pragma once

#include <vector>

#include "app.h"
#include "storage_event.h"
#include "view.h"

class View;

class ConsoleView : public View {
 public:
  ConsoleView(const std::string &programAbsPath);
  void Initialize();
  void Refresh();
  void SetObjectsToRefresh(std::map<std::string, nlohmann::json> object);
 private:
  std::map<std::string, nlohmann::json> objectToRefresh_;
  std::shared_ptr<App> pEngineEditor_;
  std::string programAbsPath_;
};