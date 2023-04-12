#pragma once

#include <utility>

#include "object.h"
#include "attributes.h"
#include "product.h"
#include "storage_event.h"

struct StorageEventHandler;

// Inhabitant_Step_2: Create and inherit the class for your inhabitant
class Thief : public Object {
 public:
  Thief(std::map<std::string,
        AttributeVariant> attributes) : Object(std::move(attributes)) {}
  TheftEvent Steal(Product* that);
};