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

    VDesc v = boost::add_vertex(g);

    switch (n->getKind()) {
        case osk::Subtree: {
            g[v].kind = OrgGraphNode::Kind::Subtree;
            break;
        }

        case osk::AdmonitionBlock: {
            if (n.as<sem::AnnotatedParagraph>()->getAnnotationKind()
                == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
                g[v].kind = OrgGraphNode::Kind::Footnote;
            } else {
                g[v].kind = OrgGraphNode::Kind::Paragraph;
            }
            break;
        }

        case osk::Paragraph: {
            g[v].kind = OrgGraphNode::Kind::Paragraph;
            break;
        }

        case osk::Document: {
            g[v].kind = OrgGraphNode::Kind::Document;
            break;
        }

        default: {
        }
    }

    boxToVertex[box] = v;
    updateUnresolved(v);
}

void OrgGraph::updateUnresolved(VDesc newNode) {

    auto add_edge = [&](CR<OrgGraphEdge> spec, CVec<OrgBoxId> target) {
        for (auto const& box : target) {
            boost::add_edge(newNode, desc(box), spec, g);
        }
    };

    for (auto const& id : unresolved.keys()) {
        Vec<int> resolved;
        auto&    unresolved_list = unresolved[id];
        for (auto const& it : enumerator(unresolved_list)) {
            bool        found_match = false;
            auto const& link        = it.value().link;
            switch (link->getLinkKind()) {
                case slk::Id: {
                    if (auto target = subtreeIds.get(link->getId().text)) {
                        found_match = true;
                        add_edge(
                            OrgGraphEdge{
                                .kind = OrgGraphEdge::Kind::SubtreeId,
                            },
                            *target);
                    }
                    break;
                }

                case slk::Footnote: {
                    if (auto target = footnoteTargets.get(
                            link->getFootnote().target)) {
                        found_match = true;
                        add_edge(
                            OrgGraphEdge{
                                .kind = OrgGraphEdge::Kind::Footnote,
                            },
                            *target);
                    }
                    break;
                }

                default: {
                }
            }

            if (found_match) { resolved.push_back(it.index()); }
        }

        rs::reverse(resolved);
        for (auto const& it : resolved) {
            unresolved_list.erase(unresolved_list.begin() + it);
        }

        if (unresolved_list.empty()) { unresolved.erase(id); }
    }
}
