#include <algorithm>
#include <fstream>
#include <random>

#include "storage_event.h"
#include "storage_model.h"

Storage::Storage() {}

void Storage::Initialize() {
  std::string inputFolder = "../Storage_(example)/input";

  nlohmann::json thief = {
      {"luck", 0.5},
      {"coords", {0.0, 0.0, 0.0}}
  };
  object_.emplace("thief0", thief);
  std::ifstream fin;
  for (const auto & entry : std::filesystem::directory_iterator(inputFolder)) {
    fin.open(entry.path().string());
    auto tmpJson = nlohmann::json::parse(fin);
    auto id = tmpJson["id"].get<std::string>();
    tmpJson.erase("id");
    object_.emplace(id, tmpJson);
    fin.close();
  }
}

void Storage::Step() {
  // Steal some bread
  auto thief = object_.find("thief0");
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<> theftRand (0, 1);
  if (theftRand(rng) < thief->second["luck"].get<float>()) {
    auto bread = object_.find("Bread");
    auto oldAmount = bread->second["amount"].get<float>();
    if(oldAmount > 1) {
      bread->second["amount"] = (oldAmount - 1);
      NotifyObservers(TheftEvent(*thief, *bread));
    }
  }

  // TODO: Deliver sth here
}

void Storage::AddObserver(Observer *observer) {
  observers_.push_back(observer);
}

void Storage::NotifyObservers(EventVariant context) {
  for (auto & observer : observers_) {
    observer->Update(context);
  }
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
