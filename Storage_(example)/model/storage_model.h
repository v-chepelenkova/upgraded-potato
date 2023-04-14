#pragma once

#include <map>
#include <vector>

#include "json.hpp"

#include "storage_controller.h"


#include "object.h"
#include "model.h"
#include "observer.h"

class Observer;

class Storage : public Model {
 public:
  Storage();

  void Initialize();
  void Step();
  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);
 private:
  std::vector<Observer*> observers_;
  std::map<std::string, nlohmann::json> object_;
  void NotifyObservers(EventVariant context);
};