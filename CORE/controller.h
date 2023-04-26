#pragma once

#include "observer.h"

class Observer;

class Controller : public Observer {
 public:
  ~Controller() override = default;
  virtual void Start() = 0;
};