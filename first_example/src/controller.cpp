#include "controller.h"

#include <iostream>
#include <string>

Controller::Controller(const std::string &input_path) {
  std::cout << "Hello from controller" << std::endl;
  model_ = new Storage(input_path);
  view_ = new ConsoleView();
}

Controller::~Controller() {
  model_->RemoveObserver(this);
  delete view_;
  delete model_;
};

void Controller::Start() {
  model_->AddObserver(this);
  // TODO: add a loop here for system to evolve
  model_->Step();
}

void Controller::Update(Inhabitant *context) {
  view_->Refresh(context);
}
