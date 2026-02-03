#pragma once

#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/chrono.h>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Str.hpp>


namespace PYBIND11_NAMESPACE {
namespace detail {
template <>
struct type_caster<hstd::Str> {
  public:
    PYBIND11_TYPE_CASTER(hstd::Str, _("str"));

    bool load(handle src, bool arg) {
        type_caster<std::string> impl;

        bool result = impl.load(src, arg);
        this->value = std::string(impl);
        return result;
    }

    static handle cast(hstd::Str src, return_value_policy a1, handle a2) {
        return type_caster<std::string>::cast(src, a1, a2);
    }
};

template <>
struct type_caster<pybind11::function> {
    PYBIND11_TYPE_CASTER(function, const_name("function"));

    bool load(handle src, bool) {
        value = src.cast<pybind11::function>();
        return !value.is_none();
    }

    static handle cast(const function& src, return_value_policy, handle) {
        return src.inc_ref();
    }
};

} // namespace detail
} // namespace PYBIND11_NAMESPACE
