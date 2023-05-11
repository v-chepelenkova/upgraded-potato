#pragma once

#include <iostream>
#include <fstream>

#include "../../CORE/mvc/model.h"

class SolarSystem : public DefaultModel {
 public:
  void Initialize() override;
  void Step(const float& time_current_ms);
  void SetTimeHowMuchMore(const float& time_ms);

  void AddObserver(Observer *observer) override;
  void RemoveObserver(Observer *observer) override;

 private:
  void NotifyObservers() override;
};