#if ORG_BUILD_WITH_PROTOBUF

#    include <boost/outcome/result.hpp>
#    include <hstd/ext/geometry/hstd_geometry_test.hpp>
#    include <hstd/ext/geometry/hstd_geometry_test_ir.hpp>
#    include <hstd/stdlib/Filesystem.hpp>
#    include <hstd/stdlib/Vec.hpp>
#    include <src/hstd/ext/geometry/hstd_geometry_test_ir.pb.h>
#    include <src/hstd/ext/graph/visual/graph_diagram.pb.h>
#    include <src/hstd/ext/graph/visual/graph_diagram_validate.pb.h>

namespace hstd::ext::graph::diagram {
hstd::ext::geometry::GeometryElementListResult diagramGeometryElements(
    graph::diagram::proto::DiaCluster const& root);
}

hstd::ext::geometry::GeometryValidationErrors runSpec(
    hstd::ext::graph::diagram::proto::DiagramTest const& test,
    hstd::Opt<hstd::fs::path> const&                     debug_dir = std::nullopt);

#endif
