#pragma once

#include <vector>

#include "inhabitant.h"
#include "observable.h"
#include "space.h"

class Model : public Observable {
 public:
  virtual ~Model() = default;
  virtual void Step() = 0;
 protected:
  Space space_;
};