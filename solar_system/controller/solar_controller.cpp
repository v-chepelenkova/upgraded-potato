#include "solar_controller.h"

SolarController::SolarController(const std::string &program_abs_path) :
model(new SolarSystem),
//view(new SolarConsoleView(model)) {
view(new SolarTestView(model, 1600,
                              900,
                              "Engine Editor",
                              program_abs_path)) {
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
  float one_frame_ms = 1000.0f / view->GetFPS();  // FPS
  float time_end_ms = 10000.0f;
  model->SetTimeHowMuchMore(one_frame_ms);
  
  timer.SetMaxTime(time_end_ms);

  while(!timer.IsTimeHasCome() && !view->IsWindowDead()) {
    model->Step(timer.GetTimeElapse());
    timer.Add(std::chrono::milliseconds((long)one_frame_ms),
              [this]{view->Refresh();},
              false);
  }
}

void SolarController::Update() {
  //std::cout << "    I'm notified" << std::endl << std::endl;
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