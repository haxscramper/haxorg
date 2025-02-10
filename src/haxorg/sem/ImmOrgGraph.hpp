#pragma once

#include <boost/graph/properties.hpp>
#include <haxorg/sem/ImmOrg.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <immer/map_transient.hpp>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>

namespace org::graph {

struct graph_error : CRTP_hexception<graph_error> {};

struct MapLink {
    struct Link {
        /// \brief Original link used to create the graph edge. Used to
        /// return an edge to unresolved state when target is deleted. When
        /// source is deleted the edge is simply dropped.
        org::ImmAdapterT<org::ImmLink> link;
        /// MapLink description field can be reused or, for description
        /// list items, this field contains a newly created statment list
        Vec<org::ImmAdapter> description;
        DESC_FIELDS(Link, (link, description));
    };

    /// \brief Unresolved radio link that was detected from AST context but
    /// the graph node has not been added yet.
    struct Radio {
        org::ImmAdapter target;
        DESC_FIELDS(Radio, (target));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, Radio, Link);
    Data data;
    DESC_FIELDS(MapLink, (data));
};


struct MapNodeProp {
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
        if (auto par = id.asOpt<org::ImmParagraph>();
            par && par->isFootnoteDefinition()) {
            return par->getFootnoteName();
        } else {
            return std::nullopt;
        }
    }

    DESC_FIELDS(MapNodeProp, (unresolved, id));
};

struct MapEdgeProp {
    MapLink link;
    DESC_FIELDS(MapEdgeProp, (link));
};


struct MapNode {
    org::ImmUniqId id;

    MapNode() : id{org::ImmUniqId()} {}
    MapNode(org::ImmUniqId id) : id{id} {}

    bool operator==(MapNode const& other) const {
        return this->id == other.id;
    }

    bool operator<(MapNode const& other) const { return id < other.id; }

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

using NodeProps    = UnorderedMap<MapNode, MapNodeProp>;
using EdgeProps    = UnorderedMap<MapEdge, MapEdgeProp>;
using AdjNodesList = Vec<MapNode>;
using AdjList      = UnorderedMap<MapNode, AdjNodesList>;

struct MapGraph;

struct MapGraph {
    NodeProps nodeProps;
    EdgeProps edgeProps;
    AdjList   adjList;
    AdjList   adjListIn;

    void clear() {
        nodeProps.clear();
        edgeProps.clear();
        adjList.clear();
        adjListIn.clear();
    }

    int nodeCount() const { return nodeProps.size(); }
    int edgeCount() const { return edgeProps.size(); }

    AdjNodesList const& outNodes(MapNode const& node) const {
        return adjList.at(node);
    }

    AdjNodesList const& inNodes(MapNode const& node) const {
        return adjListIn.at(node);
    }

    Vec<MapEdge> adjEdges(MapNode const& node) const {
        Vec<MapEdge> res;
        for (auto const& out : outNodes(node)) {
            res.push_back(MapEdge{.source = node, .target = out});
        }

        for (auto const& in : inNodes(node)) {
            res.push_back(MapEdge{.source = in, .target = node});
        }

        return res;
    }

    Vec<MapNode> adjNodes(MapNode const& node) const {
        UnorderedSet<org::graph::MapNode> adjacent;
        Vec<MapNode>                      result;
        for (auto const& node : outNodes(node)) {
            adjacent.incl(node);
            result.push_back(node);
        }

        for (auto const& n : inNodes(node)) {
            if (!adjacent.contains(n)) { result.push_back(n); }
        }
        return result;
    }

    Vec<MapEdge> outEdges(MapNode const& node) const {
        Vec<MapEdge> result;
        for (auto const& target : outNodes(node)) {
            result.push_back(MapEdge{node, target});
        }
        return result;
    }

    Vec<MapEdge> inEdges(MapNode const& node) const {
        Vec<MapEdge> result;
        for (auto const& target : inNodes(node)) {
            result.push_back(MapEdge{target, node});
        }
        return result;
    }

    int outDegree(MapNode const& node) const {
        return adjList.contains(node) ? adjList.at(node).size() : 0;
    }

    int inDegree(MapNode const& node) const {
        return adjListIn.contains(node) ? adjListIn.at(node).size() : 0;
    }

    bool isRegisteredNode(MapNode const& id) const {
        return adjList.contains(id);
    }

    bool isRegisteredNode(org::ImmUniqId const& id) const {
        return adjList.contains(MapNode{id});
    }

    MapNodeProp const& at(MapNode const& node) const {
        return nodeProps.at(node);
    }

    MapEdgeProp const& at(MapEdge const& edge) const {
        return edgeProps.at(edge);
    }


    void addEdge(MapEdge const& edge) { addEdge(edge, MapEdgeProp{}); }
    void addEdge(MapEdge const& edge, MapEdgeProp const& prop);
    /// \brief Add node to the graph, without registering any outgoing or
    /// ingoing elements.
    void addNode(MapNode const& node);
    void addNode(MapNode const& node, MapNodeProp const& prop) {
        addNode(node);
        nodeProps.insert_or_assign(node, prop);
    }

    bool hasEdge(MapNode const& source, MapNode const& target) const {
        if (adjList.find(source) != nullptr) {
            for (auto const& it : adjList.at(source)) {
                if (it == target) { return true; }
            }
        }

        return false;
    }

    bool hasNode(MapNode const& node) const {
        return adjList.contains(node);
    }

    bool hasEdge(
        org::ImmAdapter const& source,
        org::ImmAdapter const& target) const {
        return hasEdge(MapNode{source.uniq()}, MapNode{target.uniq()});
    }

    struct GvConfig {
        Func<bool(MapNode const& node)> acceptNode;
        Func<bool(MapEdge const& edge)> acceptEdge;

        static Graphviz::Node::Record getDefaultNodeLabel(
            org::ImmAdapter const& node,
            MapNodeProp const&     prop);
        Func<Graphviz::Node::Record(
            org::ImmAdapter const&,
            MapNodeProp const& prop)>
            getNodeLabel = getDefaultNodeLabel;
    };

    Graphviz::Graph toGraphviz(const ImmAstContext::Ptr& ctx) const {
        return toGraphviz(ctx, GvConfig{});
    }

    Graphviz::Graph toGraphviz(
        const ImmAstContext::Ptr& ctx,
        GvConfig const&           conf) const;

    DESC_FIELDS(MapGraph, (nodeProps, edgeProps, adjList));
};

struct MapGraphInverse {
    MapGraph* origin;

    AdjNodesList const& inNodes(MapNode const& n) const {
        return origin->outNodes(n);
    }

    AdjNodesList const& outNodes(MapNode const& n) const {
        return origin->inNodes(n);
    }

    Vec<MapEdge> inEdges(MapNode const& n) const {
        return origin->outEdges(n);
    }

    Vec<MapEdge> outEdges(MapNode const& n) const {
        return origin->inEdges(n);
    }

    Vec<MapNode> adjNodes(MapNode const& n) const {
        return origin->adjNodes(n);
    }
};

struct MapGraphUndirected {
    MapGraph*    origin;
    Vec<MapNode> adjNodes(MapNode const& n) const {
        return origin->adjNodes(n);
    }

    Vec<MapEdge> adjEdges(MapNode const& n) const {
        UnorderedSet<MapNode> adjacent;
        Vec<MapEdge>          res;
        for (auto const& out : origin->outNodes(n)) {
            res.push_back(MapEdge{.source = n, .target = out});
            adjacent.incl(out);
        }

        for (auto const& in : origin->inNodes(n)) {
            if (!adjacent.contains(in)) {
                res.push_back(MapEdge{.source = n, .target = in});
            }
        }
        return res;
    }
};

template <typename T>
concept IsOrgMapGraph //
    = std::is_same_v<std::remove_reference_t<T>, MapGraphUndirected>
   || std::is_same_v<std::remove_reference_t<T>, MapGraphInverse>
   || std::is_same_v<std::remove_reference_t<T>, MapGraph>;

struct MapGraphState;
struct MapConfig;

struct MapInterface {
    /// \brief Get node properties without resolving the target links.
    virtual Opt<MapNodeProp> getInitialNodeProp(
        MapGraphState const& s,
        org::ImmAdapter      node,
        MapConfig&           conf);
};

struct MapConfig
    : OperationsTracer
    , OperationsScope {
    SPtr<MapInterface> impl;
    MapConfig(SPtr<MapInterface> impl);
    MapConfig();

    Opt<MapNodeProp> getInitialNodeProp(
        MapGraphState const& s,
        org::ImmAdapter      node) {
        return impl->getInitialNodeProp(s, node, *this);
    }


    void message(
        std::string const& value,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE()) {
        OperationsTracer::message(
            value, activeLevel, line, function, file);
    }
};

struct MapGraphState {
    /// \brief List of nodes with unresolved outgoing links.
    UnorderedSet<MapNode> unresolved;
    MapGraph              graph;
    ImmAstContext::Ptr    ast;

    MapGraphState(ImmAstContext::Ptr ast) : ast{ast} {};

    DESC_FIELDS(MapGraphState, (unresolved, graph));
};

void registerNode(
    MapGraphState&     s,
    MapNodeProp const& node,
    MapConfig&         conf);

void addNode(
    MapGraphState&         g,
    org::ImmAdapter const& node,
    MapConfig&             conf);

void addNodeRec(
    MapGraphState&         g,
    org::ImmAdapter const& node,
    MapConfig&             conf);

Vec<MapLink> getUnresolvedSubtreeLinks(
    MapGraphState const&    s,
    ImmAdapterT<ImmSubtree> node,
    MapConfig&              conf);

Opt<MapLink> getUnresolvedLink(
    MapGraphState const& s,
    ImmAdapterT<ImmLink> node,
    MapConfig&           conf);

struct MapLinkResolveResult {
    MapLink link;
    /// \brief Target node for link resolution. Nodes are uniquely
    /// associated with the ImmUniqId, so the 'target' is always filled,
    /// but the node might not exist in the graph yet. If it does not
    /// exist, the node is added to 'unresolved' in the graph state.
    MapNode target;
    MapNode source;
    DESC_FIELDS(MapLinkResolveResult, (link, target, source));
};

/// \brief Resolve a single link with the state `s` and return the edge.
/// Use `source` as an edge origin.
Vec<MapLinkResolveResult> getResolveTarget(
    MapGraphState const& s,
    MapNode const&       source,
    MapLink const&       link,
    MapConfig&           conf);

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
    MapConfig&           conf);


bool isDescriptionItem(org::ImmAdapter const& node);
bool isLinkedDescriptionItemNode(org::ImmAdapter const& n);

bool isLinkedDescriptionItem(org::ImmAdapter const& n);
/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::ImmAdapter const& n);

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInSubtreeDescriptionList(ImmAdapter const& n);

bool isAttachedDescriptionList(ImmAdapter const& n);

bool hasGraphAnnotations(ImmAdapterT<ImmParagraph> const& par);
bool hasGraphAnnotations(ImmAdapterT<ImmSubtree> const& par);

bool isMmapIgnored(ImmAdapter const& n);

} // namespace org::graph
