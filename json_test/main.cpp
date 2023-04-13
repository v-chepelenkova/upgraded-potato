#include <iostream>
#include <vector>

#include "timer.h"
#include "json.hpp"

using json = nlohmann::json;
class Timer;

class MyModel {
 public:
  void Initialize();
  void Step(const std::string& name);

  std::vector<float> GetSimObjectCoords(const std::string& id);

  std::map<std::string, json> sim_objects;
};

class ConsoleView {
 public:
  void Refresh(const MyModel& model);
};

class Control {
 public:
  void Start();

  MyModel model;
  ConsoleView view;
  Timer timer;
};


void ConsoleView::Refresh(const MyModel& model) {
  std::cout << "Concole View on model:" << std::endl;
  for (const auto& sim_obj : model.sim_objects) {
    std::cout << sim_obj.first << std::endl;
    //std::cout << sim_obj.first + " info:" << std::endl;
    //std::cout << sim_obj.second.dump(4) << std::endl << std::endl;
  }
  std::cout << std::endl;
}


/*void AddSimObject(MyModel& model, const json& obj_data) {
  model.sim_objects.emplace_back(obj_data);
}*/

void MyModel::Initialize() {
  sim_objects.clear();

  json niels = {
    {"type", "bread"},
    {"happy", true},
    {"coords", {0.0, 0.0, 6.0}}
  };

  json greg = {
    {"type", "thief"},
    {"happy", false},
    {"gangster", true},
    {"coords", {1.0, 1.0, 0.0}}
  };

  sim_objects.emplace("bread_Niels", niels);
  sim_objects.emplace("thief_Greg", greg);
}


std::vector<float> MyModel::GetSimObjectCoords(const std::string& id) {
  if (auto search = sim_objects.find(id); search != sim_objects.end()) {
    return search->second["coords"].get<std::vector<float>>();
  }
  return {};
}

void MyModel::Step(const std::string& name) {
  json obj = {
    {"created", "yes"},
    {"coords", {1.0, 1.0, 0.0}}
  };

  sim_objects.emplace(name, obj);
}

void Control::Start() {
  model.Initialize();
  int timestep = 1;
  view.Refresh(model);
  std::cout << "Start counting" << std::endl;
  while (timestep <= 3) {
    model.Step("obj" + std::to_string(timestep));
    timer.add(std::chrono::milliseconds(1000 * timestep),
        [this]{view.Refresh(model);}, false);
    ++timestep;
  }
}

int main() {
  Control controller;
  controller.Start();
  /*MyModel model;
  model.Initialize();
  std::cout << model.GetSimObjectCoords("bread_Niels")[2] << std::endl;
  std::cout << model.GetSimObjectCoords("thief_Greg")[2] << std::endl;
  */
  /*
  
  
#include <iostream>
void foo() {
  std::cout << "hello\n";
}
void bar() {
  std::cout << "world\n";
}
int main() {
  Timer timer;
  timer.add(std::chrono::milliseconds(10000), bar, true);
  timer.add(std::chrono::milliseconds(5000), foo);
  timer.add(std::chrono::milliseconds(2000), []{}, false);
}*/


  return 0;
}