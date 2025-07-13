#include "ImmOrgGraph.hpp"
#include "haxorg/sem/ImmOrgEdit.hpp"
#include "haxorg/sem/SemBaseApi.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <immer/set_transient.hpp>
#include <immer/vector_transient.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/sem/perfetto_org.hpp>

using namespace org::graph;
using namespace hstd;
using namespace org::imm;
using namespace hstd::ext;
using osk = OrgSemKind;
using slk = org::sem::LinkTarget::Kind;

#define GRAPH_TRACE() conf->dbg.TraceState

#define GRAPH_MSG(...)                                                    \
    if (GRAPH_TRACE()) { conf->dbg.message(__VA_ARGS__); }

bool org::graph::isDescriptionItem(ImmAdapter const& node) {
    return node.as<ImmListItem>()->header->has_value();
}

bool org::graph::isLinkedDescriptionItemNode(ImmAdapter const& n) {
    return n.is(osk::ListItem)  //
        && isDescriptionItem(n) //
        && rs::any_of(
               n.pass(n.as<ImmListItem>()->header.get().value())
                   .subAs<ImmLink>(),
               [](ImmAdapterT<ImmLink> head) -> bool {
                   return !head->target.isRaw();
               });
}

bool org::graph::isLinkedDescriptionItem(ImmAdapter const& n) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        n.getParentChain(/*withSelf = */ false),
        [&](ImmAdapter parent) -> bool {
            return isLinkedDescriptionItemNode(parent);
        });
}

bool org::graph::isLinkedDescriptionList(ImmAdapter const& n) {
    return n.is(osk::List)
        && rs::any_of(n.sub(), [&](ImmAdapter arg) -> bool {
               return isLinkedDescriptionItem(arg);
           });
}

bool org::graph::isInSubtreeDescriptionList(ImmAdapter const& n) {
    return rs::any_of(n.getParentChain(), [](ImmAdapter tree) {
        return isAttachedDescriptionList(tree);
    });
}


bool org::graph::isAttachedDescriptionList(ImmAdapter const& n) {
    if (auto list = n.asOpt<ImmList>();
        list && list->isDescriptionList()) {
        auto attached = list->getListAttrs("attached");
        return attached.has(0) && attached.at(0).getString() == "subtree";
    } else {
        return false;
    }
}


bool org::graph::isMmapIgnored(ImmAdapter const& n) {
    return isInSubtreeDescriptionList(n)
        || (isLinkedDescriptionList(n) && isAttachedDescriptionList(n));
}

static const IntSet<slk> SkipLinks{
    slk::Raw,
    slk::Attachment,
};

bool org::graph::hasGraphAnnotations(const ImmAdapterT<ImmSubtree>& par) {
    return par->treeId->has_value()
        || !getSubtreeProperties<sem::NamedProperty::RadioId>(par.value())
                .empty();
}

bool org::graph::hasGraphAnnotations(
    const ImmAdapterT<ImmParagraph>& par) {
    for (auto const& node : par.sub(false)) {
        if (node.is(OrgSemKind::RadioTarget)) {
            return true;
        } else if (auto link = node.asOpt<ImmLink>();
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
    std::shared_ptr<MapConfig>   conf) {
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
    MapGraphState::Ptr const&   state,
    NodeProps&                  props,
    MapNodeResolveResult const& resolved_node,
    MapNode const&              newNode,
    std::shared_ptr<MapConfig>  conf) {
    GRAPH_MSG(
        fmt("New node {}, resolution result {}", newNode, resolved_node));

    if (resolved_node.node.unresolved.empty()) {
        // Newly added node has no unresolved elements, remove the ID from
        // map state tracking.
        if (state->unresolved.contains(newNode)) {
            state->unresolved.erase(newNode);
        }
    } else {
        LOGIC_ASSERTION_CHECK(
            !state->unresolved.contains(newNode),
            "Duplicate unresolved boxes are not expected: {}",
            newNode);

        GRAPH_MSG(fmt("Adding {} as unresolved", newNode));

        state->unresolved.insert(newNode);
    }

    for (auto const& op : resolved_node.resolved) {
        Vec<MapNode> toRemove;
        for (MapNode const& it : state->unresolved) {
            if (props.at(it).unresolved.empty()) {
                GRAPH_MSG(
                    fmt("Node {} fixed all unresolved properties", it));
                toRemove.push_back(it);
            }
        }

        for (auto const& it : toRemove) { state->unresolved.erase(it); }
    }
}

void updateResolvedEdges(
    MapGraphState::Ptr const&   s,
    MapNodeResolveResult const& resolved_node,
    std::shared_ptr<MapConfig>  conf) {
    for (auto const& op : resolved_node.resolved) {
        for (auto const& target : s->graph->adjList.at(op.source)) {
            LOGIC_ASSERTION_CHECK(
                op.target != target,
                "There is already a link between {} and {}, graph cannot "
                "contain duplicate edges op:{}",
                op.source,
                op.target,
                op);
        }


        GRAPH_MSG(fmt("add edge {}-{}", op.source, op.target));
        s->graph->addEdge(
            MapEdge{op.source, op.target}, MapEdgeProp{.link = op.link});
    }
}

void traceNodeResolve(
    MapGraphState::Ptr const&   outputState,
    MapNodeResolveResult const& resolved_node,
    std::shared_ptr<MapConfig>  conf,
    MapNode const&              mapNode) {
    if (GRAPH_TRACE()) {
        auto __scope = conf->dbg.scopeLevel();
        GRAPH_MSG(
            fmt("v:{} original unresolved state:{} resolved:{} still "
                "unresolved:{}",
                mapNode,
                outputState->unresolved,
                resolved_node.node.unresolved,
                resolved_node.resolved));

        if (outputState->graph->nodeProps.find(mapNode)
            != outputState->graph->nodeProps.end()) {
            for (auto const& u :
                 outputState->graph->at(mapNode).unresolved) {
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

void org::graph::MapGraphState::registerNode(
    MapNodeProp const&                node,
    std::shared_ptr<MapConfig> const& conf) {

    MapNode mapNode{node.id};

    graph->addNode(node.id);

    GRAPH_MSG(fmt("unresolved:{}", unresolved));


    MapNodeResolveResult resolved = getResolvedNodeInsert(
        shared_from_this(), node, conf);

    // debug-print node resolution state
    traceNodeResolve(shared_from_this(), resolved, conf, mapNode);

    // Assign node resolution result to node properties, all links have
    // been finalized.
    graph->nodeProps.insert_or_assign(mapNode, resolved.node);

    // Iterate over all known unresolved nodes and adjust node property
    // values in the graph to account for new property changes.
    removeUnresolvedNodeProps(
        graph->nodeProps, resolved, mapNode, unresolved, conf);

    // Collect new list of unresolved nodes for the changes.
    updateUnresolvedNodeTracking(
        shared_from_this(), graph->nodeProps, resolved, mapNode, conf);

    // Add all resolved edges to the graph
    updateResolvedEdges(shared_from_this(), resolved, conf);
}


static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};


Opt<MapLink> org::graph::MapGraphState::getUnresolvedLink(
    ImmAdapterT<ImmLink>              link,
    std::shared_ptr<MapConfig> const& conf) const {
    if (SkipLinks.contains(link->target.getKind())) {
        return std::nullopt;
    } else {
        return MapLink{MapLink::Link{
            .link = link.uniq(),
            .description //
            = link->description.get()
                ? Vec{link.at(link->description.get().value().toId(),
                              ImmPathStep::FieldDeref(
                                  ImmReflFieldId::FromTypeField(
                                      &ImmLink::description)))
                          .uniq()}
                : Vec<ImmUniqId>{},
        }};
    }
}


Vec<MapLink> org::graph::MapGraphState::getUnresolvedSubtreeLinks(
    ImmAdapterT<ImmSubtree>           tree,
    std::shared_ptr<MapConfig> const& conf) const {
    Vec<MapLink> unresolved;
    // Description lists with links in header are attached as the
    // outgoing link to the parent subtree. It is the only supported
    // way to provide an extensive label between subtree nodes.
    for (auto const& list : tree.subAs<ImmList>()) {
        if (auto attached = list.getListAttrs("attached");
            attached.has(0) && attached.at(0).getString() == "subtree") {
            GRAPH_MSG("Subtree has list");
            for (auto const& item : list.subAs<ImmListItem>()) {
                GRAPH_MSG(fmt("{}", item.id));
                if (isLinkedDescriptionItemNode(item)) {
                    GRAPH_MSG("List has description item");
                    for (auto const& link :
                         item.pass(item->header->value())
                             .subAs<ImmLink>()) {
                        GRAPH_MSG(fmt("List item contains link {}", link));
                        // Description list header might contain
                        // non-link elements. These are ignored in the
                        // mind map.
                        if (!SkipLinks.contains(link->target.getKind())) {
                            MapLink::Link map_link{.link = link.uniq()};
                            for (auto const& sub : item.sub()) {
                                map_link.description.push_back(sub.uniq());
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
    MapGraphState::Ptr const&  s,
    ImmAdapter                 node,
    std::shared_ptr<MapConfig> conf) {
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


    MapNodeProp result{.id = node.uniq()};

    auto register_used_links = [&](ImmAdapter arg) {
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (auto link = arg.asOpt<ImmLink>()) {
            if (auto target = s->getUnresolvedLink(link.value(), conf)) {
                GRAPH_MSG(
                    fmt("Got unresolved link for adapter {} under {}",
                        arg,
                        node))
                result.unresolved.push_back(target.value());
            }
        }
    };

    if (auto tree = node.asOpt<ImmSubtree>()) {
        result.unresolved.append(
            s->getUnresolvedSubtreeLinks(tree.value(), conf));
    } else if (auto par = node.asOpt<ImmParagraph>();
               par && par->isFootnoteDefinition()) {
        auto sub = par->sub();
        for (auto const& it : enumerator(sub)) {
            if (!it.is_first()) {
                eachSubnodeRec(it.value(), true, register_used_links);
            }
        }
    } else if (!NestedNodes.contains(node->getKind())) {
        GRAPH_MSG("registering nested outgoing links");
        auto __tmp = conf->dbg.scopeLevel();
        org::eachSubnodeRec(node, true, register_used_links);
    }


    GRAPH_MSG(fmt("box:{} unresolved:{}", node, result.unresolved));


    return result;
}

Vec<MapLinkResolveResult> org::graph::getResolveTarget(
    MapGraphState::Ptr const&  s,
    MapNode const&             source,
    MapLink const&             link,
    std::shared_ptr<MapConfig> conf) {

    GRAPH_MSG(fmt("Get resolve targets {} {}", source, link));


    Vec<MapLinkResolveResult> result;

    if (link.isRadio()) {
        // Unresolved radio link already contains all the information for
        // creating edge. This only happens when the node itself has not
        // been added to the graph.
        result.push_back(MapLinkResolveResult{
            .link   = link,
            .target = MapNode{link.getRadio().target},
            .source = source,
        });
    } else {
        GRAPH_MSG(fmt("footnotes {}", s->ast->currentTrack->footnotes));
        GRAPH_MSG(fmt("subtrees {}", s->ast->currentTrack->subtrees));
        GRAPH_MSG(fmt("names {}", s->ast->currentTrack->names));

        auto add_edge = [&](imm::ImmId const& target) {
            auto adapters = s->ast->getAdaptersFor(target);
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
        auto link_adapter      = s->ast->adapt(spec.link).as<ImmLink>();
        switch (link_adapter->target.getKind()) {
            case slk::Id: {
                auto text = link_adapter->target.getId().text;
                if (auto target = s->ast->currentTrack->subtrees.get(
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

            case slk::CustomId: {
                auto text = link_adapter->target.getCustomId().text;
                if (auto target = s->ast->currentTrack->customIds.get(
                        text)) {
                    GRAPH_MSG(
                        fmt("Subtree custom ID {} on {} resolved to {}",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    GRAPH_MSG(fmt("Not subtree with custom ID {}", text));
                }
                break;
            }

            case slk::Footnote: {
                CR<Str> text = link_adapter->target.getFootnote().target;
                if (auto target = s->ast->currentTrack->footnotes.get(
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
                CR<Str> text = link_adapter->target.getInternal().target;
                if (auto target = s->ast->currentTrack->names.get(text)) {
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
            case slk::Person:
            case slk::SubtreeTitle:
            case slk::UserProtocol: {
                break;
            }

            default: {
                throw logic_unreachable_error::init(
                    fmt("Unhandled link kind '{}'",
                        link_adapter->target.getKind()));
            }
        }
    }


    return result;
}


MapNodeResolveResult org::graph::getResolvedNodeInsert(
    const MapGraphState::Ptr&  s,
    const MapNodeProp&         node,
    std::shared_ptr<MapConfig> conf) {
    MapNodeResolveResult result;
    auto                 __scope = conf->dbg.scopeLevel();
    result.node                  = node;
    result.node.unresolved.clear();
    GRAPH_MSG(fmt("Get unresolved for node {}", node.id));

    LOGIC_ASSERTION_CHECK(
        s->unresolved.find(MapNode{node.id}) == s->unresolved.end(),
        "Node {} is already marked as unresolved in the graph",
        node.id);

    {
        auto __scope = conf->dbg.scopeLevel();
        GRAPH_MSG(fmt("Collecting radio targets in graph"));

        auto found_radio_target_node = [&](CR<ImmAdapter> radio) {
            if (s->graph->isRegisteredNode(radio.uniq())) {
                GRAPH_MSG(
                    fmt("Detected radio target from node {} "
                        "to target {}, which is a resolved "
                        "graph node. ",
                        node.id,
                        radio));
                result.resolved.push_back(MapLinkResolveResult{
                    .source = MapNode{node.id},
                    .target = MapNode{radio.uniq()},
                });
            } else {
                GRAPH_MSG(
                    fmt("Radio target {} from node {} is not "
                        "a resolved graph node.",
                        radio,
                        node.id));
                result.node.unresolved.push_back(
                    MapLink{MapLink::Radio{.target = radio.uniq()}});
            }
        };

        if (auto par = node.getAdapter(s->ast)
                           .asOpt<imm::ImmParagraph>()) {
            for (auto const& group :
                 getSubnodeGroups(s->ast, node.getAdapter(s->ast))) {
                GRAPH_MSG(fmt("Group {}", group));
                if (group.isRadioTarget()) {
                    GRAPH_MSG(fmt("Got radio target group"));
                    auto groupTarget = group.getRadioTarget().target;
                    if (groupTarget.is(OrgSemKind::Subtree)) {
                        for (auto const& subtree :
                             s->ast->getPathsFor(groupTarget)) {
                            found_radio_target_node(
                                s->ast->adapt(subtree));
                        }
                    } else if (groupTarget.is(OrgSemKind::RadioTarget)) {
                        for (ImmAdapter const& radio :
                             s->ast->getParentPathsFor(groupTarget)) {
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
        auto __scope = conf->dbg.scopeLevel();
        for (auto const& unresolvedLink : node.unresolved) {
            Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                s, MapNode{node.id}, unresolvedLink, conf);
            if (resolved_edit.empty()) {
                GRAPH_MSG(
                    fmt("No resolved links from {}", unresolvedLink));
                result.node.unresolved.push_back(unresolvedLink);
            } else {
                for (auto const& resolved : resolved_edit) {
                    if (s->graph->isRegisteredNode(resolved.target)) {
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
        auto __scope = conf->dbg.scopeLevel();
        for (MapNode const& nodeWithUnresolved : s->unresolved) {
            LOGIC_ASSERTION_CHECK(
                nodeWithUnresolved.id != node.id,
                "cannot resolve already inserted node {} == {} ({}) is "
                "recorded in s.unresolved",
                nodeWithUnresolved.id,
                node.id.id,
                nodeWithUnresolved.id != node.id);

            for (auto const& link :
                 s->graph->at(nodeWithUnresolved).unresolved) {
                Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                    s, nodeWithUnresolved, link, conf);
                if (resolved_edit.empty()) {
                    GRAPH_MSG(fmt(
                        "No resolve target for {}", nodeWithUnresolved));
                } else {
                    for (auto const& resolved : resolved_edit) {
                        if (s->graph->isRegisteredNode(resolved.target)) {
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

    if (false) {
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
    } else {
        hstd::Vec<MapLinkResolveResult>       unique_resolved;
        std::set<std::pair<MapNode, MapNode>> seen;

        for (const auto& r : result.resolved) {
            auto pair = std::make_pair(r.target, r.source);
            if (seen.find(pair) == seen.end()) {
                seen.insert(pair);
                unique_resolved.push_back(r);
            }
        }
        result.resolved = std::move(unique_resolved);
    }

    return result;
}

void org::graph::MapGraphState::addNode(
    ImmAdapter const&                 node,
    std::shared_ptr<MapConfig> const& conf) {
    GRAPH_MSG(fmt("{} {}", node, Str("- ").repeated(32)));
    auto prop = conf->getInitialNodeProp(shared_from_this(), node);
    if (prop) {
        GRAPH_MSG("ID maps to graph node");
        auto __init = conf->dbg.scopeLevel();
        registerNode(*prop, conf);
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


#if !ORG_EMCC_BUILD
Graphviz::Graph MapGraph::toGraphviz(
    imm::ImmAstContext::Ptr const& ctx,
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
#endif

MapConfig::MapConfig(SPtr<MapInterface> impl) : impl{impl} {}

MapConfig::MapConfig() : impl{std::make_shared<MapInterface>()} {}

#if !ORG_EMCC_BUILD
Graphviz::Node::Record MapGraph::GvConfig::getDefaultNodeLabel(
    const ImmAdapter&  node,
    const MapNodeProp& prop) {
    using Record = Graphviz::Node::Record;
    Record rec;
    rec.setEscaped("ID", fmt1(node.id));

    auto add_field_text = [&](Str const& name, ImmId id) {
        rec.set(
            name,
            Record{hstd::ext::Graphviz::escapeHtmlForGraphviz(
                wrap_text(flatWords(node), 60, true))});
    };

    rec.setEscaped("Select", node.selfSelect());

    switch_node_value(
        node.id,
        node.ctx.lock(),
        overloaded{
            [&](ImmSubtree const& tree) {
                rec.setEscaped(
                    "Title",
                    join(
                        " ",
                        flatWords(
                            node.ctx.lock()->adaptUnrooted(tree.title))));
            },
            [&](ImmParagraph const& tree) {
                add_field_text("Text", node.id);
            },
            [&]<typename K>(K const& value) {
                rec.setEscaped("Type", value_metadata<K>::typeName());
            },
        });

    auto file = node.getFirstMatchingParent(
        [](ImmAdapter const& a) { return a.is(OrgSemKind::File); });

    if (node->loc || file) {
        rec.setEscaped(
            "Loc",
            fmt("{}:{}:{} @ {}",
                node->loc->column,
                node->loc->line,
                node->loc->pos,
                file ? file->as<ImmFile>()->relPath.get() : Str{"?"}));
    }

    for (auto const& [idx, unresolved] : enumerate(prop.unresolved)) {
        if (unresolved.isLink()) {
            auto const& val = node.ctx.lock()
                                  ->adapt(unresolved.getLink().link)
                                  .as<ImmLink>()
                                  .value();
            rec.setEscaped(
                fmt("Unresolved link [{}]", unresolved.getLink().link.id),
                fmt("{} {}",
                    val.target.getKind(),
                    std::visit(
                        [](auto const& d) -> std::string {
                            return to_json_eval(d).dump();
                        },
                        val.target.data)));
        } else {
            rec.setEscaped(
                fmt("Unresolved radio [{}]",
                    unresolved.getRadio().target.id),
                "radio target");
        }
    }

    return rec;
}
#endif

void org::graph::MapGraphState::addNodeRec(
    std::shared_ptr<org::imm::ImmAstContext> const& ast,
    const ImmAdapter&                               node,
    std::shared_ptr<MapConfig> const&               conf) {
    Func<void(ImmAdapter const&)> aux;
    aux = [&](ImmAdapter const& node) {
        conf->dbg.message(fmt("recursive add {}", node), "addNodeRec");
        auto __tmp = conf->dbg.scopeLevel();
        switch (node->getKind()) {
            case OrgSemKind::File:
            case OrgSemKind::Directory:
            case OrgSemKind::Symlink:
            case OrgSemKind::Document: {
                __perf_trace(
                    "mmpa",
                    "Recursive add node",
                    kind,
                    fmt1(node.getKind()));

                for (auto const& it : node) { aux(it); }
                break;
            }
            case OrgSemKind::CmdInclude:
            case OrgSemKind::ListItem:
            case OrgSemKind::List: {
                for (auto const& it : node) { aux(it); }
                break;
            }
            case OrgSemKind::Paragraph: {
                auto par = node.as<imm::ImmParagraph>();
                // conf.message(
                //     fmt("rec visit of {}\n{}",
                //         par,
                //         par.treeRepr().toString()));
                if (org::graph::hasGraphAnnotations(par)) {
                    addNode(node, conf);
                } else {
                    auto group = imm::getSubnodeGroups(ast, node, false);
                    if (rs::any_of(group, [](auto const& it) {
                            return it.isRadioTarget();
                        })) {
                        // conf.message(fmt("Paragraph has radio target"));
                        addNode(node, conf);
                    }
                }
                break;
            }
            case OrgSemKind::Subtree: {
                if (auto tree = node.as<imm::ImmSubtree>();
                    org::graph::hasGraphAnnotations(tree)) {
                    addNode(node, conf);
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

std::shared_ptr<MapGraphState> org::graph::initMapGraphState(
    std::shared_ptr<imm::ImmAstContext> ast) {
    return MapGraphState::FromAstContext(ast);
}
