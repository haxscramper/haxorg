#include <editor/editor_lib/common/app_init.hpp>
#include <editor/editor_lib/document/org_document_model.hpp>
#include <editor/editor_lib/mind_map/org_graph_model.hpp>
#include <iostream>

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

    std::string loc = fmt(
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

void editorInitMain() {
    qRegisterMetaType<OrgBoxId>("OrgBoxId");
    qRegisterMetaType<org::mind_map::GraphLayoutProxy::Subgraph>(
        "OrgGraphLayoutProxySubgraph");

    QByteArray envVar = qgetenv("QT_LOGGING_RULES");
    if (!envVar.isEmpty()) {
        QLoggingCategory::setFilterRules(QString::fromLocal8Bit(envVar));
    }
}
