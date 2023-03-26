#pragma once

#include "storage.h"

Storage::Storage(const std::string &input_path) {
  deliveryFilepath_ = input_path;
  std::cout << "I'm storage and I was created!" << std::endl;
}

void Storage::Step() {
  DeliverGoods();
  thief_.Steal(products_.at(0));
  NotifyObservers(products_.at(0));
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

// TODO: add events instead of sharing private members directly
void Storage::NotifyObservers(Inhabitant *context) {
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
        //Product a(name, price, amount);
        products_.push_back(new Product(name, price, amount));
        NotifyObservers(products_.back());
      }
    }
  } else {
    std::cout << "Can't open file " << deliveryFilepath_ << std::endl;
  }
}
