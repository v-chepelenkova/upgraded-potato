#pragma once

#include <vector>

#include "observable.h"
#include "sim_object.h"

class Model : public Observable {
 public:
  virtual ~Model() override = default;

  virtual void Initialize() = 0;
  //virtual void Step() = 0;
};

class DefaultModel : public Model {
 public:
  virtual ~DefaultModel() override = default;
  virtual const std::map<std::string, json>& GetSimulationObjects() const {
    return sim_objects;
  }
 
 protected:
  std::vector<Observer*> observers;
  std::map<std::string, json> sim_objects;
  float time_how_much_more_ms;
};