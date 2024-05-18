#include <editor/editor_lib/mind_map/org_graph_model.hpp>

Vec<OrgGraph::EDesc> OrgGraph::out_edges(
    CR<VDesc>      source,
    CR<Opt<VDesc>> target) {
    Vec<EDesc> result;

    Graph::out_edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::out_edges(source, state.g);
         ei != ei_end;
         ++ei) {
        if (!target || boost::target(*ei, state.g) == *target) {
            result.push_back(*ei);
        }
    }

    return result;
}

Vec<OrgGraph::EDesc> OrgGraph::in_edges(
    CR<VDesc>      target,
    CR<Opt<VDesc>> source) {
    Vec<EDesc> result;

    Graph::in_edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::in_edges(target, state.g);
         ei != ei_end;
         ++ei) {
        if (!source || boost::source(*ei, state.g) == *source) {
            result.push_back(*ei);
        }
    }

    return result;
}


OrgGraph::GraphStructureUpdate OrgGraph::State::addMutation(
    const Edit& edit) {
    GraphStructureUpdate result;
    for (auto const& op : edit.vertices) {
        VDesc v = boost::add_vertex(g);
        nodes.push_back(v);
        g[v].box            = op.box;
        boxToVertex[op.box] = v;
        result.added_nodes.push_back(v);
    }

    for (auto const& op : edit.unresolved) {
        this->unresolved[op.origin].push_back(op);
    }

    for (auto const& op : edit.resolved) {
        rs::remove_if(
            this->unresolved[op.original.origin],
            [&](CR<UnresolvedLink> old) -> bool {
                return old.link == op.original.link;
            });

        auto [e, added] = boost::add_edge(
            boxToVertex.at(op.original.origin),
            boxToVertex.at(op.target),
            g);

        edges.push_back(e);
        result.added_edges.push_back(e);
        g[e] = op.spec;
    }

    for (auto const& note : edit.footnotes) {
        this->footnoteTargets[note.name].push_back(note.box);
    }

    for (auto const& note : edit.subtrees) {
        this->subtreeIds[note.name].push_back(note.box);
    }

    rebuildEdges();

    return result;
}

OrgGraph::GraphStructureUpdate OrgGraph::State::delMutation(
    const Edit& edit) {
    GraphStructureUpdate result;
    for (auto const& op : edit.vertices) {
        auto vertex = boxToVertex.at(op.box);
        auto it     = std::find(nodes.begin(), nodes.end(), vertex);
        if (it != nodes.end()) {
            for (auto [ei, ei_end] = boost::in_edges(vertex, g);
                 ei != ei_end;
                 ++ei) {
                result.removed_edges.push_back(*ei);
            }

            for (auto [ei, ei_end] = boost::out_edges(vertex, g);
                 ei != ei_end;
                 ++ei) {
                result.removed_edges.push_back(*ei);
            }


            nodes.erase(it);
        }

        boost::clear_vertex(*it, g);
        boost::remove_vertex(*it, g);
    }

    rebuildEdges();
    return result;
}
