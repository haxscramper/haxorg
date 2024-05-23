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

namespace {
const std::string perfetto_trace_name{"PERFETTO_TRACE_PATH"};
Opt<Str>          getPerfTrace() {
    if (getenv(perfetto_trace_name.c_str())
        && !Str{getenv(perfetto_trace_name.c_str())}.empty()) {
        return Str{getenv(perfetto_trace_name.c_str())};
    } else {
        return std::nullopt;
    }
}
} // namespace

void TestBase::init_test_base() {
    editorInitMain();
    pre_test_handler = qInstallMessageHandler(test_message_handler);


    if (getPerfTrace()) {
        InitializePerfetto();
        tracing = StartTracing();
    }
}

void TestBase::cleanup_test_base() {
    qInstallMessageHandler(pre_test_handler);
    if (getPerfTrace()) {
        Q_ASSERT(tracing.get() != nullptr);
        StopTracing(std::move(tracing), *getPerfTrace());
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

void AbstractItemModelSignalListener::addRecord(CR<Record> record) {
    if (printOnTrigger) {
        _qfmt(
            "<{}> {}",
            std::visit(
                [](auto const& it) -> std::string {
                    if (it.sender == nullptr) {
                        return "?";
                    } else if (it.sender->objectName().isEmpty()) {
                        return fmt("{:p}", (void*)it.sender);
                    } else {
                        return it.sender->objectName().toStdString();
                    }
                },
                record.data),
            record.toString());
    }
    records.push_back(record);
}

std::string AbstractItemModelSignalListener::Record::toString() const {
    std::string text;
    switch (getKind()) {
            // clang-format off
                case Kind::DataChanged: text = fmt1(std::get<DataChanged>(data)); break;
                case Kind::HeaderDataChanged: text = fmt1(std::get<HeaderDataChanged>(data)); break;
                case Kind::LayoutChanged: text = fmt1(std::get<LayoutChanged>(data)); break;
                case Kind::LayoutAboutToBeChanged: text = fmt1(std::get<LayoutAboutToBeChanged>(data)); break;
                case Kind::RowsAboutToBeInserted: text = fmt1(std::get<RowsAboutToBeInserted>(data)); break;
                case Kind::RowsInserted: text = fmt1(std::get<RowsInserted>(data)); break;
                case Kind::RowsAboutToBeRemoved: text = fmt1(std::get<RowsAboutToBeRemoved>(data)); break;
                case Kind::RowsRemoved: text = fmt1(std::get<RowsRemoved>(data)); break;
                case Kind::ColumnsAboutToBeInserted: text = fmt1(std::get<ColumnsAboutToBeInserted>(data)); break;
                case Kind::ColumnsInserted: text = fmt1(std::get<ColumnsInserted>(data)); break;
                case Kind::ColumnsAboutToBeRemoved: text = fmt1(std::get<ColumnsAboutToBeRemoved>(data)); break;
                case Kind::ColumnsRemoved: text = fmt1(std::get<ColumnsRemoved>(data)); break;
                case Kind::ModelAboutToBeReset: text = fmt1(std::get<ModelAboutToBeReset>(data)); break;
                case Kind::ModelReset: text = fmt1(std::get<ModelReset>(data)); break;
                case Kind::RowsAboutToBeMoved: text = fmt1(std::get<RowsAboutToBeMoved>(data)); break;
                case Kind::RowsMoved: text = fmt1(std::get<RowsMoved>(data)); break;
                case Kind::ColumnsAboutToBeMoved: text = fmt1(std::get<ColumnsAboutToBeMoved>(data)); break;
                case Kind::ColumnsMoved: text = fmt1(std::get<ColumnsMoved>(data)); break;
                default: { qFatal("???"); }
            // clang-format on
    }

    return fmt("{} {}", getKind(), text);
}
