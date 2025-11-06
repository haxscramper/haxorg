#pragma once

#include <src/model/graph/IOrgGraph.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

struct DiaGraphVertex : public org::graph::IVertex {
    DiaUniqId uniq;

    DiaGraphVertex(DiaUniqId const& id) : uniq{id} {}

    bool operator==(DiaGraphVertex const& vert) const {
        return uniq == vert.uniq;
    }

    struct SerialSchema {
        std::string            vertexId;
        std::string            vertexName;
        std::string            vertexKind;
        hstd::Opt<std::string> vertexDescription;

        struct Extra {
            json                   structuredDescription;
            json                   structuredName;
            hstd::Opt<std::string> todoState;
            int                    nestingLevel;
            DESC_FIELDS(
                Extra,
                (structuredDescription,
                 structuredName,
                 todoState,
                 nestingLevel));
        };

        std::string extra_type;
        Extra       extra;

        DESC_FIELDS(
            SerialSchema,
            (vertexId,
             vertexName,
             vertexKind,
             vertexDescription,
             extra,
             extra_type));
    };

    std::string getStableId() const override;

    virtual std::size_t getHash() const override;
    virtual bool isEqual(const IGraphObjectBase* other) const override;
    virtual std::string getRepr() const override;
    virtual json        getSerialNonRecursive(
               org::graph::IGraph const*   graph,
               org::graph::VertexID const& id) const override;
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
        org::graph::VertexID const& vert) const override {
        return vertices.at(vert);
    }

    DiaAdapter getAdapter(org::graph::VertexID const& id) const {
        return DiaAdapter{getVertex(id).uniq, tree_context};
    }

    org::graph::VertexID getID(DiaUniqId const& id) const {
        return getID(DiaGraphVertex{id});
    }

    org::graph::VertexID addVertex(DiaUniqId const& id);

    org::graph::VertexID delVertex(DiaUniqId const& id);
};

class DiaHierarchyEdge : public org::graph::IEdge {
    using IEdge::IEdge;
};

class DiaHierarchyEdgeCollection : public org::graph::IEdgeCollection {
    DiaContext::Ptr      tree_context;
    hstd::SPtr<DiaGraph> graph;
    hstd::UnorderedStore<org::graph::EdgeID, DiaHierarchyEdge> store;

  public:
    DiaHierarchyEdgeCollection(
        DiaContext::Ptr      tree_context,
        hstd::SPtr<DiaGraph> graph)
        : tree_context{tree_context}, graph{graph} {}

    virtual org::graph::EdgeCategoryID getCategory() const override {
        return org::graph::EdgeCategoryID(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }

    virtual std::string getStableID() const override {
        return hstd::value_metadata<
            DiaHierarchyEdgeCollection>::typeName();
    }

    virtual hstd::Vec<org::graph::EdgeID> addAllOutgoing(
        const org::graph::VertexID& vert) override;


    virtual const org::graph::IEdge& getEdge(
        const org::graph::EdgeID& id) const override {
        return store.at(id);
    }
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

    virtual org::graph::PropertyTrackerID getTrackerID() const override {
        return org::graph::PropertyTrackerID(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }


    virtual void trackVertex(const org::graph::VertexID& vertex) override;
    virtual void untrackVertex(
        const org::graph::VertexID& vertex) override;
    virtual hstd::Vec<org::graph::VertexID> getVertices(
        const org::graph::IProperty& prop) override;
};

class DiaDescriptionListEdge : public org::graph::IEdge {
    using IEdge::IEdge;
};

class DiaDescriptionListEdgeCollection
    : public org::graph::IEdgeCollection {
    hstd::SPtr<DiaGraph>            graph;
    hstd::SPtr<DiaSubtreeIdTracker> tracker;

    hstd::UnorderedStore<org::graph::EdgeID, DiaDescriptionListEdge> store;

  public:
    DiaDescriptionListEdgeCollection(
        hstd::SPtr<DiaGraph> const&            graph,
        hstd::SPtr<DiaSubtreeIdTracker> const& tracker)
        : graph{graph}, tracker{tracker} {}

    virtual hstd::Vec<org::graph::EdgeID> addAllOutgoing(
        const org::graph::VertexID& vert) override;

    virtual org::graph::EdgeCategoryID getCategory() const override {
        return org::graph::EdgeCategoryID(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }

    virtual std::string getStableID() const override {
        return hstd::value_metadata<
            DiaDescriptionListEdgeCollection>::typeName();
    }

    virtual const org::graph::IEdge& getEdge(
        const org::graph::EdgeID& id) const override {
        return store.at(id);
    }
};
