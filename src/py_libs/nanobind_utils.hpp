#pragma once

#include <immer/vector.hpp>
#include <immer/box.hpp>
#include <immer/flex_vector.hpp>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/unordered_map.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/pair.h>
#include <nanobind/make_iterator.h>
#include <hstd/stdlib/Set.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <nanobind/stl/bind_map.h>
#include <nanobind/stl/bind_vector.h>

namespace org::bind::python {

namespace nb = nanobind;

struct PyTypeRegistryGuard {
    hstd::UnorderedSet<hstd::Str> py_cxx_map;

    void incl(hstd::Str const& name) { py_cxx_map.incl(name); }
    bool contains(hstd::Str const& name) const {
        return py_cxx_map.contains(name);
    }

    PyTypeRegistryGuard() {}
};

template <typename E>
class PyEnumIterator {
  public:
    explicit PyEnumIterator(E value = hstd::value_domain<E>::low())
        : value(value) {}

    E operator*() const { return value; }

    PyEnumIterator& operator++() {
        value = hstd::value_domain<E>::succ(value);
        return *this;
    }

    bool operator!=(const PyEnumIterator& other) const {
        return hstd::value_domain<E>::ord(value)
            != hstd::value_domain<E>::ord(other.value);
    }

  private:
    E value;
};

template <typename E>
void bind_enum_iterator(
    nb::module_&         m,
    const char*          PyTypeName,
    PyTypeRegistryGuard& guard) {
    auto name = std::string(PyTypeName) + "EnumIterator";
    if (!guard.contains(name)) {
        guard.incl(name);
        nb::class_<PyEnumIterator<E>>(m, name.c_str())
            .def(
                "__iter__",
                [](PyEnumIterator<E>& self) -> PyEnumIterator<E>& {
                    return self;
                })
            .def("__next__", [](PyEnumIterator<E>& self) {
                auto current = *self;
                if (current == hstd::value_domain<E>::high()) {
                    throw nb::stop_iteration();
                }
                ++self;
                return current;
            });
    }
}

template <typename T>
void bind_hstdIntSet(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    if (!guard.contains(PyNameType)) {
        guard.incl(PyNameType);
        nb::class_<hstd::IntSet<T>>(m, PyNameType)
            .def("__init__", [](hstd::IntSet<T>* result, nb::list list) {
                new (result) hstd::IntSet<T>();
                for (nb::handle it : list) {
                    result->incl(nb::cast<T>(it));
                }
            });
    }
}

template <typename T>
void bind_immerbox(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto name = std::string(PyNameType) + "ImmBox";
    if (!guard.contains(name)) {
        guard.incl(name);
        nb::class_<immer::box<T>>(m, name.c_str())
            .def(nb::init<>())
            .def(nb::init<const immer::box<T>&>())
            .def(
                "get",
                [](immer::box<T> const& it) -> T { return it.get(); })
            //
            ;
    }
}

template <typename T, typename VT>
void bind_imm_vector_base(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto name = std::string(PyNameType) + "ImmVec";
    if (!guard.contains(name)) {
        guard.incl(name);
        nb::class_<VT>(m, name.c_str())
            .def(nb::init<>())
            .def(nb::init<const VT&>())
            .def("__len__", [](VT const& it) -> int { return it.size(); })
            .def(
                "__init__",
                [](VT* self, nb::list list) {
                    VT   result;
                    auto tmp = result.transient();
                    for (auto const& it : list) {
                        tmp.push_back(nb::cast<T>(it));
                    }
                    new (self) VT(tmp.persistent());
                })
            //
            ;
    }
}

template <typename T>
void bind_imm_vector(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    return bind_imm_vector_base<T, immer::vector<T>>(m, PyNameType, guard);
}

template <typename T>
void bind_immerflex_vector(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    return bind_imm_vector_base<T, immer::flex_vector<T>>(
        m, PyNameType, guard);
}

/// \brief Bind specialization of the std vector map for use in python
template <typename T>
void bind_stdvector(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    using Vec = std::vector<T>;

    std::string name = std::string(PyNameType) + "StdVector";
    if (guard.contains(name)) { return; }

    guard.incl(name);

    auto cls = nb::bind_vector<Vec>(m, name.c_str());
    cls.def(nb::init<>());
}

/// \brief Bind specialization of the hstd vector for use in python
template <typename T>
void bind_hstdVec(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    using Vec = hstd::Vec<T>;

    std::string name = std::string(PyNameType) + "Vec";
    if (guard.contains(name)) { return; }

    guard.incl(name);

    auto cls = nb::bind_vector<Vec>(m, name.c_str());
    cls.def(nb::init<>())
        .def(nb::init<const Vec&>())
        .def(
            "__init__",
            [](Vec* self, nb::iterable it) {
                new (self) Vec();
                for (nb::handle h : it) {
                    self->push_back(nb::cast<T>(h));
                }
            })
        .def("FromValue", &Vec::FromValue);
}

/// \brief Bind specialization of the hstd unordered map for use in python
template <typename K, typename V, typename Hash = std::hash<K>>
void bind_hstdUnorderedMap(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    using Map = hstd::UnorderedMap<K, V, Hash>;

    std::string name = std::string(PyNameType) + "UnorderedMap";
    if (guard.contains(name)) { return; }

    guard.incl(name);

    auto cls = nb::bind_map<Map>(m, name.c_str());
    cls.def(nb::init<>()).def(nb::init<const Map&>());
}

/// nodoc
template <typename T>
struct py_arg_convertor {
    /// nodoc
    static void write(T& value, nb::handle const& py) {
        value = nb::cast<T>(py);
    }
};

template <typename T>
struct py_arg_convertor<hstd::Vec<T>> {
    /// nodoc
    static void write(hstd::Vec<T>& value, nb::handle const& py) {
        for (auto const& it : py) {
            py_arg_convertor<T>::write(value.emplace_back(), it);
        }
    }
};

/// \brief Generic `__init__` from kwargs for described types
template <hstd::DescribedRecord R>
void init_fields_from_kwargs(R& value, nb::kwargs const& kwargs) {
    hstd::UnorderedSet<hstd::Str> used_kwargs;
    hstd::for_each_field_with_bases<R>([&](auto const& field) {
        if (kwargs.contains(field.name)) {
            used_kwargs.incl(field.name);
            auto& ref = value.*field.pointer;
            py_arg_convertor<std::remove_cvref_t<decltype(ref)>>::write(
                ref, kwargs[field.name]);
        }
    });

    if (used_kwargs.size() != kwargs.size()) {
        hstd::UnorderedSet<hstd::Str> passed_kwargs;
        for (auto const& it : kwargs) {
            passed_kwargs.incl(hstd::Str(nb::str(it.first).c_str()));
        }
        throw std::logic_error(
            fmt("Passed unknown field name {}",
                (passed_kwargs - used_kwargs)));
    }
}

/// \brief Generic implementation for the `__getattr__` on described
/// classes
template <hstd::DescribedRecord R>
nb::object py_getattr_impl(R const& obj, std::string const& attr) {
    if (attr == "__dict__") {
        nb::dict result;
        hstd::for_each_field_value_with_bases<R>(
            obj,
            hstd::overloaded{
                [&](char const* name, nb::callable const& func) {
                    result[name] = func;
                },
                [&]<typename T>(
                    char const* name, hstd::Opt<T> const& field) {
                    if (field.has_value()) {
                        result[name] = nb::cast(field);
                    } else {
                        result[name] = nb::none();
                    }
                },
                [&](char const* name, auto const& field) {
                    result[name] = nb::cast(field);
                }});
        return result;
    } else {
        hstd::Opt<nb::object> result;
        hstd::for_each_field_value_with_bases<R>(
            obj,
            hstd::overloaded{
                [&](char const* name, nb::callable const& func) {
                    result = func;
                },
                [&](char const* name, auto const& field) {
                    if (std::string{name} == attr) {
                        result = nb::cast(field);
                    }
                }});

        if (result.has_value()) {
            return result.value();
        } else {
            throw nb::attribute_error(
                hstd::fmt(
                    "No attribute '{}' found for type {}",
                    attr,
                    typeid(obj).name())
                    .c_str());
        }
    }
}

/// \brief Generic implementation for the `__setattr__` on described
/// classes
template <hstd::DescribedRecord R>
void py_setattr_impl(R& obj, std::string const& attr, nb::object value) {
    bool found_target = false;
    for_each_field_with_bases<R>([&](auto const& field) {
        if (field.name == attr) {
            found_target       = true;
            obj.*field.pointer = nb::cast<
                std::remove_cvref_t<decltype(obj.*field.pointer)>>(value);
        }
    });

    if (!found_target) {
        throw nb::attribute_error(
            hstd::fmt(
                "No attribute '{}' found for type {}",
                attr,
                typeid(obj).name())
                .c_str());
    }
}

template <hstd::DescribedRecord R>
std::string py_repr_impl(R const& value) {
    return hstd::fmt1(value);
}

} // namespace org::bind::python
