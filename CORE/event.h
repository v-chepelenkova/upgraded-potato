#pragma once

template<class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct EventHandler {
  virtual ~EventHandler() = default;
  virtual void Handle() = 0;
};
