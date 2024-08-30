#pragma once

#include <haxorg/sem/ImmOrg.hpp>
#include <immer/set.hpp>
#include <hstd/stdlib/TraceBase.hpp>

template <typename T>
using ImmSet = immer::set<T>;

namespace org::graph {

struct graph_error : CRTP_hexception<graph_error> {};

struct MapLink {
    /// \brief Original link used to create the graph edge. Used to return
    /// an edge to unresolved state when target is deleted. When source is
    /// deleted the edge is simply dropped.
    org::ImmId link;
    /// MapLink description field can be reused or, for description list
    /// items, this field contains a newly created statment list
    Opt<org::ImmId> description;
    DESC_FIELDS(MapLink, (link, description));
};


struct MapNodeProp {
    Vec<MapLink> unresolved;
    DESC_FIELDS(MapNodeProp, (unresolved));
};

struct MapEdgeProp {
    MapLink link;
    DESC_FIELDS(MapEdgeProp, (link));
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

struct MapGraphTransient {
    NodeProps::transient_type& nodeProps;
    EdgeProps::transient_type& edgeProps;
    AdjList::transient_type&   adjList;
};

struct MapGraph {
    org::ContextStore* ctx;
    NodeProps          nodeProps;
    EdgeProps          edgeProps;
    AdjList            adjList;
};

struct MapResolvedLink {
    MapLink link;
    MapNode target;
    MapNode source;
    DESC_FIELDS(MapResolvedLink, (link, target, source));
};

struct MapResolveResult {
    Vec<MapNode>         unresolved;
    Vec<MapResolvedLink> resolved;
    DESC_FIELDS(MapResolveResult, (unresolved, resolved));
};

struct MapOpsConfig : OperationsTracer {};

struct MapGraphState {
    ImmSet<MapNode> unresolved;
    MapGraph        graph;
};

MapGraphState addNode(
    MapGraphState const& g,
    org::ImmId           node,
    MapOpsConfig&        conf);

Opt<MapNodeProp> getNodeInsert(
    MapGraphState const& s,
    org::ImmId           node,
    MapOpsConfig&        conf);

} // namespace org::graph
