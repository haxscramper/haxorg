#pragma once

#include <QtTest>
#include <editor/editor_lib/main_gui/mainwindow.hpp>
#include <editor/editor_lib/common/app_init.hpp>
#include <editor/editor_lib/common/app_utils.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <hstd/stdlib/Enumerate.hpp>

using osk = OrgSemKind;

inline Vec<OrgBoxId> dfs_boxes(OrgTreeNode const* node) {
    Vec<OrgBoxId> result{node->boxId};
    for (auto const& sub : node->subnodes) {
        result.append(dfs_boxes(sub.get()));
    }

    return result;
}

struct test_error : CRTP_hexception<test_error> {};

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
    CR<QModelIndex>           index    = QModelIndex(),
    int                       line     = __builtin_LINE(),
    char const*               function = __builtin_FUNCTION(),
    char const*               file     = __builtin_FILE()) {
    qDebug().noquote().nospace()
        << fmt("{}:{} {}", file, line, function) << "\n"
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

    void debug(
        CR<QModelIndex> index    = QModelIndex(),
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION(),
        char const*     file     = __builtin_FILE()) {
        ::debug_tree(
            edit->model(),
            edit->docModel->store,
            index,
            line,
            function,
            file);
    }

    sem::SemId<sem::Org> getNode() const {
        return edit->docModel->toNode();
    };

    sem::SemId<sem::Org> getNode(CVec<int> path) const {
        auto index = getIndex(path);
        auto t     = edit->docModel->tree(index);
        Q_ASSERT_X(
            t != nullptr, "getNode", fmt("path:{} index:{}", path, index));
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
        auto res = ::getAtQModelPath(edit->model(), path);
        Q_ASSERT_X(
            res.isValid(), "getIndex", fmt("path:{} index:{}", path, res));
        return res;
    }

    OrgBoxId id(CVec<int> path) const { return tree(path)->id(); }

    OrgTreeNode* tree(CVec<int> path) const {
        return edit->docModel->root->at(path);
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

    void compare(TestApiAccessor const& api, CR<TestDocumentNode> node);
    void compare_structure(
        TestApiAccessor const& api,
        CR<TestDocumentNode>   node);
    void compare_format(
        TestApiAccessor const& api,
        CR<TestDocumentNode>   node);
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
#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession> tracing;
#endif

    void init_test_base();
    void cleanup_test_base();
};


class AbstractItemModelSignalListener : public QObject {
    Q_OBJECT

  public:
    QAbstractItemModel* model;
    struct Record {
        struct DataChanged {
            QObject const* sender;
            QModelIndex    topLeft;
            QModelIndex    bottomRight;
            QList<int>     roles;
            DESC_FIELDS(
                DataChanged,
                (sender, topLeft, bottomRight, roles));
        };

        struct HeaderDataChanged {
            QObject const*  sender;
            Qt::Orientation orientation;
            int             first;
            int             last;
            DESC_FIELDS(
                HeaderDataChanged,
                (sender, orientation, first, last));
        };

        struct LayoutChanged {
            QObject const*                       sender;
            QList<QPersistentModelIndex>         parents;
            QAbstractItemModel::LayoutChangeHint hint;
            DESC_FIELDS(LayoutChanged, (sender, parents, hint));
        };

        struct LayoutAboutToBeChanged {
            QObject const*                       sender;
            QList<QPersistentModelIndex>         parents;
            QAbstractItemModel::LayoutChangeHint hint;
            DESC_FIELDS(LayoutAboutToBeChanged, (sender, parents, hint));
        };

        struct RowsAboutToBeInserted {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(
                RowsAboutToBeInserted,
                (sender, parent, first, last));
        };

        struct RowsInserted {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(RowsInserted, (sender, parent, first, last));
        };

        struct RowsAboutToBeRemoved {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(
                RowsAboutToBeRemoved,
                (sender, parent, first, last));
        };

        struct RowsRemoved {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(RowsRemoved, (sender, parent, first, last));
        };

        struct ColumnsAboutToBeInserted {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(
                ColumnsAboutToBeInserted,
                (sender, parent, first, last));
        };

        struct ColumnsInserted {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(ColumnsInserted, (sender, parent, first, last));
        };

        struct ColumnsAboutToBeRemoved {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(
                ColumnsAboutToBeRemoved,
                (sender, parent, first, last));
        };

        struct ColumnsRemoved {
            QObject const* sender;
            QModelIndex    parent;
            int            first;
            int            last;
            DESC_FIELDS(ColumnsRemoved, (sender, parent, first, last));
        };

        struct ModelAboutToBeReset {
            QObject const* sender;
            DESC_FIELDS(ModelAboutToBeReset, (sender));
        };

        struct ModelReset {
            QObject const* sender;
            DESC_FIELDS(ModelReset, (sender));
        };

        struct RowsAboutToBeMoved {
            QObject const* sender;
            QModelIndex    sourceParent;
            int            sourceStart;
            int            sourceEnd;
            QModelIndex    destinationParent;
            int            destinationRow;
            DESC_FIELDS(
                RowsAboutToBeMoved,
                (sender,
                 sourceParent,
                 sourceStart,
                 sourceEnd,
                 destinationParent,
                 destinationRow));
        };

        struct RowsMoved {
            QObject const* sender;
            QModelIndex    sourceParent;
            int            sourceStart;
            int            sourceEnd;
            QModelIndex    destinationParent;
            int            destinationRow;
            DESC_FIELDS(
                RowsMoved,
                (sender,
                 sourceParent,
                 sourceStart,
                 sourceEnd,
                 destinationParent,
                 destinationRow));
        };

        struct ColumnsAboutToBeMoved {
            QObject const* sender;
            QModelIndex    sourceParent;
            int            sourceStart;
            int            sourceEnd;
            QModelIndex    destinationParent;
            int            destinationColumn;
            DESC_FIELDS(
                ColumnsAboutToBeMoved,
                (sender,
                 sourceParent,
                 sourceStart,
                 sourceEnd,
                 destinationParent,
                 destinationColumn));
        };

        struct ColumnsMoved {
            QObject const* sender;
            QModelIndex    sourceParent;
            int            sourceStart;
            int            sourceEnd;
            QModelIndex    destinationParent;
            int            destinationColumn;
            DESC_FIELDS(
                ColumnsMoved,
                (sender,
                 sourceParent,
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

        std::string toString() const;
    };

    template <typename T>
    Vec<T> getRecordsT() const {
        Vec<T> result;
        for (auto const& it : records) {
            if (std::holds_alternative<T>(it.data)) {
                result.push_back(std::get<T>(it.data));
            }
        }

        return result;
    }

    template <typename T>
    int countT() const {
        return getRecordsT<T>().size();
    }

    int count(Record::Kind kind) {
        int result = 0;
        for (auto const& it : records) {
            if (it.getKind() == kind) { ++result; }
        }

        return result;
    }

    int indexOf(Record::Kind kind) {
        int result = -1;
        for (auto const& it : enumerator(records)) {
            if (it.value().getKind() == kind) { return it.index(); }
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

    void debug() {
        for (auto const& q : records) { _qfmt("-> {}", q.toString()); }
    }

    AbstractItemModelSignalListener(QAbstractItemModel* model);

    Vec<Record> records;
    bool        printOnTrigger = false;

    void addRecord(CR<Record> record);

    void assertEq(CR<AbstractItemModelSignalListener> other);

  private slots:
    void onDataChanged(
        const QModelIndex& topLeft,
        const QModelIndex& bottomRight,
        const QList<int>&  roles) {
        addRecord({Record::DataChanged{
            .sender      = sender(),
            .topLeft     = topLeft,
            .bottomRight = bottomRight,
            .roles       = roles,
        }});
    }

    void onHeaderDataChanged(
        Qt::Orientation orientation,
        int             first,
        int             last) {
        addRecord({Record::HeaderDataChanged{
            .sender      = sender(),
            .orientation = orientation,
            .first       = first,
            .last        = last,
        }});
    }

    void onLayoutChanged(
        const QList<QPersistentModelIndex>&  parents,
        QAbstractItemModel::LayoutChangeHint hint) {
        addRecord({Record::LayoutChanged{
            .sender  = sender(),
            .parents = parents,
            .hint    = hint,
        }});
    }

    void onLayoutAboutToBeChanged(
        const QList<QPersistentModelIndex>&  parents,
        QAbstractItemModel::LayoutChangeHint hint) {
        addRecord({Record::LayoutAboutToBeChanged{
            .sender  = sender(),
            .parents = parents,
            .hint    = hint,
        }});
    }

    void onRowsAboutToBeInserted(
        const QModelIndex& parent,
        int                first,
        int                last) {
        addRecord({Record::RowsAboutToBeInserted{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onRowsInserted(const QModelIndex& parent, int first, int last) {
        addRecord({Record::RowsInserted{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onRowsAboutToBeRemoved(
        const QModelIndex& parent,
        int                first,
        int                last) {
        addRecord({Record::RowsAboutToBeRemoved{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onRowsRemoved(const QModelIndex& parent, int first, int last) {
        addRecord({Record::RowsRemoved{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsAboutToBeInserted(
        const QModelIndex& parent,
        int                first,
        int                last) {
        addRecord({Record::ColumnsAboutToBeInserted{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsInserted(
        const QModelIndex& parent,
        int                first,
        int                last) {
        addRecord({Record::ColumnsInserted{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsAboutToBeRemoved(
        const QModelIndex& parent,
        int                first,
        int                last) {
        addRecord({Record::ColumnsAboutToBeRemoved{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onColumnsRemoved(const QModelIndex& parent, int first, int last) {
        addRecord({Record::ColumnsRemoved{
            .sender = sender(),
            .parent = parent,
            .first  = first,
            .last   = last,
        }});
    }

    void onModelAboutToBeReset() {
        addRecord({Record::ModelAboutToBeReset{
            .sender = sender(),
        }});
    }

    void onModelReset() {
        addRecord({Record::ModelReset{
            .sender = sender(),
        }});
    }


    void onRowsAboutToBeMoved(
        const QModelIndex& sourceParent,
        int                sourceStart,
        int                sourceEnd,
        const QModelIndex& destinationParent,
        int                destinationRow) {
        addRecord({Record::RowsAboutToBeMoved{
            .sender            = sender(),
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
        addRecord({Record::RowsMoved{
            .sender            = sender(),
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
        addRecord({Record::ColumnsAboutToBeMoved{
            .sender            = sender(),
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
        addRecord({Record::ColumnsMoved{
            .sender            = sender(),
            .sourceParent      = sourceParent,
            .sourceStart       = sourceStart,
            .sourceEnd         = sourceEnd,
            .destinationParent = destinationParent,
            .destinationColumn = destinationColumn,
        }});
    }
};
