#pragma once

#include <QtTest>
#include <editor/editor_lib/main_gui/mainwindow.hpp>
#include <editor/editor_lib/common/app_init.hpp>
#include <editor/editor_lib/common/app_utils.hpp>
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
    return store->getBoxedNode(qvariant_cast<OrgBoxId>(index.data()));
}

inline sem::SemId<sem::Org> node(
    OrgStore*          store,
    OrgTreeNode const* tree) {
    return store->getBoxedNode(tree->boxId);
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


class AbstractItemModelSignalListener : public QObject {
    Q_OBJECT

  public:
    struct Record {
        struct DataChanged {
            QModelIndex topLeft;
            QModelIndex bottomRight;
            QList<int>  roles;
            DESC_FIELDS(DataChanged, (topLeft, bottomRight, roles));
        };

        struct HeaderDataChanged {
            Qt::Orientation orientation;
            int             first;
            int             last;
            DESC_FIELDS(HeaderDataChanged, (orientation, first, last));
        };

        struct LayoutChanged {
            QList<QPersistentModelIndex>         parents;
            QAbstractItemModel::LayoutChangeHint hint;
            DESC_FIELDS(LayoutChanged, (parents, hint));
        };

        struct LayoutAboutToBeChanged {
            QList<QPersistentModelIndex>         parents;
            QAbstractItemModel::LayoutChangeHint hint;
            DESC_FIELDS(LayoutAboutToBeChanged, (parents, hint));
        };

        struct RowsAboutToBeInserted {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(RowsAboutToBeInserted, (parent, first, last));
        };

        struct RowsInserted {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(RowsInserted, (parent, first, last));
        };

        struct RowsAboutToBeRemoved {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(RowsAboutToBeRemoved, (parent, first, last));
        };

        struct RowsRemoved {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(RowsRemoved, (parent, first, last));
        };

        struct ColumnsAboutToBeInserted {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(ColumnsAboutToBeInserted, (parent, first, last));
        };

        struct ColumnsInserted {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(ColumnsInserted, (parent, first, last));
        };

        struct ColumnsAboutToBeRemoved {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(ColumnsAboutToBeRemoved, (parent, first, last));
        };

        struct ColumnsRemoved {
            QModelIndex parent;
            int         first;
            int         last;
            DESC_FIELDS(ColumnsRemoved, (parent, first, last));
        };

        struct ModelAboutToBeReset {
            DESC_FIELDS(ModelAboutToBeReset, ());
        };
        struct ModelReset {
            DESC_FIELDS(ModelReset, ());
        };

        struct RowsAboutToBeMoved {
            QModelIndex sourceParent;
            int         sourceStart;
            int         sourceEnd;
            QModelIndex destinationParent;
            int         destinationRow;
            DESC_FIELDS(
                RowsAboutToBeMoved,
                (sourceParent,
                 sourceStart,
                 sourceEnd,
                 destinationParent,
                 destinationRow));
        };

        struct RowsMoved {
            QModelIndex sourceParent;
            int         sourceStart;
            int         sourceEnd;
            QModelIndex destinationParent;
            int         destinationRow;
            DESC_FIELDS(
                RowsMoved,
                (sourceParent,
                 sourceStart,
                 sourceEnd,
                 destinationParent,
                 destinationRow));
        };

        struct ColumnsAboutToBeMoved {
            QModelIndex sourceParent;
            int         sourceStart;
            int         sourceEnd;
            QModelIndex destinationParent;
            int         destinationColumn;
            DESC_FIELDS(
                ColumnsAboutToBeMoved,
                (sourceParent,
                 sourceStart,
                 sourceEnd,
                 destinationParent,
                 destinationColumn));
        };

        struct ColumnsMoved {
            QModelIndex sourceParent;
            int         sourceStart;
            int         sourceEnd;
            QModelIndex destinationParent;
            int         destinationColumn;
            DESC_FIELDS(
                ColumnsMoved,
                (sourceParent,
                 sourceStart,
                 sourceEnd,
                 destinationParent,
                 destinationColumn));
        };


        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            DataChanged,
            HeaderDataChanged,
            LayoutChanged,
            LayoutAboutToBeChanged,
            RowsAboutToBeInserted,
            RowsInserted,
            RowsAboutToBeRemoved,
            RowsRemoved,
            ColumnsAboutToBeInserted,
            ColumnsInserted,
            ColumnsAboutToBeRemoved,
            ColumnsRemoved,
            ModelAboutToBeReset,
            ModelReset,
            RowsAboutToBeMoved,
            RowsMoved,
            ColumnsAboutToBeMoved,
            ColumnsMoved);

        Data data;
        DESC_FIELDS(Record, (data));
    };

    template <typename T>
    Vec<T> getRecordsT() {
        Vec<T> result;
        for (auto const& it : records) {
            if (std::holds_alternative<T>(it.data)) {
                result.push_back(std::get<T>(it.data));
            }
        }

        return result;
    }

    template <typename T>
    Vec<T> popRecordsT() {
        Vec<T> result = getRecordsT<T>();

        records       //
            = records //
            | rv::remove_if([](CR<Record> it) -> bool {
                  return std::holds_alternative<T>(it.data);
              })
            | rs::to<Vec>();

        return result;
    }

    void clear() { records.clear(); }

    void debug();

    AbstractItemModelSignalListener(QAbstractItemModel* model);

    std::vector<Record> records;

  private slots:
    void onDataChanged(
        const QModelIndex& topLeft,
        const QModelIndex& bottomRight,
        const QList<int>&  roles) {
        records.push_back({Record::DataChanged{
            .topLeft     = topLeft,
            .bottomRight = bottomRight,
            .roles       = roles,
        }});
    }

    void onHeaderDataChanged(
        Qt::Orientation orientation,
        int             first,
        int             last) {
        records.push_back({Record::HeaderDataChanged{
            .orientation = orientation,
            .first       = first,
            .last        = last,
        }});
    }

    void onLayoutChanged(
        const QList<QPersistentModelIndex>&  parents,
        QAbstractItemModel::LayoutChangeHint hint) {
        records.push_back({Record::LayoutChanged{
            .parents = parents,
            .hint    = hint,
        }});
    }

    void onLayoutAboutToBeChanged(
        const QList<QPersistentModelIndex>&  parents,
        QAbstractItemModel::LayoutChangeHint hint) {
        records.push_back({Record::LayoutAboutToBeChanged{
            .parents = parents,
            .hint    = hint,
        }});
    }

    void onRowsAboutToBeInserted(
        const QModelIndex& parent,
        int                first,
        int                last) {
        records.push_back({Record::RowsAboutToBeInserted{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onRowsInserted(const QModelIndex& parent, int first, int last) {
        records.push_back({Record::RowsInserted{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onRowsAboutToBeRemoved(
        const QModelIndex& parent,
        int                first,
        int                last) {
        records.push_back({Record::RowsAboutToBeRemoved{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onRowsRemoved(const QModelIndex& parent, int first, int last) {
        records.push_back({Record::RowsRemoved{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsAboutToBeInserted(
        const QModelIndex& parent,
        int                first,
        int                last) {
        records.push_back({Record::ColumnsAboutToBeInserted{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsInserted(
        const QModelIndex& parent,
        int                first,
        int                last) {
        records.push_back({Record::ColumnsInserted{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsAboutToBeRemoved(
        const QModelIndex& parent,
        int                first,
        int                last) {
        records.push_back({Record::ColumnsAboutToBeRemoved{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsRemoved(const QModelIndex& parent, int first, int last) {
        records.push_back({Record::ColumnsRemoved{
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onModelAboutToBeReset() {
        records.push_back({Record::ModelAboutToBeReset{}});
    }

    void onModelReset() { records.push_back({Record::ModelReset{}}); }

    void onRowsAboutToBeMoved(
        const QModelIndex& sourceParent,
        int                sourceStart,
        int                sourceEnd,
        const QModelIndex& destinationParent,
        int                destinationRow) {
        records.push_back({Record::RowsAboutToBeMoved{
            .sourceParent      = sourceParent,
            .sourceStart       = sourceStart,
            .sourceEnd         = sourceEnd,
            .destinationParent = destinationParent,
            .destinationRow    = destinationRow,
        }});
    }

    void onRowsMoved(
        const QModelIndex& sourceParent,
        int                sourceStart,
        int                sourceEnd,
        const QModelIndex& destinationParent,
        int                destinationRow) {
        records.push_back({Record::RowsMoved{
            .sourceParent      = sourceParent,
            .sourceStart       = sourceStart,
            .sourceEnd         = sourceEnd,
            .destinationParent = destinationParent,
            .destinationRow    = destinationRow,
        }});
    }

    void onColumnsAboutToBeMoved(
        const QModelIndex& sourceParent,
        int                sourceStart,
        int                sourceEnd,
        const QModelIndex& destinationParent,
        int                destinationColumn) {
        records.push_back({Record::ColumnsAboutToBeMoved{
            .sourceParent      = sourceParent,
            .sourceStart       = sourceStart,
            .sourceEnd         = sourceEnd,
            .destinationParent = destinationParent,
            .destinationColumn = destinationColumn,
        }});
    }

    void onColumnsMoved(
        const QModelIndex& sourceParent,
        int                sourceStart,
        int                sourceEnd,
        const QModelIndex& destinationParent,
        int                destinationColumn) {
        records.push_back({Record::ColumnsMoved{
            .sourceParent      = sourceParent,
            .sourceStart       = sourceStart,
            .sourceEnd         = sourceEnd,
            .destinationParent = destinationParent,
            .destinationColumn = destinationColumn,
        }});
    }
};
