#pragma once


#include <string>
#include <functional>
#include <iostream>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>
#include <boost/python.hpp>

#include <hstd/stdlib/Variant.hpp>

#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>
#include <fmt/core.h>

namespace py = boost::python;

namespace boost::python {
using PObj = PyObject*;
}

namespace pywrap {


DECL_DESCRIBED_ENUM_STANDALONE(
    ValueKind,
    Number,
    String,
    Object,
    Dict,
    Set,
    List);

void     init();
py::PObj eval(const std::string& code);
py::PObj eval_file(const std::string& filename);
void     print(py::PObj obj, std::ostream& out, std::string indent = "");
std::string to_string(py::PObj value);
ValueKind   get_value_kind(py::PObj value);

struct base_msg : std::exception {
    std::string text;
    const char* what() const noexcept override {
        return strdup(text.c_str());
    }
};

struct unexpected_variant : base_msg {
    unexpected_variant(std::string const& where, std::string const& kind) {
        text = fmt::format(
            "Could not decode variant with discriminant selector '{}' at "
            "{}",
            kind,
            where);
    }
};

struct missing_field : base_msg {
    missing_field(std::string const& where, py::PObj field) {
        text = fmt::format(
            "Could not get field '{}' from {}", to_string(field), where);
    }
};

struct decode_error : base_msg {
    decode_error(std::string const& where, py::PObj got) {
        text = fmt::format(
            "Unexpected value '{}' of kind {} was found while {}",
            to_string(got),
            enum_serde<ValueKind>::to_string(get_value_kind(got))
                .toStdString(),
            where);
    }
};

py::PObj get_field(py::PObj node, char const* field);

} // namespace pywrap

template <typename T>
struct convert;

template <IsVariant T, typename CRTP_Derived>
struct variant_convert {
    static std::string get_kind(
        py::PObj    value,
        char const* kindField = "kind") {
        py::PObj kind = pywrap::get_field(value, kindField);
        return to_string(kind);
    }

    static void decode(T& result, py::PObj value) {
        CRTP_Derived::init(result, value);
        std::visit(
            [&](auto& variant) {
                ::guile::convert<typename std::remove_cvref_t<
                    decltype(variant)>>::decode(variant, value);
                return 0;
            },
            result);
    }
};

template <typename T>
struct member_type;

// Specialize for pointer-to-member types
template <typename ClassType, typename FieldType>
struct member_type<FieldType ClassType::*> {
    using type = typename std::remove_cvref_t<FieldType>;
};

template <typename T>
using member_type_t = member_type<T>::type;

template <DescribedRecord T>
struct py::extract<T> {
    T operator()(py::PObj value) {
        T result = SerdeDefaultProvider<T>::get();
        for_each_field_with_bases<T>([&](auto const& field) {
            result.*field.pointer = py::extract<
                member_type_t<decltype(field.pointer)>>::
                operator()(pywrap::get_field(value, field.name));
        });
        return result;
    }
};


std::ostream& operator<<(std::ostream& os, py::PObj value);
