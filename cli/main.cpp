#include <cli/haxorgcli.hpp>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QString>
#include <hstd/wrappers/graphviz.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>
#include <glib.h>
#include <hstd/stdlib/Debug.hpp>

#ifdef USE_PERFETTO
#    include <hstd/wrappers/perfetto_aux.hpp>
#endif

QTextStream qcout;


struct ReflectiveCliBase {
    DECL_FIELDS(ReflectiveCliBase, ());
    virtual QString getDocFor(QString const& field) const { return ""; }
};

struct TraceConfig : ReflectiveCliBase {
    DECL_FIELDS(
        TraceConfig,
        (),
        ((Opt<QFileInfo>), to, std::nullopt),
        ((bool), enabled, false),
        ((Slice<int>), extent, (slice(0, value_domain<int>::high()))),
        ((bool), dump, false),
        ((Opt<QFileInfo>), dumpTo, std::nullopt));

    virtual QString getDocFor(const QString& field) const {
        if (field == "to") {
            return "File to write debug output to";
        } else if (field == "enabled") {
            return "Is trace enabled";
        } else {
            return "";
        }
    }
};

struct Exporter : ReflectiveCliBase {
    struct Base : ReflectiveCliBase {
        DECL_FIELDS(Base, (), ((TraceConfig), trace, TraceConfig{}));
    };

    struct Tex : Base {
        DECL_FIELDS(Tex, (Base, ReflectiveCliBase));
    };

    struct NLP : Base {
        DECL_FIELDS(NLP, (Base, ReflectiveCliBase));
    };

    DECL_FIELDS(
        Exporter,
        (),
        ((Opt<Tex>), tex, std::nullopt),
        ((Opt<NLP>), nlp, std::nullopt));

    virtual QString getDocFor(const QString& field) const {
        if (field == "tex") {
            return "Latex exporter";
        } else {
            return "";
        }
    }
};

struct OptConfig {
    Vec<QString> name;
    QString      doc;
    QString      getSingleName() const { return join("-", name); }

    QCommandLineOption getOpt() const {
        return QCommandLineOption(getSingleName(), doc, "value");
    }
};

template <class C, typename T>
T getPointerType(T C::*v);

template <typename T>
struct OptWalker;

template <typename T>
struct LeafOptWalker {
    static Vec<OptConfig> get(Vec<QString> const& prefix) {
        return Vec<OptConfig>{};
    }
};

template <>
struct OptWalker<bool> : LeafOptWalker<bool> {};

template <>
struct OptWalker<Slice<int>> : LeafOptWalker<Slice<int>> {};

template <>
struct OptWalker<QFileInfo> : LeafOptWalker<QFileInfo> {};

template <typename T>
struct OptWalker<Opt<T>> {
    static Vec<OptConfig> get(Vec<QString> const& prefix) {
        return OptWalker<T>::get(prefix);
    }
};


template <DescribedRecord T>
struct OptWalker<T> {
    static Vec<OptConfig> get(Vec<QString> const& prefix) {
        using Bd = boost::describe::
            describe_bases<T, boost::describe::mod_any_access>;
        using Md = boost::describe::
            describe_members<T, boost::describe::mod_any_access>;
        Vec<OptConfig> result;

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            result.append(
                OptWalker<std::remove_cvref_t<
                    typename decltype(Base)::type>>::get(prefix));
        });

        boost::mp11::mp_for_each<Md>([&](auto const& field) {
            auto parent = OptConfig{
                .doc  = T().getDocFor(field.name),
                .name = prefix + Vec<QString>{QString(field.name)}};

            result.push_back(parent);
            result.append(
                OptWalker<std::remove_cvref_t<decltype(getPointerType(
                    field.pointer))>>::get(parent.name));
        });

        return result;
    }
};


struct Main : ReflectiveCliBase {
    DECL_FIELDS(Main, (), ((Exporter), exp, Exporter{}))
};

bool parseArgs(
    QCoreApplication&  app,
    int                argc,
    char**             argv,
    HaxorgCli::Config& config) {

    QCommandLineParser parser;
    parser.setApplicationDescription("Description of your application");
    parser.addHelpOption();
    parser.addVersionOption();

    Vec<QCommandLineOption> options;
    for (auto const& option : OptWalker<Main>::get({})) {
        qDebug() << option.name << option.doc;
        options.push_back(option.getOpt());
    }

    for (auto const& option : options) {
        parser.addOption(option);
    }

    qDebug().noquote() << parser.helpText();

    return false;
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

    HaxorgCli cli{};
    if (!parseArgs(app, argc, argv, cli.config)) {
        return 1;
    }

    cli.exec();

#ifdef USE_PERFETTO
    StopTracing(std::move(tracing_session));
#endif
    return 0;
}
