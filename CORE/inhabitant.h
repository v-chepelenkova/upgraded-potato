#pragma once
#include "inhabitant_types.h"

class Inhabitant {
 public:
  Inhabitant() : x_(0), y_(0), width_(0), height_(0) {}

  // TODO: add getters and setters
  InhabitantType GetType() { return type_; }
  virtual void Show() const = 0;

 protected:
  float x_;
  float y_;
  float width_;
  float height_;
  InhabitantType type_;
};
