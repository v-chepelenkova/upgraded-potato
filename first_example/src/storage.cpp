#pragma once
#include "storage.h"

Storage::Storage(const std::string &input_path) {
  std::cout << "I'm storage and I was created!" << std::endl
            << "Trying to read input and see what I have!" << std::endl;
  
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