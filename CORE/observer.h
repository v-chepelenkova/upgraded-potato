#pragma once

#include <vector>

#include "storage_event.h"


class Observer {
 public:
  virtual ~Observer() = default;
  virtual void Update() = 0;
};
