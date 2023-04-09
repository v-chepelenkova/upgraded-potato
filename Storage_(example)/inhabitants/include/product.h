#pragma once

#include <string>
#include <iostream>

#include "inhabitant.h"
#include "attributes.h"

// Inhabitant_Step_3.1: Specialize your inhabitant's Attributes template
template <>
class Attributes<PRODUCT> {
 public:
  std::string name_;
  float price_;
  float amount_;
};

// Inhabitant_Step_2: Create and inherit the class for your inhabitant
class Product : public Inhabitant {
 public:
  Product(const std::string &name, const float &price);
  Product(const std::string &name, const float &price,
          const float &amount);

  std::string GetName() const;
  float GetAmount() const;
  void ChangeName(const std::string &new_name);
  void ChangePrice(const float &new_price);
  void ChangeAmount(const float &new_amount);
  void Add(const float &add);

  void Show() const;

 // Inhabitant_Step_3.2: Put your inhabitant's Attributes in private
 private:
  Attributes<PRODUCT> attr_;
  //std::string name_;
  //float price_;
  //float amount_;
};