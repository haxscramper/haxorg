#include <src/utils/common.hpp>

#include <src/gui/items/DiaSceneItem.hpp>
#include <src/gui/items/DiaSceneItemVisual.hpp>
#include <src/gui/DiagramView.hpp>
#include <src/gui/DiaSceneItemModel.hpp>
#include <src/gui/DiaScene.hpp>
#include <src/MainWindow.hpp>

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
#include <src/utils/common.hpp>
#include <src/utils/file_watcher.hpp>
#include <QFileSystemWatcher>

int main(int argc, char* argv[]) {
    hstd::log::push_sink(
        hstd::log::init_file_sink("/tmp/org_diagram.log"));

    get_tracker()->start_tracing();

    auto conf = hstd::from_json_eval<StartupArgc>(json::parse(argv[1]));

    QApplication app{argc, argv};
    if (conf.mode == StartupArgc::Mode::Gui) {
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
        auto imm_context = org::imm::ImmAstContext::init_start_context();
        auto dia_context = DiaContext::shared();
        DiaVersionStore::Ptr version_store = DiaVersionStore::shared(
            imm_context, dia_context);

        version_store->addDocument(hstd::readFile(conf.documentPath));

        auto adapter = FromDocument(
            dia_context, version_store->getActiveImmRoot());
    }
}

#include "main.moc"
