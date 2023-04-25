#pragma once

#include "json.hpp"

#include "graphics/includes/Rendering/Primitives/PrimitiveObject.hpp"
#include "graphics/includes/Rendering/Primitives/Plane.hpp"
#include "graphics/includes/Rendering/Primitives/Cube.hpp"
#include "graphics/includes/Rendering/Primitives/Sphere.hpp"

using json = nlohmann::json;

class SimObject {
 public:
  SimObject(const json& other);

  void SetCoordinates(const float& x, const float& y, const float& z);
  void Draw();
 
 private:
  json attributes;
  std::unique_ptr<Engine::PrimitiveObject> shape;
};