#pragma once

struct Event {
  virtual void Handle() = 0;
};
