#pragma once

#include <QtTest>
#include <editor/editor_lib/mainwindow.hpp>
#include <editor/editor_lib/app_init.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemOrgFormat.hpp>
#include <exporters/exportertree.hpp>

using osk = OrgSemKind;


inline Vec<OrgBoxId> dfs_boxes(OrgDocumentModel::TreeNode const* node) {
    Vec<OrgBoxId> result{node->boxId};
    for (auto const& sub : node->subnodes) {
        result.append(dfs_boxes(sub.get()));
    }

    return result;
}


inline void trigger_editor_of(
    QAbstractItemView* view,
    QModelIndex const& index) {
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

inline void trigger_editor_complete(
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


inline SPtr<MainWindow> init_window(AppState const& state) {
    auto window = std::make_shared<MainWindow>(state);
    window->show();
    window->raise();
    window->activateWindow();
    return window;
}


inline void save_screenshot(const QString& filePath) {
    QScreen* screen = QGuiApplication::primaryScreen();
    if (const QWindow* window = QApplication::focusWindow()) {
        QPixmap pixmap = screen->grabWindow(window->winId());
        pixmap.save(filePath);
    }
}

inline void save_screenshot(QWidget* widget, const QString& filePath) {
    QPixmap pixmap = widget->grab();
    pixmap.save(filePath);
}


inline void add_file(
    AppState&            state,
    QTemporaryDir const& dir,
    std::string const&   relFilename,
    std::string const&   content) {
    std::string file = fs::path{dir.path().toStdString()} / relFilename;
    writeFile(file, content);
    state.opened_files.push_back(AppOpenedFile{.path = file});
}


inline sem::SemId<sem::Org> node(
    OrgStore*          store,
    QModelIndex const& index) {
    return store->node(qvariant_cast<OrgBoxId>(index.data()));
}

inline sem::SemId<sem::Org> node(
    OrgStore*                         store,
    OrgDocumentModel::TreeNode const* tree) {
    return store->node(tree->boxId);
}

inline Str str(sem::OrgArg node) {
    return ExporterUltraplain::toStr(node);
}
inline Str format(sem::OrgArg node) {
    return sem::Formatter::format(node);
}
inline Str tree_repr(sem::OrgArg node) {
    return ExporterTree::treeRepr(node).toString(false);
}

inline void debug_tree(
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

inline Str getSubtree(int treeLevel, CR<Str> name) {
    return Str("*").repeated(treeLevel) + " "_ss + name;
}

inline Str getFile(CVec<Str> elements) { return join("\n", elements); }


struct TestApiAccessor {
    SPtr<MainWindow> window;
    OrgDocumentEdit* edit;


    sem::SemId<sem::Org> getNode() { return edit->docModel->toNode(); };
    sem::SemId<sem::Org> getNode(CVec<int> path) {
        auto index = getIndex(path);
        auto t     = edit->docModel->tree(index);
        Q_ASSERT(t != nullptr);
        return t->toNode(edit->docModel->store);
    };

    template <typename T>
    sem::SemId<T> getNodeT(CVec<int> path) {
        return getNode(path).as<T>();
    };

    /// Get root node of the editor model
    QModelIndex getRoot() { return edit->model()->index(0, 0); }

    /// Get nested node from the editor by traversing full path
    QModelIndex getIndex(CVec<int> path) {
        return ::index(edit->model(), path);
    }

    Str str(sem::OrgArg node) { return ExporterUltraplain::toStr(node); }

    Str getFormat(sem::OrgArg node) {
        return sem::Formatter::format(node);
    }

    Str getFormat() { return sem::Formatter::format(getNode()); }

    /// Get text of the node at a specified path
    Str getText(CVec<int> path) {
        return str(node(edit->docModel->store, getIndex(path)));
    };

    template <typename T>
    Func<sem::SemId<T>(CVec<int>)> getAt() {
        return [this](CVec<int> path) -> sem::SemId<T> {
            auto result = this->getNodeT<T>(path);
            if (result.isNil()) {
                throw std::domain_error(
                    fmt("cannot get node at path {}", path));
            }
            return result;
        };
    }
};

struct TestControllers {
    SPtr<MainWindow> window;
    OrgDocumentEdit* edit;
    TestApiAccessor  api;
};

TestControllers init_test_for_file(CR<Str> file_content);

void test_message_handler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg);


struct TestBase {
    void init_test_base();
    void cleanup_test_base();
};
