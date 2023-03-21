#pragma once

#include "inhabitant.h"
#include "attributes.h"

template <>
class Attributes<THIEF> {
 public:
  float luck_;
};


class Thief : public Inhabitant {
 public:
  Thief();
  void InteractWithSpace();
  void InteractWithInhabitant(Inhabitant* that);
  void Show() const;
 private:
  Attributes<THIEF> attr_;
  //float luck;
};