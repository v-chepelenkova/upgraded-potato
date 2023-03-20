#include "controller.h"

#include <iostream>

Controller::Controller() {
  std::cout << "Hello from controller" << std::endl;
  model_ = new Storage();
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

void Controller::Update(const std::vector<Inhabitant *> &context) {
  view_->Refresh(context);
}
