#pragma once

#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <hstd/stdlib/algorithms.hpp>


namespace PYBIND11_NAMESPACE {
namespace detail {
    template <>
    struct type_caster<QString> {
      public:
        PYBIND11_TYPE_CASTER(QString, _("str"));

        bool load(handle src, bool) {

            /* Extract PyObject from handle */
            PyObject* source = src.ptr();

            if (!PyUnicode_Check(source)) {
                return false;
            }

            Py_ssize_t  size;
            const char* ptr = PyUnicode_AsUTF8AndSize(source, &size);

            if (!ptr) {
                return false;
            }

            /* Now try to convert into a C++ int */
            value = QString::fromUtf8(ptr, size);

            /* Ensure return code was OK (to avoid out-of-range errors etc)
             */
            return (!PyErr_Occurred());
        }

        static handle cast(
            QString src,
            return_value_policy /* policy */,
            handle /* parent */) {
            return (PyUnicode_FromString(src.toUtf8().data()));
        }
    };
} // namespace detail
} // namespace PYBIND11_NAMESPACE
