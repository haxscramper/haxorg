#include <codegen/py_wrapper.hpp>
#include <codegen/py_converters.hpp>
#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <boost/stacktrace.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <QFile>

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
    Q_CHECK_PTR(storage);

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


}; // namespace boost::python::convert

// Definitions for common types, to be moved elsewhere
namespace boost::python::convert {
template <>
struct from_python<QString> : wrapped_extractor_from_python<QString> {};

template <>
struct to_python<QString> {
    static PyObject* convert(CR<QString> value) {
        PyObject* tmp = incref(object(value.toLatin1().constData()).ptr());
        Q_CHECK_PTR(tmp);
        return tmp;
    }
};


template <typename T>
struct from_python<Vec<T>> : wrapped_extractor_from_python<Vec<T>> {};

template <typename T>
struct to_python<Vec<T>> {
    static PyObject* convert(const Vec<T>& vec) {
        py::list list;
        for (const auto& item : vec) {
            list.append(py::object(item));
        }
        return py::incref(list.ptr());
    }
};

} // namespace boost::python::convert

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
        PyObject* result = incref(object(value.getValue()).ptr());
        Q_CHECK_PTR(result);
        return result;
    }
};

} // namespace boost::python::convert

void exception_breakpoint() {
    std::cout << "Stacktrace:\n"
              << boost::stacktrace::stacktrace() << std::endl;
    throw; // rethrow the same exception
}

struct TextLayout {
    BlockStore        b;
    SimpleStringStore store;


    TextLayout() : store{&b} {}
    ~TextLayout() { qDebug() << "Destructor of text layout"; }

    void dbg() {
        qDebug() << __LINE__ << b.store.size() << store.strings.size();
    }

    BlockId text(QString t) { return store.text(t); }

    BlockId stack(CVec<BlockId> ids) { return b.stack(ids); }

    BlockId line(CVec<BlockId> ids) { return b.line(ids); }

    BlockId choice(CVec<BlockId> ids) { return b.choice(ids); }

    BlockId space(int count) { return b.space(count); }

    BlockId empty() { return b.empty(); }

    BlockId join(
        CVec<BlockId> items,
        CR<BlockId>   join,
        bool          isLine,
        bool          isTrailing) {
        return b.join(items, join, isLine, isTrailing);
    }

    BlockId wrap(CVec<BlockId> ids, QString sep) {
        return b.wrap(ids, store.str(sep));
    }

    QString toString(BlockId id, CR<Options> options) {
        try {
            return store.toString(id);
        } catch (...) { exception_breakpoint(); }
    }

    QString toTreeRepr(BlockId id) {
        try {
            return store.toTreeRepr(id);
        } catch (...) { exception_breakpoint(); }
    }

    void add_at(BlockId const& id, BlockId const& next) {
        b.add_at(id, next);
    }

    void add_at(BlockId const& id, Vec<BlockId> const& next) {
        b.add_at(id, next);
    }

    static void py_define() {
        py::class_<TextLayout>("TextLayout")
            .def("dbg", &TextLayout::dbg)
            .def("text", &TextLayout::text)
            .def("line", &TextLayout::line)
            .def(
                "stack",
                &TextLayout::stack,
                (py::arg("self"), py::arg("ids") = Vec<BlockId>{}))
            .def(
                "join",
                &TextLayout::join,
                (py::arg("self"),
                 py::arg("items"),
                 py::arg("join"),
                 py::arg("isLine")     = true,
                 py::arg("isTrailing") = false))
            .def("choice", &TextLayout::choice)
            .def("space", &TextLayout::space)
            .def("empty", &TextLayout::empty)
            .def("toString", &TextLayout::toString)
            .def("toTreeRepr", &TextLayout::toTreeRepr)
            .def(
                "add_at",
                (void(TextLayout::*)(BlockId const&, BlockId const&))
                    & TextLayout::add_at)
            .def(
                "add_at",
                (void(TextLayout::*)(BlockId const&, Vec<BlockId> const&))
                    & TextLayout::add_at)
            //
            ;
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
concept StaticallyConvertible = requires(
    CR<T>                                          value,
    PyObject*                                      obj,
    py::converter::rvalue_from_python_stage1_data* data) {
    {
        py::convert::from_python<T>::convertible(obj)
    } -> std::same_as<void*>;

    py::convert::from_python<T>::construct(obj, data);

    {
        py::convert::to_python<T>::convert(value)
    } -> std::same_as<PyObject*>;
};

template <StaticallyConvertible T>
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
    pywrap::register_converters<Vec<layout::BlockId>>();

    TextLayout::py_define();


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
