#pragma once

#include <string>
#include <iostream>

#include "../src/interface/inhabitant.h"

class Product : public Inhabitant {
 public:
  Product(const std::string &name, const float &price);
  Product(const std::string &name, const float &price,
          const float &amount);

  std::string GetName() const;
  float GetAmount() const;
  void ChangePrice(const float &new_price);
  void ChangeAmount(const float &new_amount);
  void Add(const float &add);

  void InteractWithSpace();
  void InteractWithInhabitant(Inhabitant* that);
  void Show() const;

 private:
  std::string name_;
  float price_;
  float amount_;
};