#pragma once

#include <haxorg/sem/ImmOrg.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <immer/map_transient.hpp>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>
#include <boost/graph/graph_traits.hpp>

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

    Opt<Str> getSubtreeId() const {
        if (auto tree = id.asOpt<org::ImmSubtree>();
            tree && tree.value()->treeId.get()) {
            return tree.value()->treeId->value();
        } else {
            return std::nullopt;
        }
    }

    Opt<Str> getFootnoteName() const {
        if (auto par = id.asOpt<org::ImmAnnotatedParagraph>();
            par
            && par->get()->getAnnotationKind()
                   == org::ImmAnnotatedParagraph::AnnotationKind::
                       Footnote) {
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

    MapNode(org::ImmId id) : id{id} {}
    MapNode(org::ImmAdapter id) : id{id.id} {}

    bool operator==(MapNode const& other) const {
        return this->id == other.id;
    }

    DESC_FIELDS(MapNode, (id));
};

struct MapEdge {
    MapNode source;
    MapNode target;
    DESC_FIELDS(MapEdge, (source, target));

    bool operator==(MapEdge const& other) const {
        return this->source == other.source
            && this->target == other.target;
    }
};
} // namespace org::graph


template <typename T>
inline void hax_hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


template <>
struct std::hash<org::graph::MapNode> {
    std::size_t operator()(org::graph::MapNode const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.id);
        return result;
    }
};


template <>
struct std::hash<org::graph::MapEdge> {
    std::size_t operator()(org::graph::MapEdge const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.source.id);
        hax_hash_combine(result, it.target.id);
        return result;
    }
};

namespace org::graph {
struct StructureUpdate {
    Vec<MapEdge> removed_edges;
    Vec<MapEdge> added_edges;
    Opt<MapNode> removed_node = std::nullopt;
    Opt<MapNode> added_node   = std::nullopt;

    DESC_FIELDS(
        StructureUpdate,
        (removed_edges, removed_node, added_edges, added_node));
};

using NodeProps    = immer::map<MapNode, MapNodeProp>;
using EdgeProps    = immer::map<MapEdge, MapEdgeProp>;
using AdjNodesList = immer::vector<MapNode>;
using AdjList      = immer::map<MapNode, AdjNodesList>;

struct MapGraph;

struct MapGraphTransient {
    NodeProps::transient_type nodeProps;
    EdgeProps::transient_type edgeProps;
    AdjList::transient_type   adjList;
    ContextStore*             store;

    MapGraphTransient(ContextStore* store) : store{store} {}

    MapGraph persistent();
};

struct MapGraph {
    NodeProps     nodeProps;
    EdgeProps     edgeProps;
    AdjList       adjList;
    ContextStore* store;

    MapGraph(ContextStore* store) : store{store} {}

    MapGraphTransient transient() const;

    int nodeCount() const { return nodeProps.size(); }
    int edgeCount() const { return edgeProps.size(); }

    MapNodeProp const& at(MapNode const& node) const {
        return nodeProps.at(node);
    }

    MapEdgeProp const& at(MapEdge const& edge) const {
        return edgeProps.at(edge);
    }

    bool hasEdge(MapNode const& source, MapNode const& target) {
        if (adjList.find(source) != nullptr) {
            for (auto const& it : adjList.at(source)) {
                if (it == target) { return true; }
            }
        }

        return false;
    }


    Graphviz::Graph toGraphviz() const;

    DESC_FIELDS(MapGraph, (nodeProps, edgeProps, adjList));
};


struct MapOpsConfig : OperationsTracer {
    int  activeLevel = 0;
    auto scopeLevel() {
        ++activeLevel;
        return finally{[&]() { --activeLevel; }};
    }

    auto scopeTrace(bool state) {
        TraceState = state;
        return finally{[state, this]() { TraceState = !state; }};
    }
};

struct MapGraphState {
    /// \brief List of nodes with unresolved outgoing links.
    ImmSet<MapNode> unresolved;
    /// \brief Lookup of the nodes by the footnote IDs
    ImmMap<Str, MapNode> footnoteTargets;
    /// \brief Loopup of the subtree targets by the subtree IDs
    ImmMap<Str, MapNode> subtreeTargets;
    MapGraph             graph;

    MapGraphState(ContextStore* store) : graph{store} {}

    DESC_FIELDS(
        MapGraphState,
        (unresolved, footnoteTargets, subtreeTargets, graph));
};

MapGraphState addNode(
    MapGraphState const& g,
    MapNodeProp const&   node,
    MapOpsConfig&        conf);

MapGraphState addNode(
    MapGraphState const&   g,
    org::ImmAdapter const& node,
    MapOpsConfig&          conf);

MapGraphState addNodeRec(
    MapGraphState const&   g,
    org::ImmAdapter const& node,
    MapOpsConfig&          conf);

/// \brief Get node properties without resolving the target links.
Opt<MapNodeProp> getUnresolvedNodeInsert(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapOpsConfig&        conf);


struct MapLinkResolveResult {
    MapLink           link;
    MapNode           target;
    MapNode           source;
    MapEdgeProp::Kind kind;
    DESC_FIELDS(MapLinkResolveResult, (link, target, source, kind));
};

/// \brief Resolve a single link with the state `s` and return the edge.
/// Use `source` as an edge origin.
Opt<MapLinkResolveResult> getResolveTarget(
    MapGraphState const& s,
    MapNode const&       source,
    MapLink const&       link,
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

namespace boost {

struct vector_as_graph_traversal_tag
    : public vertex_list_graph_tag
    , public adjacency_graph_tag
    , public incidence_graph_tag {};

struct map_graph_vertices_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = org::graph::MapNode;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    typename org::graph::NodeProps::const_iterator iter;

    map_graph_vertices_iterator() = default;
    map_graph_vertices_iterator(
        typename org::graph::NodeProps::const_iterator it)
        : iter(it) {}

    reference operator*() const { return iter->first; }
    pointer   operator->() const { return &(iter->first); }

    map_graph_vertices_iterator& operator++() {
        ++iter;
        return *this;
    }

    bool operator!=(const map_graph_vertices_iterator& other) const {
        return iter != other.iter;
    }
};

struct map_graph_adjacent_vertices_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = org::graph::MapNode;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    typename immer::vector<org::graph::MapNode>::const_iterator iter;

    map_graph_adjacent_vertices_iterator() = default;
    map_graph_adjacent_vertices_iterator(
        typename immer::vector<org::graph::MapNode>::const_iterator it)
        : iter(it) {}

    reference operator*() const { return *iter; }
    pointer   operator->() const { return &(*iter); }

    map_graph_adjacent_vertices_iterator& operator++() {
        ++iter;
        return *this;
    }

    bool operator!=(
        const map_graph_adjacent_vertices_iterator& other) const {
        return iter != other.iter;
    }
};

struct map_graph_out_edges_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = org::graph::MapEdge;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    org::graph::MapNode                               source;
    typename org::graph::AdjNodesList::const_iterator iter;

    map_graph_out_edges_iterator() : source{org::ImmId::Nil()} {};
    map_graph_out_edges_iterator(
        org::graph::MapNode const&                        source,
        typename org::graph::AdjNodesList::const_iterator it)
        : source{source}, iter{it} {}

    value_type operator*() const {
        return org::graph::MapEdge{source, *iter};
    }

    map_graph_out_edges_iterator& operator++() {
        ++iter;
        return *this;
    }

    bool operator!=(const map_graph_out_edges_iterator& other) const {
        return iter != other.iter;
    }
};

struct map_graph_edges_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = org::graph::MapEdge;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    typename org::graph::AdjList::const_iterator iter;
    int                                          outEdgeIndex = 0;

    map_graph_edges_iterator() {};
    map_graph_edges_iterator(
        typename org::graph::AdjList::const_iterator it)
        : iter{it} {}

    value_type operator*() const {
        return org::graph::MapEdge{
            iter->first, iter->second.at(outEdgeIndex)};
    }

    map_graph_edges_iterator& operator++() {
        ++iter;
        return *this;
    }

    bool operator!=(const map_graph_edges_iterator& other) const {
        return iter != other.iter;
    }
};

template <>
struct graph_traits<org::graph::MapGraph> {
    using vertex_descriptor      = org::graph::MapNode;
    using edge_descriptor        = org::graph::MapEdge;
    using adjacency_iterator     = map_graph_adjacent_vertices_iterator;
    using out_edge_iterator      = map_graph_out_edges_iterator;
    using in_edge_iterator       = void;
    using edge_iterator          = map_graph_edges_iterator;
    using vertex_iterator        = map_graph_vertices_iterator;
    using directed_category      = directed_tag;
    using edge_parallel_category = allow_parallel_edge_tag;
    using traversal_category     = vector_as_graph_traversal_tag;
    using vertices_size_type     = int;
    using edges_size_type        = int;
    using degree_size_type       = int;
};

template <>
struct edge_property_type<org::graph::MapGraph> {
    using type = org::graph::MapNodeProp;
};

template <>
struct vertex_property_type<org::graph::MapGraph> {
    using type = org::graph::MapEdgeProp;
};

template <>
struct graph_property_type<org::graph::MapGraph> {
    typedef void type;
};


inline std::pair<map_graph_vertices_iterator, map_graph_vertices_iterator> vertices(
    org::graph::MapGraph const& g) {
    return {
        map_graph_vertices_iterator(g.nodeProps.begin()),
        map_graph_vertices_iterator(g.nodeProps.end())};
}

inline std::pair<map_graph_edges_iterator, map_graph_edges_iterator> edges(
    org::graph::MapGraph const& g) {
    return {
        map_graph_edges_iterator(g.adjList.begin()),
        map_graph_edges_iterator(g.adjList.end()),
    };
}

inline std::pair<map_graph_adjacent_vertices_iterator, map_graph_adjacent_vertices_iterator> adjacent_vertices(
    org::graph::MapNode const&  v,
    org::graph::MapGraph const& g) {
    auto it = g.adjList.find(v);
    if (it != nullptr) {
        return {
            map_graph_adjacent_vertices_iterator(it->begin()),
            map_graph_adjacent_vertices_iterator(it->end()),
        };
    } else {
        return {
            map_graph_adjacent_vertices_iterator(),
            map_graph_adjacent_vertices_iterator(),
        };
    }
}

inline org::graph::MapNodeProp const& get(
    vertex_property_type<org::graph::MapGraph>::type,
    org::graph::MapGraph const& g,
    org::graph::MapNode const&  v) {
    return g.nodeProps.at(v);
}

inline org::graph::MapEdgeProp const& get(
    edge_property_type<org::graph::MapGraph>::type,
    org::graph::MapGraph const& g,
    org::graph::MapEdge const&  e) {
    return g.edgeProps.at(e);
}

inline int num_vertices(org::graph::MapGraph const& g) {
    return g.nodeCount();
}

inline int num_edges(org::graph::MapGraph const& g) {
    return g.edgeCount();
}

inline int out_degree(
    org::graph::MapNode const&  v,
    org::graph::MapGraph const& g) {
    auto it = g.adjList.find(v);
    return it != nullptr ? it->size() : 0;
}

inline std::pair<map_graph_out_edges_iterator, map_graph_out_edges_iterator> out_edges(
    org::graph::MapNode const&  v,
    org::graph::MapGraph const& g) {
    std::vector<org::graph::MapEdge> outEdges;
    auto                             it = g.adjList.find(v);
    if (it == nullptr) {
        return {
            map_graph_out_edges_iterator{},
            map_graph_out_edges_iterator{},
        };
    } else {
        return {
            map_graph_out_edges_iterator{v, it->begin()},
            map_graph_out_edges_iterator{v, it->end()},
        };
    }
}

inline org::graph::MapNode source(
    org::graph::MapEdge const& e,
    org::graph::MapGraph const&) {
    return e.source;
}

inline org::graph::MapNode target(
    org::graph::MapEdge const& e,
    org::graph::MapGraph const&) {
    return e.target;
}


} // namespace boost
