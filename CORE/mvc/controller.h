#pragma once

#include "observer.h"

class Controller : public Observer {
 public:
  virtual ~Controller() override = default;
  virtual void Start() = 0;
};