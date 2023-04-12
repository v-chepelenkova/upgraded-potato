#pragma once

#include <vector>

#include "storage_event.h"
#include "object.h"
#include "product.h"

class Observer {
 public:
  virtual ~Observer() = default;
  virtual void Update(const EventVariant &context) = 0;
};
