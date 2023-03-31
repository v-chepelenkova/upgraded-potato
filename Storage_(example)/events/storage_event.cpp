#include "storage_event.h"

#include <iostream>

// Events_Step_4: Write lambda function inside std::visit
// in the AnyEvent class' Handle function implementation
void StorageEvent::Handle() {
  std::visit(overloaded {
      [](DeliveryEvent arg) {
        arg.product->Show();
      },
      [](TheftEvent arg) {
        std::cout << arg.product->GetName()
                  << "'s been stolen. Only "
                  << arg.product->GetAmount()
                  << " items "
                  << "are left" << std::endl;
      }
  }, params);
}
