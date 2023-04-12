#pragma once

#include <utility>
#include <variant>
#include <vector>

#include "event.h"
#include "object.h"
#include "thief.h"

class Thief;

// Events_Step_3: Add MyEvent structure like this
struct DeliveryEvent {
  DeliveryEvent() {}
};

struct TheftEvent {
  Thief *thief;
  Product *product;

  TheftEvent(Thief *thief, Product* product) : thief(thief), product(product) {}
};

// Events_Step_1: Inherit ours AnyEvent class from the abstract Event class
struct StorageEventHandler : public EventHandler {
  // Events_Step_2: Add a particular MyEvent
  //to the std::variant in the AnyEvent structure
  StorageEventHandler(const EventVariant &params) : params(std::move(params)) {}
  std::variant<DeliveryEvent, TheftEvent> params;
  void Handle();
};

