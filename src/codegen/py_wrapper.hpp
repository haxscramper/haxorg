#pragma once


#include <string>
#include <functional>
#include <iostream>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>
#undef slots
#include <boost/python.hpp>

#include <hstd/stdlib/Variant.hpp>

#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <fmt/core.h>

template <typename T>
struct member_type;

// Specialize for pointer-to-member types
template <typename ClassType, typename FieldType>
struct member_type<FieldType ClassType::*> {
    using type = typename std::remove_cvref_t<FieldType>;
};

template <typename ClassType, typename FieldType>
struct member_type<FieldType ClassType::*const> {
    using type = typename std::remove_cvref_t<FieldType>;
};

template <typename T>
using member_type_t = ::member_type<T>::type;


namespace py = boost::python;


namespace pywrap {

// clang-format off
inline bool is_none(py::object const& obj)        { return obj.ptr() == Py_None; }
inline bool is_bool(py::object const& obj)        { return PyBool_Check(obj.ptr()); }
inline bool is_int(py::object const& obj)         { return PyLong_Check(obj.ptr()); }
inline bool is_float(py::object const& obj)       { return PyFloat_Check(obj.ptr()); }
inline bool is_complex(py::object const& obj)     { return PyComplex_Check(obj.ptr()); }
inline bool is_unicode(py::object const& obj)     { return PyUnicode_Check(obj.ptr()); }
inline bool is_bytes(py::object const& obj)       { return PyBytes_Check(obj.ptr()); }
inline bool is_bytearray(py::object const& obj)   { return PyByteArray_Check(obj.ptr()); }
inline bool is_list(py::object const& obj)        { return PyList_Check(obj.ptr()); }
inline bool is_tuple(py::object const& obj)       { return PyTuple_Check(obj.ptr()); }
inline bool is_set(py::object const& obj)         { return PySet_Check(obj.ptr()); }
inline bool is_frozenset(py::object const& obj)   { return PyFrozenSet_Check(obj.ptr()); }
inline bool is_dict(py::object const& obj)        { return PyDict_Check(obj.ptr()); }
inline bool is_slice(py::object const& obj)       { return PySlice_Check(obj.ptr()); }
inline bool is_ellipsis(py::object const& obj)    { return obj.ptr() == Py_Ellipsis; }
inline bool is_type(py::object const& obj)        { return PyType_Check(obj.ptr()); }
inline bool is_module(py::object const& obj)      { return PyModule_Check(obj.ptr()); }
inline bool is_function(py::object const& obj)    { return PyFunction_Check(obj.ptr()); }
inline bool is_generator(py::object const& obj)   { return PyGen_Check(obj.ptr()); }
inline bool is_method(py::object const& obj)      { return PyMethod_Check(obj.ptr()); }
inline bool is_iter(py::object const& obj)        { return PyIter_Check(obj.ptr()); }
inline bool is_sequence(py::object const& obj)    { return PySequence_Check(obj.ptr()); }
inline bool is_mapping(py::object const& obj)     { return PyMapping_Check(obj.ptr()); }
inline bool is_number(py::object const& obj)      { return PyNumber_Check(obj.ptr()); }
inline bool is_buffer(py::object const& obj)      { return PyObject_CheckBuffer(obj.ptr()); }
inline bool is_code(py::object const& obj)        { return PyCode_Check(obj.ptr()); }
inline bool is_frame(py::object const& obj)       { return PyFrame_Check(obj.ptr()); }
inline bool is_capsule(py::object const& obj)     { return PyCapsule_CheckExact(obj.ptr()); }
inline bool is_memoryview(py::object const& obj)  { return PyMemoryView_Check(obj.ptr()); }
inline bool is_cfunction(py::object const& obj)   { return PyCFunction_Check(obj.ptr()); }
inline bool is_object(py::object const& obj)      { return PyObject_IsInstance(obj.ptr(), (PyObject*)&PyBaseObject_Type); }
// clang-format on

DECL_DESCRIBED_ENUM_STANDALONE(
    ValueKind,
    Unknown,
    None,
    Bool,
    Int,
    Long,
    Float,
    Complex,
    String,
    Unicode,
    Bytes,
    List,
    Tuple,
    Set,
    Frozenset,
    Dict,
    Func,
    Module,
    Type,
    Code,
    Frame,
    Capsule,
    Memoryview,
    CFunction,
    Buffer,
    Obj // For instances of user-defined classes
);

void       init();
py::object eval(const std::string& code);
py::object eval_file(const std::string& filename);
void print(py::object obj, std::ostream& out, std::string indent = "");
std::string to_string(py::object value);
ValueKind   get_value_kind(py::object value);

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
    missing_field(std::string const& where, py::object field) {
        text = fmt::format(
            "Could not get field '{}' from {}", to_string(field), where);
    }
};

struct decode_error : base_msg {
    decode_error(std::string const& where, py::object got) {
        text = fmt::format(
            "Unexpected value '{}' of kind {} was found while {}",
            to_string(got),
            enum_serde<ValueKind>::to_string(get_value_kind(got))
                .toStdString(),
            where);
    }
};

Opt<boost::python::object> get_field(py::object node, char const* field);

} // namespace pywrap


template <IsSubVariantType V>
struct variant_type_resolver {
    using E = typename V::variant_enum_type;
    static int get(py::object value) {
        Opt<py::object> field = pywrap::get_field(value, "kind");
        if (field) {
            if (PyNumber_Check(field->ptr())) {
                return py::extract<int>(*field)();
            } else {
                return variant_type_resolver<E>::get(
                    enum_serde<E>::from_string(
                        py::extract<QString>(*field)()));
            }
        } else {
            qFatal() << "Missing 'kind' for a field";
        }
    }

    static int get(E value) { return value_domain<E>::ord(value); }
};

struct py_extract_base {
    py_extract_base(py::object value) : obj(value) {}

  protected:
    py::object obj;
};


template <IsSubVariantType T, typename CRTP_Derived>
struct extract : py_extract_base {
    using py_extract_base::py_extract_base;
    using V           = T::variant_data_type;
    using result_type = T;

    bool check() const { return PyDict_Check(obj); }


    T operator()(py::object value) {
        T result{
            variant_from_index<V>(variant_type_resolver<T>::get(value))};
        CRTP_Derived::init(result, value);
        std::visit(
            [&](auto& variant) {
                variant = ::py::extract<typename std::remove_cvref_t<
                    decltype(variant)>>::operator()(value);
                return 0;
            },
            result);
    }
};


template <DescribedRecord T>
struct py::extract<T> : py_extract_base {
    using result_type = T;
    using py_extract_base::py_extract_base;
    bool check() const { return PyDict_Check(obj); }

    T operator()() const {
        T result = SerdeDefaultProvider<T>::get();
        for_each_field_with_bases<T>([&](auto const& field) {
            Opt<py::object> py_field = pywrap::get_field(obj, field.name);
            if (py_field) {
                result.*field.pointer = py::extract<
                    ::member_type_t<decltype(field.pointer)>>(*py_field)();
            } else {
                qFatal() << "Missing field" << field.name << "for"
                         << typeid(T).name();
            }
        });
        return result;
    }
};


std::ostream& operator<<(std::ostream& os, py::object value);
