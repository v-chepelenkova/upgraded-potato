#pragma once

#include "../src/interface/inhabitant.h"

class Thief : public Inhabitant {
 public:
  Thief();
  void InteractWithSpace();
  void InteractWithInhabitant(Inhabitant* that);
  void Show() const;
 private:
  float luck;
};
