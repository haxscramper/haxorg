#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <editor/editor_lib/common/app_state.hpp>
#include <editor/editor_lib/common/app_init.hpp>
#include <editor/editor_lib/document/org_document_outline.hpp>
#include <editor/editor_lib/mind_map/org_graph_model.hpp>
#include <editor/editor_lib/mind_map/org_graph_scene.hpp>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMainWindow>
#include <QApplication>


template <typename E, IsVariant Var>
void from_json_variant(CR<Str> variantField, json const& in, Var& out) {
    if (!in.is_object() || !in.contains(variantField)) {
        throw std::domain_error(
            fmt("Input JSON must be an object and have '{}' field",
                variantField));
    }
    if (auto parsed = enum_serde<E>::from_string(in[variantField])) {
        out = variant_from_index<Var>(
            value_domain<E>::ord(parsed.value()));
        std::visit([&](auto& var_item) { from_json(in, var_item); }, out);
    } else {
        throw std::domain_error(
            fmt("'kind' field must be one of {} but got {}",
                enumerator_names<E>(),
                in[variantField].dump()));
    }
}

template <typename E, IsVariant Var>
void to_json_variant(
    CR<Str>    variantField,
    json&      out,
    Var const& in,
    E const&   kind) {

    std::visit([&](auto const& in_item) { to_json(out, in_item); }, in);
    out[variantField] = enum_serde<E>::to_string(kind);
}


struct Action {
    struct MindMap {
        Opt<std::string> screenshotPath;
        DESC_FIELDS(MindMap, (screenshotPath));
    };

    struct None {
        DESC_FIELDS(None, ());
    };

    struct DocumentModel {
        DESC_FIELDS(DocumentModel, ());
    };


    SUB_VARIANTS(Kind, Data, data, getKind, None, DocumentModel, MindMap);

    Data data;
};

struct DriverConfig {
    Vec<Str> input_paths;
    Str      output_path;
    Action   action;

    DESC_FIELDS(DriverConfig, (input_paths, output_path, action));
};


struct ModelDumpIr {

    struct IndexChain {
        std::string modelName;
        // u64              modelAddr;
        // Opt<u64>         internalPtr;
        // Opt<u64>         internalId;
        int row;
        int col;
        DESC_FIELDS(IndexChain, (modelName, row, col));
    };

    struct Row;

    struct Index {
        Vec<IndexChain>                 chain;
        UnorderedMap<std::string, json> roles;
        Vec<SPtr<Row>>                  nested;
        DESC_FIELDS(Index, (chain, roles, nested));
    };

    struct Row {
        Vec<Opt<Index>> columns;
        DESC_FIELDS(Row, (columns));
    };

    Opt<std::string> name; ///< Main model object name
    Index            root;

    DESC_FIELDS(ModelDumpIr, (name, root));
};

struct DriverResult {
    struct DocumentDump {
        ModelDumpIr main_document;
        ModelDumpIr outline_document;
        std::string path;
        DESC_FIELDS(DocumentDump, (main_document, outline_document, path));
    };

    struct MindMapDump {
        ModelDumpIr graphModel;
        std::string graphvizDump;
        ModelDumpIr layoutDump;
        DESC_FIELDS(MindMapDump, (graphModel, graphvizDump, layoutDump));
    };

    Vec<DocumentDump> document_dumps;
    Opt<MindMapDump>  mind_map_dump;


    Action action;
    DESC_FIELDS(DriverResult, (action, document_dumps, mind_map_dump));
};


void from_json(json const& j, Action& out) {
    from_json_variant<Action::Kind>("kind", j, out.data);
}

void to_json(json& j, Action const& in) {
    to_json_variant("kind", j, in.data, in.getKind());
}


ModelDumpIr dumpModelTree(
    QAbstractItemModel*         model,
    const QModelIndex&          parent,
    Func<json(QVariant const&)> dumpValue) {
    ModelDumpIr result;

    Func<ModelDumpIr::Index(CR<QModelIndex>)> aux;
    aux = [&](CR<QModelIndex> index) -> ModelDumpIr::Index {
        ModelDumpIr::Index out;

        auto roles = model->roleNames();
        for (int const& role : roles.keys()) {
            QVariant value = index.data(role);
            if (value.isValid()) {
                out.roles[roles.value(role).toStdString()] = dumpValue(
                    value);
            }
        }

        {
            auto add_proxy = [&](QAbstractItemModel const* proxy_model,
                                 CR<QModelIndex>           index) {
                out.chain.push_back(ModelDumpIr::IndexChain{
                    .row = index.row(),
                    .col = index.column(),
                    .modelName //
                    = model->objectName().isEmpty()
                        ? fmt("{}", (u64)model)
                        : model->objectName().toStdString(),
                });
            };

            add_proxy(model, index);

            QModelIndex currentIndex      = index;
            auto        currentProxyModel = qobject_cast<
                       QSortFilterProxyModel const*>(model);

            while (currentProxyModel && currentIndex.model() != nullptr) {
                Q_ASSERT(currentProxyModel->sourceModel() != nullptr);
                if (!currentProxyModel->sourceModel()->hasIndex(
                        currentIndex.row(), currentIndex.column())) {
                    break;
                }

                auto mapped = currentProxyModel->mapToSource(currentIndex);
                if (mapped.isValid()) {
                    currentIndex = mapped;
                    add_proxy(currentProxyModel, currentIndex);
                    currentProxyModel = qobject_cast<
                        QSortFilterProxyModel const*>(
                        currentProxyModel->sourceModel());
                } else {
                    break;
                }
            }
        }

        for (int row = 0; row < model->rowCount(index); ++row) {
            out.nested.push_back(std::make_shared<ModelDumpIr::Row>());
            auto& it = out.nested.back();
            for (int col = 0; col < model->columnCount(index); ++col) {
                QModelIndex sub = model->index(row, col, index);
                if (sub.isValid()) {
                    it->columns.push_back(aux(sub));
                } else {
                    it->columns.push_back(std::nullopt);
                }
            }
        }

        return out;
    };

    result.root = aux(parent);

    return result;
}

std::optional<nlohmann::json> QVariantToJson(const QVariant& variant) {
    if (!variant.isValid() || variant.isNull()) {
        return std::nullopt;
    } else if (auto r = qvariant_opt<QRect>(variant)) {
        return json::object({
            {"x", r->x()},
            {"y", r->y()},
            {"width", r->width()},
            {"height", r->height()},
        });
    } else {
        QJsonValue jsonValue = QJsonValue::fromVariant(variant);

        if (jsonValue.isUndefined()) {
            return std::nullopt;
        } else if (jsonValue.isObject()) {
            return nlohmann::json::parse(
                jsonValue.toString().toStdString());
        } else if (jsonValue.isArray()) {
            return json::parse(
                QJsonDocument(jsonValue.toArray()).toJson().toStdString());
        } else if (jsonValue.isBool()) {
            return json(jsonValue.toBool());
        } else if (jsonValue.isDouble()) {
            return json(jsonValue.toDouble());
        } else if (jsonValue.isNull()) {
            return std::nullopt;
        } else if (jsonValue.isString()) {
            return json(jsonValue.toString().toStdString());
        } else {
            QJsonObject obj;
            obj["value"]      = jsonValue;
            QJsonDocument doc = QJsonDocument(obj);
            return nlohmann::json::parse(doc.toJson().toStdString());
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        throw std::invalid_argument(
            "Expected one argument for the driver execution: json object "
            "for driver config");
    }

    auto config = from_json_eval<DriverConfig>(
        json::parse(readFile(argv[1])));

    qInstallMessageHandler(customMessageHandler);
    editorInitMain();

    OrgStore store;
    for (auto const& file : config.input_paths) {
        auto parsed = sem::parseFile(file, sem::OrgParseParameters{});
        store.addRoot(parsed);
    }

    DriverResult result;
    result.action = config.action;

    auto variant_dump_cb = [](QVariant const& val) -> json {
        if (auto conv = QVariantToJson(val)) {
            return conv.value();
        } else if (auto box = qvariant_opt<OrgBoxId>(val)) {
            return to_json_eval(*box);
        } else if (
            auto pair = qvariant_opt<
                Pair<OrgGraph::VDesc, OrgGraph::VDesc>>(val)) {
            return to_json_eval(*pair);
        } else {
            return qdebug_to_str(val);
        }
    };

    switch (config.action.getKind()) {
        case Action::Kind::None: {
            throw std::invalid_argument(
                "No driver action specified: add `action:` field in the "
                "main "
                "JSON.");
        }
        case Action::Kind::DocumentModel: {
            for (auto const& root : store.roots) {
                OrgDocumentModel model{&store, nullptr};
                model.setObjectName("document_model");
                model.root = root.get();
                DriverResult::DocumentDump dump;
                dump.main_document = //
                    dumpModelTree(&model, QModelIndex(), variant_dump_cb);

                OrgSubtreeSearchModel outline{&model, nullptr, &store};
                outline.filter->setObjectName("outline_filter");
                dump.outline_document = dumpModelTree(
                    outline.filter.get(), QModelIndex(), variant_dump_cb);

                result.document_dumps.push_back(dump);
            }
            break;
        }

        case Action::Kind::MindMap: {
            QApplication      app{argc, argv};
            SPtr<QMainWindow> window = std::make_shared<QMainWindow>();
            window->show();
            window->raise();
            window->activateWindow();

            auto graph = std::make_shared<OrgGraph>(&store, nullptr);
            graph->addFullStore();

            OrgGraphView* view;

            SPtr<OrgGraphLayoutProxy>
                proxy = std::make_shared<OrgGraphLayoutProxy>(
                    &store,
                    OrgGraphLayoutProxy::LayoutConfig{
                        .getNodeSize =
                            [&](QModelIndex const& index) {
                                return view->getNodeSize(index);
                            },
                        .getEdgeLabelSize =
                            [&](QModelIndex const& index) {
                                return view->getNodeSize(index);
                            },
                    },
                    nullptr);

            proxy->setSourceModel(graph.get());
            view = new OrgGraphView(proxy.get(), &store, window.get());

            window->setContentsMargins(0, 0, 0, 0);
            window->setCentralWidget(view);
            proxy->updateCurrentLayout();
            view->rebuildScene();

            auto const& map = config.action.getMindMap();
            if (map.screenshotPath) {
                save_screenshot(
                    window.get(),
                    QString::fromStdString(map.screenshotPath.value()),
                    2);
            }
            result.mind_map_dump = DriverResult::MindMapDump{};
            auto& dump           = result.mind_map_dump.value();

            proxy->setObjectName("layout_proxy");
            graph->setObjectName("base_graph");

            dump.graphvizDump = graph->toGraphviz();
            dump.graphModel   = dumpModelTree(
                graph.get(), QModelIndex(), variant_dump_cb);
            dump.layoutDump = dumpModelTree(
                proxy.get(), QModelIndex(), variant_dump_cb);


            break;
        }
    }

    writeFile(
        fs::path{config.output_path.toBase()},
        to_json_eval(result).dump(2));
}
