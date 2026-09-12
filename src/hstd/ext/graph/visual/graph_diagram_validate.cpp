#include "graph_diagram_validate.hpp"
#include "hstd/ext/graph/base/graph_base.hpp"
#include "hstd/ext/graph/visual/graph_diagram.hpp"
#include "hstd/ext/graph/visual/visual_factory.hpp"
#include "hstd/ext/hstd_serde_json_interop.hpp"
#include "hstd/stdlib/ExceptionSerde.hpp"
#include <hstd/stdlib/MapSerde.hpp>
#include <hstd/stdlib/OutcomeSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>

#if ORG_BUILD_WITH_PROTOBUF

#    include <hstd/ext/geometry/hstd_geometry.hpp>
#    include <hstd/ext/geometry/hstd_geometry_serde.hpp>
#    include <hstd/stdlib/Formatter.hpp>

#    include <string>
#    include <unordered_set>
#    include <utility>

namespace hstd {
template <>
struct JsonSerde<ext::geometry::GeometryError>
    : public JsonSerdeHexception<ext::geometry::GeometryError> {};


template <>
struct JsonSerde<ext::geometry::proto::GeometryCheck>
    : public JsonSerdeProtobufValue<ext::geometry::proto::GeometryCheck> {};
} // namespace hstd

namespace hstd::ext::graph::diagram {
namespace {

namespace geometry = hstd::ext::geometry;

struct Offset {
    double x = 0.0;
    double y = 0.0;
};

using ElementIds = std::unordered_set<std::string>;

geometry::GeometryElementListResult failure(std::string const& message) {
    return boost::outcome_v2::failure(geometry::GeometryError::init(message));
}

bool registerId(ElementIds& ids, std::string const& id) { return ids.insert(id).second; }

hstd::ext::geometry::proto::Rect translateRect(
    hstd::ext::geometry::proto::Rect const& input,
    Offset                                  offset) {
    hstd::ext::geometry::proto::Rect result = input;
    result.set_x(input.x() + offset.x);
    result.set_y(input.y() + offset.y);
    return result;
}

void translatePoint(hstd::ext::geometry::proto::Point* point, Offset offset) {
    point->set_x(point->x() + offset.x);
    point->set_y(point->y() + offset.y);
}

hstd::ext::geometry::proto::Path translatePath(
    hstd::ext::geometry::proto::Path const& input,
    Offset                                  offset) {
    hstd::ext::geometry::proto::Path result = input;

    for (auto& command : *result.mutable_commands()) {
        if (command.has_p1()) { translatePoint(command.mutable_p1(), offset); }
        if (command.has_p2()) { translatePoint(command.mutable_p2(), offset); }
        if (command.has_p3()) { translatePoint(command.mutable_p3(), offset); }
    }

    return result;
}

geometry::GeometryElement makeRectElement(
    std::string const&                      id,
    hstd::ext::geometry::proto::Rect const& rect) {
    return geometry::GeometryElement{
        .id    = id,
        .shape = hstd::serde::read_serde<geometry::Rect>(rect),
    };
}

geometry::GeometryElement makePathElement(
    std::string const&                      id,
    hstd::ext::geometry::proto::Path const& path) {
    return geometry::GeometryElement{
        .id    = id,
        .shape = hstd::serde::read_serde<geometry::Path>(path),
    };
}

boost::outcome_v2::result<void, geometry::GeometryError> appendCluster(
    graph::diagram::proto::DiaCluster const& cluster,
    Offset                                   parentOffset,
    bool                                     isRoot,
    ElementIds&                              ids,
    geometry::GeometryElementList&           output) {
    if (cluster.id().empty()) {
        return boost::outcome_v2::failure(
            geometry::GeometryError::init("Diagram cluster has an empty ID"));
    }

    if (!registerId(ids, cluster.id())) {
        return boost::outcome_v2::failure(
            geometry::GeometryError::init(
                hstd::fmt("Duplicate diagram geometry ID '{}'", cluster.id())));
    }

    if (!cluster.has_bbox()) {
        return boost::outcome_v2::failure(
            geometry::GeometryError::init(
                hstd::fmt("Diagram cluster '{}' does not define bbox", cluster.id())));
    }

    auto absoluteClusterRect = translateRect(cluster.bbox(), parentOffset);

    output.push_back(makeRectElement(cluster.id(), absoluteClusterRect));

    Offset clusterContentOffset{
        .x = absoluteClusterRect.x(),
        .y = absoluteClusterRect.y(),
    };

    for (auto const& node : cluster.nodes()) {
        if (node.id().empty()) {
            return boost::outcome_v2::failure(
                geometry::GeometryError::init(
                    hstd::fmt(
                        "Cluster '{}' contains a node with an empty ID", cluster.id())));
        }

        if (!registerId(ids, node.id())) {
            return boost::outcome_v2::failure(
                geometry::GeometryError::init(
                    hstd::fmt("Duplicate diagram geometry ID '{}'", node.id())));
        }

        if (!node.has_bbox()) {
            return boost::outcome_v2::failure(
                geometry::GeometryError::init(
                    hstd::fmt("Diagram node '{}' does not define bbox", node.id())));
        }

        output.push_back(
            makeRectElement(node.id(), translateRect(node.bbox(), clusterContentOffset)));
    }

    for (auto const& edge : cluster.edges()) {
        if (edge.id().empty()) {
            return boost::outcome_v2::failure(
                geometry::GeometryError::init(
                    hstd::fmt(
                        "Cluster '{}' contains an edge with an empty ID", cluster.id())));
        }

        if (!registerId(ids, edge.id())) {
            return boost::outcome_v2::failure(
                geometry::GeometryError::init(
                    hstd::fmt("Duplicate diagram geometry ID '{}'", edge.id())));
        }

        if (!edge.has_path()) {
            return boost::outcome_v2::failure(
                geometry::GeometryError::init(
                    hstd::fmt("Diagram edge '{}' does not define path", edge.id())));
        }

        output.push_back(
            makePathElement(edge.id(), translatePath(edge.path(), clusterContentOffset)));
    }

    for (auto const& nested : cluster.nested()) {
        auto result = appendCluster(nested, clusterContentOffset, false, ids, output);

        if (!result) { return result; }
    }

    return boost::outcome_v2::success();
}

} // namespace

hstd::ext::geometry::GeometryElementListResult hstd::ext::graph::diagram::
    diagramGeometryElements(graph::diagram::proto::DiaCluster const& root) {
    geometry::GeometryElementList result;
    ElementIds                    ids;

    auto conversion = appendCluster(root, Offset{}, true, ids, result);

    if (!conversion) { return boost::outcome_v2::failure(conversion.error()); }

    return result;
}

hstd::ext::geometry::GeometryValidationErrors hstd::ext::graph::diagram::runSpec(
    hstd::ext::graph::diagram::proto::DiagramTest const& test,
    hstd::Opt<hstd::fs::path> const&                     debug_dir) {
    auto proto_layout = hstd::ext::graph::diagram::diaClusterToGraph(test.diagram());
    auto graph        = std::make_shared<hstd::ext::graph::TrivialGraphBase>();
    hstd::ext::graph::VisualFactory factory{graph};

    if (debug_dir) { factory.setTraceFile(debug_dir.value() / "serial.log"); }
    graph->readSerial(&proto_layout, &factory);

    if (debug_dir) { factory.run->setTraceFile(debug_dir.value() / "layout.log"); }
    factory.run->runFullLayout();

    if (debug_dir) {
        auto visual = factory.run->getVisual();
        hstd::writeFile(
            debug_dir.value() / "visual.json", hstd::to_json_eval(visual).dump(2));

        hstd::writeFile(
            debug_dir.value() / "visual.svg",
            hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
    }

    auto result = std::make_unique<hstd::ext::graph::proto::IGraph>();
    graph->writeSerial(result.get());

    if (debug_dir) {
        hstd::writeFile(
            debug_dir.value() / "post-layout-graph.json",
            hstd::serde::getJString(*result));
    }

    auto simplified_result = hstd::ext::graph::diagram::graphToDiaCluster(*result);

    if (debug_dir) {
        hstd::writeFile(
            debug_dir.value() / "post-layout-diagram.json",
            hstd::serde::getJString(simplified_result));
    }

    auto elements = diagramGeometryElements(simplified_result);

    if (debug_dir) {
        hstd::writeFile(
            debug_dir.value() / "diagram-elements.json",
            hstd::to_json_eval(elements).dump(2));
    }

    auto validated = validateGeometry(elements, test.checks());

    if (debug_dir) {
        hstd::writeFile(
            debug_dir.value() / "validated.json", hstd::to_json_eval(validated).dump(2));
    }

    return validated;
}


} // namespace hstd::ext::graph::diagram

#endif
