#include <gtest/gtest.h>
#include <adaptagrams/adaptagrams_ir.hpp>

#include <hstd/ext/graph/graph_base.hpp>
#include <hstd/ext/graph/graph_graphviz.hpp>
#include <hstd/ext/graph/graph_cola.hpp>
#include <hstd/ext/graph/adaptagrams_common.hpp>

#include <libdialect/hola.h>
#include <libdialect/opts.h>

#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/ext/geometry/hstd_geometry_test.hpp>
#include "../common.hpp"
#include <libcola/output_svg.h>
#include <utility>

template <typename A, typename T>
hstd::SPtr<A> as(hstd::SPtr<T> const& value) {
    auto result = std::dynamic_pointer_cast<A>(value);
    hstd::logic_assertion_check_not_nil(result);
    return result;
}

using namespace hstd::ext::graph;
using namespace hstd::ext;
using namespace hstd;


struct TestVertex : public IVertex {
    VertexID selfId;
    TestVertex(VertexID selfId) : selfId{selfId} {}

    std::size_t getHash() const override {
        hstd::logic_assertion_check_not_nil(this);
        return std::hash<VertexID>{}(selfId);
    }

    bool isEqual(IGraphObjectBase const* other) const override {
        return this->selfId
            == dynamic_cast<TestVertex const*>(other)->selfId;
    }

    std::string getRepr() const override {
        return hstd::fmt("IVertex({})", selfId);
    }

    json getSerialNonRecursive(IGraph const* graph, VertexID const& id)
        const override {
        return json{};
    }

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }

    std::string getStableId() const override {
        return hstd::fmt("test-vertex-{}", selfId);
    }

    void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};


struct TestEdge : public IEdge {
    using IEdge::IEdge;

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }


    void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};

struct TestEdgeCollection : public IEdgeCollection {
  public:
    hstd::UnorderedIncrementalStore<EdgeID, TestEdge> edgeStore;

    EdgeCollectionID getCategory() const override {
        return getCollectionIdImpl(this);
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return &edgeStore.at(id);
    }

    EdgeIDSet addAllOutgoing(VertexID const& id) override { return {}; }
};

struct TestGraph : public IGraph {
    hstd::UnorderedIncrementalStore<VertexID, TestVertex> vertexStore;
    hstd::SPtr<TestEdgeCollection>                        edges;

    TestGraph() : edges{std::make_shared<TestEdgeCollection>()} {
        addCollection(edges);
    }

    VertexID addVertex() {
        auto result = vertexStore.add(TestVertex{vertexStore.getNextId()});
        trackVertex(result);
        return result;
    }

    const IVertex* getVertex(VertexID const& id) const override {
        return &vertexStore.at(id);
    }

    EdgeID addEdge(VertexID const& source, VertexID const& target) {
        auto result = edges->edgeStore.add(
            TestEdge{source, target}, edges->getCategory());
        edges->trackEdge(result);
        return result;
    }
};


class GraphUtils_Test : public ::testing::Test {
  protected:
    void SetUp() override {
        graph = std::make_shared<TestGraph>();
        run   = std::make_shared<layout::LayoutRun>(graph);
        run->setTraceFile(getDebugFile("layout_trace.log"));
    }

    hstd::SPtr<TestGraph>         graph;
    hstd::SPtr<layout::LayoutRun> run;

    hstd::SPtr<gv::GraphGroup> getGvGroup(VertexID const& id) {
        return run->getGroup<gv::GraphGroup>(id);
    }

    hstd::SPtr<gv::NodeAttribute> getGv(VertexID const& id) {
        return graph->getVertex(id)
            ->getUniqueAttribute<gv::NodeAttribute>();
    }

    hstd::SPtr<gv::EdgeAttribute> getGv(EdgeID const& id) {
        return graph->getEdge(id)->getUniqueAttribute<gv::EdgeAttribute>();
    }

    hstd::SPtr<cst::ColaGroup> getColaGroup(VertexID const& id) {
        return run->getGroup<cst::ColaGroup>(id);
    }

    hstd::SPtr<cst::ColaVertexAttribute> getCola(VertexID const& id) {
        return graph->getVertex(id)
            ->getUniqueAttribute<cst::ColaVertexAttribute>();
    }

    hstd::SPtr<cst::ColaEdgeAttribute> getCola(EdgeID const& id) {
        return graph->getEdge(id)
            ->getUniqueAttribute<cst::ColaEdgeAttribute>();
    }
};
