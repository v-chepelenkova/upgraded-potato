#include "console_view.h"

#include <iostream>

#include "storage_event.h"

struct StorageEventHandler;

void ConsoleView::SetObjectsToRefresh(std::map<std::string,
                                      nlohmann::json> object) {
  objectToRefresh_.clear();
  if(object.empty()) return;
  objectToRefresh_ = std::move(object);
}

void ConsoleView::Refresh() {
  if (objectToRefresh_.empty()) {
    std::cout << "Nothing to refresh" << std::endl;
  }
  for(auto &o : objectToRefresh_) {
    std::cout << o.first << ": " << o.second.dump() << std::endl;
  }
}