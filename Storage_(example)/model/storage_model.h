#pragma once
#include <vector>
#include <sstream>
#include <fstream>

#include "storage_controller.h"
#include "product.h"
#include "thief.h"
#include "object.h"
#include "model.h"
#include "observer.h"

class Observer;

class Storage : public Model {
 public:
  Storage();

  void AddThief(Thief *thief);
  void AddProduct(Product* o);
  void Step();
  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);
 private:
  Thief* thief_;
  std::vector<Product*> products_;
  void NotifyObservers(const EventVariant &context);
//  void DeliverGoods();
};