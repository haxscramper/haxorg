#include <gtest/gtest.h>

#include <hstd/ext/graph/base/graph_base.hpp>
#include <hstd/ext/graph/visual/graph_graphviz.hpp>
#include <hstd/ext/graph/visual/graph_cola.hpp>
#include <hstd/ext/graph/visual/adaptagrams_common.hpp>
#include <hstd/ext/graph/visual/graph_elk.hpp>

#include <libdialect/hola.h>
#include <libdialect/opts.h>

#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/ext/geometry/hstd_geometry_test.hpp>
#include "../common.hpp"
#include <libcola/output_svg.h>
#include <utility>
#include <hstd/stdlib/MapSerde.hpp>

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
        state = layout::LayoutRun::TrivialState{};
        run   = state.init();
        run->setTraceFile(getDebugFile("layout_trace.log"));
    }

    hstd::SPtr<TrivialGraph>     getGraph() const { return state.graph; }
    hstd::SPtr<TrivialHierarchy> getHierarchy() const {
        return state.hierarchy;
    }

    hstd::SPtr<TrivialPortCollection> getPorts() const {
        return state.ports;
    }

    VertexID addVertex(hstd::Str const& id_override) {
        return getGraph()->addVertex(id_override);
    }

    EdgeID addNesting(VertexID const& parent, VertexID const& sub) {
        return getHierarchy()->trackSubVertexRelation(parent, sub);
    }

    PortID addPort(
        VertexID const&  v,
        EdgeID const&    e,
        bool             is_start,
        hstd::Str const& id_override) {
        return getPorts()->addPort(v, e, is_start, id_override);
    }

    PortID addPort(VertexID const& v, EdgeID const& e, bool is_start) {
        return addPort(
            v,
            e,
            is_start,
            hstd::fmt(
                "P-{}-{}-{}",
                getGraph()->getVertex(v)->getStableId(),
                getGraph()->getEdge(e)->getStableId(),
                is_start ? "s" : "e"));
    }

    EdgeID addEdge(
        VertexID const&  source,
        VertexID const&  target,
        hstd::Str const& id_override) {
        return getGraph()->addEdge(source, target, id_override);
    }

    hstd::SPtr<layout::LayoutRun>   run;
    layout::LayoutRun::TrivialState state;

    hstd::SPtr<gv::GraphGroup> getGvGroup(VertexID const& id) {
        return run->getGroup<gv::GraphGroup>(id);
    }

    hstd::SPtr<gv::NodeAttribute> getGv(VertexID const& id) {
        return getGraph()
            ->getVertex(id)
            ->getUniqueAttribute<gv::NodeAttribute>();
    }

    hstd::SPtr<gv::EdgeAttribute> getGv(EdgeID const& id) {
        return getGraph()
            ->getEdge(id)
            ->getUniqueAttribute<gv::EdgeAttribute>();
    }

    hstd::SPtr<cst::ColaGroup> getColaGroup(VertexID const& id) {
        return run->getGroup<cst::ColaGroup>(id);
    }

    hstd::SPtr<cst::ColaVertexAttribute> getCola(VertexID const& id) {
        return getGraph()
            ->getVertex(id)
            ->getUniqueAttribute<cst::ColaVertexAttribute>();
    }

    hstd::SPtr<cst::ColaEdgeAttribute> getCola(EdgeID const& id) {
        return getGraph()
            ->getEdge(id)
            ->getUniqueAttribute<cst::ColaEdgeAttribute>();
    }
};
