#pragma once
#if !ORG_BUILD_EMCC
#    include <boost/graph/properties.hpp>
#endif
#include <haxorg/imm/ImmOrg.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <immer/map_transient.hpp>
#if !ORG_BUILD_EMCC
#    include <hstd/ext/graph/graph_graphviz.hpp>
#endif
#include <hstd/ext/graph/graph_base.hpp>

namespace org::graph {

namespace hgraph = hstd::ext::graph;

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


struct [[refl]] MapNodeProp
    : public hgraph::IAttribute
    , public hstd::SharedPtrApi<MapNodeProp> {
    [[refl]] org::imm::ImmUniqId id;
    [[refl]] hstd::Vec<MapLink>  unresolved;

    [[refl]] org::imm::ImmAdapter getAdapter(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const {
        return context->adapt(id);
    }

    [[refl]] hstd::Opt<hstd::Str> getSubtreeId(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const;

    [[refl]] hstd::Opt<hstd::Str> getFootnoteName(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const;

    DESC_FIELDS(MapNodeProp, (unresolved, id));
};

struct [[refl]] MapEdgeProp : public hgraph::IAttribute {
    [[refl]] MapLink link;
    DESC_FIELDS(MapEdgeProp, (link));
};


struct [[refl]] MapNode
    : public hgraph::IVertex
    , public virtual hgraph::TrivialAttributeObject
    , public hstd::SharedPtrApi<MapNode> {
    [[refl]] org::imm::ImmUniqId id;

    MapNode() : id{org::imm::ImmUniqId()} {}
    MapNode(org::imm::ImmUniqId id) : id{id} {}

    [[refl]] bool operator==(MapNode const& other) const {
        return this->id == other.id;
    }

    [[refl]] bool operator<(MapNode const& other) const {
        return id < other.id;
    }

    hstd::SPtr<MapNodeProp> getProp() const {
        return getUniqueAttribute<MapNodeProp>();
    }

    DESC_FIELDS(MapNode, (id));
};

struct [[refl]] MapEdge
    : public hgraph::IEdge
    , public virtual hgraph::TrivialAttributeObject {};


class MapEdgeCollection : public hgraph::IEdgeCollection {
  public:
    hstd::UnorderedIncrementalStore<hgraph::EdgeID, hstd::SPtr<MapEdge>>
        edges;

    hgraph::EdgeCollectionID getCollectionID() const override {
        return hgraph::EdgeCollectionID::FromCollectionTypePointer(this);
    }

    hgraph::EdgeID add(hstd::SPtr<MapEdge> const& e) {
        return edges.add(e);
    }

    const hgraph::IEdge* getEdge(hgraph::EdgeID const& id) const override {
        return edges.at(id).get();
    }

    bool hasEdge(hgraph::EdgeID const& id) const override {
        return edges.contains(id);
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
        return result;
    }
};

namespace org::graph {
struct MapGraph;

struct [[refl(
    R"({
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    },
    "c": {
      "holder-type": "shared"
    }
  }
})")]] MapGraph
    : public hstd::SharedPtrApi<MapGraph>
    , public hgraph::IGraph
    , public hstd::OperationsTracer {
    hstd::UnorderedIncrementalStore<hgraph::VertexID, hstd::SPtr<MapNode>>
                                                              nodes;
    hstd::SPtr<MapEdgeCollection>                             edges;
    hstd::UnorderedMap<org::imm::ImmUniqId, hgraph::VertexID> id_map;
    DESC_FIELDS(MapGraph, ());

    MapNodeProp::Ptr getAttr(hgraph::VertexID id) const {
        return this->getVertex(id)->getUniqueAttribute<MapNodeProp>();
    }

    hstd::generator<hstd::Pair<hgraph::VertexID, MapNodeProp::Ptr>> getProperties()
        const {
        for (auto const& id : getAllVertices()) {
            co_yield {id, getAttr(id)};
        }
    }

    const hgraph::IVertex* getVertex(
        hgraph::VertexID const& id) const override {
        return nodes.at(id).get();
    }

    [[refl]] bool isRegisteredNode(MapNode const& id) const {
        return id_map.contains(id.id);
    }

    [[refl(R"({"unique-name": "isRegisteredNodeById"})")]] bool isRegisteredNode(
        org::imm::ImmUniqId const& id) const {
        return id_map.contains(id);
    }

    [[refl(R"({"unique-name": "addEdgeWithProp"})")]] hgraph::EdgeID addEdge(
        hstd::SPtr<MapEdge> const&     node,
        hstd::SPtr<MapEdgeProp> const& prop) {
        node->addAttribute(prop);
        auto res = edges->add(node);
        return res;
    }

    /// \brief Add node to the graph, without registering any outgoing or
    /// ingoing elements.
    [[refl]] hgraph::VertexID addNode(
        hstd::SPtr<MapNode> const&     node,
        hstd::SPtr<MapNodeProp> const& prop) {
        node->addAttribute(prop);
        auto res = nodes.add(node);
        id_map.insert_or_assign(node->id, res);
        return res;
    }

#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH
    struct GvConfig {
        hgraph::layout::LayoutRun::Ptr run;
        GvConfig(hgraph::layout::LayoutRun::Ptr run) : run{run} {}

        virtual bool acceptNode(hgraph::VertexID const& node) const {
            return true;
        }

        virtual bool acceptEdge(hgraph::EdgeID const& edge) const {
            return true;
        }

        virtual hgraph::gv::NodeAttribute::Record getNodeLabel(
            org::imm::ImmAdapter const& node,
            MapNodeProp const&          prop) const;
    };

    hstd::SPtr<hgraph::gv::GraphGroup> toGraphviz(
        org::imm::ImmAstContext::Ptr const& ctx,
        GvConfig const&                     conf) const;
#endif
};

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
    hstd::SPtr<MapInterface> impl;
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
    },
    "c": {
      "holder-type": "shared"
    }
  }
})")]] MapGraphState : public hstd::SharedPtrApi<MapGraphState> {
    /// \brief List of nodes with unresolved outgoing links.
    hstd::UnorderedSet<hgraph::VertexID>              unresolved;
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
    hgraph::VertexID target;
    hgraph::VertexID source;
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


bool hasGraphAnnotations(
    org::imm::ImmAdapterT<org::imm::ImmParagraph> const& par);
bool hasGraphAnnotations(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& par);

bool isMmapIgnored(org::imm::ImmAdapter const& n);

} // namespace org::graph


template <>
struct std::formatter<org::graph::MapGraph*>
    : hstd::std_format_ptr_as_value<org::graph::MapGraph> {};
