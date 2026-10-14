#include <gtest/gtest.h>

#include <hstd_cpp_diagram_lib/avoid/graph_avoid.hpp>
#include <hstd_cpp_diagram_lib/elk/graph_elk.hpp>
#include <hstd_cpp_diagram_lib/graphviz/graph_graphviz.hpp>
#include <hstd_cpp_diagram_lib/kiwi/graph_kiwi.hpp>
#include <hstd_cpp_lib/extra/error_format/gtest_utils.hpp>
#include <hstd_cpp_lib/geometry/hstd_geometry_test.hpp>
#include <hstd_cpp_lib/graph/graph_base.hpp>
#include <hstd_cpp_lib/stdlib/containers/MapSerde.hpp>
#include <hstd_cpp_lib/stdlib/containers/VariantSerde.hpp>
#include <hstd_cpp_lib/stdlib/serde/JsonSerde.hpp>

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
        state = hstd::ext::graph::TrivialState{};
        run   = hstd::ext::graph::layout::initLayoutRun(state);
        run->setTraceFile(getDebugFile("layout_trace.log"));
    }

    void writeVisual() {
        auto visual = run->getVisual();
        hstd::writeFile(
            getDebugFile("result.svg"),
            hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());

        hstd::ext::graph::proto::IGraph out;
        state.graph->writeSerial(&out);
        hstd::writeFile(getDebugFile("serial.json"), hstd::serde::getJString(out));
    }

    hstd::SPtr<TrivialGraph>     getGraph() const { return state.graph; }
    hstd::SPtr<TrivialHierarchy> getHierarchy() const { return state.hierarchy; }

    geometry::Rect box(VertexID const& id) { return run->getAbsoluteBBox(id); }

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

    hstd::SPtr<layout::LayoutRun>  run;
    hstd::ext::graph::TrivialState state;

    hstd::SPtr<gv::GraphGroup> getGvGroup(VertexID const& id) {
        return run->getGroup<gv::GraphGroup>(id);
    }

    hstd::SPtr<gv::NodeAttribute> getGv(VertexID const& id) {
        return getGraph()->getVertex(id)->getUniqueAttribute<gv::NodeAttribute>();
    }

    hstd::SPtr<gv::EdgeAttribute> getGv(EdgeID const& id) {
        return getGraph()->getEdge(id)->getUniqueAttribute<gv::EdgeAttribute>();
    }
};
