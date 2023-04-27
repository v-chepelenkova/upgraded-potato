#include "sim_object.h"

SimObject::SimObject(const json& other) {
  attributes = other;
}

void SimObject::SetCoordinates(const float& x,
                               const float& y,
                               const float& z) {
  attributes["coordinates"] = {x, y, z};
}