#include "thief.h"

#include <iostream>

#include "product.h"

Thief::Thief() {
  attr_.luck_ = 0.7f;
  std::cout << "A thief is here" << std::endl;
}

void Thief::Steal(Product *that) {
      std::cout << that->GetName()
                << "'s been stolen. Out of "
                << std::to_string(that->GetAmount())
                << " items only "
                << std::to_string((that->Add(-1), that->GetAmount()))
                << " are left" << std::endl;
}

void Thief::Show() const {
  std::cout << "Thief is " << attr_.luck_ * 100 << "% lucky" << std::endl;
}