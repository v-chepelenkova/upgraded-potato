#include "storage_event.h"

#include <iostream>

// Events_Step_4: Write lambda function inside std::visit
// in the AnyEvent class' Handle function implementation
void StorageEventHandler::Handle() {
  std::visit(overloaded {
      [](DeliveryEvent& arg) {
      },
      [](TheftEvent& arg) {
        std::string productName = std::get<std::string>
            (arg.product->GetAttribute("id"));
        float productAmount = std::get<float>
            (arg.product->GetAttribute("amount"));
        std::cout << productAmount << " pcs of "
                  << productName << " left"
                  << std::endl;
      }
  }, params);
}
