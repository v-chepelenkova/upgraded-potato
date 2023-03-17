#pragma once
#include "storage.h"

Storage::Storage() {
  std::cout << "I'm storage and I was created!" << std::endl;
}

void Storage::DeliverGoods(const std::string &input_path) {
  std::ifstream input_file(input_path);
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
        products_.push_back(Product(name, price, amount));
      }
    }
    NotifyObservers(std::vector<Product>());
  } else {
    std::cout << "Can't open file " << input_path << std::endl;
  }
}

void Storage::Show() const {
  std::cout << "Storage::Show - This is what I have:" << std::endl;
  for (Product prod: products_) {
    prod.Show();
  }
}

void Storage::AddObserver(Observer *observer) {
  observers_.push_back(observer);
}

// TODO: add events instead of sharing private members directly
void Storage::NotifyObservers(const std::vector<Product> &context) {
  for (auto & observer : observers_) {
    observer->Update(context);
  }
}

void Storage::RemoveObserver(Observer *observer) {
  auto candidate = std::find(observers_.begin(), observers_.end(), observer);
  if(candidate != observers_.end()) {
    observers_.erase(candidate);
  }
}