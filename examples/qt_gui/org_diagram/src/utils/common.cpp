#include "common.hpp"
#include <hstd/stdlib/algorithms.hpp>
#include <qsortfilterproxymodel.h>
#include <hstd/stdlib/Map.hpp>
#include <src/model/DiaVersionStore.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <QModelIndex>
#include <hstd/ext/log_graph_tracker_qt.hpp>

static std::shared_ptr<hstd::log::log_graph_tracker> tracker = nullptr;
static std::shared_ptr<hstd::log::graphviz_processor>
    graph_processor = nullptr;
static std::shared_ptr<hstd::log::logger_processor>
    log_processor = nullptr;

std::shared_ptr<hstd::log::log_graph_tracker> get_tracker() {

    if (tracker.get() == nullptr) {
        tracker         = std::make_shared<hstd::log::log_graph_tracker>();
        graph_processor = std::make_shared<
            hstd::log::graphviz_processor>();
        tracker->add_processor(graph_processor);
        log_processor = std::make_shared<hstd::log::logger_processor>();
        tracker->add_processor(log_processor);
    }

    return tracker;
}

inline hstd::ColText escape_literal(hstd::ColText const& in) {
    hstd::ColText res;
    res.reserve(in.size() + 2);
    res.append(hstd::ColText{"«"});
    for (hstd::ColRune const& c : in) {
        if (c.rune == "\n") {
            res.append({"␤"});

        } else {
            res.append(c);
        }
    }

    res.append(hstd::ColText{"»"});

    return res;
}


hstd::ext::Graphviz::Graph get_tracker_graph() {
    return graph_processor->get_graphviz();
}

void customMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg_in) {
    QByteArray  localMsg = msg_in.toLocal8Bit();
    std::string lvl;

    switch (type) {
        case QtDebugMsg: lvl = "DEBUG"; break;
        case QtInfoMsg: lvl = "INFO"; break;
        case QtWarningMsg: lvl = "WARN"; break;
        case QtCriticalMsg: lvl = "CRIT"; break;
        case QtFatalMsg: lvl = "FATAL";
    }

    std::string loc = hstd::fmt(
        "[{}:{}] {} ({}, {}:{})",
        lvl,
        context.category,
        localMsg.constData(),
        context.function ? context.function : "?",
        context.file ? context.file : "?",
        context.line);

    if (type == QtFatalMsg || type == QtCriticalMsg) {
        std::cerr << loc << std::endl;
        if (type == QtFatalMsg) { abort(); }
    } else {
        std::cout << loc << std::endl;
    }
}

hstd::fs::path getDebugFile(QObject* testClass, const hstd::Str& suffix) {
    auto dir = std::filesystem::temp_directory_path()
             / hstd::fs::path{hstd::fmt(
                 "haxorg_tests/{}", testClass->metaObject()->className())};

    if (auto func = QTest::currentTestFunction(); func != nullptr) {
        dir = dir / hstd::fs::path{func};
    }

    if (auto tag = QTest::currentDataTag(); tag != nullptr) {
        dir = dir / hstd::fs::path{tag};
    }

    hstd::createDirectory(hstd::fs::path{dir.native()});

    if (!suffix.empty()) { dir = dir / suffix.toBase(); }

    return dir;
}

hstd::finally_std trackTestExecution(
    QObject*         testClas,
    const hstd::Str& suffix,
    int              line,
    const char*      function,
    const char*      file) {

    auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED([testClas]() {
        return ::hstd::log::init_file_sink(
            getDebugFile(testClas, "execution_trace.log").native());
    });

    auto loc = ::hstd::log::log_graph_processor::tracked_info{
        ::hstd::log::log_graph_processor::callsite(line, function, file)};

    get_tracker()->start_tracing(loc);
    HSLOG_INFO("org.test", "track test execution");
    return hstd::finally_std{
        [testClas,
         suffix,
         loc,
         scoped = std::make_shared<decltype(__log_scoped)>(
             std::move(__log_scoped))]() {
            get_tracker()->end_tracing(loc);
            if (get_tracker_graph().nodeCount() != 0) {
                get_tracker_graph().render(
                    getDebugFile(testClas, "execution_graph.png"));
            }
        }};
}


QModelIndex mapToNestedSource(const QModelIndex& index) {
    QModelIndex currentIndex = index;
    auto currentProxyModel   = qobject_cast<QSortFilterProxyModel const*>(
        index.model());

    while (currentProxyModel) {
        LOGIC_ASSERTION_CHECK(
            currentIndex.model() == currentProxyModel,
            "Index to wrong model passed to mapToSource: index is {}, "
            "model is {}",
            qdebug_to_str(currentIndex),
            qdebug_to_str(currentProxyModel));

        // Proxy model might potentially create indices that are not backed
        // by any source model elements.
        if (currentIndex.internalPointer() == nullptr) {
            break;
        } else {
            currentIndex = currentProxyModel->mapToSource(currentIndex);
            currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
                currentProxyModel->sourceModel());
        }
    }

    return currentIndex;
}

QModelIndex mapToNestedProxy(
    const QModelIndex&                index,
    hstd::Vec<QSortFilterProxyModel*> proxies) {
    QModelIndex currentIndex = index;

    for (QSortFilterProxyModel* proxyModel : proxies) {
        currentIndex = proxyModel->mapFromSource(currentIndex);
    }

    return currentIndex;
}


namespace {
struct ModelProxyRecord {
    QModelIndex index;
};

struct IndexRoleRepr {
    hstd::Str roleName;
    hstd::Str roleValue;
};

struct ModelLevelRecord {
    int                         depth;
    hstd::Vec<ModelProxyRecord> proxies;
    hstd::ColText               finalRepr;
    hstd::Vec<IndexRoleRepr>    roles;
};

void recurse_tree(
    QModelIndex const&            index,
    int                           level,
    QHash<int, QByteArray> const& role_names,
    hstd::Vec<ModelLevelRecord>&  records,
    bool                          ignoreExceptions,
    const QAbstractItemModel*     model,
    hstd::Opt<hstd::Func<hstd::ColText(QModelIndex const&)>> toString,
    hstd::Opt<int>                                           maxDepth) {
    if (maxDepth && *maxDepth < level) { return; }

    ModelLevelRecord record{.depth = level};

    QModelIndex currentIndex = index;
    auto currentProxyModel   = qobject_cast<QSortFilterProxyModel const*>(
        index.model());
    hstd::Vec<int> roles = hstd::sorted(
        role_names.keys() | hstd::rs::to<hstd::Vec>(),
        std::less_equal<int>{});


    for (int role : roles) {
        QByteArray    role_name = role_names[role];
        IndexRoleRepr repr;
        repr.roleName = role_name.toStdString();
        auto act      = [&]() {
            QVariant value = index.data(role);
            if (value.isValid()) {
                if (value.typeName() == "QString"_ss) {
                    repr.roleValue = value.toString().toStdString();
                } else {
                    repr.roleValue = qdebug_to_str(value);
                }
                record.roles.push_back(repr);
            }
        };

        if (ignoreExceptions) {
            try {
                act();
            } catch (std::exception& ex) {
                repr.roleValue = hstd::fmt(
                    "Exception {} {}", typeid(ex).name(), ex.what());
                record.roles.push_back(repr);
            }
        } else {
            act();
        }
    }

    auto add_proxy = [&](QModelIndex const& index) {
        record.proxies.push_back(ModelProxyRecord{.index = index});
    };

    add_proxy(currentIndex);

    while (currentProxyModel) {
        Q_ASSERT(currentIndex.model() != nullptr);
        Q_ASSERT(currentProxyModel->sourceModel() != nullptr);
        if (!currentProxyModel->sourceModel()->hasIndex(
                currentIndex.row(), currentIndex.column())) {
            break;
        }

        auto mapped = currentProxyModel->mapToSource(currentIndex);
        if (mapped.isValid()) {
            currentIndex = mapped;
            add_proxy(currentIndex);
            currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
                currentProxyModel->sourceModel());
        } else {
            break;
        }
    }

    if (toString) { record.finalRepr = (*toString)(index); }
    records.push_back(record);

    int rowCount = model->rowCount(index);
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex sub = model->index(row, 0, index);
        recurse_tree(
            sub,
            level + 1,
            role_names,
            records,
            ignoreExceptions,
            model,
            toString,
            maxDepth);
    }
}

hstd::ColText format_records(hstd::CVec<ModelLevelRecord> records) {
    hstd::ColStream os;

    hstd::UnorderedMap<QAbstractItemModel const*, hstd::Str> model_names;
    for (auto const& level : records) {
        for (auto const& proxy : level.proxies) {
            if (!model_names.contains(proxy.index.model())) {
                if (proxy.index.model() == nullptr) {
                    model_names.insert_or_assign(
                        proxy.index.model(), "0x0");
                } else if (proxy.index.model()->objectName().isEmpty()) {
                    model_names.insert_or_assign(
                        proxy.index.model(),
                        hstd::fmt("M{}", model_names.size()));
                } else {
                    model_names.insert_or_assign(
                        proxy.index.model(),
                        proxy.index.model()->objectName().toStdString());
                }
            }
        }
    }

    for (auto const& level : hstd::enumerator(records)) {
        auto const& l = level.value();
        os << std::string(l.depth * 2, ' ');
        for (auto const& proxy : enumerator(l.proxies)) {
            if (proxy.is_first()) {
                os << " ";
            } else {
                os << "->";
            }

            auto const& p = proxy.value();
            os << "["
               //
               << os.cyan() << hstd::fmt1(p.index.row()) << os.end() << ":"
               << os.cyan() << hstd::fmt1(p.index.column()) << os.end()
               << ","
               //
               << os.green()
               << hstd::fmt("@{:p}", p.index.internalPointer())
               << os.end()
               //
               << ", " << os.red() << model_names.at(p.index.model())
               << os.end() << "]";
            ;
        }

        auto splitFinalRepr = hstd::split(l.finalRepr, "\n");
        if (splitFinalRepr.empty()) {}
        if (splitFinalRepr.size() == 1) {
            os << " "
               << hstd::ColText{escape_literal(splitFinalRepr.at(0))};
        } else {
            for (auto const& line : splitFinalRepr) {
                os << "\n";
                os.indent(l.depth * 2 + 2);
                os << " >> " << line;
            }
        }


        for (auto const& role : l.roles) {
            os << "\n";
            os << std::string(l.depth * 2 + 3, ' ');
            os << os.green() << role.roleName << os.end() << " = ";
            if (role.roleValue.contains("\n")) {
                os << "\n";
                auto lines = role.roleValue.split("\n");
                for (auto const& line : enumerator(lines)) {
                    os << hstd::Str(" ").repeated(l.depth * 2 + 3) << "| "
                       << os.yellow() << line.value() << os.end();
                    if (!line.is_last()) { os << "\n"; }
                }
            } else {
                os << os.yellow() << role.roleValue << os.end();
            }
        }

        if (!level.is_last()) { os << "\n"; }
    }

    return os.getBuffer();
}

} // namespace

hstd::ColText printModelTree(
    const QAbstractItemModel*                                model,
    const QModelIndex&                                       parent,
    hstd::Opt<hstd::Func<hstd::ColText(QModelIndex const&)>> toString,
    bool           ignoreExceptions,
    hstd::Opt<int> maxDepth) {
    if (!model) { return hstd::ColText{""}; }


    QHash<int, QByteArray> role_names = model->roleNames();

    for (auto const& it : role_names.keys()) {
        if (it != Qt::DisplayRole      //
            && it != Qt::WhatsThisRole //
            && it < Qt::UserRole) {
            role_names.remove(it);
        }
    }

    hstd::Vec<ModelLevelRecord> records;

    recurse_tree(
        parent,
        0,
        role_names,
        records,
        ignoreExceptions,
        model,
        toString,
        maxDepth);

    return format_records(records);
}

bool hasProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind) {
    return node.getProperty(kind).has_value();
}

outcome::result<const org::sem::AttrGroup*, std::string> getFlagProperty(
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& node,
    const std::string&                                 kind) {
    BOOST_OUTCOME_TRY_OPTIONAL(
        property,
        node.getProperty(kind),
        hstd::fmt("Property '{}' not found", kind));
    BOOST_OUTCOME_TRY_SUB_VARIANT(json_data, property, CustomSubtreeFlags);
    return &json_data.value;
}

bool hasJsonProperty(
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& node,
    const std::string&                                 kind) {
    return node.getProperty("propjson", kind).has_value();
}

bool hasArgsProperty(
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& node,
    const std::string&                                 kind) {
    return node.getProperty("propargs", kind).has_value();
}

hstd::Vec<hstd::ColText> hstd::split(
    ColText const& text,
    Str const&     delimiter) {
    hstd::Vec<ColText> result;
    ColText            current;

    for (int i = 0; i < text.size(); ++i) {
        if (text.at(i).rune == delimiter) {
            result.push_back(current);
            current.clear();
        } else {
            current.push_back(text.at(i));
        }
    }

    result.push_back(current);
    return result;
}

void q_register_metatypes() {
    qRegisterMetaType<DiaVersionStore::EditTarget>();
    qRegisterMetaType<DiaVersionStore::EditCmd>();
    qRegisterMetaType<DiaVersionStore::EditGroup>();
    qRegisterMetaType<DiaVersionStore::EditApplyResult>();
    qRegisterMetaType<DiaVersionStore::DiaRootChange>();
}


void SignalDebugger::connectToAllSignals() {
    if (!targetObject) { return; }

    const QMetaObject* metaObject = targetObject->metaObject();

    for (int i = 0; i < metaObject->methodCount(); ++i) {
        QMetaMethod method = metaObject->method(i);
        if (method.methodType() == QMetaMethod::Signal) {
            connectToSignal(method);
        }
    }
}

void SignalDebugger::connectToSignal(const QMetaMethod& signal) {
    QString    signalSignature     = signal.methodSignature();
    QByteArray normalizedSignature = QMetaObject::normalizedSignature(
        signalSignature.toLocal8Bit());

    QMetaObject::Connection conn = QObject::connect(
        targetObject,
        ("2" + normalizedSignature).constData(),
        this,
        SLOT(onSignalTriggered()),
        Qt::DirectConnection);

    connections.push_back(conn);
}

void SignalDebugger::disconnectAll() {
    for (auto& conn : connections) { QObject::disconnect(conn); }
    connections.clear();
}

void SignalDebugger::onSignalTriggered() {
    QObject* senderObj = sender();
    if (!senderObj) { return; }

    const QMetaObject* senderMeta  = senderObj->metaObject();
    int                signalIndex = senderSignalIndex();

    if (signalIndex >= 0) {
        QMetaMethod signal = senderMeta->method(signalIndex);

        tracker->notify_signal_emit(
            hstd::log::log_graph_processor::signal_emit_info(
                senderObj,
                hstd::log::log_graph_processor::function_info(
                    signal.name().toStdString(),
                    formatParameterInfo(signal),
                    hstd::log::log_graph_processor::callsite::
                        this_callsite())));
    }
}

hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> SignalDebugger::
    formatParameterInfo(const QMetaMethod& method) {
    QList<QByteArray> paramNames = method.parameterNames();
    QList<QByteArray> paramTypes = method.parameterTypes();

    if (paramNames.size() != paramTypes.size()) { return {}; }
    hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> debug{};
    for (int i = 0; i < paramNames.size(); ++i) {
        debug.push_back(
            {paramTypes.at(i).toStdString(),
             paramNames.at(i).toStdString()});
    }

    return debug;
}
