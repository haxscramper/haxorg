#pragma once
#if !ORG_BUILD_EMCC
#    include <boost/property_map/dynamic_property_map.hpp>
#    include <haxorg/imm/ImmOrgGraph.hpp>

#    include <boost/graph/graph_traits.hpp>
#    include <hstd/ext/graphwrap.hpp>

namespace boost {

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

template <typename T>
struct map_graph_buffered_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    hstd::Vec<T> buffer;
    int          index = 0;

    map_graph_buffered_iterator(int index = 0) : index{index} {}
    map_graph_buffered_iterator(hstd::Vec<T> const& buf, int index = 0)
        : buffer(buf), index{index} {}

    static std::pair<map_graph_buffered_iterator<T>, map_graph_buffered_iterator<T>> to_iterator_pair(
        hstd::Vec<T> const& buf) {
        return std::make_pair(
            map_graph_buffered_iterator<T>{buf},
            map_graph_buffered_iterator<T>{buf.size()});
    }

    reference operator*() const { return buffer.at(index); }
    pointer   operator->() const { return &(buffer.at(index)); }

    map_graph_buffered_iterator& operator++() {
        ++index;
        return *this;
    }

    map_graph_buffered_iterator operator++(int) {
        auto res = *this;
        operator++();
        return res;
    }

    bool operator==(const map_graph_buffered_iterator& other) const {
        return index == other.index;
    }

    bool operator!=(const map_graph_buffered_iterator& other) const {
        return index != other.index;
    }
};

namespace o_dtl {
using edge_buffer = map_graph_buffered_iterator<::org::graph::MapEdge>;
using node_buffer = map_graph_buffered_iterator<::org::graph::MapNode>;
} // namespace o_dtl

struct map_graph_edges_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = org::graph::MapEdge;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    org::graph::AdjList::const_iterator iter;
    org::graph::AdjList const*          fullList     = nullptr;
    int                                 outEdgeIndex = 0;

    map_graph_edges_iterator() {};
    map_graph_edges_iterator(
        org::graph::AdjList::const_iterator it,
        org::graph::AdjList const&          fullList)
        : iter{it}, fullList{&fullList} {
        while (iter != fullList.end() && iter->second.empty()) { ++iter; }
        outEdgeIndex = 0;
    }

    value_type operator*() const {
        return org::graph::MapEdge{
            iter->first, iter->second.at(outEdgeIndex)};
    }

    map_graph_edges_iterator operator++(int) {
        auto res = *this;
        operator++();
        return res;
    }

    map_graph_edges_iterator& operator++() {
        LOGIC_ASSERTION_CHECK(
            fullList != nullptr,
            "cannot increment iterator with empty full list");
        if (outEdgeIndex < iter->second.size() - 1) {
            ++outEdgeIndex;
        } else {
            ++iter;
            while (iter != fullList->end() && iter->second.empty()) {
                ++iter;
            }
            outEdgeIndex = 0;
        }

        return *this;
    }

    bool operator==(const map_graph_edges_iterator& other) const {
        return outEdgeIndex == other.outEdgeIndex && iter == other.iter;
    }

    bool operator!=(const map_graph_edges_iterator& other) const {
        return outEdgeIndex != other.outEdgeIndex || iter != other.iter;
    }
};

struct vector_as_graph_traversal_tag
    // can iterate over vertices
    : public vertex_list_graph_tag
    , public adjacency_graph_tag
    , public incidence_graph_tag
    // can iterate over edges
    , public edge_list_graph_tag
//
{};

struct map_graph_traits_common {
    using ItNodes = o_dtl::node_buffer;
    using ItEdges = map_graph_buffered_iterator<org::graph::MapEdge>;

    using vertex_descriptor      = org::graph::MapNode;
    using edge_descriptor        = org::graph::MapEdge;
    using adjacency_iterator     = ItNodes;
    using out_edge_iterator      = ItEdges;
    using in_edge_iterator       = ItEdges;
    using edge_iterator          = map_graph_edges_iterator;
    using vertex_iterator        = map_graph_vertices_iterator;
    using directed_category      = directed_tag;
    using edge_parallel_category = disallow_parallel_edge_tag;
    using traversal_category     = vector_as_graph_traversal_tag;
    using vertices_size_type     = int;
    using edges_size_type        = int;
    using degree_size_type       = int;
};

template <>
struct graph_traits<org::graph::MapGraph> : map_graph_traits_common {};

template <>
struct graph_traits<org::graph::MapGraphInverse>
    : map_graph_traits_common {};

template <>
struct graph_traits<org::graph::MapGraphUndirected>
    : map_graph_traits_common {
    using directed_category = undirected_tag;
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

inline std::pair<map_graph_vertices_iterator, map_graph_vertices_iterator> vertices(
    org::graph::MapGraphUndirected const& g) {
    return {
        map_graph_vertices_iterator(g.origin->nodeProps.begin()),
        map_graph_vertices_iterator(g.origin->nodeProps.end())};
}


inline std::pair<map_graph_edges_iterator, map_graph_edges_iterator> edges(
    org::graph::MapGraph const& g) {
    return {
        map_graph_edges_iterator{g.adjList.begin(), g.adjList},
        map_graph_edges_iterator{g.adjList.end(), g.adjList},
    };
}

inline std::pair<o_dtl::node_buffer, o_dtl::node_buffer> adjacent_vertices(
    org::graph::MapNode const&  v,
    org::graph::MapGraph const& g) {
    return o_dtl::node_buffer::to_iterator_pair(g.adjNodes(v));
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
    return it != nullptr ? it->second.size() : 0;
}

inline std::pair<o_dtl::edge_buffer, o_dtl::edge_buffer> out_edges(
    org::graph::MapNode const&  v,
    org::graph::MapGraph const& g) {
    return o_dtl::edge_buffer::to_iterator_pair(g.outEdges(v));
}

inline std::pair<o_dtl::edge_buffer, o_dtl::edge_buffer> out_edges(
    org::graph::MapNode const&         v,
    org::graph::MapGraphInverse const& g) {
    return o_dtl::edge_buffer::to_iterator_pair(g.outEdges(v));
}

inline std::pair<o_dtl::edge_buffer, o_dtl::edge_buffer> out_edges(
    org::graph::MapNode const&            v,
    org::graph::MapGraphUndirected const& g) {
    return o_dtl::edge_buffer::to_iterator_pair(g.adjEdges(v));
}

inline int out_degree(
    org::graph::MapNode const&            v,
    org::graph::MapGraphUndirected const& g) {
    return g.adjEdges(v).size();
}


inline std::pair<o_dtl::edge_buffer, o_dtl::edge_buffer> in_edges(
    org::graph::MapNode const&  v,
    org::graph::MapGraph const& g) {
    return o_dtl::edge_buffer::to_iterator_pair(g.inEdges(v));
}

template <org::graph::IsOrgMapGraph G>
inline org::graph::MapNode source(org::graph::MapEdge const& e, G const&) {
    return e.source;
}

template <org::graph::IsOrgMapGraph G>
inline org::graph::MapNode target(org::graph::MapEdge const& e, G const&) {
    return e.target;
}

template <typename Key, typename Value>
struct unordered_map_property_map {
    using key_type   = Key;
    using value_type = Value;
    using reference  = const Value&;
    using category   = boost::readable_property_map_tag;

    const hstd::UnorderedMap<Key, Value>& map_ref;

    unordered_map_property_map(const hstd::UnorderedMap<Key, Value>& map)
        : map_ref(map) {}

    reference operator[](const key_type& key) const {
        return map_ref.at(key);
    }
};

template <typename Key, typename Value>
unordered_map_property_map<Key, Value> make_unordered_map_property_map(
    const hstd::UnorderedMap<Key, Value>& map) {
    return unordered_map_property_map<Key, Value>(map);
}

template <typename Key, typename Value>
Value get(
    unordered_map_property_map<Key, Value> const& map,
    Key const&                                    key) {
    return map[key];
}


template <>
struct property_map<org::graph::MapGraph, vertex_index_t> {
    using const_type = unordered_map_property_map<
        org::graph::MapNode,
        org::graph::MapNodeProp>;
    using type = const_type;
};

inline property_map<org::graph::MapGraph, vertex_index_t>::const_type get(
    vertex_index_t,
    org::graph::MapGraph const& g) {
    return make_unordered_map_property_map(g.nodeProps);
}

template <>
struct property_map<org::graph::MapGraph, vertex_bundle_t> {
    using const_type = unordered_map_property_map<
        org::graph::MapNode,
        org::graph::MapNodeProp>;
    using type = const_type;
};

inline property_map<org::graph::MapGraph, vertex_bundle_t>::const_type get(
    vertex_bundle_t,
    org::graph::MapGraph const& g) {
    return make_unordered_map_property_map(g.nodeProps);
}


struct map_vertex_identity_map {
    using key_type   = org::graph::MapNode;
    using value_type = org::graph::MapNode;
    using reference  = const org::graph::MapNode&;
    using category   = boost::readable_property_map_tag;

    reference operator[](key_type const& key) const { return key; }
};

inline map_vertex_identity_map make_map_vertex_identity_map() {
    return map_vertex_identity_map{};
}

inline org::graph::MapNode get(
    map_vertex_identity_map const& map,
    org::graph::MapNode const&     key) {
    return map[key];
}


} // namespace boost

namespace org::graph {

// to fix ADL lookup issues that some boost graph code suffers from. In
// some places these methods are called as simply `func()`, and not
// `boost::func()`, which leads to a failing attempt to look up via ADL
using boost::edges;
using boost::in_edges;
using boost::num_edges;
using boost::num_vertices;
using boost::out_degree;
using boost::out_edges;
using boost::source;
using boost::target;
using boost::vertices;

template <typename Graph>
struct boost_color_property_map_bundle {
    using vertex_descriptor = typename boost::graph_traits<
        Graph>::vertex_descriptor;
    using ColorStorage = std::
        unordered_map<vertex_descriptor, boost::default_color_type>;
    using ColorMap = boost::associative_property_map<ColorStorage>;

    boost_color_property_map_bundle(Graph const& g)
        : colors{}, map{colors} {
        // Pre-populate with white if needed
        for (auto vd : boost::make_iterator_range(boost::vertices(g))) {
            colors[vd] = boost::white_color;
        }
    }

    ColorStorage colors;
    ColorMap     map;
};


boost::dynamic_properties toGraphvizDynamicProperties(MapGraph const& g);

template <org::graph::IsOrgMapGraph OrgGraphT>
void bfs_visit(
    OrgGraphT const&                                      g,
    MapNode const&                                        start,
    hstd::ext::boost_lambda_bfs_visitor<OrgGraphT> const& visitor,
    boost_color_property_map_bundle<OrgGraphT> const&     map) {
    boost::breadth_first_search(
        g, start, boost::visitor(visitor).color_map(map.map));
}

template <org::graph::IsOrgMapGraph OrgGraphT>
inline void bfs_visit(
    OrgGraphT const&                                      g,
    MapNode const&                                        start,
    hstd::ext::boost_lambda_bfs_visitor<OrgGraphT> const& visitor) {
    boost_color_property_map_bundle<OrgGraphT> map{g};
    bfs_visit(g, start, visitor, map);
}

template <org::graph::IsOrgMapGraph OrgGraphT>
void dfs_visit(
    OrgGraphT const&                                      g,
    MapNode const&                                        start,
    hstd::ext::boost_lambda_dfs_visitor<OrgGraphT> const& visitor,
    boost_color_property_map_bundle<OrgGraphT> const&     map) {
    boost::breadth_first_search(
        g, start, boost::visitor(visitor).color_map(map.map));
}

template <org::graph::IsOrgMapGraph OrgGraphT>
inline void dfs_visit(
    OrgGraphT const&                                      g,
    MapNode const&                                        start,
    hstd::ext::boost_lambda_dfs_visitor<OrgGraphT> const& visitor) {
    boost_color_property_map_bundle<OrgGraphT> map{g};
    dfs_visit(g, start, visitor, map);
}

} // namespace org::graph

#endif
