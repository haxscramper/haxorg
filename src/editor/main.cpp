#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sem/SemBaseApi.hpp>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <absl/log/log.h>
#include <org_qml.hpp>
#include "org_qml_model.hpp"

int main(int argc, char* argv[]) {
    OrgBackend backend;
    backend.document = org::parseString(
        readFile("/home/haxscramper/tmp/doc1.org"));

    QGuiApplication         app(argc, argv);
    QQmlApplicationEngine   engine;
    OrgDocumentModel        model{backend.document};
    OrgDocumentSearchFilter filter{&model};
    OrgSubtreeSearchModel   fuzzySorted{&model};

    filter.acceptNode = [](CR<sem::SemId<sem::Org>> id) -> bool {
        return id->getKind() != OrgSemKind::Newline;
    };

    engine.rootContext()->setContextProperty("documentModel", &filter);
    engine.rootContext()->setContextProperty(
        "sortedSubtree", &fuzzySorted.filter);
    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url(u"qrc:/editor/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
