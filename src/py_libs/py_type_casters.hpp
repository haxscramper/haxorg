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
        PYBIND11_TYPE_CASTER(QDateTime, _("datetime.datetime"));

      public:
        QDateTime getValue() { return value; }

        bool load(handle src, bool) {
            /* Extract PyObject from handle */
            PyObject* source = src.ptr();

            // Check if the source is a datetime object
            if (!PyDateTime_Check(source)) {
                return false;
            }

            // Extract details from the datetime object
            int year        = PyDateTime_GET_YEAR(source);
            int month       = PyDateTime_GET_MONTH(source);
            int day         = PyDateTime_GET_DAY(source);
            int hour        = PyDateTime_DATE_GET_HOUR(source);
            int minute      = PyDateTime_DATE_GET_MINUTE(source);
            int second      = PyDateTime_DATE_GET_SECOND(source);
            int microsecond = PyDateTime_DATE_GET_MICROSECOND(source);

            // Create a QDateTime object
            QDate qdate(year, month, day);
            QTime qtime(
                hour, minute, second, microsecond / 1000); // Qt uses
                                                           // milliseconds
            value = QDateTime(qdate, qtime);

            return true;
        }

        static handle cast(
            QDateTime src,
            return_value_policy /* policy */,
            handle /* parent */) {
            QDate date = src.date();
            QTime time = src.time();

            // Convert QDateTime to Python datetime
            return PyDateTime_FromDateAndTime(
                date.year(),
                date.month(),
                date.day(),
                time.hour(),
                time.minute(),
                time.second(),
                time.msec() * 1000 // Convert milliseconds to microseconds
            );
        }
    };

    template <>
    struct type_caster<QDate> {
      public:
        PYBIND11_TYPE_CASTER(QDate, _("datetime.date"));

        bool load(handle src, bool) {
            PyObject* source = src.ptr();

            // Check if the source is a date object
            if (!PyDate_Check(source)) {
                return false;
            }

            // Extract details from the date object
            int year  = PyDateTime_GET_YEAR(source);
            int month = PyDateTime_GET_MONTH(source);
            int day   = PyDateTime_GET_DAY(source);

            // Create a QDate object
            value = QDate(year, month, day);

            return true;
        }

        static handle cast(
            QDate src,
            return_value_policy /* policy */,
            handle /* parent */) {
            // Convert QDate to Python date
            return PyDate_FromDate(src.year(), src.month(), src.day());
        }
    };

    template <>
    struct type_caster<QTime> {
      public:
        PYBIND11_TYPE_CASTER(QTime, _("datetime.time"));

        bool load(handle src, bool) {
            PyObject* source = src.ptr();

            // Check if the source is a time object
            if (!PyTime_Check(source)) {
                return false;
            }

            // Extract details from the time object
            int hour        = PyDateTime_TIME_GET_HOUR(source);
            int minute      = PyDateTime_TIME_GET_MINUTE(source);
            int second      = PyDateTime_TIME_GET_SECOND(source);
            int microsecond = PyDateTime_TIME_GET_MICROSECOND(source);

            // Create a QTime object
            value = QTime(
                hour, minute, second, microsecond / 1000); // Qt uses
                                                           // milliseconds

            return true;
        }

        static handle cast(
            QTime src,
            return_value_policy /* policy */,
            handle /* parent */) {
            // Convert QTime to Python time
            return PyTime_FromTime(
                src.hour(),
                src.minute(),
                src.second(),
                src.msec() * 1000 // Convert milliseconds to microseconds
            );
        }
    };


} // namespace detail
} // namespace PYBIND11_NAMESPACE
