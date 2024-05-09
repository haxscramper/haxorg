#include "test_utils.hpp"

#include <QtTest>
#include <QLoggingCategory>

TestControllers init_test_for_file(CR<Str> file_content) {
    QTemporaryDir dir;
    AppState      state;
    Str           nl{"\n\n"};

    add_file(state, dir, "main.org", file_content);


    auto window = init_window(state);
    window->resize(300, 300);
    window->loadFiles();

    OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
        window->findChild<OrgDocumentEdit*>(
            "MainWindow-OrgDocumentEdit-0"));

    return {
        .window = window,
        .edit   = edit,
        .api    = TestApiAccessor{
               .window = window,
               .edit   = edit,
        }};
}

static thread_local QtMessageHandler pre_test_handler;

void test_message_handler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg) {
    // Explicitly handle the 'non-error' errors at least in tests so
    // incorrect code would actually fail the test in a way that I can
    // debug.
    if (type == QtWarningMsg
        && (
            // clang-format off
            msg.contains("QSortFilterProxyModel: index from wrong model")
            || msg.contains("QWidget::repaint: Recursive repaint detected")
            || msg.contains("Cannot destroy paint device that is being painted")
            // clang-format on
            )) {
        qFatal("%s", msg.toStdString().data());

        // } else if (msg.contains("Caught unhandled exception")) {
        //     qFatal("Caught unhandled exception");
    } else {
        pre_test_handler(type, context, msg);
    }
}

void TestBase::init_test_base() {
    editorInitMain();
    pre_test_handler = qInstallMessageHandler(test_message_handler);
}

void TestBase::cleanup_test_base() {
    qInstallMessageHandler(pre_test_handler);
}
