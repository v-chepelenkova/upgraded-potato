#include "controller/solar_controller.h"

int main(int argc, char** argv) {
  SolarController controller(argv[0]);
  controller.Start();
  return 0;
}