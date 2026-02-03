#include "ElkJsonSerial.hpp"

#include <unordered_set>

void dia::layout::elk::validate(const Graph& graph) {
    std::unordered_set<hstd::Str> node_ids;
    std::unordered_set<hstd::Str> port_ids;
    std::unordered_set<hstd::Str> edge_ids;

    std::function<void(const Node&)> collect_node_ids =
        [&](const Node& node) {
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

    std::function<void(const std::optional<std::vector<Edge>>&)>
        validate_edges = [&](const std::optional<std::vector<Edge>>&
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

    std::function<void(const Node&)> validate_node_edges =
        [&](const Node& node) {
            if (node.edges) { validate_edges(node.edges); }
            for (const auto& child : node.children) {
                validate_node_edges(child);
            }
        };

    for (const auto& node : graph.children) { validate_node_edges(node); }
}
