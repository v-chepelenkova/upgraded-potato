#pragma once

#include <vector>

#include "product.h"
#include "observer.h"

class Observable {
 public:
  virtual void AddObserver(Observer *observer) = 0;
  virtual void RemoveObserver(Observer *observer) = 0;
 protected:
  std::vector<Observer*> observers_;
  virtual void NotifyObservers(const std::vector<Inhabitant*> &context) = 0;
};