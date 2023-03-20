#pragma once

#include <vector>

#include "inhabitant.h"
#include "product.h"

class Observer {
 public:
  virtual void Update(const std::vector<Inhabitant *> &context) = 0;
};
