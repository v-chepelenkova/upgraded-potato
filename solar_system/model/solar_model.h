#pragma once

#include <iostream>

#include "../../CORE/mvc/model.h"

class SolarSystem : public DefaultModel {
 public:
  void Initialize() override;
  void Step() override;
  void SetTimeHowMuchMore(const float& time_ms);

  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);

 private:
  void NotifyObservers();
};