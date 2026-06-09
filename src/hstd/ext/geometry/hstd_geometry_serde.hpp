#pragma once

#include <hstd/ext/geometry/hstd_geometry.hpp>
#include <src/hstd/ext/geometry/hstd_geometry.pb.h>
#include <hstd/ext/hstd_serde.hpp>

namespace hstd::serde {

template <>
struct proto_serde<ext::geometry::proto::Point, ext::geometry::Point> {
    static void write(
        ext::geometry::proto::Point* out,
        ext::geometry::Point const&  in);
    static void read(
        ext::geometry::proto::Point const& in,
        ext::geometry::Point*              out);
};

template <>
struct proto_serde<ext::geometry::proto::Point, ext::geometry::Size> {
    static void write(
        ext::geometry::proto::Point* out,
        ext::geometry::Size const&   in);
    static void read(
        ext::geometry::proto::Point const& in,
        ext::geometry::Size*               out);
};

template <>
struct proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect> {
    static void write(
        ext::geometry::proto::Rect* out,
        ext::geometry::Rect const&  in);
    static void read(
        ext::geometry::proto::Rect const& in,
        ext::geometry::Rect*              out);
};

template <>
struct proto_serde<ext::geometry::proto::Polygon, ext::geometry::Polygon> {
    static void write(
        ext::geometry::proto::Polygon* out,
        ext::geometry::Polygon const&  in);
    static void read(
        ext::geometry::proto::Polygon const& in,
        ext::geometry::Polygon*              out);
};

template <>
struct proto_serde<
    ext::geometry::proto::Path::Command,
    ext::geometry::Path::Command> {
    static void write(
        ext::geometry::proto::Path::Command* out,
        ext::geometry::Path::Command const&  in);
    static void read(
        ext::geometry::proto::Path::Command const& in,
        ext::geometry::Path::Command*              out);
};

template <>
struct proto_serde<ext::geometry::proto::Path, ext::geometry::Path> {
    static void write(
        ext::geometry::proto::Path* out,
        ext::geometry::Path const&  in);
    static void read(
        ext::geometry::proto::Path const& in,
        ext::geometry::Path*              out);
};

template <>
struct proto_serde<ext::geometry::proto::Padding, ext::geometry::Padding> {
    static void write(
        ext::geometry::proto::Padding* out,
        ext::geometry::Padding const&  in);
    static void read(
        ext::geometry::proto::Padding const& in,
        ext::geometry::Padding*              out);
};
} // namespace hstd::serde
