#include "mainwindow.hpp"

#include <QApplication>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QLoggingCategory>
#include <QDebug>

struct AppOpenedFile {
    Str path;
    DESC_FIELDS(AppOpenedFile, (path));
};

struct AppState {
    Vec<AppOpenedFile> opened_files;
    /// Path to the saved application state. If init options have it, then
    /// it is copied from CLI, otherwise it defaults to the application
    /// cache.
    Str saved_state;
    DESC_FIELDS(AppState, (opened_files, saved_state));
};

struct AppStartOptions {
    Opt<Str> saved_state;
    DESC_FIELDS(AppStartOptions, (saved_state));
};

template <typename Derived>
struct CRTP_hexception
    : std::exception
    , CRTP_this_method<Derived> {
    Str         msg;
    int         line;
    char const* function;
    char const* file;

    static Derived init(
        Str const&  msg,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        auto result     = Derived{};
        result.msg      = msg;
        result.line     = line;
        result.file     = file;
        result.function = function;
        return result;
    }


  public:
    virtual const char* what() const noexcept override {
        return strdup(
            std::format("{} at {}:{} in {}", msg, file, line, function)
                .c_str());
    }
};

struct editor_init_exception : CRTP_hexception<editor_init_exception> {};

AppState load_app_state(CR<Str> path) {
    fs::path file1{path.toBase()};
    if (!fs::is_regular_file(file1)) {
        throw editor_init_exception::init(
            fmt("Startup options file {} does not exist or is not a "
                "regular text file",
                path));
    }

    Str  start_text = readFile(file1);
    json start_json = [&]() {
        try {
            return json::parse(start_text);
        } catch (json::exception& e) {
            throw editor_init_exception::init(
                fmt("Failed to parse app start JSON from {}: {}",
                    path,
                    e.what()));
        }
    }();

    AppStartOptions start;
    AppState        state;
    from_json(start_json, start);

    std::string state_file = start.saved_state
                               ? *start.saved_state
                               : QDir(QStandardPaths::writableLocation(
                                          QStandardPaths::CacheLocation))
                                     .absoluteFilePath("editor_state.json")
                                     .toStdString();

    fs::path file{state_file};
    if (!fs::is_regular_file(file)) {
        if (start.saved_state) {
            throw editor_init_exception::init(
                fmt("Path to the saved app state does not exist: {} is "
                    "not a regular text file",
                    file.native()));
        } else {
            qInfo() << fmt(
                "No default saved state found at {}, using default value",
                state_file);
            return state;
        }
    }

    Str  state_text = readFile(file);
    json state_json = [&]() {
        try {
            return json::parse(state_text);
        } catch (json::exception& e) {
            throw editor_init_exception::init(
                fmt("Failed to parse app state JSON from {}: {}, "
                    "startup config from {}",
                    state_file,
                    e.what(),
                    path));
        }
    }();

    from_json(state_json, state);
    if (start.saved_state) {
        qInfo() << fmt(
            "Initial app startup loaded from {}", *start.saved_state);

    } else {
        qInfo() << fmt(
            "Initial app startup options file {} did not specify the "
            "loading state, using default cache path.",
            path);
    }

    state.saved_state = start.saved_state.value();
    return state;
}

void customMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg_in) {
    QByteArray  localMsg     = msg_in.toLocal8Bit();
    const char* fileName     = context.file ? context.file : "?";
    const char* functionName = context.function ? context.function : "?";
    std::string lvl;

    switch (type) {
        case QtDebugMsg: lvl = "DEBUG"; break;
        case QtInfoMsg: lvl = "INFO "; break;
        case QtWarningMsg: lvl = "WARN "; break;
        case QtCriticalMsg: lvl = "CRIT "; break;
        case QtFatalMsg: lvl = "FATAL";
    }

    std::string loc = fmt(
        "[{}] {} ({}, {}:{})",
        lvl,
        localMsg.constData(),
        functionName,
        fileName,
        context.line);

    if (type == QtFatalMsg || type == QtCriticalMsg) {
        std::cerr << loc << std::endl;
        if (type == QtFatalMsg) { abort(); }
    } else {
        std::cout << loc << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw editor_init_exception::init(
            "Expected at least one (1) CLI argument -- path to the file "
            "for the application init state.");
    }
    qInstallMessageHandler(customMessageHandler);

    AppState state = load_app_state(argv[1]);

    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    int result = a.exec();

    json saved_state;
    to_json(saved_state, state);
    writeFile(state.saved_state.toBase(), saved_state.dump(2));
    return result;
}
