#include "haxorgcli.hpp"

#include <lexbase/NodeIO.hpp>
#include <exporters/ExporterJson.hpp>
#include <QElapsedTimer>
#include <parse/OrgSpec.hpp>
#include <sem/ErrorWrite.hpp>
#include <exporters/exporterdot.hpp>
#include <exporters/exportertree.hpp>
#include <exporters/exportergantt.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exporterhtml.hpp>
#include <exporters/exporterqtextdocument.hpp>
#include <exporters/exportersimplesexpr.hpp>
#include <exporters/exporterlatex.hpp>
#include <exporters/exportereventlog.hpp>
#include <annotators/annotatorspelling.hpp>
#include <exporters/exportersubtreestructure.hpp>
#include <exporters/exportermindmap.hpp>
#include <exporters/exporternlp.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>
#include <QGuiApplication>
#include <perfetto.h>
#include <hstd/stdlib/algorithms.hpp>


using org = OrgNodeKind;
using otk = OrgTokenKind;

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
    CR<OrgId>                     root,
    CR<OrgNodeGroup>              nodes,
    CR<QString>                   src,
    CR<HaxorgCli::NodeOperations> ops) {
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

    auto spec = getOrgSpec();

    Func<Result(CR<OrgId>, Opt<OrgSpecName>, int)> aux;
    aux = [&](CR<OrgId>        root,
              Opt<OrgSpecName> subnodeName,
              int              indexInParent) -> Result {
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
                                % to_string_vec(subnodeName.value_or(
                                    OrgSpecName::Unnamed))},
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
            auto [begin, end] = nodes.subnodesOf(root).value();
            int index         = 0;
            for (; begin != end && (begin.id <= end.id); ++begin) {
                sub.push_back(
                    aux(*begin,
                        spec->fieldName(OrgAdapter(&nodes, root), index),
                        index));
                ++index;
            }

            QString nested;
            int     level = 0;
            for (const auto& it : sub) {
                nested += it.content + "\n";
                level = std::max(it.level, level);
            }


            Opt<Slice<OrgId>> allsub = nodes.allSubnodesOf(root);

            Opt<int> textStart;
            Opt<int> textEnd;

            QString record;
            if (ops.started.contains(root) && ops.ended.contains(root)) {
                record = "+@$#/-@$#"
                       % to_string_vec(
                             ops.started.at(root).line,
                             ops.ended.at(root).line);
            } else {
                record = "<none>";
            }


            if (allsub.has_value()) {
                for (const auto& id : allsub.value()) {
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
            }

            auto table = nestedTable
                       % fold_format_pairs({
                           {"headerRows", headerRows},
                           {"range",
                            getRangeClick(
                                textStart,
                                textEnd,
                                allsub
                                    ? (", $#..$#"
                                       % to_string_vec(
                                           allsub->first.getIndex(),
                                           allsub->last.getIndex()))
                                    : QString(""))},
                           {"width", to_string(level * 10)},
                           {"subnodeName",
                            "$#"
                                % to_string_vec(subnodeName.value_or(
                                    OrgSpecName::Unnamed))},
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
                            allsub ? to_string(allsub->first.getIndex())
                                   : QString("")},
                           {"extentEnd",
                            allsub ? to_string(allsub->last.getIndex())
                                   : QString("")},
                       });

            return Result{.level = level + 1, .content = table};
        }
    };

    Result  top       = aux(root, std::nullopt, 0);
    QString mainTable = top.content;


    QString headerWidths;


    auto v = Vec<int>{100, 100, 100, 150, 150, 200};
    for (const auto& [idx, width] : enumerate(v)) {
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


void writeAnnotated(
    QFileInfo const& file,
    QString const&   annotatedOutput) {
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
    writeFile(file, htmlDoc % to_string_vec(annotatedOutput));
};

void writeHtml(QFileInfo const& file, QString const& tableOutput) {
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

    writeFile(file, htmlDoc % to_string_vec(tableOutput));
};


void fillTokenGroups(
    OrgTokenGroup const&                                  tokens,
    UnorderedMap<OrgTokenId, OrgTokenizer::Report> const& pushedOn,
    QString&                                              tableOutput,
    QString&                                              csvOutput,
    QString&                                              annotatedOutput,
    LineColInfo const&                                    info) {

    for (const auto& [id, token] : tokens.tokens.pairs()) {
        if (pushedOn.contains(id)) {
            bool hasStr = token->hasData();

            Slice<int> absolute = hasStr
                                    ? tokens.toAbsolute(token->getText())
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

        } else {
            qWarning() << "Token " << *token << " with id " << id
                       << " was not pushed using reporting";
        }
    }
}

void HaxorgCli::initLocationResolvers() {
    locationResolver = [&](CR<PosStr> str) -> LineCol {
        Slice<int> absolute = tokens.toAbsolute(str.view);
        return {
            info.whichLine(absolute.first + str.pos) + 1,
            info.whichColumn(absolute.first + str.pos),
            absolute.first + str.pos,
        };
    };

    converter.locationResolver = locationResolver;
    tokenizer->setLocationResolver(locationResolver);
    parser->setLocationResolver(locationResolver);
}

void HaxorgCli::initTracers() {
    if (config.trace.lex.doTrace) {
        tokenizer->trace = true;
        if (config.trace.lex.traceTo.has_value()) {
            Q_ASSERT(
                config.trace.lex.traceTo.value()
                    .absoluteFilePath()
                    .length()
                != 0);
            tokenizer->setTraceFile(config.trace.lex.traceTo.value());
        }

        tokenizer->setTraceUpdateHook(
            [&](CR<OrgTokenizer::Report> in, bool& doTrace, bool first) {
                if (in.str != nullptr) {
                    LineCol loc = locationResolver(*(in.str));
                    if (config.trace.lex.traceExtent.contains(loc.line)) {
                        // if (in.kind == OrgTokenizer::ReportKind::Push) {
                        //     if (in.addBuffered) {
                        //         doTrace = !first;
                        //     }
                        // } else {
                        // }
                        doTrace = true;
                    } else if (loc.line != -1) {
                        doTrace = false;
                    }
                }
            });
    }

    if (config.trace.parse.doTrace) {
        parser->trace = true;
        if (config.trace.parse.traceTo.has_value()) {
            parser->setTraceFile(config.trace.parse.traceTo.value());
        }

        parser->setTraceUpdateHook(
            [&](CR<OrgParser::Report> in, bool& doTrace, bool first) {
                if (in.node.has_value()) {
                    OrgId node = in.node.value();
                    if (nodes.at(node).isTerminal()) {
                        auto tok = tokens.at(nodes.at(node).getToken());
                        if (tok.hasData()) {
                            LineCol loc = locationResolver(tok.getText());
                            if (loc.line != -1) {
                                doTrace = config.trace.parse.traceExtent
                                              .contains(loc.line);
                            }
                        }
                    }
                }
            });
    }
}

#ifdef USE_PERFETTO
#    define __trace(name) TRACE_EVENT("cli", name)
#else
#    define __trace(a)
#endif


bool HaxorgCli::runTokenizer(bool catchExceptions) {
    __trace("tokenize file");
    if (!catchExceptions) {
        tokenizer->lexGlobal(*str);
        return true;
    } else {
        Id inId = 0;

        try {
            tokenizer->lexGlobal(*str);
            return true;
        } catch (OrgTokenizer::TokenizerError& err) {
            QStringView  view = err.getView();
            Opt<LineCol> loc  = err.getLoc();
            int          pos  = err.getPos();
            using E           = OrgTokenizer::Errors;

            auto msg = QString(std::visit(
                overloaded{
                    [](E::UnexpectedChar const&) -> QString {
                        return "UnexpectedChar"_qs;
                    },
                    [](E::UnexpectedConstruct const&) -> QString {
                        return "UnexpectedConstruct"_qs;
                    },
                    [](E::UnknownConstruct const&) -> QString {
                        return "UnknownConstruct"_qs;
                    },
                    [](E::MissingElement const&) -> QString {
                        return "MissingElement"_qs;
                    },
                    [](E::None const&) -> QString { return "None"_qs; },
                    [](const auto& it) -> QString { return ""_qs; }},
                err.err));

            auto r = Report(ReportKind::Error, inId, pos - 1)
                         .with_message(QString(err.what()))
                         .with_code("03")
                         .with_label(
                             Label(std::make_shared<TupleCodeSpan>(
                                       inId, slice(pos - 1, pos - 1)))
                                 .with_message(msg));

            r.write(sources, qcout);
            return false;
        }
    }
}

Opt<LineCol> approximateLocation(
    Func<LineCol(PosStr const&)> locationResolver,
    OrgTokenId                   id,
    OrgTokenGroup const&         tokens) {
    for (int offset = 0; tokens.tokens.contains(id + (-offset))
                         || tokens.tokens.contains(id + offset);
         ++offset) {
        for (int direction : Vec{-1, 1}) {
            auto shifted = id + (offset * direction);
            if (tokens.tokens.contains(shifted)) {
                OrgToken tok = tokens.tokens.at(shifted);
                if (tok.hasData()) {
                    PosStr str{tok.getText()};
                    return locationResolver(str);
                }
            }
        }
    }

    return std::nullopt;
}

void HaxorgCli::writeYamlLex() {
    __trace("Convert lex to yaml");
    yaml result;
    for (const auto& [id, token] : tokens.tokens.pairs()) {
        yaml item = yamlRepr(id, *token, true);
        if (pushedOn.contains(id)) {
            OrgTokenizer::Report const& rep = pushedOn.at(id);
            yaml                        pushed;
            pushed["line"] = rep.line;
            pushed["func"] = rep.name.toBase();
            item["pushed"] = pushed;
        }

        if (auto loc = approximateLocation(locationResolver, id, tokens);
            loc.has_value()) {
            yaml location;
            location["line"]   = loc->line;
            location["column"] = loc->column;
            location["pos"]    = loc->pos;
            item["loc"]        = location;
        }

        result.push_back(item);
    }

    auto file = "/tmp/lexed_output.yaml";
    writeFile(QFileInfo(file), to_string(result) + "\n");
    qInfo() << "Wrote YAML lex representation into " << file;
}

void HaxorgCli::writeYamlParse() {
    __trace("Convert parse to yaml");
    writeFile(config.outFile, to_string(yamlRepr(nodes)) + "\n");
    qInfo() << "Wrote YAML parse representation into " << config.outFile;
}

void HaxorgCli::writeTreeParse() {
    __trace("Write out tree repr for the parsed tree");
    writeFile(QFileInfo("/tmp/parsed_tree.txt"), nodes.treeRepr(OrgId(0)));
}

void HaxorgCli::writeJsonParse() {
    __trace("Convert parse to json");
    writeFile(config.outFile, to_string(jsonRepr(nodes)) + "\n");
    qInfo() << "Wrote JSON parse representation into " << config.outFile;
}

void HaxorgCli::writeJson() {
    __trace("Export json");
    ExporterJson exporter;
    json         result = exporter.visitTop(node);

    writeFile(QFileInfo("/tmp/result.json"), to_string(result));
    qDebug() << "Json repr ok";
}

void HaxorgCli::writeYaml() {
    __trace("Export yaml");
    ExporterYaml  exporter;
    yaml          result = exporter.visitTop(node);
    std::ofstream of{"/tmp/result.yaml"};
    of << result;
    qDebug() << "Yaml OK";
}

void HaxorgCli::writeQDocument() {
    __trace("Export QDocument");
    int   argc = 0;
    char* argv = "";

    QGuiApplication       app(argc, &argv);
    ExporterQTextDocument exporter;
    exporter.visitTop(node);
    writeFile(
        QFileInfo("/tmp/qt_document.md"), exporter.document->toMarkdown());
    writeFile(
        QFileInfo("/tmp/qt_document.html"), exporter.document->toHtml());
    writeFile(
        QFileInfo("/tmp/qt_document.txt"), exporter.document->toRawText());
}

void HaxorgCli::writeSimpleSExpr() {
    __trace("Export S-expresions");
    ExporterSimpleSExpr exporter;
    layout::Block::Ptr  result = exporter.visitTop(node);
    QString formatted = exporter.store.toString(result, layout::Options{});
    writeFile(QFileInfo("/tmp/result.lisp"), formatted);
}

void HaxorgCli::writeHtml() {
    __trace("Export HTML");
    ExporterHtml       exporter;
    layout::Block::Ptr result = exporter.visitTop(node);
    QString formatted = exporter.store.toString(result, layout::Options{});
    writeFile(QFileInfo("/tmp/result.html"), formatted);
}

void HaxorgCli::writeGantt() {
    __trace("Export gantt");
    ExporterGantt gantt;
    gantt.gantt.timeSpan = slice(QDateTime(), QDateTime());
    gantt.visitTop(node);

    writeFile(QFileInfo("/tmp/gantt.puml"_qs), gantt.gantt.toString());
    writeFile(
        QFileInfo("/tmp/gantt.json"_qs), to_string(gantt.gantt.toJson()));
}


HaxorgCli::HaxorgCli()
    : tokenizer()
    , nodes(nullptr)
    , lex(&tokens)
    , converter(sem::OrgConverter(&store)) {
    nodes.tokens = &tokens;
}


void HaxorgCli::exec() {
    //    InitializePerfetto();
    //    auto tracing_session = StartTracing();

    {
        __trace("read file");
        source      = readFile(config.sourceFile);
        tokens.base = source.data();
        info        = LineColInfo{source};
    }

    parser    = OrgParser::initImpl(&nodes, config.trace.parse.doTrace);
    tokenizer = OrgTokenizer::initImpl(&tokens, config.trace.lex.doTrace);
    tokenizer->reserve(source.size() / 3);
    parser->reserve(source.size() / 3);


    initLocationResolvers();
    initTracers();


    using R = OrgTokenizer::ReportKind;

    using Target = HaxorgCli::Config::Target;

    if (config.target == Target::HtmlParse) {
        parser->setReportHook([&](CR<OrgParser::Report> report) {
            using R = OrgParser::ReportKind;
            switch (report.kind) {
                case R::StartNode:
                    ops.started[*report.node] = report;
                    break;
                case R::EndNode: ops.ended[*report.node] = report; break;
                case R::AddToken: ops.pushed[*report.node] = report; break;
            }
        });
    }

    bool const writeLexInfo = config.target == Target::AnnotatedLex
                           || config.target == Target::CsvLex
                           || config.target == Target::HtmlLex;

    if (writeLexInfo) {
        tokenizer->setReportHook([&](CR<OrgTokenizer::Report> report) {
            switch (report.kind) {
                case R::Push: {
                    pushedOn[report.id] = report;
                    break;
                }
            }
        });
    }

    str     = std::make_shared<PosStr>(source);
    Id inId = 0;
    sources.add(inId, source, config.sourceFile.fileName());

    {
        __trace("Tokenize");
        if (!runTokenizer(false)) {
            return;
        }
        //        writeYamlLex();
    }

    {
        __trace("Write tokenized output");
        if (config.target == Target::YamlLex) {
            writeYamlLex();
            return;
        } else if (config.target == Target::JsonLex) {
            writeFile(config.outFile, to_string(jsonRepr(tokens)) + "\n");
            qInfo() << "Wrote JSON lex representation into "
                    << config.outFile;
            return;
        } else if (writeLexInfo) {
            QString table;
            QString csv;
            QString annotated;
            fillTokenGroups(tokens, pushedOn, table, csv, annotated, info);
            switch (config.target) {
                case Target::CsvLex: {
                    writeFile(config.outFile, csv);
                    return;
                }
                case Target::AnnotatedLex: {
                    writeAnnotated(config.outFile, annotated);
                    return;
                }
                case Target::HtmlLex: {
                    ::writeHtml(config.outFile, table);
                    return;
                }
            }
        }
    }

    {
        __trace("Parse");
        {
            __trace("parse lexed tokens");
            parser->parseTop(lex);
        }
        {
            __trace("Extend subtree trails");
            parser->extendSubtreeTrails(OrgId(0));
        }
        {
            __trace("Convert attached trails");
            parser->extendAttachedTrails(OrgId(0));
        }
    }


    {
        __trace("Write parsed output");
        if (config.target == Target::YamlParse) {
            writeYamlParse();
            return;
        } else if (config.target == Target::JsonParse) {
            writeJsonParse();
            return;
        } else if (config.target == Target::HtmlParse) {
            QString repr = htmlRepr(OrgId(0), nodes, source, ops);
            writeFile(config.outFile, repr);
            return;
        }
    }

    //    writeTreeParse();

    {
        if (config.trace.sem.doTrace) {
            converter.trace = true;
            if (config.trace.sem.traceTo) {
                converter.setTraceFile(config.trace.sem.traceTo.value());
            }
        }

        {
            __trace("convert parse to sem");
            node = converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
            qInfo() << "Finished conversion";
        }

        Vec<Pair<OrgSemKind, int>> counts;


        store.eachStore([&](sem::SemId::StoreIndexT     selfIndex,
                            sem::OrgKindStorePtrVariant store) {
            std::visit(
                [&](auto it) {
                    counts.push_back({
                        std::remove_reference_t<
                            decltype(*it)>::NodeType::staticKind,
                        it->size(),
                    });
                },
                store);
        });

        sort<Pair<OrgSemKind, int>>(
            counts,
            [](Pair<OrgSemKind, int> const& lhs,
               Pair<OrgSemKind, int> const& rhs) -> bool {
                return lhs.second < rhs.second;
            });

        for (const auto& [kind, count] : counts) {}

        {
            ExporterEventLog exporter;
            using Ev = ExporterEventLog::Event;
            UnorderedMap<Ev::Kind, Vec<Ev>> events;

            exporter.logConsumer = [&](ExporterEventLog::Event const& ev) {
                events[ev.getKind()].push_back(ev);
            };

            exporter.visitTop(node);
            qDebug() << "Log consumer done";
        }

        {
            ExporterMindMap exporter;
            exporter.visitTop(node);

            writeFile(
                QFileInfo("/tmp/mindmap_tree.json"_qs),
                to_string(exporter.toJsonTree()));

            writeFile(
                QFileInfo("/tmp/mindmap_graph.json"_qs),
                to_string(exporter.toJsonGraph()));
        }

        {
            ExporterSubtreeStructure exporter;
            json                     result = exporter.visitTop(node);
            writeFile(
                QFileInfo("/tmp/subtree-hierarhcy.json"),
                to_string(result));
        }

        { writeGantt(); }
        //        { writeJson(); }
        //        { writeYaml(); }


        {
            __trace("Export Latex");
            ExporterLatex exporter;
            exporter.subTocForAndAbove(ExporterLatex::SubtreeCmd::section);
            OperationsTracer trace{QFileInfo("/tmp/latex_export_trace")};
            [&](ExporterLatex::VisitEvent const& ev) {
                using K = typename ExporterLatex::VisitEvent::Kind;
                if (((ev.kind == K::PushVisit || ev.kind == K::VisitStart)
                     && !ev.isStart)
                    || ((ev.kind == K::PopVisit || ev.kind == K::VisitEnd)
                        && ev.isStart)) {
                    return;
                }

                auto os = trace.getStream();


                os << os.indent(ev.level * 2) << (ev.isStart ? ">" : "<")
                   << " " << to_string(ev.kind);

                if (ev.visitedNode) {
                    os << " node:" << to_string(ev.visitedNode->getKind());
                }

                if (0 < ev.field.length()) {
                    os << " field:" << ev.field;
                }

                os << " on " << QFileInfo(ev.file).fileName() << ":"
                   << ev.line << " " << ev.function << " " << os.end();

                if (0 < ev.type.length()) {
                    os << " type:" << demangle(ev.type.toLatin1());
                }

                trace.endStream(os);
            };

            layout::Block::Ptr result    = exporter.visitTop(node);
            QString            formatted = exporter.store.toString(
                result, layout::Options{});
            writeFile(QFileInfo("/tmp/result.tex"), formatted);
            qDebug() << "Latex output ok";
        }

        if (true) {
            __trace("Mind map exporter");
            ExporterMindMap exporter;
            exporter.visitTop(node);
            exporter.toGraph();
            writeFile(
                QFileInfo("/tmp/mindmap.json"_qs),
                QString::fromStdString(to_compact_json(
                    exporter.toJsonGraph(), {.width = 160})));
            qDebug() << "Mind map export ok";
        }

        if (false) {
            using namespace NLP::builder;

            __trace("Exporter NLP");
            ExporterNLP nlp{QUrl("http://localhost:9000")};
            nlp.visitTop(node);
            nlp.executeRequests();
            nlp.waitForRequests();
            auto trees = nlp.findMatches(
                rel::Dir(Tag("VBN"), Tag("*"), "nsubj"));

            for (auto const& tree : trees) {
                qDebug().noquote() << tree->treeRepr();
            }

            qDebug() << "Finished NLP requester execution";
            QThread::msleep(1200);
        }

        return;
    }

    writeJson();
    writeYaml();

    {
        ColStream    os{qcout};
        ExporterTree tree{os};
    }

    Graphviz gvc;
    {
        ExporterDot dot("g");
        dot.visitTop(node);

        gvc.writeFile("/tmp/graph.dot", *dot.graph);

        //    gvc.renderToFile(
        //        "/tmp/graph.png", *dot.graph,
        //        Graphviz::RenderFormat::PNG);

        qDebug() << "Graphviz ok";
    }

    writeGantt();

    {
        AnnotatorSpelling spelling;
        spelling.setSpeller("en_US");
        spelling.annotate(node);
    }


    {
        ExporterMindMap exporter;
        exporter.visitTop(node);

        writeFile(
            QFileInfo("/tmp/mindmap.json"_qs),
            to_string(exporter.toJsonTree()));

        {
            auto      graph = exporter.toGraph();
            QFileInfo res{"/tmp/mindmap_graph.dot"};

            writeFile(res, exporter.toGraphviz());

            //            Graphviz::Graph read{res};
            //            gvc.renderToFile("/tmp/mindmap_graph.png", read);
            //            qDebug() << "Graph generation ok";
        }

        qDebug() << "Graphviz ok";
    }


    return;
}
