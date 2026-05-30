#pragma once
#if !ORG_BUILD_EMCC
#    include <boost/graph/properties.hpp>
#endif
#include <haxorg/imm/ImmOrg.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <immer/map_transient.hpp>
#if !ORG_BUILD_EMCC
#    include <hstd/ext/graph/visual/graph_graphviz.hpp>
#endif
#include <hstd/ext/graph/base/graph_base.hpp>
#include <haxorg/imm/ImmGetterApi.hpp>
#include <haxorg/serde/SemOrgSerde.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>

namespace org::graph {

namespace hgraph = hstd::ext::graph;

struct graph_error : hstd::CRTP_hexception<graph_error> {};

struct MapLink {
    struct Link {
        /// \brief Original link used to create the graph edge. Used to
        /// return an edge to unresolved state when target is deleted. When
        /// source is deleted the edge is simply dropped.
        org::imm::ImmUniqId link;
        /// MapLink description field can be reused or, for description
        /// list items, this field contains a newly created statment list
        hstd::Vec<org::imm::ImmUniqId> description;
        DESC_FIELDS(Link, (link, description));
    };

    /// \brief Unresolved radio link that was detected from AST context but
    /// the graph node has not been added yet.
    struct Radio {
        org::imm::ImmUniqId target;
        DESC_FIELDS(Radio, (target));
    };

    SUB_VARIANTS_REFL(Kind, Data, data, getKind, Radio, Link);
    Data data;
    DESC_FIELDS(MapLink, (data));
};


struct MapNodeProp
    : public hgraph::IAttribute
    , public hstd::SharedPtrApi<MapNodeProp> {
    hstd::Vec<MapLink> unresolved;

    DESC_FIELDS(MapNodeProp, (unresolved));

    std::string getRepr() const override { return "MapNodeProp"; }

    void writeSerial(
        hstd::ext::graph::proto::IAttribute* out,
        hstd::ext::graph::IGraph const*      graph) const override {}

    void readSerial(
        hstd::ext::graph::proto::IAttribute const*   in,
        hstd::ext::graph::IGraph const*              graph,
        hstd::ext::graph::IGraphSerialReaderFactory* factory,
        hstd::ext::graph::IAttributeObject const*    vertex) override {
        throw hstd::ext::graph::serde_error::init(
            "Map node prop does not support de-serialization from graph. "
            "Construct immutable AST context and rebuild the graph from "
            "it");
    }
};

struct MapEdgeProp
    : public hgraph::IAttribute
    , public hstd::SharedPtrApi<MapEdgeProp> {
    MapLink link;
    DESC_FIELDS(MapEdgeProp, (link));

    std::string getRepr() const override { return "MapEdgeProp"; }

    void writeSerial(
        hstd::ext::graph::proto::IAttribute* out,
        hstd::ext::graph::IGraph const*      graph) const override {
        logic_todo_impl();
    }

    void readSerial(
        hstd::ext::graph::proto::IAttribute const*   in,
        hstd::ext::graph::IGraph const*              graph,
        hstd::ext::graph::IGraphSerialReaderFactory* factory,
        hstd::ext::graph::IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }
};


struct MapNode
    : public hgraph::IVertex
    , public virtual hgraph::TrivialAttributeObject
    , public hstd::SharedPtrApi<MapNode> {
    org::imm::ImmAdapter id;

    hstd::Opt<hstd::Str> getSubtreeId(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const;

    hstd::Opt<hstd::Str> getFootnoteName(
        std::shared_ptr<org::imm::ImmAstContext> const& context) const;

    MapNode() : hgraph::IVertex{""}, id{org::imm::ImmAdapter()} {}
    MapNode(
        org::imm::ImmAdapter const&   id,
        hstd::Opt<std::string> const& stable_id = std::nullopt)
        : hgraph::IVertex{stable_id.value_or(id.id.getReadableId())}
        , id{id} {}

    bool operator==(MapNode const& other) const {
        return this->id == other.id;
    }

    bool operator<(MapNode const& other) const {
        return id.id < other.id.id;
    }

    org::imm::ImmAdapter getAdapter() const { return id; }

    hstd::SPtr<MapNodeProp> getProp() const {
        return getUniqueAttribute<MapNodeProp>();
    }

    DESC_FIELDS(MapNode, (id));

    std::size_t getHash() const override {
        std::size_t res{};
        hstd::hax_hash_combine(res, id.uniq());
        return res;
    }

    bool isEqual(IGraphObjectBase const* other) const override {
        return other->isInstance<MapNode>()
            && dynamic_cast<MapNode const*>(other)->id == id;
    }

    template <typename T>
    hstd::outcome::result<T, std::string> getJsonProperty(
        std::shared_ptr<org::imm::ImmAstContext> const& context,
        std::string const&                              name) {
        return getStructuredProperty<T>(id, name);
    }


  public:
    void readSerial(
        hstd::ext::graph::proto::IVertex const*      in,
        hstd::ext::graph::IGraph const*              graph,
        hstd::ext::graph::IGraphSerialReaderFactory* factory) override {
        logic_todo_impl();
    }


    void writeSerial(
        hgraph::proto::IVertex* out,
        hgraph::IGraph const*   graph,
        hgraph::VertexID const& self_id) const override;
};

struct MapEdge
    : public hgraph::IEdge
    , public virtual hgraph::TrivialAttributeObject {
    DESC_FIELDS(MapEdge, ());
    using hgraph::IEdge::IEdge;
};


class MapEdgeCollection : public hgraph::IEdgeCollection {
  public:
    hstd::UnorderedIncrementalStore<hgraph::EdgeID, hstd::SPtr<MapEdge>>
        edges;

    hgraph::EdgeCollectionID getCollectionID() const override {
        return hgraph::EdgeCollectionID::FromCollectionTypePointer(this);
    }

    hgraph::EdgeID add(hstd::SPtr<MapEdge> const& e) {
        return edges.add(e, getCollectionID());
    }

    const hgraph::IEdge* getEdge(hgraph::EdgeID const& id) const override {
        return edges.at(id).get();
    }

    using hgraph::IEdgeCollection::hasEdge;
    bool hasEdge(hgraph::EdgeID const& id) const override {
        return edges.contains(id);
    }
    DESC_FIELDS(MapEdgeCollection, ());


    void writeSerial(
        hstd::ext::graph::proto::IEdgeCollection* out,
        hstd::ext::graph::IGraph const*           graph) const override;

    void readSerial(
        hstd::ext::graph::proto::IEdgeCollection const* in,
        hstd::ext::graph::IGraph const*                 graph,
        hstd::ext::graph::IGraphSerialReaderFactory*    factory) override;
};

} // namespace org::graph


template <>
struct std::hash<org::graph::MapNode> {
    std::size_t operator()(org::graph::MapNode const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.getHash());
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

struct MapGraph
    : public hstd::SharedPtrApi<MapGraph>
    , public hgraph::IGraph
    , public hstd::OperationsTracer {
    hstd::UnorderedIncrementalStore<hgraph::VertexID, hstd::SPtr<MapNode>>
                                                              nodes;
    hstd::SPtr<MapEdgeCollection>                             edges;
    hstd::UnorderedMap<org::imm::ImmUniqId, hgraph::VertexID> id_map;
    DESC_FIELDS(MapGraph, ());

    hstd::ext::graph::VertexID addVertex(
        hstd::SPtr<hstd::ext::graph::IVertex> const& vertex) override {
        return nodes.add(hstd::validated_dynamic_cast<MapNode>(vertex));
    }

    MapGraph() : edges{std::make_shared<MapEdgeCollection>()} {
        addCollection(edges);
    }

    hgraph::VertexID getVertexID(org::imm::ImmUniqId id) const {
        return id_map.at(id);
    }

    hgraph::VertexID getVertexID(org::imm::ImmAdapter const& ad) const {
        return getVertexID(ad.uniq());
    }

    org::imm::ImmUniqId getImmID(hgraph::VertexID id) const {
        return getCastVertex<MapNode>(id)->id.uniq();
    }

    MapNode const* get(hgraph::VertexID id) const {
        return this->getCastVertex<MapNode>(id);
    }

    MapEdge const* get(hgraph::EdgeID id) const {
        return this->getCastEdge<MapEdge>(id);
    }

    MapNodeProp::Ptr getAttr(hgraph::VertexID id) const {
        return this->getVertex(id)->getUniqueAttribute<MapNodeProp>();
    }

    MapEdgeProp::Ptr getAttr(hgraph::EdgeID id) const {
        return this->getEdge(id)->getUniqueAttribute<MapEdgeProp>();
    }

    hstd::generator<std::tuple<hgraph::VertexID, org::imm::ImmUniqId, MapNodeProp::Ptr>> getProperties()
        const {
        for (auto const& id : getAllVertices()) {
            co_yield {
                id, getCastVertex<MapNode>(id)->id.uniq(), getAttr(id)};
        }
    }

    hstd::Vec<std::tuple<hgraph::EdgeID, hstd::SPtr<MapEdgeProp>>> getEdges()
        const {
        hstd::Vec<std::tuple<hgraph::EdgeID, hstd::SPtr<MapEdgeProp>>> res;
        for (auto const& e : edges->getEdges()) {
            res.push_back({e, getAttr(e)});
        }
        return res;
    }

    const hgraph::IVertex* getVertex(
        hgraph::VertexID const& id) const override {
        return nodes.at(id).get();
    }

    bool isRegisteredNode(MapNode const& id) const {
        return id_map.contains(id.id.uniq());
    }

    bool isRegisteredNode(org::imm::ImmUniqId const& id) const {
        return id_map.contains(id);
    }

    bool hasEdge(hgraph::VertexID source, hgraph::VertexID target) const {
        return edges->hasEdge(source, target);
    }

    bool hasEdge(
        org::imm::ImmUniqId const& source,
        org::imm::ImmUniqId const& target) const {
        return hasEdge(getVertexID(source), getVertexID(target));
    }

    bool hasEdge(
        org::imm::ImmAdapter const& source,
        org::imm::ImmAdapter const& target) const {
        return hasEdge(source.uniq(), target.uniq());
    }


    hgraph::EdgeID addEdge(
        hstd::SPtr<MapEdge> const&     edge,
        hstd::SPtr<MapEdgeProp> const& prop,
        hgraph::VertexID               source,
        hgraph::VertexID               target) {
        edge->addAttribute(prop);
        auto res = edges->add(edge);
        LOGIC_ASSERTION_CHECK(edges->hasEdge(res), "");
        edges->trackEdge(res, source, target);
        return res;
    }

    /// \brief Add node to the graph, without registering any outgoing or
    /// ingoing elements.
    hgraph::VertexID addNode(
        hstd::SPtr<MapNode> const&     node,
        hstd::SPtr<MapNodeProp> const& prop) {
        node->addAttribute(prop);
        auto res = nodes.add(node);
        id_map.insert_or_assign(node->id.uniq(), res);
        trackVertex(res);
        return res;
    }

#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH
    struct GvConfig {
        hgraph::layout::LayoutRun::TrivialState state;
        hgraph::layout::LayoutRun::Ptr          run;

        GvConfig() : run{state.init()} {}

        hstd::UnorderedMap<hgraph::VertexID, hgraph::VertexID>
            layout_vertices;

        virtual bool acceptNode(hgraph::VertexID const& node) const {
            return true;
        }

        virtual bool acceptEdge(hgraph::EdgeID const& edge) const {
            return true;
        }

        virtual hgraph::gv::NodeAttribute::Record getNodeLabel(
            org::imm::ImmAdapter const& node,
            MapNodeProp::Ptr const&     prop) const;

        hstd::SPtr<hgraph::gv::GraphGroup> toGraphviz(
            org::imm::ImmAstContext::Ptr const& ctx,
            MapGraph::Ptr const&                graph);
    };

    struct GvConfigCallbackFilters : public GvConfig {
        hstd::Func<bool(hstd::ext::graph::VertexID node)> accept_node_cb;
        hstd::Func<bool(hstd::ext::graph::EdgeID edge)>   accept_edge_cb;

        bool acceptNode(
            hstd::ext::graph::VertexID const& node) const override {
            if (accept_node_cb) {
                return accept_node_cb(node);
            } else {
                return GvConfig::acceptNode(node);
            }
        }

        bool acceptEdge(
            hstd::ext::graph::EdgeID const& edge) const override {
            if (accept_edge_cb) {
                return accept_edge_cb(edge);
            } else {
                return GvConfig::acceptEdge(edge);
            }
        }

        // hstd::ext::graph::gv::NodeAttribute::Record getNodeLabel(
        //     const imm::ImmAdapter&  node,
        //     const MapNodeProp::Ptr& prop) const override {
        //     if ()
        // }
    };


#endif
};

struct MapGraphState;
struct MapConfig;

struct MapInterface {};

struct MapConfig : hstd::SharedPtrApi<MapConfig> {
    hstd::SPtr<MapInterface> impl;
    MapConfig(hstd::SPtr<MapInterface> impl);
    MapConfig();

    DESC_FIELDS(MapConfig, ());

    /// \brief Get node properties without resolving the target links. This
    /// is an entry point method that creates a new instance of the
    /// property attribute object and fills in all outgoing elements in it.
    virtual hstd::SPtr<MapNodeProp> getInitialNodeProp(
        MapGraphState const* state,
        org::imm::ImmAdapter node);
};

struct MapGraphState : public hstd::SharedPtrApi<MapGraphState> {
    /// \brief List of nodes with unresolved outgoing links.
    hgraph::VertexIDSet                      unresolved;
    std::shared_ptr<MapGraph>                graph;
    std::shared_ptr<org::imm::ImmAstContext> ast;
    std::shared_ptr<MapGraph> getGraph() const { return graph; }

    MapGraphState(org::imm::ImmAstContext::Ptr ast)
        : ast{ast}, graph{std::make_shared<MapGraph>()} {};

    static std::shared_ptr<MapGraphState> FromAstContext(
        std::shared_ptr<org::imm::ImmAstContext> ast) {
        return MapGraphState::shared(ast);
    }

    hgraph::VertexID addNode(
        org::imm::ImmAdapter const&       node,
        std::shared_ptr<MapConfig> const& conf);

    void addNodeRec(
        std::shared_ptr<org::imm::ImmAstContext> const& ast,
        org::imm::ImmAdapter const&                     node,
        std::shared_ptr<MapConfig> const&               conf);

    /// \brief Get all outgoing links used in the subtree. This will scan
    /// the subtree and its sub-nodes for the attached description lists.
    hstd::Vec<MapLink> getUnresolvedSubtreeLinks(
        org::imm::ImmAdapterT<org::imm::ImmSubtree> node) const;

    /// \brief Get the unresolved link used in the specified node. Returns
    /// only one link per node, if it is present. This function will not
    /// recursively scan the node, it will only return the link if it is
    /// present in the node argument.
    hstd::Opt<MapLink> getUnresolvedLink(
        org::imm::ImmAdapterT<org::imm::ImmLink> node) const;

    DESC_FIELDS(MapGraphState, (unresolved, graph));
};

std::shared_ptr<MapGraphState> initMapGraphState(
    std::shared_ptr<org::imm::ImmAstContext> ast);


struct MapLinkResolveResult {
    MapLink link;
    /// \brief Target node for link resolution. Nodes are uniquely
    /// associated with the ImmUniqId, so the 'target' is always filled,
    /// but the node might not exist in the graph yet. If it does not
    /// exist, the node is added to 'unresolved' in the graph state.
    org::imm::ImmUniqId target;
    org::imm::ImmUniqId source;
    DESC_FIELDS(MapLinkResolveResult, (link, target, source));
};

/// \brief Resolve a single link with the state `s` and return the edge.
/// Use `source` as an edge origin.
hstd::Vec<MapLinkResolveResult> getResolveTarget(
    MapGraphState::Ptr const&  state,
    hgraph::VertexID const&    source,
    MapLink const&             link,
    std::shared_ptr<MapConfig> conf);

struct MapNodeResolveResult {
    hstd::Vec<MapLinkResolveResult> resolved;
    DESC_FIELDS(MapNodeResolveResult, (resolved));
};

/// \brief Attempt to resolve links in the initial insert and split the
/// graph links into `.node.unresolved` and `.resolved` fields of the
/// returned.
MapNodeResolveResult getResolvedNodeInsert(
    MapGraphState::Ptr const&         state,
    hstd::ext::graph::VertexID const& node,
    std::shared_ptr<MapConfig>        conf);


bool hasGraphAnnotations(
    org::imm::ImmAdapterT<org::imm::ImmParagraph> const& par);
bool hasGraphAnnotations(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& par);

bool isMmapIgnored(org::imm::ImmAdapter const& n);

} // namespace org::graph


template <>
struct std::formatter<org::graph::MapGraph*>
    : hstd::std_format_ptr_as_value<org::graph::MapGraph> {};
