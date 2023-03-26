#pragma once

#include <vector>

#include "storage_event.h"
#include "inhabitant.h"
#include "product.h"

class Observer {
 public:
  virtual void Update(StorageEvent &context) = 0;
};
