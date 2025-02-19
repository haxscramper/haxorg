#pragma once

#include <pybind11/stl_bind.h>
#include <hstd/stdlib/Set.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/Map.hpp>

namespace py = pybind11;

struct PyTypeRegistryGuard {
    UnorderedSet<Str> py_cxx_map;

    void incl(Str const& name) { py_cxx_map.incl(name); }
    bool contains(Str const& name) const {
        return py_cxx_map.contains(name);
    }

    PyTypeRegistryGuard() {
        auto const& registered_types = pybind11::detail::get_internals()
                                           .registered_types_py;
        for (auto& item : registered_types) {
            auto type = Str((((PyTypeObject*)item.first)->tp_name));
            auto name = type.split(".").at(1);
            py_cxx_map.incl(name);
        }
    }
};

template <typename E>
class PyEnumIterator {
  public:
    explicit PyEnumIterator(E value = value_domain<E>::low())
        : value(value) {}

    E operator*() const { return value; }

    PyEnumIterator& operator++() {
        value = value_domain<E>::succ(value);
        return *this;
    }

    bool operator!=(const PyEnumIterator& other) const {
        return value_domain<E>::ord(value)
            != value_domain<E>::ord(other.value);
    }

  private:
    E value;
};

template <typename E>
void bind_enum_iterator(
    py::module&          m,
    const char*          PyTypeName,
    PyTypeRegistryGuard& guard) {
    auto name = std::string(PyTypeName) + "EnumIterator";
    if (!guard.contains(name)) {
        guard.incl(name);
        py::class_<PyEnumIterator<E>>(m, name.c_str())
            .def("__iter__", [](PyEnumIterator<E>& self) { return self; })
            .def("__next__", [](PyEnumIterator<E>& self) {
                auto current = *self;
                if (current == value_domain<E>::high()) {
                    throw py::stop_iteration();
                }
                ++self;
                return current;
            });
    }
}

template <typename T>
void bind_int_set(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    if (!guard.contains(PyNameType)) {
        guard.incl(PyNameType);
        py::class_<IntSet<T>>(m, PyNameType)
            .def(py::init([](py::list list) -> IntSet<T> {
                IntSet<T> result;
                for (auto const& it : list) { result.incl(it.cast<T>()); }

                return result;
            }));
    }
}

template <typename T>
void bind_vector(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto base_name = std::string(PyNameType) + "StdVector";
    auto hstd_name = std::string(PyNameType) + "Vec";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        py::bind_vector<std::vector<T>>(m, base_name.c_str());
    }

    if (!guard.contains(hstd_name)) {
        guard.incl(hstd_name);
        pybind11::class_<Vec<T>, std::vector<T>>(m, hstd_name.c_str())
            .def(pybind11::init<>())
            .def(pybind11::init<int, const T&>())
            .def(pybind11::init<std::initializer_list<T>>())
            .def(pybind11::init<const Vec<T>&>())
            .def(py::init([](py::list list) -> Vec<T> {
                Vec<T> result;
                for (auto const& it : list) {
                    result.push_back(it.cast<T>());
                }
                return result;
            }))
            .def("FromValue", &Vec<T>::FromValue)
            // .def("append", (void(Vec<T>::*)(const Vec<T>&)) &
            // Vec<T>::append)
            ;
    }
}

template <typename K, typename V>
void bind_unordered_map(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    auto base_name = std::string(PyNameType) + "StdUnorderedMap";
    auto hstd_name = std::string(PyNameType) + "UnorderedMap";


    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        py::bind_map<std::unordered_map<K, V>>(m, base_name.c_str());
    }

    if (!guard.contains(hstd_name)) {
        guard.incl(hstd_name);
        pybind11::class_<UnorderedMap<K, V>, std::unordered_map<K, V>>(
            m, hstd_name.c_str())
            .def(pybind11::init<>())
            .def(pybind11::init<const UnorderedMap<K, V>&>());
    }
}

template <typename K, typename V>
void bind_mapping(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    using M = UnorderedMap<K, V>;

    auto base_name = std::string(PyNameType) + "StdUnorderedMap";
    auto hstd_name = std::string(PyNameType) + "UnorderedMap";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        py::bind_map<std::unordered_map<K, V>>(m, base_name.c_str());
    }

    if (!guard.contains(hstd_name)) {
        guard.incl(hstd_name);
        py::class_<UnorderedMap<K, V>, std::unordered_map<K, V>>(
            m, hstd_name.c_str())
            .def(py::init<>())
            .def("contains", &M::contains)
            .def("get", &M::get)
            .def("keys", &M::keys);
    }
}

template <typename T>
struct py_arg_convertor {
    static void write(T& value, pybind11::handle const& py) {
        value = py.cast<T>();
    }
};

template <typename T>
struct py_arg_convertor<Vec<T>> {
    static void write(Vec<T>& value, pybind11::handle const& py) {
        for (auto const& it : py) {
            py_arg_convertor<T>::write(value.emplace_back(), it);
        }
    }
};

template <DescribedRecord R>
void init_fields_from_kwargs(R& value, pybind11::kwargs const& kwargs) {
    UnorderedSet<Str> used_kwargs;
    for_each_field_with_bases<R>([&](auto const& field) {
        if (kwargs.contains(field.name)) {
            used_kwargs.incl(field.name);
            auto& ref = value.*field.pointer;
            py_arg_convertor<std::remove_cvref_t<decltype(ref)>>::write(
                ref, kwargs[field.name]);
        }
    });

    if (used_kwargs.size() != kwargs.size()) {
        UnorderedSet<Str> passed_kwargs;
        for (auto const& it : kwargs) {
            passed_kwargs.incl(Str(pybind11::str(it.first)));
        }
        throw std::logic_error(
            fmt("Passed unknown field name {}",
                (passed_kwargs - used_kwargs)));
    }
}

template <DescribedRecord R>
py::object py_getattr_impl(R const& obj, std::string const& attr) {
    if (attr == "__dict__") {
        py::dict result;
        for_each_field_with_bases<R>(overloaded{
            [&]<typename T>(Opt<T> const& field) {
                if (field.has_value()) {
                    result[field.name] = py::cast(obj.*field.pointer);
                } else {
                    result[field.name] = py::none();
                }
            },
            [&](auto const& field) {
                result[field.name] = py::cast(obj.*field.pointer);
            }});
        return result;
    } else {
        Opt<py::object> result;
        for_each_field_with_bases<R>([&](auto const& field) {
            if (field.name == attr) {
                result = py::cast(obj.*field.pointer);
            }
        });

        if (result.has_value()) {
            return result.value();
        } else {
            throw py::attribute_error(
                fmt("No attribute '{}' found for type {}",
                    attr,
                    typeid(obj).name()));
        }
    }
}

template <DescribedRecord R>
void py_setattr_impl(R& obj, std::string const& attr, py::object value) {
    bool found_target = false;
    for_each_field_with_bases<R>([&](auto const& field) {
        if (field.name == attr) {
            found_target       = true;
            obj.*field.pointer = value.cast<
                std::remove_cvref_t<decltype(obj.*field.pointer)>>();
        }
    });

    if (!found_target) {
        throw py::attribute_error(
            fmt("No attribute '{}' found for type {}",
                attr,
                typeid(obj).name()));
    }
}

template <DescribedRecord R>
std::string py_repr_impl(R const& value) {
    return fmt1(value);
}
