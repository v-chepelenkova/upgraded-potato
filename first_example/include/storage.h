#pragma once
#include <vector>
#include <sstream>
#include <fstream>

#include "product.h"

class Storage {
 public:
  Storage(const std::string &input_path);
  void Show() const;
 
 private:
  std::vector<Product> products_;
};