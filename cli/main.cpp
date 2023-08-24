#include <cli/haxorgcli.hpp>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QString>
#include <hstd/wrappers/graphviz.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>
#include <glib.h>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Json.hpp>

#include "config.hpp"

#ifdef USE_PERFETTO
#    include <hstd/wrappers/perfetto_aux.hpp>
#endif

QTextStream qcout;


bool parseArgs(
    QCoreApplication& app,
    int               argc,
    char**            argv,
    cli::Main&        config) {

    QCommandLineParser parser;
    parser.setApplicationDescription("Description of your application");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", "Input org file");

    Vec<Pair<QCommandLineOption, cli::OptConfig>> options;
    for (auto const& option : cli::OptWalker<cli::Main>::get({})) {

        options.push_back({option.getOpt(), option});
    }

    for (auto const& option : options) {
        parser.addOption(option.first);
    }

    parser.process(app);

    for (auto const& [qt, conf] : options) {
        if (parser.isSet(qt)) {
            auto handle = config.getHandle(conf.name);
            qDebug() << "Setting" << conf.name << "to" << parser.value(qt)
                     << handle.getKind();
            if (handle.getKind()
                == cli::ReflectiveCliBase::FieldHandle::Kind::Primitive) {
                auto& primitive = handle.getPrimitive();
                if (conf.isFlag) {
                    primitive.setFrom("true");
                } else {
                    primitive.setFrom(parser.value(qt));
                }
            }
        }
    }

    config.getHandle(CVec<QString>{"source"})
        .getPrimitive()
        .setFrom(parser.positionalArguments().at(0));

    json j;
    to_json(j, config);
    qDebug().noquote() << to_compact_json(j, {.width = 240});

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

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("MyApp");
    QCoreApplication::setApplicationVersion("1.0");

    g_log_set_handler(
        NULL,
        (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL),
        glib_log_handler,
        NULL);

#ifdef USE_PERFETTO
    qInfo() << "Compiled with perfetto trace enabled, starting perfetto";
    InitializePerfetto();
    auto tracing_session = StartTracing();

    // Give a custom name for the traced process.
    perfetto::ProcessTrack process_track = perfetto::ProcessTrack::
        Current();
    perfetto::protos::gen::TrackDescriptor desc = process_track
                                                      .Serialize();
    desc.mutable_process()->set_process_name("Example");
    perfetto::TrackEvent::SetTrackDescriptor(process_track, desc);
#endif

    QFile file;
    file.open(stdout, QIODevice::WriteOnly);
    qcout.setDevice(&file);
    QtMessageHandler old = qInstallMessageHandler(tracedMessageHandler);

    cli::Main config;
    if (!parseArgs(app, argc, argv, config)) {
        return 1;
    }

    HaxorgCli cli{config};
    cli.exec();

#ifdef USE_PERFETTO
    StopTracing(std::move(tracing_session));
#endif
    return 0;
}
