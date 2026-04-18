#pragma once

#pragma clang diagnostic ignored "-Wunknown-attributes"

#pragma warning(push, 0)
#include <libavoid/libavoid.h>
#include <libdialect/graphs.h>
#pragma warning(pop)

#include <hstd/ext/geometry/hstd_geometry.hpp>
#include <hstd/ext/geometry/hstd_visual.hpp>
#include <hstd/ext/graph/graph_base.hpp>

namespace hstd::ext::graph::adapt {

geometry::Point   to_hstd(Avoid::Point const& input);
geometry::Rect    to_hstd(vpsc::Rectangle const& input);
geometry::Rect    to_hstd(Avoid::Rectangle const& input);
geometry::Rect    to_hstd_rect(Avoid::Polygon const& input);
geometry::Polygon to_hstd(Avoid::Polygon const& input);
geometry::Path    to_hstd_path(Avoid::Polygon const& input);
geometry::Path    to_hstd_path(cola::Edge const& input);


inline void add_checkpoint(
    visual::VisGroup&        g,
    Avoid::Checkpoint const& ch) {
    g.elements.push_back(
        visual::VisElement{visual::VisElement::EllipseShape{
            .geometry = geometry::Rect::FromCenterWH(
                to_hstd(ch.point), 5, 5)}});
}

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

inline void add_rect(visual::VisGroup& g, vpsc::Rectangle const& shape) {
    g.elements.push_back(
        visual::VisElement{visual::VisElement::RectShape{to_hstd(shape)}});
}


} // namespace hstd::ext::graph::adapt
