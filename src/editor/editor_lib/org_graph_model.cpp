#include <editor/editor_lib/org_graph_model.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>

#pragma clang diagnostic error "-Wswitch"

using slk = sem::Link::Kind;

void OrgGraph::addBox(CR<OrgBoxId> box) {
    sem::SemId<sem::Org> n = store->node(box);
    if (n->is(osk::Subtree)) {
        sem::SemId<sem::Subtree> tree = n.as<sem::Subtree>();
        if (tree->treeId) {
            this->subtreeIds[tree->treeId.value()].push_back(box);
        }
    } else if (n->is(osk::AnnotatedParagraph)) {
        sem::SemId<sem::AnnotatedParagraph>
            par = n.as<sem::AnnotatedParagraph>();
        if (par->getAnnotationKind()
            == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
            this->footnoteTargets[par->getFootnote().name].push_back(box);
        }
    }

    if (!NestedNodes.contains(n->getKind())) {
        sem::eachSubnodeRec(n, [&](sem::OrgArg arg) {
            // Unconditionally register all links as unresolved -- some of
            // them will be converted to edges later on.
            if (arg->is(osk::Link)) {
                auto link = arg.as<sem::Link>();
                if (link->getLinkKind() != slk::Raw) {
                    unresolved[box].push_back(UnresolvedLink{
                        .link = arg.as<sem::Link>(),
                    });
                }
            }
        });
    }

    VDesc v          = boost::add_vertex(g);
    boxToVertex[box] = v;

    for (auto const& id : unresolved.keys()) {
        Vec<int> resolved;
        auto&    unresolved_list = unresolved[id];
        for (auto const& it : enumerator(unresolved_list)) {
            auto target = resolve(it.value().link);
            if (target) {
                for (auto const& box : *target) {
                    OrgGraphEdge spec;
                    if (it.value().link->getLinkKind() == slk::Id) {
                        spec.kind = OrgGraphEdge::Kind::SubtreeId;
                    }


                    boost::add_edge(v, desc(box), spec, g);
                }
                resolved.push_back(it.index());
            }
        }

        rs::reverse(resolved);
        for (auto const& it : resolved) {
            unresolved_list.erase(unresolved_list.begin() + it);
        }

        if (unresolved_list.empty()) { unresolved.erase(id); }
    }
}

Opt<Vec<OrgBoxId>> OrgGraph::resolve(CR<sem::SemId<sem::Link>> link) {
    switch (link->getLinkKind()) {
        case slk::Id: {
            return subtreeIds.get(link->getId().text);
        }

        case slk::Footnote: {
            return footnoteTargets.get(link->getFootnote().target);
        }

        case slk::File:
        case slk::UserProtocol:
        case slk::Internal:
        case slk::Person:
        case slk::Raw: {
            return std::nullopt;
        }
    }
}
