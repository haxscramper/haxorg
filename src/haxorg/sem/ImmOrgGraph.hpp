#pragma once

#include <haxorg/sem/ImmOrg.hpp>
#include <immer/set.hpp>

template <typename T>
using ImmSet = immer::set<T>;

namespace org::graph {


struct ImmLink {
    /// \brief Original link used to create the graph edge. Used to return
    /// an edge to unresolved state when target is deleted. When source is
    /// deleted the edge is simply dropped.
    org::ImmId link;
    /// Link description field can be reused or, for description list
    /// items, this field contains a newly created statment list
    Opt<org::ImmId> description;
    DESC_FIELDS(ImmLink, (link, description));
};


struct ImmNodeProp {
    ImmVec<ImmLink> unresolved;
    DESC_FIELDS(ImmNodeProp, (unresolved));
};

struct ImmEdgeProp {
    ImmLink link;
    DESC_FIELDS(ImmEdgeProp, (link));
};

struct ImmNode {
    org::ImmId id;
    DESC_FIELDS(ImmNode, (id));
};

struct ImmEdge {
    ImmNode source;
    ImmNode target;
    DESC_FIELDS(ImmEdge, (source, target));
};

struct ImmStructureUpdate {
    Vec<ImmEdge> removed_edges;
    Vec<ImmEdge> added_edges;
    Opt<ImmNode> removed_node = std::nullopt;
    Opt<ImmNode> added_node   = std::nullopt;

    DESC_FIELDS(
        ImmStructureUpdate,
        (removed_edges, removed_node, added_edges, added_node));
};

using ImmNodeProps = immer::map<ImmNode, ImmNodeProp>;
using ImmEdgeProps = immer::map<ImmEdge, ImmEdgeProp>;
using ImmAdjList   = immer::map<ImmNode, immer::vector<ImmNode>>;

struct ImmTransient {
    ImmNodeProps::transient_type& nodeProps;
    ImmEdgeProps::transient_type& edgeProps;
    ImmAdjList::transient_type&   adjList;
};

struct ImmGraph {
    org::ContextStore* ctx;
    ImmNodeProps       nodeProps;
    ImmEdgeProps       edgeProps;
    ImmAdjList         adjList;
};

struct ResolvedLink {};

struct ImmResolveTarget {
    ImmNode           node;
    Vec<ResolvedLink> resolved;
    DESC_FIELDS(ImmResolveTarget, (node, resolved));
};

struct ImmState {
    ImmSet<ImmNode> unresolved;
    ImmGraph        graph;
};

ImmState addNode(ImmState const& g, org::ImmId);

} // namespace org::graph
