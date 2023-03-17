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

void Controller::Start(const std::string &input_path) {
  model_->AddObserver(this);
  model_->DeliverGoods(input_path);
}

void Controller::Update(const std::vector<Product> &context) {
  view_->Refresh(context);
}
