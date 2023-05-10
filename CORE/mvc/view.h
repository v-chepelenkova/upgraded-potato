#pragma once

#include "model.h"

class View {
 public:
  virtual ~View() = default;
  virtual void Initialize() = 0;
  virtual void Refresh() = 0;
};

class ConsoleView : public View {
 public:
  virtual ~ConsoleView() = default;
};

class GraphicsView : public View {
 public:
  virtual ~GraphicsView() = default;
  //virtual void LoadResources() = 0;
};