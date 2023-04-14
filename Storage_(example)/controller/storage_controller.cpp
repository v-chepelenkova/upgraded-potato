#include "storage_controller.h"

#include <iostream>
#include <variant>

StorageController::StorageController() {
  model_ = new Storage;
  view_ = new ConsoleView;
}

StorageController::~StorageController() {
  model_->RemoveObserver(this);
  delete view_;
  delete model_;
};

void StorageController::Start() {
  model_->Initialize();
  model_->AddObserver(this);
  // TODO: add a loop here for system to evolve
  for (int i = 0; i < 5; ++i) {
    objectToRefresh_.clear();
    model_->Step();
    view_->SetObjectsToRefresh(objectToRefresh_);
    std::cout << "step #" << i << std::endl;
    timer_.add(std::chrono::milliseconds(1000),
              [this]{view_->Refresh();},
              false);
  }
}

void StorageController::Update(EventVariant &context) {
  std::visit(overloaded {
      [this](DeliveryEvent& arg) {
        objectToRefresh_.insert(arg.product);
      },
      [this](TheftEvent& arg) {
        objectToRefresh_.insert(arg.thief);
        objectToRefresh_.insert(arg.product);
      }
  }, context);
}
