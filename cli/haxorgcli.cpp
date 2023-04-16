#include "haxorgcli.hpp"

#include <lexbase/NodeIO.hpp>
#include <exporters/ExporterJson.hpp>
#include <QElapsedTimer>


void HaxorgCli::timeStats() {
    for (const auto& rep : processStatus.reports) {
        qInfo().noquote()
            << R"(Processing of '$#' took:
  lex:     $#s
  parse:   $#s
  convert: $#s
  export:  $#s)"
                   % to_string_vec(
                       rep.file.filePath(),
                       float(rep.lexNs.value_or(0)) / 1000000,
                       float(rep.parseNs.value_or(0)) / 1000000,
                       float(rep.convertNs.value_or(0)) / 1000000,
                       float(rep.exportNs.value_or(0)) / 1000000);
    }
}

HaxorgCli::HaxorgCli() : tokenizer(nullptr), nodes(nullptr), lex(&tokens) {
    nodes.tokens  = &tokens;
    tokenizer.out = &tokens;
}

void HaxorgCli::exec() {
    source      = readFile(config.sourceFile);
    tokens.base = source.data();
    info        = LineColInfo{source};

    parser.initImpl(&nodes, config.trace.parse.doTrace);

    Func<LineCol(CR<PosStr>)> locationResolver =
        [&](CR<PosStr> str) -> LineCol {
        Slice<int> absolute = tokens.toAbsolute(str.view);
        return {
            info.whichLine(absolute.first + str.pos) + 1,
            info.whichColumn(absolute.first + str.pos),
        };
    };

    tokenizer.locationResolver = locationResolver;
    converter.locationResolver = locationResolver;
    parser.setLocationResolver(locationResolver);

    if (config.trace.lex.doTrace) {
        tokenizer.trace = true;
        if (config.trace.lex.traceTo.has_value()) {
            tokenizer.setTraceFile(config.trace.lex.traceTo.value());
        }
    }

    tokenizer.traceUpdateHook =
        [&](CR<OrgTokenizer::Report> in, bool& doTrace, bool first) {
            if (in.str != nullptr) {
                LineCol loc = tokenizer.locationResolver(*(in.str));
                if (config.trace.lex.traceExtent.contains(loc.line)) {
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

    parser.setTraceUpdateHook([&](CR<OrgParser::Report> in,
                                  bool&                 doTrace,
                                  bool                  first) {
        if (in.node.has_value()) {
            OrgId node = in.node.value();
            if (nodes.at(node).isTerminal()) {
                auto tok = tokens.at(nodes.at(node).getToken());
                if (tok.hasData()) {
                    LineCol loc = tokenizer.locationResolver(
                        tok.getText());
                    if (loc.line != -1) {
                        doTrace = config.trace.parse.traceExtent.contains(
                            loc.line);
                    }
                }
            }
        }
    });

    PosStr        str{source};
    QElapsedTimer timer;

    timer.start();
    processStatus.reports.push_back({});
    ProcessStatus::FileReport& rep = processStatus.reports.back();
    rep.file                       = config.sourceFile;
    tokenizer.lexGlobal(str);
    rep.lexNs = timer.nsecsElapsed();

    using Target = HaxorgCli::Config::Target;

    if (config.target == Target::YamlLex) {
        writeFile(config.outFile, to_string(yamlRepr(tokens)) + "\n");
        qInfo() << "Wrote YAML lex representation into " << config.outFile;
        return;
    } else if (config.target == Target::JsonLex) {
        writeFile(config.outFile, to_string(jsonRepr(tokens)) + "\n");
        qInfo() << "Wrote JSON lex representation into " << config.outFile;
        return;
    }

    timer.restart();
    parser.parseTop(lex);
    parser.extendSubtreeTrails(OrgId(0));
    parser.extendAttachedTrails(OrgId(0));
    rep.lexNs = timer.nsecsElapsed();

    if (config.target == Target::YamlParse) {
        writeFile(config.outFile, to_string(yamlRepr(nodes)) + "\n");
        qInfo() << "Wrote YAML parse representation into "
                << config.outFile;
        return;
    } else if (config.target == Target::JsonParse) {
        writeFile(config.outFile, to_string(jsonRepr(nodes)) + "\n");
        qInfo() << "Wrote JSON parse representation into "
                << config.outFile;
        return;
    }

    timer.restart();
    sem::Wrap<sem::Document> node = converter.toDocument(
        OrgAdapter(&nodes, OrgId(0)));
    rep.convertNs = timer.nsecsElapsed();

    timer.restart();
    ExporterJson exporter;
    Exporter::Wrap<ExporterJson::Result>
        result   = exporter.exportNode(node)->as<ExporterJson::Result>();
    rep.exportNs = timer.nsecsElapsed();

    writeFile(config.outFile, to_string(result->value));
    qInfo() << "Wrote JSON SEM representation into " << config.outFile;

    return;
}
