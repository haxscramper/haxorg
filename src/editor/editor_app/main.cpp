#include <editor/editor_lib/mainwindow.hpp>

#include <QApplication>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <QDebug>
#include <QCoreApplication>
#include <QLoggingCategory>
#include <QDebug>
#include <editor/editor_lib/app_state.hpp>
#include <QDataStream>

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

    std::string loc = fmt(
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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw editor_init_exception::init(
            "Expected at least one (1) CLI argument -- path to the file "
            "for the application init state.");
    }

    qInstallMessageHandler(customMessageHandler);
    qRegisterMetaType<OrgBoxId>("OrgBoxId");

    AppState     state = load_app_state(argv[1]);
    QApplication a(argc, argv);
    MainWindow   w{state};

    w.loadFiles();
    w.show();
    int result = a.exec();

    json saved_state;
    to_json(saved_state, state);
    writeFile(state.saved_state.toBase(), saved_state.dump(2));
    qInfo() << fmt(
        "Saved current application state in {}", state.saved_state);
    return result;
}
