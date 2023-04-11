#pragma once

class View {
 public:
  virtual ~View() = default;
  virtual void Refresh(EventHandler &context) = 0;
};