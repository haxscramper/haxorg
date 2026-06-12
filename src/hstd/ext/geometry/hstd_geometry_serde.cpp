#include "hstd_geometry_serde.hpp"

#if ORG_BUILD_WITH_PROTOBUF

using namespace hstd::ext::geometry;


void hstd::serde::proto_serde<proto::Point, Point>::write(
    proto::Point* out,
    Point const&  in) {
    out->set_x(in.x());
    out->set_y(in.y());
}

void hstd::serde::proto_serde<proto::Point, Point>::read(
    proto::Point const& in,
    Point*              out) {
    *out = Point(in.x(), in.y());
}

void hstd::serde::proto_serde<proto::Point, Size>::write(
    proto::Point* out,
    Size const&   in) {
    out->set_x(in.x());
    out->set_y(in.y());
}

void hstd::serde::proto_serde<proto::Point, Size>::read(
    proto::Point const& in,
    Size*               out) {
    *out = Size(in.x(), in.y());
}

void hstd::serde::proto_serde<proto::Rect, Rect>::write(
    proto::Rect* out,
    Rect const&  in) {
    double const x0 = in.min_corner().x();
    double const y0 = in.min_corner().y();
    double const x1 = in.max_corner().x();
    double const y1 = in.max_corner().y();

    out->set_x(x0);
    out->set_y(y0);
    out->set_width(x1 - x0);
    out->set_height(y1 - y0);
}

void hstd::serde::proto_serde<proto::Rect, Rect>::read(proto::Rect const& in, Rect* out) {
    *out = Rect(in.x(), in.y(), in.width(), in.height());
}

void hstd::serde::proto_serde<proto::Polygon, Polygon>::write(
    proto::Polygon* out,
    Polygon const&  in) {
    out->clear_points();
    for (auto const& p : in.outer()) {
        auto* dst = out->add_points();
        hstd::serde::proto_serde<proto::Point, Point>::write(dst, p);
    }
}

void hstd::serde::proto_serde<proto::Polygon, Polygon>::read(
    proto::Polygon const& in,
    Polygon*              out) {
    out->outer().clear();
    out->outer().reserve(static_cast<std::size_t>(in.points_size()));
    for (auto const& p : in.points()) {
        Point dst;
        hstd::serde::proto_serde<proto::Point, Point>::read(p, &dst);
        out->outer().push_back(dst);
    }
}

void hstd::serde::proto_serde<proto::Path::Command, Path::Command>::write(
    proto::Path::Command* out,
    Path::Command const&  in) {
    out->set_type(static_cast<proto::Path_CommandType>(in.type));
    hstd::serde::proto_serde<proto::Point, Point>::write(out->mutable_p1(), in.p1);
    hstd::serde::proto_serde<proto::Point, Point>::write(out->mutable_p2(), in.p2);
    hstd::serde::proto_serde<proto::Point, Point>::write(out->mutable_p3(), in.p3);
}

void hstd::serde::proto_serde<proto::Path::Command, Path::Command>::read(
    proto::Path::Command const& in,
    Path::Command*              out) {
    out->type = static_cast<Path::CommandType>(in.type());
    hstd::serde::proto_serde<proto::Point, Point>::read(in.p1(), &out->p1);
    hstd::serde::proto_serde<proto::Point, Point>::read(in.p2(), &out->p2);
    hstd::serde::proto_serde<proto::Point, Point>::read(in.p3(), &out->p3);
}

void hstd::serde::proto_serde<proto::Path, Path>::write(
    proto::Path* out,
    Path const&  in) {
    out->clear_commands();
    for (auto const& cmd : in.commands) {
        auto* dst = out->add_commands();
        hstd::serde::proto_serde<proto::Path::Command, Path::Command>::write(dst, cmd);
    }
}

void hstd::serde::proto_serde<proto::Path, Path>::read(proto::Path const& in, Path* out) {
    out->commands.clear();
    out->commands.reserve(static_cast<std::size_t>(in.commands_size()));
    for (auto const& cmd : in.commands()) {
        Path::Command dst;
        hstd::serde::proto_serde<proto::Path::Command, Path::Command>::read(cmd, &dst);
        out->commands.push_back(dst);
    }
}

void hstd::serde::proto_serde<proto::Padding, Padding>::write(
    proto::Padding* out,
    Padding const&  in) {
    out->set_top(in.top);
    out->set_bottom(in.bottom);
    out->set_left(in.left);
    out->set_right(in.right);
}

void hstd::serde::proto_serde<proto::Padding, Padding>::read(
    proto::Padding const& in,
    Padding*              out) {
    *out = Padding(in.top(), in.bottom(), in.left(), in.right());
}

#endif
