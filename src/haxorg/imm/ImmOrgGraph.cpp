#include "ImmOrgGraph.hpp"
#include <haxorg/imm/ImmOrgEdit.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <immer/set_transient.hpp>
#include <immer/vector_transient.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>
#include "ImmGetterApi.hpp"

using namespace org::graph;
using namespace hstd;
using namespace org::imm;
using namespace hstd::ext;
using osk = OrgSemKind;
using slk = org::sem::LinkTarget::Kind;

bool org::graph::isMmapIgnored(ImmAdapter const& n) {
    return isInSubtreeDescriptionList(n)
        || (isLinkedDescriptionList(n) && isAttachedDescriptionList(n));
}

static const IntSet<slk> SkipLinks{
    slk::Raw,
    slk::Attachment,
};

bool org::graph::hasGraphAnnotations(ImmAdapterT<ImmSubtree> const& par) {
    return par->treeId->has_value()
        || !getSubtreeProperties<sem::NamedProperty::RadioId>(par.value())
                .empty();
}

bool org::graph::hasGraphAnnotations(
    ImmAdapterT<ImmParagraph> const& par) {
    for (auto const& node : par.sub(false)) {
        if (node.is(OrgSemKind::RadioTarget)) {
            return true;
        } else if (
            auto link = node.asOpt<ImmLink>();
            link && !SkipLinks.contains(link.value()->target.getKind())) {
            return true;
        }
    }

    return false;
}


void removeUnresolvedNodeProps(
    MapGraphState const*        state,
    MapNodeResolveResult const& resolved_node,
    hgraph::VertexID const&     newNode,
    hgraph::VertexIDSet const&  existingUnresolved,
    std::shared_ptr<MapConfig>  conf) {
    for (auto const& op : resolved_node.resolved) {
        auto remove_resolved = [&](hgraph::VertexID node) {
            auto attr = state->graph->getVertex(node)
                            ->getUniqueAttribute<MapNodeProp>();
            rs::actions::remove_if(
                attr->unresolved, [&](MapLink const& old) -> bool {
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
        };

        for (auto const& box : existingUnresolved) {
            remove_resolved(box);
        }
        remove_resolved(newNode);
    }
}

void updateUnresolvedNodeTracking(
    MapGraphState::Ptr const&   state,
    MapNodeResolveResult const& resolved_node,
    hgraph::VertexID const&     newNode,
    std::shared_ptr<MapConfig>  conf) {
    auto attr = state->graph->getAttr(newNode);
    state->graph->message(
        fmt("New node {}, resolution result {}, attribute unresolved {}",
            newNode,
            resolved_node,
            attr->unresolved.size()));

    auto node = state->graph->get(newNode);

    if (attr->unresolved.empty()) {
        // Newly added node has no unresolved elements, remove the ID from
        // map state tracking.
        if (state->unresolved.contains(newNode)) {
            state->unresolved.erase(newNode);
        }
    } else {
        LOGIC_ASSERTION_CHECK_FMT(
            !state->unresolved.contains(newNode),
            "Duplicate unresolved boxes are not expected: {}",
            newNode);

        state->graph->message(fmt("Adding {} as unresolved", newNode));

        state->unresolved.insert(newNode);
    }

    for (auto const& op : resolved_node.resolved) {
        hgraph::VertexIDSet toRemove;
        for (hgraph::VertexID const& it : state->unresolved) {
            if (state->graph->getAttr(it)->unresolved.empty()) {
                state->graph->message(
                    fmt("Node {} fixed all unresolved properties", it));
                toRemove.incl(it);
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
        s->graph->message(fmt("add edge {}-{}", op.source, op.target));
        auto edge = std::make_shared<MapEdge>();
        auto attr = std::make_shared<MapEdgeProp>();
        s->graph->addEdge(edge, attr, op.source, op.target);
    }
}

void traceNodeResolve(
    MapGraphState::Ptr const&   state,
    MapNodeResolveResult const& resolved_node,
    std::shared_ptr<MapConfig>  conf,
    hgraph::VertexID const&     mapNode) {
    auto node = state->graph->get(mapNode);
    auto attr = state->graph->getAttr(mapNode);
    if (state->graph->TraceState) {
        auto __scope = state->graph->scopeLevel();
        state->graph->message(
            fmt("v:{} original unresolved state:{} resolved:{} still "
                "unresolved:{}",
                mapNode,
                state->unresolved,
                attr->unresolved,
                resolved_node.resolved));

        for (auto const& u : attr->unresolved) {
            state->graph->message(fmt(">> g[v] unresolved {}", u));
        }

        for (auto const& u : resolved_node.resolved) {
            state->graph->message(
                fmt("<<+ updated resolved {} {}->{}",
                    u.link,
                    u.source,
                    u.target));
        }
    }
}


hgraph::VertexID MapGraphState::addNode(
    imm::ImmAdapter const&            node,
    std::shared_ptr<MapConfig> const& conf) {

    auto attr = conf->getInitialNodeProp(this, node);
    graph->message(
        fmt("initial node prop unresolved:{}", attr->unresolved));
    auto graph_node = MapNode::shared(node.uniq());
    auto res        = getGraph()->addNode(graph_node, attr);
    graph->message(
        fmt("added node:{} unresolved:{}",
            graph->getDebug(res),
            getGraph()->getAttr(res)->unresolved));


    graph->message(
        fmt(">>> unresolved:{}", getGraph()->getAttr(res)->unresolved));

    MapNodeResolveResult resolved = getResolvedNodeInsert(
        shared_from_this(), res, conf);

    graph->message(
        fmt(">>> unresolved:{}", getGraph()->getAttr(res)->unresolved));

    // debug-print node resolution state
    traceNodeResolve(shared_from_this(), resolved, conf, res);

    graph->message(
        fmt(">>> unresolved:{}", getGraph()->getAttr(res)->unresolved));

    // Iterate over all known unresolved nodes and adjust node property
    // values in the graph to account for new property changes.
    removeUnresolvedNodeProps(this, resolved, res, unresolved, conf);

    graph->message(
        fmt(">>> unresolved:{}", getGraph()->getAttr(res)->unresolved));

    // Collect new list of unresolved nodes for the changes.
    updateUnresolvedNodeTracking(shared_from_this(), resolved, res, conf);

    graph->message(
        fmt(">>> unresolved:{}", getGraph()->getAttr(res)->unresolved));

    // Add all resolved edges to the graph
    updateResolvedEdges(shared_from_this(), resolved, conf);

    graph->message(
        fmt(">>> unresolved:{}", getGraph()->getAttr(res)->unresolved));
    return res;
}


static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};


Opt<MapLink> org::graph::MapGraphState::getUnresolvedLink(
    ImmAdapterT<ImmLink> link) const {
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
    ImmAdapterT<ImmSubtree> tree) const {
    Vec<MapLink> unresolved;
    // Description lists with links in header are attached as the
    // outgoing link to the parent subtree. It is the only supported
    // way to provide an extensive label between subtree nodes.
    for (auto const& list : tree.subAs<ImmList>()) {
        if (auto attached = list.getListAttrs("attached");
            attached.has(0) && attached.at(0).getString() == "subtree") {
            graph->message("Subtree has list");
            for (auto const& item : list.subAs<ImmListItem>()) {
                graph->message(fmt("{}", item.id));
                if (isLinkedDescriptionItemNode(item)) {
                    graph->message("List has description item");
                    for (auto const& link :
                         item.pass(item->header->value())
                             .subAs<ImmLink>()) {
                        graph->message(
                            fmt("List item contains link {}", link));
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


SPtr<MapNodeProp> org::graph::MapConfig::getInitialNodeProp(
    MapGraphState const* state,
    ImmAdapter           node) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    LOGIC_ASSERTION_CHECK_FMT(
        !isMmapIgnored(node), "Node {} is ignored for mmap", node);

    state->graph->message(
        fmt("box:{} desc-item:{} desc-list:{}",
            node.id.getReadableId(),
            isLinkedDescriptionItem(node),
            isLinkedDescriptionList(node)));

    auto result = std::make_shared<MapNodeProp>();

    auto register_used_links = [&](ImmAdapter arg) {
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (auto link = arg.asOpt<ImmLink>()) {
            if (auto target = state->getUnresolvedLink(link.value())) {
                state->graph->message(
                    fmt("Got unresolved link for adapter {} under {}",
                        arg,
                        node));
                result->unresolved.push_back(target.value());
            }
        }
    };

    if (auto tree = node.asOpt<ImmSubtree>()) {
        result->unresolved.append(
            state->getUnresolvedSubtreeLinks(tree.value()));
    } else if (
        auto par = node.asOpt<ImmParagraph>();
        par && par->isFootnoteDefinition()) {
        auto sub = par->sub();
        for (auto const& it : enumerator(sub)) {
            if (!it.is_first()) {
                eachSubnodeRec(it.value(), true, register_used_links);
            }
        }
    } else if (!NestedNodes.contains(node->getKind())) {
        state->graph->message("registering nested outgoing links");
        auto __tmp = state->graph->scopeLevel();
        org::eachSubnodeRec(node, true, register_used_links);
    }


    state->graph->message(
        fmt("box:{} unresolved:{}",
            node.id.getReadableId(),
            result->unresolved));


    return result;
}

Vec<MapLinkResolveResult> org::graph::getResolveTarget(
    MapGraphState::Ptr const&  state,
    hgraph::VertexID const&    source,
    MapLink const&             link,
    std::shared_ptr<MapConfig> conf) {
    auto g = state->graph;
    g->message(fmt("Get resolve targets {} {}", source, link));

    Vec<MapLinkResolveResult> result;

    if (link.isRadio()) {
        // Unresolved radio link already contains all the information for
        // creating edge. This only happens when the node itself has not
        // been added to the graph.
        result.push_back(
            MapLinkResolveResult{
                .link   = link,
                .target = g->getVertexID(link.getRadio().target),
                .source = source,
            });
    } else {
        g->message(
            fmt("footnotes {}", state->ast->currentTrack->footnotes));
        g->message(fmt("subtrees {}", state->ast->currentTrack->subtrees));
        g->message(fmt("names {}", state->ast->currentTrack->names));

        auto add_edge = [&](imm::ImmId const& target) {
            auto adapters = state->ast->getAdaptersFor(target);
            LOGIC_ASSERTION_CHECK_FMT(
                !adapters.empty(),
                "Target node {} does not have any parent adapters tracked",
                target);

            for (auto const& full : adapters) {
                result.push_back(
                    MapLinkResolveResult{
                        .link   = link,
                        .target = g->getVertexID(full),
                        .source = source,
                    });
            }
        };

        MapLink::Link const& spec = link.getLink();
        auto link_adapter = state->ast->adapt(spec.link).as<ImmLink>();
        switch (link_adapter->target.getKind()) {
            case slk::Id: {
                auto text = link_adapter->target.getId().text;
                if (auto target = state->ast->currentTrack->subtrees.get(
                        text)) {
                    g->message(
                        fmt("Subtree ID {} on {} resolved to {}",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    g->message(fmt("Not subtree with ID {}", text));
                }
                break;
            }

            case slk::CustomId: {
                auto text = link_adapter->target.getCustomId().text;
                if (auto target = state->ast->currentTrack->customIds.get(
                        text)) {
                    g->message(
                        fmt("Subtree custom ID {} on {} resolved to {}",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    g->message(fmt("Not subtree with custom ID {}", text));
                }
                break;
            }

            case slk::Footnote: {
                Str const& text = link_adapter->target.getFootnote()
                                      .target;
                if (auto target = state->ast->currentTrack->footnotes.get(
                        text)) {
                    g->message(
                        fmt("Footnote name {} on {} resolved to {}",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    g->message(fmt("No footnote with ID {}", text));
                }
                break;
            }

            case slk::Internal: {
                Str const& text = link_adapter->target.getInternal()
                                      .target;
                if (auto target = state->ast->currentTrack->names.get(
                        text)) {
                    g->message(
                        fmt("Internal link name '{}' on '{}' resolved to "
                            "named "
                            "node '{}'",
                            text,
                            source,
                            *target));
                    add_edge(*target);
                } else {
                    g->message(fmt("No internal link with ID '{}'", text));
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

namespace {
void collect_radio_targets(
    std::shared_ptr<MapGraph> const& g,
    MapNodeResolveResult&            result,
    MapNodeProp::Ptr const&          attr,
    hgraph::VertexID const&          node_id,
    MapNode const*                   node,
    MapGraphState::Ptr const&        state) {
    auto __scope = g->scopeLevel();
    g->message(fmt("Collecting radio targets in graph"));

    auto found_radio_target_node = [&](ImmAdapter const& radio) {
        if (g->isRegisteredNode(radio.uniq())) {
            g->message(
                fmt("Detected radio target from node {} "
                    "to target {}, which is a resolved "
                    "graph node. ",
                    g->getDebug(node_id),
                    radio));
            result.resolved.push_back(
                MapLinkResolveResult{
                    .source = node_id,
                    .target = g->getVertexID(radio.uniq()),
                });
        } else {
            g->message(
                fmt("Radio target {} from node {} is not "
                    "a resolved graph node.",
                    radio,
                    g->getDebug(node_id)));
            attr->unresolved.push_back(
                MapLink{MapLink::Radio{.target = radio.uniq()}});
        }
    };

    if (auto par = node->getAdapter(state->ast)
                       .asOpt<org::imm::ImmParagraph>()) {
        for (auto const& group :
             getSubnodeGroups(state->ast, node->getAdapter(state->ast))) {
            g->message(fmt("Group {}", group));
            if (group.isRadioTarget()) {
                g->message(fmt("Got radio target group"));
                auto groupTarget = group.getRadioTarget().target;
                if (groupTarget.is(OrgSemKind::Subtree)) {
                    for (auto const& subtree :
                         state->ast->getPathsFor(groupTarget)) {
                        found_radio_target_node(
                            state->ast->adapt(subtree));
                    }
                } else if (groupTarget.is(OrgSemKind::RadioTarget)) {
                    for (ImmAdapter const& radio :
                         state->ast->getParentPathsFor(groupTarget)) {
                        found_radio_target_node(radio);
                    }
                } else {
                    LOGIC_ASSERTION_CHECK_FMT(
                        false,
                        "Unexpected subnode group target kind {}",
                        groupTarget.getKind())
                }
            }
        }
    }
}
} // namespace

MapNodeResolveResult org::graph::getResolvedNodeInsert(
    MapGraphState::Ptr const&  state,
    hgraph::VertexID const&    node_id,
    std::shared_ptr<MapConfig> conf) {
    MapNodeResolveResult result;

    auto g       = state->graph;
    auto __scope = g->scopeLevel();
    auto attr    = g->getAttr(node_id);
    auto node    = g->getCastVertex<MapNode>(node_id);

    attr->unresolved.clear();
    g->message(fmt("Get unresolved for node {}", g->getDebug(node_id)));

    LOGIC_ASSERTION_CHECK_FMT(
        !state->unresolved.contains(node_id),
        "Node {} is already marked as unresolved in the graph",
        g->getDebug(node_id));

    g->message(fmt("Unresolved state {}", g->getDebug(state->unresolved)));

    collect_radio_targets(g, result, attr, node_id, node, state);

    {
        auto __scope = g->scopeLevel();
        for (auto const& unresolvedLink : attr->unresolved) {
            Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                state, node_id, unresolvedLink, conf);
            if (resolved_edit.empty()) {
                g->message(
                    fmt("No resolved links from {}", unresolvedLink));
                attr->unresolved.push_back(unresolvedLink);
            } else {
                for (auto const& resolved : resolved_edit) {
                    // if (g->isRegisteredNode(resolved.target)) {
                    //     g->message(
                    //         fmt("resolved to known node:{}", resolved));
                    //     result.resolved.push_back(resolved);
                    // } else {
                    g->message(
                        fmt("resolved to unregistered node:{}", resolved));
                    attr->unresolved.push_back(unresolvedLink);
                    // }
                }
            }
        }
    }

    g->message(fmt("Process unresolved for state"));
    {
        auto __scope = g->scopeLevel();
        for (hgraph::VertexID const& nodeWithUnresolved :
             state->unresolved) {
            LOGIC_ASSERTION_CHECK_FMT(
                nodeWithUnresolved != node_id,
                "cannot resolve already inserted node {} == {} ({}) is "
                "recorded in s.unresolved",
                nodeWithUnresolved,
                node_id,
                nodeWithUnresolved != node_id);

            for (auto const& link :
                 g->getAttr(nodeWithUnresolved)->unresolved) {
                Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                    state, nodeWithUnresolved, link, conf);
                if (resolved_edit.empty()) {
                    g->message(fmt(
                        "No resolve target for {}", nodeWithUnresolved));
                } else {
                    for (auto const& resolved : resolved_edit) {
                        // if (g->isRegisteredNode(resolved.target)) {
                        g->message(
                            fmt("resolved to registered node:{} it:{} "
                                "edit:{}",
                                resolved,
                                nodeWithUnresolved,
                                node_id));
                        result.resolved.push_back(resolved);
                        // }
                    }
                }
            }
        }
    }

    g->message(
        fmt("box:{} resolved:{} unresolved:{}",
            node_id,
            result.resolved,
            attr->unresolved));

    if (false) {
        for (auto const& r1 : result.resolved) {
            int count = 0;
            for (auto const& r2 : result.resolved) {
                if (r1.target == r2.target && r1.source == r2.source) {
                    ++count;
                }
            }

            LOGIC_ASSERTION_CHECK_FMT(
                count <= 1,
                "Resolved link target contains duplicate edges: {}-{}",
                r1.source,
                r1.target);
        }
    } else {
        hstd::Vec<MapLinkResolveResult> unique_resolved;
        std::set<std::pair<hgraph::VertexID, hgraph::VertexID>> seen;

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

using namespace hstd::ext::graph;

#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH

hstd::SPtr<gv::GraphGroup> MapGraph::GvConfig::toGraphviz(
    imm::ImmAstContext::Ptr const& ctx,
    MapGraph::Ptr const&           graph) {
    hstd::SPtr<gv::GraphGroup> res = gv::GraphGroup::newRootGraph(
        run, "g"_ss);

    LOGIC_ASSERTION_CHECK(run->groups->getEdges().size() == 0, "");
    LOGIC_ASSERTION_CHECK(res->run->graph->getVertexCount() == 0, "");
    LOGIC_ASSERTION_CHECK(res->run->groups->getVertexCount() == 0, "");

    auto rg = layout_graph->addVertex();
    run->addRootGroup(rg, res);
    // base ID <-> mapped ID
    hstd::ext::Unordered1to1Bimap<VertexID, VertexID> ids;

    auto get_mapped = [&](VertexID id) -> VertexID {
        return ids.at_right(id);
    };

    for (auto const& [it, imm_id, prop] : graph->getProperties()) {
        if (acceptNode(it)) {
            auto mapped_id = layout_graph->addVertex();
            ids.add_unique(it, mapped_id);
            auto node = res->addVertex(rg, mapped_id);
            node->setAttr("org_id", imm_id.getReadableId());
            node->startHtmlRecord();
            *node->getNodeRecord() = getNodeLabel(
                ctx->adapt(imm_id), prop);
            node->finishHtmlRecord();
        }
    }

    for (auto const& [eid, prop] : graph->getEdges()) {
        if (acceptNode(graph->getSource(eid))
            && acceptNode(graph->getTarget(eid)) && acceptEdge(eid)) {
            auto mapped_edge = layout_graph->addEdge(
                get_mapped(graph->getTarget(eid)), graph->getSource(eid));
            auto edge = res->addEdge(mapped_edge);
        }
    }

    return res;
}
#endif

MapConfig::MapConfig(SPtr<MapInterface> impl) : impl{impl} {}

MapConfig::MapConfig() : impl{std::make_shared<MapInterface>()} {}

#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH
gv::NodeAttribute::Record MapGraph::GvConfig::getNodeLabel(
    ImmAdapter const&       node,
    MapNodeProp::Ptr const& prop) const {
    using Record = gv::NodeAttribute::Record;
    Record rec;
    rec.setEscaped("ID", fmt1(node.id));

    auto add_field_text = [&](Str const& name, ImmId id) {
        rec.set(
            name,
            Record{gv::escapeHtmlForGraphviz(
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

    for (auto const& [idx, unresolved] : enumerate(prop->unresolved)) {
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
    ImmAdapter const&                               node,
    std::shared_ptr<MapConfig> const&               conf) {
    Func<void(ImmAdapter const&)> aux;
    aux = [&](ImmAdapter const& node) {
        graph->message(fmt("recursive add {}", node), "addNodeRec");
        auto __tmp = graph->scopeLevel();
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
                    std::ignore = addNode(node, conf);
                } else {
                    auto group = imm::getSubnodeGroups(ast, node, false);
                    if (rs::any_of(group, [](auto const& it) {
                            return it.isRadioTarget();
                        })) {
                        // conf.message(fmt("Paragraph has radio target"));
                        std::ignore = addNode(node, conf);
                    }
                }
                break;
            }
            case OrgSemKind::Subtree: {
                if (auto tree = node.as<imm::ImmSubtree>();
                    org::graph::hasGraphAnnotations(tree)) {
                    std::ignore = addNode(node, conf);
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

hstd::Opt<Str> MapNode::getFootnoteName(
    std::shared_ptr<imm::ImmAstContext> const& context) const {
    if (auto par = getAdapter(context).asOpt<org::imm::ImmParagraph>();
        par && par->isFootnoteDefinition()) {
        return par->getFootnoteName();
    } else {
        return std::nullopt;
    }
}

hstd::Opt<Str> MapNode::getSubtreeId(
    std::shared_ptr<imm::ImmAstContext> const& context) const {
    if (auto tree = getAdapter(context).asOpt<org::imm::ImmSubtree>();
        tree && tree.value()->treeId.get()) {
        return tree.value()->treeId->value();
    } else {
        return std::nullopt;
    }
}
