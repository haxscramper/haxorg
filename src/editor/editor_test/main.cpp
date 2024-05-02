#include <QtTest>
#include <editor/editor_lib/mainwindow.hpp>
#include <editor/editor_lib/app_init.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <exporters/ExporterUltraplain.hpp>

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


class DebugEventFilter : public QObject {
  public:
    DebugEventFilter(QObject* parent) : QObject(parent) {}

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override {
        qDebug().noquote().nospace()
            << "Object: '" << obj->metaObject()->className()
            << "::" << obj->objectName() << //
            "' Type: " << event->type() <<  //
            " Event: " << event <<          //
            " Receiver: " << obj;
        return false;
    }
};


void debug_event_filter(QObject* obj) {
    obj->installEventFilter(new DebugEventFilter(obj));
}

finally scoped_debug_event_filter(QObject* obj) {
    SPtr<DebugEventFilter> filter = std::make_shared<DebugEventFilter>(
        obj);

    obj->installEventFilter(filter.get());
    return finally(
        [filter, obj]() { obj->removeEventFilter(filter.get()); });
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

QModelIndex index(QAbstractItemModel* model, Vec<Pair<int, int>> path) {
    QModelIndex result = model->index(path.at(0).first, path.at(0).second);
    for (int i = 1; i < path.size(); ++i) {
        result = model->index(path.at(i).first, path.at(i).second, result);
    }

    return result;
}

sem::SemId<sem::Org> node(OrgStore* store, QModelIndex const& index) {
    return store->node(qvariant_cast<OrgBoxId>(index.data()));
}

Str str(sem::OrgArg node) { return ExporterUltraplain::toStr(node); }

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
        add_file(state, dir, "main.org", R"(
First paragraph in document

Second paragraph in document
)");

        auto window = init_window(state);
        auto s      = window->store.get();
        window->resize(300, 300);
        window->loadFiles();

        OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
            window->findChild<OrgDocumentEdit*>(
                "MainWindow-OrgDocumentEdit-0"));

        QVERIFY(edit);

        auto index = edit->model()->index(0, 0);
        QVERIFY(index.isValid());
        edit->setFocus();
        QVERIFY(QTest::qWaitForWindowActive(window.get()));
        QCOMPARE_EQ(edit->model()->rowCount(), 2);

        {
            auto n = node(s, index);
            QVERIFY(n->is(OrgSemKind::Paragraph));
            QCOMPARE_EQ(str(n), "First paragraph in document");
        }


        trigger_editor_of(edit, index);

        QTest::qWait(100);

        QApplication::processEvents();

        QTextEdit* focusedWidget = qobject_cast<QTextEdit*>(
            QApplication::focusWidget());
        QVERIFY(focusedWidget);
        QTest::keyClicks(focusedWidget, "your text here ");
        trigger_editor_complete(edit, index);
        QTest::qWait(5);

        {
            auto n = node(s, index);
            QVERIFY(n->is(OrgSemKind::Paragraph));
            QCOMPARE_EQ(str(n), "your text here First paragraph in document");
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
            QCOMPARE_EQ(m->rowCount(), 3);
            {
                auto t1  = m->index(0, 0);
                auto t11 = m->index(0, 0, t1);
                auto t12 = m->index(1, 0, t1);
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
            QCOMPARE_EQ(m->rowCount(), 3);
            // 'First subtree' has two nested paragraphs and two nested
            // sub-subtrees, each one having two paragraphs of their own.
            // Outline model filters all non-subtree elements so it should
            // have only two subtrees under t1 and no sub-sub-nodes under
            // t11 and t12.
            {
                auto t1  = m->index(0, 0);
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
            for (auto const& [path_outline, path_edit] :
                 Vec<Pair<Vec<Pair<int, int>>, Vec<Pair<int, int>>>>{
                     // List of model index paths in both outlines
                     {
                         // Frist first toplevel tree in the outline to the
                         // first toplevel tree in the editor.
                         {std::make_pair(0, 0)},
                         {std::make_pair(0, 0)},
                     },
                     {
                         // First-First toplevel to the first-first outline
                         // should account for paragraph offsets.
                         {std::make_pair(0, 0), std::make_pair(1, 0)},
                         {std::make_pair(0, 0), std::make_pair(3, 0)},
                     },
                     {
                         {std::make_pair(2, 0)},
                         {std::make_pair(2, 0)},
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
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    editorInitMain();

    GuiTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "main.moc"
