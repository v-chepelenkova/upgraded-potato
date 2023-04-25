#include "storage_controller.h"

int main(int argc, char** argv) {
  StorageController controller(argv[0]);
  controller.Start();
  return 0;
}