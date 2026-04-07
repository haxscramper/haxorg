#include "log_graph_tracker.hpp"

#if !ORG_BUILD_EMCC

#    if ORG_BUILD_WITH_CGRAPH
#        include <graphviz/gvc.h>
#        include <graphviz/cgraph.h>
#    endif

#    include <hstd/ext/logger.hpp>
#    include <hstd/stdlib/Formatter.hpp>
#    include <hstd/ext/graphviz.hpp>

#    if ORG_BUILD_WITH_QT
#        include <QMetaObject>
#        include <QMetaMethod>
#    endif

using namespace hstd::log;


void log_graph_tracker::add_processor(
    std::shared_ptr<log_graph_processor> processor,
    int                                  line,
    char const*                          function,
    char const*                          file) {
    processors.push_back(processor);
}

void log_graph_tracker::start_tracing(
    log_graph_processor::tracked_info const& info) {
    if (TraceState) {
        throw std::runtime_error("Tracing already started");
    }
    TraceState = true;
    for (auto& processor : processors) { processor->track_started(info); }
}

void log_graph_tracker::end_tracing(
    log_graph_processor::tracked_info const& info) {
    if (!TraceState) { throw std::runtime_error("Tracing not started"); }
    TraceState = false;
    for (auto& processor : processors) { processor->track_ended(info); }
}

void log_graph_tracker::notify_function_start(
    log_graph_processor::function_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_function_start(info);
    }
}

void log_graph_tracker::notify_function_end(
    log_graph_processor::function_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_function_end(info);
    }
}


void log_graph_tracker::notify_scope_enter(
    log_graph_processor::scope_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_scope_enter(info);
    }
}

void log_graph_tracker::notify_scope_exit(
    log_graph_processor::scope_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_scope_exit(info);
    }
}

void log_graph_tracker::notify_named_text(
    log_graph_processor::named_text_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_named_text(info);
    }
}

void log_graph_tracker::notify_named_jump(
    log_graph_processor::named_jump_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_named_jump(info);
    }
}


hstd::finally_std log_graph_tracker::track_scope(
    log_graph_processor::scope_info const& info) {
    notify_scope_enter(info);
    return hstd::finally_std{
        [this, info]() { this->notify_scope_exit(info); }};
}

hstd::finally_std log_graph_tracker::track_function(
    log_graph_processor::function_info const& info) {
    notify_function_start(info);
    return hstd::finally_std{
        [this, info]() { this->notify_function_end(info); }};
}

#    if ORG_BUILD_WITH_CGRAPH
void graphviz_processor::track_function_start(function_info const& info) {
    call_stack.push(info.name);
    if (2 <= call_stack.size()) {
        std::string parent = get_parent();
        if (parent != info.name) {
            add_edge(parent, info.name);
            nodes.at(parent).children.push_back(info.name);
            nodes.at(parent).is_cluster = true;
        }
    }
    nodes.insert_or_assign(info.name, node_info{.name = info.name});
}

void graphviz_processor::track_function_end(
    log_graph_processor::function_info const& info) {
    if (!call_stack.empty()) { call_stack.pop(); }
}


void graphviz_processor::track_scope_enter(scope_info const& info) {
    call_stack.push(info.name);
    if (2 <= call_stack.size()) {
        std::string parent = get_parent();
        add_edge(parent, info.name);
    }
    nodes.insert_or_assign(
        info.name,
        node_info{
            .name     = info.name,
            .is_scope = true,
        });
}

void graphviz_processor::track_scope_exit(
    log_graph_processor::scope_info const& info) {
    if (!call_stack.empty()) { call_stack.pop(); }
}

void graphviz_processor::track_started(tracked_info const& info) {
    nodes.clear();
    edges.clear();
    while (!call_stack.empty()) { call_stack.pop(); }
    pending_jump.clear();
}

void graphviz_processor::track_named_jump(named_jump_info const& info) {
    pending_jump = info.description;
}

hstd::ext::Graphviz::Graph graphviz_processor::get_graphviz() {
    using namespace hstd::ext;
    Graphviz::Graph                                  graph{"g"_ss};
    std::unordered_map<std::string, Graphviz::Node>  graph_nodes{};
    std::unordered_map<std::string, Graphviz::Graph> clusters{};

    graph.defaultNode.setShape(Graphviz::Node::Shape::rect);

    for (auto const& [name, info] : nodes) {
        if (info.is_cluster) {
            std::string     cluster_name = std::format("cluster_{}", name);
            Graphviz::Graph cluster      = graph.newSubgraph(cluster_name);
            cluster.setLabel(name);
            clusters.insert_or_assign(name, cluster);

            Graphviz::Node node = cluster.node(name);
            graph_nodes.insert_or_assign(name, node);

            for (auto const& child : info.children) {
                Graphviz::Node child_node = cluster.node(child);
                graph_nodes.insert_or_assign(child, child_node);
            }
        } else if (graph_nodes.find(name) == graph_nodes.end()) {
            Graphviz::Node node = graph.node(name);
            graph_nodes.insert_or_assign(name, node);
        }
    }

    for (auto const& [edge_key, call] : edges) {
        int         pos  = edge_key.find(" -> ");
        std::string from = edge_key.substr(0, pos);
        std::string to   = edge_key.substr(pos + 4);

        Graphviz::Node from_node = graph_nodes.at(from);
        Graphviz::Node to_node   = graph_nodes.at(to);

        Graphviz::Edge edge = graph.edge(from_node, to_node);

        std::string label{};
        if (!call.jump_description.empty() && call.count > 1) {
            label = std::format(
                "{} ({})", call.jump_description, call.count);
        } else if (!call.jump_description.empty()) {
            label = call.jump_description;
        } else if (call.count > 1) {
            label = std::format("({})", call.count);
        }

        if (!label.empty()) { edge.setLabel(label); }
    }

    return graph;
}

std::string graphviz_processor::get_parent() {
    if (call_stack.size() < 2) { return {}; }
    std::string top = call_stack.top();
    call_stack.pop();
    std::string parent = call_stack.top();
    call_stack.push(top);
    return parent;
}

void graphviz_processor::add_edge(
    std::string const& from,
    std::string const& to) {
    std::string edge_key = std::format("{} -> {}", from, to);
    auto        it       = edges.find(edge_key);
    if (it != edges.end()) {
        if (it->second.jump_description == pending_jump) {
            it->second.count++;
        } else {
            it->second.jump_description = pending_jump;
            it->second.count            = 1;
        }
    } else {
        edges.insert_or_assign(edge_key, call_info{pending_jump, 1});
    }
    pending_jump.clear();
}

void hstd::log::graphviz_processor::track_signal_emit(
    signal_emit_info const& info) {
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
    slot_trigger_info const& info) {
    std::string full_name = std::format("{}", info.name);
    call_stack.push(full_name);
    nodes.insert_or_assign(
        full_name,
        node_info{
            .name    = full_name,
            .is_slot = true,
        });
}


#    endif

void logger_processor::track_function_start(function_info const& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message("function enter::'{}'", info.name)
        .end();
    ++log_scoped_depth_attr::instance().depth;
}

void logger_processor::track_function_end(function_info const& info) {
    --log_scoped_depth_attr::instance().depth;
    // log_record{}
    //     .set_callsite(info.loc.line, info.loc.function, info.loc.file)
    //     .fmt_message("function end::'{}'", info.name)
    //     .end();
}


void logger_processor::track_scope_enter(scope_info const& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message("scope enter::'{}'", info.name)
        .end();
    ++log_scoped_depth_attr::instance().depth;
}

void logger_processor::track_scope_exit(scope_info const& info) {
    --log_scoped_depth_attr::instance().depth;
    // log_record{}
    //     .set_callsite(info.loc.line, info.loc.function, info.loc.file)
    //     .fmt_message("scope exit::'{}'", info.name)
    //     .end();
}

void logger_processor::track_started(tracked_info const& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message("track started")
        .end();
    ++log_scoped_depth_attr::instance().depth;
}

void logger_processor::track_ended(tracked_info const& info) {
    --log_scoped_depth_attr::instance().depth;
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message("track ended")
        .end();
}

void logger_processor::track_named_text(named_text_info const& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message("track named text::'{}' = '{}'", info.key, info.value)
        .end();
}

void logger_processor::track_named_jump(named_jump_info const& info) {
    log_record{}
        .set_callsite(info.loc.line, info.loc.function, info.loc.file)
        .fmt_message("named jump::'{}'", info.description)
        .end();
}


#    if ORG_BUILD_WITH_QT
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
    log_graph_processor::slot_trigger_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_slot_trigger(info);
    }
}

hstd::finally_std hstd::log::log_graph_tracker::track_slot(
    log_graph_processor::slot_trigger_info const& info) {
    notify_slot_trigger(info);
    return track_function(
        hstd::log::log_graph_processor::function_info(
            info.name, info.args, info.loc));
}

void hstd::log::log_graph_tracker::notify_qobject(
    log_graph_processor::qobject_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) { processor->track_qobject(info); }
}

void hstd::log::log_graph_tracker::notify_connect(
    log_graph_processor::connect_info const& info) {
    if (!TraceState) { return; }
    for (auto& processor : processors) { processor->track_connect(info); }
}


void hstd::log::logger_processor::track_signal_emit(
    signal_emit_info const& info) {
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
    slot_trigger_info const& info) {
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

void hstd::log::logger_processor::track_connect(connect_info const& info) {
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

    QMetaObject const* metaObject = targetObject->metaObject();

    for (int i = 0; i < metaObject->methodCount(); ++i) {
        QMetaMethod method = metaObject->method(i);
        if (method.methodType() == QMetaMethod::Signal) {
            connectToSignal(method);
        }
    }
}

void SignalDebugger::connectToSignal(QMetaMethod const& signal) {
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

    QMetaObject const* senderMeta  = senderObj->metaObject();
    int                signalIndex = senderSignalIndex();

    if (0 <= signalIndex) {
        QMetaMethod signal = senderMeta->method(signalIndex);

        tracker->notify_signal_emit(
            hstd::log::log_graph_processor::signal_emit_info(
                senderObj,
                hstd::log::log_graph_processor::function_info(
                    signal.name().toStdString(),
                    formatParameterInfo(signal),
                    hstd::log::log_graph_processor::callsite::
                        this_callsite())));
    }
}

hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> SignalDebugger::
    formatParameterInfo(QMetaMethod const& method) {
    QList<QByteArray> paramNames = method.parameterNames();
    QList<QByteArray> paramTypes = method.parameterTypes();

    if (paramNames.size() != paramTypes.size()) { return {}; }
    hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> debug{};
    for (int i = 0; i < paramNames.size(); ++i) {
        debug.push_back(
            {paramTypes.at(i).toStdString(),
             paramNames.at(i).toStdString()});
    }

    return debug;
}


#        include "log_graph_tracker.moc"

#    endif
#endif
