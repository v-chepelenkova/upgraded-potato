#include "thief.h"

#include <iostream>

#include "product.h"

Thief::Thief() {
  attr_.luck_ = 0.7f;
  std::cout << "A thief is here" << std::endl;
}

void Thief::InteractWithSpace() {
  std::cout << "Boo" << std::endl;
}

void Thief::InteractWithInhabitant(Inhabitant* that) {
  Product* product;
  switch (that->GetType()) {
    case PRODUCT:
      product = dynamic_cast<Product*>(that);
      std::cout << product->GetName()
          << "'s been stolen. Out of "
          << std::to_string(product->GetAmount())
          << " items only "
          << std::to_string((product->Add(-1), product->GetAmount()))
          << " are left" << std::endl;
      break;
    case THIEF:
      std::cout << "Hey there mr. Thief!" << std::endl;
      break;
  }
}

void Thief::Show() const {
  std::cout << "Thief: " << attr_.luck_ * 100 << "% lucky" << std::endl;
}
