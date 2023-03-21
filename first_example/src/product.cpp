#pragma once

#include "product.h"
#include "thief.h"

Product::Product(const std::string &name, const float &price) {
  attr_.name_ = name;
  attr_.price_ = price;
  attr_.amount_ = 0.0f;
  std::cout << attr_.name_ + " is here!" << std::endl;
}

Product::Product(const std::string &name, const float &price,
                 const float &amount) {
  attr_.name_ = name;
  attr_.price_ = price;
  attr_.amount_ = amount;
  std::cout << attr_.name_ + " is here!" << std::endl;
}

std::string Product::GetName() const {
  return attr_.name_;
}

float Product::GetAmount() const {
  return attr_.amount_;
}

void Product::ChangePrice(const float &new_price) {
  if (new_price >= 0.0f)
    attr_.price_ = new_price;
  else
    std::cout << "Can't change " + attr_.name_ + " price: "
              << "new price <= 0" << std::endl;
}

void Product::ChangeAmount(const float &new_amount) {
  attr_.amount_ = (new_amount > 0.0f) ? new_amount : 0.0f;
}

void Product::Add(const float &add) {
  attr_.amount_ = (attr_.amount_ + add > 0.0f) ? (attr_.amount_ + add) : 0.0f;
}

void Product::InteractWithSpace() {
  std::cout << "Hello from " + attr_.name_ << std::endl;
}

void Product::InteractWithInhabitant(Inhabitant *that) {
  std::string message;
  switch (that->GetType()) {
    case PRODUCT:message = this->attr_.name_ + " meets " + dynamic_cast<Product *>(that)->attr_.name_;
      std::cout << message << std::endl;
      break;
    case THIEF:dynamic_cast<Thief *>(that)->InteractWithInhabitant(this);
      break;
  }
}

void Product::Show() const {
  std::cout << "Product: " << attr_.name_ << std::endl
            << "Price: " << attr_.price_ << std::endl
            << "Amount: " << attr_.amount_ << std::endl << std::endl;
}
