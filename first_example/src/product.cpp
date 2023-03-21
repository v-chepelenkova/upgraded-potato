#pragma once

#include "product.h"
#include "thief.h"

Product::Product(const std::string &name, const float &price) {
  name_ = name;
  price_ = price;
  amount_ = 0.0f;
  type_ = PRODUCT;
  std::cout << name_ + " is here!" << std::endl;
}

Product::Product(const std::string &name, const float &price,
                 const float &amount) {
  name_ = name;
  price_ = price;
  amount_ = amount;
  type_ = PRODUCT;
  std::cout << name_ + " is here!" << std::endl;
}

std::string Product::GetName() const {
  return name_;
}

float Product::GetAmount() const {
  return amount_;
}

void Product::ChangePrice(const float &new_price) {
  if (new_price >= 0.0f)
    price_ = new_price;
  else
    std::cout << "Can't change " + name_ + " price: "
              << "new price <= 0" << std::endl;
}

void Product::ChangeAmount(const float &new_amount) {
  amount_ = (new_amount > 0.0f) ? new_amount : 0.0f;
}

void Product::Add(const float &add) {
  amount_ = (amount_ + add > 0.0f) ? (amount_ + add) : 0.0f;
}

void Product::InteractWithSpace() {
  std::cout << "Hello from " + name_ << std::endl;
}

void Product::InteractWithInhabitant(Inhabitant *that) {
  std::string message;
  switch (that->GetType()) {
    case PRODUCT:
      message = this->name_ + " meets " + dynamic_cast<Product *>(that)->name_;
      std::cout << message << std::endl;
      break;
    case THIEF:dynamic_cast<Thief *>(that)->InteractWithInhabitant(this);
      break;
  }
}

void Product::Show() const {
  std::cout << "Product: " << name_ << std::endl
            << "Price: " << price_ << std::endl
            << "Amount: " << amount_ << std::endl << std::endl;
}
