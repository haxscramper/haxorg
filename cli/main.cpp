#include <cli/haxorgcli.hpp>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QString>
#include <hstd/wrappers/graphviz.hpp>

QTextStream qcout;

struct QOptionsConfig {
    struct TraceConfig {
        QCommandLineOption doTrace;
        QCommandLineOption traceTo;
        QCommandLineOption traceExtent;
    };

    QCommandLineOption target;

    struct Trace {
        TraceConfig lex;
        TraceConfig parse;
        TraceConfig sem;
    } trace;
};

bool parseArgs(int argc, char** argv, HaxorgCli::Config& config) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("MyApp");
    QCoreApplication::setApplicationVersion("1.0");


    QOptionsConfig opts {
        .target = QCommandLineOption("export", "Export format target " +
                                     join(", ", enumerator_names<HaxorgCli::Config::Target>())),
        .trace = {
            .lex = {
                .doTrace = QCommandLineOption("lex-trace", "Do lex tracing?"),
                .traceTo = QCommandLineOption("lex-trace-to", "Where to stream lexer trace?"),
                .traceExtent = QCommandLineOption("lex-trace-extent", "Trace extent in the file"),
            },
            .parse = {
                .doTrace = QCommandLineOption("parse-trace", "Do parse tracing?"),
                .traceTo = QCommandLineOption("parse-trace-to", "Where to stream parse trace?"),
                .traceExtent = QCommandLineOption("parse-trace-extent", "Trace extent in the file"),
            },
            .sem = {
                .doTrace = QCommandLineOption("sem-trace", "Do sem tracing?"),
                .traceTo = QCommandLineOption("sem-trace-to", "Where to stream sem trace?"),
                .traceExtent = QCommandLineOption("sem-trace-extent", "Trace extent in the file"),
            },
        },
    };


    QCommandLineParser parser;
    parser.setApplicationDescription("Description of your application");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption(opts.target);
    parser.addOption(opts.trace.lex.doTrace);
    parser.addOption(opts.trace.lex.traceTo);
    parser.addOption(opts.trace.lex.traceExtent);

    parser.addOption(opts.trace.parse.doTrace);
    parser.addOption(opts.trace.parse.traceTo);
    parser.addOption(opts.trace.parse.traceExtent);

    parser.addOption(opts.trace.sem.doTrace);
    parser.addOption(opts.trace.sem.traceTo);
    parser.addOption(opts.trace.sem.traceExtent);


    // Adding positional arguments for input and output files
    parser.addPositionalArgument("source", "Input org-mode file to parse");
    parser.addPositionalArgument(
        "output", "Output file to write parse result to");

    // Process the actual command line arguments of the application
    parser.process(app);

    QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.size() >= 2) {
        config.sourceFile = QFileInfo(positionalArguments.at(0));
        config.outFile    = QFileInfo(positionalArguments.at(1));
    } else {
        qCritical()
            << "Error: Both source and output files must be provided.";
        return false;
    }

    // TODO Make into generic option-to-enum setter, add adequate error
    // message and 'did you mean' check
    if (parser.isSet(opts.target)) {
        Opt<HaxorgCli::Config::Target>
            target = string_to_enum<HaxorgCli::Config::Target>(
                parser.value(opts.target));

        if (target.has_value()) {
            config.target = target.value();
        } else {
            qCritical() << "Invalid value for option"
                        << opts.target.names();
            return false;
        }
    }


    Array<Pair<Slice<int>*, QCommandLineOption*>, 3> ranges;

    ranges[0] = {
        &config.trace.lex.traceExtent, &opts.trace.lex.traceExtent};
    ranges[1] = {
        &config.trace.parse.traceExtent, &opts.trace.parse.traceExtent};
    ranges[2] = {
        &config.trace.sem.traceExtent, &opts.trace.sem.traceExtent};

    for (const auto& [range, opt] : ranges) {
        if (parser.isSet(*opt)) {
            QStringList extentList = parser.value(*opt).split(':');
            if (extentList.size() == 2) {
                bool okStart, okEnd;
                int  start = extentList[0].toInt(&okStart);
                int  end   = extentList[1].toInt(&okEnd);

                if (okStart && okEnd) {
                    *range = slice(start, end);
                } else {
                    qCritical() << "Invalid range format for trace-extent "
                                   "option. Use START:END format.";
                    return false;
                }
            } else {
                qCritical() << "Invalid range format for trace-extent "
                               "option. Use START:END format.";
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char** argv) {
    Graphviz        ctx;
    Graphviz::Graph graph("g");
    graph.node("test");
    ctx.renderToFile(
        "/tmp/res.png",
        graph,
        Graphviz::RenderFormat::PNG,
        Graphviz::LayoutType::Dot);

    QFile file;
    file.open(stdout, QIODevice::WriteOnly);
    qcout.setDevice(&file);
    QtMessageHandler old = qInstallMessageHandler(tracedMessageHandler);

    HaxorgCli cli{};
    if (!parseArgs(argc, argv, cli.config)) {
        return 1;
    }

    cli.exec();
    cli.timeStats();
    return 0;
}
