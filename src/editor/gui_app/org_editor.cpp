#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sem/SemBaseApi.hpp>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <absl/log/log.h>
#include <gui_lib/org_qml.hpp>
#include <gui_lib/org_qml_backend.hpp>
#include <sem/perfetto_org.hpp>
#include <hstd/wrappers/perfetto_aux_impl_template.hpp>

int main(int argc, char* argv[]) {
    QGuiApplication       app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<OrgBackend>("OrgQml", 1, 0, "OrgBackend");
    const QUrl url(u"qrc:/org_editor_app/gui_app/OrgTreeTable.qml"_qs);
    // const QUrl url(u"qrc:/org_editor_app/gui_app/OrgEditor.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
