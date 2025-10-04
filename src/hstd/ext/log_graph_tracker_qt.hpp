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


void hstd::log::log_graph_tracker::notify_signal_emit(
    log_graph_processor::signal_emit_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_signal_emit(info);
    }
}

void hstd::log::log_graph_tracker::notify_slot_trigger(
    const log_graph_processor::slot_trigger_info& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_slot_trigger(info);
    }
}

hstd::finally_std hstd::log::log_graph_tracker::track_slot(
    const log_graph_processor::slot_trigger_info& info) {
    notify_slot_trigger(info);
    return track_function(hstd::log::log_graph_processor::function_info(
        info.name, info.args, info.loc));
}

void hstd::log::log_graph_tracker::notify_qobject(
    const log_graph_processor::qobject_info& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) { processor->track_qobject(info); }
}

void hstd::log::log_graph_tracker::notify_connect(
    const log_graph_processor::connect_info& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) { processor->track_connect(info); }
}

void hstd::log::graphviz_processor::track_signal_emit(
    const signal_emit_info& info) {
    std::string full_name = std::format("{}", info.name);
    if (!call_stack.empty()) { add_edge(call_stack.top(), full_name); }
    nodes.insert_or_assign(
        full_name,
        node_info{
            .name      = full_name,
            .is_signal = true,
        });
}

void hstd::log::graphviz_processor::track_slot_trigger(
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

void hstd::log::logger_processor::track_signal_emit(
    const signal_emit_info& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message(
            "signal emit::{} -> '{}({})'",
            descObjectPtr(info.sender),
            info.name,
            info.args)
        .end();
}

void hstd::log::logger_processor::track_slot_trigger(
    const slot_trigger_info& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message(
            "slot trigger::{} -> '{}'",
            descObjectPtr(info.receiver),
            info.name)
        .end();
}

void hstd::log::logger_processor::track_qobject(
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

void hstd::log::logger_processor::track_connect(const connect_info& info) {
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

#endif
