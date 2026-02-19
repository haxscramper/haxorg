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

namespace org::bind::python {

namespace nb = nanobind;

struct PyTypeRegistryGuard {
    hstd::UnorderedSet<hstd::Str> py_cxx_map;

    void incl(hstd::Str const& name) { py_cxx_map.incl(name); }
    bool contains(hstd::Str const& name) const {
        return py_cxx_map.contains(name);
    }

    PyTypeRegistryGuard() {
        // nanobind does not expose a global registry of registered types
        // in the same way pybind11 does, so we start with an empty guard.
    }
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

template <typename T>
void bind_stdvector(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto base_name = std::string(PyNameType) + "StdVector";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        nb::class_<std::vector<T>>(m, base_name.c_str())
            .def(nb::init<>())
            .def(
                "__len__",
                [](std::vector<T> const& v) { return v.size(); })
            .def(
                "__getitem__",
                [](std::vector<T> const& v, size_t i) -> T const& {
                    if (i >= v.size()) { throw nb::index_error(); }
                    return v[i];
                },
                nb::rv_policy::reference_internal)
            .def(
                "__setitem__",
                [](std::vector<T>& v, size_t i, T const& val) {
                    if (i >= v.size()) { throw nb::index_error(); }
                    v[i] = val;
                })
            .def(
                "append",
                [](std::vector<T>& v, T const& val) { v.push_back(val); })
            .def(
                "__iter__",
                [](std::vector<T>& v) {
                    return nb::make_iterator(
                        nb::type<std::vector<T>>(),
                        "iterator",
                        v.begin(),
                        v.end());
                },
                nb::keep_alive<0, 1>());
    }
}

template <typename T>
void bind_hstdVec(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto base_name = std::string(PyNameType) + "StdVector";
    auto hstd_name = std::string(PyNameType) + "Vec";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        nb::class_<std::vector<T>>(m, base_name.c_str())
            .def(nb::init<>())
            .def(
                "__len__",
                [](std::vector<T> const& v) { return v.size(); })
            .def(
                "__getitem__",
                [](std::vector<T> const& v, size_t i) -> T const& {
                    if (i >= v.size()) { throw nb::index_error(); }
                    return v[i];
                },
                nb::rv_policy::reference_internal)
            .def(
                "__setitem__",
                [](std::vector<T>& v, size_t i, T const& val) {
                    if (i >= v.size()) { throw nb::index_error(); }
                    v[i] = val;
                })
            .def(
                "append",
                [](std::vector<T>& v, T const& val) { v.push_back(val); })
            .def(
                "__iter__",
                [](std::vector<T>& v) {
                    return nb::make_iterator(
                        nb::type<std::vector<T>>(),
                        "iterator",
                        v.begin(),
                        v.end());
                },
                nb::keep_alive<0, 1>());
    }

    if (!guard.contains(hstd_name)) {
        guard.incl(hstd_name);
        nb::class_<hstd::Vec<T>, std::vector<T>>(m, hstd_name.c_str())
            .def(nb::init<>())
            .def(nb::init<const hstd::Vec<T>&>())
            .def(
                "__init__",
                [](hstd::Vec<T>* self, nb::list list) {
                    new (self) hstd::Vec<T>();
                    for (auto const& it : list) {
                        self->push_back(nb::cast<T>(it));
                    }
                })
            .def("FromValue", &hstd::Vec<T>::FromValue);
    }
}


template <typename K, typename V>
void bind_hstdUnorderedMap(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    auto base_name = std::string(PyNameType) + "StdUnorderedMap";
    auto hstd_name = std::string(PyNameType) + "UnorderedMap";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        nb::class_<std::unordered_map<K, V>>(m, base_name.c_str())
            .def(nb::init<>())
            .def(
                "__len__",
                [](std::unordered_map<K, V> const& map) {
                    return map.size();
                })
            .def(
                "__getitem__",
                [](std::unordered_map<K, V> const& map,
                   K const&                        key) -> V const& {
                    auto it = map.find(key);
                    if (it == map.end()) { throw nb::key_error(); }
                    return it->second;
                },
                nb::rv_policy::reference_internal)
            .def(
                "__setitem__",
                [](std::unordered_map<K, V>& map,
                   K const&                  key,
                   V const&                  val) { map[key] = val; })
            .def(
                "__contains__",
                [](std::unordered_map<K, V> const& map, K const& key) {
                    return map.count(key) > 0;
                })
            .def(
                "__iter__",
                [](std::unordered_map<K, V>& map) {
                    return nb::make_key_iterator(
                        nb::type<std::unordered_map<K, V>>(),
                        "key_iterator",
                        map.begin(),
                        map.end());
                },
                nb::keep_alive<0, 1>());
    }

    if (!guard.contains(hstd_name)) {
        guard.incl(hstd_name);
        nb::class_<hstd::UnorderedMap<K, V>, std::unordered_map<K, V>>(
            m, hstd_name.c_str())
            .def(nb::init<>())
            .def(nb::init<const hstd::UnorderedMap<K, V>&>());
    }
}

/// \brief Bind unordered map type for python
template <typename K, typename V>
void bind_mapping(
    nb::module_&         m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    using M = hstd::UnorderedMap<K, V>;

    auto base_name = std::string(PyNameType) + "StdUnorderedMap";
    auto hstd_name = std::string(PyNameType) + "UnorderedMap";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        nb::class_<std::unordered_map<K, V>>(m, base_name.c_str())
            .def(nb::init<>())
            .def(
                "__len__",
                [](std::unordered_map<K, V> const& map) {
                    return map.size();
                })
            .def(
                "__getitem__",
                [](std::unordered_map<K, V> const& map,
                   K const&                        key) -> V const& {
                    auto it = map.find(key);
                    if (it == map.end()) { throw nb::key_error(); }
                    return it->second;
                },
                nb::rv_policy::reference_internal)
            .def(
                "__setitem__",
                [](std::unordered_map<K, V>& map,
                   K const&                  key,
                   V const&                  val) { map[key] = val; })
            .def(
                "__contains__",
                [](std::unordered_map<K, V> const& map, K const& key) {
                    return map.count(key) > 0;
                })
            .def(
                "__iter__",
                [](std::unordered_map<K, V>& map) {
                    return nb::make_key_iterator(
                        nb::type<std::unordered_map<K, V>>(),
                        "key_iterator",
                        map.begin(),
                        map.end());
                },
                nb::keep_alive<0, 1>());
    }

    if (!guard.contains(hstd_name)) {
        guard.incl(hstd_name);
        nb::class_<hstd::UnorderedMap<K, V>, std::unordered_map<K, V>>(
            m, hstd_name.c_str())
            .def(nb::init<>())
            .def("contains", &M::contains)
            .def("get", &M::get)
            .def("keys", &M::keys);
    }
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
