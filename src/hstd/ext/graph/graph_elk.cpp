#include "graph_elk.hpp"

#include <unordered_set>
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/Ranges.hpp>


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
                throw hstd::runtime_error::init("Empty node ID");
            }

            if (node_ids.contains(node.id)) {
                throw hstd::runtime_error::init(
                    std::format("Duplicate node id: '{}'", node.id));
            }
            node_ids.insert(node.id);

            for (const auto& port : node.ports) {
                if (port_ids.contains(port.id)) {
                    throw hstd::runtime_error::init(
                        std::format("Duplicate port id: '{}'", node.id));
                }
                port_ids.insert(port.id);
            }

            for (const auto& child : node.children) {
                collect_node_ids(child);
            }
        };

    for (const auto& node : graph.children) { collect_node_ids(node); }

    for (const auto& port : graph.ports) {
        if (port_ids.contains(port.id)) {
            throw hstd::runtime_error::init(
                std::format("Duplicate port id: '{}'", port.id));
        }
        port_ids.insert(port.id);
    }

    std::function<void(
        std::optional<std::vector<EdgeElkLayoutData>> const&)>
        validate_edges = [&](std::optional<std::vector<
                                 EdgeElkLayoutData>> const& edges) {
            if (!edges) { return; }

            for (const auto& edge : *edges) {
                if (edge.id.empty()) {
                    throw hstd::runtime_error::init("Empty edge ID");
                }
                if (edge_ids.contains(edge.id)) {
                    throw hstd::runtime_error::init(
                        std::format("Duplicate edge id: '{}'", edge.id));
                }
                edge_ids.insert(edge.id);

                if (edge.source && !node_ids.contains(*edge.source)
                    && !port_ids.contains(*edge.source)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown source: '{}'",
                            edge.id,
                            *edge.source));
                }

                if (edge.target && !node_ids.contains(*edge.target)
                    && !port_ids.contains(*edge.target)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown target: '{}'",
                            edge.id,
                            *edge.target));
                }

                if (edge.sourcePort
                    && !port_ids.contains(*edge.sourcePort)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown source port: "
                            "'{}'",
                            edge.id,
                            *edge.sourcePort));
                }

                if (edge.targetPort
                    && !port_ids.contains(*edge.targetPort)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown target port: "
                            "'{}'",
                            edge.id,
                            *edge.targetPort));
                }

                for (const auto& source : edge.sources) {
                    if (!node_ids.contains(source)
                        && !port_ids.contains(source)) {
                        throw hstd::runtime_error::init(
                            std::format(
                                "Edge '{}' references unknown source: "
                                "'{}'",
                                edge.id,
                                source));
                    }
                }

                for (const auto& target : edge.targets) {
                    if (!node_ids.contains(target)
                        && !port_ids.contains(target)) {
                        throw hstd::runtime_error::init(
                            std::format(
                                "Edge '{}' references unknown target: "
                                "'{}'",
                                edge.id,
                                target));
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
    elk::GraphElkLayoutData const&       graph,
    hstd::SPtr<layout::LayoutRun> const& run) {
    json       serial  = hstd::to_json_eval(graph);
    static int counter = 0;
    run->writeAdjacentToTraceFile(
        hstd::fmt("pre_validate_dump_{}.json", counter), serial.dump(2));
    elk::validate(graph);
    std::string tmp    = serial.dump();
    auto        layout = layoutDiagram(tmp);
    auto        parsed = json::parse(layout);
    run->writeAdjacentToTraceFile(
        hstd::fmt("post_layout_dump_{}.json", counter), parsed.dump(2));
    return hstd::from_json_eval<elk::GraphElkLayoutData>(parsed);
}

namespace {

struct IdCollection {
    hstd::ext::Unordered1to1Bimap<hstd::Str, VertexID> v_id_map;
    hstd::ext::Unordered1to1Bimap<hstd::Str, EdgeID>   e_id_map;

    VertexID get_vertex_id(hstd::Str const& id) const {
        return v_id_map.at_right(id);
    }

    EdgeID get_edge_id(hstd::Str const& id) const {
        return e_id_map.at_right(id);
    }

    hstd::Str get_id(VertexID const& id) {
        if (!v_id_map.contains_right(id)) {
            auto id_text = hstd::fmt("n-{}", id);
            v_id_map.add_unique(id_text, id);
        }
        return v_id_map.at_left(id);
    }

    hstd::Str get_id(EdgeID const& id) {
        if (!e_id_map.contains_right(id)) {
            auto id_text = hstd::fmt("e-{}", id);
            e_id_map.add_unique(id_text, id);
        }
        return e_id_map.at_left(id);
    }
};

elk::EdgeElkLayoutData gen_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    EdgeID const&                        edge,
    IdCollection&                        id_map) {
    auto res    = *run->getEdgeVisualAttribute<elk::EdgeVisual>(edge);
    res.id      = id_map.get_id(edge);
    res.sources = {id_map.get_id(run->getGraph()->getSource(edge))};
    res.targets = {id_map.get_id(run->getGraph()->getTarget(edge))};
    // run->message(hstd::value_metadata<hstd::Opt<hstd::Str>>::isEmpty(res.));
    return res;
}

elk::NodeElkLayoutData gen_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    IdCollection&                        id_map,
    VertexID const&                      id,
    hstd::Opt<VertexID> const&           parent);

elk::NodeElkLayoutData gen_subgroup_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    IdCollection&                        id_map,
    VertexID const&                      id,
    hstd::Opt<VertexID> const&           parent) {
    auto group    = run->getGroup(id);
    auto gv_group = hstd::validated_dynamic_cast<elk::GroupVisual>(group);
    LOGIC_ASSERTION_CHECK(
        gv_group != nullptr,
        "Nested subgroup without layout algorithm must be an "
        "instance of gv::GroupVisual");

    elk::NodeElkLayoutData res;
    res.id       = id_map.get_id(id);
    auto __scope = run->scopeLevel();
    for (auto const& sub : run->getSubGroups(id)) {
        res.children.push_back(gen_node_structure(run, id_map, sub, id));
    }

    for (auto const& node : run->getDirectVertices(id)) {
        res.children.push_back(gen_node_structure(run, id_map, node, id));
    }

    for (auto const& edge : run->getDirectlyNestedEdges(id)) {
        res.edges.push_back(gen_node_structure(run, edge, id_map));
    }

    return res;
}

elk::NodeElkLayoutData gen_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    IdCollection&                        id_map,
    VertexID const&                      id,
    hstd::Opt<VertexID> const&           parent) {
    if (run->isGroupVertex(id)) {
        auto group = run->getGroup(id);

        if (group->hasAlgorithm()) {
            run->message(
                hstd::fmt(
                    "group '{}' has layout algorithm set",
                    group->getStableId()));
            auto recursiveBBox = run->getLayout(id)->getBBox();


            elk::NodeElkLayoutData res;
            res.id = id_map.get_id(id);
            res.setSize(recursiveBBox.width(), recursiveBBox.height());
            return res;
        } else {
            return gen_subgroup_node_structure(run, id_map, id, parent);
        }
    } else {
        elk::NodeElkLayoutData
            res = *run->getVertexVisualAttribute<elk::NodeVisual>(id);
        res.id  = id_map.get_id(id);
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

    IdCollection id_map;

    {
        run->message("collecting nodes for the graphviz layout");
        auto sub_group = gen_subgroup_node_structure(
            run, id_map, root_id, std::nullopt);
        full_graph.edges    = sub_group.edges;
        full_graph.children = sub_group.children;
    }

    Result res;

    GraphElkLayoutData post_layout = manager->layoutDiagram(
        full_graph, run);

    auto aux_edge = [&](EdgeElkLayoutData const& node) {
        EdgeID id  = id_map.get_edge_id(node.id);
        auto   lyt = std::make_shared<EdgeLayout>();
        static_cast<EdgeElkLayoutData&>(*lyt) = node;
        lyt->validate();
        res.edges.insert_or_assign(id, lyt);
    };

    auto aux_node = [&](this auto&&              self,
                        NodeElkLayoutData const& node) -> void {
        VertexID id = id_map.get_vertex_id(node.id);

        if (run->isGroupVertex(id)) {
            auto lyt = std::make_shared<GroupLayout>();
            static_cast<NodeElkLayoutData&>(*lyt) = node;
            lyt->validate();
            res.vertices.insert_or_assign(id, lyt);

            rs::for_each(node.children, self);
            rs::for_each(node.edges, aux_edge);
        } else {
            auto lyt = std::make_shared<NodeLayout>();
            static_cast<NodeElkLayoutData&>(*lyt) = node;
            lyt->validate();
            res.vertices.insert_or_assign(id, lyt);
        }
    };

    rs::for_each(post_layout.children, aux_node);
    rs::for_each(post_layout.edges, aux_edge);

    auto lyt    = std::make_shared<GroupLayout>();
    lyt->x      = post_layout.x.value_or(0);
    lyt->y      = post_layout.x.value_or(0);
    lyt->width  = post_layout.width.value();
    lyt->height = post_layout.height.value();
    res.vertices.insert_or_assign(root_id, lyt);

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
