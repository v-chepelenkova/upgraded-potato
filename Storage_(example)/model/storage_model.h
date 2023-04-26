#pragma once

#include <map>
#include <vector>
#include <deque>

#include "json.hpp"

#include "storage_controller.h"


#include "model.h"
#include "observer.h"

class Observer;

class Storage : public Model {
 public:
  Storage();

  void Initialize() override;
  void Step() override;
  void AddObserver(Observer *observer) override;
  void RemoveObserver(Observer *observer) override;
  EventVariant getEvent();
 private:
  std::vector<Observer*> observers_;
  std::map<std::string, nlohmann::json> objects_;
  EventVariant current_event;

  void NotifyObservers() override;
};