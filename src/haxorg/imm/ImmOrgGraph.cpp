#include "ImmOrgGraph.hpp"
#include "ImmGetterApi.hpp"
#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>
#include <haxorg/imm/ImmOrgEdit.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <immer/set_transient.hpp>
#include <immer/vector_transient.hpp>
#if ORG_BUILD_WITH_PROTOBUF
#    include "src/haxorg/imm/ImmOrgGraph.pb.h"
#endif
#include <haxorg/serde/SemOrgSerde.hpp>
#include <haxorg/serde/SemOrgSerdeDeclarations.hpp>
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/MapFormatter.hpp>
#include <hstd/stdlib/SetFormatter.hpp>

using namespace org::graph;
using namespace hstd;
using namespace org::imm;
using namespace hstd::ext;
using osk = OrgSemKind;
using slk = org::sem::LinkTarget::Kind;


hstd::Opt<Str> org::graph::MapNode::getSubtreeId(
    std::shared_ptr<org::imm::ImmAstContext> const& context) const {
    if (auto tree = getAdapter().asOpt<org::imm::ImmSubtree>();
        tree && tree.value()->treeId.get()) {
        return tree.value()->treeId->value();
    } else {
        return std::nullopt;
    }
}

static const IntSet<slk> SkipLinks{
    slk::Raw,
    slk::Attachment,
};

bool org::graph::hasGraphAnnotations(org::imm::ImmAdapterT<ImmSubtree> const& par) {
    return par->treeId->has_value()
        || !getSubtreeProperties<sem::NamedProperty::RadioId>(par.value()).empty();
}

bool org::graph::hasGraphAnnotations(org::imm::ImmAdapterT<ImmParagraph> const& par) {
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
    __perf_trace("graph", "remove unresolved node props");
    for (auto const& op : resolved_node.resolved) {
        OP_TRACER_MESSAGE(state->graph, "removing unresolved node props {}", op);
        auto remove_resolved = [&](hgraph::VertexID node) {
            auto attr = state->graph->getVertex(node)->getUniqueAttribute<MapNodeProp>();
            rs::actions::remove_if(attr->unresolved, [&](MapLink const& old) -> bool {
                bool res = false;
                if (old.isLink() && op.link.isLink()) {
                    res = old.getLink().link == op.link.getLink().link;
                } else if (old.isRadio() && op.link.isRadio()) {
                    res = old.getRadio().target == op.link.getRadio().target;
                }
                OP_TRACER_MESSAGE(
                    state->graph,
                    "checking if state must be removed? {} for {}",
                    res,
                    old);
                return res;
            });
        };

        for (auto const& box : existingUnresolved) { remove_resolved(box); }

        remove_resolved(newNode);
    }
}

void updateUnresolvedNodeTracking(
    MapGraphState::Ptr const&   state,
    MapNodeResolveResult const& resolved_node,
    hgraph::VertexID const&     newNode,
    std::shared_ptr<MapConfig>  conf) {
    __perf_trace("graph", "update unresolved node tracking");
    auto attr = state->graph->getAttr(newNode);
    OP_TRACER_MESSAGE(
        state->graph,
        "New node {}, resolution result {}, attribute unresolved {}",
        newNode,
        resolved_node,
        attr->unresolved.size());

    auto node = state->graph->get(newNode);

    if (attr->unresolved.empty()) {
        // Newly added node has no unresolved elements, remove the ID from
        // map state tracking.
        if (state->unresolved.contains(newNode)) { state->unresolved.erase(newNode); }
    } else {
        LOGIC_ASSERTION_CHECK_FMT(
            !state->unresolved.contains(newNode),
            "Duplicate unresolved boxes are not expected: {}",
            newNode);

        OP_TRACER_MESSAGE(state->graph, "Adding {} as unresolved", newNode);

        state->unresolved.insert(newNode);
    }

    for (auto const& op : resolved_node.resolved) {
        hgraph::VertexIDSet toRemove;
        for (hgraph::VertexID const& it : state->unresolved) {
            if (state->graph->getAttr(it)->unresolved.empty()) {
                OP_TRACER_MESSAGE(
                    state->graph, "Node {} fixed all unresolved properties", it);
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
        OP_TRACER_MESSAGE(s->graph, "add edge {}-{}", op.source, op.target);
        auto edge = std::make_shared<MapEdge>(hstd::fmt1(
            s->graph->edges->edges.getNextId(s->graph->edges->getCollectionID().t)));
        auto attr = std::make_shared<MapEdgeProp>();
        s->graph->addEdge(
            edge,
            attr,
            s->graph->getVertexID(op.source),
            s->graph->getVertexID(op.target));
    }
}

void traceNodeResolve(
    MapGraphState::Ptr const&   state,
    MapNodeResolveResult const& resolved_node,
    std::shared_ptr<MapConfig>  conf,
    hgraph::VertexID const&     mapNode) {
    if (state->graph->canTrace()) {
        auto node    = state->graph->get(mapNode);
        auto attr    = state->graph->getAttr(mapNode);
        auto __scope = state->graph->begin_scope();
        OP_TRACER_MESSAGE(
            state->graph,
            "v:{} original unresolved state:{} resolved:{} still "
            "unresolved:{}",
            mapNode,
            state->unresolved,
            attr->unresolved,
            resolved_node.resolved);

        for (auto const& u : attr->unresolved) {
            OP_TRACER_MESSAGE(state->graph, ">> g[v] unresolved {}", u);
        }

        for (auto const& u : resolved_node.resolved) {
            OP_TRACER_MESSAGE(
                state->graph,
                "<<+ updated resolved {} {}->{}",
                u.link,
                u.source,
                u.target);
        }
    }
}


hstd::Opt<Str> org::graph::MapNode::getFootnoteName(
    std::shared_ptr<org::imm::ImmAstContext> const& context) const {
    if (auto par = getAdapter().asOpt<org::imm::ImmParagraph>();
        par && par->isFootnoteDefinition()) {
        return par->getFootnoteName();
    } else {
        return std::nullopt;
    }
}


hgraph::EdgeID org::graph::MapGraph::addEdge(
    hstd::SPtr<MapEdge> const&     edge,
    hstd::SPtr<MapEdgeProp> const& prop,
    hstd::ext::graph::VertexID     source,
    hstd::ext::graph::VertexID     target) {
    edge->addAttribute(prop);
    auto res = edges->add(edge);
    LOGIC_ASSERTION_CHECK(edges->hasEdge(res), "");
    edges->trackEdge(res, source, target);

    TRACE_COUNTER("graph", "edge_count", edges->getNumEdges());
    return res;
}


hgraph::VertexID org::graph::MapGraph::addNode(
    hstd::SPtr<MapNode> const&     node,
    hstd::SPtr<MapNodeProp> const& prop) {
    node->addAttribute(prop);
    auto res = nodes.add(node);
    id_map.insert_or_assign(node->id.uniq(), res);
    trackVertex(res);

    TRACE_COUNTER("graph", "vertex_count", getVertexCount());
    return res;
}


SPtr<MapNodeProp> org::graph::MapConfig::getInitialNodeProp(
    MapGraphState const* state,
    org::imm::ImmAdapter node) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.

    OP_TRACER_MESSAGE(
        state->graph,
        "box:{} desc-item:{} desc-list:{}",
        node.id.getReadableId(),
        isPartOfDescriptionListItem(node),
        isInternalLinkedDescriptionList(node));

    auto result = std::make_shared<MapNodeProp>();

    auto register_used_links = [&](ImmAdapter arg) {
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (auto link = arg.asOpt<ImmLink>()) {
            if (auto target = state->getUnresolvedLink(link.value())) {
                OP_TRACER_MESSAGE(
                    state->graph,
                    "Got unresolved link for adapter {} under {}",
                    arg,
                    node);
                result->unresolved.push_back(target.value());
            }
        }
    };

    if (SemSet{
            OrgSemKind::Paragraph,
        }
            .contains(node->getKind())) {
        auto __tmp = state->graph->begin_scope("registering nested outgoing links");
        org::eachSubnodeRec(node, true, register_used_links);
    }

    OP_TRACER_MESSAGE(
        state->graph,
        "box:{} unresolved:{}",
        node.id.getReadableId(),
        result->unresolved);


    return result;
}

hstd::Vec<org::imm::ImmAdapter> const& org::graph::MapGraphState::getAdaptersFor(
    org::imm::ImmId const& id) {
    if (!cache.contains(id)) {
        cache.insert_or_assign(id, ast->getAdaptersFor(id));
        TRACE_COUNTER("graph", "adapter_cache", cache.size());
    }
    return cache.at(id);
}

hgraph::VertexID org::graph::MapGraphState::addNode(
    org::imm::ImmAdapter const&       node,
    std::shared_ptr<MapConfig> const& conf) {
    __perf_trace("graph", "add node");

    auto attr = conf->getInitialNodeProp(this, node);
    OP_TRACER_MESSAGE(graph, "initial node prop unresolved:{}", attr->unresolved);
    auto graph_node = MapNode::shared(node);
    auto res        = getGraph()->addNode(graph_node, attr);
    OP_TRACER_MESSAGE(
        graph,
        "added node:{} unresolved:{}",
        graph->getDebug(res),
        getGraph()->getAttr(res)->unresolved);


    MapNodeResolveResult resolved = getResolvedNodeInsert(shared_from_this(), res, conf);

    // debug-print node resolution state
    traceNodeResolve(shared_from_this(), resolved, conf, res);

    // Iterate over all known unresolved nodes and adjust node property
    // values in the graph to account for new property changes.
    removeUnresolvedNodeProps(this, resolved, res, unresolved, conf);

    // Collect new list of unresolved nodes for the changes.
    updateUnresolvedNodeTracking(shared_from_this(), resolved, res, conf);

    // Add all resolved edges to the graph
    updateResolvedEdges(shared_from_this(), resolved, conf);

    return res;
}

namespace {

struct resolve_state {
    std::shared_ptr<MapGraph> const&  g;
    MapNodeResolveResult&             result;
    MapNodeProp::Ptr const&           attr;
    hgraph::VertexID const&           node_id;
    MapNode const*                    node;
    MapGraphState::Ptr const&         state;
    std::shared_ptr<MapConfig> const& conf;

    void collect_radio_targets() {
        __perf_trace("graph", "collect_radio_targets");
        auto __scope = g->begin_scope("Collecting radio targets in graph");

        auto found_radio_target_node = [&](ImmAdapter const& radio) {
            if (g->isRegisteredNode(radio.uniq())) {
                OP_TRACER_MESSAGE(
                    g,
                    "Detected radio target from node {} "
                    "to target {}, which is a resolved "
                    "graph node. ",
                    g->getDebug(node_id),
                    radio);
                result.resolved.push_back(
                    MapLinkResolveResult{
                        .target = radio.uniq(),
                        .source = g->getImmID(node_id),
                    });
            } else {
                OP_TRACER_MESSAGE(
                    g,
                    "Radio target {} from node {} is not "
                    "a resolved graph node.",
                    radio,
                    g->getDebug(node_id));
                attr->unresolved.push_back(
                    MapLink{MapLink::Radio{.target = radio.uniq()}});
            }
        };

        if (auto par = node->getAdapter().asOpt<org::imm::ImmParagraph>()) {
            for (auto const& group : getSubnodeGroups(state->ast, node->getAdapter())) {
                OP_TRACER_MESSAGE(g, "Group {}", group);
                if (group.isRadioTarget()) {
                    OP_TRACER_MESSAGE(g, "Got radio target group");
                    auto groupTarget = group.getRadioTarget().target;
                    if (groupTarget.is(OrgSemKind::Subtree)) {
                        for (auto const& subtree : state->ast->getPathsFor(groupTarget)) {
                            found_radio_target_node(state->ast->adapt(subtree));
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

    void attempt_attribute_resolve() {
        __perf_trace("graph", "attempt_attribute_resolve");
        auto original_unresolved = attr->unresolved;
        attr->unresolved.clear();
        auto __scope = g->begin_scope();
        for (auto const& unresolvedLink : original_unresolved) {
            Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                state, node_id, unresolvedLink, conf);
            if (resolved_edit.empty()) {
                OP_TRACER_MESSAGE(g, "No resolved links from {}", unresolvedLink);
                attr->unresolved.push_back(unresolvedLink);
            } else {
                for (auto const& resolved : resolved_edit) {
                    if (g->isRegisteredNode(resolved.target)) {
                        OP_TRACER_MESSAGE(g, "resolved to known node:{}", resolved);
                        result.resolved.push_back(resolved);
                    } else {
                        OP_TRACER_MESSAGE(
                            g, "resolved to unregistered node:{}", resolved);
                        attr->unresolved.push_back(unresolvedLink);
                    }
                }
            }
        }
    }

    void process_global_pending_unresolved() {
        __perf_trace("graph", "process_global_pending_unresolved");
        OP_TRACER_MESSAGE(g, "Process unresolved for state");
        auto __scope = g->begin_scope();
        for (hgraph::VertexID const& nodeWithUnresolved : state->unresolved) {
            LOGIC_ASSERTION_CHECK_FMT(
                nodeWithUnresolved != node_id,
                "cannot resolve already inserted node {} == {} ({}) is "
                "recorded in s.unresolved",
                nodeWithUnresolved,
                node_id,
                nodeWithUnresolved != node_id);

            for (auto const& link : g->getAttr(nodeWithUnresolved)->unresolved) {
                Vec<MapLinkResolveResult> resolved_edit = getResolveTarget(
                    state, nodeWithUnresolved, link, conf);
                if (resolved_edit.empty()) {
                    OP_TRACER_MESSAGE(g, "No resolve target for {}", nodeWithUnresolved);
                } else {
                    for (auto const& resolved : resolved_edit) {
                        if (g->isRegisteredNode(resolved.target)) {
                            OP_TRACER_MESSAGE(
                                g,
                                "resolved to registered node:{} it:{} "
                                "edit:{}",
                                resolved,
                                nodeWithUnresolved,
                                node_id);
                            result.resolved.push_back(resolved);
                        }
                    }
                }
            }
        }
    }

    void fill_resolved_nodes() {
        if (false) {
            for (auto const& r1 : result.resolved) {
                int count = 0;
                for (auto const& r2 : result.resolved) {
                    if (r1.target == r2.target && r1.source == r2.source) { ++count; }
                }

                LOGIC_ASSERTION_CHECK_FMT(
                    count <= 1,
                    "Resolved link target contains duplicate edges: {}-{}",
                    r1.source,
                    r1.target);
            }
        } else {
            hstd::Vec<MapLinkResolveResult>                               unique_resolved;
            std::set<std::pair<org::imm::ImmUniqId, org::imm::ImmUniqId>> seen;

            for (const auto& r : result.resolved) {
                auto pair = std::make_pair(r.target, r.source);
                if (seen.find(pair) == seen.end()) {
                    seen.insert(pair);
                    unique_resolved.push_back(r);
                }
            }
            result.resolved = std::move(unique_resolved);
        }
    }
};


} // namespace

MapNodeResolveResult org::graph::getResolvedNodeInsert(
    MapGraphState::Ptr const&  state,
    hgraph::VertexID const&    node_id,
    std::shared_ptr<MapConfig> conf) {
    __perf_trace("graph", "getResolvedNodeInsert");
    MapNodeResolveResult result;

    auto g       = state->graph;
    auto __scope = g->begin_scope();
    auto attr    = g->getAttr(node_id);
    auto node    = g->getCastVertex<MapNode>(node_id);


    OP_TRACER_MESSAGE(g, "Get unresolved for node {}", g->getDebug(node_id));

    LOGIC_ASSERTION_CHECK_FMT(
        !state->unresolved.contains(node_id),
        "Node {} is already marked as unresolved in the graph",
        g->getDebug(node_id));

    OP_TRACER_MESSAGE(g, "Unresolved state {}", g->getDebug(state->unresolved));

    resolve_state rs{
        .g       = g,
        .result  = result,
        .attr    = attr,
        .node_id = node_id,
        .node    = node,
        .state   = state,
        .conf    = conf,
    };

    rs.collect_radio_targets();
    rs.attempt_attribute_resolve();
    rs.process_global_pending_unresolved();


    OP_TRACER_MESSAGE(
        g,
        "box:{} resolved:{} unresolved:{}",
        node_id,
        result.resolved,
        attr->unresolved);

    rs.fill_resolved_nodes();

    return result;
}

using namespace hstd::ext::graph;

#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH

gv::Record org::graph::MapGraph::GvConfig::getNodeLabel(
    org::imm::ImmAdapter const& node,
    MapNodeProp::Ptr const&     prop) const {
    using Record = gv::Record;
    Record rec;
    rec.setEscaped("ID", fmt1(node.id));

    auto add_field_text = [&](Str const& name, ImmId id) {
        rec.set(
            name,
            Record{gv::escapeHtmlForGraphviz(wrap_text(flatWords(node), 60, true))});
    };

    rec.setEscaped("Select", node.selfSelect());

    switch_node_value(
        node.id,
        node.ctx.lock(),
        overloaded{
            [&](ImmSubtree const& tree) {
                rec.setEscaped(
                    "Title",
                    join(" ", flatWords(node.ctx.lock()->adaptUnrooted(tree.title))));
            },
            [&](ImmParagraph const& tree) { add_field_text("Text", node.id); },
            [&]<typename K>(K const& value) {
                rec.setEscaped("Type", value_metadata<K>::typeName());
            },
        });

    auto file = node.getFirstMatchingParent(
        [](ImmAdapter const& a) { return a.is(OrgSemKind::File); });

    if (node->loc || file) {
        rec.setEscaped(
            "Loc",
            hstd::fmt(
                "{}:{}:{} @ {}",
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
                hstd::fmt("Unresolved link [{}]", unresolved.getLink().link.id),
                hstd::fmt(
                    "{} {}",
                    val.target.getKind(),
                    std::visit(
                        [](auto const& d) -> std::string {
                            return to_json_eval(d).dump();
                        },
                        val.target.data)));
        } else {
            rec.setEscaped(
                hstd::fmt("Unresolved radio [{}]", unresolved.getRadio().target.id),
                "radio target");
        }
    }

    return rec;
}
#endif

MapConfig::MapConfig(SPtr<MapInterface> impl) : impl{impl} {}

MapConfig::MapConfig() : impl{std::make_shared<MapInterface>()} {}

#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH
hstd::SPtr<gv::GraphGroup> org::graph::MapGraph::GvConfig::toGraphviz(
    org::imm::ImmAstContext::Ptr const& ctx,
    MapGraph::Ptr const&                graph) {
    hstd::SPtr<gv::GraphGroup> res = gv::GraphGroup::newRootGraph(run, "g"_ss);

    LOGIC_ASSERTION_CHECK(run->getGroups()->getEdges().size() == 0, "");
    LOGIC_ASSERTION_CHECK(res->run->getGraph()->getVertexCount() == 0, "");
    LOGIC_ASSERTION_CHECK(res->run->getGroups()->getVertexCount() == 0, "");

    auto rg = state.graph->addVertex();
    run->setRootGroupAttribute(rg, res);
    // base ID <-> mapped ID
    hstd::ext::Unordered1to1Bimap<VertexID, VertexID> ids;

    auto get_mapped = [&](VertexID id) -> VertexID { return ids.at_right(id); };

    for (auto const& [it, imm_id, prop] : graph->getProperties()) {
        if (acceptNode(it)) {
            auto mapped_id = state.graph->addVertex(imm_id.getReadableId());
            ids.add_unique(it, mapped_id);
            state.hierarchy->trackVertex(mapped_id);
            auto nesting_id = state.hierarchy->trackSubVertexRelation(rg, mapped_id);
            OP_TRACER_MESSAGE(
                run, "Nesting ID {} {}", nesting_id, run->getDebug(nesting_id));

            auto node = res->addVertex(nesting_id);
            node->setAttr("org_id", imm_id.getReadableId());
            node->setHtmlNodeRecord(getNodeLabel(ctx->adapt(imm_id), prop));
        }
    }

    for (auto const& [eid, prop] : graph->getEdges()) {
        if (acceptNode(graph->getSource(eid)) && acceptNode(graph->getTarget(eid))
            && acceptEdge(eid)) {
            auto mapped_edge = state.graph->addEdge(
                get_mapped(graph->getTarget(eid)), get_mapped(graph->getSource(eid)));
            auto edge = res->addEdge(mapped_edge);
        }
    }

    return res;
}
#endif

namespace {
hgraph::VertexID add_single_node(
    org::graph::MapGraphState*         state,
    ImmAdapter const&                  node,
    hstd::Opt<hgraph::VertexID> const& parent,
    std::shared_ptr<MapConfig> const&  conf,
    hstd::Opt<MapEdge::EdgeKind>       edge_override = std::nullopt) {
    auto vertex = state->addNode(node, conf);
    if (parent.has_value()) {
        auto edge = std::make_shared<MapEdge>(
            hstd::fmt1(state->graph->edges->edges.getNextId(
                state->graph->edges->getCollectionID().t)));
        if (edge_override) {
            edge->kind = edge_override.value();
        } else if (
            state->graph->getCastVertex<MapNode>(parent.value())
                ->getAdapter()
                .is(OrgSemKind::Subtree)
            && node.is(OrgSemKind::Subtree)) {
            edge->kind = MapEdge::EdgeKind::NestedSubtree;
        } else {
            edge->kind = MapEdge::EdgeKind::NestedStatementElement;
        }
        auto attr = std::make_shared<MapEdgeProp>();
        state->graph->addEdge(edge, attr, parent.value(), vertex);
    }

    return vertex;
}

void add_node_rec_aux(
    org::graph::MapGraphState*         state,
    ImmAdapter const&                  node,
    hstd::Opt<hgraph::VertexID> const& parent,
    std::shared_ptr<MapConfig> const&  conf,
    hstd::Opt<MapEdge::EdgeKind>       edge_override = std::nullopt) {
    TRACE_COUNTER("graph", "visited_nodes", ++state->counters.visited_node_counter);

    auto __tmp = state->graph->begin_scope(
        state->graph->fmt_message("recursive add {}", node), std::nullopt, "addNodeRec");

    switch (node->getKind()) {
        case OrgSemKind::File:
        case OrgSemKind::Directory:
        case OrgSemKind::Symlink:
        case OrgSemKind::Document:
        case OrgSemKind::CmdInclude:
        case OrgSemKind::Subtree:
        case OrgSemKind::List: {
            auto added = add_single_node(state, node, parent, conf);
            for (auto const& it : node) { add_node_rec_aux(state, it, added, conf); }
            break;
        }
        case OrgSemKind::ListItem: {
            auto item  = node.as<ImmListItem>();
            auto added = add_single_node(state, node, parent, conf);
            if (item.isDescriptionItem()) {
                add_node_rec_aux(
                    state,
                    item.getHeader().value(),
                    added,
                    conf,
                    MapEdge::EdgeKind::DescriptionListHead);
            }
            for (auto const& it : node) { add_node_rec_aux(state, it, added, conf); }
            break;
        }
        case OrgSemKind::Paragraph: {
            std::ignore = add_single_node(state, node, parent, conf);
            break;
        }
        default: {
        }
    }
}

} // namespace

void org::graph::MapGraphState::addNodeRec(
    std::shared_ptr<org::imm::ImmAstContext> const& ast,
    org::imm::ImmAdapter const&                     node,
    std::shared_ptr<MapConfig> const&               conf) {
    add_node_rec_aux(this, node, std::nullopt, conf);
}


Opt<MapLink> org::graph::MapGraphState::getUnresolvedLink(
    org::imm::ImmAdapterT<org::imm::ImmLink> link) const {
    if (SkipLinks.contains(link->target.getKind())) {
        return std::nullopt;
    } else {
        return MapLink{MapLink::Link{
            .link = link.uniq(),
            .description //
            = link->description.get()
                ? Vec{link.at(link->description.get().value().toId(),
                              ImmSubnodeAccessStep::FieldDeref(
                                  ImmReflFieldId::FromTypeField(&ImmLink::description)))
                          .uniq()}
                : Vec<ImmUniqId>{},
        }};
    }
}

#if ORG_BUILD_WITH_PROTOBUF
void org::graph::MapNode::writeSerial(
    hgraph::proto::IVertex* out,
    hgraph::IGraph const*   graph,
    hgraph::VertexID const& self_id) const {
    IVertex::writeSerial(out, graph, self_id);
    out->set_type("org::graph::MapNode");
    proto::MapNodePayload payload;

    hstd::serde::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        payload.mutable_node(), org::imm::sem_from_immer(id.id, *id.ctx.lock()));

    out->mutable_payload()->PackFrom(payload);
}
#endif


std::shared_ptr<MapGraphState> org::graph::initMapGraphState(
    std::shared_ptr<org::imm::ImmAstContext> ast) {
    return MapGraphState::FromAstContext(ast);
}

#if ORG_BUILD_WITH_PROTOBUF
void org::graph::MapEdge::readSerial(
    hstd::ext::graph::proto::IEdge const*        in,
    hstd::ext::graph::IGraph const*              graph,
    hstd::ext::graph::IGraphSerialReaderFactory* factory) {
    throw hstd::ext::graph::serde_error::init(
        "imm org map graph does not support de-serialization, build "
        "immutable AST context and build the graph from it.");
}

void org::graph::MapEdge::writeSerial(
    hstd::ext::graph::proto::IEdge* out,
    hstd::ext::graph::IGraph const* graph,
    hstd::ext::graph::EdgeID const& self_id) const {
    IEdge::writeSerial(out, graph, self_id);
    proto::MapEdgePayload payload;
    payload.set_kind(static_cast<proto::MapEdgePayload::EdgeKind>(kind));

    out->mutable_payload()->PackFrom(payload);
}
#endif

Vec<MapLinkResolveResult> org::graph::getResolveTarget(
    MapGraphState::Ptr const&  state,
    hgraph::VertexID const&    source,
    MapLink const&             link,
    std::shared_ptr<MapConfig> conf) {
    auto g = state->graph;
    OP_TRACER_MESSAGE(g, "Get resolve targets {} {}", source, link);

    Vec<MapLinkResolveResult> result;

    if (link.isRadio()) {
        // Unresolved radio link already contains all the information for
        // creating edge. This only happens when the node itself has not
        // been added to the graph.
        result.push_back(
            MapLinkResolveResult{
                .link   = link,
                .target = link.getRadio().target,
                .source = g->getImmID(source),
            });
    } else {
        OP_TRACER_MESSAGE(
            g,
            "footnotes {} subtrees {} names {}",
            state->ast->currentTrack->footnotes,
            state->ast->currentTrack->subtrees,
            state->ast->currentTrack->names);

        auto add_edge = [&](imm::ImmId const& target) {
            auto adapters = state->getAdaptersFor(target);
            LOGIC_ASSERTION_CHECK_FMT(
                !adapters.empty(),
                "Target node {} does not have any parent adapters tracked",
                target);

            for (auto const& full : adapters) {
                result.push_back(
                    MapLinkResolveResult{
                        .link   = link,
                        .target = full.uniq(),
                        .source = g->getImmID(source),
                    });
            }
        };

        MapLink::Link const& spec         = link.getLink();
        auto                 link_adapter = state->ast->adapt(spec.link).as<ImmLink>();
        switch (link_adapter->target.getKind()) {
            case slk::Id: {
                auto text = link_adapter->target.getId().text;
                if (auto target = state->ast->currentTrack->subtrees.get(text)) {
                    OP_TRACER_MESSAGE(
                        g, "Subtree ID {} on {} resolved to {}", text, source, *target);
                    add_edge(*target);
                } else {
                    OP_TRACER_MESSAGE(g, "Not subtree with ID {}", text);
                }
                break;
            }

            case slk::CustomId: {
                auto text = link_adapter->target.getCustomId().text;
                if (auto target = state->ast->currentTrack->customIds.get(text)) {
                    OP_TRACER_MESSAGE(
                        g,
                        "Subtree custom ID {} on {} resolved to {}",
                        text,
                        source,
                        *target);
                    add_edge(*target);
                } else {
                    OP_TRACER_MESSAGE(g, "Not subtree with custom ID {}", text);
                }
                break;
            }

            case slk::Footnote: {
                Str const& text = link_adapter->target.getFootnote().target;
                if (auto target = state->ast->currentTrack->footnotes.get(text)) {
                    OP_TRACER_MESSAGE(
                        g,
                        "Footnote name {} on {} resolved to {}",
                        text,
                        source,
                        *target);
                    add_edge(*target);
                } else {
                    OP_TRACER_MESSAGE(g, "No footnote with ID {}", text);
                }
                break;
            }

            case slk::Internal: {
                Str const& text = link_adapter->target.getInternal().target;
                if (auto target = state->ast->currentTrack->names.get(text)) {
                    OP_TRACER_MESSAGE(
                        g,
                        "Internal link name '{}' on '{}' resolved to "
                        "named node '{}'",
                        text,
                        source,
                        *target);
                    add_edge(*target);
                } else {
                    OP_TRACER_MESSAGE(g, "No internal link with ID '{}'", text);
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
                    hstd::fmt(
                        "Unhandled link kind '{}'", link_adapter->target.getKind()));
            }
        }
    }


    return result;
}

#if ORG_BUILD_WITH_PROTOBUF
void org::graph::MapEdgeCollection::writeSerial(
    hstd::ext::graph::proto::IEdgeCollection* out,
    hstd::ext::graph::IGraph const*           graph) const {
    IEdgeCollection::writeSerial(out, graph);
    proto::MapEdgeCollectionPayload tag;
    out->mutable_payload()->PackFrom(tag);
}

void org::graph::MapEdgeCollection::readSerial(
    hstd::ext::graph::proto::IEdgeCollection const* in,
    hstd::ext::graph::IGraph const*                 graph,
    hstd::ext::graph::IGraphSerialReaderFactory*    factory) {
    IEdgeCollection::readSerial(in, graph, factory);
}

#endif
