#pragma once

#include "observer.h"

class Observer;

class Controller : public Observer {
 public:
  virtual ~Controller() = default;
  virtual void Start() = 0;
};