#pragma once

#include <src/hstd/ext/graph/visual/graph_diagram.pb.h>

namespace hstd::ext::graph::diagram {

hstd::ext::graph::diagram::proto::DiaCluster graphToDiaCluster(
    hstd::ext::graph::proto::IGraph const& graph,
    bool                                   preserveOrigin = false);

hstd::ext::graph::proto::IGraph diaClusterToGraph(
    hstd::ext::graph::diagram::proto::DiaCluster const& root);

} // namespace hstd::ext::graph::diagram
