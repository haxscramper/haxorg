#pragma once

#include <functional>

struct finally {
    std::function<void(void)> action;
    explicit finally(std::function<void(void)> _action)
        : action(_action) {}
    ~finally() { action(); }
};

template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;


template <typename T>
bool notNil(T* ptr) {
    return ptr != nullptr;
}

template <typename T>
bool isNil(T* ptr) {
    return ptr == nullptr;
}

#define CRTP_this_method(__target)                                          \
  protected:                                                                \
    inline __target*       _this() { return static_cast<__target*>(this); } \
    inline __target const* _this() const {                                  \
        return static_cast<__target const*>(this);                          \
    }
