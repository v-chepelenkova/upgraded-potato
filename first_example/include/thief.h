#pragma once

#include "inhabitant.h"
#include "attributes.h"
#include "product.h"
#include "storage_event.h"

template <>
class Attributes<THIEF> {
 public:
  float luck_;
};

struct StorageEvent;

class Thief : public Inhabitant {
 public:
  Thief();
  StorageEvent Steal(Product* that);
  void Show() const;
 private:
  Attributes<THIEF> attr_;

};