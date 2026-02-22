#pragma once
#if !ORG_BUILD_EMCC
#    include <boost/graph/properties.hpp>
#endif
#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <immer/map_transient.hpp>
#if !ORG_BUILD_EMCC
#    include <hstd/ext/graphviz.hpp>
#endif

namespace org::graph {

struct graph_error : hstd::CRTP_hexception<graph_error> {};

struct [[refl]] MapLink {
    struct [[refl]] Link {
        /// \brief Original link used to create the graph edge. Used to
        /// return an edge to unresolved state when target is deleted. When
        /// source is deleted the edge is simply dropped.
        [[refl]] org::imm::ImmUniqId link;
        /// MapLink description field can be reused or, for description
        /// list items, this field contains a newly created statment list
        [[refl]] hstd::Vec<org::imm::ImmUniqId> description;
        DESC_FIELDS(Link, (link, description));
    };

    /// \brief Unresolved radio link that was detected from AST context but
    /// the graph node has not been added yet.
    struct [[refl]] Radio {
        [[refl]] org::imm::ImmUniqId target;
        DESC_FIELDS(Radio, (target));
    };

    SUB_VARIANTS_REFL(Kind, Data, data, getKind, Radio, Link);
    Data data;
    DESC_FIELDS(MapLink, (data));
};


struct [[refl]] MapNodeProp {
    [[refl]] org::imm::ImmUniqId id;
    [[refl]] hstd::Vec<MapLink>  unresolved;

    [[refl]] org::imm::ImmAdapter getAdapter(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const {
        return context->adapt(id);
    }

    [[refl]] hstd::Opt<hstd::Str> getSubtreeId(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const {
        if (auto tree = getAdapter(context).asOpt<org::imm::ImmSubtree>();
            tree && tree.value()->treeId.get()) {
            return tree.value()->treeId->value();
        } else {
            return std::nullopt;
        }
    }

    [[refl]] hstd::Opt<hstd::Str> getFootnoteName(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const;

    DESC_FIELDS(MapNodeProp, (unresolved, id));
};

struct [[refl]] MapEdgeProp {
    [[refl]] MapLink link;
    DESC_FIELDS(MapEdgeProp, (link));
};


struct [[refl]] MapNode {
    [[refl]] org::imm::ImmUniqId id;

    MapNode() : id{org::imm::ImmUniqId()} {}
    MapNode(org::imm::ImmUniqId id) : id{id} {}

    [[refl]] bool operator==(MapNode const& other) const {
        return this->id == other.id;
    }

    [[refl]] bool operator<(MapNode const& other) const {
        return id < other.id;
    }

    DESC_FIELDS(MapNode, (id));
};

struct [[refl]] MapEdge {
    [[refl]] MapNode source;
    [[refl]] MapNode target;
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
        hstd::hax_hash_combine(result, it.id);
        return result;
    }
};


template <>
struct std::hash<org::graph::MapEdge> {
    std::size_t operator()(org::graph::MapEdge const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.source.id);
        hstd::hax_hash_combine(result, it.target.id);
        return result;
    }
};

namespace org::graph {
[[refl]] typedef hstd::UnorderedMap<MapNode, MapNodeProp>  NodeProps;
[[refl]] typedef hstd::UnorderedMap<MapEdge, MapEdgeProp>  EdgeProps;
[[refl]] typedef hstd::Vec<MapNode>                        AdjNodesList;
[[refl]] typedef hstd::UnorderedMap<MapNode, AdjNodesList> AdjList;

struct MapGraph;

struct [[refl(
    R"({
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    }
  }
})")]] MapGraph : hstd::SharedPtrApi<MapGraph> {
    [[refl]] NodeProps nodeProps;
    [[refl]] EdgeProps edgeProps;
    [[refl]] AdjList   adjList;
    [[refl]] AdjList   adjListIn;

    DESC_FIELDS(MapGraph, (nodeProps, edgeProps, adjList, adjListIn));

    void clear() {
        nodeProps.clear();
        edgeProps.clear();
        adjList.clear();
        adjListIn.clear();
    }

    [[refl]] int nodeCount() const { return nodeProps.size(); }
    [[refl]] int edgeCount() const { return edgeProps.size(); }

    [[refl]] AdjNodesList const& outNodes(MapNode const& node) const {
        return adjList.at(node);
    }

    [[refl]] AdjNodesList const& inNodes(MapNode const& node) const {
        return adjListIn.at(node);
    }

    [[refl]] hstd::Vec<MapEdge> adjEdges(MapNode const& node) const {
        hstd::Vec<MapEdge> res;
        for (auto const& out : outNodes(node)) {
            res.push_back(MapEdge{.source = node, .target = out});
        }

        for (auto const& in : inNodes(node)) {
            res.push_back(MapEdge{.source = in, .target = node});
        }

        return res;
    }

    [[refl]] hstd::Vec<MapNode> adjNodes(MapNode const& node) const {
        hstd::UnorderedSet<org::graph::MapNode> adjacent;
        hstd::Vec<MapNode>                      result;
        for (auto const& node : outNodes(node)) {
            adjacent.incl(node);
            result.push_back(node);
        }

        for (auto const& n : inNodes(node)) {
            if (!adjacent.contains(n)) { result.push_back(n); }
        }
        return result;
    }

    [[refl]] hstd::Vec<MapEdge> outEdges(MapNode const& node) const {
        hstd::Vec<MapEdge> result;
        for (auto const& target : outNodes(node)) {
            result.push_back(MapEdge{node, target});
        }
        return result;
    }

    [[refl]] hstd::Vec<MapEdge> inEdges(MapNode const& node) const {
        hstd::Vec<MapEdge> result;
        for (auto const& target : inNodes(node)) {
            result.push_back(MapEdge{target, node});
        }
        return result;
    }

    [[refl]] int outDegree(MapNode const& node) const {
        return adjList.contains(node) ? adjList.at(node).size() : 0;
    }

    [[refl]] int inDegree(MapNode const& node) const {
        return adjListIn.contains(node) ? adjListIn.at(node).size() : 0;
    }

    [[refl]] bool isRegisteredNode(MapNode const& id) const {
        return adjList.contains(id);
    }

    [[refl(R"({"unique-name": "isRegisteredNodeById"})")]] bool isRegisteredNode(
        org::imm::ImmUniqId const& id) const {
        return adjList.contains(MapNode{id});
    }

    [[refl(R"({"unique-name": "atMapNode"})")]] MapNodeProp const& at(
        MapNode const& node) const {
        return nodeProps.at(node);
    }

    [[refl(R"({"unique-name": "atMapEdge"})")]] MapEdgeProp const& at(
        MapEdge const& edge) const {
        return edgeProps.at(edge);
    }


    [[refl]] void addEdge(MapEdge const& edge) {
        addEdge(edge, MapEdgeProp{});
    }
    [[refl(R"({"unique-name": "addEdgeWithProp"})")]] void addEdge(
        MapEdge const&     edge,
        MapEdgeProp const& prop);
    /// \brief Add node to the graph, without registering any outgoing or
    /// ingoing elements.
    [[refl]] void addNode(MapNode const& node);
    [[refl(R"({"unique-name": "addNodeWithProp"})")]] void addNode(
        MapNode const&     node,
        MapNodeProp const& prop) {
        addNode(node);
        nodeProps.insert_or_assign(node, prop);
    }

    [[refl]] bool hasEdge(MapNode const& source, MapNode const& target)
        const {
        if (adjList.find(source) != adjList.end()) {
            for (auto const& it : adjList.at(source)) {
                if (it == target) { return true; }
            }
        }

        return false;
    }

    [[refl]] bool hasNode(MapNode const& node) const {
        return adjList.contains(node);
    }

    [[refl(R"({"unique-name": "has2AdapterEdge"})")]] bool hasEdge(
        org::imm::ImmAdapter const& source,
        org::imm::ImmAdapter const& target) const {
        return hasEdge(MapNode{source.uniq()}, MapNode{target.uniq()});
    }

#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH
    struct GvConfig {
        hstd::Func<bool(MapNode const& node)> acceptNode;
        hstd::Func<bool(MapEdge const& edge)> acceptEdge;

        static hstd::ext::Graphviz::Node::Record getDefaultNodeLabel(
            org::imm::ImmAdapter const& node,
            MapNodeProp const&          prop);
        hstd::Func<hstd::ext::Graphviz::Node::Record(
            org::imm::ImmAdapter const&,
            MapNodeProp const& prop)>
            getNodeLabel = getDefaultNodeLabel;
    };

    hstd::ext::Graphviz::Graph toGraphviz(
        const org::imm::ImmAstContext::Ptr& ctx) const {
        return toGraphviz(ctx, GvConfig{});
    }

    hstd::ext::Graphviz::Graph toGraphviz(
        const org::imm::ImmAstContext::Ptr& ctx,
        GvConfig const&                     conf) const;
#endif
};

struct MapGraphInverse {
    MapGraph::Ptr origin;

    AdjNodesList const& inNodes(MapNode const& n) const {
        return origin->outNodes(n);
    }

    AdjNodesList const& outNodes(MapNode const& n) const {
        return origin->inNodes(n);
    }

    hstd::Vec<MapEdge> inEdges(MapNode const& n) const {
        return origin->outEdges(n);
    }

    hstd::Vec<MapEdge> outEdges(MapNode const& n) const {
        return origin->inEdges(n);
    }

    hstd::Vec<MapNode> adjNodes(MapNode const& n) const {
        return origin->adjNodes(n);
    }
};

struct MapGraphUndirected {
    MapGraph::Ptr      origin;
    hstd::Vec<MapNode> adjNodes(MapNode const& n) const {
        return origin->adjNodes(n);
    }

    hstd::Vec<MapEdge> adjEdges(MapNode const& n) const {
        hstd::UnorderedSet<MapNode> adjacent;
        hstd::Vec<MapEdge>          res;
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
    virtual hstd::Opt<MapNodeProp> getInitialNodeProp(
        std::shared_ptr<MapGraphState> const& s,
        org::imm::ImmAdapter                  node,
        std::shared_ptr<MapConfig>            conf);
};

struct [[refl(
    R"({
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    }
  }
})")]] MapConfig : hstd::SharedPtrApi<MapConfig> {
    hstd::SPtr<MapInterface>        impl;
    [[refl]] hstd::OperationsTracer dbg;
    MapConfig(hstd::SPtr<MapInterface> impl);
    MapConfig();

    DESC_FIELDS(MapConfig, ());

    hstd::Opt<MapNodeProp> getInitialNodeProp(
        std::shared_ptr<MapGraphState> const& s,
        org::imm::ImmAdapter                  node) {
        return impl->getInitialNodeProp(s, node, shared_from_this());
    }
};

struct [[refl(
    R"({
  "default-constructor": false,
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    }
  }
})")]] MapGraphState : hstd::SharedPtrApi<MapGraphState> {
    /// \brief List of nodes with unresolved outgoing links.
    hstd::UnorderedSet<MapNode>                       unresolved;
    [[refl]] std::shared_ptr<MapGraph>                graph;
    [[refl]] std::shared_ptr<org::imm::ImmAstContext> ast;

    [[refl]] std::shared_ptr<MapGraph> getGraph() const { return graph; }

    MapGraphState(org::imm::ImmAstContext::Ptr ast)
        : ast{ast}, graph{std::make_shared<MapGraph>()} {};

    [[refl]] static std::shared_ptr<MapGraphState> FromAstContext(
        std::shared_ptr<org::imm::ImmAstContext> ast) {
        return MapGraphState::shared(ast);
    }


    [[refl]] void registerNode(
        MapNodeProp const&                node,
        std::shared_ptr<MapConfig> const& conf);

    [[refl]] void addNode(
        org::imm::ImmAdapter const&       node,
        std::shared_ptr<MapConfig> const& conf);

    [[refl]] void addNodeRec(
        std::shared_ptr<org::imm::ImmAstContext> const& ast,
        org::imm::ImmAdapter const&                     node,
        std::shared_ptr<MapConfig> const&               conf);

    [[refl]] hstd::Vec<MapLink> getUnresolvedSubtreeLinks(
        org::imm::ImmAdapterT<org::imm::ImmSubtree> node,
        std::shared_ptr<MapConfig> const&           conf) const;

    [[refl]] hstd::Opt<MapLink> getUnresolvedLink(
        org::imm::ImmAdapterT<org::imm::ImmLink> node,
        std::shared_ptr<MapConfig> const&        conf) const;


    DESC_FIELDS(MapGraphState, (unresolved, graph));
};

[[refl]] std::shared_ptr<MapGraphState> initMapGraphState(
    std::shared_ptr<org::imm::ImmAstContext> ast);


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
hstd::Vec<MapLinkResolveResult> getResolveTarget(
    MapGraphState::Ptr const&  s,
    MapNode const&             source,
    MapLink const&             link,
    std::shared_ptr<MapConfig> conf);

struct MapNodeResolveResult {
    MapNodeProp                     node = MapNodeProp{};
    hstd::Vec<MapLinkResolveResult> resolved;
    DESC_FIELDS(MapNodeResolveResult, (node, resolved));
};

/// \brief Attempt to resolve links in the initial insert and split the
/// graph links into `.node.unresolved` and `.resolved` fields of the
/// returned.
MapNodeResolveResult getResolvedNodeInsert(
    MapGraphState::Ptr const&  s,
    MapNodeProp const&         node,
    std::shared_ptr<MapConfig> conf);


bool isDescriptionItem(org::imm::ImmAdapter const& node);
bool isLinkedDescriptionItemNode(org::imm::ImmAdapter const& n);

bool isLinkedDescriptionItem(org::imm::ImmAdapter const& n);
/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::imm::ImmAdapter const& n);

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInSubtreeDescriptionList(org::imm::ImmAdapter const& n);

bool isAttachedDescriptionList(org::imm::ImmAdapter const& n);

bool hasGraphAnnotations(
    org::imm::ImmAdapterT<org::imm::ImmParagraph> const& par);
bool hasGraphAnnotations(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& par);

bool isMmapIgnored(org::imm::ImmAdapter const& n);

} // namespace org::graph


template <>
struct std::formatter<org::graph::MapGraph*>
    : hstd::std_format_ptr_as_value<org::graph::MapGraph> {};
