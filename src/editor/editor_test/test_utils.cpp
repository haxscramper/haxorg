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
            || (msg.contains("is different from this scene") && msg.contains("QGraphicsScene::removeItem"))
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

void AbstractItemModelSignalListener::debug() {
    for (auto const& q : records) {
        std::string text;
        switch (q.getKind()) {
                // clang-format off
                case Record::Kind::DataChanged: text = fmt1(std::get<Record::DataChanged>(q.data)); break;
                case Record::Kind::HeaderDataChanged: text = fmt1(std::get<Record::HeaderDataChanged>(q.data)); break;
                case Record::Kind::LayoutChanged: text = fmt1(std::get<Record::LayoutChanged>(q.data)); break;
                case Record::Kind::LayoutAboutToBeChanged: text = fmt1(std::get<Record::LayoutAboutToBeChanged>(q.data)); break;
                case Record::Kind::RowsAboutToBeInserted: text = fmt1(std::get<Record::RowsAboutToBeInserted>(q.data)); break;
                case Record::Kind::RowsInserted: text = fmt1(std::get<Record::RowsInserted>(q.data)); break;
                case Record::Kind::RowsAboutToBeRemoved: text = fmt1(std::get<Record::RowsAboutToBeRemoved>(q.data)); break;
                case Record::Kind::RowsRemoved: text = fmt1(std::get<Record::RowsRemoved>(q.data)); break;
                case Record::Kind::ColumnsAboutToBeInserted: text = fmt1(std::get<Record::ColumnsAboutToBeInserted>(q.data)); break;
                case Record::Kind::ColumnsInserted: text = fmt1(std::get<Record::ColumnsInserted>(q.data)); break;
                case Record::Kind::ColumnsAboutToBeRemoved: text = fmt1(std::get<Record::ColumnsAboutToBeRemoved>(q.data)); break;
                case Record::Kind::ColumnsRemoved: text = fmt1(std::get<Record::ColumnsRemoved>(q.data)); break;
                case Record::Kind::ModelAboutToBeReset: text = fmt1(std::get<Record::ModelAboutToBeReset>(q.data)); break;
                case Record::Kind::ModelReset: text = fmt1(std::get<Record::ModelReset>(q.data)); break;
                case Record::Kind::RowsAboutToBeMoved: text = fmt1(std::get<Record::RowsAboutToBeMoved>(q.data)); break;
                case Record::Kind::RowsMoved: text = fmt1(std::get<Record::RowsMoved>(q.data)); break;
                case Record::Kind::ColumnsAboutToBeMoved: text = fmt1(std::get<Record::ColumnsAboutToBeMoved>(q.data)); break;
                case Record::Kind::ColumnsMoved: text = fmt1(std::get<Record::ColumnsMoved>(q.data)); break;
                default: { qFatal("???"); }
                // clang-format on
        }

        _qfmt("-> {} {}", q.getKind(), text);
    }
}

AbstractItemModelSignalListener::AbstractItemModelSignalListener(
    QAbstractItemModel* model) {
    // clang-format off
        connect(model, &QAbstractItemModel::dataChanged, this, &AbstractItemModelSignalListener::onDataChanged);
        connect(model, &QAbstractItemModel::headerDataChanged, this, &AbstractItemModelSignalListener::onHeaderDataChanged);
        connect(model, &QAbstractItemModel::layoutChanged, this, &AbstractItemModelSignalListener::onLayoutChanged);
        connect(model, &QAbstractItemModel::layoutAboutToBeChanged, this, &AbstractItemModelSignalListener::onLayoutAboutToBeChanged);
        connect(model, &QAbstractItemModel::rowsAboutToBeInserted, this, &AbstractItemModelSignalListener::onRowsAboutToBeInserted);
        connect(model, &QAbstractItemModel::rowsInserted, this, &AbstractItemModelSignalListener::onRowsInserted);
        connect(model, &QAbstractItemModel::rowsAboutToBeRemoved, this, &AbstractItemModelSignalListener::onRowsAboutToBeRemoved);
        connect(model, &QAbstractItemModel::rowsRemoved, this, &AbstractItemModelSignalListener::onRowsRemoved);
        connect(model, &QAbstractItemModel::columnsAboutToBeInserted, this, &AbstractItemModelSignalListener::onColumnsAboutToBeInserted);
        connect(model, &QAbstractItemModel::columnsInserted, this, &AbstractItemModelSignalListener::onColumnsInserted);
        connect(model, &QAbstractItemModel::columnsAboutToBeRemoved, this, &AbstractItemModelSignalListener::onColumnsAboutToBeRemoved);
        connect(model, &QAbstractItemModel::columnsRemoved, this, &AbstractItemModelSignalListener::onColumnsRemoved);
        connect(model, &QAbstractItemModel::modelAboutToBeReset, this, &AbstractItemModelSignalListener::onModelAboutToBeReset);
        connect(model, &QAbstractItemModel::modelReset, this, &AbstractItemModelSignalListener::onModelReset);
        connect(model, &QAbstractItemModel::rowsAboutToBeMoved, this, &AbstractItemModelSignalListener::onRowsAboutToBeMoved);
        connect(model, &QAbstractItemModel::rowsMoved, this, &AbstractItemModelSignalListener::onRowsMoved);
        connect(model, &QAbstractItemModel::columnsAboutToBeMoved, this, &AbstractItemModelSignalListener::onColumnsAboutToBeMoved);
        connect(model, &QAbstractItemModel::columnsMoved, this, &AbstractItemModelSignalListener::onColumnsMoved);
    // clang-format on
}
