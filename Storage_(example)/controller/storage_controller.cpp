#include "storage_controller.h"

#include <iostream>
#include <string>

StorageController::StorageController(const std::string &input_path) {
  std::cout << "Hello from controller" << std::endl;
  model_ = new Storage(input_path);
  view_ = new ConsoleView();
}

StorageController::~StorageController() {
  model_->RemoveObserver(this);
  delete view_;
  delete model_;
};

void StorageController::Start() {
  model_->AddObserver(this);
  // TODO: add a loop here for system to evolve
  model_->Step();
}

void StorageController::Update(StorageEventHandler &context) {
  view_->Refresh(context);
}
