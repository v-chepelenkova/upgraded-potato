#pragma once

#include <vector>


#include "storage_event.h"
#include "view.h"

class View;

class ConsoleView : public View {
 public:
  void Refresh();
  void SetObjectsToRefresh(std::map<std::string, nlohmann::json> object);
 private:
  std::map<std::string, nlohmann::json> objectToRefresh_;
};