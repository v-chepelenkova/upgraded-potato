#include "solar_controller.h"

SolarController::SolarController(const std::string &program_abs_path) :
model(new SolarSystem),
view(new SolarConsoleView(model)) {
  model->AddObserver(this);
}

SolarController::~SolarController() {
  model->RemoveObserver(this);
  delete view;
  delete model;
}

void SolarController::Start() {
  model->Initialize();
  view->Initialize();
  float one_frame_ms = 1000.0f / 1.0f;  // FPS
  float time_end_ms = 4000.0f;
  model->SetTimeHowMuchMore(one_frame_ms);
  float time_elapsed_ms = 0.0f;
  while(time_elapsed_ms <= time_end_ms) {
    model->Step();
    timer.Add(std::chrono::milliseconds((long)one_frame_ms),
              [this]{view->Refresh();},
              false);
    time_elapsed_ms += one_frame_ms;
  }
}

void SolarController::Update() {
  std::cout << "    I'm notified" << std::endl << std::endl;
  // auto context = model->getEvent();
  // std::visit(overloaded {
  //     [this](DeliveryEvent& arg) {
  //       objectToRefresh_.insert(arg.product);
  //     },
  //     [this](TheftEvent& arg) {
  //       objectToRefresh_.insert(arg.thief);
  //       objectToRefresh_.insert(arg.product);
  //     }
  // }, context);
}