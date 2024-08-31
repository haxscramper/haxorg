#include "ImmOrgGraph.hpp"
#include "haxorg/sem/SemBaseApi.hpp"
#include <hstd/stdlib/Ranges.hpp>

using namespace org::graph;
using osk = OrgSemKind;
using slk = org::ImmLink::Kind;

namespace {

bool isDescriptionItem(org::ImmAdapter node) {
    return node.as<org::ImmListItem>()->header->has_value();
}

bool isLinkedDescriptionItemNode(org::ImmAdapter n) {
    return n.is(osk::ListItem)  //
        && isDescriptionItem(n) //
        && rs::any_of(
               n.pass(n.as<org::ImmListItem>()->header.get().value())
                   .subAs<org::ImmLink>(),
               [](org::ImmAdapterT<org::ImmLink> head) -> bool {
                   return head->getLinkKind() != slk::Raw;
               });
}

bool isLinkedDescriptionItem(org::ImmAdapter n) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        n.getParentChain(/*withSelf = */ false),
        [&](org::ImmAdapter parent) -> bool {
            return isLinkedDescriptionItemNode(parent);
        });
}

/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::ImmAdapter n) {
    return n.is(osk::List)
        && rs::any_of(n.sub(), [&](org::ImmAdapter arg) -> bool {
               return isLinkedDescriptionItem(arg);
           });
}

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInLinkedDescriptionList(org::ImmAdapter n) {
    return rs::any_of(n.getParentChain(), [](org::ImmAdapter tree) {
        return isLinkedDescriptionItem(tree);
    });
}

bool isMmapIgnored(org::ImmAdapter n) {
    return isInLinkedDescriptionList(n) || isLinkedDescriptionList(n);
}
} // namespace

org::graph::MapGraphState org::graph::addNode(
    MapGraphState const& g,
    MapNodeProp const&   node,
    MapOpsConfig&        conf) {

    auto    graphTransient = g.graph.transient();
    MapNode mapNode{node.id.id};

    graphTransient.adjList.set(mapNode, ImmVec<MapNode>{});
    if (conf.TraceState) {
        conf.message(fmt("unresolved:{}", g.unresolved));
    }

    auto footnotesTransient = g.footnoteTargets.transient();
    auto subtreesTransient  = g.subtreeTargets.transient();

    if (auto footnote = node.getFootnoteName()) {
        logic_assertion_check(
            footnotesTransient.find(*footnote) == nullptr,
            "Duplicate footnote");
        footnotesTransient.set(*footnote, mapNode);
    }

    if (auto id = node.getSubtreeId()) {
        logic_assertion_check(
            subtreesTransient.find(*id) == nullptr,
            "Duplicate subtree ID");
        subtreesTransient.set(*id, mapNode);
    }

    graphTransient.nodeProps.set(mapNode, node);

#if false
    ResolveResult updated_resolve = getUnresolvedEdits(edit);
    if (conf.TraceState) {
        conf.message(
            fmt("v:{} g[v]:{} edit:{} updated:{}",
                v,
                g[v].unresolved,
                edit.unresolved,
                updated_resolve.node.unresolved));

        for (auto const& u : g[v].unresolved) {
            conf.message(
                fmt(">> g[v] unresolved {}", ::debug(u.link.asOrg())));
        }
        for (conf.message(fmt const& u : updated_resolve.node.unresolved) {
            conf.message(
                fmt("<<- updated unresolved {}", ::debug(u.link.asOrg())));
        }
        for (auto const& u : updated_resolve.resolved) {
            conf.message(
                fmt("<<+ updated resolved {} {}->{}",
                    ::debug(u.link.link.asOrg()),
                    u.source,
                    u.target));
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

        if (conf.TraceState) {
            conf.message(
                fmt("add edge {}-{} (vertex {}-{})",
                    op.source,
                    op.target,
                    source,
                    target));
        }

        auto [e, added] = boost::add_edge(source, target, g);

        result.added_edges.push_back(e);
        g[e] = OrgGraphEdge{.link = op.link};
    }

    return g;
#endif
}


static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::List,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};


Opt<MapNodeProp> getNodeInsert(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapOpsConfig&        conf) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    if (isMmapIgnored(node)) { return std::nullopt; }

    if (conf.TraceState) {
        conf.message(
            fmt("box:{} desc-item:{} desc-list:{}",
                node,
                isLinkedDescriptionItem(node),
                isLinkedDescriptionList(node)));
    }

    MapNodeProp result{.id = node};

    auto register_used_links = [&](org::ImmAdapter arg) {
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (arg.is(osk::Link)) {
            auto link = arg.as<org::ImmLink>();
            if (link->getLinkKind() != slk::Raw) {
                result.unresolved.push_back(MapLink{
                    .link = arg.as<org::ImmLink>(),
                    .description //
                    = link->description.get()
                        ? Vec{arg.pass(
                              link->description.get().value().toId())}
                        : Vec<org::ImmAdapter>{},
                });
            }
        }
    };

    if (auto tree = node.asOpt<org::ImmSubtree>()) {
        // Description lists with links in header are attached as the
        // outgoing link to the parent subtree. It is the only supported
        // way to provide an extensive label between subtree edges.
        for (auto const& list : tree->subAs<org::ImmList>()) {
            for (auto const& item : list.subAs<org::ImmListItem>()) {
                if (isLinkedDescriptionItem(item)) {
                    for (auto const& link :
                         item.pass(item->header->value())
                             .subAs<org::ImmLink>()) {
                        // Description list header might contain
                        // non-link elements. These are ignored in the
                        // mind map.
                        if (link->getLinkKind() != slk::Raw) {
                            MapLink map_link{.link = link};
                            for (auto const& sub : item) {
                                map_link.description.push_back(sub);
                            }
                            result.unresolved.push_back(map_link);
                        }
                    }
                }
            }
        }
    } else if (!NestedNodes.contains(node->getKind())) {
        org::eachSubnodeRec(node, register_used_links);
    }

    switch (node->getKind()) {
        case osk::Subtree: {
            result.kind = MapNodeProp::Kind::Subtree;
            break;
        }

        case osk::AnnotatedParagraph: {
            if (node.as<sem::AnnotatedParagraph>()->getAnnotationKind()
                == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
                result.kind = MapNodeProp::Kind::Footnote;
            } else {
                result.kind = MapNodeProp::Kind::Paragraph;
            }
            break;
        }

        case osk::Paragraph: {
            result.kind = MapNodeProp::Kind::Paragraph;
            break;
        }

        case osk::Document: {
            result.kind = MapNodeProp::Kind::Document;
            break;
        }

        case osk::List: {
            result.kind = MapNodeProp::Kind::List;
            break;
        }

        case osk::ListItem: {
            result.kind = MapNodeProp::Kind::ListItem;
            break;
        }

        default: {
        }
    }

    if (conf.TraceState) {
        conf.message(fmt("box:{} unresolved:{}", node, result.unresolved));
    }

    return result;
}

MapGraph org::graph::MapGraphTransient::persistent() {
    return MapGraph{
        .adjList   = adjList.persistent(),
        .edgeProps = edgeProps.persistent(),
        .nodeProps = nodeProps.persistent(),
    };
}

MapGraphTransient org::graph::MapGraph::transient() const {
    return MapGraphTransient{
        .nodeProps = nodeProps.transient(),
        .edgeProps = edgeProps.transient(),
        .adjList   = adjList.transient(),
    };
}

Opt<MapLinkResolveResult> org::graph::getResolveTarget(
    const MapGraphState& s,
    MapNode const&       source,
    MapLink const&       link,
    MapOpsConfig&        conf) {

    Opt<MapLinkResolveResult> result;

    if (conf.TraceState) {
        conf.message(
            fmt("subtreeIds:{} footnoteTargets:{} link:{}",
                s.subtreeTargets,
                s.footnoteTargets,
                link));
    }

    auto add_edge = [&](MapEdgeProp::Kind kind, MapNode target) {
        result = MapLinkResolveResult{
            .link   = link,
            .target = target,
            .source = source,
            .kind   = kind,
        };
    };

    switch (link.link->getLinkKind()) {
        case slk::Id: {
            if (auto target = s.subtreeTargets.get(
                    link.link->getId().text)) {
                add_edge(MapEdgeProp::Kind::SubtreeId, *target);
            }
            break;
        }

        case slk::Footnote: {
            if (auto target = s.footnoteTargets.get(
                    link.link->getFootnote().target)) {
                add_edge(MapEdgeProp::Kind::Footnote, *target);
            }
            break;
        }

        default: {
        }
    }

    return result;
}


MapNodeResolveResult getResolvedNodeInsert(
    const MapGraphState& s,
    const MapNodeProp&   node,
    MapOpsConfig&        conf) {
    MapNodeResolveResult result;
    result.node = node;
    result.node.unresolved.clear();

    logic_assertion_check(
        s.unresolved.find(MapNode{node.id.id}) == nullptr,
        "Node edit with unresolved elements is already listed as "
        "unresolved node: box is {}",
        node);

    if (conf.TraceState) {
        conf.message(fmt("unresolved:{}", s.unresolved));
    }

    for (auto const& unresolvedLink : node.unresolved) {
        Opt<MapLinkResolveResult> resolved_edit = getResolveTarget(
            s, MapNode{node.id.id}, unresolvedLink, conf);
        if (resolved_edit) {
            if (conf.TraceState) {
                conf.message(fmt("resolved:{}", *resolved_edit));
            }

            result.resolved.push_back(*resolved_edit);
        } else {
            result.node.unresolved.push_back(unresolvedLink);
        }
    }

    for (auto const& nodeWithUnresolved : s.unresolved) {
        logic_assertion_check(nodeWithUnresolved.id != node.id.id, "");
        for (auto const& link :
             s.graph.at(nodeWithUnresolved).unresolved) {
            Opt<MapLinkResolveResult> resolved_edit = getResolveTarget(
                s, nodeWithUnresolved, link, conf);
            if (resolved_edit) {
                if (conf.TraceState) {
                    conf.message(
                        fmt("resolved:{} it:{} edit:{}",
                            *resolved_edit,
                            nodeWithUnresolved,
                            node));
                }
                result.resolved.push_back(*resolved_edit);
            }
        }
    }

    if (conf.TraceState) {
        conf.message(
            fmt("box:{} resolved:{} unresolved:{}",
                node,
                result.resolved,
                result.node.unresolved));
    }

    for (auto const& r1 : result.resolved) {
        int count = 0;
        for (auto const& r2 : result.resolved) {
            if (r1.target == r2.target && r1.source == r2.source) {
                ++count;
            }
        }

        logic_assertion_check(
            count <= 1,
            "Resolved link target contains duplicate edges: {}-{}",
            r1.source,
            r1.target);
    }

    return result;
}
