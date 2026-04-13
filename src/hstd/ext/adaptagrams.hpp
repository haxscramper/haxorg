#pragma once

#pragma clang diagnostic ignored "-Wunknown-attributes"

#pragma warning(push, 0)
#include <libavoid/libavoid.h>
#include <libdialect/graphs.h>
#pragma warning(pop)

#include <hstd/ext/hstd_geometry.hpp>
#include <hstd/ext/hstd_graph.hpp>
#include <hstd/ext/hstd_visual.hpp>

namespace hstd::ext::graph::adapt {

geometry::Point   to_hstd(Avoid::Point const& input);
geometry::Rect    to_hstd(Avoid::Rectangle const& input);
geometry::Rect    to_hstd_rect(Avoid::Polygon const& input);
geometry::Polygon to_hstd(Avoid::Polygon const& input);
geometry::Path    to_hstd_path(Avoid::Polygon const& input);

inline void add_rect(visual::VisGroup& g, Avoid::Polygon const& shape) {
    g.elements.push_back(
        visual::VisElement{
            visual::VisElement::RectShape{to_hstd_rect(shape)}});
}

inline void add_path(visual::VisGroup& g, Avoid::Polygon const& shape) {
    g.elements.push_back(
        visual::VisElement{
            visual::VisElement::PathShape{to_hstd_path(shape)}});
}


} // namespace hstd::ext::graph::adapt
