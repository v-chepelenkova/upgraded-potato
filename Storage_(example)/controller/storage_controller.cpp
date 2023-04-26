#include "storage_controller.h"

#include <iostream>
#include <variant>

template<class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

StorageController::StorageController(const std::string &programAbsPath) {
  model_ = new Storage;
  view_ = new ConsoleView(programAbsPath);
}

StorageController::~StorageController() {
  model_->RemoveObserver(this);
  delete view_;
  delete model_;
};

void StorageController::Start() {
  model_->Initialize();
  view_->Initialize();
  model_->AddObserver(this);
  // TODO: add a loop here for system to evolve
  for (int i = 0; i < 10; ++i) {
    objectToRefresh_.clear();
    model_->Step();
    view_->SetObjectsToRefresh(objectToRefresh_);
    std::cout << "step #" << i << std::endl;
    timer_.add(std::chrono::milliseconds(100),
              [this]{view_->Refresh();},
              false);
  }
}

void StorageController::Update() {
  auto context = model_->getEvent();
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
