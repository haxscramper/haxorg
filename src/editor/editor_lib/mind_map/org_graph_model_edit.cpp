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

Graph::GraphStructureUpdate Graph::State::addMutation(const Edit& edit) {
    GraphStructureUpdate result;
    for (auto const& op : edit.vertices) {
        VDesc v = boost::add_vertex(g);
        nodes.push_back(v);
        g[v].box            = op.box;
        boxToVertex[op.box] = v;
        result.added_nodes.push_back(v);
    }

    for (auto const& op : edit.unresolved) {
        this->unresolved.push_back(op);
    }

    for (auto const& op : edit.resolved) {
        auto is_same = [&](CR<UnresolvedLink> old) -> bool {
            Q_ASSERT(!old.link.isNil());
            Q_ASSERT(!op.original.link.isNil());

            sem::Link const& lhs = *old.link.value;
            sem::Link const& rhs = *op.original.link.value;

            if (lhs.getLinkKind() != rhs.getLinkKind()) {
                return false;
            } else {
                switch (lhs.getLinkKind()) {
                    case slk::Id:
                        return lhs.getId().text == rhs.getId().text;
                    case slk::Footnote:
                        return lhs.getFootnote().target
                            == rhs.getFootnote().target;
                    default: qFatal("TODO");
                }
            }
        };

        rs::actions::remove_if(this->unresolved, is_same);

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

Graph::GraphStructureUpdate Graph::State::delMutation(const Edit& edit) {
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
