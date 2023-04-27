#pragma once

#include <vector>

class Observer {
 public:
  virtual ~Observer() = default;
  virtual void Update() = 0;
};
