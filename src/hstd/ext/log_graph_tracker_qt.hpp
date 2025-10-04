#include "log_graph_tracker.hpp"

#if ORG_USE_QT
#    include <QMetaObject>
#    include <QMetaMethod>

std::string hstd::descObjectPtr(QObject* obj) {
    return hstd::fmt(
        "'{}' at 0x{:X}",
        obj ? (obj->objectName().isEmpty()
                   ? obj->metaObject()->className()
                   : obj->objectName().toStdString())
            : "<nullptr>",
        reinterpret_cast<std::ptrdiff_t>(obj));
}


void log_graph_tracker::notify_signal_emit(
    log_graph_processor::signal_emit_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_signal_emit(info);
    }
}

void log_graph_tracker::notify_slot_trigger(
    const log_graph_processor::slot_trigger_info& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_slot_trigger(info);
    }
}

hstd::finally_std log_graph_tracker::track_slot(
    const log_graph_processor::slot_trigger_info& info) {
    notify_slot_trigger(info);
    return track_function(
        log_graph_processor::function_info(info.name, info.loc));
}

void log_graph_tracker::notify_qobject(
    const log_graph_processor::qobject_info& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) { processor->track_qobject(info); }
}

void log_graph_tracker::notify_connect(
    const log_graph_processor::connect_info& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) { processor->track_connect(info); }
}

void graphviz_processor::track_signal_emit(const signal_emit_info& info) {
    std::string full_name = std::format("{}", info.name);
    if (!call_stack.empty()) { add_edge(call_stack.top(), full_name); }
    nodes.insert_or_assign(
        full_name,
        node_info{
            .name      = full_name,
            .is_signal = true,
        });
}

void graphviz_processor::track_slot_trigger(
    const slot_trigger_info& info) {
    std::string full_name = std::format("{}", info.name);
    call_stack.push(full_name);
    nodes.insert_or_assign(
        full_name,
        node_info{
            .name    = full_name,
            .is_slot = true,
        });
}

void logger_processor::track_signal_emit(const signal_emit_info& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message(
            "signal emit::{} -> '{}({})'",
            descObjectPtr(info.sender),
            info.name,
            info.args)
        .end();
}

void logger_processor::track_slot_trigger(const slot_trigger_info& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message(
            "slot trigger::{} -> '{}'",
            descObjectPtr(info.receiver),
            info.name)
        .end();
}

void logger_processor::track_qobject(
    log_graph_processor::qobject_info const& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message("created {}", descObjectPtr(info.object))
        .end();

    QObject::connect(
        info.object, &QObject::destroyed, info.object, [info]() {
            log_record{}
                .set_callsite(
                    info.loc.line, info.loc.function, info.loc.file)
                .fmt_message("destroyed {}", descObjectPtr(info.object))
                .end();
        });
}

void logger_processor::track_connect(const connect_info& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message(
            "connect 0x{:X}::{} -> 0x{:X}::{}",
            reinterpret_cast<std::ptrdiff_t>(info.sender),
            info.signal,
            reinterpret_cast<std::ptrdiff_t>(info.receiver),
            info.slot)
        .end();
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

        tracker->notify_signal_emit(log_graph_processor::signal_emit_info(
            senderObj,
            signal.name().toStdString(),
            formatParameterInfo(signal),
            log_graph_processor::callsite::this_callsite()));
    }
}

std::vector<std::string> SignalDebugger::formatParameterInfo(
    const QMetaMethod& method) {
    QList<QByteArray> paramNames = method.parameterNames();
    QList<QByteArray> paramTypes = method.parameterTypes();

    if (paramNames.size() != paramTypes.size()) { return {}; }
    std::vector<std::string> debug{};
    for (int i = 0; i < paramNames.size(); ++i) {
        debug.push_back(hstd::fmt(
            "{}={}",
            paramTypes.at(i).toStdString(),
            paramNames.at(i).toStdString()));
    }

    return debug;
}

#endif
