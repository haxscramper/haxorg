#include "ImmOrgGraph.hpp"
#include "haxorg/sem/SemBaseApi.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <immer/set_transient.hpp>
#include <immer/vector_transient.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>

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

void removeUnresolvedNodeProps(
    NodeProps::transient_type&  props,
    MapNodeResolveResult const& resolved_node,
    MapNode const&              newNode,
    ImmSet<MapNode> const&      existingUnresolved,
    MapOpsConfig&               conf) {
    for (auto const& op : resolved_node.resolved) {
        auto remove_resolved = [&](MapNode node) {
            MapNodeProp prop = props[node];
            rs::actions::remove_if(
                prop.unresolved, [&](CR<MapLink> old) -> bool {
                    bool result = old.link == op.link.link;
                    return result;
                });

            props.set(node, prop);
        };

        for (auto const& box : existingUnresolved) {
            remove_resolved(box);
        }
        remove_resolved(newNode);
    }
}

ImmSet<MapNode> updateUnresolvedNodeTracking(
    MapGraphState const&        inputState,
    NodeProps::transient_type&  props,
    MapNodeResolveResult const& resolved_node,
    MapNode const&              newNode,
    MapOpsConfig&               conf) {
    conf.message(
        fmt("New node {}, resolution result {}", newNode, resolved_node),
        conf.activeLevel);

    auto tmp = inputState.unresolved.transient();
    if (resolved_node.node.unresolved.empty()) {
        // Newly added node has no unresolved elements, remove the ID from
        // map state tracking.
        if (inputState.unresolved.find(newNode)) { tmp.erase(newNode); }
    } else {
        logic_assertion_check(
            !inputState.unresolved.find(newNode),
            "Duplicate unresolved boxes are not expected: {}",
            newNode);

        if (conf.TraceState) {
            conf.message(
                fmt("Adding {} as unresolved", newNode), conf.activeLevel);
        }
        tmp.insert(newNode);
    }

    for (auto const& op : resolved_node.resolved) {
        for (auto it : inputState.unresolved) {
            if (props.at(it).unresolved.empty()) {
                conf.message(
                    fmt("Node {} fixed all unresolved properties", it),
                    conf.activeLevel);
                tmp.erase(it);
            }
        }
    }

    return tmp.persistent();
}

void updateResolvedEdges(
    MapGraphTransient&          graphTransient,
    MapNodeResolveResult const& resolved_node,
    MapOpsConfig&               conf) {
    for (auto const& op : resolved_node.resolved) {
        for (auto const& target : graphTransient.adjList.at(op.source)) {
            logic_assertion_check(
                op.target != target,
                "There is already a link between {} and {}, graph cannot "
                "contain duplicate edges op:{}",
                op.source,
                op.target,
                op);
        }

        if (conf.TraceState) {
            conf.message(
                fmt("add edge {}-{}", op.source, op.target),
                conf.activeLevel);
        }

        MapEdge edge{op.source, op.target};

        graphTransient.adjList.set(
            op.source,
            graphTransient.adjList.at(op.source).push_back(op.target));

        graphTransient.edgeProps.set(edge, MapEdgeProp{.link = op.link});
    }
}

org::graph::MapGraphState updateTrackingTables(
    MapGraphState const& inputState,
    MapNodeProp const&   unresolved_node,
    MapOpsConfig&        conf) {

    MapGraphState outputState = inputState;
    MapNode       mapNode{unresolved_node.id.id};

    if (auto footnote = unresolved_node.getFootnoteName()) {
        logic_assertion_check(
            inputState.footnoteTargets.find(*footnote) == nullptr,
            "Duplicate footnote");
        outputState.footnoteTargets = inputState.footnoteTargets.set(
            *footnote, mapNode);
    }

    if (auto id = unresolved_node.getSubtreeId()) {
        logic_assertion_check(
            inputState.subtreeTargets.find(*id) == nullptr,
            "Duplicate subtree ID");
        outputState.subtreeTargets = inputState.subtreeTargets.set(
            *id, mapNode);
    }

    return outputState;
}

void traceNodeResolve(
    MapGraphState const&        outputState,
    MapNodeResolveResult const& resolved_node,
    MapOpsConfig&               conf,
    MapNode const&              mapNode) {
    if (conf.TraceState) {
        conf.message(
            fmt("v:{} original unresolved state:{} resolved:{} still "
                "unresolved:{}",
                mapNode,
                outputState.unresolved,
                resolved_node.node.unresolved,
                resolved_node.resolved),
            conf.activeLevel);

        if (outputState.graph.nodeProps.find(mapNode) != nullptr) {
            for (auto const& u :
                 outputState.graph.at(mapNode).unresolved) {
                conf.message(
                    fmt(">> g[v] unresolved {}", u.link),
                    conf.activeLevel);
            }
        } else {
            conf.message(
                fmt(">> new node, no preexisting unresolved"),
                conf.activeLevel);
        }

        for (auto const& u : resolved_node.node.unresolved) {
            conf.message(
                fmt("<<- updated unresolved {}", u.link),
                conf.activeLevel);
        }
        for (auto const& u : resolved_node.resolved) {
            conf.message(
                fmt("<<+ updated resolved {} {}->{}",
                    u.link.link,
                    u.source,
                    u.target),
                conf.activeLevel);
        }
    }
}

org::graph::MapGraphState org::graph::addNode(
    MapGraphState const& inputState,
    MapNodeProp const&   unresolved_node,
    MapOpsConfig&        conf) {

    // Update ID tracking tables so the newly added node could be found by
    // the ID resolution.
    MapGraphState outputState = updateTrackingTables(
        inputState, unresolved_node, conf);

    auto    graphTransient = inputState.graph.transient();
    MapNode mapNode{unresolved_node.id.id};

    graphTransient.adjList.set(mapNode, ImmVec<MapNode>{});
    if (conf.TraceState) {
        conf.message(
            fmt("unresolved:{}", outputState.unresolved),
            conf.activeLevel);
    }

    MapNodeResolveResult resolved_node = getResolvedNodeInsert(
        outputState, unresolved_node, conf);


    // debug-print node resolution state
    traceNodeResolve(outputState, resolved_node, conf, mapNode);

    // Assign node resolution result to node properties, all links have
    // been finalized.
    graphTransient.nodeProps.set(mapNode, resolved_node.node);

    // Iterate over all known unresolved nodes and adjust node property
    // values in the graph to account for new property changes.
    removeUnresolvedNodeProps(
        graphTransient.nodeProps,
        resolved_node,
        mapNode,
        outputState.unresolved,
        conf);

    // Collect new list of unresolved nodes for the changes.
    outputState.unresolved = updateUnresolvedNodeTracking(
        outputState,
        graphTransient.nodeProps,
        resolved_node,
        mapNode,
        conf);

    // Add all resolved edges to the graph
    updateResolvedEdges(graphTransient, resolved_node, conf);
    outputState.graph = graphTransient.persistent();

    return outputState;
}


static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::List,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};


Opt<MapNodeProp> org::graph::getUnresolvedNodeInsert(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapOpsConfig&        conf) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    if (isMmapIgnored(node)) {
        conf.message(
            fmt("Node {} is ignored for mmap", node), conf.activeLevel);
        return std::nullopt;
    }

    if (conf.TraceState) {
        conf.message(
            fmt("box:{} desc-item:{} desc-list:{}",
                node,
                isLinkedDescriptionItem(node),
                isLinkedDescriptionList(node)),
            conf.activeLevel);
    }

    MapNodeProp result{.id = node};

    auto register_used_links = [&](org::ImmAdapter arg) {
        conf.message(fmt("Node {}", arg), conf.activeLevel);
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
        // way to provide an extensive label between subtree nodes.
        for (auto const& list : tree->subAs<org::ImmList>()) {
            conf.message("Subtree has list", conf.activeLevel);
            for (auto const& item : list.subAs<org::ImmListItem>()) {
                conf.message(fmt("{}", item.id), conf.activeLevel);
                if (isLinkedDescriptionItemNode(item)) {
                    conf.message(
                        "List has description item", conf.activeLevel);
                    for (auto const& link :
                         item.pass(item->header->value())
                             .subAs<org::ImmLink>()) {
                        conf.message(
                            fmt("List item contains link {}", link),
                            conf.activeLevel);
                        // Description list header might contain
                        // non-link elements. These are ignored in the
                        // mind map.
                        if (link->getLinkKind() != slk::Raw) {
                            MapLink map_link{.link = link};
                            for (auto const& sub : item.sub()) {
                                map_link.description.push_back(sub);
                            }
                            result.unresolved.push_back(map_link);
                        }
                    }
                }
            }
        }
    } else if (!NestedNodes.contains(node->getKind())) {
        conf.message(
            "registering nested outgoing links", conf.activeLevel);
        auto __tmp = conf.scopeLevel();
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
        conf.message(
            fmt("box:{} unresolved:{}", node, result.unresolved),
            conf.activeLevel);
    }

    return result;
}

MapGraph org::graph::MapGraphTransient::persistent() {
    auto result = MapGraph{};

    result.adjList   = adjList.persistent();
    result.edgeProps = edgeProps.persistent();
    result.nodeProps = nodeProps.persistent();

    return result;
}

MapGraphTransient org::graph::MapGraph::transient() const {
    auto result = MapGraphTransient{};

    result.nodeProps = nodeProps.transient();
    result.edgeProps = edgeProps.transient();
    result.adjList   = adjList.transient();

    return result;
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
                link),
            conf.activeLevel);
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


MapNodeResolveResult org::graph::getResolvedNodeInsert(
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
        conf.message(fmt("unresolved:{}", s.unresolved), conf.activeLevel);
    }

    for (auto const& unresolvedLink : node.unresolved) {
        Opt<MapLinkResolveResult> resolved_edit = getResolveTarget(
            s, MapNode{node.id.id}, unresolvedLink, conf);
        if (resolved_edit) {
            if (conf.TraceState) {
                conf.message(
                    fmt("resolved:{}", *resolved_edit), conf.activeLevel);
            }

            result.resolved.push_back(*resolved_edit);
        } else {
            result.node.unresolved.push_back(unresolvedLink);
        }
    }

    for (auto const& nodeWithUnresolved : s.unresolved) {
        logic_assertion_check(
            nodeWithUnresolved.id != node.id.id,
            "cannot resolve already inserted node {} == {} ({}) is "
            "recorded in "
            "s.unresolved",
            nodeWithUnresolved.id,
            node.id.id,
            nodeWithUnresolved.id != node.id.id);

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
                            node),
                        conf.activeLevel);
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
                result.node.unresolved),
            conf.activeLevel);
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

MapGraphState org::graph::addNode(
    const MapGraphState&   g,
    const org::ImmAdapter& node,
    MapOpsConfig&          conf) {
    if (conf.TraceState) {
        conf.message(Str("- ").repeated(32), conf.activeLevel);
    }
    auto prop = getUnresolvedNodeInsert(g, node, conf);
    if (prop) {
        if (conf.TraceState) {
            conf.message("ID maps to graph node", conf.activeLevel);
        }
        auto __init = conf.scopeLevel();
        return addNode(g, *prop, conf);
    } else {
        return g;
    }
}

Graphviz::Graph MapGraph::toGraphviz(org::ImmAstContext const& ctx) const {
    Graphviz::Graph                       res{"g"_ss};
    UnorderedMap<MapNode, Graphviz::Node> gvNodes;
    UnorderedMap<MapEdge, Graphviz::Edge> gvEdges;
    for (auto const& [it, props] : nodeProps) {
        gvNodes.insert_or_assign(it, res.node(it.id.getReadableId()));
    }

    for (auto const& [source, targets] : adjList) {
        for (auto const& target : targets) {
            gvEdges.insert_or_assign(
                {source, target},
                res.edge(gvNodes.at(source), gvNodes.at(target)));
        }
    }

    for (auto const& [it, prop] : nodeProps) {
        using Record = Graphviz::Node::Record;
        auto& node   = gvNodes.at(it);
        node.startRecord();
        auto rec       = node.getNodeRecord();
        auto add_field = [&](Record const& r) { rec->push_back(r); };

        add_field(Record{{
            Record{left_aligned("ID", 16)},
            Record{fmt1(it.id)},
        }});

        add_field(Record{{
            Record{left_aligned("Path", 16)},
            Record{join("/", ctx.getPath(it.id))},
        }});

        add_field(Record{{
            Record{left_aligned("Kind", 16)},
            Record{fmt1(prop.kind)},
        }});

        for (auto const& [idx, unresolved] : enumerate(prop.unresolved)) {
            add_field(Record{{
                Record{left_aligned(fmt("Unresolved [{}]", idx), 16)},
                Record{fmt1(unresolved.link)},
            }});
        }

        switch (prop.kind) {
            case MapNodeProp::Kind::Subtree: {
                break;
            }
            default: {
            }
        }

        node.finishRecord();
    }

    return res;
}

MapGraphState org::graph::addNodeRec(
    const MapGraphState&   g,
    const org::ImmAdapter& node,
    MapOpsConfig&          conf) {
    auto                               res = g;
    Func<void(org::ImmAdapter const&)> aux;
    aux = [&](org::ImmAdapter const& node) {
        conf.message(fmt("recursive add {}", node), conf.activeLevel);
        auto __tmp = conf.scopeLevel();
        switch (node->getKind()) {
            case osk::Document:
            case osk::ListItem:
            case osk::List: {
                for (auto const& it : node) { aux(it); }
                break;
            }
            case osk::Paragraph: {
                {
                    auto __add = conf.scopeTrace(false);
                    res        = addNode(res, node, conf);
                }
                break;
            }
            case osk::Subtree: {
                {
                    auto __add = conf.scopeTrace(false);
                    res        = addNode(res, node, conf);
                }
                for (auto const& it : node) { aux(it); }
                break;
            }
            default: {
            }
        }
    };

    aux(node);

    return res;
}
