#include "log_graph_tracker.hpp"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <hstd/ext/logger.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/ext/graphviz.hpp>

#if HAXORG_LOGGER_SUPPORT_QT
#    include <QMetaObject>
#    include <QMetaMethod>
#endif


using namespace hstd::log;


std::string descObject(const QObject* obj) {
    return hstd::fmt(
        "'{}' at 0x{:X}",
        obj->objectName().isEmpty() ? obj->metaObject()->className()
                                    : obj->objectName().toStdString(),
        reinterpret_cast<std::ptrdiff_t>(obj));
}

void log_graph_tracker::add_processor(
    std::shared_ptr<log_graph_processor> processor,
    int                                  line,
    const char*                          function,
    const char*                          file) {
    processors.push_back(processor);
}

void log_graph_tracker::start_tracing(
    int         line,
    const char* function,
    const char* file) {
    if (TraceState) {
        throw std::runtime_error("Tracing already started");
    }
    TraceState = true;
    for (auto& processor : processors) {
        processor->track_started(line, function, file);
    }
}

void log_graph_tracker::end_tracing(
    int         line,
    const char* function,
    const char* file) {
    if (!TraceState) { throw std::runtime_error("Tracing not started"); }
    TraceState = false;
    for (auto& processor : processors) {
        processor->track_ended(line, function, file);
    }
}

void log_graph_tracker::notify_function_start(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_function_start(
            function_name, line, function, file);
    }
}

void log_graph_tracker::notify_function_end(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_function_end(function_name, line, function, file);
    }
}

void log_graph_tracker::notify_signal_emit(
    const QObject*                  _this,
    const std::string&              signal_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_signal_emit(
            _this, signal_name, args, line, function, file);
    }
}

void log_graph_tracker::notify_slot_trigger(
    const QObject*                  _this,
    const std::string&              slot_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_slot_trigger(
            _this, slot_name, args, line, function, file);
    }
}

void log_graph_tracker::notify_scope_enter(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_scope_enter(scope_name, line, function, file);
    }
}

void log_graph_tracker::notify_scope_exit(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_scope_exit(scope_name, line, function, file);
    }
}

void log_graph_tracker::notify_named_text(
    const std::string& key,
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_named_text(key, value, line, function, file);
    }
}

void log_graph_tracker::notify_named_jump(
    const std::string& description,
    int                line,
    const char*        function,
    const char*        file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_named_jump(description, line, function, file);
    }
}

hstd::finally_std log_graph_tracker::track_slot(
    QObject const*                  _this,
    const std::string&              description,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    notify_slot_trigger(_this, description, args, line, function, file);
    return track_function(description, line, function, file);
}

void log_graph_tracker::notify_qobject(
    const QObject* _this,
    int            line,
    const char*    function,
    const char*    file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_qobject(_this, line, function, file);
    }
}

void log_graph_tracker::notify_connect(
    const QObject*     emitter,
    const std::string& signal,
    const QObject*     receiver,
    const std::string& slot,
    int                line,
    const char*        function,
    const char*        file) {
    if (!TraceState) { return; }
    for (auto& processor : processors) {
        processor->track_connect(
            emitter, signal, receiver, slot, line, function, file);
    }
}

hstd::finally_std log_graph_tracker::track_scope(
    const std::string& description,
    int                line,
    const char*        function,
    const char*        file) {
    notify_scope_enter(description, line, function, file);
    return hstd::finally_std{[this, description, line, function, file]() {
        this->notify_scope_exit(description, line, function, file);
    }};
}

hstd::finally_std log_graph_tracker::track_function(
    const std::string& description,
    int                line,
    const char*        function,
    const char*        file) {
    notify_function_start(description, line, function, file);
    return hstd::finally_std{[this, description, line, function, file]() {
        this->notify_function_end(description, line, function, file);
    }};
}

void graphviz_processor::track_function_start(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    call_stack.push(function_name);
    if (call_stack.size() >= 2) {
        std::string parent = get_parent();
        if (parent != function_name) {
            add_edge(parent, function_name);
            nodes.at(parent).children.push_back(function_name);
            nodes.at(parent).is_cluster = true;
        }
    }
    nodes.insert_or_assign(
        function_name, node_info{function_name, false, {}});
}

void graphviz_processor::track_function_end(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!call_stack.empty()) { call_stack.pop(); }
}

void graphviz_processor::track_signal_emit(
    QObject const*                  _this,
    const std::string&              signal_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    std::string full_name = std::format("{}", signal_name);
    if (!call_stack.empty()) { add_edge(call_stack.top(), full_name); }
    nodes.insert_or_assign(
        full_name,
        node_info{
            .name      = full_name,
            .is_signal = true,
        });
}

void graphviz_processor::track_slot_trigger(
    QObject const*                  _this,
    const std::string&              slot_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    std::string full_name = std::format("{}", slot_name);
    call_stack.push(full_name);
    nodes.insert_or_assign(
        full_name,
        node_info{
            .name    = full_name,
            .is_slot = true,
        });
}

void graphviz_processor::track_scope_enter(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    call_stack.push(scope_name);
    if (call_stack.size() >= 2) {
        std::string parent = get_parent();
        add_edge(parent, scope_name);
    }
    nodes.insert_or_assign(
        scope_name,
        node_info{
            .name     = scope_name,
            .is_scope = true,
        });
}

void graphviz_processor::track_scope_exit(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!call_stack.empty()) { call_stack.pop(); }
}

void graphviz_processor::track_started(
    int         line,
    const char* function,
    const char* file) {
    nodes.clear();
    edges.clear();
    while (!call_stack.empty()) { call_stack.pop(); }
    pending_jump.clear();
}

void graphviz_processor::track_named_jump(
    const std::string& description,
    int                line,
    const char*        function,
    const char*        file) {
    pending_jump = description;
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
    const std::string& from,
    const std::string& to) {
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

void logger_processor::track_function_start(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("function enter::'{}'", function_name)
        .end();
    ++log_scoped_depth_attr::instance().depth;
}

void logger_processor::track_function_end(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    --log_scoped_depth_attr::instance().depth;
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("function end::'{}'", function_name)
        .end();
}

void logger_processor::track_signal_emit(
    const QObject*                  _this,
    const std::string&              signal_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message(
            "signal emit::{} -> '{}({})'",
            descObject(_this),
            signal_name,
            args)
        .end();
}

void logger_processor::track_slot_trigger(
    const QObject*                  _this,
    const std::string&              slot_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message(
            "slot trigger::{} -> '{}'", descObject(_this), slot_name)
        .end();
}

void logger_processor::track_qobject(
    const QObject* _this,
    int            line,
    const char*    function,
    const char*    file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("created {}", descObject(_this))
        .end();

    QObject::connect(
        _this,
        &QObject::destroyed,
        _this,
        [_this, line, function, file]() {
            log_record{}
                .set_callsite(line, function, file)
                .fmt_message("destroyed {}", descObject(_this))
                .end();
        });
}

void logger_processor::track_connect(
    const QObject*     emitter,
    const std::string& signal,
    const QObject*     receiver,
    const std::string& slot,
    int                line,
    const char*        function,
    const char*        file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message(
            "connect 0x{:X}::{} -> 0x{:X}::{}",
            reinterpret_cast<std::ptrdiff_t>(emitter),
            signal,
            reinterpret_cast<std::ptrdiff_t>(receiver),
            slot)
        .end();
}

void logger_processor::track_scope_enter(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("scope enter::'{}'", scope_name)
        .end();
    ++log_scoped_depth_attr::instance().depth;
}

void logger_processor::track_scope_exit(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    --log_scoped_depth_attr::instance().depth;
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("scope exit::'{}'", scope_name)
        .end();
}

void logger_processor::track_started(
    int         line,
    const char* function,
    const char* file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("track started")
        .end();
    ++log_scoped_depth_attr::instance().depth;
}

void logger_processor::track_ended(
    int         line,
    const char* function,
    const char* file) {
    --log_scoped_depth_attr::instance().depth;
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("track ended")
        .end();
}

void logger_processor::track_named_text(
    const std::string& key,
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("track named text::'{}' = '{}'", key, value)
        .end();
}

void logger_processor::track_named_jump(
    const std::string& description,
    int                line,
    const char*        function,
    const char*        file) {
    log_record{}
        .set_callsite(line, function, file)
        .fmt_message("named jump::'{}'", description)
        .end();
}

#if HAXORG_LOGGER_SUPPORT_QT


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

        tracker->notify_signal_emit(
            senderObj,
            signal.name().toStdString(),
            formatParameterInfo(signal));
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
