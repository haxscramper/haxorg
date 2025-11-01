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
        std::string vertexId;
        std::string vertexName;
        DESC_FIELDS(SerialSchema, (vertexId, vertexName));
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

    int const categoryId = 0;

    virtual org::graph::EdgeCategory getCategory() const override {
        return org::graph::EdgeCategory(categoryId);
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
             sourceId,
             targetId,
             bundleIndex,
             sourcePortId,
             targetPortId));
    };

    virtual json getEdgeSerial(
        org::graph::EdgeID const& id) const override;
};
