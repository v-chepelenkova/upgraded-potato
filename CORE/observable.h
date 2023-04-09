#pragma once

#include <vector>

#include "product.h"
#include "observer.h"

class Observable {
 public:
  virtual ~Observable() = default;
  virtual void AddObserver(Observer *observer) = 0;
  virtual void RemoveObserver(Observer *observer) = 0;
 protected:
  std::vector<Observer*> observers_;
  virtual void NotifyObservers(StorageEventHandler context) = 0;
};