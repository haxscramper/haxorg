#include <QtTest>
#include <editor/editor_lib/mainwindow.hpp>
#include <editor/editor_lib/app_init.hpp>
#include <editor/editor_lib/app_utils.hpp>

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

Func<std::string(QModelIndex const&)> store_index_printer(
    OrgStore* store) {
    return [store](QModelIndex const& idx) -> std::string {
        OrgBoxId box  = qvariant_cast<OrgBoxId>(idx.data());
        auto     node = store->node(box);
        return fmt(
            "[{}, {}] {} {}",
            idx.row(),
            idx.column(),
            qdebug_to_str(idx),
            node->getKind());
    };
}

class GuiTest : public QObject {
    Q_OBJECT

  private slots:
    void testOutlineJump() {
        QTemporaryDir dir;
        AppState      state;
        add_file(state, dir, "main.org", R"(
* First subtree

First subtree paragraph 1

First subtree paragraph 2

** First subtree subtree 1

First subtree subtree 1 paragraph 1

First subtree subtree 1 paragraph 2

** First subtree subtree 2

First subtree subtree 2 paragraph 1

First subtree subtree 2 paragraph 2

* Second subtree

Second subtree paragraph 1

Second subtree paragraph 2

* Third subtree

Third subtree paragraph 1

Third subtree paragraph 2

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

        {
            auto m = outline->model();
            // qDebug().noquote() << printModelTree(
            //     m,
            //     QModelIndex(),
            //     store_index_printer(window->store.get()));

            QCOMPARE_EQ(m->rowCount(), 3);
            {
                auto t1  = m->index(0, 0);
                auto t11 = m->index(0, 0, t1);
                auto t12 = m->index(1, 0, t1);
                QCOMPARE_EQ(m->rowCount(t1), 2);
                QCOMPARE_EQ(m->rowCount(t11), 0);
                QCOMPARE_EQ(m->rowCount(t12), 0);
            }
        }
        {
            auto m = treeView2->model();
            QCOMPARE_EQ(m->rowCount(), 3);
            // 'First subtree' has two nested paragraphs and two nested
            // sub-subtrees, each one having two paragraphs of their own.
            // Outline model filters all non-subtree elements so it should
            // have only two subtrees under t1 and no sub-sub-nodes under
            // t11 and t12.
            {
                auto t1 = m->index(0, 0);
                QCOMPARE_EQ(m->rowCount(t1), 4);
                auto t11 = m->index(2, 0, t1);
                QCOMPARE_EQ(m->rowCount(t11), 2);
                auto t12 = m->index(3, 0, t1);
                QCOMPARE_EQ(m->rowCount(t12), 2);
            }
        }
    }
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    editorInitMain();

    GuiTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "main.moc"
