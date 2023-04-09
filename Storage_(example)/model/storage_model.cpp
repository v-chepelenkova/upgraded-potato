#include "storage_model.h"

#include <algorithm>

#include "storage_event.h"

Storage::Storage(const std::string &input_path) {
  deliveryFilepath_ = input_path;
  std::cout << "I'm storage and I was created!" << std::endl;
}

void Storage::Step() {
  // Events_Step_6.1: Observers are notified inside this function,
  // because it is Model's member
  DeliverGoods(); 

  // Events_Step_6.2: Observers are notified manually,
  // because Inhabitant generated the event
  NotifyObservers(thief_.Steal(products_.at(1)));
}

void Storage::Show() const {
  std::cout << "Storage::Show - This is what I have:" << std::endl;
  for (auto item: products_) {
    item->Show();
  }
}

void Storage::AddObserver(Observer *observer) {
  observers_.push_back(observer);
}

// TODO: add events instead of sharing private members directly (DONE)
void Storage::NotifyObservers(StorageEventHandler context) {
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

void Storage::DeliverGoods() {
  std::ifstream input_file(deliveryFilepath_);
  std::string name;
  float price;
  float amount;
  std::string line;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      if (line[0] != '#') {
        std::stringstream iss(line);
        iss >> name;
        iss >> price;
        iss >> amount;
        products_.push_back(new Product(name, price, amount));
        // Events_Step_6: Don't forget to notify observers
        // when event is happening
      }
    }
      NotifyObservers({DeliveryEvent(products_)});
  } else {
    std::cout << "Can't open file " << deliveryFilepath_ << std::endl;
  }
}
