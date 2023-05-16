#include "timer.h"

Timer::Timer() {
  m_time_from_last_update = std::chrono::steady_clock::now();
}
void Timer::Add(std::chrono::milliseconds delay,
                std::function<void()> callback,
                bool asynchronous) {
  if (asynchronous) {
    std::thread([=]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      callback();
    }).detach();
  }
  else {
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - m_time_from_last_update).count();
    
    if (elapsed_ms > delay.count()) {
      m_time_from_last_update = std::chrono::steady_clock::now();
      callback();
      m_runtime_ms += elapsed_ms;
      if (m_runtime_ms > m_max_time_ms && !m_is_time_has_come) {
        m_is_time_has_come = true;
      }
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
}

void Timer::SetMaxTime(const long long& max_time_ms) {
  m_max_time_ms = max_time_ms;
}
