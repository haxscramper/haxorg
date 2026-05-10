#include "graph_elk.hpp"

#include <unordered_set>
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/JsonSerde.hpp>


using namespace hstd;
using namespace hstd::ext;
using namespace hstd::ext::graph;

void elk::validate(elk::Graph const& graph) {
    std::unordered_set<hstd::Str> node_ids;
    std::unordered_set<hstd::Str> port_ids;
    std::unordered_set<hstd::Str> edge_ids;

    std::function<void(Node const&)> collect_node_ids =
        [&](Node const& node) {
            if (node.id.empty()) {
                throw std::runtime_error("Empty node ID");
            }

            if (node_ids.contains(node.id)) {
                throw std::runtime_error(
                    std::format("Duplicate node id: '{}'", node.id));
            }
            node_ids.insert(node.id);

            if (node.ports) {
                for (const auto& port : *node.ports) {
                    if (port_ids.contains(port.id)) {
                        throw std::runtime_error(
                            std::format(
                                "Duplicate port id: '{}'", node.id));
                    }
                    port_ids.insert(port.id);
                }
            }

            for (const auto& child : node.children) {
                collect_node_ids(child);
            }
        };

    for (const auto& node : graph.children) { collect_node_ids(node); }

    if (graph.ports) {
        for (const auto& port : *graph.ports) {
            if (port_ids.contains(port.id)) {
                throw std::runtime_error(
                    std::format("Duplicate port id: '{}'", port.id));
            }
            port_ids.insert(port.id);
        }
    }

    std::function<void(std::optional<std::vector<Edge>> const&)>
        validate_edges = [&](std::optional<std::vector<Edge>> const&
                                 edges) {
            if (!edges) { return; }

            for (const auto& edge : *edges) {
                if (edge.id.empty()) {
                    throw std::runtime_error("Empty edge ID");
                }
                if (edge_ids.contains(edge.id)) {
                    throw std::runtime_error(
                        std::format("Duplicate edge id: '{}'", edge.id));
                }
                edge_ids.insert(edge.id);

                if (edge.source && !node_ids.contains(*edge.source)
                    && !port_ids.contains(*edge.source)) {
                    throw std::runtime_error(
                        std::format(
                            "Edge '{}' references unknown source: '{}'",
                            edge.id,
                            *edge.source));
                }

                if (edge.target && !node_ids.contains(*edge.target)
                    && !port_ids.contains(*edge.target)) {
                    throw std::runtime_error(
                        std::format(
                            "Edge '{}' references unknown target: '{}'",
                            edge.id,
                            *edge.target));
                }

                if (edge.sourcePort
                    && !port_ids.contains(*edge.sourcePort)) {
                    throw std::runtime_error(
                        std::format(
                            "Edge '{}' references unknown source port: "
                            "'{}'",
                            edge.id,
                            *edge.sourcePort));
                }

                if (edge.targetPort
                    && !port_ids.contains(*edge.targetPort)) {
                    throw std::runtime_error(
                        std::format(
                            "Edge '{}' references unknown target port: "
                            "'{}'",
                            edge.id,
                            *edge.targetPort));
                }

                if (edge.sources) {
                    for (const auto& source : *edge.sources) {
                        if (!node_ids.contains(source)
                            && !port_ids.contains(source)) {
                            throw std::runtime_error(
                                std::format(
                                    "Edge '{}' references unknown source: "
                                    "'{}'",
                                    edge.id,
                                    source));
                        }
                    }
                }

                if (edge.targets) {
                    for (const auto& target : *edge.targets) {
                        if (!node_ids.contains(target)
                            && !port_ids.contains(target)) {
                            throw std::runtime_error(
                                std::format(
                                    "Edge '{}' references unknown target: "
                                    "'{}'",
                                    edge.id,
                                    target));
                        }
                    }
                }
            }
        };

    validate_edges(graph.edges);

    std::function<void(Node const&)> validate_node_edges =
        [&](Node const& node) {
            if (node.edges) { validate_edges(node.edges); }
            for (const auto& child : node.children) {
                validate_node_edges(child);
            }
        };

    for (const auto& node : graph.children) { validate_node_edges(node); }
}


std::string elk::ElkLayoutManager::layoutDiagram(
    std::string const& graphJson) {
    LOGIC_ASSERTION_CHECK(
        elkEngine->isInitialized(),
        "Initialization failed earlier, cannot execute layout");

    return elkEngine->performLayout(graphJson);
}

elk::Graph elk::ElkLayoutManager::layoutDiagram(elk::Graph const& graph) {
    json serial = hstd::to_json_eval(graph);
    HSLOG_TRACE("{}", serial.dump(2));
    elk::validate(graph);
    std::string tmp    = serial.dump();
    auto        layout = layoutDiagram(tmp);
    HSLOG_TRACE("{}", layout);
    return hstd::from_json_eval<elk::Graph>(json::parse(layout));
}
