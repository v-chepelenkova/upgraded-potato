#pragma once

#include <utility>
#include <map>
#include <variant>
#include <vector>

#include "../../CORE/utils/json/json.hpp"

struct DeliveryEvent;
struct TheftEvent;

using EventVariant = std::variant<DeliveryEvent,
                                  TheftEvent>;

struct DeliveryEvent {
  std::pair<std::string, nlohmann::json> product;

  DeliveryEvent() = default;
  explicit DeliveryEvent(std::pair<std::string, nlohmann::json> product)
  : product(std::move(product)) {}
};

struct TheftEvent {
  std::pair<std::string, nlohmann::json> thief;
  std::pair<std::string, nlohmann::json> product;

  TheftEvent() = default;
  TheftEvent(std::pair<std::string, nlohmann::json> thief,
             std::pair<std::string, nlohmann::json> product)
  : thief(std::move(thief)), product(std::move(product)) {}
};
