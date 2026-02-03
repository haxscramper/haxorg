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
std::function<bool(T const& obj)> get_method_filter(
    bool (T::*method)() const) {
    return [method](T const& obj) -> bool { return (obj.*method)(); };
}

} // namespace hstd
