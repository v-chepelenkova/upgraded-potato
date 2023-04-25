#include "sim_object.h"

SimObject::SimObject(const json& other) {
  attributes = other;

  std::string shape_type = other["shape"]["type"];
  std::vector<float> pos = other["shape"]["position"];

  if (shape_type == "cube") {
    float width = other["shape"]["width"];
    float length = other["shape"]["length"];
    float height = other["shape"]["height"];
    shape = std::make_unique<Engine::Cube>(glm::vec3(pos[0], pos[1], pos[2]),
                                           width, length, height);
  } else if (shape_type == "plane") {
    float width = other["shape"]["width"];
    float length = other["shape"]["length"];
    shape = std::make_unique<Engine::Plane>(glm::vec3(pos[0], pos[1], pos[2]),
                                            width, length);
  } else if (shape_type == "sphere") {
    float radius = other["shape"]["radius"];
    shape = std::make_unique<Engine::Sphere>(glm::vec3(pos[0], pos[1], pos[2]),
                                                       radius); 
  } else {
    shape = std::make_unique<Engine::Sphere>(glm::vec3(pos[0], pos[1], pos[2]),
                                                       1.0); 
  }
}

void SimObject::SetCoordinates(const float& x,
                               const float& y,
                               const float& z) {
  attributes["coordinates"] = {x, y, z};
}