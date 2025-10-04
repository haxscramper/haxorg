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

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "main"

int main(int argc, char* argv[]) {
    hstd::log::push_sink(
        hstd::log::init_file_sink("/tmp/org_diagram.log"));

    get_tracker()->start_tracing();

    auto conf = hstd::from_json_eval<StartupArgc>(json::parse(argv[1]));
    QFileSystemWatcher watcher;


    qInstallMessageHandler(customMessageHandler);
    QApplication app{argc, argv};
    QLoggingCategory::setFilterRules("qt.qpa.painting.debug=true");

    auto window = std::make_shared<MainWindow>(conf);

    QObject::connect(
        &watcher,
        &QFileSystemWatcher::fileChanged,
        [&](QString const& event) {
            HSLOG_TRACE(
                _cat, hstd::fmt("File changed:{}", event.toStdString()));
            window->loadFile(event);
        });

    watcher.addPath(QString::fromStdString(conf.documentPath));


    window->show();

    int result = app.exec();
    get_tracker()->end_tracing();
    return result;
}

#include "main.moc"
