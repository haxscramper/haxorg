#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>

#include <QFileInfo>

#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Filesystem.hpp>

#include "gen_description.hpp"
#include "gen_converter.hpp"
#include "guile_wrapper.hpp"

QTextStream qcout;

namespace guile {

template <typename T>
struct convert<std::shared_ptr<T>> {
    static bool decode(std::shared_ptr<T>& rhs, SCM node) {
        rhs = std::make_shared<T>();
        ::guile::convert<T>::decode(*rhs, node);
        return true;
    }
};

template <typename T>
struct convert<Vec<T>> {
    static void decode(Vec<T>& result, SCM list) {
        if (scm_is_true(scm_list_p(list))) {
            for (; scm_is_true(scm_pair_p(list)); list = scm_cdr(list)) {
                T temp;
                ::guile::convert<T>::decode(temp, scm_car(list));
                result.push_back(temp);
            }
        } else {
            throw decode_error("parsing list value", list);
        }
    }
};

template <typename T>
struct convert<Opt<T>> {
    static void decode(Opt<T>& result, SCM list) {
        if constexpr (std::is_same_v<bool, T>) {
            result = scm_is_true(list);
        } else if (!scm_is_false(list)) {
            T out;
            ::guile::convert<T>::decode(out, list);
            result = out;
        }
    }
};

template <>
struct convert<Str> {
    static void decode(Str& result, SCM item) {
        if (scm_is_true(scm_string_p(item))) {
            result = Str::fromStdString(::guile::to_string(item));
        } else if (scm_is_symbol(item)) {
            result = Str::fromStdString(::guile::to_string(item));
        } else {
            throw decode_error("parsing string", item);
        }
    }
};

template <>
struct convert<GenTu::Entry>
    : variant_convert<GenTu::Entry, convert<GenTu::Entry>> {
    static void init(GenTu::Entry& result, SCM value) {
        std::string kind = convert<GenTu::Entry>::get_kind(value);
        if (kind == "Struct") {
            result = std::make_shared<GenTu::Struct>();
        } else if (kind == "Enum") {
            result = std::make_shared<GenTu::Enum>();
        } else if (kind == "Group") {
            result = std::make_shared<GenTu::TypeGroup>();
        } else if (kind == "Include") {
            result = GenTu::Include{};
        } else if (kind == "Pass") {
            result = GenTu::Pass{};
        } else if (kind == "Method") {
            result = std::make_shared<GenTu::Function>();
        } else {
            throw decode_error(
                "parsing GenDescriptionEntry variant", value);
        }
    }
};

} // namespace guile

int main(int argc, const char** argv) {
    QFile stdoutFile;
    if (stdoutFile.open(stdout, QIODevice::WriteOnly)) {
        qcout.setDevice(&stdoutFile);
    } else {
        qFatal("Failed to open stdout for reading");
    }

    guile::init();
    SCM           doc = guile::eval_file(argv[1]);
    std::ofstream file{"/tmp/repr.txt"};
    ::guile::print(doc, file);
    file << std::endl;


    QtMessageHandler old = qInstallMessageHandler(tracedMessageHandler);

    GenFiles description;
    ::guile::convert<GenFiles>::decode(description, doc);
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
