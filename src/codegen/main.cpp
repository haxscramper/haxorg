#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>

#include <QFileInfo>

#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Filesystem.hpp>

#include "gen_description.hpp"
#include "gen_converter.hpp"
#include "py_wrapper.hpp"
#include <hstd/stdlib/strformat.hpp>

QTextStream qcout;

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
    bool check() const { return PyCheck_List(obj); }

    Vec<T> operator()() {
        Vec<T> result;
        result.resize(PyList_Size(obj));

        for (int i = 0; i < result.size(); ++i) {
            result.at(i) = py::extract<T>(PyList_GetItem(list, i))();
        }

        return result;
    }
};

template <typename T>
struct extract<Opt<T>> : py_extract_base {
    using result_type = Opt<T>;
    bool check() const { return; }

    T operator()() {
        if constexpr (obj == Py_None) {
            return std::nullopt;
        } else {
            return py::extract<T>(obj)();
        }
    }
};

template <>
struct extract<Str> : py_extract_base {
    using result_type = Str;
    using py_extract_base::py_extract_base;
    bool check() const { return PyUnicode_Check(obj.ptr()); }
    Str  operator()() {
        if (!check()) {
            PyErr_SetString(PyExc_TypeError, "Expected a Unicode string");
            boost::python::throw_error_already_set();
        }

        // Convert the Python Unicode object to a UTF-8 string
        PyObject* utf8_str = PyUnicode_AsUTF8String(obj.ptr());
        if (utf8_str == nullptr) {
            PyErr_SetString(
                PyExc_ValueError, "Failed to encode string to UTF-8");
            boost::python::throw_error_already_set();
        }

        // Convert the UTF-8 string to a QString
        char*   c_str = PyBytes_AsString(utf8_str);
        QString qstr  = QString::fromUtf8(c_str);

        // Decrement the reference count of the temporary UTF-8 string
        Py_DECREF(utf8_str);

        return qstr;
    }
};


} // namespace boost::python

int main(int argc, const char** argv) {
    QFile stdoutFile;
    if (stdoutFile.open(stdout, QIODevice::WriteOnly)) {
        qcout.setDevice(&stdoutFile);
    } else {
        qFatal("Failed to open stdout for reading");
    }

    Py_Initialize();

    py::object main = py::import("__main__");

    // Import the Python script file
    std::ifstream t(argv[1]);
    std::string   script(
        (std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    // Execute the script
    py::exec(script.c_str(), main.attr("__dict__"));

    // Call the gen_value function
    py::object gen_value = main.attr("gen_value");
    py::object result    = gen_value();

    QtMessageHandler old = qInstallMessageHandler(tracedMessageHandler);

    GenFiles   description = py::extract<GenFiles>(result)();
    ASTBuilder builder;

    for (GenUnit const& tu : description.files) {
        for (int i = 0; i <= 1; ++i) {
            if (i == 1 && !tu.source.has_value()) {
                continue;
            }

            bool isHeader = i == 0;
            auto result   = builder.TranslationUnit(
                {isHeader
                       ? GenConverter(builder, !isHeader).convert(tu.header)
                       : GenConverter(builder, !isHeader)
                             .convert(tu.source.value())});

            auto const& define = isHeader ? tu.header : tu.source.value();
            QString     path   = define.path
                         % fold_format_pairs({
                             {"base", "/mnt/workspace/repos/haxorg/src"},
                         });

            QFileInfo file{path};
            QString   newCode = builder.store.toString(
                result, layout::Options());

            if (file.exists()) {
                QString oldCode = readFile(file);
                if (oldCode != newCode) {
                    std::ofstream out{path.toStdString()};
                    out << newCode;
                    qDebug() << "Updated code in" << path << "pattern was"
                             << define.path;
                } else {
                    qDebug() << "No changes on" << path << "pattern was"
                             << define.path;
                }
            } else {
                std::ofstream out{path.toStdString()};
                out << newCode;
                qDebug() << "Wrote to" << path << "pattern was"
                         << define.path;
            }
        }
    }
}
