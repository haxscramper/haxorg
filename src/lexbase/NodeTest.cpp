#include <lexbase/NodeTest.hpp>
#include <QString>

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

ParseSpec::ParseSpec(CR<yaml> node) {
    specLocation = node.Mark();

    if (node["conf"]) {
        auto c = node["conf"];
        maybe_field<Conf::MatchMode>(
            c, conf.tokenMatchMode, "token_match");
        maybe_field<Conf::MatchMode>(c, conf.nodeMatchMode, "node_match");
    }

    if (node["debug"]) {
        auto debug = node["debug"];
        maybe_field<bool>(debug, dbg.traceLex, "trace_lex");
        maybe_field<bool>(debug, dbg.doParse, "do_lex");
        maybe_field<bool>(debug, dbg.doParse, "do_parse");
        maybe_field<bool>(debug, dbg.doSem, "do_sem");
        maybe_field<bool>(debug, dbg.traceParse, "trace_parse");
        maybe_field<bool>(debug, dbg.lexToFile, "lex_to_file");
        maybe_field<bool>(debug, dbg.parseToFile, "parse_to_file");
        maybe_field<bool>(debug, dbg.printLexed, "print_lexed");
        maybe_field<bool>(debug, dbg.printParsed, "print_parsed");
        maybe_field<bool>(debug, dbg.printSemToFile, "sem_to_file");
        maybe_field<bool>(
            debug, dbg.printLexedToFile, "print_lexed_to_file");
        maybe_field<bool>(
            debug, dbg.printParsedToFile, "print_parsed_to_file");
        maybe_field<bool>(debug, dbg.printSource, "print_source");
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
                auto spec = ParseSpec(it);

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
                        string_to_enum<ParseSpec::ExpectedMode>(
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
        auto tmp = ParseSpec(node);
        validate(tmp);
        specs.push_back(tmp);
    }
}
