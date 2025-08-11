#include "log_graph_tracker.hpp"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <hstd/system/Formatter.hpp>


using namespace hstd::log;

void log_graph_tracker::add_processor(
    std::shared_ptr<log_graph_processor> processor,
    int                                  line,
    const char*                          function,
    const char*                          file) {
    std::lock_guard<std::mutex> lock{mutex};
    processors.push_back(processor);
}

void log_graph_tracker::start_tracing(
    int         line,
    const char* function,
    const char* file) {
    std::lock_guard<std::mutex> lock{mutex};
    if (tracing.exchange(true)) {
        throw std::runtime_error("Tracing already started");
    }
    for (auto& processor : processors) { processor->track_started(); }
}

void log_graph_tracker::end_tracing(
    int         line,
    const char* function,
    const char* file) {
    std::lock_guard<std::mutex> lock{mutex};
    if (!tracing.exchange(false)) {
        throw std::runtime_error("Tracing not started");
    }
    for (auto& processor : processors) { processor->track_ended(); }
    processors.clear();
}

void log_graph_tracker::notify_function_start(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_function_start(function_name);
    }
}

void log_graph_tracker::notify_function_end(
    const std::string& function_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_function_end(function_name);
    }
}

void log_graph_tracker::notify_signal_emit(
    const std::string&              signal_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_signal_emit(signal_name, args);
    }
}

void log_graph_tracker::notify_slot_trigger(
    const std::string&              slot_name,
    const std::vector<std::string>& args,
    int                             line,
    const char*                     function,
    const char*                     file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_slot_trigger(slot_name, args);
    }
}

void log_graph_tracker::notify_scope_enter(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_scope_enter(scope_name);
    }
}

void log_graph_tracker::notify_scope_exit(
    const std::string& scope_name,
    int                line,
    const char*        function,
    const char*        file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_scope_exit(scope_name);
    }
}

void log_graph_tracker::notify_named_text(
    const std::string& key,
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_named_text(key, value);
    }
}

void log_graph_tracker::notify_named_jump(
    const std::string& description,
    int                line,
    const char*        function,
    const char*        file) {
    if (!tracing.load()) { return; }
    std::lock_guard<std::mutex> lock{mutex};
    for (auto& processor : processors) {
        processor->track_named_jump(description);
    }
}

void graphviz_processor::track_function_start(
    const std::string& function_name) {
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
    const std::string& function_name) {
    if (!call_stack.empty()) { call_stack.pop(); }
}

void graphviz_processor::track_signal_emit(
    const std::string&              signal_name,
    const std::vector<std::string>& args) {
    std::string full_name = std::format("signal_{}", signal_name);
    if (!call_stack.empty()) { add_edge(call_stack.top(), full_name); }
    nodes.insert_or_assign(full_name, node_info{full_name, false, {}});
}

void graphviz_processor::track_slot_trigger(
    const std::string&              slot_name,
    const std::vector<std::string>& args) {
    std::string full_name = std::format("slot_{}", slot_name);
    call_stack.push(full_name);
    nodes.insert_or_assign(full_name, node_info{full_name, false, {}});
}

void graphviz_processor::track_scope_enter(const std::string& scope_name) {
    call_stack.push(scope_name);
    if (call_stack.size() >= 2) {
        std::string parent = get_parent();
        add_edge(parent, scope_name);
    }
    nodes.insert_or_assign(scope_name, node_info{scope_name, false, {}});
}

void graphviz_processor::track_scope_exit(const std::string& scope_name) {
    if (!call_stack.empty()) { call_stack.pop(); }
}

void graphviz_processor::track_started() {
    nodes.clear();
    edges.clear();
    while (!call_stack.empty()) { call_stack.pop(); }
    pending_jump.clear();
}

void graphviz_processor::track_named_jump(const std::string& description) {
    pending_jump = description;
}

void graphviz_processor::write_graphviz(const std::string& filename) {
    Agraph_t* graph = agopen(
        const_cast<char*>("callgraph"), Agdirected, nullptr);

    std::unordered_map<std::string, Agnode_t*> graph_nodes{};
    std::unordered_map<std::string, Agraph_t*> clusters{};

    for (auto const& [name, info] : nodes) {
        if (info.is_cluster) {
            std::string cluster_name = std::format("cluster_{}", name);
            Agraph_t*   cluster      = agsubg(
                graph, const_cast<char*>(cluster_name.c_str()), 1);
            agsafeset(
                cluster,
                const_cast<char*>("label"),
                const_cast<char*>(name.c_str()),
                const_cast<char*>(""));
            clusters.insert_or_assign(name, cluster);

            Agnode_t* node = agnode(
                cluster, const_cast<char*>(name.c_str()), 1);
            graph_nodes.insert_or_assign(name, node);

            for (auto const& child : info.children) {
                Agnode_t* child_node = agnode(
                    cluster, const_cast<char*>(child.c_str()), 1);
                graph_nodes.insert_or_assign(child, child_node);
            }
        } else if (graph_nodes.find(name) == graph_nodes.end()) {
            Agnode_t* node = agnode(
                graph, const_cast<char*>(name.c_str()), 1);
            graph_nodes.insert_or_assign(name, node);
        }
    }

    for (auto const& [edge_key, call] : edges) {
        int         pos  = edge_key.find(" -> ");
        std::string from = edge_key.substr(0, pos);
        std::string to   = edge_key.substr(pos + 4);

        Agnode_t* from_node = graph_nodes.at(from);
        Agnode_t* to_node   = graph_nodes.at(to);

        Agedge_t* edge = agedge(graph, from_node, to_node, nullptr, 1);

        std::string label{};
        if (!call.jump_description.empty() && call.count > 1) {
            label = std::format(
                "{} ({})", call.jump_description, call.count);
        } else if (!call.jump_description.empty()) {
            label = call.jump_description;
        } else if (call.count > 1) {
            label = std::format("({})", call.count);
        }

        if (!label.empty()) {
            agsafeset(
                edge,
                const_cast<char*>("label"),
                const_cast<char*>(label.c_str()),
                const_cast<char*>(""));
        }
    }

    FILE* file = fopen(filename.c_str(), "w");
    agwrite(graph, file);
    fclose(file);
    agclose(graph);
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
