#pragma once

#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/chrono.h>
import hstd.stdlib.algorithms;
import hstd.stdlib.Str;


namespace PYBIND11_NAMESPACE {
namespace detail {
    template <>
    struct type_caster<Str> {
      public:
        PYBIND11_TYPE_CASTER(Str, _("str"));

        bool load(handle src, bool arg) {
            type_caster<std::string> impl;

            bool result = impl.load(src, arg);
            this->value = std::string(impl);
            return result;
        }

        static handle cast(Str src, return_value_policy a1, handle a2) {
            return type_caster<std::string>::cast(src, a1, a2);
        }
    };

} // namespace detail
} // namespace PYBIND11_NAMESPACE
