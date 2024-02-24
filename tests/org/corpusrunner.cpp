#include "corpusrunner.hpp"

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <exporters/ExporterJson.hpp>
#include <exporters/exportertree.hpp>
#include <exporters/exportersimplesexpr.hpp>
#include <exporters/exporteryaml.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/diffs.hpp>
#include <fstream>
#include <cstdlib>
#include <gtest/gtest.h>
#include <sem/perfetto_org.hpp>
#include <sem/SemOrgFormat.hpp>

#ifdef ORG_USE_PERFETTO
#    pragma clang diagnostic ignored "-Wmacro-redefined"
#    define __perf_trace(name) TRACE_EVENT("cli", name)
#else
#    define __perf_trace(...)
#endif


struct DiffItem {
    DECL_DESCRIBED_ENUM(Op, Replace, Remove, Add);
    Op          op;
    std::string path;
    json        value;
};


Vec<DiffItem> json_diff(
    const json&          source,
    const json&          target,
    const std::string&   path   = "",
    Func<bool(CR<json>)> ignore = [](CR<json>) -> bool { return false; }) {

    // the patch
    Vec<DiffItem> result;

    if (ignore(target)) { return result; }

    // if the values are the same, return empty patch
    if (source == target) { return result; }

    if (source.type() != target.type()) {
        // different types: replace value
        result.push_back({DiffItem::Op::Replace, path, target});
        return result;
    }

    switch (source.type()) {
        case json::value_t::array: {
            // first pass: traverse common elements
            std::size_t i = 0;
            while (i < source.size() && i < target.size()) {
                // recursive call to compare array values at index i
                auto temp_diff = json_diff(
                    source[i],
                    target[i],
                    nlohmann::detail::concat(
                        path, '/', std::to_string(i)));
                result.insert(
                    result.end(), temp_diff.begin(), temp_diff.end());
                ++i;
            }

            // We now reached the end of at least one array
            // in a second pass, traverse the remaining elements

            // remove my remaining elements
            const auto end_index = static_cast<json::difference_type>(
                result.size());
            while (i < source.size()) {
                // add operations in reverse order to avoid invalid
                // indices
                result.insert(
                    result.begin() + end_index,
                    {DiffItem::Op::Remove,
                     nlohmann::detail::concat(
                         path, '/', std::to_string(i))});

                ++i;
            }

            // add other remaining elements
            while (i < target.size()) {
                result.push_back(
                    {DiffItem::Op::Add,
                     nlohmann::detail::concat(path, "/-"),
                     target[i]});
                ++i;
            }

            break;
        }

        case json::value_t::object: {
            // first pass: traverse this object's elements
            for (auto it = source.cbegin(); it != source.cend(); ++it) {
                // escape the key name to be used in a JSON patch
                const auto path_key = nlohmann::detail::concat(
                    path, '/', nlohmann::detail::escape(it.key()));

                if (target.find(it.key()) != target.end()) {
                    // recursive call to compare object values at key it
                    auto temp_diff = json_diff(
                        it.value(), target[it.key()], path_key);
                    result.insert(
                        result.end(), temp_diff.begin(), temp_diff.end());
                } else {
                    // found a key that is not in o -> remove it
                    result.push_back({DiffItem::Op::Remove, path_key});
                }
            }

            // second pass: traverse other object's elements
            for (auto it = target.cbegin(); it != target.cend(); ++it) {
                if (source.find(it.key()) == source.end()) {
                    // found a key that is not in this -> add it
                    const auto path_key = nlohmann::detail::concat(
                        path, '/', nlohmann::detail::escape(it.key()));
                    result.push_back(
                        {DiffItem::Op::Add, path_key, it.value()});
                }
            }

            break;
        }

        case json::value_t::null:
        case json::value_t::string:
        case json::value_t::boolean:
        case json::value_t::number_integer:
        case json::value_t::number_unsigned:
        case json::value_t::number_float:
        case json::value_t::binary:
        case json::value_t::discarded:
        default: {
            // both primitive type: replace value
            result.push_back({DiffItem::Op::Replace, path, target});
            break;
        }
    }

    return result;
}


void CorpusRunner::writeFileOrStdout(
    const fs::path&    target,
    const std::string& content,
    bool               useFile) {
    if (useFile) {
        writeFile(target, content);

    } else {
        std::cout << content;
    }
}

void format(
    ColStream&               os,
    CR<FormattedDiff>        text,
    Func<ColText(int, bool)> formatCb,
    int                      lhsSize          = 48,
    int                      rhsSize          = 16,
    bool                     dropLeadingKeep  = false,
    bool                     dropTrailingKeep = false) {
    if (text.isUnified()) {
        os << (ColText("Given") <<= lhsSize) << (ColText("Expected"))
           << "\n";
        Vec<Pair<FormattedDiff::DiffLine, FormattedDiff::DiffLine>> lines;
        for (auto const& pair : text.unifiedLines()) {
            lines.push_back(pair);
        }

        if (lines.empty()) { return; }

        Slice<int> range = slice(0, lines.size() - 1);
        if (dropLeadingKeep) {
            for (int i = 0; i <= range.last; ++i) {
                if (lines[i].first.prefix == SeqEditKind::Keep
                    && lines[i].second.prefix == SeqEditKind::Keep) {
                    range.first = i;
                } else {
                    // two lines of context before diff
                    range.first = std::max(0, i - 1);
                    break;
                }
            }
        }

        if (dropTrailingKeep) {
            for (int i = range.last; range.first < i; --i) {
                if (lines[i].first.prefix == SeqEditKind::Keep
                    && lines[i].second.prefix == SeqEditKind::Keep) {
                    range.last = i;
                } else {
                    range.last = std::min(lines.high(), i + 1);
                    break;
                }
            }
        }

        for (const auto& i : range) {
            auto const& lhs = lines[i].first;
            auto const& rhs = lines[i].second;

            auto lhsStyle = toStyle(lhs.prefix);
            auto rhsStyle = toStyle(rhs.prefix);

            os << (ColText(lhsStyle, toPrefix(lhs.prefix)) <<= 2)
               << ((lhs.empty() ? ColText("")
                                : formatCb(lhs.index().value(), true)
                                      .withStyle(lhsStyle))
                   <<= lhsSize)
               << (ColText(rhsStyle, toPrefix(rhs.prefix)) <<= 2)
               << ((rhs.empty() ? ColText("")
                                : formatCb(rhs.index().value(), false)
                                      .withStyle(rhsStyle))
                   <<= rhsSize)
               << "\n";
        }
    }
}


void describeDiff(
    ColStream&      os,
    DiffItem const& it,
    json const&     expected,
    json const&     converted) {
    json::json_pointer path{it.path};

    os << "  ";
    switch (it.op) {
        case DiffItem::Op::Remove: {
            os << os.red() << "converted has extra entry";
            break;
        }
        case DiffItem::Op::Add: {
            os << os.green() << "export missing entry";
            break;
        }
        case DiffItem::Op::Replace: {
            os << os.magenta() << "changed entry";
            break;
        }
    }

    os << " on path '" << os.yellow() << path.to_string() << os.end()
       << "' ";

    switch (it.op) {
        case DiffItem::Op::Remove: {
            os << "    " << os.red() << converted[path].dump() << os.end();
            break;
        }
        case DiffItem::Op::Add: {
            os << "    " << it.value.dump();
            break;
        }
        case DiffItem::Op::Replace: {
            json const& exp  = expected[path];
            json const& conv = converted[path];
            std::string from = exp.dump();
            std::string to   = conv.dump();

            if (exp.type() != conv.type()) {
                os << "type mismatch: " << exp.type_name()
                   << " != " << conv.type_name() << " ";
            }

            if (40 < from.size() || 40 < to.size()) {
                os << "\n";
                os << "    from " << os.red()
                   << to_compact_json(
                          exp, {.width = 120, .startIndent = 10})
                   << os.end() << "\n";
                os << "    to   " << os.red()
                   << to_compact_json(
                          conv, {.width = 120, .startIndent = 10})
                   << os.end();
            } else {
                os << "    from " << os.red() << from << os.end() << " to "
                   << os.green() << to << os.end();
            }


            break;
        }
    }
}

bool isSimple(json const& j) {
    switch (j.type()) {
        case json::value_t::number_float:
        case json::value_t::number_integer:
        case json::value_t::boolean:
        case json::value_t::null:
        case json::value_t::string: return true;
        default: return false;
    }
};

bool isEmpty(json const& j) { return (j.is_array() && j.empty()); }

void writeSimple(ColStream& os, json const& j) {
    switch (j.type()) {
        case json::value_t::number_float: {
            os << os.magenta() << j.get<float>() << os.end();
            break;
        }
        case json::value_t::number_integer: {
            os << os.blue() << j.get<int>() << os.end();
            break;
        }
        case json::value_t::boolean: {
            os << os.cyan() << j.get<bool>() << os.end();
            break;
        }
        case json::value_t::string: {
            os << os.yellow() << escape_literal(j.get<std::string>())
               << os.end();
            break;
        }
        case json::value_t::null: {
            os << os.cyan() << "null" << os.end();
            break;
        }
        default: {
        }
    }
};


json CorpusRunner::toTextLyt(
    layout::BlockStore&       b,
    layout::BlockId           block,
    Func<Str(layout::LytStr)> getStr) {
    using B = layout::Block;

    auto getSubnodes = [&](CVec<layout::BlockId> elements) {
        json res = json::array();
        for (auto const& e : elements) {
            res.push_back(toTextLyt(b, e, getStr));
        }
        return res;
    };

    return std::visit(
        overloaded{
            [&](B::Empty const&) -> json {
                return {{"kind", "empty"}};
            },
            [&](B::Line const& l) -> json {
                return {
                    {"kind", "line"},
                    {"subnodes", getSubnodes(l.elements)}};
            },
            [&](B::Stack const& l) -> json {
                return {
                    {"kind", "block"},
                    {"subnodes", getSubnodes(l.elements)}};
            },
            [&](B::Choice const& l) -> json {
                return {
                    {"kind", "choice"},
                    {"subnodes", getSubnodes(l.elements)}};
            },
            [&](B::Verb const& l) -> json {
                json arr = json::array();
                for (auto const& i : l.textLines) {
                    json line = json::array();
                    for (auto const& it : i.strs) {
                        line.push_back(getStr(it));
                    }
                    arr.push_back(line);
                }

                return {
                    {"kind", "verb"}, {"fistNl", "bool"}, {"lines", arr}};
            },
            [&](B::Text const& l) -> json {
                json arr = json::array();
                for (auto const& i : l.text.strs) {
                    arr.push_back(getStr(i));
                }
                return {{"kind", "text"}, {"tokens", arr}};
            },
            [&](B::Wrap const& text) -> json {
                return {
                    {"kind", "wrap"},
                    {"sep", getStr(text.sep)},
                    {"prefix",
                     text.prefix ? json(getStr(text.prefix.value()))
                                 : json()},
                    {"subnodes", getSubnodes(text.wrapElements)}};
            },
        },
        b.at(block).data);
}


template <typename E>
void exporterVisit(
    OperationsTracer&             trace,
    typename E::VisitEvent const& ev) {

    using K = typename E::VisitEvent::Kind;
    if (((ev.kind == K::PushVisit || ev.kind == K::VisitStart)
         && !ev.isStart)
        || ((ev.kind == K::PopVisit || ev.kind == K::VisitEnd)
            && ev.isStart)) {
        return;
    }

    auto os = trace.getStream();


    os << os.indent(ev.level * 2) << (ev.isStart ? ">" : "<") << " "
       << fmt1(ev.kind);

    if (ev.visitedNode) {
        os << " node:" << fmt1((*ev.visitedNode)->getKind());
    }

    if (0 < ev.field.length()) { os << " field:" << ev.field; }

    os << " on " << fs::path(ev.file).stem() << ":" << ev.line << " "
       << ev.function << " " << os.end();

    if (0 < ev.type.length()) {
        os << " type:" << demangle(ev.type.c_str());
    }

    trace.endStream(os);
}

CorpusRunner::ExportResult CorpusRunner::runExporter(
    ParseSpec const&                 spec,
    sem::SemId<sem::Org>             top,
    const ParseSpec::ExporterExpect& exp) {
    using ER = ExportResult;

    auto strForStore = [](layout::SimpleStringStore const& store)
        -> Func<Str(layout::LytStr)> {
        return [&](layout::LytStr str) { return store.str(str); };
    };

    auto withTreeExporter =
        [this, &strForStore](
            sem::SemId<sem::Org> top, layout::BlockStore& b, auto& run) {
            auto block = run.evalTop(top);
            return ER(ER::Text{
                .textLyt = toTextLyt(b, block, strForStore(run.store))});
        };

    if (exp.name == "json") {
        return ER(ER::Structured{.data = ExporterJson().evalTop(top)});
    } else if (exp.name == "sexp") {
        ExporterSimpleSExpr run;
        return withTreeExporter(top, run.b, run);

    } else {
        throw std::domain_error(
            "Unexpected export result name " + exp.name);
    }
}


template <typename K, typename V>
CorpusRunner::RunResult::LexCompare compareTokens(
    CR<TokenGroup<K, V>>       lexed,
    CR<TokenGroup<K, V>>       expected,
    ParseSpec::Conf::MatchMode match,
    auto                       token_eq,
    auto                       get_token_text) {

    using Tok                    = Token<K, V>;
    using Mode                   = ParseSpec::Conf::MatchMode;
    BacktrackRes tokenSimilarity = longestCommonSubsequence<Tok>(
        lexed.tokens.content, expected.tokens.content, token_eq)[0];

    if ((match == Mode::Full
         && tokenSimilarity.lhsIndex.size() == lexed.size()
         && tokenSimilarity.rhsIndex.size() == expected.size())
        || (match == Mode::ExpectedSubset
            && tokenSimilarity.rhsIndex.size() == expected.size())) {
        return {{.isOk = true}};
    } else {
        ShiftedDiff tokenDiff{
            tokenSimilarity, lexed.size(), expected.size()};

        Func<Str(CR<Tok>)> conv = [](CR<Tok> tok) -> Str {
            return std::format("{}", tok);
        };

        FormattedDiff text{tokenDiff};

        ColStream os;
        int       lhsSize = 48;
        int       rhsSize = 30;

        format(
            os,
            text,
            [&](int id, bool isLhs) -> ColText {
                auto tok = isLhs ? lexed.tokens.content.at(id)
                                 : expected.tokens.content.at(id);

                HDisplayOpts opts{};
                opts.flags.excl(HDisplayFlag::UseQuotes);

                std::string text = escape_literal(
                    hshow(get_token_text(tok), opts).toString(false));

                std::string result = //
                    "${index} ${kind} ${text}"
                    % fold_format_pairs({
                        {"index", fmt1(id)},
                        {"kind", fmt1(tok.kind)},
                        {"text", text},
                        {"size", fmt1(rune_length(text))},
                    });

                auto indexFmt = Str(std::format("[{}]", id));
                return result;
            },
            lhsSize,
            rhsSize,
            false,
            false);

        return {{.isOk = false, .failDescribe = os.getBuffer()}};
    }
}

CorpusRunner::RunResult::NodeCompare CorpusRunner::compareNodes(
    CR<OrgNodeGroup> parsed,
    CR<OrgNodeGroup> expected) {
    BacktrackRes nodeSimilarity;
    auto         paths = longestCommonSubsequence<OrgNode>(
        parsed.nodes.content,
        expected.nodes.content,
        [](CR<OrgNode> lhs, CR<OrgNode> rhs) -> bool {
            if (lhs.kind != rhs.kind) {
                return false;
            } else {
                if (lhs.isTerminal()) {
                    return lhs.getToken() == rhs.getToken();
                } else {
                    return lhs.getExtent() == rhs.getExtent();
                }
            }
        });

    if (!paths.empty()) { nodeSimilarity = paths[0]; }

    ShiftedDiff nodeDiff{nodeSimilarity, parsed.size(), expected.size()};


    if (nodeSimilarity.lhsIndex.size() == parsed.size()
        && nodeSimilarity.rhsIndex.size() == expected.size()) {
        return {{.isOk = true}};
    } else {
        ShiftedDiff nodeDiff{
            nodeSimilarity, parsed.size(), expected.size()};

        Func<Str(CR<OrgNode>)> conv = [](CR<OrgNode> tok) -> Str {
            return std::format("{}", tok);
        };

        FormattedDiff text{nodeDiff};
        ColStream     os;
        format(
            os,
            text,
            [&](int id, bool isLhs) -> ColText {
                auto node = isLhs ? parsed.nodes.content.at(id)
                                  : expected.nodes.content.at(id);

                auto group = isLhs ? &parsed : &expected;

                return "$# $# $#($# $#)"
                     % to_string_vec(
                           id,
                           node.kind,
                           node.isTerminal() ? escape_literal(
                               hshow(
                                   group->tokens->tokens.content
                                       .get_copy(
                                           node.getToken().getIndex())
                                       .value_or(OrgToken{})
                                       ->text,
                                   HDisplayOpts().excl(
                                       HDisplayFlag::UseQuotes))
                                   .toString(false))
                                             : std::string(""),
                           node.kind,
                           node.isTerminal()
                               ? "tok=" + fmt1(node.getToken().getIndex())
                               : "ext=" + fmt1(node.getExtent()));
            },
            48,
            16,
            false,
            false);

        return {{.isOk = false, .failDescribe = os.getBuffer()}};
    }
}

void filterFields(
    json&                           j,
    const std::vector<std::string>& fieldsToRemove) {
    if (j.is_object()) {
        for (auto it = j.begin(); it != j.end();) {
            if (std::find(
                    fieldsToRemove.begin(), fieldsToRemove.end(), it.key())
                != fieldsToRemove.end()) {
                it = j.erase(it);
            } else {
                filterFields(*it, fieldsToRemove);
                ++it;
            }
        }
    } else if (j.is_array()) {
        for (json& el : j) { filterFields(el, fieldsToRemove); }
    }
}

yaml toTestYaml(sem::OrgArg arg) {
    ExporterYaml exporter;
    exporter.skipNullFields  = true;
    exporter.skipFalseFields = true;
    exporter.skipZeroFields  = true;
    exporter.skipLocation    = true;
    exporter.skipId          = true;
    return exporter.evalTop(arg);
}

json toTestJson(sem::OrgArg arg) {
    ExporterJson exporter;
    json         converted = exporter.evalTop(arg);
    filterFields(converted, {"loc"});
    return converted;
}

CorpusRunner::RunResult::SemCompare CorpusRunner::compareSem(
    CR<ParseSpec>        spec,
    sem::SemId<sem::Org> node,
    json                 expected) {

    json          converted = toTestJson(node);
    Vec<DiffItem> diff      = json_diff(converted, expected);
    int           failCount = 0;
    ColStream     os;
    UnorderedMap<std::string, DiffItem> ops;


    for (auto const& it : diff) {
        json::json_pointer path{it.path};
        if (!path.empty() && it.op == DiffItem::Op::Remove) {
            continue;
        } else {
            ++failCount;
        }

        ops[it.path] = it;
        describeDiff(os, it, expected, converted);
        os << "\n";
    }

    auto maybePathDiff = [&](json::json_pointer const& path) {
        if (ops.contains(path.to_string())) {
            describeDiff(os, ops[path.to_string()], expected, converted);
        }
    };

    if (0 < failCount) {
        yaml converted_yaml  = toYaml(converted);
        yaml expected_yaml   = toYaml(expected);
        auto converted_lines = Str(fmt1(converted_yaml)).split('\n');
        auto expected_lines  = Str(fmt1(expected_yaml)).split('\n');

        BacktrackRes sem_lcs = longestCommonSubsequence<Str>(
            converted_lines,
            expected_lines,
            [](CR<Str> lhs, CR<Str> rhs) -> bool {
                return lhs == rhs;
            })[0];

        ShiftedDiff sem_diff{
            sem_lcs, converted_lines.size(), expected_lines.size()};
        FormattedDiff text{sem_diff};

        format(
            os,
            text,
            [&](int id, bool isLhs) -> ColText {
                auto node = isLhs ? converted_lines.at(id)
                                  : expected_lines.at(id);
                return ColText{node};
            },
            rs::max(converted_lines | rv::transform([](CR<Str> s) {
                        return s.size();
                    }))
                + 8,
            rs::max(expected_lines | rv::transform([](CR<Str> s) {
                        return s.size();
                    }))
                + 8);


        return {{.isOk = false, .failDescribe = os.getBuffer()}};
    } else {
        return {{.isOk = true}};
    }
}


CorpusRunner::RunResult CorpusRunner::runSpec(
    CR<ParseSpec>   spec,
    CR<std::string> from) {
    __perf_trace("run spec");
    MockFull p(spec.debug.traceParse, spec.debug.traceLex);

    if (spec.debug.traceAll || spec.debug.printSource) {
        writeFile(spec.debugFile("source.org"), spec.source);
    }

    auto skip = RunResult{RunResult::Skip{}};

    if (!spec.debug.doLexBase) { return skip; }
    auto base_lex_result = runSpecBaseLex(p, spec);
    if (!base_lex_result.isOk) { return RunResult{base_lex_result}; }

    if (!spec.debug.doLex) { return skip; }
    auto lex_result = runSpecLex(p, spec);
    if (!lex_result.isOk) { return RunResult{lex_result}; }

    if (!spec.debug.doParse) { return skip; }
    auto parse_result = runSpecParse(p, spec);
    if (!parse_result.isOk) { return RunResult{parse_result}; }

    if (!spec.debug.doSem) { return skip; }
    auto sem_result = runSpecSem(p, spec);
    if (!parse_result.isOk) { return RunResult{sem_result}; }

    if (!spec.debug.doFormatReparse) { return skip; }

    ParseSpec      rerun = spec;
    MockFull       p2(spec.debug.traceParse, spec.debug.traceLex);
    sem::Formatter formatter;
    auto           fmt_result = formatter.toString(p.node);
    rerun.source              = formatter.store.toString(fmt_result);
    rerun.base_tokens         = std::nullopt;
    rerun.subnodes            = std::nullopt;
    rerun.tokens              = std::nullopt;
    rerun.sem                 = toTestJson(p.node);
    rerun.source.resize(rerun.source.size() - 1);
    rerun.debug.debugOutDir.append("_reformat");

    if (spec.debug.traceAll || spec.debug.printSource) {
        writeFile(
            rerun.debugFile("org2_format_tree.org"),
            formatter.store.toTreeRepr(fmt_result));
        writeFile(rerun.debugFile("org2_format.org"), rerun.source);
        writeFile(rerun.debugFile("org2_source.org"), spec.source);

        auto read = [](char c) { return visibleName(c).first; };

        writeFile(
            rerun.debugFile("org2_format_array.org"),
            fmt1(
                rerun.source | rv::transform(read)
                | rs::to<std::vector>()));
        writeFile(
            rerun.debugFile("org2_source_array.org"),
            fmt1(
                spec.source | rv::transform(read)
                | rs::to<std::vector>()));
    }

    runSpecBaseLex(p2, rerun);
    runSpecLex(p2, rerun);
    runSpecParse(p2, rerun);
    auto reformat_result = runSpecSem(p2, rerun);
    if (!reformat_result.isOk) {
        writeFile(
            rerun.debugFile("sem2_expected.yaml"),
            fmt1(toTestYaml(p.node)));
        writeFile(
            rerun.debugFile("sem2_parsed.yaml"),
            fmt1(toTestYaml(p2.node)));

        writeFile(
            rerun.debugFile("sem2_reformat_fail.txt"),
            reformat_result.failDescribe.toString(false));

        return RunResult{reformat_result};
    }

    return RunResult();
}

CorpusRunner::RunResult::LexCompare CorpusRunner::runSpecBaseLex(
    MockFull&     p,
    CR<ParseSpec> spec) {
    __perf_trace("lex base");

    SPtr<std::ofstream> fileTrace;
    if (spec.debug.traceAll || spec.debug.traceLexBase) {
        fileTrace = std::make_shared<std::ofstream>(
            spec.debugFile("trace_lex_base.log"));
    }

    LexerParams params;
    params.maxUnknown  = spec.debug.maxBaseLexUnknownCount;
    params.traceStream = fileTrace.get();
    __perf_trace("tokenize base");
    p.tokenizeBase(spec.source, params);

    if (spec.debug.traceAll || spec.debug.printBaseLexed
        || spec.debug.printBaseLexedToFile) {
        auto content = std::format("{}", yamlRepr(p.baseTokens));

        if (spec.debug.traceAll || spec.debug.printBaseLexedToFile) {
            writeFile(spec.debugFile("base_lexed.yaml"), content + "\n");
        } else {
            std::cout << content << std::endl;
        }
    }

    if (spec.base_tokens.has_value()) {
        Str                   buffer;
        RunResult::LexCompare result = compareTokens(
            p.baseTokens,
            fromFlatTokens<OrgTokenKind, OrgFill>(
                spec.base_tokens.value(), buffer),
            spec.conf.tokenMatch,
            [](CR<OrgToken> lhs, CR<OrgToken> rhs) -> bool {
                if (lhs.kind != rhs.kind) {
                    return false;
                } else if (lhs.value.text != rhs.value.text) {
                    return false;
                } else {
                    return true;
                }
            },
            [](CR<OrgToken> tok) { return tok.value.text; });

        return result;
    } else {
        return CorpusRunner::RunResult::LexCompare{{.isOk = true}};
    }
}

CorpusRunner::RunResult::LexCompare CorpusRunner::runSpecLex(
    MockFull&     p,
    CR<ParseSpec> spec) {
    __perf_trace("lex");

    p.tokenizer->TraceState = spec.debug.traceAll || spec.debug.traceLex;
    p.tokenizer->setTraceFile(spec.debugFile("trace_lex.log"));

    __perf_trace("tokenize convert");
    p.tokenizeConvert();

    if (spec.debug.traceAll || spec.debug.printLexed
        || spec.debug.printLexedToFile) {
        auto content = std::format("{}", yamlRepr(p.tokens));

        __perf_trace("write lexer yaml file");
        if (spec.debug.traceAll || spec.debug.printLexedToFile) {
            writeFile(spec.debugFile("lexed.yaml"), content + "\n");
        } else {
            std::cout << content << std::endl;
        }
    }

    if (spec.tokens.has_value()) {
        Str                   buffer;
        RunResult::LexCompare result = compareTokens(
            p.tokens,
            fromFlatTokens<OrgTokenKind, OrgFill>(
                spec.tokens.value(), buffer),
            spec.conf.tokenMatch,
            [](CR<OrgToken> lhs, CR<OrgToken> rhs) -> bool {
                if (lhs.kind != rhs.kind) {
                    return false;
                } else if (
                    // Not 100% 'equal', but ATTW I want to save on
                    // debugging why 'given' in tests sometimes has a
                    // non-empty base and sometimes it is a true
                    // nullopt_t value.
                    lhs->text != rhs->text) {
                    return false;
                } else {
                    return true;
                }
            },
            [](CR<OrgToken> tok) { return tok->text; });

        return result;
    } else {
        return RunResult::LexCompare{{.isOk = true}};
    }
}

CorpusRunner::RunResult::NodeCompare CorpusRunner::runSpecParse(
    MockFull&     p,
    CR<ParseSpec> spec) {

    __perf_trace("parse");
    using Pos = OrgNodeGroup::TreeReprConf::WritePos;
    UnorderedMap<OrgId, int> parseAddedOnLine;

    auto writeImpl =
        [&](OrgNodeGroup::TreeReprConf::WriteParams const& par) {
            switch (par.pos) {
                case Pos::AfterKind: {
                    if (par.parent && par.subnodeIdx) {
                        auto name = p.spec->fieldName(
                            OrgAdapter(&p.nodes, *par.parent),
                            *par.subnodeIdx);
                        if (name) {
                            par.os << " " << par.os.magenta()
                                   << fmt("{}", *name) << par.os.end();
                        } else {
                            par.os << " " << par.os.red()
                                   << fmt("!! Missing field name for "
                                          "element {} of node "
                                          "{} !!",
                                          *par.subnodeIdx,
                                          OrgAdapter(&p.nodes, *par.parent)
                                              .getKind())
                                   << par.os.end() << " ";
                        }
                    }
                    break;
                }
                case Pos::LineEnd: {
                    if (parseAddedOnLine.contains(par.current)) {
                        par.os << " " << par.os.red()
                               << fmt(" @{}",
                                      parseAddedOnLine.at(par.current))
                               << par.os.end();
                    }
                    break;
                }
                default:
            }
        };


    p.parser->TraceState = spec.debug.traceAll || spec.debug.traceParse;
    p.parser->setTraceFile(spec.debugFile("trace_parse.log"));

    p.parser->reportHook = [&](CR<OrgParser::Report> rep) {
        if (rep.kind == OrgParser::ReportKind::AddToken
            || rep.kind == OrgParser::ReportKind::StartNode) {
            parseAddedOnLine.insert_or_assign(*rep.node, rep.line);
        }
    };

    (void)p.parser->parseTop(p.lex);

    if (spec.debug.traceAll || spec.debug.printParsed
        || spec.debug.printParsedToFile) {
        writeFile(
            spec.debugFile("parsed_non_extended.yaml"),
            std::format("{}", yamlRepr(p.nodes)) + "\n");
    }

    p.parser->extendSubtreeTrails(OrgId(0));

    if (spec.debug.traceAll || spec.debug.printParsed
        || spec.debug.printParsedToFile) {
        writeFile(
            spec.debugFile("parsed.yaml"),
            std::format("{}", yamlRepr(p.nodes)) + "\n");

        for (auto const& [colored, path] : Vec<Pair<bool, Str>>{
                 {false, "parsed.txt"}, {true, "parsed_colored.ansi"}}) {
            std::stringstream buffer;
            ColStream         text{buffer};
            text.colored = colored;

            OrgAdapter(&p.nodes, OrgId(0))
                .treeRepr(
                    text,
                    0,
                    OrgNodeGroup::TreeReprConf{.customWrite = writeImpl});

            writeFile(spec.debugFile(path), buffer.str() + "\n");
        }
    }


    if (spec.subnodes.has_value()) {
        Str           buffer;
        OrgNodeGroup  nodes;
        OrgTokenGroup tokens;

        if (spec.tokens.has_value()) {
            tokens = fromFlatTokens<OrgTokenKind, OrgFill>(
                spec.tokens.value(), buffer);
        }

        if (spec.subnodes.has_value()) {
            nodes = fromFlatNodes<OrgNodeKind, OrgTokenKind, OrgFill>(
                spec.subnodes.value());
        }

        nodes.tokens = &tokens;

        return compareNodes(p.nodes, nodes);
    } else {
        return RunResult::NodeCompare{{.isOk = true}};
    }
}

CorpusRunner::RunResult::SemCompare CorpusRunner::runSpecSem(
    MockFull&     p,
    CR<ParseSpec> spec) {
    __perf_trace("sem convert");
    sem::OrgConverter converter{};

    converter.TraceState = spec.debug.traceAll || spec.debug.traceSem;
    converter.setTraceFile(spec.debugFile("trace_sem.log"));

    auto document = converter.toDocument(OrgAdapter(&p.nodes, OrgId(0)));
    p.node        = document.asOrg();

    if (spec.debug.traceAll || spec.debug.printSem
        || spec.debug.printSemToFile) {

        writeFileOrStdout(
            spec.debugFile("sem.yaml"),
            std::format("{}", toTestYaml(document)) + "\n",
            spec.debug.traceAll || spec.debug.printSemToFile);

        {
            std::ofstream file{spec.debugFile("sem.txt")};
            ColStream     os{file};
            os.colored = false;
            ExporterTree tree{os};
            tree.evalTop(document);
        }

        {
            std::ofstream file{spec.debugFile("sem_colored.ansi")};
            ColStream     os{file};
            os.colored = true;
            ExporterTree tree{os};
            tree.evalTop(document);
        }
    }

    if (spec.sem.has_value()) {
        return compareSem(spec, document, spec.sem.value());
    } else {
        return RunResult::SemCompare{{.isOk = true}};
    }
}

void gtest_run_spec(CR<TestParams> params) {
    auto spec              = params.spec;
    spec.debug.debugOutDir = "/tmp/corpus_runs/" + params.testName();
    CorpusRunner runner;
    using RunResult  = CorpusRunner::RunResult;
    RunResult result = runner.runSpec(spec, params.file.native());

    if (result.isOk() && result.isSkip()) {
        GTEST_SKIP() << "Partially covered test: "
                     << (spec.debug.doLex ? "" : "lex is disabled ")     //
                     << (spec.debug.doParse ? "" : "parse is disabled ") //
                     << (spec.debug.doSem ? "" : "sem is disabled ");
    } else if (result.isOk()) {
        SUCCEED();
    } else {
        spec.debug = ParseSpec::Dbg{
            .debugOutDir      = "/tmp/corpus_runs/" + params.testName(),
            .traceLex         = true,
            .traceParse       = true,
            .traceSem         = true,
            .printLexed       = true,
            .printBaseLexed   = true,
            .printParsed      = true,
            .printSource      = true,
            .printLexedToFile = true,
            .printBaseLexedToFile = true,
            .printParsedToFile    = true,
            .printSemToFile       = true,
        };

        for (auto& exporter : spec.exporters) {
            exporter.doTrace     = true;
            exporter.print       = true;
            exporter.printToFile = true;
        }

        RunResult fail = runner.runSpec(spec, params.file.native());
        ColText   os;

        std::visit(
            overloaded{
                [&](CR<RunResult::CompareBase> node) {
                    os = node.failDescribe;
                },
                [&](RunResult::Skip const& node) {},
                [&](RunResult::None const& node) {},
            },
            fail.data);

        writeFile(spec.debugFile("failure.txt"), os.toString(false));

        FAIL() << params.fullName() << " failed, , wrote debug to "
               << spec.debug.debugOutDir;
    }
}
