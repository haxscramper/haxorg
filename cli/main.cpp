#include <cli/haxorgcli.hpp>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QString>
#include <hstd/wrappers/graphviz.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>
#include <glib.h>
#include <hstd/stdlib/Debug.hpp>


#include <hstd/wrappers/perfetto_aux.hpp>

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
                .traceTo = QCommandLineOption("lex-trace-to", "Where to stream lexer trace?", "lex-trace-file"),
                .traceExtent = QCommandLineOption("lex-trace-extent", "Trace extent in the file"),
            },
            .parse = {
                .doTrace = QCommandLineOption("parse-trace", "Do parse tracing?"),
                .traceTo = QCommandLineOption("parse-trace-to", "Where to stream parse trace?", "parse-trace-file"),
                .traceExtent = QCommandLineOption("parse-trace-extent", "Trace extent in the file"),
            },
            .sem = {
                .doTrace = QCommandLineOption("sem-trace", "Do sem tracing?"),
                .traceTo = QCommandLineOption("sem-trace-to", "Where to stream sem trace?", "sem-trace-file"),
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

    Array<
        Pair<
            HaxorgCli::Config::TraceConfig*,
            QOptionsConfig::TraceConfig*>,
        3>
        traces;

    traces[0] = {&config.trace.lex, &opts.trace.lex};
    traces[1] = {&config.trace.parse, &opts.trace.parse};
    traces[2] = {&config.trace.sem, &opts.trace.sem};


    for (const auto& [trace, opt] : traces) {
        if (parser.isSet(opt->doTrace)) {
            trace->doTrace = true;
        }

        if (parser.isSet(opt->traceTo)) {
            trace->doTrace = true;
            QString value  = parser.value(opt->traceTo);
            qDebug() << value;
            Q_ASSERT(value.length() != 0);
            trace->traceTo = QFileInfo(value);
            Q_ASSERT(
                trace->traceTo.value().absoluteFilePath().length() != 0);
        }

        if (parser.isSet(opt->traceExtent)) {
            QStringList extentList = parser.value(opt->traceExtent)
                                         .split(':');
            if (extentList.size() == 2) {
                bool okStart, okEnd;
                int  start = extentList[0].toInt(&okStart);
                int  end   = extentList[1].toInt(&okEnd);

                if (okStart && okEnd) {
                    trace->traceExtent = slice(start, end);
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

// Because people who depend on the glib library never thought that their
// code might be used as a part of an application that does not appreciate
// writing random garbage to he stderr. So instead I wrap everything into
// the do-nothing function in order to fix the inclusion.
void glib_log_handler(
    const gchar*   log_domain,
    GLogLevelFlags log_level,
    const gchar*   message,
    gpointer       user_data) {
    // Do nothing.
}

QString to_string(QFileInfo const& fi) { return fi.absoluteFilePath(); }

QTextStream& operator<<(QTextStream& os, QFileInfo const& fi) {
    return os << fi.absoluteFilePath();
}

int main(int argc, char** argv) {
    g_log_set_handler(
        NULL,
        (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL),
        glib_log_handler,
        NULL);

    InitializePerfetto();
    auto tracing_session = StartTracing();

    // Give a custom name for the traced process.
    perfetto::ProcessTrack process_track = perfetto::ProcessTrack::
        Current();
    perfetto::protos::gen::TrackDescriptor desc = process_track
                                                      .Serialize();
    desc.mutable_process()->set_process_name("Example");
    perfetto::TrackEvent::SetTrackDescriptor(process_track, desc);

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

    _dbg(cli.config.trace.lex.traceTo);
    _dbg(cli.config.trace.parse.traceTo);
    _dbg(cli.config.trace.sem.traceTo);


    cli.exec();

    StopTracing(std::move(tracing_session));
    return 0;
}
