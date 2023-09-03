#include "corpusrunner.hpp"

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <exporters/ExporterJson.hpp>
#include <exporters/exportertree.hpp>
#include <exporters/exportersimplesexpr.hpp>
#include <exporters/exportersubtreestructure.hpp>
#include <exporters/exporterhtml.hpp>
#include <exporters/exportermindmap.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exporterlatex.hpp>
#include <exporters/exporterpandoc.hpp>
#include <exporters/exportereventlog.hpp>
#include <exporters/exportergantt.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/diffs.hpp>


#define CB(name)                                                          \
    { Str(#name), &OrgTokenizer::lex##name }


const UnorderedMap<Str, MockFull::LexerMethod> lexers({
    CB(Angle),          CB(TimeStamp),      CB(TimeRange),
    CB(LinkTarget),     CB(Bracket),        CB(TextChars),
    CB(ParenArguments), CB(Text),           CB(Logbook),
    CB(Properties),     CB(Description),    CB(Drawer),
    CB(SubtreeTodo),    CB(SubtreeUrgency), CB(SubtreeTitle),
    CB(SubtreeTimes),   CB(Subtree),        CB(SourceBlockContent),
    CB(CommandBlock),   CB(List),           CB(Paragraph),
    CB(Comment),        CB(Table),          CB(Structure),
    CB(Global),
});
#undef CB

#define CB(name)                                                          \
    { Str(#name), &OrgParser::parse##name }
const UnorderedMap<Str, MockFull::ParserMethod> parsers({
    CB(HashTag),
    CB(Macro),
    CB(RawUrl),
    CB(Link),
    CB(InlineMath),
    CB(Symbol),
    CB(HashTag),
    CB(TimeStamp),
    CB(TimeRange),
    CB(Ident),
    CB(SrcInline),
    CB(Table),
    CB(CommandArguments),
    CB(SrcArguments),
    CB(Src),
    CB(ListItemBody),
    CB(ListItem),
    CB(TopParagraph),
    CB(InlineParagraph),
    CB(NestedList),
    CB(List),
    CB(SubtreeLogbookClockEntry),
    CB(SubtreeLogbookListEntry),
    CB(SubtreeLogbook),
    CB(SubtreeDrawer),
    CB(Subtree),
    CB(OrgFile),
    CB(LineCommand),
    CB(ToplevelItem),
    CB(Top),
    CB(Full),
});
#undef CB

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

    if (ignore(target)) {
        return result;
    }

    // if the values are the same, return empty patch
    if (source == target) {
        return result;
    }

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
    const QFileInfo& target,
    const QString&   content,
    bool             useFile) {
    if (useFile) {
        writeFile(target, content);

    } else {
        QFile file;
        file.open(stdout, QIODevice::WriteOnly);
        QTextStream stream{&file};
        stream << content;
    }
}

MockFull::ParserMethod CorpusRunner::getParser(CR<Str> name) {
    if (parsers.contains(name)) {
        return parsers.at(name);
    } else {
        throw GetterError(
            "'$#$#' is missing from parser method table"
            % to_string_vec(name, name.empty() ? "(empty)" : ""));
    }
}

MockFull::LexerMethod CorpusRunner::getLexer(CR<Str> name) {
    if (lexers.contains(name)) {
        return lexers.at(name);
    } else {
        throw GetterError(
            "'$#$#' is missing from lexer method table"
            % to_string_vec(name, name.empty() ? "(empty)" : ""));
    }
}


void format(
    ColStream&               os,
    CR<FormattedDiff>        text,
    Func<ColText(int, bool)> formatCb,
    int                      lhsSize    = 48,
    int                      rhsSize    = 16,
    bool                     useQFormat = false) {
    if (text.isUnified()) {
        os << (ColText("Given") <<= lhsSize) << (ColText("Expected"))
           << "\n";
        Vec<Pair<FormattedDiff::DiffLine, FormattedDiff::DiffLine>> lines;
        for (auto const& pair : text.unifiedLines()) {
            lines.push_back(pair);
        }

        Slice<int> range = slice(0, lines.size() - 1);
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

        for (int i = range.last; range.first < i; --i) {
            if (lines[i].first.prefix == SeqEditKind::Keep
                && lines[i].second.prefix == SeqEditKind::Keep) {
                range.last = i;
            } else {
                range.last = std::min(lines.high(), i + 1);
                break;
            }
        }

        for (const auto& i : range) {
            auto const& lhs = lines[i].first;
            auto const& rhs = lines[i].second;

            auto lhsStyle = useQFormat ? ColStyle() : toStyle(lhs.prefix);
            auto rhsStyle = useQFormat ? ColStyle() : toStyle(rhs.prefix);

            os << (ColText(lhsStyle, toPrefix(lhs.prefix)) <<= 2)
               << ((lhs.empty()
                        ? ColText("")
                        : ColText(
                            lhsStyle, formatCb(lhs.index().value(), true)))
                   <<= lhsSize)
               << (useQFormat
                       ? ColText("")
                       : (ColText(rhsStyle, toPrefix(rhs.prefix)) <<= 2))
               << ((rhs.empty() ? ColText("")
                                : ColText(
                                    rhsStyle,
                                    formatCb(rhs.index().value(), false)))
                   <<= rhsSize)
               << Qt::endl;
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
            os << os.red() << "missing entry";
            break;
        }
        case DiffItem::Op::Add: {
            os << os.green() << "unexpected entry";
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
            os << "\"" << os.yellow() << j.get<std::string>() << os.end()
               << "\"";
            break;
        }
    }
};


json CorpusRunner::toTextLyt(
    layout::Block::Ptr        block,
    Func<Str(layout::LytStr)> getStr) {
    using b = layout::Block;

    auto getSubnodes = [&](CVec<b::Ptr> elements) {
        json res = json::array();
        for (auto const& e : elements) {
            res.push_back(toTextLyt(e, getStr));
        }
        return res;
    };

    return std::visit(
        overloaded{
            [&](b::Empty const&) -> json {
                return {{"kind", "empty"}};
            },
            [&](b::Line const& l) -> json {
                return {
                    {"kind", "line"},
                    {"subnodes", getSubnodes(l.elements)}};
            },
            [&](b::Stack const& l) -> json {
                return {
                    {"kind", "block"},
                    {"subnodes", getSubnodes(l.elements)}};
            },
            [&](b::Choice const& l) -> json {
                return {
                    {"kind", "choice"},
                    {"subnodes", getSubnodes(l.elements)}};
            },
            [&](b::Verb const& l) -> json {
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
            [&](b::Text const& l) -> json {
                json arr = json::array();
                for (auto const& i : l.text.strs) {
                    arr.push_back(getStr(i));
                }
                return {{"kind", "text"}, {"tokens", arr}};
            },
            [&](b::Wrap const& text) -> json {
                return {
                    {"kind", "wrap"},
                    {"sep", getStr(text.sep)},
                    {"prefix",
                     text.prefix ? json(getStr(text.prefix.value()))
                                 : json()},
                    {"subnodes", getSubnodes(text.wrapElements)}};
            },
        },
        block->data);
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
       << to_string(ev.kind);

    if (ev.visitedNode) {
        os << " node:" << to_string(ev.visitedNode->getKind());
    }

    if (0 < ev.field.length()) {
        os << " field:" << ev.field;
    }

    os << " on " << QFileInfo(ev.file).fileName() << ":" << ev.line << " "
       << ev.function << " " << os.end();

    if (0 < ev.type.length()) {
        os << " type:" << demangle(ev.type.toLatin1());
    }

    trace.endStream(os);
}


void to_json(json& res, ExporterEventLog::Event const& ev) {
    res         = json::object();
    res["kind"] = to_string(ev.getKind());
    std::visit(
        [&](auto const& it) {
            json sub = json::object();
            to_json(sub, ev);
            res[to_string(ev.getKind()).toStdString()] = sub;
        },
        ev.data);
}

CorpusRunner::ExportResult CorpusRunner::runExporter(
    ParseSpec const&                 spec,
    sem::SemId                       top,
    const ParseSpec::ExporterExpect& exp) {
    using ER = ExportResult;

    auto strForStore = [](layout::SimpleStringStore const& store)
        -> Func<Str(layout::LytStr)> {
        return [&](layout::LytStr str) { return store.str(str); };
    };

    auto withTreeExporter = [this,
                             &strForStore](sem::SemId top, auto& run) {
        auto block = run.visitTop(top);
        return ER(
            ER::Text{.textLyt = toTextLyt(block, strForStore(run.store))});
    };

    if (exp.name == "json") {
        return ER(ER::Structured{.data = ExporterJson().visitTop(top)});
    } else if (exp.name == "sexp") {
        ExporterSimpleSExpr run;
        return withTreeExporter(top, run);

    } else if (exp.name == "pandoc") {
        return ER(ER::Structured{
            .data = ExporterPandoc().visitTop(top).unpacked.at(0)});

    } else if (exp.name == "html") {
        ExporterHtml run;
        return withTreeExporter(top, run);

    } else if (exp.name == "event_log") {
        ExporterEventLog exporter;
        using Ev = ExporterEventLog::Event;
        Vec<Ev> events;
        exporter.logConsumer = [&](ExporterEventLog::Event const& ev) {
            events.push_back(ev);
        };

        exporter.visitTop(top);

        json res;
        to_json(res, events);

        return ER(ER::Structured{.data = res});

    } else if (exp.name == "gantt") {
        ExporterGantt exporter;
        exporter.visitTop(top);
        return ER(ER::Structured{.data = json()});

    } else if (exp.name == "latex") {
        ExporterLatex run;
        return withTreeExporter(top, run);

    } else if (exp.name == "subtree_structure") {
        return ER(ER::Structured{
            .data = ExporterSubtreeStructure().visitTop(top)});

    } else if (exp.name == "mmap") {
        ExporterMindMap run;
        run.visitTop(top);
        ExporterMindMap::Graph const& g = run.toGraph();
        ER::JsonGraph                 result;

        for (auto [it, it_end] = boost::edges(g); it != it_end; ++it) {
            result.edges.push_back(run.toJsonGraphEdge(*it));
        }

        for (auto [it, it_end] = boost::vertices(g); it != it_end; ++it) {
            result.nodes.push_back(run.toJsonGraphNode(*it));
        }

        if (exp.print) {
            QString     buf;
            QTextStream stream{&buf};
            if (!result.nodes.empty()) {
                stream << "nodes:\n";
                for (auto const& node : result.nodes) {
                    stream << "  - "
                           << to_compact_json(
                                  node, {.startIndent = 6, .width = 160})
                           << "\n";
                }
            }

            if (!result.edges.empty()) {
                stream << "edges:\n";
                for (auto const& edge : result.edges) {
                    stream << "  - "
                           << to_compact_json(
                                  edge, {.startIndent = 6, .width = 160})
                           << "\n";
                }
            }

            writeFileOrStdout(
                spec.debugFile(exp.name + "result.txt"),
                buf + "\n\n" + run.toGraphviz() + "\n\n",
                exp.printToFile);
        }

        return ER(result);

    } else {
        throw std::domain_error(
            "Unexpected export result name " + exp.name.toStdString());
    }
}

CorpusRunner::RunResult::ExportCompare::Run CorpusRunner::compareExport(
    const ParseSpec::ExporterExpect& exp,
    const ExportResult&              result) {
    RunResult::ExportCompare::Run cmp;
    cmp.isOk = true;
    ColStream os;
    switch (result.getKind()) {
        case ExportResult::Kind::JsonGraph: {
            auto const& res = result.getJsonGraph();
            if (exp.expected["nodes"]) {
                UnorderedMap<std::string, json> given;
                for (auto const& node : res.nodes) {
                    given[node["metadata"]["id"].get<std::string>()] = node;
                }

                for (auto const& node : exp.expected["nodes"]) {
                    auto id = node["metadata"]["id"].as<std::string>();
                    if (given.contains(id)) {
                        int  failCount = 0;
                        auto expected  = toJson(node);
                        for (auto const& it :
                             json_diff(given.at(id), expected)) {
                            if (it.op == DiffItem::Op::Remove) {
                                continue;
                            }
                            json::json_pointer path{it.path};
                            os << "- Node with ID '" << id << "'";
                            describeDiff(os, it, expected, given.at(id));
                            os << "\n";
                            ++failCount;
                        }

                        if (0 < failCount) {
                            cmp.isOk = false;
                        }

                    } else {
                        cmp.isOk = false;
                        os << "Node with ID '" << os.red() << id
                           << os.end() << "' missing\n";
                    }
                }
            }

            if (exp.expected["edges"]) {
                UnorderedMap<
                    Pair<Pair<std::string, int>, std::string>,
                    Vec<json>>
                    generated_map;

                for (auto const& edge : res.edges) {
                    generated_map
                        [std::make_pair(
                             std::make_pair(
                                 edge["source"].get<std::string>(),
                                 edge["metadata"]["out_index"].get<int>()),
                             edge["target"].get<std::string>())]
                            .push_back(edge);
                }

                for (auto const& edge_expected : exp.expected["edges"]) {
                    std::string source = edge_expected["source"]
                                             .as<std::string>();
                    std::string target = edge_expected["target"]
                                             .as<std::string>();

                    int out_index = edge_expected["metadata"]["out_index"]
                                        .as<int>(0);

                    auto key = std::make_pair(
                        std::make_pair(source, out_index), target);

                    json expected_json = toJson(edge_expected);

                    if (generated_map.contains(key)
                        && !generated_map[key].empty()) {
                        for (auto const& given_json : generated_map[key]) {
                            int failCount = 0;
                            for (auto const& it :
                                 json_diff(given_json, expected_json)) {
                                if (it.op == DiffItem::Op::Remove) {
                                    continue;
                                } else {
                                    ++failCount;
                                    json::json_pointer path{it.path};
                                    os << "- Edge No " << out_index
                                       << " between '" << source << "' '"
                                       << target << "' differs: ";
                                    describeDiff(
                                        os, it, expected_json, given_json);
                                    os << "\n";
                                }
                            }

                            if (0 < failCount) {
                                cmp.isOk = false;
                            }
                        }
                    } else {
                        cmp.isOk = false;
                        os << "No edge between nodes '" << os.red()
                           << source << "' and '" << target << os.end()
                           << "'\n";
                        os << "  expected " << expected_json.dump()
                           << "\n";
                    }
                }
            }
            break;
        }
        default: {
            qCritical() << ("TODO" + to_string(result.getKind()));
            cmp.isOk = true;
        }
    }

    cmp.failDescribe = os.getBuffer();
    return cmp;
}

CorpusRunner::RunResult::LexCompare CorpusRunner::compareTokens(
    CR<TokenGroup<OrgTokenKind>> lexed,
    CR<TokenGroup<OrgTokenKind>> expected,
    ParseSpec::Conf::MatchMode   match) {
    using Mode                   = ParseSpec::Conf::MatchMode;
    BacktrackRes tokenSimilarity = longestCommonSubsequence<OrgToken>(
        lexed.tokens.content,
        expected.tokens.content,
        [](CR<OrgToken> lhs, CR<OrgToken> rhs) -> bool {
            if (lhs.kind != rhs.kind) {
                return false;
            } else if (lhs.hasData() != rhs.hasData()) {
                return false;
            } else if (
                lhs.hasData()
                && Str(lhs.getText()) != Str(rhs.getText())) {
                return false;
            } else {
                return true;
            }
        })[0];

    if ((match == Mode::Full
         && tokenSimilarity.lhsIndex.size() == lexed.size()
         && tokenSimilarity.rhsIndex.size() == expected.size())
        || (match == Mode::ExpectedSubset
            && tokenSimilarity.rhsIndex.size() == expected.size())) {
        return {.isOk = true};
    } else {
        ShiftedDiff tokenDiff{
            tokenSimilarity, lexed.size(), expected.size()};

        Func<Str(CR<OrgToken>)> conv = [](CR<OrgToken> tok) -> Str {
            return to_string(tok);
        };

        FormattedDiff text{tokenDiff};

        ColStream os;
        int       lhsSize = 48;
        int       rhsSize = 30;
        bool      inQt    = useQFormat();

        format(
            os,
            text,
            [&](int id, bool isLhs) -> ColText {
                auto tok = isLhs ? lexed.tokens.content.at(id)
                                 : expected.tokens.content.at(id);

                HDisplayOpts opts{};
                opts.flags.excl(HDisplayFlag::UseQuotes);
                if (useQFormat()) {
                    opts.flags.incl(HDisplayFlag::UseAscii);
                }

                QString result = //
                    QString(
                        useQFormat()
                            ? (isLhs ? "${kind} \"${text}\" <"
                                     : "> \"${text}\" ${kind}")
                            : "${index} ${kind} ${text}")
                    % fold_format_pairs({
                        {"index", to_string(id)},
                        {"kind", to_string(tok.kind)},
                        {"text",
                         hshow(tok.strVal(), opts).toString(false)},
                        // {tok.hasData()},
                    });

                auto indexFmt = QString("[%1]").arg(id);
                return useQFormat()
                         ? (isLhs ? indexFmt
                                        + right_aligned(
                                            result,
                                            lhsSize - indexFmt.size())
                                  : left_aligned(
                                        result, rhsSize - indexFmt.size())
                                        + indexFmt)
                         : result;
            },
            lhsSize,
            rhsSize,
            useQFormat());

        return {.isOk = false, .failDescribe = os.getBuffer()};
    }
}

CorpusRunner::RunResult::NodeCompare CorpusRunner::compareNodes(
    CR<NodeGroup<OrgNodeKind, OrgTokenKind>> parsed,
    CR<NodeGroup<OrgNodeKind, OrgTokenKind>> expected) {
    BacktrackRes nodeSimilarity = longestCommonSubsequence<OrgNode>(
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
        })[0];


    ShiftedDiff nodeDiff{nodeSimilarity, parsed.size(), expected.size()};


    if (nodeSimilarity.lhsIndex.size() == parsed.size()
        && nodeSimilarity.rhsIndex.size() == expected.size()) {
        return {.isOk = true};
    } else {
        ShiftedDiff nodeDiff{
            nodeSimilarity, parsed.size(), expected.size()};

        Func<Str(CR<OrgNode>)> conv = [](CR<OrgNode> tok) -> Str {
            return to_string(tok);
        };

        FormattedDiff text{nodeDiff};
        ColStream     os;
        format(os, text, [&](int id, bool isLhs) -> ColText {
            auto node = isLhs ? parsed.nodes.content.at(id)
                              : expected.nodes.content.at(id);

            auto group = isLhs ? &parsed : &expected;

            return "$# $# $#($# $#)"
                 % to_string_vec(
                       id,
                       node.kind,
                       node.isTerminal() ? escape_literal(
                           hshow(
                               group->strVal(OrgId(id)),
                               HDisplayOpts().excl(
                                   HDisplayFlag::UseQuotes))
                               .toString(false))
                                         : QString(""),
                       node.kind,
                       node.isTerminal()
                           ? "tok=" + to_string(node.getToken().getIndex())
                           : "ext=" + to_string(node.getExtent()));
        });

        return {.isOk = false, .failDescribe = os.getBuffer()};
    }
}

CorpusRunner::RunResult::SemCompare CorpusRunner::compareSem(
    CR<ParseSpec> spec,
    sem::SemId    node,
    json          expected) {

    ExporterJson     exporter;
    OperationsTracer trace{spec.debugFile("sem_export_trace.txt")};
    exporter.visitEventCb = [&](ExporterJson::VisitEvent const& ev) {
        exporterVisit<ExporterJson>(trace, ev);
    };

    json          converted = exporter.visitTop(node);
    Vec<DiffItem> diff      = json_diff(converted, expected);
    int           failCount = 0;
    ColStream     os;
    if (useQFormat()) {
        os.colored = false;
    }
    UnorderedMap<std::string, DiffItem> ops;


    for (auto const& it : diff) {
        ops[it.path] = it;
        json::json_pointer path{it.path};
        if (!path.empty() && it.op == DiffItem::Op::Remove) {
            continue;
        } else {
            ++failCount;
        }

        describeDiff(os, it, expected, converted);
        os << "\n";
    }

    auto maybePathDiff = [&](json::json_pointer const& path) {
        if (ops.contains(path.to_string())) {
            describeDiff(os, ops[path.to_string()], expected, converted);
        }
    };

    Func<void(json, int, json::json_pointer const&)> aux;
    aux = [&](json const& j, int level, json::json_pointer const& path) {
        switch (j.type()) {
            case json::value_t::array: {
                for (int i = 0; i < j.size(); ++i) {
                    if (isEmpty(j[i])) {
                        continue;
                    }
                    os.indent(level * 2) << "-";
                    if (isSimple(j[i])) {
                        os << " ";
                        writeSimple(os, j);
                        os << " ";
                        maybePathDiff(path / i);
                        os << "\n";
                    } else {
                        maybePathDiff(path / i);
                        os << "\n";
                        aux(j[i], level + 1, path / i);
                    }
                }
                break;
            }
            case json::value_t::object: {
                for (json::const_iterator it = j.begin(); it != j.end();
                     ++it) {
                    if (it.key() == "id" || it.key() == "loc"
                        || isEmpty(it.value())) {
                        continue;
                    }
                    os.indent(level * 2) << it.key() << ":";
                    json const& value = it.value();
                    if (isSimple(value)) {
                        os << " ";
                        writeSimple(os, value);
                        maybePathDiff(path / it.key());
                        os << "\n";
                    } else {
                        maybePathDiff(path / it.key());
                        os << "\n";
                        aux(it.value(), level + 1, path / it.key());
                        os << "\n";
                    }
                }
                break;
            }
            case json::value_t::number_float:
            case json::value_t::number_integer:
            case json::value_t::boolean:
            case json::value_t::string: {
                writeSimple(os, j);
                break;
            }
        }
    };

    if (0 < failCount) {
        os << "converted:\n";
        aux(converted, 0, json::json_pointer{});
        os << "\nexpected:\n";
        aux(expected, 0, json::json_pointer{});

        return {.isOk = false, .failDescribe = os.getBuffer()};
    } else {
        return {.isOk = true};
    }
}

CorpusRunner::RunResult CorpusRunner::runSpec(
    CR<ParseSpec> spec,
    CR<QString>   from) {
    MockFull::LexerMethod lexCb = getLexer(spec.lexImplName);
    MockFull              p(spec.debug.traceParse, spec.debug.traceLex);

    { // Input source
        if (spec.debug.printSource) {
            writeFile(spec.debugFile("source.org"), spec.source);
        }
    }


    { // Lexing
        if (spec.debug.doLex) {
            p.tokenizer->trace = spec.debug.traceLex;
            if (spec.debug.lexToFile) {
                p.tokenizer->setTraceFile(spec.debugFile("trace_lex.txt"));
            }

            p.tokenize(spec.source, lexCb);
        } else {
            return RunResult{};
        }

        if (spec.debug.printLexed) {
            writeFileOrStdout(
                spec.debugFile("lexed.yaml"),
                to_string(yamlRepr(p.tokens)) + "\n",
                spec.debug.printLexedToFile);
        }

        if (spec.tokens.has_value()) {
            Str                   buffer;
            RunResult::LexCompare result = compareTokens(
                p.tokens,
                fromFlatTokens<OrgTokenKind>(spec.tokens.value(), buffer),
                spec.conf.tokenMatch);
            if (!result.isOk) {
                return RunResult(result);
            }
        }
    }

    { // Parsing
        if (spec.debug.doParse) {
            p.parser->trace = spec.debug.traceParse;
            if (spec.debug.parseToFile) {
                p.parser->setTraceFile(spec.debugFile("trace_parse.txt"));
            }

            MockFull::ParserMethod parseCb = getParser(spec.parseImplName);

            p.parse(parseCb);

            if (spec.debug.printParsed) {
                writeFileOrStdout(
                    spec.debugFile("parsed.yaml"),
                    to_string(yamlRepr(p.nodes)) + "\n",
                    spec.debug.printParsedToFile);

                writeFileOrStdout(
                    spec.debugFile("parsed.txt"),
                    OrgAdapter(&p.nodes, OrgId(0)).treeRepr(false) + "\n",
                    spec.debug.printParsedToFile);
            }
        } else {
            return RunResult{};
        }

        if (spec.subnodes.has_value()) {
            Str           buffer;
            OrgNodeGroup  nodes;
            OrgTokenGroup tokens;

            if (spec.tokens.has_value()) {
                tokens = fromFlatTokens<OrgTokenKind>(
                    spec.tokens.value(), buffer);
            }

            if (spec.subnodes.has_value()) {
                nodes = fromFlatNodes<OrgNodeKind, OrgTokenKind>(
                    spec.subnodes.value());
            }

            nodes.tokens = &tokens;

            RunResult::NodeCompare result = compareNodes(p.nodes, nodes);
            if (!result.isOk) {
                return RunResult(result);
            }
        }
    }


    { // Sem conversion
        if (spec.debug.doSem) {
            sem::ContextStore context;
            sem::OrgConverter converter(&context);

            converter.trace = spec.debug.traceSem;
            if (spec.debug.semToFile) {
                converter.setTraceFile(spec.debugFile("trace_sem.txt"));
            }

            auto document = converter.toDocument(
                OrgAdapter(&p.nodes, OrgId(0)));


            if (spec.debug.printSem) {
                ExporterYaml exporter;
                exporter.skipNullFields  = true;
                exporter.skipFalseFields = true;
                exporter.skipZeroFields  = true;
                exporter.skipLocation    = true;
                exporter.skipId          = true;
                writeFileOrStdout(
                    spec.debugFile("sem.yaml"),
                    to_string(exporter.visitTop(document)) + "\n",
                    spec.debug.printSemToFile);
            }

            if (spec.sem.has_value()) {
                RunResult::SemCompare result = compareSem(
                    spec, document, spec.sem.value());


                if (!result.isOk) {
                    return RunResult(result);
                }
            }

            if (!spec.exporters.empty()) {
                RunResult::ExportCompare cmp;
                for (auto const& exp : spec.exporters) {
                    cmp.run.push_back(compareExport(
                        exp, runExporter(spec, document, exp)));
                }

                return RunResult(cmp);
            }
        }
    }

    return RunResult();
}
