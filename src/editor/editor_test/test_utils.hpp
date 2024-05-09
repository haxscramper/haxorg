#pragma once

#include <QtTest>
#include <editor/editor_lib/mainwindow.hpp>
#include <editor/editor_lib/app_init.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemOrgFormat.hpp>
#include <exporters/exportertree.hpp>
#include <hstd/stdlib/Enumerate.hpp>

using osk = OrgSemKind;

inline Vec<OrgBoxId> dfs_boxes(OrgTreeNode const* node) {
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
    OrgStore*          store,
    OrgTreeNode const* tree) {
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
               store_index_printer(store))
               .toString(false);
}

inline Str getSubtree(int treeLevel, CR<Str> name) {
    return Str("*").repeated(treeLevel) + " "_ss + name;
}

inline Str getFile(CVec<Str> elements) { return join("\n", elements); }

struct TestApiAccessor {
    SPtr<MainWindow> window;
    OrgDocumentEdit* edit;


    sem::SemId<sem::Org> getNode() const {
        return edit->docModel->toNode();
    };

    sem::SemId<sem::Org> getNode(CVec<int> path) const {
        auto index = getIndex(path);
        auto t     = edit->docModel->tree(index);
        Q_ASSERT(t != nullptr);
        return t->toNode();
    };

    template <typename T>
    sem::SemId<T> getNodeT(CVec<int> path) const {
        return getNode(path).as<T>();
    };

    /// Get root node of the editor model
    QModelIndex getRoot() const { return edit->model()->index(0, 0); }

    /// Get nested node from the editor by traversing full path
    QModelIndex getIndex(CVec<int> path) const {
        return ::index(edit->model(), path);
    }

    Str str(sem::OrgArg node) const {
        return ExporterUltraplain::toStr(node);
    }

    Str getFormat(sem::OrgArg node) const {
        return sem::Formatter::format(node);
    }

    Str getFormat() const { return sem::Formatter::format(getNode()); }

    /// Get text of the node at a specified path
    Str getText(CVec<int> path) const {
        return str(node(edit->docModel->store, getIndex(path)));
    };

    template <typename T>
    Func<sem::SemId<T>(CVec<int>)> getAt() const {
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

struct TestDocumentNode {
    enum class Kind
    {
        Subtree,
        Paragraph,
        Document,
    };

    Kind                  kind;
    Vec<TestDocumentNode> subnodes;
    Opt<Str>              text;
};

struct TestDocumentModel {
    TestDocumentNode document(CVec<TestDocumentNode> subnodes = {}) const {
        return TestDocumentNode{
            .kind     = TestDocumentNode::Kind::Document,
            .subnodes = subnodes,
        };
    }

    TestDocumentNode tree(
        CR<Str>                title    = "Subtree",
        CVec<TestDocumentNode> subnodes = {}) const {
        return TestDocumentNode{
            .kind     = TestDocumentNode::Kind::Subtree,
            .subnodes = subnodes,
            .text     = title,
        };
    }

    TestDocumentNode paragraph(CR<Str> text = "Paragraph") const {
        return TestDocumentNode{
            .kind = TestDocumentNode::Kind::Paragraph,
            .text = text,
        };
    }

    void compare(TestApiAccessor const& api, CR<TestDocumentNode> node) {
        Func<void(CVec<int>, CR<TestDocumentNode>)> aux_compare;
        using K     = TestDocumentNode::Kind;
        aux_compare = [&](CVec<int> path, CR<TestDocumentNode> node) {
            switch (node.kind) {
                case K::Subtree: {
                    sem::SemId<sem::Subtree>
                                tree  = api.getNodeT<sem::Subtree>(path);
                    QModelIndex index = api.getIndex(path);
                    QCOMPARE_EQ(tree->level, path.size() - 1);
                    QCOMPARE_EQ(api.str(tree->title), node.text);
                    QCOMPARE_EQ(
                        api.edit->model()->rowCount(index),
                        node.subnodes.size());
                    break;
                }
                case K::Paragraph: {
                    sem::SemId<sem::Paragraph>
                        par = api.getNodeT<sem::Paragraph>(path);
                    break;
                }
                case K::Document: {
                    sem::SemId<sem::Document>
                        par = api.getNodeT<sem::Document>(path);
                    break;
                }
            }

            for (auto const& it : enumerator(node.subnodes)) {
                aux_compare(path + Vec<int>{it.index()}, it.value());
            }
        };

        aux_compare(Vec<int>{0}, node);

        Func<void(Str&, CR<TestDocumentNode>, int)> aux_format;
        aux_format = [&](Str& res, CR<TestDocumentNode> node, int level) {
            switch (node.kind) {
                case K::Subtree: {
                    res += Str("*").repeated(level);
                    res += " ";
                    res += node.text.value();
                    if (!node.subnodes.empty()) { res += "\n"; }
                    break;
                }
                case K::Paragraph: {
                    res += node.text.value();
                    break;
                }
                default: {
                }
            }

            for (auto const& it : enumerator(node.subnodes)) {
                if (!it.is_first()) { res += "\n"; }
                if (node.kind == K::Subtree) { res += "\n"; }
                aux_format(res, it.value(), level + 1);
            }
        };

        Str expected_format;
        aux_format(expected_format, node, 0);
        QCOMPARE_EQ(api.getFormat(), expected_format);
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
