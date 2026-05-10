#include "graph_elk.hpp"

#include <unordered_set>
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/JsonSerde.hpp>


using namespace hstd;
using namespace hstd::ext;
using namespace hstd::ext::graph;

void elk::validate(elk::GraphElkLayoutData const& graph) {
    std::unordered_set<hstd::Str> node_ids;
    std::unordered_set<hstd::Str> port_ids;
    std::unordered_set<hstd::Str> edge_ids;

    std::function<void(NodeElkLayoutData const&)> collect_node_ids =
        [&](NodeElkLayoutData const& node) {
            if (node.id.empty()) {
                throw std::runtime_error("Empty node ID");
            }

            if (node_ids.contains(node.id)) {
                throw std::runtime_error(
                    std::format("Duplicate node id: '{}'", node.id));
            }
            node_ids.insert(node.id);

            for (const auto& port : node.ports) {
                if (port_ids.contains(port.id)) {
                    throw std::runtime_error(
                        std::format("Duplicate port id: '{}'", node.id));
                }
                port_ids.insert(port.id);
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

    std::function<void(
        std::optional<std::vector<EdgeElkLayoutData>> const&)>
        validate_edges = [&](std::optional<std::vector<
                                 EdgeElkLayoutData>> const& edges) {
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

    std::function<void(NodeElkLayoutData const&)> validate_node_edges =
        [&](NodeElkLayoutData const& node) {
            validate_edges(node.edges);
            for (const auto& child : node.children) {
                validate_node_edges(child);
            }
        };

    for (const auto& node : graph.children) { validate_node_edges(node); }
}


std::string elk::ElkLayoutAlgorithm::Manager::layoutDiagram(
    std::string const& graphJson) {
    LOGIC_ASSERTION_CHECK(
        elkEngine->isInitialized(),
        "Initialization failed earlier, cannot execute layout");

    return elkEngine->performLayout(graphJson);
}

elk::GraphElkLayoutData elk::ElkLayoutAlgorithm::Manager::layoutDiagram(
    elk::GraphElkLayoutData const& graph) {
    json serial = hstd::to_json_eval(graph);
    HSLOG_TRACE("{}", serial.dump(2));
    elk::validate(graph);
    std::string tmp    = serial.dump();
    auto        layout = layoutDiagram(tmp);
    HSLOG_TRACE("{}", layout);
    return hstd::from_json_eval<elk::GraphElkLayoutData>(
        json::parse(layout));
}

namespace {

elk::EdgeElkLayoutData gen_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    EdgeID const&                        edge) {
    return *run->getEdgeVisualAttribute<elk::EdgeVisual>(edge);
}

elk::NodeElkLayoutData gen_node_structure(
    hstd::SPtr<layout::LayoutRun> const&    run,
    hstd::UnorderedMap<hstd::Str, VertexID> layout_switch_nodes,
    VertexID const&                         id,
    hstd::Opt<VertexID> const&              parent) {
    auto group = run->getGroup(id);
    if (group->hasAlgorithm()) {
        run->message(
            hstd::fmt(
                "group '{}' has layout algorithm set",
                group->getStableId()));
        auto recursiveBBox = run->getLayout(id)->getBBox();
        auto id_text       = hstd::fmt("tmp-subgraph-node-{}", id);
        layout_switch_nodes.insert_or_assign(id_text, id);

        elk::NodeElkLayoutData res;
        res.id = id_text;
        res.setSize(recursiveBBox.width(), recursiveBBox.height());
        return res;
    } else {
        auto gv_group = hstd::validated_dynamic_cast<elk::GroupVisual>(
            group);
        LOGIC_ASSERTION_CHECK(
            gv_group != nullptr,
            "Nested subgroup without layout algorithm must be an "
            "instance of gv::GroupVisual");

        elk::NodeElkLayoutData res;
        auto                   __scope = run->scopeLevel();
        for (auto const& sub : run->getSubGroups(id)) {
            res.children.push_back(
                gen_node_structure(run, layout_switch_nodes, sub, id));
        }

        for (auto const& edge : run->getDirectlyNestedEdges(id)) {
            res.edges.push_back(gen_node_structure(run, edge));
        }

        return res;
    }
};
} // namespace

hstd::ext::graph::layout::IPlacementAlgorithm::Result hstd::ext::graph::
    elk::ElkLayoutAlgorithm::runSingleLayout(VertexID const& root_id) {
    GraphElkLayoutData full_graph;
    full_graph.x      = this->x;
    full_graph.y      = this->y;
    full_graph.width  = this->width;
    full_graph.height = this->height;
    full_graph.opts   = this->opts;

    hstd::UnorderedMap<hstd::Str, VertexID> layout_switch_nodes;


    {
        run->message("collecting nodes for the graphviz layout");

        for (auto const& sub : run->getSubGroups(root_id)) {
            full_graph.children.push_back(gen_node_structure(
                run, layout_switch_nodes, root_id, std::nullopt));
        }

        for (auto const& edge : run->getDirectlyNestedEdges(root_id)) {
            full_graph.edges->push_back(gen_node_structure(run, edge));
        }
    }


    Result res;

    manager->layoutDiagram(full_graph);

    return res;
}

hstd::SPtr<elk::GroupVisual> hstd::ext::graph::elk::GroupVisual::
    newRootGraph(
        hstd::SPtr<layout::LayoutRun> run,
        hstd::Str const&              name) {

    auto result = std::make_shared<elk::GroupVisual>(
        std::make_shared<elk::GroupVisual::SharedCtx>(run), name);

    result->algorithm = std::make_shared<elk::ElkLayoutAlgorithm>(
        run, std::make_shared<ElkLayoutAlgorithm::Manager>());

    return result;
}
