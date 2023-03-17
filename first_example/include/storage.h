#pragma once
#include <vector>
#include <sstream>
#include <fstream>

#include "controller.h"
#include "product.h"
#include "interface/observable.h"
#include "interface/observer.h"

class Observable;
class Observer;

class Storage : public Observable {
 public:
  Storage();
  void DeliverGoods(const std::string &input_path);
  void Show() const;
  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);
 private:
  std::vector<Product> products_;
  void NotifyObservers(const std::vector<Product> &context);
};