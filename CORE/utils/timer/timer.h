#pragma once

#include <chrono>
#include <functional>
#include <thread>

class Timer {
 public:
  Timer() = default;
  void Add(std::chrono::milliseconds delay,
           std::function<void ()> callback,
           bool asynchronous = true);
};