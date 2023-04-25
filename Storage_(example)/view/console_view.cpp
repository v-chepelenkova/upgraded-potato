#include "console_view.h"

#include <iostream>
#include <thread>

#include "storage_event.h"

struct StorageEventHandler;

ConsoleView::ConsoleView(const std::string &programAbsPath) {
  pEngineEditor_ = std::make_shared<App>();
  this->programAbsPath_ = programAbsPath;
}

void ConsoleView::Initialize() {
  pEngineEditor_->initialize(1600,
                             900,
                             "Engine Editor",
                             programAbsPath_);
//  std::thread guiThread([this](){pEngineEditor_->start();});
  pEngineEditor_->start();
}

void ConsoleView::Refresh() {
  if (objectToRefresh_.empty()) {
    std::cout << "Nothing to refresh" << std::endl;
  }
  for(auto &o : objectToRefresh_) {
    std::cout << o.first << ": " << o.second.dump() << std::endl;
  }
}

void ConsoleView::SetObjectsToRefresh(std::map<std::string,
                                      nlohmann::json> object) {
  objectToRefresh_.clear();
  if(object.empty()) return;
  objectToRefresh_ = std::move(object);
}