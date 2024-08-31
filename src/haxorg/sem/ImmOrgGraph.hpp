#pragma once

#include <haxorg/sem/ImmOrg.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <immer/map_transient.hpp>


namespace org::graph {

struct graph_error : CRTP_hexception<graph_error> {};

struct MapLink {
    /// \brief Original link used to create the graph edge. Used to return
    /// an edge to unresolved state when target is deleted. When source is
    /// deleted the edge is simply dropped.
    org::ImmAdapterT<org::ImmLink> link;
    /// MapLink description field can be reused or, for description list
    /// items, this field contains a newly created statment list
    Vec<org::ImmAdapter> description;
    DESC_FIELDS(MapLink, (link, description));
};


struct MapNodeProp {
    DECL_DESCRIBED_ENUM(
        Kind,
        Subtree,
        Document,
        Paragraph,
        Footnote,
        List,
        ListItem);

    Kind            kind;
    org::ImmAdapter id;
    Vec<MapLink>    unresolved;

    MapNodeProp() {}

    Opt<Str> getSubtreeId() const {
        if (auto tree = id.asOpt<org::ImmSubtree>();
            tree.value()->treeId.get()) {
            return tree.value()->treeId->value();
        } else {
            return std::nullopt;
        }
    }

    Opt<Str> getFootnoteName() const {
        if (auto par = id.asOpt<org::ImmAnnotatedParagraph>();
            par->get()->getAnnotationKind()
            == org::ImmAnnotatedParagraph::AnnotationKind::Footnote) {
            // return par->getFootnote().name;
            logic_todo_impl();
        } else {
            return std::nullopt;
        }
    }

    DESC_FIELDS(MapNodeProp, (unresolved, id, kind));
};

struct MapEdgeProp {
    DECL_DESCRIBED_ENUM(Kind, SubtreeId, Footnote);
    Kind    kind;
    MapLink link;
    DESC_FIELDS(MapEdgeProp, (link, kind));
};

struct MapNode {
    org::ImmId id;
    DESC_FIELDS(MapNode, (id));
};

struct MapEdge {
    MapNode source;
    MapNode target;
    DESC_FIELDS(MapEdge, (source, target));
};

struct StructureUpdate {
    Vec<MapEdge> removed_edges;
    Vec<MapEdge> added_edges;
    Opt<MapNode> removed_node = std::nullopt;
    Opt<MapNode> added_node   = std::nullopt;

    DESC_FIELDS(
        StructureUpdate,
        (removed_edges, removed_node, added_edges, added_node));
};

using NodeProps = immer::map<MapNode, MapNodeProp>;
using EdgeProps = immer::map<MapEdge, MapEdgeProp>;
using AdjList   = immer::map<MapNode, immer::vector<MapNode>>;

struct MapGraph;

struct MapGraphTransient {
    NodeProps::transient_type nodeProps;
    EdgeProps::transient_type edgeProps;
    AdjList::transient_type   adjList;

    MapGraph persistent();
};

struct MapGraph {
    NodeProps nodeProps;
    EdgeProps edgeProps;
    AdjList   adjList;

    MapGraphTransient transient() const;
};

struct MapLinkResolveResult {
    MapLink link;
    MapNode target;
    MapNode source;
    DESC_FIELDS(MapLinkResolveResult, (link, target, source));
};

struct MapOpsConfig : OperationsTracer {};

struct MapGraphState {
    ImmSet<MapNode>      unresolved;
    ImmMap<Str, MapNode> footnoteTargets;
    ImmMap<Str, MapNode> subtreeTargets;
    MapGraph             graph;
};

MapGraphState addNode(
    MapGraphState const& g,
    MapNodeProp const&   node,
    MapOpsConfig&        conf);

/// \brief Get node properties without resolving the target links.
Opt<MapNodeProp> getUnresolvedNodeInsert(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapOpsConfig&        conf);

struct MapNodeResolveResult {
    MapNodeProp               node = MapNodeProp{};
    Vec<MapLinkResolveResult> resolved;
    DESC_FIELDS(MapNodeResolveResult, (node, resolved));
};

/// \brief Attempt to resolve links in the initial insert and split the
/// graph links into `.node.unresolved` and `.resolved` fields of the
/// returned.
MapNodeResolveResult getResolvedNodeInsert(
    MapGraphState const& s,
    MapNodeProp const&   node,
    MapOpsConfig&        conf);

} // namespace org::graph
