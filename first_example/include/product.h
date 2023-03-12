#pragma once
#include <string>
#include <iostream>

class Product {
 public:
  Product(const std::string &name, const float &price);
  Product(const std::string &name, const float &price,
          const float &amount);
  void ChangePrice(const float &new_price);
  void ChangeAmount(const float &new_amount);
  void Add(const float &add);

  void Show() const;

 private:
  std::string name_;
  float price_;
  float amount_;
};