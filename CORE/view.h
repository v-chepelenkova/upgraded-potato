#pragma once

class View {
 public:
  virtual ~View() = default;
  virtual void Refresh() = 0;
};