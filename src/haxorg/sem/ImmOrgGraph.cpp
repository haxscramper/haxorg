#include "ImmOrgGraph.hpp"
#include "haxorg/sem/ImmOrgEdit.hpp"
#include "haxorg/sem/SemBaseApi.hpp"
#include <boost/algorithm/string/replace.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <immer/set_transient.hpp>
#include <immer/vector_transient.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>

using namespace org::graph;
using osk = OrgSemKind;
using slk = sem::LinkTarget::Kind;

#define GRAPH_TRACE() conf.OperationsTracer::TraceState

#define GRAPH_MSG(...)                                                    \
    if (GRAPH_TRACE()) { conf.message(__VA_ARGS__); }

bool org::graph::isDescriptionItem(org::ImmAdapter const& node) {
    return node.as<org::ImmListItem>()->header->has_value();
}

bool org::graph::isLinkedDescriptionItemNode(org::ImmAdapter const& n) {
    return n.is(osk::ListItem)  //
        && isDescriptionItem(n) //
        && rs::any_of(
               n.pass(n.as<org::ImmListItem>()->header.get().value())
                   .subAs<org::ImmLink>(),
               [](org::ImmAdapterT<org::ImmLink> head) -> bool {
                   return !head->target.isRaw();
               });
}

bool org::graph::isLinkedDescriptionItem(org::ImmAdapter const& n) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        n.getParentChain(/*withSelf = */ false),
        [&](org::ImmAdapter parent) -> bool {
            return isLinkedDescriptionItemNode(parent);
        });
}

bool org::graph::isLinkedDescriptionList(org::ImmAdapter const& n) {
    return n.is(osk::List)
        && rs::any_of(n.sub(), [&](org::ImmAdapter arg) -> bool {
               return isLinkedDescriptionItem(arg);
           });
}

bool org::graph::isInSubtreeDescriptionList(org::ImmAdapter const& n) {
    return rs::any_of(n.getParentChain(), [](org::ImmAdapter tree) {
        return isAttachedDescriptionList(tree);
    });
}


bool org::graph::isAttachedDescriptionList(ImmAdapter const& n) {
    if (auto list = n.asOpt<org::ImmList>();
        list && list->isDescriptionList()) {
        auto attached = list->getListAttrs("attached");
        return attached.has(0) && attached.at(0).value == "subtree";
    } else {
        return false;
    }
}


bool org::graph::isMmapIgnored(org::ImmAdapter const& n) {
    return isInSubtreeDescriptionList(n)
        || (isLinkedDescriptionList(n) && isAttachedDescriptionList(n));
}

static const IntSet<slk> SkipLinks{
    slk::Raw,
    slk::Attachment,
};

bool org::graph::hasGraphAnnotations(const ImmAdapterT<ImmSubtree>& par) {
    return par->treeId->has_value()
        || !org::getSubtreeProperties<sem::NamedProperty::RadioId>(
                par.value())
                .empty();
}

bool org::graph::hasGraphAnnotations(
    const ImmAdapterT<ImmParagraph>& par) {
    for (auto const& node : par.sub(false)) {
        if (node.is(OrgSemKind::RadioTarget)) {
            return true;
        } else if (auto link = node.asOpt<org::ImmLink>();
                   link
                   && !SkipLinks.contains(
                       link.value()->target.getKind())) {
            return true;
        }
    }

    return false;
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
                    if (old.isLink() && op.link.isLink()) {
                        return old.getLink().link
                            == op.link.getLink().link;
                    } else if (old.isRadio() && op.link.isRadio()) {
                        return old.getRadio().target
                            == op.link.getRadio().target;
                    } else {
                        return false;
                    }
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
    GRAPH_MSG(
        fmt("New node {}, resolution result {}", newNode, resolved_node));

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

        GRAPH_MSG(fmt("Adding {} as unresolved", newNode));

        state.unresolved.insert(newNode);
    }

    for (auto const& op : resolved_node.resolved) {
        Vec<MapNode> toRemove;
        for (MapNode const& it : state.unresolved) {
            if (props.at(it).unresolved.empty()) {
                GRAPH_MSG(
                    fmt("Node {} fixed all unresolved properties", it));
                toRemove.push_back(it);
            }
        }

        for (auto const& it : toRemove) { state.unresolved.erase(it); }
    }
}

void updateResolvedEdges(
    MapGraphState&              s,
    MapNodeResolveResult const& resolved_node,
    MapConfig&                  conf) {
    for (auto const& op : resolved_node.resolved) {
        for (auto const& target : s.graph.adjList.at(op.source)) {
            LOGIC_ASSERTION_CHECK(
                op.target != target,
                "There is already a link between {} and {}, graph cannot "
                "contain duplicate edges op:{}",
                op.source,
                op.target,
                op);
        }


        GRAPH_MSG(fmt("add edge {}-{}", op.source, op.target));
        s.graph.addEdge(
            MapEdge{op.source, op.target}, MapEdgeProp{.link = op.link});
    }
}

void traceNodeResolve(
    MapGraphState const&        outputState,
    MapNodeResolveResult const& resolved_node,
    MapConfig&                  conf,
    MapNode const&              mapNode) {
    if (GRAPH_TRACE()) {
        auto __scope = conf.scopeLevel();
        GRAPH_MSG(
            fmt("v:{} original unresolved state:{} resolved:{} still "
                "unresolved:{}",
                mapNode,
                outputState.unresolved,
                resolved_node.node.unresolved,
                resolved_node.resolved));

        if (outputState.graph.nodeProps.find(mapNode) != nullptr) {
            for (auto const& u :
                 outputState.graph.at(mapNode).unresolved) {
                GRAPH_MSG(fmt(">> g[v] unresolved {}", u));
            }
        } else {
            GRAPH_MSG(fmt(">> new node, no preexisting unresolved"));
        }

        for (auto const& u : resolved_node.node.unresolved) {
            GRAPH_MSG(fmt("<<- updated unresolved {}", u));
        }
        for (auto const& u : resolved_node.resolved) {
            GRAPH_MSG(
                fmt("<<+ updated resolved {} {}->{}",
                    u.link,
                    u.source,
                    u.target));
        }
    }
}

void org::graph::registerNode(
    MapGraphState&     s,
    MapNodeProp const& node,
    MapConfig&         conf) {

    auto&   graph = s.graph;
    MapNode mapNode{node.id.uniq()};

    s.graph.addNode(node.id.uniq());

    GRAPH_MSG(fmt("unresolved:{}", s.unresolved));


    MapNodeResolveResult resolved = getResolvedNodeInsert(s, node, conf);

    // debug-print node resolution state
    traceNodeResolve(s, resolved, conf, mapNode);

    // Assign node resolution result to node properties, all links have
    // been finalized.
    graph.nodeProps.insert_or_assign(mapNode, resolved.node);

    // Iterate over all known unresolved nodes and adjust node property
    // values in the graph to account for new property changes.
    removeUnresolvedNodeProps(
        graph.nodeProps, resolved, mapNode, s.unresolved, conf);

    // Collect new list of unresolved nodes for the changes.
    updateUnresolvedNodeTracking(
        s, graph.nodeProps, resolved, mapNode, conf);

    // Add all resolved edges to the graph
    updateResolvedEdges(s, resolved, conf);
}


static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};


Opt<MapLink> org::graph::getUnresolvedLink(
    const MapGraphState& s,
    ImmAdapterT<ImmLink> link,
    MapConfig&           conf) {
    if (SkipLinks.contains(link->target.getKind())) {
        return std::nullopt;
    } else {
        return MapLink{MapLink::Link{
            .link = link,
            .description //
            = link->description.get()
                ? Vec{link.at(
                      link->description.get().value().toId(),
                      ImmPathStep::FieldDeref(
                          org::ImmReflFieldId::FromTypeField(
                              &org::ImmLink::description)))}
                : Vec<org::ImmAdapter>{},
        }};
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
        if (auto attached = list.getListAttrs("attached");
            attached.has(0) && attached.at(0).value == "subtree") {
            GRAPH_MSG("Subtree has list");
            for (auto const& item : list.subAs<org::ImmListItem>()) {
                GRAPH_MSG(fmt("{}", item.id));
                if (isLinkedDescriptionItemNode(item)) {
                    GRAPH_MSG("List has description item");
                    for (auto const& link :
                         item.pass(item->header->value())
                             .subAs<org::ImmLink>()) {
                        GRAPH_MSG(fmt("List item contains link {}", link));
                        // Description list header might contain
                        // non-link elements. These are ignored in the
                        // mind map.
                        if (!SkipLinks.contains(link->target.getKind())) {
                            MapLink::Link map_link{.link = link};
                            for (auto const& sub : item.sub()) {
                                map_link.description.push_back(sub);
                            }
                            unresolved.push_back(MapLink{map_link});
                        }
                    }
                }
            }
        }
    }

    return unresolved;
}


Opt<MapNodeProp> org::graph::MapInterface::getInitialNodeProp(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapConfig&           conf) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    if (isMmapIgnored(node)) {
        GRAPH_MSG(fmt("Node {} is ignored for mmap", node));
        return std::nullopt;
    }

    GRAPH_MSG(
        fmt("box:{} desc-item:{} desc-list:{}",
            node,
            isLinkedDescriptionItem(node),
            isLinkedDescriptionList(node)));


    MapNodeProp result{.id = node};

    auto register_used_links = [&](org::ImmAdapter arg) {
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (auto link = arg.asOpt<org::ImmLink>()) {
            if (auto target = getUnresolvedLink(s, link.value(), conf)) {
                GRAPH_MSG(
                    fmt("Got unresolved link for adapter {} under {}",
                        arg,
                        node))
                result.unresolved.push_back(target.value());
            }
        }
    };

    if (auto tree = node.asOpt<org::ImmSubtree>()) {
        result.unresolved.append(
            getUnresolvedSubtreeLinks(s, tree.value(), conf));
    } else if (auto par = node.asOpt<org::ImmParagraph>();
               par && par->isFootnoteDefinition()) {
        auto sub = par->sub();
        for (auto const& it : enumerator(sub)) {
            if (!it.is_first()) {
                org::eachSubnodeRec(it.value(), true, register_used_links);
            }
        }
    } else if (!NestedNodes.contains(node->getKind())) {
        GRAPH_MSG("registering nested outgoing links");
        auto __tmp = conf.scopeLevel();
        org::eachSubnodeRec(node, true, register_used_links);
    }


    GRAPH_MSG(fmt("box:{} unresolved:{}", node, result.unresolved));


    return result;
}

Vec<MapLinkResolveResult> org::graph::getResolveTarget(
    const MapGraphState& s,
    MapNode const&       source,
    MapLink const&       link,
    MapConfig&           conf) {

    GRAPH_MSG(fmt("Get resolve targets {} {}", source, link));


    Vec<MapLinkResolveResult> result;

    if (link.isRadio()) {
        // Unresolved radio link already contains all the information for
        // creating edge. This only happens when the node itself has not
        // been added to the graph.
        result.push_back(MapLinkResolveResult{
            .link   = link,
            .target = MapNode{link.getRadio().target.uniq()},
            .source = source,
        });
    } else {
        GRAPH_MSG(fmt("footnotes {}", s.ast->currentTrack->footnotes));
        GRAPH_MSG(fmt("subtrees {}", s.ast->currentTrack->subtrees));
        GRAPH_MSG(fmt("names {}", s.ast->currentTrack->names));

        auto add_edge = [&](org::ImmId const& target) {
            auto adapters = s.ast->getAdaptersFor(target);
            LOGIC_ASSERTION_CHECK(
                !adapters.empty(),
                "Target node {} does not have any parent adapters tracked",
                target);

            for (auto const& full : adapters) {
                result.push_back(MapLinkResolveResult{
                    .link   = link,
                    .target = MapNode{full.uniq()},
                    .source = source,
                });
            }
        };

        CR<MapLink::Link> spec = link.getLink();
        switch (spec.link->target.getKind()) {
            case slk::Id: {
                auto text = spec.link->target.getId().text;
                if (auto target = s.ast->currentTrack->subtrees.get(
                        text)) {
                    GRAPH_MSG(
                        fmt("Subtree ID {} on {} resolved to {}",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    GRAPH_MSG(fmt("Not subtree with ID {}", text));
                }
                break;
            }

            case slk::Footnote: {
                CR<Str> text = spec.link->target.getFootnote().target;
                if (auto target = s.ast->currentTrack->footnotes.get(
                        text)) {
                    GRAPH_MSG(
                        fmt("Footnote name {} on {} resolved to {}",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    GRAPH_MSG(fmt("No footnote with ID {}", text));
                }
                break;
            }

            case slk::Internal: {
                CR<Str> text = spec.link->target.getInternal().target;
                if (auto target = s.ast->currentTrack->names.get(text)) {
                    GRAPH_MSG(
                        fmt("Internal link name '{}' on '{}' resolved to "
                            "named "
                            "node '{}'",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    GRAPH_MSG(fmt("No internal link with ID '{}'", text));
                }
                break;
            }

            case slk::File:
            case slk::Attachment:
            case slk::UserProtocol: {
                break;
            }

            default: {
                throw logic_unreachable_error::init(
                    fmt("Unhandled link kind '{}'",
                        spec.link->target.getKind()));
            }
        }
    }


    return result;
}


MapNodeResolveResult org::graph::getResolvedNodeInsert(
    const MapGraphState& s,
    const MapNodeProp&   node,
    MapConfig&           conf) {
    MapNodeResolveResult result;
    auto                 __scope = conf.scopeLevel();
    result.node                  = node;
    result.node.unresolved.clear();
    GRAPH_MSG(fmt("Get unresolved for node {}", node.id));

    auto ctx = node.id.ctx.lock();

    LOGIC_ASSERTION_CHECK(
        s.unresolved.find(MapNode{node.id.uniq()}) == nullptr,
        "Node {} is already marked as unresolved in the graph",
        node.id);

    {
        auto __scope = conf.scopeLevel();
        GRAPH_MSG(fmt("Collecting radio targets in graph"));

        auto found_radio_target_node = [&](CR<org::ImmAdapter> radio) {
            if (s.graph.isRegisteredNode(radio.uniq())) {
                GRAPH_MSG(
                    fmt("Detected radio target from node {} "
                        "to target {}, which is a resolved "
                        "graph node. ",
                        node.id,
                        radio));
                result.resolved.push_back(MapLinkResolveResult{
                    .source = MapNode{node.id.uniq()},
                    .target = MapNode{radio.uniq()},
                });
            } else {
                GRAPH_MSG(
                    fmt("Radio target {} from node {} is not "
                        "a resolved graph node.",
                        radio,
                        node.id));
                result.node.unresolved.push_back(
                    MapLink{MapLink::Radio{.target = radio}});
            }
        };

        if (auto par = node.id.asOpt<org::ImmParagraph>()) {
            for (auto const& group : getSubnodeGroups(node.id)) {
                GRAPH_MSG(fmt("Group {}", group));
                if (group.isRadioTarget()) {
                    auto groupTarget = group.getRadioTarget().target;
                    if (groupTarget.is(OrgSemKind::Subtree)) {
                        for (auto const& subtree :
                             ctx->getPathsFor(groupTarget)) {
                            found_radio_target_node(ctx->adapt(subtree));
                        }
                    } else if (groupTarget.is(OrgSemKind::RadioTarget)) {
                        for (org::ImmAdapter const& radio :
                             ctx->getParentPathsFor(groupTarget)) {
                            found_radio_target_node(radio);
                        }
                    } else {
                        LOGIC_ASSERTION_CHECK(
                            false,
                            "Unexpected subnode group target kind {}",
                            groupTarget.getKind())
                    }
                }
            }
        }
    }


    {
        auto __scope = conf.scopeLevel();
        for (auto const& unresolvedLink : node.unresolved) {
            Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                s, MapNode{node.id.uniq()}, unresolvedLink, conf);
            if (resolved_edit.empty()) {
                GRAPH_MSG(
                    fmt("No resolved links from {}", unresolvedLink));
                result.node.unresolved.push_back(unresolvedLink);
            } else {
                for (auto const& resolved : resolved_edit) {
                    if (s.graph.isRegisteredNode(resolved.target)) {
                        GRAPH_MSG(
                            fmt("resolved to known node:{}", resolved));
                        result.resolved.push_back(resolved);
                    } else {
                        GRAPH_MSG(fmt(
                            "resolved to unregistered node:{}", resolved));
                        result.node.unresolved.push_back(unresolvedLink);
                    }
                }
            }
        }
    }

    GRAPH_MSG(fmt("Process unresolved for state"));
    {
        auto __scope = conf.scopeLevel();
        for (MapNode const& nodeWithUnresolved : s.unresolved) {
            LOGIC_ASSERTION_CHECK(
                nodeWithUnresolved.id != node.id.uniq(),
                "cannot resolve already inserted node {} == {} ({}) is "
                "recorded in s.unresolved",
                nodeWithUnresolved.id,
                node.id.id,
                nodeWithUnresolved.id != node.id.uniq());

            for (auto const& link :
                 s.graph.at(nodeWithUnresolved).unresolved) {
                Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                    s, nodeWithUnresolved, link, conf);
                if (resolved_edit.empty()) {
                    GRAPH_MSG(fmt(
                        "No resolve target for {}", nodeWithUnresolved));
                } else {
                    for (auto const& resolved : resolved_edit) {
                        if (s.graph.isRegisteredNode(resolved.target)) {
                            GRAPH_MSG(
                                fmt("resolved to registered node:{} it:{} "
                                    "edit:{}",
                                    resolved,
                                    nodeWithUnresolved,
                                    node));
                            result.resolved.push_back(resolved);
                        }
                    }
                }
            }
        }
    }

    GRAPH_MSG(
        fmt("box:{} resolved:{} unresolved:{}",
            node,
            result.resolved,
            result.node.unresolved));

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
    GRAPH_MSG(fmt("{} {}", node, Str("- ").repeated(32)));
    auto prop = conf.getInitialNodeProp(g, node);
    if (prop) {
        GRAPH_MSG("ID maps to graph node");
        auto __init = conf.scopeLevel();
        registerNode(g, *prop, conf);
    } else {
        GRAPH_MSG(fmt("No initial properties for {}, skipping", node.id));
    }
}

void MapGraph::addEdge(const MapEdge& edge, const MapEdgeProp& prop) {
    LOGIC_ASSERTION_CHECK(
        adjList.contains(edge.target),
        "Edge target {} is missing from the graph definition (source {})",
        edge.target,
        edge.source);

    LOGIC_ASSERTION_CHECK(
        adjList.contains(edge.source),
        "Edge source {} is missing from the graph definition (target {})",
        edge.source,
        edge.target);

    adjList.at(edge.source).push_back(edge.target);
    adjListIn.at(edge.target).push_back(edge.source);
    edgeProps.insert_or_assign(edge, prop);
}

void MapGraph::addNode(const MapNode& node) {
    if (!adjList.contains(MapNode{node})) {
        adjList.insert_or_assign(MapNode{node}, Vec<MapNode>{});
        nodeProps.insert_or_assign(MapNode{node}, MapNodeProp{});
        adjListIn.insert_or_assign(MapNode{node}, Vec<MapNode>{});
    }
}


Graphviz::Graph MapGraph::toGraphviz(
    org::ImmAstContext::Ptr const& ctx,
    GvConfig const&                conf) const {
    Graphviz::Graph                       res{"g"_ss};
    UnorderedMap<MapNode, Graphviz::Node> gvNodes;
    UnorderedMap<MapEdge, Graphviz::Edge> gvEdges;

    auto edgeOk = [&](MapEdge const& edge) {
        return !conf.acceptEdge || conf.acceptEdge(edge);
    };

    auto nodeOk = [&](MapNode const& node) {
        return !conf.acceptNode || conf.acceptNode(node);
    };

    for (auto const& [it, props] : nodeProps) {
        if (nodeOk(it)) {
            auto node = res.node(it.id.id.getReadableId());
            node.setAttr("org_id", it.id.id.getReadableId());
            gvNodes.insert_or_assign(it, node);
        }
    }

    for (auto const& [source, targets] : adjList) {
        for (auto const& target : targets) {
            if (nodeOk(source) && nodeOk(target)
                && edgeOk({source, target})) {
                gvEdges.insert_or_assign(
                    {source, target},
                    res.edge(gvNodes.at(source), gvNodes.at(target)));
            }
        }
    }

    for (auto const& [it, prop] : nodeProps) {
        if (!nodeOk(it)) { continue; }
        using Record = Graphviz::Node::Record;
        auto& node   = gvNodes.at(it);
        node.startHtmlRecord();
        *node.getNodeRecord() = conf.getNodeLabel(ctx->adapt(it.id), prop);

        node.finishHtmlRecord();
    }

    return res;
}


MapConfig::MapConfig(SPtr<MapInterface> impl) : impl{impl} {
    this->OperationsScope::TraceState //
        = &this->OperationsTracer::TraceState;
}

MapConfig::MapConfig() : impl{std::make_shared<MapInterface>()} {
    this->OperationsScope::TraceState //
        = &this->OperationsTracer::TraceState;
}

Graphviz::Node::Record MapGraph::GvConfig::getDefaultNodeLabel(
    const ImmAdapter&  node,
    const MapNodeProp& prop) {
    using Record = Graphviz::Node::Record;
    Record rec;
    rec.setEscaped("ID", fmt1(node.id));

    auto add_field_text = [&](Str const& name, org::ImmId id) {
        rec.set(
            name,
            Record{Graphviz::escapeHtmlForGraphviz(
                wrap_text(flatWords(node), 60, true))});
    };

    rec.setEscaped("Select", node.selfSelect());

    switch_node_value(
        node.id,
        node.ctx.lock(),
        overloaded{
            [&](org::ImmSubtree const& tree) {
                rec.setEscaped(
                    "Title",
                    join(
                        " ",
                        flatWords(
                            node.ctx.lock()->adaptUnrooted(tree.title))));
            },
            [&](org::ImmParagraph const& tree) {
                add_field_text("Text", node.id);
            },
            [&]<typename K>(K const& value) {
                rec.setEscaped("Type", TypeName<K>::get());
            },
        });

    auto file = node.getFirstMatchingParent(
        [](org::ImmAdapter const& a) { return a.is(OrgSemKind::File); });

    if (node->loc || file) {
        rec.setEscaped(
            "Loc",
            fmt("{}:{}:{} @ {}",
                node->loc->column,
                node->loc->line,
                node->loc->pos,
                file ? file->as<org::ImmFile>()->relPath.get()
                     : Str{"?"}));
    }

    for (auto const& [idx, unresolved] : enumerate(prop.unresolved)) {
        if (unresolved.isLink()) {
            rec.setEscaped(
                fmt("Unresolved link [{}]", unresolved.getLink().link.id),
                to_json_eval(unresolved.getLink().link.value()).dump(2));
        } else {
            rec.setEscaped(
                fmt("Unresolved radio [{}]",
                    unresolved.getRadio().target.id),
                "radio target");
        }
    }

    return rec;
}

void org::graph::addNodeRec(
    MapGraphState&    g,
    const ImmAdapter& node,
    MapConfig&        conf) {
    Func<void(org::ImmAdapter const&)> aux;
    aux = [&](org::ImmAdapter const& node) {
        conf.message(fmt("recursive add {}", node), "addNodeRec");
        auto __tmp = conf.scopeLevel();
        switch (node->getKind()) {
            case OrgSemKind::CmdInclude:
            case OrgSemKind::File:
            case OrgSemKind::Directory:
            case OrgSemKind::Symlink:
            case OrgSemKind::Document:
            case OrgSemKind::ListItem:
            case OrgSemKind::List: {
                for (auto const& it : node) { aux(it); }
                break;
            }
            case OrgSemKind::Paragraph: {
                auto par = node.as<org::ImmParagraph>();
                // conf.message(
                //     fmt("rec visit of {}\n{}",
                //         par,
                //         par.treeRepr().toString()));
                if (org::graph::hasGraphAnnotations(par)) {
                    addNode(g, node, conf);
                } else {
                    auto group = org::getSubnodeGroups(node, false);
                    if (rs::any_of(group, [](auto const& it) {
                            return it.isRadioTarget();
                        })) {
                        // conf.message(fmt("Paragraph has radio target"));
                        addNode(g, node, conf);
                    }
                }
                break;
            }
            case OrgSemKind::Subtree: {
                if (auto tree = node.as<org::ImmSubtree>();
                    org::graph::hasGraphAnnotations(tree)) {
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
