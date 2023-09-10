#include <codegen/py_wrapper.hpp>
#include <codegen/py_converters.hpp>
#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/stdlib/Vec.hpp>

using namespace layout;

namespace boost::python {
template <typename T>
extract<T> extract_ptr(PyObject* ptr) {
    return py::extract<T>(py::object(python::handle<>(ptr)));
}
} // namespace boost::python

namespace boost::python::convert {

using pydata = py::converter::rvalue_from_python_stage1_data;

template <typename T>
struct to_python;

template <>
struct to_python<QString> {
    static PyObject* convert(CR<QString> value) {
        return incref(object(value.toLatin1().constData()).ptr());
    }
};

template <typename T>
struct from_python;

template <typename T>
void* is_accepted_by_extractor(PyObject* obj_ptr) {
    if (py::extract_ptr<T>(obj_ptr).check()) {
        return obj_ptr;
    } else {
        return 0;
    }
}


template <typename T, typename F>
void execute_extractor_cb(PyObject* obj_ptr, pydata* data, F cb) {
    // Grab pointer to memory into which to construct the new QString
    void* storage = ((py::converter::rvalue_from_python_storage<T>*)data)
                        ->storage.bytes;

    // in-place construct the new T using the character data
    // extraced from the python object
    new (storage) T(cb(obj_ptr));

    // Stash the memory chunk pointer for later use by boost.python
    data->convertible = storage;
}

template <typename T>
void execute_extractor(PyObject* obj_ptr, pydata* data) {
    execute_extractor_cb<T>(obj_ptr, data, [](PyObject* ptr) {
        return py::extract_ptr<T>(ptr)();
    });
}

template <typename T>
struct wrapped_extractor_from_python {
    // Determine if obj_ptr can be converted in a QString
    static void* convertible(PyObject* obj_ptr) {
        return is_accepted_by_extractor<T>(obj_ptr);
    }

    // Convert obj_ptr into a T
    static void construct(PyObject* obj_ptr, pydata* data) {
        execute_extractor<T>(obj_ptr, data);
    }
};

template <>
struct from_python<QString> : wrapped_extractor_from_python<QString> {};

}; // namespace boost::python::convert

namespace boost::python::convert {
template <>
struct from_python<BlockId> {
    static void* convertible(PyObject* obj_ptr) {
        return is_accepted_by_extractor<BlockId::id_base_type>(obj_ptr);
    }

    static void construct(PyObject* ptr, pydata* data) {
        execute_extractor_cb<BlockId>(ptr, data, [](PyObject* ptr) {
            return BlockId::FromValue(
                py::extract_ptr<BlockId::id_base_type>(ptr)());
        });
    }
};

template <>
struct to_python<BlockId> {
    static PyObject* convert(CR<BlockId> value) {
        return incref(object(value.getValue()).ptr());
    }
};

} // namespace boost::python::convert

struct TextLayout {
    BlockStore        b;
    SimpleStringStore store;
    TextLayout() : store{&b} {}

    BlockId text(QString t) { return store.text(t); }
    BlockId stack(CVec<BlockId> ids) { return b.stack(ids); }
    BlockId line(CVec<BlockId> ids) { return b.line(ids); }
    BlockId choice(CVec<BlockId> ids) { return b.choice(ids); }
    BlockId space(int count) { return b.space(count); }
    BlockId empty() { return b.empty(); }

    BlockId wrap(CVec<BlockId> ids, QString sep) {
        return b.wrap(ids, store.str(sep));
    }


    QString toString(BlockId id, CR<Options> options) {
        return store.toString(id);
    }
};

BOOST_DESCRIBE_STRUCT(
    Options,
    (),
    (leftMargin,
     rightMargin,
     leftMarginCost,
     rightMarginCost,
     linebreakCost,
     indentSpaces,
     cpack));

namespace pywrap {
template <typename T>
void register_converters() {
    py::to_python_converter<T, py::convert::to_python<T>>();

    py::converter::registry::push_back(
        &boost::python::convert::from_python<T>::convertible,
        &boost::python::convert::from_python<T>::construct,
        py::type_id<T>());
}
} // namespace pywrap

BOOST_PYTHON_MODULE(py_textlayout) {
    using namespace boost::python;

    pywrap::register_converters<QString>();
    pywrap::register_converters<layout::BlockId>();

    class_<TextLayout>("TextLayout")
        .def("text", &TextLayout::text)
        .def("line", &TextLayout::line)
        .def("stack", &TextLayout::stack)
        .def("choice", &TextLayout::choice)
        .def("space", &TextLayout::space)
        .def("empty", &TextLayout::empty)
        .def("toString", &TextLayout::toString)
        //
        ;

    class_<layout::Options>("TextOptions")
        .def_readwrite("leftMargin", &Options::leftMargin)
        .def_readwrite("rightMargin", &Options::rightMargin)
        .def_readwrite("leftMarginCost", &Options::leftMarginCost)
        .def_readwrite("rightMarginCost", &Options::rightMarginCost)
        .def_readwrite("linebreakCost", &Options::linebreakCost)
        .def_readwrite("indentSpaces", &Options::indentSpaces)
        .def_readwrite("cpack", &Options::cpack)
        //
        ;
}
