#include <editor/editor_lib/main_gui/mainwindow.hpp>

#include <QApplication>
#include <QDebug>
#include <editor/editor_lib/common/app_state.hpp>
#include <editor/editor_lib/common/app_init.hpp>
#include <QDataStream>
#include <editor/editor_lib/common/app_utils.hpp>

#include <hstd/wrappers/hstd_extra/perfetto_aux_impl_template.hpp>

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

    json saved_state = to_json_eval(state);
    writeFile(state.saved_state.toBase(), saved_state.dump(2));
    qInfo() << fmt(
        "Saved current application state in {}", state.saved_state);
    return result;
}
