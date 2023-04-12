#include "storage_controller.h"

#include <filesystem>
#include <map>
#include <string>

#include "json.hpp"

StorageController::StorageController() {
  model_ = new Storage();
  view_ = new ConsoleView();
}

StorageController::~StorageController() {
  model_->RemoveObserver(this);
  delete view_;
  delete model_;
};

void StorageController::Start() {
  model_->AddObserver(this);
  std::string path = "../Storage_(example)/input";
  Object *o;
  for (const auto & entry : std::filesystem::directory_iterator(path)) {
    o = CreateObject(entry.path());
    if (std::get<std::string>(o->GetAttribute("type")) == "Product") {
      model_->AddProduct(dynamic_cast<Product *>(o));
    }
    if (std::get<std::string>(o->GetAttribute("type")) == "Thief") {
      model_->AddThief(dynamic_cast<Thief *>(o));
    }
    // TODO: else throw an exception with sth like "invalid type" in its message
  }
  // TODO: add a loop here for system to evolve
  model_->Step();
}

void StorageController::Update(const EventVariant &context) {
  view_->Refresh(context);
}

Object* StorageController::CreateObject(const std::string &jsonName) {
  std::ifstream fin(jsonName);
  nlohmann::json j = nlohmann::json::parse(fin);

  std::map<std::string, AttributeVariant> objectAttributes;
  for (auto& item : j.items()) {
    if (item.value().is_array()) {
      objectAttributes.emplace(item.key(),
                               item.value().get<std::vector<float>>());
    }
    if (item.value().is_string()) {
      objectAttributes.emplace(item.key(),
                               item.value().get<std::string>());
    }
    if (item.value().is_number_float()) {
      objectAttributes.emplace(item.key(),
                               item.value().get<float>());
    }
    if (item.value().is_number_integer()) {
      objectAttributes.emplace(item.key(),
                               item.value().get<int>());
    }
    if (item.value().is_boolean()) {
      objectAttributes.emplace(item.key(),
                               item.value().get<bool>());
    }
  }
  if (std::get<std::string>(objectAttributes["type"]) == "Product") {
    return new Product(objectAttributes);
  }
  if (std::get<std::string>(objectAttributes["type"]) == "Thief") {
    return new Thief(objectAttributes);
  }
}