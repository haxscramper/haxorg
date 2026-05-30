#pragma once

#include "graph_common.hpp"
#include "graph_attribute.hpp"
#include "graph_port.hpp"

namespace hstd::ext::graph {

struct IEdge
    : public virtual IGraphObjectBase
    , public virtual IAttributeObject {
    using id_type = EdgeID;

    using IGraphObjectBase::IGraphObjectBase;

    DESC_FIELDS(IEdge, ());

    struct SerialSchema {
        std::string edgeId;
        DESC_FIELDS(SerialSchema, (edgeId));
    };

    bool operator==(IEdge const& other) const {
        return this->isEqual(&other);
    }

    virtual std::size_t getHash() const override;
    virtual bool isEqual(IGraphObjectBase const* other) const override;
    virtual std::string getRepr() const override {
        return hstd::fmt1(*this);
    }

#if ORG_BUILD_WITH_PROTOBUF
    virtual void writeSerial(
        proto::IEdge* out,
        IGraph const* graph,
        EdgeID const& self_id) const;
#endif
};

struct TrivialEdge
    : public IEdge
    , public virtual TrivialAttributeObject {
    using IEdge::IEdge;
};


/// \brief Base class for the collections that provide the edges in the
/// graph.
///
/// Edge provider maps the edge ID to the real object. The term "tracking"
/// refers to the incidence matrix presence: knowing the source/target of
/// the edge ID, and having the ID itself registered.
class IEdgeProvider {
  protected:
    hstd::UnorderedMap<Str, EdgeID> stableIdMap;

  public:
    virtual ~IEdgeProvider() = default;
    /// \brief Return edge category for this collection, uniquely
    /// identifying this specific one collection.
    virtual EdgeCollectionID getCollectionID() const = 0;

    /// \brief Get already constructed edge object from the store.
    virtual IEdge const* getEdge(EdgeID const& id) const   = 0;
    virtual VertexID     getSource(EdgeID const& id) const = 0;
    virtual VertexID     getTarget(EdgeID const& id) const = 0;

    bool hasEdgeStableId(Str const& id) const {
        return stableIdMap.contains(id);
    }

    EdgeID getEdgeIDByStableId(Str const& id) const {
        return stableIdMap.at(id);
    }

    /// \brief Return stable identifier for this edge collection.
    virtual std::string getStableID() const;

    /// \brief Get the full list of edges stored in the collection
    virtual EdgeIDSet getEdges() const = 0;

    /// \brief Add the vertex to the edge collection without any of the
    /// incoming/outgoing edges.
    virtual void trackVertex(VertexID const& vert) = 0;

    struct DependantDeletion {
        VertexIDSet vertices;
        EdgeIDSet   edges;
    };

    /// \brief Remove the vertex from the collection including any outgoing
    /// edges. Edge removal is done using `untrackEdge`.
    virtual DependantDeletion untrackVertex(VertexID const& vert) = 0;


    /// \brief Get list of all outgoing edges for the target vertex
    virtual EdgeIDSet getOutgoing(VertexID const& vert) const = 0;

    /// \brief Get list of all incoming edges for the target vertex
    virtual EdgeIDSet getIncoming(VertexID const& vert) const = 0;
    /// \brief Check if the derived edge provider has the edge object
    /// associated with the given edge.
    virtual bool hasEdge(EdgeID const& id) const = 0;

    virtual int getInDegree(VertexID const& id) const {
        return getIncoming(id).size();
    }

    virtual int getOutDegree(VertexID const& id) const {
        return getOutgoing(id).size();
    }

    virtual EdgeIDSet getAdjacentEdges(VertexID id) const {
        return getIncoming(id) + getOutgoing(id);
    }

    virtual VertexIDSet getOutNodes(VertexID id) const;

    virtual VertexIDSet getInNodes(VertexID id) const;

    virtual VertexIDSet getAdjacentNodes(VertexID id) const {
        return getOutNodes(id) + getInNodes(id);
    }

    virtual int getNumEdges() const { return getEdges().size(); }

    /// \brief Check if the edge is tracked by the provider. This method is
    /// independent of the `hasEdge` and is only concerned with the
    /// incidence matrix presence for the edgei.
    virtual bool isTrackingEdge(EdgeID const& id) const = 0;

    virtual bool hasEdge(VertexID const& source, VertexID const& target)
        const = 0;

    // static API for masking the edge IDs.

    /// \brief Hierachy category should have the first bit set to 1.

    static EdgeCollectionID edgeCategoryFromEdge(EdgeID const& id);
    static EdgeCollectionID hierarchyIdFromEdge(EdgeID const& id);
};

class IEdgeCollection : public IEdgeProvider {
    hstd::UnorderedMap<
        VertexID,
        hstd::UnorderedMap<VertexID, hstd::Vec<EdgeID>>>
        incidence;

    hstd::UnorderedMap<VertexID, hstd::Vec<VertexID>> incoming_from;
    hstd::UnorderedMap<EdgeID, hstd::Pair<VertexID, VertexID>>
        source_target;


  public:
    virtual void writeSerial(
        proto::IEdgeCollection* out,
        IGraph const*           graph) const = 0;

    virtual void readSerial(
        proto::IEdgeCollection const* in,
        IGraph const*                 graph,
        IGraphSerialReaderFactory*    factory) = 0;

    bool isTrackingEdge(EdgeID const& id) const override {
        bool res = source_target.contains(id);
        if (res) {
            LOGIC_ASSERTION_CHECK_FMT(
                incidence.at(getSource(id)).at(getTarget(id)).contains(id),
                "malformed edge collection structure: source-target {}-{}"
                "contains an edge {}, but the incidence matrix does not",
                getSource(id),
                getTarget(id),
                id);
        }
        return res;
    }

    using IEdgeProvider::hasEdge;
    bool hasEdge(VertexID const& source, VertexID const& target)
        const override {
        return incidence.contains(source)
            && incidence.at(source).contains(target);
    }


    EdgeIDSet         getEdges() const override;
    EdgeIDSet         getOutgoing(VertexID const& vert) const override;
    EdgeIDSet         getIncoming(VertexID const& vert) const override;
    void              trackVertex(VertexID const& vert) override;
    DependantDeletion untrackVertex(VertexID const& vert) override;

    IPortCollection::EdgePortsSpec getPortSpecs(EdgeID const& e) const {
        return IPortCollection::EdgePortsSpec{
            IPortCollection::PortSpec{getSource(e), e, true},
            IPortCollection::PortSpec{getTarget(e), e, false},
        };
    }

    VertexID getSource(EdgeID const& id) const override {
        return source_target.at(id).first;
    }

    VertexID getTarget(EdgeID const& id) const override {
        return source_target.at(id).second;
    }

    /// \brief Get list of edges in a specific sub-set of the stored
    /// vertices. Both source and target must be in the subset.
    hstd::UnorderedSet<EdgeID> getFullyIncludedEdges(
        hstd::UnorderedSet<VertexID> const& subset) const {
        hstd::UnorderedSet<EdgeID> res;
        // TODO: This function can be optimized: instead of iterating over
        // the list of all edges, and then filtering out ones that don't
        // match the requirements, it can walk over the incidence matrix
        // directly.
        for (auto const& id : getEdges()) {
            if (subset.contains(getSource(id))
                && subset.contains(getTarget(id))) {
                res.incl(id);
            }
        }

        return res;
    }

    /// \brief Get list of edges that are at least partially included in
    /// the subset: at least source or target must be in the subset.
    hstd::UnorderedSet<EdgeID> getPartiallyIncludedEdges(
        hstd::UnorderedSet<VertexID> const& subset) const {
        hstd::UnorderedSet<EdgeID> res;
        for (auto const& id : getEdges()) {
            if (subset.contains(getSource(id))
                || subset.contains(getTarget(id))) {
                res.incl(id);
            }
        }

        return res;
    }

    virtual void trackEdge(
        EdgeID const&   id,
        VertexID const& source,
        VertexID const& target);
    /// \brief Remove the edge from the collection. This method is called
    /// by the `untrackVertex`.
    virtual void untrackEdge(EdgeID const& id);
};


struct TrivialEdgeCollection : public IEdgeCollection {
  public:
    hstd::UnorderedIncrementalStore<EdgeID, TrivialEdge> edgeStore;

    EdgeCollectionID collection_id = EdgeCollectionID{};

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    EdgeID addEdge(
        VertexID const&               source,
        VertexID const&               target,
        hstd::Opt<std::string> const& stable_id = std::nullopt) {
        auto res = edgeStore.add(
            TrivialEdge{
                stable_id.value_or(hstd::fmt("{}-{}", source, target))},
            getCollectionID());
        trackEdge(res, source, target);
        return res;
    }

    TrivialEdgeCollection(EdgeCollectionID const& id)
        : collection_id{id} {}

    EdgeCollectionID getCollectionID() const override {
        return collection_id;
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return &edgeStore.at(id);
    }

    void trackEdge(
        EdgeID const&   id,
        VertexID const& source,
        VertexID const& target) override {
        IEdgeCollection::trackEdge(id, source, target);
    }

    void writeSerial(proto::IEdgeCollection* out, IGraph const* graph)
        const override {
        IEdgeCollection::writeSerial(out, graph);
        proto::TrivialEdgeCollectionPayload tag;
        out->mutable_payload()->PackFrom(tag);
    }

    void readSerial(
        proto::IEdgeCollection const* in,
        IGraph const*                 graph,
        IGraphSerialReaderFactory*    factory) override {
        IEdgeCollection::readSerial(in, graph, factory);
    }
};

struct IdOnlyEdgeCollection : public IEdgeCollection {
  public:
    hstd::UnorderedSet<EdgeID> edgeStore;

    EdgeCollectionID collection_id = EdgeCollectionID{};

    bool hasEdge(EdgeID const& id) const override {
        return edgeStore.contains(id);
    }

    IdOnlyEdgeCollection(EdgeCollectionID const& id) : collection_id{id} {}

    EdgeCollectionID getCollectionID() const override {
        return collection_id;
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return nullptr;
    }


    void trackEdge(
        EdgeID const&   id,
        VertexID const& source,
        VertexID const& target) override {
        edgeStore.incl(id);
        IEdgeCollection::trackEdge(id, source, target);
    }
};


} // namespace hstd::ext::graph
