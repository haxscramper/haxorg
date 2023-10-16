#include <lexbase/NodeTest.hpp>
#include <string>
#include <filesystem>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/system/reflection.hpp>
#include <boost/mp11.hpp>


json toJson(CR<yaml> node) {
    switch (node.Type()) {
        case YAML::NodeType::Undefined: {
            return json();
        }

        case YAML::NodeType::Map: {
            json res = json::object();
            for (const auto& it : node) {
                res[it.first.as<std::string>()] = toJson(it.second);
            }
            return res;
        }

        case YAML::NodeType::Sequence: {
            json res = json::array();
            for (const auto& it : node) {
                res.push_back(toJson(it));
            }
            return res;
        }

        case YAML::NodeType::Null: {
            return json();
        }

        case YAML::NodeType::Scalar: {
            bool    ok     = false;
            std::string scalar = std::string::fromStdString(node.Scalar());
            {
                long long int intValue = scalar.toLongLong(&ok);
                if (ok) {
                    return intValue;
                }
            }

            {
                double doubleVal = scalar.toDouble(&ok);
                if (ok) {
                    return doubleVal;
                }
            }

            { return node.Scalar(); }
        }
    }
}

namespace YAML {

template <typename T>
struct convert<Vec<T>> {
    static Node encode(Vec<T> const& v) {
        Node res;
        for (auto const& it : v) {
            res.push_back(::YAML::convert<T>::encode(it));
        }
        return res;
    }

    static bool decode(Node const& in, Vec<T>& out) {
        for (auto const& it : in) {
            T tmp;
            ::YAML::convert<T>::decode(it, tmp);
            out.push_back(tmp);
        }
        return true;
    }
};

template <>
struct convert<Str> {
    static Node encode(Str const& v) { return Node(v); }

    static bool decode(Node const& in, Str& out) {
        out = std::string::fromStdString(in.as<std::string>());
        return true;
    }
};


template <>
struct convert<json> {
    static Node encode(json const& v) { return Node(); }
    static bool decode(Node const& in, json& out) {
        out = toJson(in);
        return true;
    }
};

template <>
struct convert<Mark> {
    static Node encode(Mark const& v) { return Node(); }
    static bool decode(Node const& in, Mark& out) { return true; }
};


template <DescribedRecord T>
struct verbose_convert {

    using Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>;
    using Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>;

    static UnorderedMap<std::string, bool> knownFieldCache;

    static Node encode(T const& str) {
        Node in;
        mp_for_each<Md>([&](auto const& field) {
            in[field.name] = str.*field.pointer;
        });

        mp_for_each<Bd>([&](auto Base) {
            Node res = ::YAML::convert<
                typename decltype(Base)::type>::encode(str);
            for (auto const& item : res) {
                in[item.first.as<std::string>()] = item.second;
            }
        });

        return in;
    }

    static bool decode(Node const& in, T& out) {
        boost::mp11::mp_for_each<Md>([&](auto const& field) {
            if (!knownFieldCache.contains(field.name)) {
                knownFieldCache[field.name] = true;
            }

            Node val = in[field.name];
            if (val && !val.IsNull()) {
                ::YAML::convert<
                    std::remove_cvref_t<decltype(out.*field.pointer)>>::
                    decode(val, out.*field.pointer);
            }
        });

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            ::YAML::convert<typename decltype(Base)::type>::decode(
                in, out);
        });

        for (auto const& it : in) {
            std::string name = it.first.as<std::string>();
            if (!knownFieldCache.contains(name)) {
                // TODO 'did you mean' with corrections
                Vec<std::string> names;
                std::string      msg = "unexpected field name '" + name
                                + "', expected "
                                + join(" or ", knownFieldCache.keys())
                                      ;
                throw RepresentationException(it.first.Mark(), msg);
            }
        }

        return true;
    }
};

template <DescribedRecord T>
UnorderedMap<std::string, bool> verbose_convert<T>::knownFieldCache;

template <>
struct convert<ParseSpec::Dbg> : verbose_convert<ParseSpec::Dbg> {};

template <>
struct convert<ParseSpec::Conf> : verbose_convert<ParseSpec::Conf> {};

template <>
struct convert<ParseSpec::ExporterExpect>
    : verbose_convert<ParseSpec::ExporterExpect> {};

template <>
struct convert<ParseSpec> : verbose_convert<ParseSpec> {};

} // namespace YAML


QFileInfo ParseSpec::debugFile(std::string relativePath, bool create) const {
    if (debug.debugOutDir.isEmpty()) {
        throw FilesystemError(
            "Cannot get relative path for the spec configuration that "
            "does not provide debug output directory path");
    } else {
        auto dir = QDir(debug.debugOutDir);
        if (!dir.exists()) {
            if (!QDir().mkpath(dir.absolutePath())) {
                throw FilesystemError(
                    "Failed to create debugging directory for writing "
                    "test log"
                    + debug.debugOutDir);
            }
        }

        return QFileInfo(dir.filePath(relativePath));
    }
}

ParseSpec::ParseSpec(
    CR<yaml>    node,
    CR<std::string> specFile,
    CR<std::string> testRoot)
    : specFile(specFile) {
    specLocation = node.Mark();

    if (!node["source"] && !node["file"]) {
        throw SpecValidationError(
            "Input spec must contain 'source' string field or 'file'");
    } else if (node["file"]) {
        QDir    root{testRoot};
        std::string path = node["file"].as<std::string>();
        auto    full = QFileInfo{root.absoluteFilePath(path)};
        if (!QFileInfo{path}.isRelative()) {
            throw SpecValidationError(
                "'file' field must store a relative path, but '" + path
                + "' is not relative");
        }

        if (!full.exists()) {
            throw SpecValidationError(
                "'file' field must store a relative path, but '$#' does "
                "not exist (test root '$#')"
                % to_string_vec(full.absoluteFilePath(), testRoot));
        }

        this->source = readFile(full);
    }

    ::YAML::convert<ParseSpec>::decode(node, *this);
}

ParseSpecGroup::ParseSpecGroup(
    CR<yaml>    node,
    CR<std::string> from,
    CR<std::string> testRoot) {
    auto validate = [&](CR<ParseSpec> spec) {
        if (spec.parseImplName.empty() || spec.lexImplName.empty()) {
            throw ParseSpec::SpecValidationError(
                "$# function name missing from specifiction "
                "-- must be provided as `$#` in either "
                "specific parser test case on toplevel of the "
                "test file or in specific test in $#"
                % to_string_vec(
                    spec.parseImplName.empty() ? "Parser" : "Lexer",
                    spec.parseImplName.empty() ? "lex" : "parse",
                    from));
        }
    };
    if (node["items"]) {
        if (node["items"].IsSequence()) {
            for (const auto& it : node["items"]) {
                auto spec = ParseSpec(it, from, testRoot);

                if (spec.lexImplName.empty() && node["lex"]) {
                    spec.lexImplName = node["lex"].as<std::string>();
                }

                if (spec.parseImplName.empty() && node["parse"]) {
                    spec.parseImplName = node["parse"].as<std::string>();
                }

                validate(spec);

                if (!spec.name) {
                    if (node["name"]) {
                        spec.name = node["name"].as<std::string>();
                    }
                }

                if (!it["expected"] && node["expected"]) {
                    spec.expectedMode =
                        //
                        enum_serde<ParseSpec::ExpectedMode>::from_string(
                            node["expected"].as<std::string>())
                            .value_or(ParseSpec::ExpectedMode::Nested);
                }

                specs.push_back(spec);
            }
        } else {
            throw ParseSpec::SpecValidationError(
                "Spec group 'items' field must be a sequence");
        }

    } else {
        auto tmp = ParseSpec(node, from, testRoot);
        validate(tmp);
        specs.push_back(tmp);
    }
}
