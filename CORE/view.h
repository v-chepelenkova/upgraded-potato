#pragma once

class View {
 public:
  virtual ~View() = default;
  virtual void Refresh(const EventVariant &context) = 0;
};