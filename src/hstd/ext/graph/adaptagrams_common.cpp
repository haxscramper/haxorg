#include "adaptagrams_common.hpp"

namespace hstd::ext::graph::adapt {


geometry::Point to_hstd(Avoid::Point const& input) {
    return geometry::Point(input.x, input.y);
}

geometry::Rect to_hstd(Avoid::Rectangle const& input) {
    auto bbox = input.offsetBoundingBox(0);
    return geometry::Rect(
        bbox.min.x, bbox.min.y, bbox.width(), bbox.height());
}

geometry::Rect to_hstd(vpsc::Rectangle const& input) {
    return geometry::Rect(
        input.getMinX(),
        input.getMinY(),
        input.getMaxX() - input.getMinX(),
        input.getMaxY() - input.getMinY());
}

geometry::Rect to_hstd_rect(Avoid::Polygon const& input) {
    auto bbox = input.offsetBoundingBox(0);
    return geometry::Rect(
        bbox.min.x, bbox.min.y, bbox.width(), bbox.height());
}

geometry::Polygon to_hstd(Avoid::Polygon const& input) {
    geometry::Polygon result;
    for (int i = 0; i < input.size(); ++i) {
        result.push_back(to_hstd(input.at(i)));
    }

    return result;
}

geometry::Path to_hstd_path(Avoid::Polygon const& input) {
    geometry::Path result;
    for (int i = 0; i < input.size(); ++i) {
        if (i == 0) {
            result.moveTo(to_hstd(input.at(i)));
        } else {
            result.lineTo(to_hstd(input.at(i)));
        }
    }

    return result;
}


} // namespace hstd::ext::graph::adapt
