#pragma once

#include "../utils/json/json.hpp"

using json = nlohmann::json;

class SimObject {
 public:
  SimObject(const json& other);

  void SetCoordinates(const float& x, const float& y, const float& z);
 
 private:
  json attributes;
};