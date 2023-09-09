#include "py_wrapper.hpp"

#include <format>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/strutils.hpp>

using namespace py;
using namespace pywrap;

Opt<py::object> pywrap::get_field(py::object obj, char const* field) {
    if (is_dict(obj)) { // If it's a dictionary
        return obj[field];
    } else if (
        is_object(obj) && PyObject_HasAttrString(obj.ptr(), field)) {
        return obj.attr(field);
    } else {
        return std::nullopt;
    }
}

ValueKind pywrap::get_value_kind(py::object obj) {
    if (is_none(obj)) {
        return ValueKind::None;
    } else if (is_bool(obj)) {
        return ValueKind::Bool;
    } else if (is_int(obj)) { // Checking int before obj to correctly
                              // identify integers
        return ValueKind::Long;
    } else if (is_float(obj)) {
        return ValueKind::Float;
    } else if (is_bytes(obj)) {
        return ValueKind::Bytes;
    } else if (is_unicode(obj)) {
        return ValueKind::Unicode;
    } else if (is_list(obj)) {
        return ValueKind::List;
    } else if (is_tuple(obj)) {
        return ValueKind::Tuple;
    } else if (is_set(obj)) {
        return ValueKind::Set;
    } else if (is_dict(obj)) {
        return ValueKind::Dict;
    } else if (is_function(obj) || is_method(obj)) { // Both are callable
        return ValueKind::Func;
    } else if (is_module(obj)) {
        return ValueKind::Module;
    } else if (is_type(obj)) {
        return ValueKind::Type;
    } else if (is_complex(obj)) {
        return ValueKind::Complex;
    } else if (is_frozenset(obj)) {
        return ValueKind::Frozenset;
    } else if (is_code(obj)) {
        return ValueKind::Code;
    } else if (is_frame(obj)) {
        return ValueKind::Frame;
    } else if (is_capsule(obj)) {
        return ValueKind::Capsule;
    } else if (is_memoryview(obj)) {
        return ValueKind::Memoryview;
    } else if (is_cfunction(obj)) {
        return ValueKind::CFunction;
    } else if (is_buffer(obj)) {
        return ValueKind::Buffer;
    }

    return ValueKind::Unknown;
}


void pywrap::format(py::object obj, QTextStream& out, QString indent) {
    switch (get_value_kind(obj)) {
        case ValueKind::Bool: {
            out << indent << "<boolean>: " << py::extract<bool>(obj)()
                << "\n";
            break;
        }
        case ValueKind::Int: {
            out << indent << "<integer>: " << py::extract<int>(obj)()
                << "\n";
            break;
        }
        case ValueKind::Long: {
            out << indent
                << "<integer>: " << py::extract<long long int>(obj)()
                << "\n";
            break;
        }
        case ValueKind::Float: {
            out << indent << "<real>: " << py::extract<double>(obj)()
                << "\n";
            break;
        }
        case ValueKind::Complex: {
            out << indent << "<complex>: "
                << "\n";
            break;
        }
        case ValueKind::Unicode:
        case ValueKind::String: {
            out << indent << "<string>: "
                << escape_for_write(py::extract<QString>(obj)()) << "\n";
            break;
        }
        case ValueKind::List: {
            out << indent << "<list>:\n";
            py::list const& list = py::extract<py::list>(obj)();
            for (int i = 0; i < py::len(list); ++i) {
                format(list[i], out, indent + "  ");
            }
            break;
        }
        default: {
            out << "TODO" << get_value_kind(obj);
        }
    }
}


QString pywrap::format(const boost::python::object& obj, QString indent) {
    QString     res;
    QTextStream os{&res};
    format(obj, os, indent);
    return res;
}


QString pywrap::describe_value(py::object const& obj) {
    QString res;
    res += "kind:";
    res += ::to_string(get_value_kind(obj));
    switch (get_value_kind(obj)) {
        case ValueKind::Unicode: {
            QString text = py::extract<QString>(obj)();
            res += QString(" of %1 chars: '%2%3'")
                       .arg(text.size())
                       .arg(escape_for_write(
                           text.mid(0, std::min<int>(text.size(), 10))))
                       .arg(10 < text.size() ? "..." : "");
            break;
        }

        case ValueKind::List: {
            res += QString(" of %1 items").arg(PyList_Size(obj.ptr()));
            break;
        }
        case ValueKind::Obj: {
            res += Py_TYPE(obj.ptr())->tp_name;
            break;
        }
    }

    return res;
}
