#pragma once

#include "../../CORE/mvc/controller.h"
#include "../../CORE/utils/timer/timer.h"
//#include "timer.h"

#include "solar_model.h"
#include "solar_view.h"

class SolarController : public Controller {
 public:
  explicit SolarController(const std::string& program_abs_path);
  ~SolarController() override;
  void Start() override;
  void Update() override;

 private:
  SolarSystem* model;
  //SolarConsoleView* view;
  SolarTestView* view;
  Timer timer;
  std::map<std::string, json> objects_to_refresh;
};
