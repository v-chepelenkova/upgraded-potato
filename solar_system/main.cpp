#include "controller/solar_controller.h"
#include <fstream>

void CreateScene() {
  json all = {
      {"SCENE", {
        {"CAMERA",
          {
              {"position", {-10, 0.0, 0.0}},
              {"rotation", {0.0, 0.0, 0.0}},
              {"fov", 60.0},
              {"near_plane", 0.1},
              {"far_plane", 100.0},
          }},
         {"FPS", 75}
        }
      },
      {"OBJECTS", {
        {
          {"ID", "Planet"}, 
          {"ATTRIBUTES", {
            {"type", "planet"},
            {"mass", 1.0},
            {"radius", 1.0},
            {"orbit", 5.0},
            {"coordinates", {5.0, 0.0, 0.0}},
            {"GRAPHICS", {
              {"model", "sphere"},
              {"texture", "res/textures/earth2048.bmp"},
              {"material", "default"}
              }}
            }
          }
        },
        {
          {"ID", "Planet2"},
          {"ATTRIBUTES", {
            {"type", "planet"},
            {"mass", 1.0},
            {"radius", 1.0},
            {"orbit", 5.0},
            {"coordinates", {0.0, -2.5, -1.0}},
            {"GRAPHICS", {
              {"model", "sphere"},
              {"texture", "res/textures/earth2048.bmp"},
              {"material", "default"}
              }}
            }
          }
        },
        {
          {"ID", "Sun"},
          {"ATTRIBUTES", {
            {"type", "star"},
            {"mass", 10.0},
            {"radius", 2.0},
            {"coordinates", {0.0, 0.0, 0.0}},
            {"GRAPHICS", {
              {"model", "sphere"},
              {"texture", "res/textures/obama_sphere.png"},
              {"material", "light_source"}
              }}
            }
          }
        }}
      }
  };

  json camera_config = all["SCENE"]["CAMERA"].get<json>();
  std::ofstream file("scene.json");
  if (file.is_open()) {
    file << all.dump(4);
  }
  file.close();
}

int main(int argc, char** argv) {
  CreateScene();
  SolarController controller(argv[0]);
  controller.Start();
  return 0;
}