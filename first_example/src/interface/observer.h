#pragma once

#include <vector>

#include "product.h"

class Observer{
 public:
  virtual void Update(const std::vector<Product> &context) = 0;
};
