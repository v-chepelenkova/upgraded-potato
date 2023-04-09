#pragma once

#include <utility>
#include <variant>
#include <vector>

#include "event.h"
#include "inhabitant.h"
#include "thief.h"

class Thief;

// Events_Step_3: Add MyEvent structure like this
struct DeliveryEvent {
  std::vector<Product *>product;

  DeliveryEvent(std::vector<Product *>& product) : product(product) {}
};

struct TheftEvent {
  Thief *thief;

  TheftEvent(Thief *thief) : thief(thief) {}
};

// Events_Step_1: Inherit ours AnyEvent class from the abstract Event class
struct StorageEventHandler : public EventHandler {
  // Events_Step_2: Add a particular MyEvent
  //to the std::variant in the AnyEvent structure
  StorageEventHandler(std::variant<DeliveryEvent,
               TheftEvent> params) : params(std::move(params)) {}
  std::variant<DeliveryEvent, TheftEvent> params;
  void Handle();
};

