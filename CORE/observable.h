#pragma once

#include <vector>


#include "observer.h"

class Observable {
 public:
  virtual ~Observable() = default;
  virtual void AddObserver(Observer *observer) = 0;
  virtual void RemoveObserver(Observer *observer) = 0;
 protected:
  virtual void NotifyObservers(EventVariant context) = 0;
};