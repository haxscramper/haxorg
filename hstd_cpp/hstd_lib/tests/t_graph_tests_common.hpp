#include <gtest/gtest.h>

#include <hstd/extra/error_format/gtest_utils.hpp>
#include <hstd/geometry/hstd_geometry_test.hpp>
#include <hstd/graph/graph_base.hpp>
#include <hstd/stdlib/containers/MapSerde.hpp>
#include <hstd/stdlib/containers/VariantSerde.hpp>
#include <hstd/stdlib/serde/JsonSerde.hpp>

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
    void SetUp() override { state = hstd::ext::graph::TrivialState{}; }

    hstd::SPtr<TrivialGraph>     getGraph() const { return state.graph; }
    hstd::SPtr<TrivialHierarchy> getHierarchy() const { return state.hierarchy; }


    hstd::SPtr<TrivialPortCollection> getPorts() const { return state.ports; }

    VertexID addVertex(hstd::Str const& id_override) {
        return getGraph()->addVertex(id_override);
    }

    void trackHierarchyVertex(VertexID const& id) {
        if (!getHierarchy()->isTrackingVertex(id)) { getHierarchy()->trackVertex(id); }
    }

    EdgeID addNesting(VertexID const& parent, VertexID const& sub) {
        trackHierarchyVertex(parent);
        trackHierarchyVertex(sub);
        return getHierarchy()->trackSubVertexRelation(
            parent,
            sub,
            TrivialEdge{hstd::fmt(
                "{}-{}",
                state.graph->getStableId(parent),
                state.graph->getStableId(sub))});
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

    EdgeID addEdge(VertexID const& source, VertexID const& target) {
        return addEdge(
            source,
            target,
            hstd::fmt(
                "{}-{}",
                state.graph->getStableId(source),
                state.graph->getStableId(target)));
    }


    hstd::ext::graph::TrivialState state;
};
