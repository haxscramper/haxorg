
#if ORG_BUILD_WITH_CGRAPH
#    include <graphviz/cgraph.h>
#    include <graphviz/gvc.h>
#endif


#include <hstd/ext/graph/visual/graph_graphviz.hpp>


hstd::SPtr<hstd::ext::graph::gv::GraphGroup> graphviz_processor::get_graphviz(
    hstd::SPtr<hstd::ext::graph::layout::LayoutRun> const& run) {
    using namespace hstd::ext;
    using namespace hstd::ext::graph;
    auto graph = gv::GraphGroup::newStandaloneRootGraph("g"_ss);
    std::unordered_map<std::string, hstd::SPtr<gv::NodeAttribute>> graph_nodes{};
    std::unordered_map<std::string, hstd::SPtr<gv::GraphGroup>>    clusters{};

    graph->defaultNode.setNodeShape(gv::NodeShape::rect);

    auto get_node = [&](hstd::SPtr<gv::GraphGroup> const& g, std::string const& name) {
        if (!graph_nodes.contains(name)) {
            graph_nodes.insert_or_assign(name, g->node(name));
        }
        return graph_nodes.at(name);
    };

    for (auto const& [name, info] : nodes) {
        if (info.is_cluster) {
            std::string cluster_name = fmt::format("cluster_{}", name);
            auto        cluster      = graph->newSubgraph(cluster_name);
            cluster->setLabel(name);
            clusters.insert_or_assign(name, cluster);

            auto node = get_node(cluster, name);

            for (auto const& sub : info.subnodes) { get_node(cluster, sub); }
        } else {
            get_node(graph, name);
        }
    }

    for (auto const& [edge_key, call] : edges) {
        int         pos  = edge_key.find(" -> ");
        std::string from = edge_key.substr(0, pos);
        std::string to   = edge_key.substr(pos + 4);

        auto from_node = graph_nodes.at(from);
        auto to_node   = graph_nodes.at(to);
        auto edge      = graph->edge(*from_node, *to_node);

        std::string label{};
        if (!call.jump_description.empty() && call.count > 1) {
            label = fmt::format("{} ({})", call.jump_description, call.count);
        } else if (!call.jump_description.empty()) {
            label = call.jump_description;
        } else if (call.count > 1) {
            label = fmt::format("({})", call.count);
        }

        if (!label.empty()) { edge->setLabel(label); }
    }

    return graph;
}

// hstd_cpp/hstd_lib/tests/tGraphTracker.cpp
{
    layout::LayoutRun::TrivialState state;
    auto                            run = state.init();

    hstd::fs::path path = getDebugFile("result.png");
    processor->get_graphviz(run)->render(path);
    std::ifstream file{path};
    EXPECT_TRUE(file.good());
}
{
    layout::LayoutRun::TrivialState state;
    auto                            run  = state.init();
    hstd::fs::path                  path = getDebugFile("result.dot");
    processor->get_graphviz(run)->render(
        path, gv::LayoutType::dot, gv::RenderFormat::DOT);
    std::ifstream file{path};
    EXPECT_TRUE(file.good());
}
