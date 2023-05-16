#pragma once

#include <chrono>
#include <functional>
#include <thread>

class Timer {
 public:
  Timer();
  void Add(std::chrono::milliseconds delay,
           std::function<void ()> callback,
           bool asynchronous = true);
  const bool IsTimeHasCome() const { return m_is_time_has_come; };

  void SetMaxTime(const long long& max_time_ms);
  long long GetTimeElapse() const { return m_runtime_ms; };
private:
    std::chrono::steady_clock::time_point m_time_from_last_update;
    bool m_is_time_has_come = false;
    long long m_max_time_ms = 3000;
    long long m_runtime_ms = 0;
};