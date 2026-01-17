#include <org_diagram/src/utils/common.hpp>

#include <org_diagram/src/gui/items/DiaSceneItem.hpp>
#include <org_diagram/src/gui/items/DiaSceneItemVisual.hpp>
#include <org_diagram/src/gui/DiagramView.hpp>
#include <org_diagram/src/gui/DiaSceneItemModel.hpp>
#include <org_diagram/src/gui/DiaScene.hpp>
#include <org_diagram/src/MainWindow.hpp>

#include <QtWidgets>
#include <QApplication>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QFileDialog>
#include <QListWidget>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSplitter>
#include <QAbstractItemModel>
#include <QTreeView>
#include <QLineEdit>
#include <QColorDialog>
#include <QSlider>
#include <QWheelEvent>
#include <hstd/stdlib/Debug.hpp>
#include <org_diagram/src/utils/common.hpp>
#include <org_diagram/src/utils/file_watcher.hpp>
#include <QFileSystemWatcher>
#include <org_diagram/src/model/graph/IOrgGraph.hpp>
#include <org_diagram/src/model/graph/DiaGraph.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

class CliApplication : public QCoreApplication {
    Q_OBJECT
  public:
    StartupArgc conf;

    org::imm::ImmAstContext::Ptr imm_context;
    DiaContext::Ptr              dia_context;
    DiaVersionStore::Ptr         version_store;
    hstd::SPtr<DiaGraph>         dia_graph;

    hstd::SPtr<DiaHierarchyEdgeCollection> hierarchy_collection;
    hstd::SPtr<DiaSubtreeIdTracker>        subtree_id_tracker;
    hstd::SPtr<DiaDescriptionListEdgeCollection>
        description_list_collection;

    CliApplication(int argc, char* argv[], StartupArgc const& conf)
        : QCoreApplication{argc, argv}
        , conf{conf}
        , imm_context{org::imm::ImmAstContext::init_start_context()}
        , dia_context{DiaContext::shared()}
        , version_store{DiaVersionStore::shared(imm_context, dia_context)}
        , dia_graph{std::make_shared<DiaGraph>(dia_context)}
        , hierarchy_collection{std::make_shared<
              DiaHierarchyEdgeCollection>(dia_context, dia_graph)}
        , subtree_id_tracker(
              std::make_shared<DiaSubtreeIdTracker>(dia_graph))
        , description_list_collection(
              std::make_shared<DiaDescriptionListEdgeCollection>(
                  dia_graph,
                  subtree_id_tracker)) {

        // dia_graph->addCollection(hierarchy_collection);
        dia_graph->addTracker(subtree_id_tracker);
        dia_graph->addCollection(description_list_collection);
        dia_context->use_padding     = conf.use_padding;
        dia_context->use_nested_todo = conf.use_nested_todo;

        connect(
            version_store.get(),
            &DiaVersionStore::diaRootChanged,
            this,
            &CliApplication::diaRootChanged);
    }

    void loadFile(std::string const& path) {
        version_store->addDocument(hstd::readFile(path));

        HSLOG_DEBUG(
            "Constructed tree:\n{}",
            version_store->getActiveDiaRoot().format().toString(false));
    }

  public slots:
    void diaRootChanged(DiaVersionStore::DiaRootChange const& change) {
        TRACKED_SLOT("diaRootChanged", change);
        hstd::Vec<org::graph::VertexID> added;
        hstd::Vec<org::graph::VertexID> removed;
        for (auto const& edit : change.edits) {
            switch (edit.getKind()) {
                case DiaEdit::Kind::Delete: {
                    auto aux = [&](DiaAdapter const& a,
                                   auto&&            self) -> void {
                        removed.push_back(dia_graph->delVertex(a.uniq()));
                        for (auto const& sub : a.sub(true)) {
                            self(sub, self);
                        }
                    };
                    aux(edit.getSrc(), aux);
                    break;
                }

                case DiaEdit::Kind::Insert: {
                    auto aux = [&](DiaAdapter const& a,
                                   auto&& self) -> org::graph::VertexID {
                        auto added_vertex = dia_graph->addVertex(a.uniq());
                        added.push_back(added_vertex);
                        for (auto const& sub : a.sub(true)) {
                            auto sub_vertex = self(sub, self);
                            dia_graph->trackSubVertexRelation(
                                added_vertex, sub_vertex);
                        }

                        return added_vertex;
                    };
                    // Discarding root vertices in the graph as there are
                    // no super-vertices to attach them to.
                    std::ignore = aux(edit.getDst(), aux);
                    break;
                }

                case DiaEdit::Kind::Update:
                case DiaEdit::Kind::Move: {
                    // discard operations
                }
            }
        }

        dia_graph->untrackVertexList(removed);
        dia_graph->trackVertexList(added);
    }
};

int main(int argc, char* argv[]) {
    hstd::log::push_sink(
        hstd::log::init_file_sink("/tmp/org_diagram.log"));

    get_tracker()->start_tracing();

    auto conf = hstd::from_json_eval<StartupArgc>(json::parse(argv[1]));

    if (conf.mode == StartupArgc::Mode::Gui) {
        QApplication       app{argc, argv};
        QFileSystemWatcher watcher;


        qInstallMessageHandler(customMessageHandler);
        QLoggingCategory::setFilterRules("qt.qpa.painting.debug=true");

        auto window = std::make_shared<MainWindow>(conf);

        QObject::connect(
            &watcher,
            &QFileSystemWatcher::fileChanged,
            [&](QString const& event) {
                HSLOG_TRACE("File changed:{}", event.toStdString());
                window->loadFile(event);
            });

        watcher.addPath(QString::fromStdString(conf.documentPath));


        window->show();

        int result = app.exec();
        get_tracker()->end_tracing();
        return result;
    } else if (conf.mode == StartupArgc::Mode::MindMapDump) {
        CliApplication app{argc, argv, conf};
        app.loadFile(conf.documentPath);
        auto serial = app.dia_graph->getGraphSerial();
        hstd::writeFile(conf.outputPath, serial.dump(2));
    }
}

#include "main.moc"
