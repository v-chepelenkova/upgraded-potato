#pragma once

#include <variant>
#include <vector>

#include "event.h"
#include "inhabitant.h"
#include "thief.h"

class Thief;

// Events_Step_3: Add MyEvent structure like this
struct DeliveryEvent {
  Product *product;

  DeliveryEvent(Product *product) : product(product) {}
};

struct TheftEvent {
  Product *product;

  TheftEvent(Product *product) : product(product) {}
};

// Events_Step_1: Inherit ours AnyEvent class from the abstract Event class
struct StorageEvent : public Event {
  // Events_Step_2: Add a particular MyEvent
  //to the std::variant in the AnyEvent structure
  StorageEvent(std::variant<DeliveryEvent,
               TheftEvent> params) : params(params) {}
  std::variant<DeliveryEvent, TheftEvent> params;
  void Handle();
};

