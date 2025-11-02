#pragma once

#include <src/model/graph/IOrgGraph.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

struct DiaGraphVertex {
    DiaUniqId uniq;

    bool operator==(DiaGraphVertex const& vert) const {
        return uniq == vert.uniq;
    }

    std::string getStableId() const {
        return std::format(
            "{}-{}", uniq.target, std::hash<DiaUniqId>{}(uniq));
    }
};

template <>
struct std::hash<DiaGraphVertex> {
    std::size_t operator()(DiaGraphVertex const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.uniq);
        return result;
    }
};


class DiaGraph : public org::graph::IGraph {
    DiaContext::Ptr tree_context;
    hstd::UnorderedStore<org::graph::VertexID, DiaGraphVertex> vertices;

  public:
    DiaGraph(DiaContext::Ptr tree_context) : tree_context{tree_context} {};

    org::graph::VertexID getID(DiaGraphVertex const& vert) const {
        return vertices.at(vert);
    }

    DiaGraphVertex const& getVertex(
        org::graph::VertexID const& vert) const {
        return vertices.at(vert);
    }

    DiaAdapter getAdapter(org::graph::VertexID const& id) const {
        return DiaAdapter{getVertex(id).uniq, tree_context};
    }

    org::graph::VertexID getID(DiaUniqId const& id) const {
        return getID(DiaGraphVertex{id});
    }

    org::graph::VertexID addVertex(DiaUniqId const& id) {
        return vertices.add(DiaGraphVertex{id});
    }

    org::graph::VertexID delVertex(DiaUniqId const& id) {
        return vertices.del(DiaGraphVertex(id));
    }

    struct SerialSchema {
        std::string            vertexId;
        std::string            vertexName;
        std::string            vertexKind;
        hstd::Opt<std::string> vertexDescription;

        struct Extra {
            json structuredDescription;
            DESC_FIELDS(Extra, (structuredDescription));
        };

        Extra extra;

        DESC_FIELDS(
            SerialSchema,
            (vertexId, vertexName, vertexKind, vertexDescription, extra));
    };

    virtual json getVertexSerial(
        org::graph::VertexID const& id) const override;

    hstd::Vec<org::graph::VertexID> getVertices() const override {
        return vertices.keys();
    }
};


class DiaHierarchyEdgeCollection : public org::graph::IEdgeCollection {
    DiaContext::Ptr      tree_context;
    hstd::SPtr<DiaGraph> graph;

  public:
    DiaHierarchyEdgeCollection(
        DiaContext::Ptr      tree_context,
        hstd::SPtr<DiaGraph> graph)
        : tree_context{tree_context}, graph{graph} {}

    virtual org::graph::EdgeCategory getCategory() const override {
        return org::graph::EdgeCategory(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }

    virtual hstd::Vec<org::graph::Edge> getOutgoing(
        const org::graph::VertexID& vert) override;

    struct SerialSchema {
        std::string            category = "hierarchy";
        std::string            edgeId;
        std::string            sourceId;
        std::string            targetId;
        int                    bundleIndex;
        hstd::Opt<std::string> sourcePortId;
        hstd::Opt<std::string> targetPortId;
        DESC_FIELDS(
            SerialSchema,
            (category,
             edgeId,
             sourceId,
             targetId,
             bundleIndex,
             sourcePortId,
             targetPortId));
    };

    virtual json getEdgeSerial(
        org::graph::EdgeID const& id) const override;
};

class DiaSubtreeIdProperty : public org::graph::IProperty {
    std::string id;

  public:
    DiaSubtreeIdProperty(std::string const& id) : id{id} {}

    std::string const& getId() const { return id; }

    virtual std::size_t getHash() const override {
        return std::hash<std::string>{}(id);
    }

    virtual bool isEqual(const IProperty* other) const override {
        return other->isInstance<DiaSubtreeIdProperty>()
            && dynamic_cast<DiaSubtreeIdProperty const*>(other)->id == id;
    }

    virtual std::string getRepr() const override {
        return std::format("DiaSubtreeIdProperty({})", id);
    }
};

class DiaSubtreeIdTracker : public org::graph::IPropertyTracker {
    hstd::SPtr<DiaGraph>                                  graph;
    hstd::UnorderedMap<std::string, org::graph::VertexID> map;

  public:
    DiaSubtreeIdTracker(hstd::SPtr<DiaGraph> const& graph)
        : graph{graph} {}

    virtual void trackVertex(const org::graph::VertexID& vertex) override;
    virtual void untrackVertex(
        const org::graph::VertexID& vertex) override;
    virtual hstd::Vec<org::graph::VertexID> getVertices(
        const org::graph::IProperty& prop) override;
};

class DiaDescriptionListEdgeCollection
    : public org::graph::IEdgeCollection {
    hstd::SPtr<DiaGraph>            graph;
    hstd::SPtr<DiaSubtreeIdTracker> tracker;

  public:
    DiaDescriptionListEdgeCollection(
        hstd::SPtr<DiaGraph> const&            graph,
        hstd::SPtr<DiaSubtreeIdTracker> const& tracker)
        : graph{graph}, tracker{tracker} {}

    virtual hstd::Vec<org::graph::Edge> getOutgoing(
        const org::graph::VertexID& vert) override;

    virtual org::graph::EdgeCategory getCategory() const override {
        return org::graph::EdgeCategory(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }

    struct SerialSchema {
        std::string            category = "description-list";
        std::string            edgeId;
        std::string            sourceId;
        std::string            targetId;
        int                    bundleIndex;
        hstd::Opt<std::string> sourcePortId;
        hstd::Opt<std::string> targetPortId;
        DESC_FIELDS(
            SerialSchema,
            (category,
             edgeId,
             sourceId,
             targetId,
             bundleIndex,
             sourcePortId,
             targetPortId));
    };

    virtual json getEdgeSerial(
        const org::graph::EdgeID& id) const override;
};
