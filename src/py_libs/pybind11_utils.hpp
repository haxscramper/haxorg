#pragma once

#include <pybind11/stl_bind.h>

namespace py = pybind11;

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
void bind_enum_iterator(py::module& m, const char* PyTypeName) {
    py::class_<PyEnumIterator<E>>(
        m, (std::string(PyTypeName) + "EnumIterator").c_str())
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

template <typename T>
void bind_int_set(py::module& m, const char* PyNameType) {
    py::class_<IntSet<T>>(m, PyNameType)
        .def(py::init([](py::list list) -> IntSet<T> {
            IntSet<T> result;
            for (auto const& it : list) { result.incl(it.cast<T>()); }

            return result;
        }));
}

template <typename T>
void bind_vector(py::module& m, const char* PyNameType) {
    py::bind_vector<std::vector<T>>(
        m, (std::string(PyNameType) + "StdVector").c_str());
    pybind11::class_<Vec<T>, std::vector<T>>(
        m, (std::string(PyNameType) + "Vec").c_str())
        .def(pybind11::init<>())
        .def(pybind11::init<int, const T&>())
        .def(pybind11::init<std::initializer_list<T>>())
        .def(pybind11::init<const Vec<T>&>())
        .def(py::init([](py::list list) -> Vec<T> {
            Vec<T> result;
            for (auto const& it : list) { result.push_back(it.cast<T>()); }
            return result;
        }))
        .def("FromValue", &Vec<T>::FromValue)
        // .def("append", (void(Vec<T>::*)(const Vec<T>&)) &
        // Vec<T>::append)
        ;
}

template <typename K, typename V>
void bind_unordered_map(py::module& m, const char* PyNameType) {
    py::bind_map<std::unordered_map<K, V>>(
        m, (std::string(PyNameType) + "StdUnorderedMap").c_str());

    pybind11::class_<UnorderedMap<K, V>, std::unordered_map<K, V>>(
        m, (std::string(PyNameType) + "UnorderedMap").c_str())
        .def(pybind11::init<>())
        .def(pybind11::init<const UnorderedMap<K, V>&>());
}

template <typename K, typename V>
void bind_mapping(py::module& m, const char* PyNameType) {
    using M = UnorderedMap<K, V>;

    py::bind_map<std::unordered_map<K, V>>(
        m, (std::string(PyNameType) + "StdUnorderedMap").c_str());

    py::class_<UnorderedMap<K, V>, std::unordered_map<K, V>>(
        m, (std::string(PyNameType) + "UnorderedMap").c_str())
        .def(py::init<>())
        .def("contains", &M::contains)
        .def("get", &M::get)
        .def("keys", &M::keys);
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
        for_each_field_with_bases<R>([&](auto const& field) {
            result[field.name] = py::cast(obj.*field.pointer);
        });
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
