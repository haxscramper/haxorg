#pragma once

#include <boost/graph/properties.hpp>
#include <haxorg/sem/ImmOrg.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <immer/map_transient.hpp>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>

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

    DESC_FIELDS(MapNodeProp, (unresolved, id));
};

struct MapEdgeProp {
    DECL_DESCRIBED_ENUM(Kind, SubtreeId, Footnote);
    Kind    kind;
    MapLink link;
    DESC_FIELDS(MapEdgeProp, (link, kind));
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


    Graphviz::Graph toGraphviz(const ImmAstContext& ctx) const;

    DESC_FIELDS(MapGraph, (nodeProps, edgeProps, adjList));
};

struct MapGraphState;

struct MapConfig
    : OperationsTracer
    , OperationsScope {
    MapConfig();

    Func<Opt<MapNodeProp>(
        MapGraphState const& s,
        org::ImmAdapter      node,
        MapConfig&           conf)>
        getUnresolvedNodeInsertImpl;

    Opt<MapNodeProp> getUnresolvedNodeInsert(
        MapGraphState const& s,
        org::ImmAdapter      node) {
        return getUnresolvedNodeInsertImpl(s, node, *this);
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
    ImmAstContext         ast;

    MapGraphState(ImmAstContext const& ast) : ast{ast} {};

    DESC_FIELDS(MapGraphState, (unresolved, graph));
};

void addNode(MapGraphState& g, MapNodeProp const& node, MapConfig& conf);

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

/// \brief Get node properties without resolving the target links.
Opt<MapNodeProp> getUnresolvedNodeInsertDefault(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapConfig&           conf);


struct MapLinkResolveResult {
    MapLink link;
    /// \brief Target node for link resolution. If resolution fails the
    /// link is set to nullopt.
    Opt<MapNode>      target;
    MapNode           source;
    MapEdgeProp::Kind kind;
    DESC_FIELDS(MapLinkResolveResult, (link, target, source, kind));
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


bool isDescriptionItem(org::ImmAdapter node);
bool isLinkedDescriptionItemNode(org::ImmAdapter n);

bool isLinkedDescriptionItem(org::ImmAdapter n);
/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::ImmAdapter n);

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInLinkedDescriptionList(org::ImmAdapter n);

bool isMmapIgnored(org::ImmAdapter n);

} // namespace org::graph
