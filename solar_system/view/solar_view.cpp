#include "solar_view.h"

SolarConsoleView::SolarConsoleView(const SolarSystem* other) : 
model(other) {}

void SolarConsoleView::Initialize() {

}

void SolarConsoleView::Refresh() {
  std::cout << "Solar Concole View on model:" << std::endl;
  auto sim_objects = model->GetSimulationObjects();
  for (const auto& sim_obj : sim_objects) {
    std::cout << sim_obj.first << std::endl;
  }
  std::cout << std::endl;
}


SolarTestView::SolarTestView(const SolarSystem* other, 
    unsigned int window_width,
		unsigned int window_height,
		const char* title,
		const std::string& abs_path) : 
model(other) {
  render = new Engine::RenderingInterface(window_width, window_height,
      title, abs_path);
}

void SolarTestView::Initialize() {
  std::ifstream f("scene.json");
  json all_data = json::parse(f);
  render->ConfigureObjects(all_data);
  fps = all_data["SCENE"]["FPS"].get<float>();
}

void SolarTestView::Refresh() {
    json rendering_objects;
  auto simulation_objects = model->GetSimulationObjects();
  for (const auto& record : simulation_objects) {
    json obj;
    obj["ID"] = record.first;
    obj["coordinates"] = record.second["coordinates"].get<std::vector<float>>();
    //std::cout << obj["coordinates"] << std::endl;
    //std::cout << obj["ID"] << std::endl;
    rendering_objects.emplace_back(obj); 
  }
  render->Draw(rendering_objects);
}