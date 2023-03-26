#pragma once

#include <variant>
#include <vector>

#include "event.h"
#include "inhabitant.h"
#include "thief.h"

class Thief;

template<class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct DeliveryEvent {
  Product *product;

  DeliveryEvent(Product *product) : product(product) {}
};
struct TheftEvent {
  Product *product;

  TheftEvent(Product *product) : product(product) {}
};

struct StorageEvent : public Event {
  StorageEvent(std::variant<DeliveryEvent,
               TheftEvent> params) : params(params) {}
  std::variant<DeliveryEvent, TheftEvent> params;
  void Handle();
};

