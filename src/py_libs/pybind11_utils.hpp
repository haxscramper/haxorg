#pragma once

#include <immer/vector.hpp>
#include <immer/box.hpp>
#include <immer/flex_vector.hpp>
#include <pybind11/stl_bind.h>
#include <hstd/stdlib/Set.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/Map.hpp>

namespace org::bind::python {

namespace py = pybind11;

struct PyTypeRegistryGuard {
    hstd::UnorderedSet<hstd::Str> py_cxx_map;

    void incl(hstd::Str const& name) { py_cxx_map.incl(name); }
    bool contains(hstd::Str const& name) const {
        return py_cxx_map.contains(name);
    }

    PyTypeRegistryGuard() {
        auto const& registered_types = pybind11::detail::get_internals()
                                           .registered_types_py;
        for (auto& item : registered_types) {
            auto type = hstd::Str((((PyTypeObject*)item.first)->tp_name));
            auto name = type.split(".").at(1);
            py_cxx_map.incl(name);
        }
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
                if (current == hstd::value_domain<E>::high()) {
                    throw py::stop_iteration();
                }
                ++self;
                return current;
            });
    }
}

template <typename T>
void bind_hstdIntSet(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    if (!guard.contains(PyNameType)) {
        guard.incl(PyNameType);
        py::class_<hstd::IntSet<T>>(m, PyNameType)
            .def(py::init([](py::list list) -> hstd::IntSet<T> {
                hstd::IntSet<T> result;
                for (auto const& it : list) { result.incl(it.cast<T>()); }

                return result;
            }));
    }
}

template <typename T>
void bind_immerbox(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto name = std::string(PyNameType) + "ImmBox";
    if (!guard.contains(name)) {
        guard.incl(name);
        pybind11::class_<immer::box<T>>(m, name.c_str())
            .def(pybind11::init<>())
            .def(pybind11::init<const immer::box<T>&>())
            .def(
                "get",
                [](immer::box<T> const& it) -> T { return it.get(); })
            //
            ;
    }
}

template <typename T, typename VT>
void bind_imm_vector_base(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto name = std::string(PyNameType) + "ImmVec";
    if (!guard.contains(name)) {
        guard.incl(name);
        pybind11::class_<VT>(m, name.c_str())
            .def(pybind11::init<>())
            .def(pybind11::init<int, const T&>())
            .def(pybind11::init<std::initializer_list<T>>())
            .def(pybind11::init<const VT&>())
            .def("__len__", [](VT const& it) -> int { return it.size(); })
            .def(py::init([](py::list list) -> VT {
                VT   result;
                auto tmp = result.transient();
                for (auto const& it : list) {
                    tmp.push_back(it.cast<T>());
                }
                return tmp.persistent();
            }))
            //
            ;
    }
}

template <typename T>
void bind_imm_vector(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    return bind_imm_vector_base<T, immer::vector<T>>(m, PyNameType, guard);
}

template <typename T>
void bind_immerflex_vector(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    return bind_imm_vector_base<T, immer::flex_vector<T>>(
        m, PyNameType, guard);
}

template <typename T>
void bind_stdvector(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {

    auto base_name = std::string(PyNameType) + "StdVector";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        py::bind_vector<std::vector<T>>(m, base_name.c_str());
    }
}

template <typename T>
void bind_hstdVec(
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
        pybind11::class_<hstd::Vec<T>, std::vector<T>>(
            m, hstd_name.c_str())
            .def(pybind11::init<>())
            .def(pybind11::init<int, const T&>())
            .def(pybind11::init<std::initializer_list<T>>())
            .def(pybind11::init<const hstd::Vec<T>&>())
            .def(py::init([](py::list list) -> hstd::Vec<T> {
                hstd::Vec<T> result;
                for (auto const& it : list) {
                    result.push_back(it.cast<T>());
                }
                return result;
            }))
            .def("FromValue", &hstd::Vec<T>::FromValue)
            // .def("append", (void(Vec<T>::*)(const Vec<T>&)) &
            // Vec<T>::append)
            ;
    }
}

template <typename K, typename V>
void bind_hstdUnorderedMap(
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
        pybind11::
            class_<hstd::UnorderedMap<K, V>, std::unordered_map<K, V>>(
                m, hstd_name.c_str())
                .def(pybind11::init<>())
                .def(pybind11::init<const hstd::UnorderedMap<K, V>&>());
    }
}

template <typename K, typename V>
void bind_mapping(
    py::module&          m,
    const char*          PyNameType,
    PyTypeRegistryGuard& guard) {
    using M = hstd::UnorderedMap<K, V>;

    auto base_name = std::string(PyNameType) + "StdUnorderedMap";
    auto hstd_name = std::string(PyNameType) + "UnorderedMap";

    if (!guard.contains(base_name)) {
        guard.incl(base_name);
        py::bind_map<std::unordered_map<K, V>>(m, base_name.c_str());
    }

    if (!guard.contains(hstd_name)) {
        guard.incl(hstd_name);
        py::class_<hstd::UnorderedMap<K, V>, std::unordered_map<K, V>>(
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
struct py_arg_convertor<hstd::Vec<T>> {
    static void write(hstd::Vec<T>& value, pybind11::handle const& py) {
        for (auto const& it : py) {
            py_arg_convertor<T>::write(value.emplace_back(), it);
        }
    }
};

template <hstd::DescribedRecord R>
void init_fields_from_kwargs(R& value, pybind11::kwargs const& kwargs) {
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
            passed_kwargs.incl(hstd::Str(pybind11::str(it.first)));
        }
        throw std::logic_error(
            fmt("Passed unknown field name {}",
                (passed_kwargs - used_kwargs)));
    }
}

template <hstd::DescribedRecord R>
py::object py_getattr_impl(R const& obj, std::string const& attr) {
    if (attr == "__dict__") {
        py::dict result;
        hstd::for_each_field_value_with_bases<R>(
            obj,
            hstd::overloaded{
                [&](char const* name, py::function const& func) {
                    result[name] = func;
                },
                [&]<typename T>(
                    char const* name, hstd::Opt<T> const& field) {
                    if (field.has_value()) {
                        result[name] = py::cast(field);
                    } else {
                        result[name] = py::none();
                    }
                },
                [&](char const* name, auto const& field) {
                    result[name] = py::cast(field);
                }});
        return result;
    } else {
        hstd::Opt<py::object> result;
        hstd::for_each_field_value_with_bases<R>(
            obj,
            hstd::overloaded{
                [&](char const* name, py::function const& func) {
                    result = func;
                },
                [&](char const* name, auto const& field) {
                    if (std::string{name} == attr) {
                        result = py::cast(field);
                    }
                }});

        if (result.has_value()) {
            return result.value();
        } else {
            throw py::attribute_error(hstd::fmt(
                "No attribute '{}' found for type {}",
                attr,
                typeid(obj).name()));
        }
    }
}

template <hstd::DescribedRecord R>
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
        throw py::attribute_error(hstd::fmt(
            "No attribute '{}' found for type {}",
            attr,
            typeid(obj).name()));
    }
}

template <hstd::DescribedRecord R>
std::string py_repr_impl(R const& value) {
    return hstd::fmt1(value);
}

} // namespace org::bind::python
