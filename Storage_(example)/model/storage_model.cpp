#include <algorithm>
#include <variant>

#include "storage_event.h"
#include "storage_model.h"

Storage::Storage() {}

void Storage::AddProduct(Product *o) {
  products_.push_back(o);
}

void Storage::AddThief(Thief *thief) {
  thief_ = thief;
}

void Storage::Step() {
  // Events_Step_6.1: Observers are notified inside this function,
  // because it is Model's member
//  DeliverGoods();

  // Events_Step_6.2: Observers are notified manually,
  // because Inhabitant generated the event
  NotifyObservers(thief_->Steal(products_.at(1)));
}

void Storage::AddObserver(Observer *observer) {
  observers_.push_back(observer);
}

void Storage::NotifyObservers(const EventVariant &context) {
  for (auto & observer : observers_) {
    observer->Update(context);
  }
}

void Storage::RemoveObserver(Observer *observer) {
  auto candidate = std::find(
      observers_.begin(),
      observers_.end(),
      observer);
  if(candidate != observers_.end()) {
    observers_.erase(candidate);
  }
}

//void Storage::DeliverGoods() {
//  std::ifstream input_file(deliveryFilepath_);
//  std::string name;
//  float price;
//  float amount;
//  std::string line;
//  if (input_file.is_open()) {
//    while (std::getline(input_file, line)) {
//      if (line[0] != '#') {
//        std::stringstream iss(line);
//        iss >> name;
//        iss >> price;
//        iss >> amount;
//        products_.push_back(new Product(name, price, amount));
//        // Events_Step_6: Don't forget to notify observers
//        // when event is happening
//      }
//    }
//      NotifyObservers({DeliveryEvent(products_)});
//  } else {
//    std::cout << "Can't open file " << deliveryFilepath_ << std::endl;
//  }
//}
