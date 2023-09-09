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

template <>
struct extract<GenTu::Entry> : py_extract_base {
    using py_extract_base::py_extract_base;
    using result_type = GenTu::Entry;
    bool check() const { return true; }

    result_type operator()() {
        result_type result{variant_from_index<result_type>(
            variant_type_index<GenTu::EntryKind>(obj, "kind"))};
        visit_extract<result_type>(result, obj);
        return result;
    }
};

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
        py::list const& list = py::extract<py::list>(obj)();
        Vec<T>          result;
        result.resize(py::len(list));

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
    try {
        py::exec(script.c_str(), main.attr("__dict__"));
    } catch (py::error_already_set& err) {
        PyErr_Print();
        return 1;
    }

    py::object gen_value;
    try {
        gen_value = main.attr("gen_value");
    } catch (py::error_already_set& as) {
        qFatal() << "Expected 'gen_value' function in the script file";
        return 1;
    }

    py::object result = gen_value();

    QtMessageHandler old = qInstallMessageHandler(tracedMessageHandler);

    try {
        GenFiles description = py::extract<GenFiles>(result)();
    } catch (py::error_already_set& as) { PyErr_Print(); }

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
