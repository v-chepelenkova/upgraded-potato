#include "solar_model.h"

void SolarSystem::Initialize() {
  std::cout << "Solar System initialized" << std::endl;
}

void SolarSystem::Step() {
  std::cout << "Solar System Step" << std::endl;
  NotifyObservers();
}

void SolarSystem::SetTimeHowMuchMore(const float& time_ms) {
  time_how_much_more_ms = time_ms;
}

void SolarSystem::AddObserver(Observer *observer) {
  observers.push_back(observer);
}

void SolarSystem::RemoveObserver(Observer *observer) {
  auto candidate = std::find(
      observers.begin(),
      observers.end(),
      observer);
  if (candidate != observers.end()) {
    observers.erase(candidate);
  }
}

void SolarSystem::NotifyObservers() {
  for (auto & observer : observers) {
    observer->Update();
  }
}