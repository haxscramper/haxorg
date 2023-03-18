#include "common.hpp"
#include "org_parse_aux.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgSpec.hpp>
#include <lexbase/NodeIO.hpp>
#include <lexbase/NodeTest.hpp>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <hstd/stdlib/diffs.hpp>

#include <fnmatch.h>
#include <ranges>

namespace rs = std::views;

#define CB(name)                                                          \
    { Str(#name), &OrgTokenizer::lex##name }

void writeFileOrStdout(
    fs::path const& target,
    QString const&  content,
    bool            useStdout) {
    if (useStdout) {
        writeFile(target, content);
    } else {
        QFile file;
        file.open(stdout, QIODevice::WriteOnly);
        QTextStream stream{&file};
        stream << content;
    }
}


const UnorderedMap<Str, MockFull::LexerMethod> lexers({
    CB(Angle),
    CB(Time),
    CB(LinkTarget),
    CB(Bracket),
    CB(TextChars),
    CB(ParenArguments),
    CB(Text),
    CB(Logbook),
    CB(Properties),
    CB(Description),
    CB(Drawer),
    CB(SubtreeTodo),
    CB(SubtreeUrgency),
    CB(SubtreeTitle),
    CB(SubtreeTimes),
    CB(Subtree),
    CB(SourceBlockContent),
    CB(CommandBlock),
    CB(List),
    CB(Paragraph),
    CB(Comment),
    CB(Table),
    CB(Structure),
    CB(Global),
});
#undef CB

#define CB(name)                                                          \
    { Str(#name), &OrgParser::parse##name }
const UnorderedMap<Str, MockFull::ParserMethod> parsers({
    CB(HashTag),
    CB(CSVArguments),
    CB(Macro),
    CB(RawUrl),
    CB(Link),
    CB(InlineMath),
    CB(Symbol),
    CB(HashTag),
    CB(Time),
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
    CB(LogbookClockEntry),
    CB(LogbookListEntry),
    CB(Logbook),
    CB(Drawer),
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
    int                      lhsSize = 48,
    int                      rhsSize = 16) {
    if (text.isUnified()) {
        os << (ColText("Given") <<= lhsSize) << (ColText("Expected"))
           << "\n";
        for (const auto& [lhs, rhs] : text.unifiedLines()) {
            auto lhsStyle = toStyle(lhs.prefix);
            auto rhsStyle = toStyle(rhs.prefix);
            os
                //
                << (ColText(lhsStyle, toPrefix(lhs.prefix)) <<= 2)
                << ((lhs.empty() ? ColText("")
                                 : ColText(
                                     lhsStyle,
                                     formatCb(lhs.index().value(), true)))
                    <<= lhsSize)
                << (ColText(rhsStyle, toPrefix(rhs.prefix)) <<= 2)
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
        SUCCEED("Parsed tree structure match");
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

            return "$# $# $#($# $# $#)"
                 % to_string_vec(
                       id,
                       node.kind,
                       hshow(group->strVal(OrgId(id))).toString(false),
                       node.kind,
                       node.isTerminal(),
                       node.isTerminal() ? to_string(node.getToken())
                                         : to_string(node.getExtent()));
        });

        qcout << buffer << Qt::endl;
        FAIL("Parsed tree structure mismatch");
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
        SUCCEED("Token lexer execution correct");
    } else {
        qDebug() << match;
        ShiftedDiff tokenDiff{
            tokenSimilarity, lexed.size(), expected.size()};

        Func<Str(CR<OrgToken>)> conv = [](CR<OrgToken> tok) -> Str {
            return to_string(tok);
        };

        // Vec<Str> lexedStr    = map(lexed.tokens.content, conv);
        // Vec<Str> expectedStr = map(expected.tokens.content, conv);

        FormattedDiff text{tokenDiff};

        QString     buffer;
        QTextStream os{&buffer};
        format(os, text, [&](int id, bool isLhs) -> QString {
            auto tok = isLhs ? lexed.tokens.content.at(id)
                             : expected.tokens.content.at(id);


            return "$# $# $#"
                 % to_string_vec(
                       id,
                       tok.kind,
                       hshow(tok.strVal()).toString(false),
                       tok.hasData());
        });

        qcout << buffer << Qt::endl;
        FAIL("Lexed token mismatch");
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

    p.trace = spec.dbg.traceParse;
    if (spec.dbg.parseToFile) {
        p.setTraceFile("/tmp/parse.txt");
    }

    p.tokenizer.trace = spec.dbg.traceLex;
    if (spec.dbg.lexToFile) {
        p.tokenizer.setTraceFile("/tmp/random.txt");
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
            "/tmp/lexed.yaml",
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
                    "/tmp/parsed.yaml",
                    to_string(yamlRepr(p.nodes)) + "\n",
                    spec.dbg.printParsedToFile);
            }

            if (spec.subnodes.has_value()) {
                compareNodes(p.nodes, nodes);
            }
        }
    }
}

void runSpec(CR<YAML::Node> group, CR<QString> from) {
    ParseSpecGroup parsed{group, from};
    auto           sectionName = [&](CR<ParseSpec> spec) {
        return ("$# at $#"
                % to_string_vec(
                    spec.testName.has_value() ? spec.testName.value()
                                              : QString("<spec>"),
                    from))
            .toStdString();
    };


    for (const auto& spec : parsed.specs) {
        SECTION(sectionName(spec)) { runSpec(spec, from); }
    }
}


TEST_CASE("Parse file", "[corpus][notes]") {
    MockFull p;
    // QString  source = readFile(
    //     "/mnt/workspace/repos/personal/indexed/notes.org");
    QString source = readFile("/tmp/doc.org");

    p.tokenizer.setTraceFile("/tmp/file_parse_trace.txt");

    // p.tokenizer.trace = false;
    p.tokens.base = source.data();
    LineColInfo info{source};
    p.tokenizer.locationResolver = [&](CR<PosStr> str) -> LineCol {
        Slice<int> absolute = p.tokens.toAbsolute(str.view);
        return {
            info.whichLine(absolute.first + str.pos),
            info.whichColumn(absolute.first + str.pos),
        };
    };

    UnorderedMap<OrgTokenId, OrgTokenizer::Report> pushedOn;

    using R = OrgTokenizer::ReportKind;

    p.tokenizer.reportHook = [&](CR<OrgTokenizer::Report> report) {
        switch (report.kind) {
            case R::Push: {
                pushedOn[report.id] = report;
                break;
            }
        }
    };

    // using It = Pair<Slice<int>, int>;
    // Vec<It> lines;
    // for (const auto& [key, val] : info.lines) {
    //     lines.push_back({key, val});
    // }

    // sort<It>(lines, [](CR<It> lhs, CR<It> rhs) {
    //     return lhs.first.first < rhs.first.first;
    // });

    // for (const auto& it : lines) {
    //     qDebug() << it;
    // }

    if (true) {
        p.tokenize(source, &OrgTokenizer::lexGlobal);
    } else {
        try {
            p.tokenize(source, &OrgTokenizer::lexGlobal);
        } catch (OrgTokenizer::Errors::Base& err) {
            Slice<int> absolute = p.tokens.toAbsolute(err.view);
            qDebug() << absolute << err.pos;
            qDebug() << info.whichLine(absolute.first + err.pos)
                     << info.whichColumn(absolute.first + err.pos)
                     << err.what();
            throw;
        }
    }

    QString csvOutput;
    QString tableOutput;
    QString annotatedOutput;

    int       index          = 0;
    const int cutoff         = 6000;
    auto      writeAnnotated = [&]() {
        QString htmlDoc = R"(
<!DOCTYPE html>
<html>
<style>
html * { font-family: Iosevka !important; }
/* Tooltip container */
.tooltip {
  position: relative;
  display: inline-block;
  border-left: 1px dotted black;
}

/* Tooltip text */
.tooltip .tooltiptext {
  visibility: hidden;
  width: max-content;
  background-color: black;
  color: #fff;
  text-align: left;
  padding: 5px 0;
  border-radius: 6px;

  /* Position the tooltip text - see examples below! */
  position: absolute;
  z-index: 1;
}

/* Show the tooltip text when you mouse over the tooltip container */
.tooltip:hover .tooltiptext {
  visibility: visible;
}
</style>
<body>
<pre>
$#
</pre>
</body>
</html>
)";
        writeFile(
            ("/tmp/annotated_$#.html" % to_string_vec(index / cutoff))
                .toStdString(),
            htmlDoc % to_string_vec(annotatedOutput));
    };

    auto writeHtml = [&]() {
        QString htmlDoc = R"(
<!DOCTYPE html>
<html>
<style>
html * { font-family: Iosevka !important; }
table, th, td { border: 1px solid black; padding: 0; margin: 0; }
td { line-height: 0; }
th {
  background: white;
  position: sticky;
  top: 0; /* Don't forget this, required for the stickiness */
  box-shadow: 0 2px 2px -1px rgba(0, 0, 0, 0.4);
}
</style>
<body>
<table>
<tr>
  <th>Pushed on</th>
  <th>Index</th>
  <th>Slice</th>
  <th>Line</th>
  <th>Column</th>
  <th>Kind</th>
  <th>Text</th>
</tr>
$#
</table>
</body>
</html>)";

        // qDebug() << index;
        writeFile(
            ("/tmp/table_$#.html" % to_string_vec(index / cutoff))
                .toStdString(),
            htmlDoc % to_string_vec(tableOutput));
        tableOutput = "";
    };

    for (const auto& [id, token] : p.tokens.tokens.pairs()) {
        if (pushedOn.contains(id)) {
            bool hasStr = token->hasData();

            Slice<int> absolute = hasStr
                                    ? p.tokens.toAbsolute(token->getText())
                                    : slice(-1, -1);

            int  line   = hasStr ? info.whichLine(absolute.first) : -1;
            int  column = hasStr ? info.whichColumn(absolute.first) : -1;
            auto rep    = pushedOn.at(id);

            auto formatting = to_string_vec(
                rep.line,
                id.getIndex(),
                absolute,
                line,
                column,
                token->kind,
                token->strVal());

            csvOutput += "$#\t$#\t$#\t$#\t$#\t$#\t$#\n" % formatting;
            tableOutput += R"(
<tr>
<td><pre>$#</pre></td>
<td><pre>$#</pre></td>
<td><pre>$#</pre></td>
<td><pre>$#</pre></td>
<td><pre>$#</pre></td>
<td><pre>$#</pre></td>
<td><pre>$#</pre></td>
</tr>
)" % formatting;

            // annotatedOutput += token->strVal();
            if (hasStr || true) {
                QString special = "⩨";
                switch (token->kind) {
                    case otk::GroupStart: special = "⋖"; break;
                    case otk::GroupEnd: special = "⋗"; break;
                    case otk::StmtListOpen: special = "⟦"; break;
                    case otk::StmtListClose: special = "⟧"; break;
                    case otk::ParagraphStart: special = "⟪"; break;
                    case otk::ParagraphEnd: special = "⟫"; break;
                    case otk::ListItemStart: special = "⁅"; break;
                    case otk::ListItemEnd: special = "⁆"; break;
                    case otk::SameIndent: special = "⫩"; break;
                    case otk::Indent: special = "⫧"; break;
                    case otk::Dedent: special = "⫨"; break;
                }


                annotatedOutput
                    += "<span title=\"$#\" style=\"$#\">$#</span>"
                     % to_string_vec(
                           R"(pushed=$#
index=$#
absolute=$#
line=$#
column=$#
kind=$#
)" % formatting,
                           hasStr ? "" : "foreground-color:gray",
                           hasStr ? token->strVal().replace("\n", "␤\n")
                                  : special);
            }

            ++index;
            if (index % cutoff == 0) {
                writeHtml();
                writeAnnotated();
            }

        } else {
            qWarning() << "Token " << *token << " with id " << id
                       << " was not pushed using reporting";
        }
    }

    index += cutoff;
    writeHtml();
    writeAnnotated();
    writeFile("/tmp/tokens.csv", csvOutput);

    writeFile(
        "/tmp/file_parsed.yml", to_string(yamlRepr(p.tokens)) + "\n");
}


TEST_CASE("Parse corpus", "[corpus]") {
    std::string glob = testParameters.corpusGlob.toStdString();
    for (fs::directory_entry const& path :
         fs::recursive_directory_iterator(
             __CURRENT_FILE_DIR__ / "corpus")) {

        if (path.is_regular_file()) {
            if (testParameters.corpusGlob.empty()) {
                YAML::Node spec = YAML::LoadFile(path.path());
                runSpec(spec, QString::fromStdString(path.path()));
            } else {
                std::string path_str = path.path();
                int         matchRes = fnmatch(
                    glob.c_str(), path_str.c_str(), FNM_EXTMATCH);
                if (!(matchRes == FNM_NOMATCH)) {
                    YAML::Node spec = YAML::LoadFile(path.path());
                    runSpec(spec, QString::fromStdString(path.path()));
                }
            }
        }
    }
};
