#include "solar_model.h"
  

void SolarSystem::Initialize() {
  std::ifstream f("scene.json");
  json all_data = json::parse(f);
  for (const auto& obj : all_data["OBJECTS"].get<json>()) {
    sim_objects.emplace(obj["ID"].get<std::string>(),
      obj["ATTRIBUTES"].get<json>());
  }
  // json gr_info = {
  //   {"Planet", {
  //     //primitive, material,...
  //   }}
  // };
  // json planet1 = {
  //   {"type", "planet"},
  //   {"mass", 4.0},
  //   {"radius", 3.0},
  //   {"coordinates", {0.0, 0.0, 0.0}}
  // };
  // sim_objects.emplace("Planet", planet1);
  std::cout << "Solar System initialized" << std::endl;
}

void SolarSystem::Step(const float& time_current_ms) {
  //std::cout << "Solar System Step" << std::endl;
  auto search = sim_objects.find("Planet");
  if (search != sim_objects.end()) {
    float R = search->second["orbit"].get<float>();
    float x = R*cosf(3.1416f*0.001f*time_current_ms);
    float y = R*sinf(3.1416f*0.001f*time_current_ms);
    float z = 0.0f;
    search->second["coordinates"] = {x, y, z};
  }

  search = sim_objects.find("Planet2");
  if (search != sim_objects.end()) {
      float R = search->second["orbit"].get<float>();
      float x = R * cosf(3.1416f * 0.001f * time_current_ms);
      float y = -R * sinf(3.1416f * 0.001f * time_current_ms);
      float z = 0.0f;
      search->second["coordinates"] = { x, y, z };
  }

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