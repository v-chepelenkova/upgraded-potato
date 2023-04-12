#pragma once

#include "controller.h"
#include "console_view.h"
#include "observer.h"
#include "product.h"
#include "storage_model.h"

class Observer;
class Storage;
class ConsoleView;

class StorageController : public Controller {
 public:
  StorageController();
  ~StorageController();
  void Start();
  void Update(const EventVariant &context);
 private:
  Storage* model_;
  ConsoleView* view_;

  Object* CreateObject(const std::string &jsonName);
  // TODO: RemoveObject(...) : call sth in model to remove it from there,
  //        then destroy the object itself
};