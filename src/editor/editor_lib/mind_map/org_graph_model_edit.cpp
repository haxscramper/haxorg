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
    if (debug) { _qfmt("unresolved:{}", unresolved); }
    g[v] = edit;
    Q_ASSERT(!boxToVertex.contains(edit.box));
    Q_ASSERT(!unresolved.contains(edit.box));

    boxToVertex[edit.box] = v;
    result.added_node     = v;

    if (debug) {
        _qfmt("box:{} v:{} boxToVertex:{}", edit.box, v, boxToVertex);
    }

    if (edit.footnoteName) {
        Q_ASSERT(!footnoteTargets.contains(*edit.footnoteName));
        footnoteTargets[*edit.footnoteName] = edit.box;
    }

    if (edit.subtreeId) {
        Q_ASSERT(!subtreeIds.contains(*edit.subtreeId));
        subtreeIds[*edit.subtreeId] = edit.box;
    }


    ResolveResult updated_resolve = getUnresolvedEdits(edit);
    if (debug) {
        _qfmt(
            "v:{} g[v]:{} edit:{} updated:{}",
            v,
            g[v].unresolved,
            edit.unresolved,
            updated_resolve.node.unresolved);

        for (auto const& u : g[v].unresolved) {
            _qfmt(">> g[v] unresolved {}", ::debug(u.link.asOrg()));
        }
        for (auto const& u : updated_resolve.node.unresolved) {
            _qfmt("<<- updated unresolved {}", ::debug(u.link.asOrg()));
        }
        for (auto const& u : updated_resolve.resolved) {
            _qfmt(
                "<<+ updated resolved {} {}->{}",
                ::debug(u.link.link.asOrg()),
                u.source,
                u.target);
        }
    }

    g[v] = updated_resolve.node;

    if (g[v].unresolved.empty()) {
        if (unresolved.contains(edit.box)) { unresolved.erase(edit.box); }
    } else {
        Q_ASSERT_X(
            !unresolved.contains(edit.box),
            "addMutation",
            fmt("Duplicate unresolved boxes are not expected: {}", edit));

        unresolved.incl(edit.box);
    }


    for (auto const& op : updated_resolve.resolved) {
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

        for (auto it = unresolved.begin(); it != unresolved.end();) {
            if (g[boxToVertex.at(*it)].unresolved.empty()) {
                it = unresolved.erase(it);
            } else {
                ++it;
            }
        }

        VDesc source = boxToVertex.at(op.source);
        VDesc target = boxToVertex.at(op.target);
        for (auto [it, end] = boost::in_edges(target, g); it != end;
             ++it) {
            Q_ASSERT_X(
                (boost::source(*it, g) != source),
                "duplicate edge",
                fmt("There is already a link between {} and {} (vertex "
                    "{}-{}), graph cannot contain duplicate edges op:{}",
                    op.source,
                    op.target,
                    source,
                    target,
                    op));
        }

        if (debug) {
            _qfmt(
                "add edge {}-{} (vertex {}-{})",
                op.source,
                op.target,
                source,
                target);
        }

        auto [e, added] = boost::add_edge(source, target, g);

        result.added_edges.push_back(e);
        g[e] = OrgGraphEdge{.link = op.link};
    }

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
            auto source = boost::source(*ei, g);
            auto target = boost::target(*ei, g);
            Q_ASSERT(g[target].box == edit.box);
            g[source].unresolved.push_back(g[*ei].link);
            result.removed_edges.push_back(*ei);
            unresolved.incl(g[source].box);
        }

        for (auto [ei, ei_end] = boost::out_edges(vertex, g); ei != ei_end;
             ++ei) {
            result.removed_edges.push_back(*ei);
        }
    }

    boxToVertex.erase(edit.box);

    if (unresolved.contains(edit.box)) { unresolved.excl(edit.box); }
    if (edit.subtreeId) { subtreeIds.erase(*edit.subtreeId); }
    if (edit.footnoteName) { footnoteTargets.erase(*edit.footnoteName); }
    result.removed_node = vertex;

    boost::clear_vertex(*it, g);
    boost::remove_vertex(*it, g);

    return result;
}
