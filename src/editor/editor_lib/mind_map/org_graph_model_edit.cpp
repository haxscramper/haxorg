#include <editor/editor_lib/mind_map/org_graph_model.hpp>

using namespace org::mind_map;

Vec<EDesc> Graph::out_edges(CR<VDesc> source, CR<Opt<VDesc>> target) {
    Vec<EDesc> result;

    BoostBase::out_edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::out_edges(source, state.g);
         ei != ei_end;
         ++ei) {
        if (!target || boost::target(*ei, state.g) == *target) {
            result.push_back(*ei);
        }
    }

    return result;
}

Vec<EDesc> Graph::in_edges(CR<VDesc> target, CR<Opt<VDesc>> source) {
    Vec<EDesc> result;

    BoostBase::in_edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::in_edges(target, state.g);
         ei != ei_end;
         ++ei) {
        if (!source || boost::source(*ei, state.g) == *source) {
            result.push_back(*ei);
        }
    }

    return result;
}

using slk = sem::Link::Kind;

Graph::GraphStructureUpdate Graph::State::addMutation(
    OrgGraphNode const& edit) {
    GraphStructureUpdate result;
    VDesc                v = boost::add_vertex(g);
    nodes.push_back(v);
    g[v] = edit;
    Q_ASSERT(!boxToVertex.contains(edit.box));
    boxToVertex[edit.box] = v;
    result.added_nodes.push_back(v);

    if (!edit.unresolved.empty()) { unresolved.push_back(edit.box); }

    if (edit.footnoteName) {
        this->footnoteTargets[edit.footnoteName.value()].push_back(
            edit.box);
    }

    if (edit.subtreeId) {
        this->subtreeIds[edit.subtreeId.value()].push_back(edit.box);
    }

    _qfmt("edit:{}", edit);

    ResolveResult updated_resolve = getUnresolvedEdits(edit);
    g[v]                          = updated_resolve.node;

    if (g[v].unresolved.empty()) {
        auto it = unresolved.indexOf(edit.box);
        if (it != -1) { unresolved.erase(unresolved.begin() + it); }
    }

    for (auto const& op : updated_resolve.resolved) {
        _qfmt("op:{} node:{}", op, debug(op.link.link.asOrg()));
        auto remove_resolved = [&](OrgBoxId box) {
            auto desc = boxToVertex.at(box);
            rs::actions::remove_if(
                g[desc].unresolved, [&](CR<GraphLink> old) -> bool {
                    bool result = old == op.link;
                    return result;
                });
        };

        for (auto const& box : unresolved) { remove_resolved(box); }
        remove_resolved(edit.box);

        rs::actions::remove_if(unresolved, [&](CR<OrgBoxId> box) {
            return g[boxToVertex.at(box)].unresolved.empty();
        });

        auto [e, added] = boost::add_edge(
            boxToVertex.at(op.source), boxToVertex.at(op.target), g);

        edges.push_back(e);
        result.added_edges.push_back(e);
        g[e] = OrgGraphEdge{.link = op.link};
    }

    rebuildEdges();

    return result;
}

Graph::GraphStructureUpdate Graph::State::delMutation(
    OrgGraphNode const& edit) {
    GraphStructureUpdate result;
    auto                 vertex = boxToVertex.at(edit.box);
    auto it = std::find(nodes.begin(), nodes.end(), vertex);
    if (it != nodes.end()) {
        for (auto [ei, ei_end] = boost::in_edges(vertex, g); ei != ei_end;
             ++ei) {
            result.removed_edges.push_back(*ei);
        }

        for (auto [ei, ei_end] = boost::out_edges(vertex, g); ei != ei_end;
             ++ei) {
            result.removed_edges.push_back(*ei);
        }


        nodes.erase(it);
    }

    boost::clear_vertex(*it, g);
    boost::remove_vertex(*it, g);

    rebuildEdges();
    return result;
}
