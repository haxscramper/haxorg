#include "ImmOrgGraph.hpp"
#include "haxorg/sem/SemBaseApi.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <immer/set_transient.hpp>
#include <immer/vector_transient.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>

using namespace org::graph;
using osk = OrgSemKind;
using slk = org::ImmLink::Kind;


bool org::graph::isDescriptionItem(org::ImmAdapter node) {
    return node.as<org::ImmListItem>()->header->has_value();
}

bool org::graph::isLinkedDescriptionItemNode(org::ImmAdapter n) {
    return n.is(osk::ListItem)  //
        && isDescriptionItem(n) //
        && rs::any_of(
               n.pass(n.as<org::ImmListItem>()->header.get().value())
                   .subAs<org::ImmLink>(),
               [](org::ImmAdapterT<org::ImmLink> head) -> bool {
                   return head->getLinkKind() != slk::Raw;
               });
}

bool org::graph::isLinkedDescriptionItem(org::ImmAdapter n) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        n.getParentChain(/*withSelf = */ false),
        [&](org::ImmAdapter parent) -> bool {
            return isLinkedDescriptionItemNode(parent);
        });
}

bool org::graph::isLinkedDescriptionList(org::ImmAdapter n) {
    return n.is(osk::List)
        && rs::any_of(n.sub(), [&](org::ImmAdapter arg) -> bool {
               return isLinkedDescriptionItem(arg);
           });
}

bool org::graph::isInLinkedDescriptionList(org::ImmAdapter n) {
    return rs::any_of(n.getParentChain(), [](org::ImmAdapter tree) {
        return isLinkedDescriptionItem(tree);
    });
}

bool org::graph::isMmapIgnored(org::ImmAdapter n) {
    return isInLinkedDescriptionList(n) || isLinkedDescriptionList(n);
}

void removeUnresolvedNodeProps(
    NodeProps&                   props,
    MapNodeResolveResult const&  resolved_node,
    MapNode const&               newNode,
    UnorderedSet<MapNode> const& existingUnresolved,
    MapConfig&                   conf) {
    for (auto const& op : resolved_node.resolved) {
        auto remove_resolved = [&](MapNode node) {
            MapNodeProp prop = props[node];
            rs::actions::remove_if(
                prop.unresolved, [&](CR<MapLink> old) -> bool {
                    bool result = old.link == op.link.link;
                    return result;
                });

            props.insert_or_assign(node, prop);
        };

        for (auto const& box : existingUnresolved) {
            remove_resolved(box);
        }
        remove_resolved(newNode);
    }
}

void updateUnresolvedNodeTracking(
    MapGraphState&              state,
    NodeProps&                  props,
    MapNodeResolveResult const& resolved_node,
    MapNode const&              newNode,
    MapConfig&                  conf) {
    conf.message(
        fmt("New node {}, resolution result {}", newNode, resolved_node),
        conf.activeLevel);

    if (resolved_node.node.unresolved.empty()) {
        // Newly added node has no unresolved elements, remove the ID from
        // map state tracking.
        if (state.unresolved.contains(newNode)) {
            state.unresolved.erase(newNode);
        }
    } else {
        LOGIC_ASSERTION_CHECK(
            !state.unresolved.contains(newNode),
            "Duplicate unresolved boxes are not expected: {}",
            newNode);

        if (conf.TraceState) {
            conf.message(
                fmt("Adding {} as unresolved", newNode), conf.activeLevel);
        }
        state.unresolved.insert(newNode);
    }

    for (auto const& op : resolved_node.resolved) {
        Vec<MapNode> toRemove;
        for (MapNode const& it : state.unresolved) {
            if (props.at(it).unresolved.empty()) {
                conf.message(
                    fmt("Node {} fixed all unresolved properties", it),
                    conf.activeLevel);
                toRemove.push_back(it);
            }
        }

        for (auto const& it : toRemove) { state.unresolved.erase(it); }
    }
}

void updateResolvedEdges(
    MapGraph&                   graph,
    MapNodeResolveResult const& resolved_node,
    MapConfig&                  conf) {
    for (auto const& op : resolved_node.resolved) {
        for (auto const& target : graph.adjList.at(op.source)) {
            LOGIC_ASSERTION_CHECK(
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

        graph.adjList.at(op.source).push_back(op.target);

        graph.edgeProps.insert_or_assign(
            edge, MapEdgeProp{.link = op.link});
    }
}

void updateTrackingTables(
    MapGraphState&     state,
    MapNodeProp const& unresolved_node,
    MapConfig&         conf) {

    MapNode mapNode{unresolved_node.id.id};

    if (auto footnote = unresolved_node.getFootnoteName()) {
        LOGIC_ASSERTION_CHECK(
            state.footnoteTargets.find(*footnote) == nullptr,
            "Duplicate footnote");
        state.footnoteTargets.insert_or_assign(*footnote, mapNode);
    }

    if (auto id = unresolved_node.getSubtreeId()) {
        LOGIC_ASSERTION_CHECK(
            state.subtreeTargets.find(*id) == nullptr,
            "Duplicate subtree ID");
        state.subtreeTargets.insert_or_assign(*id, mapNode);
    }
}

void traceNodeResolve(
    MapGraphState const&        outputState,
    MapNodeResolveResult const& resolved_node,
    MapConfig&                  conf,
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

void org::graph::addNode(
    MapGraphState&     state,
    MapNodeProp const& unresolved_node,
    MapConfig&         conf) {

    // Update ID tracking tables so the newly added node could be found by
    // the ID resolution.
    updateTrackingTables(state, unresolved_node, conf);

    auto&   graph = state.graph;
    MapNode mapNode{unresolved_node.id.id};

    graph.adjList.insert_or_assign(mapNode, Vec<MapNode>{});
    if (conf.TraceState) {
        conf.message(
            fmt("unresolved:{}", state.unresolved), conf.activeLevel);
    }

    MapNodeResolveResult resolved_node = getResolvedNodeInsert(
        state, unresolved_node, conf);


    // debug-print node resolution state
    traceNodeResolve(state, resolved_node, conf, mapNode);

    // Assign node resolution result to node properties, all links have
    // been finalized.
    graph.nodeProps.insert_or_assign(mapNode, resolved_node.node);

    // Iterate over all known unresolved nodes and adjust node property
    // values in the graph to account for new property changes.
    removeUnresolvedNodeProps(
        graph.nodeProps, resolved_node, mapNode, state.unresolved, conf);

    // Collect new list of unresolved nodes for the changes.
    updateUnresolvedNodeTracking(
        state, graph.nodeProps, resolved_node, mapNode, conf);

    // Add all resolved edges to the graph
    updateResolvedEdges(graph, resolved_node, conf);
}


static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::List,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};


Opt<MapLink> org::graph::getUnresolvedLink(
    const MapGraphState& s,
    ImmAdapterT<ImmLink> link,
    MapConfig&           conf) {
    if (link->getLinkKind() != slk::Raw) {
        return MapLink{
            .link = link,
            .description //
            = link->description.get()
                ? Vec{link.at(
                      link->description.get().value().toId(),
                      ImmPathStep::FieldDeref("description"))}
                : Vec<org::ImmAdapter>{},
        };
    } else {
        return std::nullopt;
    }
}


Vec<MapLink> org::graph::getUnresolvedSubtreeLinks(
    const MapGraphState&         s,
    ImmAdapterT<org::ImmSubtree> tree,
    MapConfig&                   conf) {
    Vec<MapLink> unresolved;
    // Description lists with links in header are attached as the
    // outgoing link to the parent subtree. It is the only supported
    // way to provide an extensive label between subtree nodes.
    for (auto const& list : tree.subAs<org::ImmList>()) {
        conf.message("Subtree has list", conf.activeLevel);
        for (auto const& item : list.subAs<org::ImmListItem>()) {
            conf.message(fmt("{}", item.id), conf.activeLevel);
            if (isLinkedDescriptionItemNode(item)) {
                conf.message(
                    "List has description item", conf.activeLevel);
                for (auto const& link : item.pass(item->header->value())
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
                        unresolved.push_back(map_link);
                    }
                }
            }
        }
    }

    return unresolved;
}


Opt<MapNodeProp> org::graph::getUnresolvedNodeInsertDefault(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapConfig&           conf) {
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
        if (auto link = node.asOpt<org::ImmLink>()) {
            auto target = getUnresolvedLink(s, link.value(), conf);
            if (target) { result.unresolved.push_back(target.value()); }
        }
    };

    if (auto tree = node.asOpt<org::ImmSubtree>()) {
        result.unresolved.append(
            getUnresolvedSubtreeLinks(s, tree.value(), conf));
    } else if (!NestedNodes.contains(node->getKind())) {
        conf.message(
            "registering nested outgoing links", conf.activeLevel);
        auto __tmp = conf.scopeLevel();
        org::eachSubnodeRec(node, register_used_links);
    }

    if (conf.TraceState) {
        conf.message(
            fmt("box:{} unresolved:{}", node, result.unresolved),
            conf.activeLevel);
    }

    return result;
}

Opt<MapLinkResolveResult> org::graph::getResolveTarget(
    const MapGraphState& s,
    MapNode const&       source,
    MapLink const&       link,
    MapConfig&           conf) {

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
    MapConfig&           conf) {
    MapNodeResolveResult result;
    result.node = node;
    result.node.unresolved.clear();

    LOGIC_ASSERTION_CHECK(
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
        LOGIC_ASSERTION_CHECK(
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

        LOGIC_ASSERTION_CHECK(
            count <= 1,
            "Resolved link target contains duplicate edges: {}-{}",
            r1.source,
            r1.target);
    }

    return result;
}

void org::graph::addNode(
    MapGraphState&         g,
    org::ImmAdapter const& node,
    MapConfig&             conf) {
    if (conf.TraceState) {
        conf.message(Str("- ").repeated(32), conf.activeLevel);
    }
    auto prop = conf.getUnresolvedNodeInsert(g, node);
    if (prop) {
        if (conf.TraceState) {
            conf.message("ID maps to graph node", conf.activeLevel);
        }
        auto __init = conf.scopeLevel();
        addNode(g, *prop, conf);
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


        for (auto const& [idx, unresolved] : enumerate(prop.unresolved)) {
            add_field(Record{{
                Record{left_aligned(fmt("Unresolved [{}]", idx), 16)},
                Record{fmt1(unresolved.link)},
            }});
        }

        node.finishRecord();
    }

    return res;
}

void org::graph::addNodeRec(
    MapGraphState&         g,
    org::ImmAdapter const& node,
    MapConfig&             conf) {
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
                    addNode(g, node, conf);
                }
                break;
            }
            case osk::Subtree: {
                {
                    auto __add = conf.scopeTrace(false);
                    addNode(g, node, conf);
                }
                for (auto const& it : node) { aux(it); }
                break;
            }
            default: {
            }
        }
    };

    aux(node);
}

MapConfig::MapConfig() {
    this->getUnresolvedNodeInsertImpl = getUnresolvedNodeInsertDefault;
}
