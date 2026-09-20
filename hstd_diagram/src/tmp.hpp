#include <hstd/ext/graph/visual/adaptagrams_common.hpp>
#include <hstd/ext/graph/visual/graph_elk.hpp>
#include <hstd/ext/graph/visual/graph_graphviz.hpp>
#include <hstd/ext/graph/visual/graph_kiwi.hpp>
#include <libcola/output_svg.h>

#include <libdialect/hola.h>
#include <libdialect/opts.h>


hstd::SPtr<hstd::ext::graph::gv::GraphGroup> get_graphviz(
    hstd::SPtr<hstd::ext::graph::layout::LayoutRun> const& run);


// from graph tests common class fixture

// old version of the setup
void SetUp() override {
    state = layout::LayoutRun::TrivialState{};
    run   = state.init();
    run->setTraceFile(getDebugFile("layout_trace.log"));
}

geometry::Rect box(VertexID const& id) { return run->getAbsoluteBBox(id); }

void writeVisual() {
    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());

#if ORG_BUILD_WITH_PROTOBUF
    hstd::ext::graph::proto::IGraph out;
    state.graph->writeSerial(&out);
    hstd::writeFile(getDebugFile("serial.json"), hstd::serde::getJString(out));
#endif
}


hstd::SPtr<layout::LayoutRun> run;

hstd::SPtr<gv::GraphGroup> getGvGroup(VertexID const& id) {
    return run->getGroup<gv::GraphGroup>(id);
}

hstd::SPtr<gv::NodeAttribute> getGv(VertexID const& id) {
    return getGraph()->getVertex(id)->getUniqueAttribute<gv::NodeAttribute>();
}

hstd::SPtr<gv::EdgeAttribute> getGv(EdgeID const& id) {
    return getGraph()->getEdge(id)->getUniqueAttribute<gv::EdgeAttribute>();
}
