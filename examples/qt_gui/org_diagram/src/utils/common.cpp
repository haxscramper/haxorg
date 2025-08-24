#include "common.hpp"

static std::shared_ptr<hstd::log::log_graph_tracker> tracker = nullptr;
static std::shared_ptr<hstd::log::graphviz_processor>
    graph_processor = nullptr;
static std::shared_ptr<hstd::log::logger_processor>
    log_processor = nullptr;

std::shared_ptr<hstd::log::log_graph_tracker> get_tracker() {

    if (tracker.get() == nullptr) {
        tracker         = std::make_shared<hstd::log::log_graph_tracker>();
        graph_processor = std::make_shared<
            hstd::log::graphviz_processor>();
        tracker->add_processor(graph_processor);
        log_processor = std::make_shared<hstd::log::logger_processor>();
        tracker->add_processor(log_processor);
    }

    return tracker;
}


hstd::ext::Graphviz::Graph get_tracker_graph() {
    return graph_processor->get_graphviz();
}

void customMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg_in) {
    QByteArray  localMsg = msg_in.toLocal8Bit();
    std::string lvl;

    switch (type) {
        case QtDebugMsg: lvl = "DEBUG"; break;
        case QtInfoMsg: lvl = "INFO"; break;
        case QtWarningMsg: lvl = "WARN"; break;
        case QtCriticalMsg: lvl = "CRIT"; break;
        case QtFatalMsg: lvl = "FATAL";
    }

    std::string loc = hstd::fmt(
        "[{}:{}] {} ({}, {}:{})",
        lvl,
        context.category,
        localMsg.constData(),
        context.function ? context.function : "?",
        context.file ? context.file : "?",
        context.line);

    if (type == QtFatalMsg || type == QtCriticalMsg) {
        std::cerr << loc << std::endl;
        if (type == QtFatalMsg) { abort(); }
    } else {
        std::cout << loc << std::endl;
    }
}

hstd::fs::path getDebugFile(QObject* testClass, const hstd::Str& suffix) {
    auto dir = std::filesystem::temp_directory_path()
             / hstd::fs::path{hstd::fmt(
                 "haxorg_tests/{}", testClass->metaObject()->className())};

    if (auto func = QTest::currentTestFunction(); func != nullptr) {
        dir = dir / hstd::fs::path{func};
    }

    if (auto tag = QTest::currentDataTag(); tag != nullptr) {
        dir = dir / hstd::fs::path{tag};
    }

    hstd::createDirectory(hstd::fs::path{dir.native()});

    if (!suffix.empty()) { dir = dir / suffix.toBase(); }

    return dir;
}

hstd::finally_std trackTestExecution(
    QObject*         testClas,
    const hstd::Str& suffix,
    int              line,
    const char*      function,
    const char*      file) {

    auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED([testClas]() {
        return ::hstd::log::init_file_sink(
            getDebugFile(testClas, "execution_trace.log").native());
    });

    auto loc = ::hstd::log::log_graph_processor::tracked_info{
        ::hstd::log::log_graph_processor::callsite(line, function, file)};

    get_tracker()->start_tracing(loc);
    HSLOG_INFO("org.test", "track test execution");
    return hstd::finally_std{
        [testClas,
         suffix,
         loc,
         scoped = std::make_shared<decltype(__log_scoped)>(
             std::move(__log_scoped))]() {
            get_tracker()->end_tracing(loc);
            get_tracker_graph().render(
                getDebugFile(testClas, "execution_graph.png"));
        }};
}
