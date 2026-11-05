#pragma once

#include <functional>

namespace hstd {
template <typename T>
using Func = std::function<T>;

template <typename T, typename F>
std::function<F(T const& obj)> get_field_get(F T::* field) {
    return [field](T const& obj) -> F { return obj.*field; };
}

template <typename T, typename F>
std::function<F(T const& obj)> get_getter_get(F (T::*method)() const) {
    return [method](T const& obj) -> F { return (obj.*method)(); };
}

template <typename T>
std::function<bool(T const& obj)> get_method_filter(bool (T::*method)() const) {
    return [method](T const& obj) -> bool { return (obj.*method)(); };
}

/// Trigger callback when exiting the scope. Ad-hoc RAII
/// implementation
template <typename Func>
struct finally {
    /// Callback function called in destructor
    Func action;

    /// Default constructor, use as ~funally{[](){ callback-action(); }}~
    explicit finally(Func _action) : action(_action) {}

    /// Overloaded constructor to run scope finalizer with some captured
    /// value
    template <typename T, typename Func1>
    static finally init(Func1 _action, T const& value) {
        return finally([value, _action]() { _action(value); });
    }

    /// Constructor for do-nothing default action
    static finally nop() { return finally{finally::nop_impl}; }

    ~finally() { action(); }

  private:
    static void nop_impl() {}
};

using finally_std = finally<std::function<void(void)>>;


template <typename Func>
bool no_exception(Func const& f) {
    try {
        f();
        return true;
    } catch (...) { return false; }
}

/// Overloading support for `std::visit`
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

} // namespace hstd
