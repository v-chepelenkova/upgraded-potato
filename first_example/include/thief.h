#pragma once

#include "inhabitant.h"
#include "attributes.h"
#include "product.h"

template <>
class Attributes<THIEF> {
 public:
  float luck_;
};


class Thief : public Inhabitant {
 public:
  Thief();
  void Steal(Product* that);
  void Show() const;
 private:
  Attributes<THIEF> attr_;

};