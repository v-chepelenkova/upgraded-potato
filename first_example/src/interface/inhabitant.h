#pragma once

enum InhabitantType {
  PRODUCT,
  THIEF
};

class Inhabitant {
 public:
  Inhabitant() : x(0), y(0), width(0), height(0) {}

  // TODO: add getters and setters
  InhabitantType GetType() { return type; }

  virtual void InteractWithSpace() = 0;
  virtual void InteractWithInhabitant(Inhabitant* that) = 0;
  virtual void Show() const = 0;

 protected:
  float x;
  float y;
  float width;
  float height;
  InhabitantType type;
};
