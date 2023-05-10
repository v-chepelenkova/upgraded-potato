#pragma once

#include "../../CORE/mvc/view.h"
#include "../../CORE/graphics/includes/RendererInterface.hpp"

#include "solar_model.h"

class SolarConsoleView : ConsoleView {
 public:
  SolarConsoleView(const SolarSystem* model);
  void Initialize() override;
  void Refresh() override;

 private:
  const SolarSystem* model;
};

class SolarTestView : GraphicsView {
 public:
  SolarTestView(const SolarSystem* model,
      unsigned int window_width,
			unsigned int window_height,
			const char* title,
			const std::string& abs_path);
  
  void Initialize() override;
  void Refresh() override;

  float GetFPS() const { return fps;}

 private:
  const SolarSystem* model;
  Engine::RenderingInterface* render;
  float fps;
};