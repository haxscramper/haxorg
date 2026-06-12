#pragma once

#if ORG_BUILD_WITH_PROTOBUF

#    include <hstd/ext/geometry/hstd_visual.hpp>
#    include <src/hstd/ext/geometry/hstd_visual.pb.h>

namespace hstd::serde {

template <typename Proto, typename T>
struct proto_serde;

template <>
struct proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor> {
    static void write(
        ext::visual::proto::VisColor* out,
        ext::visual::VisColor const&  in);
    static void read(
        ext::visual::proto::VisColor const& in,
        ext::visual::VisColor*              out);
};

template <>
struct proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen> {
    static void write(
        ext::visual::proto::VisPen* out,
        ext::visual::VisPen const&  in);
    static void read(
        ext::visual::proto::VisPen const& in,
        ext::visual::VisPen*              out);
};

template <>
struct proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush> {
    static void write(
        ext::visual::proto::VisBrush* out,
        ext::visual::VisBrush const&  in);
    static void read(
        ext::visual::proto::VisBrush const& in,
        ext::visual::VisBrush*              out);
};

template <>
struct proto_serde<ext::visual::proto::VisFont, ext::visual::VisFont> {
    static void write(
        ext::visual::proto::VisFont* out,
        ext::visual::VisFont const&  in);
    static void read(
        ext::visual::proto::VisFont const& in,
        ext::visual::VisFont*              out);
};

template <>
struct proto_serde<
    ext::visual::proto::VisTextAlign,
    ext::visual::VisTextAlign> {
    static void write(
        ext::visual::proto::VisTextAlign* out,
        ext::visual::VisTextAlign const&  in);
    static void read(
        ext::visual::proto::VisTextAlign const& in,
        ext::visual::VisTextAlign*              out);
};

template <>
struct proto_serde<ext::visual::proto::VisCustom, ext::visual::VisCustom> {
    static void write(
        ext::visual::proto::VisCustom* out,
        ext::visual::VisCustom const&  in);
    static void read(
        ext::visual::proto::VisCustom const& in,
        ext::visual::VisCustom*              out);
};

template <>
struct proto_serde<
    ext::visual::proto::RectShape,
    ext::visual::VisElement::RectShape> {
    static void write(
        ext::visual::proto::RectShape*            out,
        ext::visual::VisElement::RectShape const& in);
    static void read(
        ext::visual::proto::RectShape const& in,
        ext::visual::VisElement::RectShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::EllipseShape,
    ext::visual::VisElement::EllipseShape> {
    static void write(
        ext::visual::proto::EllipseShape*            out,
        ext::visual::VisElement::EllipseShape const& in);
    static void read(
        ext::visual::proto::EllipseShape const& in,
        ext::visual::VisElement::EllipseShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::LineShape,
    ext::visual::VisElement::LineShape> {
    static void write(
        ext::visual::proto::LineShape*            out,
        ext::visual::VisElement::LineShape const& in);
    static void read(
        ext::visual::proto::LineShape const& in,
        ext::visual::VisElement::LineShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::PathShape,
    ext::visual::VisElement::PathShape> {
    static void write(
        ext::visual::proto::PathShape*            out,
        ext::visual::VisElement::PathShape const& in);
    static void read(
        ext::visual::proto::PathShape const& in,
        ext::visual::VisElement::PathShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::PolygonShape,
    ext::visual::VisElement::PolygonShape> {
    static void write(
        ext::visual::proto::PolygonShape*            out,
        ext::visual::VisElement::PolygonShape const& in);
    static void read(
        ext::visual::proto::PolygonShape const& in,
        ext::visual::VisElement::PolygonShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::TextShape,
    ext::visual::VisElement::TextShape> {
    static void write(
        ext::visual::proto::TextShape*            out,
        ext::visual::VisElement::TextShape const& in);
    static void read(
        ext::visual::proto::TextShape const& in,
        ext::visual::VisElement::TextShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::PixmapShape,
    ext::visual::VisElement::PixmapShape> {
    static void write(
        ext::visual::proto::PixmapShape*            out,
        ext::visual::VisElement::PixmapShape const& in);
    static void read(
        ext::visual::proto::PixmapShape const& in,
        ext::visual::VisElement::PixmapShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::PointShape,
    ext::visual::VisElement::PointShape> {
    static void write(
        ext::visual::proto::PointShape*            out,
        ext::visual::VisElement::PointShape const& in);
    static void read(
        ext::visual::proto::PointShape const& in,
        ext::visual::VisElement::PointShape*  out);
};

template <>
struct proto_serde<
    ext::visual::proto::VisElementData,
    ext::visual::VisElement::Data> {
    static void write(
        ext::visual::proto::VisElementData*  out,
        ext::visual::VisElement::Data const& in);
    static void read(
        ext::visual::proto::VisElementData const& in,
        ext::visual::VisElement::Data*            out);
};

template <>
struct proto_serde<
    ext::visual::proto::VisElement,
    ext::visual::VisElement> {
    static void write(
        ext::visual::proto::VisElement* out,
        ext::visual::VisElement const&  in);
    static void read(
        ext::visual::proto::VisElement const& in,
        ext::visual::VisElement*              out);
};

template <>
struct proto_serde<ext::visual::proto::VisGroup, ext::visual::VisGroup> {
    static void write(
        ext::visual::proto::VisGroup* out,
        ext::visual::VisGroup const&  in);
    static void read(
        ext::visual::proto::VisGroup const& in,
        ext::visual::VisGroup*              out);
};

} // namespace hstd::serde

#endif
