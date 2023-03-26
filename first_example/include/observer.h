#pragma once

#include <vector>

#include "inhabitant.h"
#include "product.h"

class Observer {
 public:
  virtual void Update(Inhabitant *context) = 0;
};
