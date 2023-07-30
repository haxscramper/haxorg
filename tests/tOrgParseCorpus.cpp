#include "org_parse_aux.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <lexbase/NodeIO.hpp>
#include <lexbase/NodeTest.hpp>
#include <sem/ErrorWrite.hpp>
#include <gtest/gtest.h>
#include <QDirIterator>

#include <exporters/ExporterJson.hpp>
#include <exporters/exportertree.hpp>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <sem/SemConvert.hpp>

#include <hstd/stdlib/diffs.hpp>

#include <fnmatch.h>
#include <ranges>

namespace rs = std::views;

#define CB(name)                                                          \
    { Str(#name), &OrgTokenizer::lex##name }

bool useQFormat() { return getenv("IN_QT_RUN") == "true"; }

void writeFileOrStdout(
    QFileInfo const& target,
    QString const&   content,
    bool             useStdout) {
    if (useStdout) {
        QFile file;
        file.open(stdout, QIODevice::WriteOnly);
        QTextStream stream{&file};
        stream << content;

    } else {
        writeFile(target, content);
    }
}


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


MockFull::ParserMethod getParser(CR<Str> name) {
    if (parsers.contains(name)) {
        return parsers.at(name);
    } else {
        throw GetterError(
            "'$#$#' is missing from parser method table"
            % to_string_vec(name, name.empty() ? "(empty)" : ""));
    }
}

MockFull::LexerMethod getLexer(CR<Str> name) {
    if (lexers.contains(name)) {
        return lexers.at(name);
    } else {
        throw GetterError(
            "'$#$#' is missing from lexer method table"
            % to_string_vec(name, name.empty() ? "(empty)" : ""));
    }
}

inline void format(
    QTextStream&             os,
    CR<FormattedDiff>        text,
    Func<QString(int, bool)> formatCb,
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

void compareNodes(
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
        SUCCEED();
    } else {
        ShiftedDiff nodeDiff{
            nodeSimilarity, parsed.size(), expected.size()};

        Func<Str(CR<OrgNode>)> conv = [](CR<OrgNode> tok) -> Str {
            return to_string(tok);
        };

        FormattedDiff text{nodeDiff};
        QString       buffer;
        QTextStream   os{&buffer};
        format(os, text, [&](int id, bool isLhs) -> QString {
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

        qcout << buffer << Qt::endl;
        FAIL() << "Parsed tree structure mismatch";
    }
}

void compareTokens(
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
        SUCCEED();
    } else {
        qDebug() << match;
        ShiftedDiff tokenDiff{
            tokenSimilarity, lexed.size(), expected.size()};

        Func<Str(CR<OrgToken>)> conv = [](CR<OrgToken> tok) -> Str {
            return to_string(tok);
        };

        FormattedDiff text{tokenDiff};

        QString     buffer;
        QTextStream os{&buffer};
        int         lhsSize = 48;
        int         rhsSize = 30;
        bool        inQt    = useQFormat();
        format(
            os,
            text,
            [&](int id, bool isLhs) -> QString {
                auto tok = isLhs ? lexed.tokens.content.at(id)
                                 : expected.tokens.content.at(id);

                HDisplayOpts opts{};
                opts.flags.excl(HDisplayFlag::UseQuotes);
                if (useQFormat) {
                    opts.flags.incl(HDisplayFlag::UseAscii);
                }

                QString result = //
                    QString(
                        useQFormat
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
                return useQFormat
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
            useQFormat);

        FAIL() << "Lexed token mismatch\n" << buffer;
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

void compareSem(CR<ParseSpec> spec, sem::SemId node, json expected) {
    json        converted = ExporterJson().visitTop(node);
    json        diff      = json::diff(converted, expected);
    int         failCount = 0;
    QString     buf;
    QTextStream stream{&buf};
    ColStream   os{stream};
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
                || path.back() == "subnodes")) {
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

        FAIL() << "Sem tree structure mismatch for '" << spec.getLocMsg()
               << "'\n"
               << buf.toStdString();
    }
}

void runSpec(CR<ParseSpec> spec, CR<QString> from) {
    MockFull::LexerMethod lexCb = getLexer(spec.lexImplName);
    MockFull              p;

    // qDebug().noquote() << ((
    //     "$# at $#:$#"
    //     % to_string_vec(
    //         spec.testName,
    //         spec.specLocation.line,
    //         spec.specLocation.column)));

    p.parser->trace = spec.dbg.traceParse;
    if (spec.dbg.parseToFile) {
        p.parser->setTraceFile(spec.debugFile("parse.txt"));
    }

    p.tokenizer->trace = spec.dbg.traceLex;
    if (spec.dbg.lexToFile) {
        p.tokenizer->setTraceFile(spec.debugFile("random.txt"));
    }

    if (spec.dbg.printSource) {
        qDebug().noquote().nospace()
            << "\n------------------\n"
            << spec.source << "\n------------------\n";
    }

    if (spec.dbg.doLex) {
        p.tokenize(spec.source, lexCb);
    }
    YAML::Emitter emitter;

    Str           buffer;
    OrgNodeGroup  nodes;
    OrgTokenGroup tokens;

    if (spec.expectedMode == ParseSpec::ExpectedMode::Nested) {
        if (spec.subnodes.has_value()) {
            auto tree = fromHomogeneous<OrgNodeKind, OrgTokenKind>(
                spec.subnodes.value());
            auto flatResult = tree.flatten(buffer);
            nodes           = flatResult.first;
            tokens          = flatResult.second;
        }
    } else {
        if (spec.tokens.has_value()) {
            tokens = fromFlatTokens<OrgTokenKind>(
                spec.tokens.value(), buffer);
        }

        if (spec.subnodes.has_value()) {
            nodes = fromFlatNodes<OrgNodeKind, OrgTokenKind>(
                spec.subnodes.value());
        }
    }

    p.nodes.tokens = &p.tokens;
    nodes.tokens   = &tokens;

    if (spec.dbg.printLexed) {
        writeFileOrStdout(
            spec.debugFile("lexed.yaml"),
            to_string(yamlRepr(p.tokens)) + "\n",
            spec.dbg.printLexedToFile);
    }

    if (spec.dbg.doLex) {
        if (spec.tokens.has_value()) {
            compareTokens(p.tokens, tokens, spec.conf.tokenMatchMode);
        }

        if (spec.dbg.doParse) {
            MockFull::ParserMethod parseCb = getParser(spec.parseImplName);

            p.parse(parseCb);

            if (spec.dbg.printParsed) {
                writeFileOrStdout(
                    spec.debugFile("parsed.yaml"),
                    to_string(yamlRepr(p.nodes)) + "\n",
                    spec.dbg.printParsedToFile);
            }

            if (spec.subnodes.has_value()) {
                compareNodes(p.nodes, nodes);
            }

            if (spec.dbg.doSem && spec.semExpected.has_value()) {
                sem::OrgConverter converter;
                compareSem(
                    spec,
                    converter.toDocument(OrgAdapter(&p.nodes, OrgId(0))),
                    spec.semExpected.value());
            }
        }
    }
}

TEST(PrintError, MultipleFiles) {
    QString a_tao = R"''(def five = 5)''";
    QString b_tao = R"''(def six = five + "1")''";

    ColText natColorized  = "Nat"_qs;
    ColText strColorized  = "Str"_qs;
    ColText fiveColorized = "5"_qs;

    Id a_id = 1;
    Id b_id = 2;

    ColStyle a;
    ColStyle b;
    ColStyle c;

    StrCache sources;
    sources.add(a_id, a_tao, "a_tao");
    sources.add(b_id, b_tao, "b_tao");

    QString     buf;
    QTextStream os{&buf};
    Report(ReportKind::Error, b_id, 10)
        .with_code("3")
        .with_message("Cannot add types Nat and Str"_qs)
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(b_id, slice(10, 14)))
                .with_message("This is of type " + natColorized)
                .with_color(a))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(b_id, slice(17, 20)))
                .with_message("This is of typee " + strColorized)
                .with_color(b))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(b_id, slice(15, 16)))
                .with_message(
                    natColorized + " and " + strColorized
                    + " undergo addition here")
                .with_color(c)
                .with_order(10))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(a_id, slice(4, 8)))
                .with_message(
                    "Original definition of " + fiveColorized + " is here")
                .with_color(a))
        .with_note(
            natColorized
            + " is a number and can only be added to other numbers")
        .write(sources, os);

    qDebug().noquote() << "\n" << buf;
    qDebug() << "First error run complete complete";
}

TEST(PrintError, MultipleAnnotations) {
    Id       id   = 0;
    QString  code = R"(def fives = ["5", 5]

def sixes = ["6", 6, True, (), []]

def multiline :: Str = match Some 5 in {
    | Some x => x
    | None => 0

})";
    StrCache sources;
    sources.add(id, code, "tao");
    QString     buf;
    QTextStream os{&buf};
    Report(ReportKind::Error, id, 13)
        .with_code("3")
        .with_message(("Incompatible types"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(0, 1 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(1, 2 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(2, 3 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(3, 4 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(4, 5 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(5, 6 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(6, 7 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(7, 8 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(8, 9 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(9, 10 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(10, 11 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(11, 12 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(12, 13 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(13, 14 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(14, 15 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(15, 16 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(16, 17 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(17, 18 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(18, 19 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(19, 20 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(20, 21 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(18, 19 + 1)))
                .with_message("This is of type Nat"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(13, 16 + 1)))
                .with_message("This is of type Str"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(40, 41 + 1)))
                .with_message("This is of type Nat"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(43, 47 + 1)))
                .with_message("This is of type Bool"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(49, 51 + 1)))
                .with_message("This is of type ()"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(53, 55 + 1)))
                .with_message("This is of type [_]"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(25, 78 + 1)))
                .with_message("This is of type Str"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(81, 124 + 1)))
                .with_message("This is of type Nat"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(100, 126 + 1)))
                .with_message("This is an inner multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(106, 120 + 1)))
                .with_message("This is another inner multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(108, 122 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(110, 111 + 1)))
                .with_message(
                    "This is an inline within the ne  b   bsting!"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(111, 112 + 1)))
                .with_message("And another!"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(103, 123 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(105, 125 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(112, 116 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(26, 100 + 1)))
                .with_message("Hahaha!"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(85, 110 + 1)))
                .with_message("Oh god, no more 1"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(84, 114 + 1)))
                .with_message("Oh god, no more 2"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(89, 113 + 1)))
                .with_message("Oh god, no more 3"_qs))
        .with_config(Config()
                         .with_cross_gap(false)
                         .with_compact(true)
                         .with_underlines(true)
                         .with_tab_width(4))
        .write(sources, os);

    qDebug().noquote() << buf;
}

// std::string corpusGlob = "*text.yaml";
std::string corpusGlob = "";

struct TestParams {
    ParseSpec spec;
    QFileInfo file;

    QString testName() const {
        QString final;
        for (QChar const& ch : fullName()) {
            if (ch.isDigit() || ch.isLetter() || ch == '_') {
                final.push_back(ch);
            } else {
                final.push_back('_');
            }
        }

        return final;
    }

    QString fullName() const {
        return "$# at $#:$#:$#"
             % to_string_vec(
                   spec.testName.has_value() ? spec.testName.value()
                                             : QString("<spec>"),
                   file.fileName(),
                   spec.specLocation.line,
                   spec.specLocation.column);
    }

    // Provide a friend overload.
    friend void PrintTo(const TestParams& point, std::ostream* os) {
        *os << point.fullName().toStdString();
    }
};

class ParseFile : public ::testing::TestWithParam<TestParams> {};

Vec<TestParams> generateTestRuns() {
    Vec<TestParams> results;
    QDirIterator    it(
        __CURRENT_FILE_DIR__ / "corpus"_qs, QDirIterator::Subdirectories);

    auto addSpecs = [&](QFileInfo const& path) {
        try {
            YAML::Node group = YAML::LoadFile(
                path.filePath().toStdString());
            ParseSpecGroup parsed{group, path.filePath()};
            for (const auto& spec : parsed.specs) {
                results.push_back({spec, path});
            }
        } catch (YAML::Exception& ex) {
            qFatal() << ex.what() << "at" << path.filePath();
        }
    };

    while (it.hasNext()) {
        QFileInfo path{it.next()};
        if (path.isFile() && path.fileName().endsWith(".yaml")) {
            std::string p = path.filePath().toStdString();
            if (corpusGlob.empty()) {
                addSpecs(path);
            } else {
                int matchRes = fnmatch(
                    corpusGlob.c_str(), p.c_str(), FNM_EXTMATCH);
                if (!(matchRes == FNM_NOMATCH)) {
                    addSpecs(path);
                }
            }
        }
    }
    for (auto& spec : results) {
        if (spec.spec.dbg.debugOutDir.size() == 0) {
            spec.spec.dbg.debugOutDir = "/tmp/" + spec.testName();
        }
    }


    return results;
}


std::string getTestName(
    const testing::TestParamInfo<ParseFile::ParamType>& info) {
    return info.param.testName().toStdString();
}

TEST_P(ParseFile, CorpusAll) {
    TestParams params = GetParam();
    runSpec(params.spec, params.file.filePath());
}

INSTANTIATE_TEST_CASE_P(
    CorpusAllParametrized,
    ParseFile,
    ::testing::ValuesIn(generateTestRuns()),
    getTestName);
