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
