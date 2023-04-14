#pragma once

#include <vector>

#include "storage_event.h"
#include "object.h"


class Observer {
 public:
  virtual ~Observer() = default;
  virtual void Update(EventVariant &context) = 0;
};
