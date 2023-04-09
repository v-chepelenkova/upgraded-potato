#pragma once

template<class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct EventHandler {
  virtual void Handle() = 0;
};
