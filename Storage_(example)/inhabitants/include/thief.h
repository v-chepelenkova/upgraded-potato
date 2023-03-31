#pragma once

#include "inhabitant.h"
#include "attributes.h"
#include "product.h"
#include "storage_event.h"

// Inhabitant_Step_3.1: Specialize your inhabitant's Attributes template
template <>
class Attributes<THIEF> {
 public:
  float luck_;
};

// Inhabitant_Step_2: Create and inherit the class for your inhabitant
class Thief : public Inhabitant {
 public:
  Thief();
  // Events_Step_5: Don't forget to return AnyEvent where needed
  StorageEvent Steal(Product* that);
  void Show() const;

 // Inhabitant_Step_3.2: Put your inhabitant's Attributes in private
 private:
  Attributes<THIEF> attr_;

};