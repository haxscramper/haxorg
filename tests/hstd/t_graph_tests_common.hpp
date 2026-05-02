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

struct TestVertex : public TrivialVertex {};
struct TestEdge : public TrivialEdge {};
struct TestEdgeCollection : public TrivialEdgeCollection {};
struct TestGraph : public TrivialGraph {};


class GraphUtils_Test : public ::testing::Test {
  protected:
    void SetUp() override {
        graph = std::make_shared<TestGraph>();
        run   = std::make_shared<layout::LayoutRun>(graph);
        run->setTraceFile(getDebugFile("layout_trace.log"));
    }

    VertexID addVertex(hstd::Str const& id_override) {
        auto res = graph->addVertex();
        graph->getCastMVertex<TrivialVertex>(res)
            ->stableIdOverride = id_override;
        return res;
    }

    hstd::SPtr<TestGraph>         graph;
    hstd::SPtr<layout::LayoutRun> run;
    hstd::SPtr<TrivialHierarchy>  hierarchy;

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
