#include <editor/editor_lib/mainwindow.hpp>

#include <QApplication>
#include <QDebug>
#include <editor/editor_lib/app_state.hpp>
#include <editor/editor_lib/app_init.hpp>
#include <QDataStream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw editor_init_exception::init(
            "Expected at least one (1) CLI argument -- path to the file "
            "for the application init state.");
    }

    qInstallMessageHandler(customMessageHandler);
    editorInitMain();

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
