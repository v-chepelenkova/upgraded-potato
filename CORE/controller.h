#pragma once

#include "observer.h"

class Observer;

class Controller : public Observer {
 public:
  virtual ~Controller() = default;
  virtual void Start() = 0;
  virtual Object* CreateObject(const std::string &jsonName) = 0;
};