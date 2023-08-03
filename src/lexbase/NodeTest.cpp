#include <lexbase/NodeTest.hpp>
#include <QString>
#include <QDir>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/system/reflection.hpp>
#include <boost/mp11.hpp>

namespace YAML {
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
                std::string msg = "unexpected field name '" + name + "'";
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


} // namespace YAML


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
            QString scalar = QString::fromStdString(node.Scalar());
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

QFileInfo ParseSpec::debugFile(QString relativePath, bool create) const {
    if (dbg.debugOutDir.isEmpty()) {
        throw FilesystemError(
            "Cannot get relative path for the spec configuration that "
            "does not provide debug output directory path");
    } else {
        auto dir = QDir(dbg.debugOutDir);
        if (!dir.exists()) {
            if (!QDir().mkpath(dir.absolutePath())) {
                throw FilesystemError(
                    "Failed to create debugging directory for writing "
                    "test log"
                    + dbg.debugOutDir);
            }
        }

        return QFileInfo(dir.filePath(relativePath));
    }
}

ParseSpec::ParseSpec(CR<yaml> node, CR<QString> specFile)
    : specFile(specFile) {
    specLocation = node.Mark();

    if (node["conf"]) {
        auto c = node["conf"];
        maybe_field<Conf::MatchMode>(
            c, conf.tokenMatchMode, "token_match");
        maybe_field<Conf::MatchMode>(c, conf.nodeMatchMode, "node_match");
    }

    if (node["debug"]) {
        ::YAML::convert<Dbg>::decode(node["debug"], dbg);
    }

    maybe_field<QString>(node, lexImplName, "lex");
    maybe_field<Opt<QString>>(node, testName, "name");
    maybe_field<QString>(node, parseImplName, "parse");

    if (node["source"]) {
        sourceLocation = node["source"].Mark();
        source         = node["source"].as<QString>();
    } else {
        throw SpecValidationError(
            "Input spec must contain 'source' string field");
    }

    if (node["subnodes"]) {
        subnodes = node["subnodes"];
    }

    if (node["tokens"]) {
        tokens = node["tokens"];
    }

    if (node["sem"]) {
        semExpected = toJson(node["sem"]);
    }

    if (node["export"]) {
        for (auto const& exp : node["export"]) {
            ExporterExpect res;
            maybe_field<Opt<yaml>>(exp, res.parmeters, "parameters");
            maybe_field<QString>(exp, res.exporterName, "name");
            maybe_field<yaml>(exp, res.expected, "expected");
            maybe_field<bool>(exp, res.traceExport, "do_trace");
            exporterExpect.push_back(res);
        }
    }

    maybe_field<ExpectedMode>(node, expectedMode, "expected");
}

ParseSpecGroup::ParseSpecGroup(CR<yaml> node, CR<QString> from) {
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
                auto spec = ParseSpec(it, from);

                if (spec.lexImplName.empty() && node["lex"]) {
                    spec.lexImplName = node["lex"].as<QString>();
                }

                if (spec.parseImplName.empty() && node["parse"]) {
                    spec.parseImplName = node["parse"].as<QString>();
                }

                validate(spec);

                if (!spec.testName) {
                    if (node["name"]) {
                        spec.testName = node["name"].as<QString>();
                    } else {
                    }
                }

                if (!it["expected"] && node["expected"]) {
                    spec.expectedMode =
                        //
                        enum_serde<ParseSpec::ExpectedMode>::from_string(
                            node["expected"].as<QString>())
                            .value_or(ParseSpec::ExpectedMode::Nested);
                }

                specs.push_back(spec);
            }
        } else {
            throw ParseSpec::SpecValidationError(
                "Spec group 'items' field must be a sequence");
        }

    } else {
        auto tmp = ParseSpec(node, from);
        validate(tmp);
        specs.push_back(tmp);
    }
}
