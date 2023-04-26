#include <algorithm>
#include <fstream>
#include <random>

#include "storage_event.h"
#include "storage_model.h"

Storage::Storage() {
}

void Storage::Initialize() {
  std::string inputFolder = "../Storage_(example)/input";

  nlohmann::json thief = {
      {"luck", 0.7},
      {"coords", {0.0, 0.0, 0.0}}
  };
  objects_.emplace("thief0", thief);
  std::ifstream fin;
  for (const auto & entry : std::filesystem::directory_iterator(inputFolder)) {
    fin.open(entry.path().string());
    auto tmpJson = nlohmann::json::parse(fin);
    auto id = tmpJson["id"].get<std::string>();
    tmpJson.erase("id");
    objects_.emplace(id, tmpJson);
    fin.close();
  }
}

void Storage::Step() {
  // Steal some bread
  auto thief = objects_.find("thief0");
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<> theftRand (0, 1);
  if (theftRand(rng) < thief->second["luck"].get<float>()) {
    auto bread = objects_.find("Bread");
    auto oldAmount = bread->second["amount"].get<float>();
    if(oldAmount > 1) {
      bread->second["amount"] = (oldAmount - 1);
      current_event = TheftEvent(*thief, *bread);
      NotifyObservers();
    }
  }

  // TODO: Deliver sth here
}

void Storage::AddObserver(Observer *observer) {
  observers_.push_back(observer);
}

void Storage::RemoveObserver(Observer *observer) {
  auto candidate = std::find(
      observers_.begin(),
      observers_.end(),
      observer);
  if(candidate != observers_.end()) {
    observers_.erase(candidate);
  }
}

EventVariant Storage::getEvent() {
  return current_event;
}

void Storage::NotifyObservers() {
  for (auto & observer : observers_) {
    observer->Update();
  }
}