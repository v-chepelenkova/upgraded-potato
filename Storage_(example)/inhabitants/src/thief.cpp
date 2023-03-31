#include "thief.h"

#include <iostream>

#include "storage_event.h"
#include "product.h"

Thief::Thief() {
  attr_.luck_ = 0.7f;
  std::cout << "A thief is here" << std::endl;
}

// Events_Step_5: Don't forget to return AnyEvent where needed
StorageEvent Thief::Steal(Product *that) {
  that->Add(-1);
  return {TheftEvent(that)};
}

void Thief::Show() const {
  std::cout << "Thief is " << attr_.luck_ * 100 << "% lucky" << std::endl;
}