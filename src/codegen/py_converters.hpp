#pragma once

#include "py_wrapper.hpp"

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Str.hpp>

namespace boost::python {
template <typename T>
struct extract<std::shared_ptr<T>> : py_extract_base {
    using py_extract_base::py_extract_base;
    using result_type = std::shared_ptr<T>;
    bool check() const { return extract<T>(obj).check(); }

    std::shared_ptr<T> operator()() {
        return std::make_shared<T>(extract<T>(obj)());
    }
};


template <typename T>
struct extract<Vec<T>> : py_extract_base {
    using py_extract_base::py_extract_base;
    using result_type = Vec<T>;
    bool check() const { return pywrap::is_list(obj); }

    Vec<T> operator()() {
        py::list const& list = py::extract<py::list>(obj)();
        Vec<T>          result;
        result.resize(py::len(list), SerdeDefaultProvider<T>::get());

        for (int i = 0; i < result.size(); ++i) {
            result.at(i) = py::extract<T>(list[i])();
        }

        return result;
    }
};

template <>
struct extract<Str> : py_extract_base {
    using py_extract_base::py_extract_base;
    bool check() const { return extract<QString>(obj).check(); }
    Str  operator()() { return extract<QString>(obj)(); }
};


} // namespace boost::python
