#include <src/common.hpp>

#include <src/DiagramNode.hpp>
#include <src/DiagramNodeVisual.hpp>
#include <src/DiagramView.hpp>
#include <src/DiagramTreeModel.hpp>
#include <src/DiagramScene.hpp>
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



#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "main"


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

int main(int argc, char* argv[]) {
    hstd::log::push_sink(
        hstd::log::init_file_sink("/tmp/org_diagram.log"));

    get_tracker()->start_tracing();


    qInstallMessageHandler(customMessageHandler);
    QApplication app{argc, argv};
    QLoggingCategory::setFilterRules("qt.qpa.painting.debug=true");

    MainWindow window{};
    window.show();

    int result = app.exec();
    get_tracker()->end_tracing();
    return result;
}

#include "main.moc"
