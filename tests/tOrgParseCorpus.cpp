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

            HDisplayOpts opts{};
            opts.flags.excl(HDisplayFlag::UseQuotes);
            return "$# $# $#"
                 % to_string_vec(
                       id,
                       tok.kind,
                       hshow(tok.strVal(), opts).toString(false),
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
        // qDebug() << sectionName(spec);
        SECTION(sectionName(spec)) { runSpec(spec, from); }
    }
}

struct NodeOperations {
    UnorderedMap<OrgId, OrgParser::Report> started, ended, pushed;
};


const QString mainDoc = R"RAW(
<!DOCTYPE html>
<html>
<head>
<script>
  function collapse(cell) {
    var row = cell.parentElement;
    for (i = row.rowIndex + 1; i < row.parentElement.children.length; ++i) {
      var target_row = row.parentElement.children[i];
      if (target_row.style.display == 'table-row') {
        cell.innerHTML = '+';
        target_row.style.display = 'none';
      } else {
        cell.innerHTML = '-';
        target_row.style.display = 'table-row';
      }
    }
  }

  function selectAndHighlightRange(id, start, end) {
    const preElement = document.getElementById(id);
    const textContent = preElement.textContent;

    if (start < 0 || textContent.length <= end) {
      console.error("Invalid range.");
      return;
    }

    const beforeHighlight = textContent.substring(0, start - 1);
    const highlightedText = textContent.substring(start - 1, end);
    const afterHighlight = textContent.substring(end);

    preElement.innerHTML = `$${beforeHighlight}<span class="highlight">$${highlightedText}</span>$${afterHighlight}`;
  }

</script>
<style>
  * { font-family: Iosevka; }
  .collapseButton { vertical-align: text-top; }
  th, td {
    padding: 0em;
    text-align: right;
    // outline: 1px dotted #00000055;
  }
  td.padding_fill { background-color: red; }
  .Table { margin-left: 0em; margin-top: 0em; margin-right: 0em; }
  table {
    border-collapse: collapse;
    outline: 1px solid;
  }
  .highlight { background-color: yellow; }
  table table {
    width: auto;
    margin-left: auto;
    margin-right: 0;
    display: table;

    // margin-top: 4px;
    // margin-bottom: 4px;
  }

${headerWidths}
  th.button { min-width: 10; width: 10px; }
  th.inner_content { visibility: hidden; height: 0; }
  table th, td {
    text-align: left;
    // padding: 4px;
  }
  #collapseButton:hover { background-color: red; }
</style>
</head>
<body>
  <table>
    <tr>
      <td>
        <table>
          <tr>
            <th></th>
            <th style="min-width:${width}px; width:${width}px;"></th>
${headerRows}
          </tr>
${table}
        </table>
      </td>
      <td style="vertical-align:top;">
        <pre id="target">
${text}
        </pre>
      </td>
    <tr>
  </table>
</body>
</html>
)RAW";


const QString tokenTable = R"RAW(
<tr id="hidden"> <!-- From token node -->
  <td colspan=${colspan}>
    <table>
      <tr>
        <th style="width:0px;"></th>
${headerRows}
      </tr>
      <tr>
        <td class="padding_fill"></td>
        <td>${index}</td>
        <td>${kind}</td>
        <td>${subnodeName}</td>
        <td>${value}</td>
        <td>${record}</td>
        ${range}
      </tr>
    </table>
  </td>
</tr>
)RAW";

const QString nestedTable = R"RAW(
<tr id="hidden"> <!-- Main nested table content row -->
  <td colspan=${colspan}>
    <!-- From nested node, index=${index}, level=${level} -->
    <table>
      <tr> <!-- Nested table header -->
        <th class="button"></th>
        <th style="width:${width}px;" class="padding_fill"></th>
        ${headerRows}
      </tr>
      <tr> <!-- First nested table row -->
        <td id="collapseButton" onclick="collapse(this)">+</td>
        <td class="padding_fill"></td>
        <td>${index}</td>
        <td>${kind}</td>
        <td>${subnodeName}</td>
        <td></td>
        <td>${record}</td>
        ${range}
      </tr>
      <tr> <!-- Nested table content row -->
        <td colspan="${colspan}">
          <table>
<!-- START Nested nodes for subtree -->
${nested}
<!-- END Nested nodes for subtree -->
          </table>
        </td>
      </tr>
    </table>
  </td>
</tr>
)RAW";


QString htmlRepr(
    CR<OrgId>          root,
    CR<OrgNodeGroup>   nodes,
    CR<QString>        src,
    CR<NodeOperations> ops) {
    struct Result {
        int     level;
        QString content;
    };

    auto getTokTextRange = [&](CR<OrgTokenId> tokId) -> Opt<Slice<int>> {
        OrgToken const& tok = nodes.tokens->at(tokId);
        if (tok.hasData()) {
            return nodes.tokens->toAbsolute(tok.getText());
        } else {
            return std::nullopt;
        }
    };

    auto getNodeTextRange = [&](CR<OrgId> id) -> Opt<Slice<int>> {
        if (nodes.at(id).isTerminal()) {
            OrgTokenId tokId = nodes.at(id).getToken();
            return getTokTextRange(tokId);
        } else {
            return std::nullopt;
        }
    };

    auto getRangeClick = [&](CR<Opt<int>> textStart,
                             CR<Opt<int>> textEnd,
                             CR<QString>  text) -> QString {
        return (textStart.has_value() && textEnd.has_value())
                 ? R"html(<td onclick="selectAndHighlightRange('target', $1, $2)">[$1..$2]$3</td>)html"
                       % to_string_vec(*textStart, *textEnd, text)
                 : "<td>none$#</td>" % to_string_vec(text);
    };

    const int dataColNum  = 6;
    const int baseColspan = dataColNum + 1;

    Func<Result(CR<OrgId>, Opt<Str>, int)> aux;
    aux = [&](CR<OrgId> root,
              Opt<Str>  subnodeName,
              int       indexInParent) -> Result {
        QString headerRows;
        for (int i = 0; i < dataColNum; ++i) {
            headerRows += (R"(<th class="content$#"></th>)"
                           "\n")
                        % to_string_vec(to_string(i));
        }

        if (nodes.at(root).isTerminal()
            || nodes.at(root).kind == org::Empty) {

            Opt<Slice<int>> textRange = getNodeTextRange(root);
            Opt<int>        first, last;
            if (textRange) {
                first = textRange->first;
                last  = textRange->last;
            }

            QString record = "<none>";
            if (ops.pushed.contains(root)) {
                record = "@" + to_string(ops.pushed.at(root).line);
            }

            auto table = tokenTable
                       % fold_format_pairs({
                           {"range", getRangeClick(first, last, "")},
                           {"headerRows", headerRows},
                           {"colspan", to_string(baseColspan)},
                           {"index",
                            "$# [$#]"
                                % to_string_vec(
                                    root.getIndex(), indexInParent)},
                           {"kind", to_string(nodes.at(root).kind)},
                           {"subnodeName",
                            "$#"
                                % to_string_vec(
                                    subnodeName.value_or("?"))},
                           {"record", record},
                           {"value",
                            to_string(
                                nodes.strVal(root).replace("\n", "␤"))},
                           {"start", to_string(0)},
                           {"end", to_string(1)},
                       });

            return {.level = 1, .content = table};
        } else {
            Vec<Result> sub;
            auto [begin, end] = nodes.subnodesOf(root);
            int index         = 0;
            for (; begin != end; ++begin) {
                sub.push_back(
                    aux(*begin,
                        spec.fieldName(OrgAdapter(&nodes, root), index),
                        index));
                ++index;
            }

            QString nested;
            int     level = 0;
            for (const auto& it : sub) {
                nested += it.content + "\n";
                level = std::max(it.level, level);
            }


            Slice<OrgId> allsub = nodes.allSubnodesOf(root);
            Opt<int>     textStart;
            Opt<int>     textEnd;

            QString record;
            if (ops.started.contains(root) && ops.ended.contains(root)) {
                record = "+@$#/-@$#"
                       % to_string_vec(
                             ops.started.at(root).line,
                             ops.ended.at(root).line);
            } else {
                record = "<none>";
            }


            for (const auto& id : allsub) {
                if (nodes.at(id).isTerminal()) {
                    auto absolute = getNodeTextRange(id);
                    if (absolute.has_value()) {
                        if (!textStart) {
                            textStart = absolute->first;
                        }

                        textEnd = absolute->last;
                    }
                }
            }

            auto table = nestedTable
                       % fold_format_pairs({
                           {"headerRows", headerRows},
                           {"range",
                            getRangeClick(
                                textStart,
                                textEnd,
                                ", $#..$#"
                                    % to_string_vec(
                                        allsub.first.getIndex(),
                                        allsub.last.getIndex()))},
                           {"width", to_string(level * 10)},
                           {"subnodeName",
                            "$#"
                                % to_string_vec(
                                    subnodeName.value_or("?"))},
                           {"colspan", to_string(baseColspan + level)},
                           {"index",
                            "$# [$#]"
                                % to_string_vec(
                                    root.getIndex(), indexInParent)},
                           {"kind", to_string(nodes.at(root).kind)},
                           {"nested", nested},
                           {"record", record},
                           {"level", to_string(level)},
                           {"extentStart",
                            to_string(allsub.first.getIndex())},
                           {"extentEnd",
                            to_string(allsub.last.getIndex())},
                       });

            return Result{.level = level + 1, .content = table};
        }
    };

    Result  top       = aux(root, std::nullopt, 0);
    QString mainTable = top.content;


    QString headerWidths;


    auto v = Vec<int>{100, 100, 100, 150, 150, 150};
    for (const auto& [idx, width] : enumerate(v)) {
        qDebug() << idx << width;
        headerWidths.push_back(
            (R"(th.content$1 { min-width: $2px; width: $2px; })"
             "\n")
            % to_string_vec(idx, width));
    }

    std::vector<QString> res;
    for (int i = 0; i < dataColNum; ++i) {
        res.push_back(to_string(i));
    }

    QString headerRows = repeat(
                             (R"(<th class="content$#">$$#</th>)"
                              "\n"),
                             dataColNum)
                       % res;

    return mainDoc
         % fold_format_pairs({
             {"width", to_string(top.level * 10)},
             {"table", mainTable},
             {"headerWidths", headerWidths},
             {"headerRows",
              headerRows
                  % to_string_vec(
                      "Index", "Kind", "Name", "Text", "Pushed", "Range")},
             {"text", src},
         });
}


TEST_CASE("Parse file", "[corpus][notes]") {
    MockFull p;
    // QString  source = readFile(
    //     "/mnt/workspace/repos/personal/indexed/notes.org");
    QString source = readFile("/tmp/doc.org");

    p.tokenizer.setTraceFile("/tmp/file_lex_trace.txt");
    p.setTraceFile("/tmp/file_parse_trace.txt");

    p.tokens.base = source.data();
    LineColInfo info{source};
    p.tokenizer.locationResolver = [&](CR<PosStr> str) -> LineCol {
        Slice<int> absolute = p.tokens.toAbsolute(str.view);
        return {
            info.whichLine(absolute.first + str.pos) + 1,
            info.whichColumn(absolute.first + str.pos),
        };
    };

    p.locationResolver = p.tokenizer.locationResolver;

    int  start  = 430;
    auto target = slice(start, start + 100);

    p.tokenizer.traceUpdateHook =
        [&](CR<OrgTokenizer::Report> in, bool& doTrace, bool first) {
            if (in.str != nullptr) {
                LineCol loc = p.tokenizer.locationResolver(*(in.str));
                if (target.contains(loc.line)) {
                    if (in.kind == OrgTokenizer::ReportKind::Push) {
                        if (in.addBuffered) {
                            doTrace = !first;
                        }
                    } else {
                        doTrace = true;
                    }
                } else if (loc.line != -1) {
                    doTrace = false;
                }
            }
        };

    p.traceUpdateHook =
        [&](CR<OrgParser::Report> in, bool& doTrace, bool first) {
            if (in.node.has_value()) {
                OrgId node = in.node.value();
                if (p.nodes.at(node).isTerminal()) {
                    auto tok = p.tokens.at(p.nodes.at(node).getToken());
                    if (tok.hasData()) {
                        LineCol loc = p.tokenizer.locationResolver(
                            tok.getText());
                        if (loc.line != -1) {
                            doTrace = target.contains(loc.line);
                        }
                    }
                }
            }
        };

    UnorderedMap<OrgTokenId, OrgTokenizer::Report> pushedOn;
    NodeOperations                                 ops;

    using R = OrgTokenizer::ReportKind;

    p.reportHook = [&](CR<OrgParser::Report> report) {
        using R = OrgParser::ReportKind;
        switch (report.kind) {
            case R::StartNode: ops.started[*report.node] = report; break;
            case R::EndNode: ops.ended[*report.node] = report; break;
            case R::AddToken: ops.pushed[*report.node] = report; break;
        }
    };

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
table, th, td { padding: 0; margin: 0; }
td { line-height: 0; outline: 1px dashed; }
th {
  margin: 0;
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
        "/tmp/file_lexed.yaml", to_string(yamlRepr(p.tokens)) + "\n");

    qDebug() << "Lex ok";
    p.parse(&OrgParser::parseTop);

    qDebug() << "Top parse";
    writeFile(
        "/tmp/file_parsed.yaml", to_string(yamlRepr(p.nodes)) + "\n");
    qDebug() << "Wrote parsed representation into yaml";

    writeFile(
        "/tmp/parsed_tree.html", htmlRepr(OrgId(0), p.nodes, source, ops));

    qDebug() << "Wrote parsed tree representation";
    SUCCEED("Parsed input corpus file");
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
