#include "thief.h"

#include <iostream>

#include "storage_event.h"
#include "product.h"

// Inhabitant_Step_4: Implement inhabitant's behavior
Thief::Thief() {
  attr_.luck_ = 0.7f;
  attr_.stolenProduct = new Product("", 0, 0);
  std::cout << "A thief is here" << std::endl;
}

// Events_Step_5: Don't forget to return AnyEvent where needed
StorageEventHandler Thief::Steal(Product *that) {
  float amountToSteal = 1;
  that->Add(-amountToSteal);
  attr_.stolenProduct->ChangeName(that->GetName());
  attr_.stolenProduct->ChangeAmount(amountToSteal);
  return {TheftEvent(this)};
}

void Thief::Show() const {
  std::cout << "Thief: " << attr_.stolenProduct->GetAmount() << " pcs of "
            << attr_.stolenProduct->GetName() << " have been stolen"
            << std::endl;
}