#pragma once

#include <utility>
#include <map>
#include <variant>
#include <vector>

#include "json.hpp"

#include "event.h"
#include "object.h"


class Thief;

struct DeliveryEvent {
  std::pair<std::string, nlohmann::json> product;
  DeliveryEvent(std::pair<std::string, nlohmann::json> product)
  : product(std::move(product)) {}
};

struct TheftEvent {
  std::pair<std::string, nlohmann::json> thief;
  std::pair<std::string, nlohmann::json> product;

  TheftEvent(std::pair<std::string, nlohmann::json> thief,
             std::pair<std::string, nlohmann::json> product)
  : thief(std::move(thief)), product(std::move(product)) {}
};

struct StorageEventHandler : public EventHandler {
  StorageEventHandler(EventVariant event) : params(std::move(event)) {}
  EventVariant params;
  void Handle();
};
