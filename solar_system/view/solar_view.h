#pragma once

#include "../../CORE/mvc/view.h"

#include "solar_model.h"

class SolarConsoleView : ConsoleView {
 public:
  SolarConsoleView(const SolarSystem* model);
  void Initialize() override;
  void Refresh() override;

 private:
  const SolarSystem* model;
};