#pragma once

#include <org_diagram/src/model/graph/IOrgGraph.hpp>
#include <hstd/ext/hstd_graph.hpp>
#include <org_diagram/src/model/nodes/DiagramTreeNode.hpp>

struct DiaGraphVertex : public hstd::ext::graph::IVertex {
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
            json                             structuredDescription;
            json                             structuredName;
            hstd::Opt<std::string>           todoState;
            int                              nestingLevel;
            hstd::Opt<DiaNodeItem::Geometry> geometry;

            struct TodoSubtree {
                json                   structuredName;
                hstd::Opt<json>        structuredDescription;
                std::string            name;
                hstd::Opt<std::string> description;
                hstd::Vec<TodoSubtree> nested;
                hstd::Opt<std::string> todoState;
                DESC_FIELDS(
                    TodoSubtree,
                    (nested,
                     structuredName,
                     structuredDescription,
                     name,
                     description,
                     todoState));
            };

            hstd::Vec<TodoSubtree> nestedSubtrees;

            DESC_FIELDS(
                Extra,
                (structuredDescription,
                 structuredName,
                 todoState,
                 nestingLevel,
                 geometry,
                 nestedSubtrees));
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
    virtual bool isEqual(IGraphObjectBase const* other) const override;
    virtual std::string getRepr() const override;
    virtual json        getSerialNonRecursive(
        hstd::ext::graph::IGraph const*   graph,
        hstd::ext::graph::VertexID const& id) const override;
};

template <>
struct std::hash<DiaGraphVertex> {
    std::size_t operator()(DiaGraphVertex const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.uniq);
        return result;
    }
};

class DiaHierarchyEdgeCollection;
class DiaGraph : public hstd::ext::graph::IGraph {
    hstd::UnorderedStore<hstd::ext::graph::VertexID, DiaGraphVertex>
        vertices;

  public:
    DiaContext::Ptr                        tree_context;
    hstd::SPtr<DiaHierarchyEdgeCollection> subtree_hierarchy;
    DiaGraph(DiaContext::Ptr tree_context) : tree_context{tree_context} {};

    hstd::ext::graph::VertexID getID(DiaGraphVertex const& vert) const {
        return vertices.at(vert);
    }

    DiaGraphVertex const& getVertex(
        hstd::ext::graph::VertexID const& vert) const override {
        return vertices.at(vert);
    }

    DiaAdapter getAdapter(hstd::ext::graph::VertexID const& id) const {
        return DiaAdapter{getVertex(id).uniq, tree_context};
    }

    hstd::ext::graph::VertexID getID(DiaUniqId const& id) const {
        return getID(DiaGraphVertex{id});
    }

    hstd::ext::graph::VertexID addVertex(DiaUniqId const& id);

    hstd::ext::graph::VertexID delVertex(DiaUniqId const& id);
};

class DiaHierarchyEdge : public hstd::ext::graph::IEdge {
    using IEdge::IEdge;
};

class DiaHierarchyEdgeCollection
    : public hstd::ext::graph::IVertexHierarchy {
    DiaContext::Ptr      tree_context;
    hstd::SPtr<DiaGraph> graph;
    hstd::UnorderedStore<hstd::ext::graph::EdgeID, DiaHierarchyEdge> store;

  public:
    DiaHierarchyEdgeCollection(
        DiaContext::Ptr      tree_context,
        hstd::SPtr<DiaGraph> graph)
        : tree_context{tree_context}, graph{graph} {}

    virtual hstd::ext::graph::EdgeCollectionID getCategory()
        const override {
        return hstd::ext::graph::EdgeCollectionID(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }

    virtual std::string getStableID() const override {
        return hstd::value_metadata<
            DiaHierarchyEdgeCollection>::typeName();
    }

    virtual hstd::Vec<hstd::ext::graph::EdgeID> addAllOutgoing(
        hstd::ext::graph::VertexID const& vert) override;


    virtual const hstd::ext::graph::IEdge& getEdge(
        hstd::ext::graph::EdgeID const& id) const override {
        return store.at(id);
    }

    hstd::ext::graph::GraphHierarchyID getHierarchyId() const override;
};

class DiaSubtreeIdProperty : public hstd::ext::graph::IProperty {
    std::string id;

  public:
    DiaSubtreeIdProperty(std::string const& id) : id{id} {}

    std::string const& getId() const { return id; }

    virtual std::size_t getHash() const override {
        return std::hash<std::string>{}(id);
    }

    virtual bool isEqual(IProperty const* other) const override {
        return other->isInstance<DiaSubtreeIdProperty>()
            && dynamic_cast<DiaSubtreeIdProperty const*>(other)->id == id;
    }

    virtual std::string getRepr() const override {
        return std::format("DiaSubtreeIdProperty({})", id);
    }
};

class DiaSubtreeIdTracker : public hstd::ext::graph::IPropertyTracker {
    hstd::SPtr<DiaGraph>                                        graph;
    hstd::UnorderedMap<std::string, hstd::ext::graph::VertexID> map;

  public:
    DiaSubtreeIdTracker(hstd::SPtr<DiaGraph> const& graph)
        : graph{graph} {}

    virtual hstd::ext::graph::PropertyTrackerID getTrackerID()
        const override {
        return hstd::ext::graph::PropertyTrackerID(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }


    virtual void trackVertex(
        hstd::ext::graph::VertexID const& vertex) override;
    virtual void untrackVertex(
        hstd::ext::graph::VertexID const& vertex) override;
    virtual hstd::Vec<hstd::ext::graph::VertexID> getVertices(
        hstd::ext::graph::IProperty const& prop) override;
};

class DiaDescriptionListEdge : public hstd::ext::graph::IEdge {
    using IEdge::IEdge;

  public:
    org::imm::ImmAdapterT<org::imm::ImmListItem> item;
    hstd::Opt<org::imm::ImmAdapter>              edgeBrief;
    hstd::Vec<org::imm::ImmAdapter>              edgeDetailed;

    struct SerialSchema : public hstd::ext::graph::IEdge::SerialSchema {
        struct Extra {
            hstd::Opt<std::string> edgeBrief;
            hstd::Opt<std::string> edgeDetailed;
            hstd::Opt<json>        structuredEdgeBrief;
            hstd::Opt<json>        structuredEdgeDetailed;
            DESC_FIELDS(
                Extra,
                (edgeBrief,
                 edgeDetailed,
                 structuredEdgeBrief,
                 structuredEdgeDetailed));
        };

        BOOST_DESCRIBE_CLASS(
            SerialSchema,
            (hstd::ext::graph::IEdge::SerialSchema),
            (),
            (),
            ());
    };

    virtual json getSerialNonRecursive(
        hstd::ext::graph::IGraph const* graph,
        hstd::ext::graph::EdgeID const& id) const override;
};

class DiaDescriptionListEdgeCollection
    : public hstd::ext::graph::IEdgeCollection {
    hstd::SPtr<DiaGraph>            graph;
    hstd::SPtr<DiaSubtreeIdTracker> tracker;

    hstd::UnorderedStore<hstd::ext::graph::EdgeID, DiaDescriptionListEdge>
        store;

  public:
    DiaDescriptionListEdgeCollection(
        hstd::SPtr<DiaGraph> const&            graph,
        hstd::SPtr<DiaSubtreeIdTracker> const& tracker)
        : graph{graph}, tracker{tracker} {}

    virtual hstd::Vec<hstd::ext::graph::EdgeID> addAllOutgoing(
        hstd::ext::graph::VertexID const& vert) override;

    virtual hstd::ext::graph::EdgeCollectionID getCategory()
        const override {
        return hstd::ext::graph::EdgeCollectionID(
            hstd::hash_to_uint16(typeid(this).hash_code()));
    }

    virtual std::string getStableID() const override {
        return hstd::value_metadata<
            DiaDescriptionListEdgeCollection>::typeName();
    }

    virtual const hstd::ext::graph::IEdge& getEdge(
        hstd::ext::graph::EdgeID const& id) const override {
        return store.at(id);
    }
};
