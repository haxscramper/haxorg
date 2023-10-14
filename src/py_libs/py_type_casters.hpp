#pragma once

#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/chrono.h>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Str.hpp>
#include <QDateTime>


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

    template <>
    struct type_caster<Str> {
      public:
        PYBIND11_TYPE_CASTER(Str, _("str"));

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

    template <>
    struct type_caster<QDateTime> {
      public:
        PYBIND11_TYPE_CASTER(QDateTime, _("int"));

      public:
        QDateTime getValue() { return value; }

        bool load(handle src, bool) {
            value = QDateTime::fromSecsSinceEpoch(
                PyLong_AsLong(src.ptr()));
            return true;
        }

        static handle cast(QDateTime src, return_value_policy, handle) {
            return PyLong_FromLong(src.toSecsSinceEpoch());
        }
    };

    template <>
    struct type_caster<QDate> {
      public:
        PYBIND11_TYPE_CASTER(QDate, _("int"));

        bool load(handle src, bool) {
            value = QDateTime::fromSecsSinceEpoch(PyLong_AsLong(src.ptr()))
                        .date();
            return true;
        }

        static handle cast(QDate src, return_value_policy, handle) {
            return PyLong_FromLong(
                QDateTime(src, QTime()).toSecsSinceEpoch());
        }
    };

    template <>
    struct type_caster<QTime> {
      public:
        PYBIND11_TYPE_CASTER(QTime, _("int"));

        bool load(handle src, bool) {
            value = QDateTime::fromSecsSinceEpoch(PyLong_AsLong(src.ptr()))
                        .time();
            return true;
        }

        static handle cast(QTime src, return_value_policy, handle) {
            return PyLong_FromLong(
                QDateTime(QDate(), src).toSecsSinceEpoch());
        }
    };


} // namespace detail
} // namespace PYBIND11_NAMESPACE
