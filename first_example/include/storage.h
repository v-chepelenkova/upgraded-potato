#pragma once
#include <vector>
#include <sstream>
#include <fstream>

#include "controller.h"
#include "product.h"
#include "thief.h"
#include "inhabitant.h"
#include "model.h"
#include "observer.h"

class Observer;

class Storage : public Model {
 public:
  Storage();
  void Step();
  void Show() const;
  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);
 private:
  Thief thief_;
  std::string deliveryFilepath = "../../input/products.txt";
  void NotifyObservers(const std::vector<Inhabitant *> &context);
  void DeliverGoods(const std::string &input_path);
  void Steal();
};