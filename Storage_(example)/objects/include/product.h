#pragma once

#include <string>
#include <iostream>

#include "object.h"
#include "attributes.h"

// Inhabitant_Step_2: Create and inherit the class for your inhabitant
class Product : public Object {
 public:
  Product(std::map<std::string,
          AttributeVariant> attributes) : Object(std::move(attributes)) {}
};