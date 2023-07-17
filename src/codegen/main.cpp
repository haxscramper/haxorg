#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>

#include <QFileInfo>

#include <hstd/stdlib/Debug.hpp>

#include "gen_description.hpp"
#include "gen_converter.hpp"
#include "guile_wrapper.hpp"

QTextStream qcout;

namespace guile {
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
struct convert<GenDescription::Entry>
    : variant_convert<
          GenDescription::Entry,
          convert<GenDescription::Entry>> {
    static void init(GenDescription::Entry& result, SCM value) {
        std::string kind = convert<GenDescription::Entry>::get_kind(value);
        if (kind == "Struct") {
            result = GenDescription::Struct{};
        } else if (kind == "Enum") {
            result = GenDescription::Enum{};
        } else if (kind == "TypeGroup") {
            result = GenDescription::TypeGroup{};
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

    GenDescription description;
    ::guile::convert<GenDescription>::decode(description, doc);
    ASTBuilder builder;

    auto definitions = convert(builder, description);
    auto result      = builder.TranslationUnit({definitions});

    std::ofstream out{"/tmp/result.cpp"};
    out << builder.store.toString(result, layout::Options()) << std::endl;
}
