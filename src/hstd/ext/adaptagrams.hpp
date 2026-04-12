#pragma once

#pragma clang diagnostic ignored "-Wunknown-attributes"

#pragma warning(push, 0)
#include <libavoid/libavoid.h>
#include <libdialect/graphs.h>
#pragma warning(pop)

#include <hstd/ext/hstd_geometry.hpp>
#include <hstd/ext/hstd_graph.hpp>

namespace hstd::ext::graph::adapt {


inline geometry::Point to_hstd(Avoid::Point const& input) {
    return geometry::Point(input.x, input.y);
}

inline geometry::Rect to_hstd(Avoid::Rectangle const& input) {
    auto bbox = input.offsetBoundingBox(0);
    return geometry::Rect(
        bbox.min.x, bbox.min.y, bbox.width(), bbox.height());
}

inline geometry::Polygon to_hstd(Avoid::Polygon const& input) {
    geometry::Polygon result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(to_hstd(input.at(i)));
    }

    return result;
}

} // namespace hstd::ext::graph::adapt
