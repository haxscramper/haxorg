#include <QtTest>
#include <editor/editor_lib/mainwindow.hpp>
#include <editor/editor_lib/app_init.hpp>

SPtr<MainWindow> init_window(AppState const& state) {
    return std::make_shared<MainWindow>(state);
}

void add_file(
    AppState&            state,
    QTemporaryDir const& dir,
    std::string const&   relFilename,
    std::string const&   content) {
    std::string file = fs::path{dir.path().toStdString()} / relFilename;
    writeFile(file, content);
    state.opened_files.push_back(AppOpenedFile{.path = file});
}


class GuiTest : public QObject {
    Q_OBJECT

  private slots:
    void testOutlineJump() {
        QTemporaryDir dir;
        AppState      state;
        add_file(state, dir, "main.org", R"(
* First subtree
* Second subtree
* Third subtree
)");

        auto window = init_window(state);
        window->loadFiles();

        OrgDocumentOutline* outline = dynamic_cast<OrgDocumentOutline*>(
            window->findChild<OrgDocumentOutline*>(
                "MainWindow-OrgDocumentOutline"));

        OrgDocumentEdit* treeView2 = dynamic_cast<OrgDocumentEdit*>(
            window->findChild<OrgDocumentEdit*>(
                "MainWindow-OrgDocumentEdit-0"));

        QVERIFY(outline);
        QVERIFY(treeView2);
    }
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    editorInitMain();

    GuiTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "main.moc"
