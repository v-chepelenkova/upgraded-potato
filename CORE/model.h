#pragma once

#include <vector>

#include "observable.h"
#include "space.h"

class Model : public Observable {
 public:
  ~Model() override = default;

  virtual void Initialize() = 0;
  virtual void Step() = 0;
};

class DefaultModel : public Model {
 public:


};