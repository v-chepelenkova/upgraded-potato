#include "storage_event.h"

#include <iostream>

// Events_Step_4: Write lambda function inside std::visit
// in the AnyEvent class' Handle function implementation
void StorageEventHandler::Handle() {
  std::visit(overloaded {
      [](DeliveryEvent& arg) {
          for(auto p : arg.product) {
              p->Show();
          }
      },
      [](TheftEvent arg) {
        arg.thief->Show();
      }
  }, params);
}
