#pragma once

#undef slots
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/optional.h>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Str.hpp>

namespace nanobind {
namespace detail {
template <>
struct type_caster<hstd::Str> {
    NB_TYPE_CASTER(hstd::Str, const_name("str"));

    bool from_python(
        handle        src,
        uint8_t       flags,
        cleanup_list* cleanup) noexcept {
        type_caster<std::string> impl;
        bool result = impl.from_python(src, flags, cleanup);
        if (result) { this->value = impl.value; }
        return result;
    }

    static handle from_cpp(
        hstd::Str     src,
        rv_policy     policy,
        cleanup_list* cleanup) noexcept {
        return type_caster<std::string>::from_cpp(
            std::string(src), policy, cleanup);
    }
};

} // namespace detail
} // namespace nanobind
