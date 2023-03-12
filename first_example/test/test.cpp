#include "test.h"

void Test_Product() {
  std::cout << "Test_Product function start" << std::endl << std::endl;
  
  Product milk("milk", 1.0f);
  Product cola("cola", 1.2f);
  std::cout << "hello from Test_Product" << std::endl;
  std::cout << "changing prices and amounts" << std::endl;
  milk.ChangePrice(2.0f);
  milk.ChangeAmount(100.0f);
  cola.ChangeAmount(12.5f);
  milk.Show();
  cola.Show();
  
  std::cout << std::endl << "Test_Product function end"
            << std::endl << std::endl;
}

void Test_Storage() {
  std::cout << "Test_Storage function start" << std::endl << std::endl;

  std::string path = "..\\input\\products.txt"; //hardcoded
  Storage s(path);
  s.Show();

  std::cout << std::endl << "Test_Storage function end"
            << std::endl << std::endl;
}

/*void ReadInput() {
  std::string path = "..\\input\\products.txt";
  std::ifstream input_file(path);
  std::string name;
  float price;
  float amount;
  std::string line;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      if (line[0] != '#') {
        std::stringstream iss(line);
        iss >> name;
        iss >> price;
        iss >> amount;
        std::cout << "Product: " << name << std::endl
                  << "Price: " << price << std::endl
                  << "Amount: " << amount << std::endl << std::endl;
      }
    }
  } else {
    std::cout << "Can't open file " << path << std::endl;
  }
}*/