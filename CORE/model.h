#pragma once

#include <vector>

#include "observable.h"
#include "space.h"

class Model : public Observable {
 public:
  virtual ~Model() = default;

  virtual void Initialize() = 0;
  virtual void Step() = 0;
};

class DefaultModel : public Model {
 public:


};