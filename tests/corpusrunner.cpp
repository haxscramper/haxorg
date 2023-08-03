#include "corpusrunner.hpp"

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <exporters/ExporterJson.hpp>
#include <exporters/exportertree.hpp>
#include <exporters/exportersimplesexpr.hpp>
#include <exporters/exportersubtreestructure.hpp>
#include <exporters/exporterhtml.hpp>
#include <exporters/exporterlatex.hpp>
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
});
#undef CB


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
    ColStream&  os,
    json const& it,
    json const& expected,
    json const& converted) {
    auto op = it["op"].get<std::string>();

    json::json_pointer path{it["path"].get<std::string>()};

    os << "  ";
    if (op == "remove") {
        os << os.red() << "missing entry";
    } else if (op == "add") {
        os << os.green() << "unexpected entry";
    } else {
        os << os.magenta() << "changed entry";
    }

    os << " on path '" << os.yellow() << path.to_string() << os.end()
       << "' ";

    if (op == "replace") {
        os << "    from " << os.red() << expected[path].dump() << os.end()
           << " to " << os.green() << converted[path].dump() << os.end();

    } else if (op == "add") {
        os << "    " << it["value"].dump();
    } else if (op == "remove") {
        os << "    " << os.red() << converted[path].dump() << os.end();
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


CorpusRunner::ExportResult CorpusRunner::runExporter(
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

    if (exp.exporterName == "json") {
        return ER(ER::Structured{.data = ExporterJson().visitTop(top)});
    } else if (exp.exporterName == "sexp") {
        ExporterSimpleSExpr run;
        return withTreeExporter(top, run);

    } else if (exp.exporterName == "html") {
        ExporterHtml run;
        return withTreeExporter(top, run);

    } else if (exp.exporterName == "latex") {
        ExporterLatex run;
        return withTreeExporter(top, run);

    } else if (exp.exporterName == "subtree_structure") {
        return ER(ER::Structured{
            .data = ExporterSubtreeStructure().visitTop(top)});


    } else {
        throw std::domain_error(
            "Unexpected export result name "
            + exp.exporterName.toStdString());
    }
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

    json      converted = exporter.visitTop(node);
    json      diff      = json::diff(converted, expected);
    int       failCount = 0;
    ColStream os;
    if (useQFormat()) {
        os.colored = false;
    }
    UnorderedMap<std::string, json> ops;


    for (auto const& it : diff) {
        ops[it["path"].get<std::string>()] = it;
        auto               op              = it["op"].get<std::string>();
        json::json_pointer path{it["path"].get<std::string>()};
        if (!path.empty()               //
            && op == "remove"           //
            && (path.back() == "id"     //
                || path.back() == "loc" //
                || path.back() == "subnodes"
                || path.back() == "attached")) {
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
