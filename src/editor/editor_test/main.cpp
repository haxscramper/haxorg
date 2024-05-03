#include <QtTest>
#include <editor/editor_lib/mainwindow.hpp>
#include <editor/editor_lib/app_init.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemOrgFormat.hpp>
#include <exporters/exportertree.hpp>

SPtr<MainWindow> init_window(AppState const& state) {
    auto window = std::make_shared<MainWindow>(state);
    window->show();
    window->raise();
    window->activateWindow();
    return window;
}


void save_screenshot(const QString& filePath) {
    QScreen* screen = QGuiApplication::primaryScreen();
    if (const QWindow* window = QApplication::focusWindow()) {
        QPixmap pixmap = screen->grabWindow(window->winId());
        pixmap.save(filePath);
    }
}

void save_screenshot(QWidget* widget, const QString& filePath) {
    QPixmap pixmap = widget->grab();
    pixmap.save(filePath);
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


sem::SemId<sem::Org> node(OrgStore* store, QModelIndex const& index) {
    return store->node(qvariant_cast<OrgBoxId>(index.data()));
}

sem::SemId<sem::Org> node(
    OrgStore*                         store,
    OrgDocumentModel::TreeNode const* tree) {
    return store->node(tree->boxId);
}

Str str(sem::OrgArg node) { return ExporterUltraplain::toStr(node); }
Str format(sem::OrgArg node) { return sem::Formatter::format(node); }
Str tree_repr(sem::OrgArg node) {
    return ExporterTree::treeRepr(node).toString(false);
}

void debug_tree(
    QAbstractItemModel const* model,
    OrgStore const*           store,
    CR<QModelIndex>           index = QModelIndex()) {
    qDebug().noquote().nospace()
        << "\n"
        << printModelTree(
               model,
               index.isValid() ? index : model->index(0, 0),
               store_index_printer(store));
}

Vec<OrgBoxId> dfs_boxes(OrgDocumentModel::TreeNode const* node) {
    Vec<OrgBoxId> result{node->boxId};
    for (auto const& sub : node->subnodes) {
        result.append(dfs_boxes(sub.get()));
    }

    return result;
}

using osk = OrgSemKind;

void trigger_editor_of(QAbstractItemView* view, QModelIndex const& index) {
    // https://stackoverflow.com/questions/46795224/qlistwidget-doesnt-recognize-signals-from-qtestmousedclick
    // Using QTest, the signal doubleClicked is never emitted
    QTest::mouseClick(
        view->viewport(),
        Qt::LeftButton,
        Qt::NoModifier,
        view->visualRect(index).center());
    QTest::mouseDClick(
        view->viewport(),
        Qt::LeftButton,
        Qt::NoModifier,
        view->visualRect(index).center());

    // Double click works for the outline processing where double click
    // immediately sends the event off, but with the editor component there
    // is no reaction to the event (event handler is not even triggered).
}

void trigger_editor_complete(
    QAbstractItemView* view,
    const QModelIndex& index) {
    QWidget* editor = view->indexWidget(index);
    QVERIFY2(
        editor, "Cannot trigger editor completion with nullptr widget");

    emit static_cast<QAbstractItemDelegate*>(view->itemDelegate())
        ->commitData(editor);
    emit static_cast<QAbstractItemDelegate*>(view->itemDelegate())
        ->closeEditor(editor, QAbstractItemDelegate::SubmitModelCache);
}

class GuiTest : public QObject {
    Q_OBJECT

  private slots:
    void testSubtreeEditing() {
        QTemporaryDir dir;
        AppState      state;
        add_file(
            state,
            dir,
            "main.org",
            "First paragraph in document\n\nSecond paragraph in document");

        auto window = init_window(state);
        auto s      = window->store.get();
        window->resize(300, 300);
        window->loadFiles();

        OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
            window->findChild<OrgDocumentEdit*>(
                "MainWindow-OrgDocumentEdit-0"));

        QVERIFY(edit);

        auto index = edit->model()->index(
            0, 0, edit->model()->index(0, 0));
        QVERIFY(index.isValid());
        edit->setFocus();
        QVERIFY(QTest::qWaitForWindowActive(window.get()));
        QCOMPARE_EQ(edit->model()->rowCount(), 1);

        auto dfs_before = dfs_boxes(edit->docModel->root.get());

        { // Verify the original structure of the document read from the
          // text
            auto r = edit->docModel->root.get();
            QCOMPARE_EQ(r->parent, nullptr);
            QCOMPARE_EQ(r->subnodes.size(), 2);
            QVERIFY(node(s, r)->is(osk::Document));
            QVERIFY(node(s, r->subnodes.at(0).get())->is(osk::Paragraph));
            QVERIFY(node(s, r->subnodes.at(1).get())->is(osk::Paragraph));
            auto n = node(s, index);
            QVERIFY(n->is(osk::Paragraph));
            QCOMPARE_EQ(str(n), "First paragraph in document");
            auto tree = edit->docModel->toNode();

            QCOMPARE_EQ(
                format(tree),
                "First paragraph in document\n\nSecond paragraph in "
                "document");
        }


        { // Double-click on the editor cell and enter some text
            trigger_editor_of(edit, index);

            QTest::qWait(100);

            QApplication::processEvents();

            QTextEdit* focusedWidget = qobject_cast<QTextEdit*>(
                QApplication::focusWidget());
            QVERIFY(focusedWidget);
            QTest::keyClicks(focusedWidget, "your text here ");
            trigger_editor_complete(edit, index);
            QTest::qWait(5);
        }

        auto dfs_after = dfs_boxes(edit->docModel->root.get());


        { // After editing operations only a single element in the model
          // should change the boxed node value.
            QCOMPARE_EQ(dfs_before.size(), dfs_after.size());
            QCOMPARE_EQ(dfs_before.size(), 3);
            QCOMPARE_EQ(dfs_before.at(0), dfs_after.at(0));
            QCOMPARE_NE(dfs_before.at(1), dfs_after.at(1));
            QCOMPARE_EQ(dfs_before.at(2), dfs_after.at(2));

            // The store does not replace the content of the original boxed
            // node -- it creates an entirely new node and puts it into the
            // store. This way it is still possible to access all the
            // previous building blocks of the document.
            QCOMPARE_EQ(
                format(s->node(dfs_before.at(1))),
                "First paragraph in document");
            QCOMPARE_EQ(
                format(s->node(dfs_after.at(1))),
                "your text here First paragraph in document");
        }

        {
            auto n = node(s, index);
            QVERIFY(n->is(osk::Paragraph));
            QCOMPARE_EQ(
                str(n), "your text here First paragraph in document");
            auto tree = edit->docModel->toNode();
            QCOMPARE_EQ(
                format(tree),
                "your text here First paragraph in document\n\nSecond "
                "paragraph in document");
        }
    }

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
        auto s      = window->store.get();
        window->loadFiles();

        OrgDocumentOutline* outline = dynamic_cast<OrgDocumentOutline*>(
            window->findChild<OrgDocumentOutline*>(
                "MainWindow-OrgDocumentOutline"));

        OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
            window->findChild<OrgDocumentEdit*>(
                "MainWindow-OrgDocumentEdit-0"));

        QVERIFY(outline);
        QVERIFY(edit);

        { // Text outline model structure
            auto m = outline->model();
            QCOMPARE_EQ(m->rowCount(), 1);
            qDebug() << "Start model structure compare";
            {
                auto r   = m->index(0, 0);
                auto t1  = m->index(0, 0, r);
                auto t11 = m->index(0, 0, t1);
                auto t12 = m->index(1, 0, t1);
                QVERIFY(node(s, r)->is(osk::Document));
                QVERIFY(r.isValid());
                QCOMPARE_EQ(m->rowCount(r), 3);

                QVERIFY(t1.isValid());
                QVERIFY(t11.isValid());
                QVERIFY(t12.isValid());
                QCOMPARE_EQ(m->rowCount(t1), 2);
                QCOMPARE_EQ(m->rowCount(t11), 0);
                QCOMPARE_EQ(m->rowCount(t12), 0);
                QCOMPARE_EQ(node(s, t1).getAs<sem::Subtree>()->level, 1);
                QCOMPARE_EQ(node(s, t11).getAs<sem::Subtree>()->level, 2);
                QCOMPARE_EQ(node(s, t12).getAs<sem::Subtree>()->level, 2);
            }
        }

        { // Text edit model structure
            auto m = edit->model();
            QCOMPARE_EQ(m->rowCount(), 1);
            // 'First subtree' has two nested paragraphs and two nested
            // sub-subtrees, each one having two paragraphs of their own.
            // Outline model filters all non-subtree elements so it should
            // have only two subtrees under t1 and no sub-sub-nodes under
            // t11 and t12.
            {
                auto r   = m->index(0, 0);
                auto t1  = m->index(0, 0, r);
                auto t11 = m->index(2, 0, t1);
                auto t12 = m->index(3, 0, t1);
                QCOMPARE_EQ(m->rowCount(t1), 4);
                QCOMPARE_EQ(m->rowCount(t11), 2);
                QCOMPARE_EQ(m->rowCount(t12), 2);
            }
        }

        { // Trigger navigation double click
            auto       outline_model = outline->model();
            auto       edit_model    = edit->model();
            QSignalSpy spy{edit, SIGNAL(focusedOn(QModelIndex))};

            QTest::mouseDClick(
                outline->viewport(),
                Qt::LeftButton,
                Qt::NoModifier,
                outline->visualRect(outline_model->index(0, 0)).center());

            QTest::qWait(100);
            QCOMPARE_EQ(spy.count(), 1);
            QList<QVariant> arguments = spy.takeFirst();
            QCOMPARE_EQ(
                arguments.at(0).value<QModelIndex>(),
                edit_model->index(0, 0));
        }

        { // Test the rest of the outline jump mappings
            auto outline_model = outline->model();
            auto edit_model    = edit->model();
            auto p00           = std::make_pair(0, 0);
            for (auto const& [path_outline, path_edit] :
                 Vec<Pair<Vec<Pair<int, int>>, Vec<Pair<int, int>>>>{
                     // List of model index paths in both outlines
                     {
                         // Frist first toplevel tree in the outline to the
                         // first toplevel tree in the editor.
                         {p00, p00},
                         {p00, p00},
                     },
                     {
                         // First-First toplevel to the first-first outline
                         // should account for paragraph offsets.
                         {p00, p00, std::make_pair(1, 0)},
                         {p00, p00, std::make_pair(3, 0)},
                     },
                     {
                         {p00, std::make_pair(2, 0)},
                         {p00, std::make_pair(2, 0)},
                     },
                 }) {
                edit->scrollTo(
                    edit->model()->index(0, 0),
                    QAbstractItemView::PositionAtTop);
                QSignalSpy spy{edit, SIGNAL(focusedOn(QModelIndex))};
                auto outline_index = index(outline_model, path_outline);
                auto edit_index    = index(edit_model, path_edit);
                QVERIFY(outline_index.isValid());
                QVERIFY(edit_index.isValid());

                QTest::mouseDClick(
                    outline->viewport(),
                    Qt::LeftButton,
                    Qt::NoModifier,
                    outline->visualRect(outline_index).center());

                QTest::qWait(100);
                QCOMPARE_EQ(spy.count(), 1);
                QList<QVariant> arguments = spy.takeFirst();
                QCOMPARE_EQ(
                    arguments.at(0).value<QModelIndex>(), edit_index);
            }
        }
    }


    void testParagraphMovements() {
        QTemporaryDir dir;
        AppState      state;
        Str           nl{"\n\n"};
        Str           p1{"First paragraph in document"};
        Str           p2{"Second paragraph in document"};
        Str           p3{"Third paragraph in document"};

        add_file(state, dir, "main.org", p1 + nl + p2 + nl + p3);


        auto window = init_window(state);
        window->resize(300, 300);
        window->loadFiles();

        OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
            window->findChild<OrgDocumentEdit*>(
                "MainWindow-OrgDocumentEdit-0"));

        auto get       = [&]() { return edit->docModel->toNode(); };
        auto root      = edit->model()->index(0, 0);
        auto par_index = [&](int index) {
            return edit->model()->index(index, 0, root);
        };

        auto par_text = [&](int row) {
            return str(node(edit->docModel->store, par_index(row)));
        };

        { // Moving paragraph outside of the document boundary is ignored
            auto i0 = edit->model()->index(0, 0, root);


            edit->movePositionUp(i0, 0);
            QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);

            edit->movePositionUp(i0, 200);
            QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);

            auto i2 = edit->model()->index(2, 0, root);
            edit->movePositionDown(i2, 0);
            QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);

            edit->movePositionDown(i2, 200);
            QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);
        }

        debug_tree(edit->model(), edit->docModel->store);

        { // Move first paragraph down and back up
            edit->movePositionDown(edit->model()->index(0, 0, root), 1);
            QCOMPARE_EQ(format(get()), p2 + nl + p1 + nl + p3);
            QCOMPARE_EQ(par_text(0), p2);
            QCOMPARE_EQ(par_text(1), p1);
            QCOMPARE_EQ(par_text(2), p3);

            edit->movePositionUp(edit->model()->index(1, 0, root), 1);
            QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);
            QCOMPARE_EQ(par_text(0), p1);
            QCOMPARE_EQ(par_text(1), p2);
            QCOMPARE_EQ(par_text(2), p3);
        }

        { // Move first paragraph all the way down and then back again
            edit->movePositionDown(edit->model()->index(0, 0, root), 2);
            QCOMPARE_EQ(format(get()), p2 + nl + p3 + nl + p1);
            QCOMPARE_EQ(par_text(0), p2);
            QCOMPARE_EQ(par_text(1), p3);
            QCOMPARE_EQ(par_text(2), p1);

            edit->movePositionUp(edit->model()->index(2, 0, root), 2);
            QCOMPARE_EQ(format(get()), p1 + nl + p2 + nl + p3);
            QCOMPARE_EQ(par_text(0), p1);
            QCOMPARE_EQ(par_text(1), p2);
            QCOMPARE_EQ(par_text(2), p3);
        }


        QVERIFY(edit);
    }
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    editorInitMain();

    GuiTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "main.moc"
