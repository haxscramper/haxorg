#include "hstd_visual_serde.hpp"

#include <stdexcept>
#include <google/protobuf/struct.pb.h>
#include <google/protobuf/wrappers.pb.h>
#include <hstd/stdlib/Json.hpp>

#include <hstd/ext/geometry/hstd_geometry_serde.hpp>
#include <hstd/ext/hstd_serde.hpp>

using namespace hstd;

namespace hstd::serde {

void proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::
    write(
        ext::visual::proto::VisColor* out,
        ext::visual::VisColor const&  in) {
    out->set_r(static_cast<::google::protobuf::uint32>(in.r));
    out->set_g(static_cast<::google::protobuf::uint32>(in.g));
    out->set_b(static_cast<::google::protobuf::uint32>(in.b));
    out->set_a(static_cast<::google::protobuf::uint32>(in.a));
}

void proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::
    read(
        ext::visual::proto::VisColor const& in,
        ext::visual::VisColor*              out) {
    out->r = static_cast<uint8_t>(in.r());
    out->g = static_cast<uint8_t>(in.g());
    out->b = static_cast<uint8_t>(in.b());
    out->a = static_cast<uint8_t>(in.a());
}

void proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::write(
    ext::visual::proto::VisPen* out,
    ext::visual::VisPen const&  in) {
    proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::
        write(out->mutable_color(), in.color);
    out->set_width(in.width);
    out->set_style(
        static_cast<ext::visual::proto::VisPen_LineStyle>(
            static_cast<int>(in.style) + 1));
}

void proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::read(
    ext::visual::proto::VisPen const& in,
    ext::visual::VisPen*              out) {
    proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::read(
        in.color(), &out->color);
    out->width = in.width();
    out->style = (in.style()
                  == ext::visual::proto::
                      VisPen_LineStyle_LINE_STYLE_UNSPECIFIED)
                   ? static_cast<ext::visual::VisPen::LineStyle>(0)
                   : static_cast<ext::visual::VisPen::LineStyle>(
                         static_cast<int>(in.style()) - 1);
}

void proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::
    write(
        ext::visual::proto::VisBrush* out,
        ext::visual::VisBrush const&  in) {
    proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::
        write(out->mutable_color(), in.color);
    out->set_style(
        static_cast<ext::visual::proto::VisBrush_BrushStyle>(
            static_cast<int>(in.style) + 1));
}

void proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::
    read(
        ext::visual::proto::VisBrush const& in,
        ext::visual::VisBrush*              out) {
    proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::read(
        in.color(), &out->color);
    out->style = (in.style()
                  == ext::visual::proto::
                      VisBrush_BrushStyle_BRUSH_STYLE_UNSPECIFIED)
                   ? static_cast<ext::visual::VisBrush::BrushStyle>(0)
                   : static_cast<ext::visual::VisBrush::BrushStyle>(
                         static_cast<int>(in.style()) - 1);
}

void proto_serde<ext::visual::proto::VisFont, ext::visual::VisFont>::write(
    ext::visual::proto::VisFont* out,
    ext::visual::VisFont const&  in) {
    out->set_family(in.family);
    out->set_pixel_size(in.pixelSize);
    out->set_weight(
        static_cast<ext::visual::proto::VisFont_Weight>(
            static_cast<int>(in.weight) + 1));
    out->set_font_style(
        static_cast<ext::visual::proto::VisFont_FontStyle>(
            static_cast<int>(in.fontStyle) + 1));
}

void proto_serde<ext::visual::proto::VisFont, ext::visual::VisFont>::read(
    ext::visual::proto::VisFont const& in,
    ext::visual::VisFont*              out) {
    out->family    = in.family();
    out->pixelSize = in.pixel_size();
    out->weight    = (in.weight()
                      == ext::visual::proto::
                          VisFont_Weight_WEIGHT_UNSPECIFIED)
                       ? static_cast<ext::visual::VisFont::Weight>(0)
                       : static_cast<ext::visual::VisFont::Weight>(
                             static_cast<int>(in.weight()) - 1);
    out->fontStyle = (in.font_style()
                      == ext::visual::proto::
                          VisFont_FontStyle_FONT_STYLE_UNSPECIFIED)
                       ? static_cast<ext::visual::VisFont::FontStyle>(0)
                       : static_cast<ext::visual::VisFont::FontStyle>(
                             static_cast<int>(in.font_style()) - 1);
}

void proto_serde<
    ext::visual::proto::VisTextAlign,
    ext::visual::VisTextAlign>::
    write(
        ext::visual::proto::VisTextAlign* out,
        ext::visual::VisTextAlign const&  in) {
    out->set_horizontal(
        static_cast<ext::visual::proto::VisTextAlign_HAlign>(
            static_cast<int>(in.horizontal) + 1));
    out->set_vertical(
        static_cast<ext::visual::proto::VisTextAlign_VAlign>(
            static_cast<int>(in.vertical) + 1));
}

void proto_serde<
    ext::visual::proto::VisTextAlign,
    ext::visual::VisTextAlign>::
    read(
        ext::visual::proto::VisTextAlign const& in,
        ext::visual::VisTextAlign*              out) {
    out->horizontal = (in.horizontal()
                       == ext::visual::proto::
                           VisTextAlign_HAlign_H_ALIGN_UNSPECIFIED)
                        ? static_cast<ext::visual::VisTextAlign::HAlign>(0)
                        : static_cast<ext::visual::VisTextAlign::HAlign>(
                              static_cast<int>(in.horizontal()) - 1);
    out->vertical   = (in.vertical()
                       == ext::visual::proto::
                           VisTextAlign_VAlign_V_ALIGN_UNSPECIFIED)
                        ? static_cast<ext::visual::VisTextAlign::VAlign>(0)
                        : static_cast<ext::visual::VisTextAlign::VAlign>(
                              static_cast<int>(in.vertical()) - 1);
}

void proto_serde<ext::visual::proto::VisCustom, ext::visual::VisCustom>::
    write(
        ext::visual::proto::VisCustom* out,
        ext::visual::VisCustom const&  in) {
    json_to_struct(in.extra, out->mutable_extra());

    out->clear_comment();
    for (auto const& it : in.comment) { out->add_comment(it); }

    if (in.title.has_value()) {
        out->mutable_title()->set_value(*in.title);
    } else {
        out->clear_title();
    }

    out->clear_desc();
    for (auto const& it : in.desc) { out->add_desc(it); }

    out->clear_attrs();
    for (auto const& [k, v] : in.attrs) { (*out->mutable_attrs())[k] = v; }

    out->set_debug_mode(
        static_cast<ext::visual::proto::VisCustom_DebugMode>(
            static_cast<int>(in.debugMode) + 1));
}

void proto_serde<ext::visual::proto::VisCustom, ext::visual::VisCustom>::
    read(
        ext::visual::proto::VisCustom const& in,
        ext::visual::VisCustom*              out) {
    out->extra = struct_to_json(in.extra());

    out->comment.clear();
    for (auto const& it : in.comment()) { out->comment.push_back(it); }

    if (in.has_title()) {
        out->title = in.title().value();
    } else {
        out->title = ::hstd::Opt<::hstd::Str>{};
    }

    out->desc.clear();
    for (auto const& it : in.desc()) { out->desc.push_back(it); }

    out->attrs.clear();
    for (auto const& [k, v] : in.attrs()) {
        out->attrs.insert_or_assign(k, v);
    }

    out->debugMode = (in.debug_mode()
                      == ext::visual::proto::
                          VisCustom_DebugMode_DEBUG_MODE_UNSPECIFIED)
                       ? static_cast<ext::visual::VisCustom::DebugMode>(0)
                       : static_cast<ext::visual::VisCustom::DebugMode>(
                             static_cast<int>(in.debug_mode()) - 1);
}

void proto_serde<
    ext::visual::proto::RectShape,
    ext::visual::VisElement::RectShape>::
    write(
        ext::visual::proto::RectShape*            out,
        ext::visual::VisElement::RectShape const& in) {
    proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::write(
        out->mutable_geometry(), in.geometry);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::write(
        out->mutable_pen(), in.pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::
        write(out->mutable_brush(), in.brush);

    if (in.cornerRadius.has_value()) {
        out->mutable_corner_radius()->set_value(*in.cornerRadius);
    } else {
        out->clear_corner_radius();
    }
}

void proto_serde<
    ext::visual::proto::RectShape,
    ext::visual::VisElement::RectShape>::
    read(
        ext::visual::proto::RectShape const& in,
        ext::visual::VisElement::RectShape*  out) {
    proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::read(
        in.geometry(), &out->geometry);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::read(
        in.pen(), &out->pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::read(
        in.brush(), &out->brush);

    if (in.has_corner_radius()) {
        out->cornerRadius = in.corner_radius().value();
    } else {
        out->cornerRadius = ::hstd::Opt<double>{};
    }
}

void proto_serde<
    ext::visual::proto::EllipseShape,
    ext::visual::VisElement::EllipseShape>::
    write(
        ext::visual::proto::EllipseShape*            out,
        ext::visual::VisElement::EllipseShape const& in) {
    proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::write(
        out->mutable_geometry(), in.geometry);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::write(
        out->mutable_pen(), in.pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::
        write(out->mutable_brush(), in.brush);
}

void proto_serde<
    ext::visual::proto::EllipseShape,
    ext::visual::VisElement::EllipseShape>::
    read(
        ext::visual::proto::EllipseShape const& in,
        ext::visual::VisElement::EllipseShape*  out) {
    proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::read(
        in.geometry(), &out->geometry);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::read(
        in.pen(), &out->pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::read(
        in.brush(), &out->brush);
}

void proto_serde<
    ext::visual::proto::LineShape,
    ext::visual::VisElement::LineShape>::
    write(
        ext::visual::proto::LineShape*            out,
        ext::visual::VisElement::LineShape const& in) {
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::write(
        out->mutable_p1(), in.p1);
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::write(
        out->mutable_p2(), in.p2);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::write(
        out->mutable_pen(), in.pen);
}

void proto_serde<
    ext::visual::proto::LineShape,
    ext::visual::VisElement::LineShape>::
    read(
        ext::visual::proto::LineShape const& in,
        ext::visual::VisElement::LineShape*  out) {
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::read(
        in.p1(), &out->p1);
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::read(
        in.p2(), &out->p2);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::read(
        in.pen(), &out->pen);
}

void proto_serde<
    ext::visual::proto::PathShape,
    ext::visual::VisElement::PathShape>::
    write(
        ext::visual::proto::PathShape*            out,
        ext::visual::VisElement::PathShape const& in) {
    proto_serde<ext::geometry::proto::Path, ext::geometry::Path>::write(
        out->mutable_path(), in.path);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::write(
        out->mutable_pen(), in.pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::
        write(out->mutable_brush(), in.brush);
}

void proto_serde<
    ext::visual::proto::PathShape,
    ext::visual::VisElement::PathShape>::
    read(
        ext::visual::proto::PathShape const& in,
        ext::visual::VisElement::PathShape*  out) {
    proto_serde<ext::geometry::proto::Path, ext::geometry::Path>::read(
        in.path(), &out->path);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::read(
        in.pen(), &out->pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::read(
        in.brush(), &out->brush);
}

void proto_serde<
    ext::visual::proto::PolygonShape,
    ext::visual::VisElement::PolygonShape>::
    write(
        ext::visual::proto::PolygonShape*            out,
        ext::visual::VisElement::PolygonShape const& in) {
    proto_serde<ext::geometry::proto::Polygon, ext::geometry::Polygon>::
        write(out->mutable_points(), in.points);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::write(
        out->mutable_pen(), in.pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::
        write(out->mutable_brush(), in.brush);
}

void proto_serde<
    ext::visual::proto::PolygonShape,
    ext::visual::VisElement::PolygonShape>::
    read(
        ext::visual::proto::PolygonShape const& in,
        ext::visual::VisElement::PolygonShape*  out) {
    proto_serde<ext::geometry::proto::Polygon, ext::geometry::Polygon>::
        read(in.points(), &out->points);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::read(
        in.pen(), &out->pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::read(
        in.brush(), &out->brush);
}

void proto_serde<
    ext::visual::proto::TextShape,
    ext::visual::VisElement::TextShape>::
    write(
        ext::visual::proto::TextShape*            out,
        ext::visual::VisElement::TextShape const& in) {
    out->set_content(in.content);
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::write(
        out->mutable_anchor(), in.anchor);

    if (in.boundingBox.has_value()) {
        proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::
            write(out->mutable_bounding_box(), *in.boundingBox);
    } else {
        out->clear_bounding_box();
    }

    proto_serde<ext::visual::proto::VisFont, ext::visual::VisFont>::write(
        out->mutable_font(), in.font);
    proto_serde<
        ext::visual::proto::VisTextAlign,
        ext::visual::VisTextAlign>::
        write(out->mutable_alignment(), in.alignment);
    proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::
        write(out->mutable_color(), in.color);
}

void proto_serde<
    ext::visual::proto::TextShape,
    ext::visual::VisElement::TextShape>::
    read(
        ext::visual::proto::TextShape const& in,
        ext::visual::VisElement::TextShape*  out) {
    out->content = in.content();
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::read(
        in.anchor(), &out->anchor);

    if (in.has_bounding_box()) {
        ext::geometry::Rect box;
        proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::read(
            in.bounding_box(), &box);
        out->boundingBox = box;
    } else {
        out->boundingBox = ::hstd::Opt<ext::geometry::Rect>{};
    }

    proto_serde<ext::visual::proto::VisFont, ext::visual::VisFont>::read(
        in.font(), &out->font);
    proto_serde<
        ext::visual::proto::VisTextAlign,
        ext::visual::VisTextAlign>::read(in.alignment(), &out->alignment);
    proto_serde<ext::visual::proto::VisColor, ext::visual::VisColor>::read(
        in.color(), &out->color);
}

void proto_serde<
    ext::visual::proto::PixmapShape,
    ext::visual::VisElement::PixmapShape>::
    write(
        ext::visual::proto::PixmapShape*            out,
        ext::visual::VisElement::PixmapShape const& in) {
    out->set_path(in.path);
    proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::write(
        out->mutable_geometry(), in.geometry);
}

void proto_serde<
    ext::visual::proto::PixmapShape,
    ext::visual::VisElement::PixmapShape>::
    read(
        ext::visual::proto::PixmapShape const& in,
        ext::visual::VisElement::PixmapShape*  out) {
    out->path = in.path();
    proto_serde<ext::geometry::proto::Rect, ext::geometry::Rect>::read(
        in.geometry(), &out->geometry);
}

void proto_serde<
    ext::visual::proto::PointShape,
    ext::visual::VisElement::PointShape>::
    write(
        ext::visual::proto::PointShape*            out,
        ext::visual::VisElement::PointShape const& in) {
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::write(
        out->mutable_position(), in.position);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::write(
        out->mutable_pen(), in.pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::
        write(out->mutable_brush(), in.brush);
    out->set_radius(in.radius);
}

void proto_serde<
    ext::visual::proto::PointShape,
    ext::visual::VisElement::PointShape>::
    read(
        ext::visual::proto::PointShape const& in,
        ext::visual::VisElement::PointShape*  out) {
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::read(
        in.position(), &out->position);
    proto_serde<ext::visual::proto::VisPen, ext::visual::VisPen>::read(
        in.pen(), &out->pen);
    proto_serde<ext::visual::proto::VisBrush, ext::visual::VisBrush>::read(
        in.brush(), &out->brush);
    out->radius = in.radius();
}

void proto_serde<
    ext::visual::proto::VisElementData,
    ext::visual::VisElement::Data>::
    write(
        ext::visual::proto::VisElementData*  out,
        ext::visual::VisElement::Data const& in) {
    std::visit(
        [&](auto const& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (
                std::is_same_v<T, ext::visual::VisElement::RectShape>) {
                proto_serde<ext::visual::proto::RectShape, T>::write(
                    out->mutable_rect(), v);
            } else if constexpr (
                std::is_same_v<T, ext::visual::VisElement::EllipseShape>) {
                proto_serde<ext::visual::proto::EllipseShape, T>::write(
                    out->mutable_ellipse(), v);
            } else if constexpr (
                std::is_same_v<T, ext::visual::VisElement::LineShape>) {
                proto_serde<ext::visual::proto::LineShape, T>::write(
                    out->mutable_line(), v);
            } else if constexpr (
                std::is_same_v<T, ext::visual::VisElement::PathShape>) {
                proto_serde<ext::visual::proto::PathShape, T>::write(
                    out->mutable_path(), v);
            } else if constexpr (
                std::is_same_v<T, ext::visual::VisElement::PolygonShape>) {
                proto_serde<ext::visual::proto::PolygonShape, T>::write(
                    out->mutable_polygon(), v);
            } else if constexpr (
                std::is_same_v<T, ext::visual::VisElement::TextShape>) {
                proto_serde<ext::visual::proto::TextShape, T>::write(
                    out->mutable_text(), v);
            } else if constexpr (
                std::is_same_v<T, ext::visual::VisElement::PixmapShape>) {
                proto_serde<ext::visual::proto::PixmapShape, T>::write(
                    out->mutable_pixmap(), v);
            } else if constexpr (
                std::is_same_v<T, ext::visual::VisElement::PointShape>) {
                proto_serde<ext::visual::proto::PointShape, T>::write(
                    out->mutable_point(), v);
            }
        },
        in);
}

void proto_serde<
    ext::visual::proto::VisElementData,
    ext::visual::VisElement::Data>::
    read(
        ext::visual::proto::VisElementData const& in,
        ext::visual::VisElement::Data*            out) {
    switch (in.data_case()) {
        case ext::visual::proto::VisElementData::kRect: {
            ext::visual::VisElement::RectShape v;
            proto_serde<
                ext::visual::proto::RectShape,
                ext::visual::VisElement::RectShape>::read(in.rect(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::kEllipse: {
            ext::visual::VisElement::EllipseShape v;
            proto_serde<
                ext::visual::proto::EllipseShape,
                ext::visual::VisElement::EllipseShape>::
                read(in.ellipse(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::kLine: {
            ext::visual::VisElement::LineShape v;
            proto_serde<
                ext::visual::proto::LineShape,
                ext::visual::VisElement::LineShape>::read(in.line(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::kPath: {
            ext::visual::VisElement::PathShape v;
            proto_serde<
                ext::visual::proto::PathShape,
                ext::visual::VisElement::PathShape>::read(in.path(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::kPolygon: {
            ext::visual::VisElement::PolygonShape v;
            proto_serde<
                ext::visual::proto::PolygonShape,
                ext::visual::VisElement::PolygonShape>::
                read(in.polygon(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::kText: {
            ext::visual::VisElement::TextShape v;
            proto_serde<
                ext::visual::proto::TextShape,
                ext::visual::VisElement::TextShape>::read(in.text(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::kPixmap: {
            ext::visual::VisElement::PixmapShape v;
            proto_serde<
                ext::visual::proto::PixmapShape,
                ext::visual::VisElement::PixmapShape>::
                read(in.pixmap(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::kPoint: {
            ext::visual::VisElement::PointShape v;
            proto_serde<
                ext::visual::proto::PointShape,
                ext::visual::VisElement::PointShape>::read(in.point(), &v);
            *out = v;
            return;
        }
        case ext::visual::proto::VisElementData::DATA_NOT_SET:
            throw std::runtime_error("VisElementData.data is not set");
    }

    throw std::runtime_error("Unknown VisElementData case");
}


void proto_serde<ext::visual::proto::VisElement, ext::visual::VisElement>::
    write(
        ext::visual::proto::VisElement* out,
        ext::visual::VisElement const&  in) {

    proto_serde<
        ext::visual::proto::VisElementData,
        ext::visual::VisElement::Data>::
        write(out->mutable_data(), in.data);

    proto_serde<ext::visual::proto::VisCustom, ext::visual::VisCustom>::
        write(out->mutable_custom(), in.custom);
}

void proto_serde<ext::visual::proto::VisElement, ext::visual::VisElement>::
    read(
        ext::visual::proto::VisElement const& in,
        ext::visual::VisElement*              out) {
    proto_serde<
        ext::visual::proto::VisElementData,
        ext::visual::VisElement::Data>::read(in.data(), &out->data);

    proto_serde<ext::visual::proto::VisCustom, ext::visual::VisCustom>::
        read(in.custom(), &out->custom);
}

void proto_serde<ext::visual::proto::VisGroup, ext::visual::VisGroup>::
    write(
        ext::visual::proto::VisGroup* out,
        ext::visual::VisGroup const&  in) {
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::write(
        out->mutable_offset(), in.offset);

    out->clear_elements();
    for (auto const& it : in.elements) {
        proto_serde<
            ext::visual::proto::VisElement,
            ext::visual::VisElement>::write(out->add_elements(), it);
    }

    out->clear_subgroups();
    for (auto const& it : in.subgroups) {
        proto_serde<ext::visual::proto::VisGroup, ext::visual::VisGroup>::
            write(out->add_subgroups(), it);
    }

    proto_serde<ext::visual::proto::VisCustom, ext::visual::VisCustom>::
        write(out->mutable_custom(), in.custom);

    if (in.max_point.has_value()) {
        proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::
            write(out->mutable_max_point(), *in.max_point);
    } else {
        out->clear_max_point();
    }

    if (in.original_id.has_value()) {
        out->mutable_original_id()->set_value(*in.original_id);
    } else {
        out->clear_original_id();
    }

    if (in.original_type.has_value()) {
        out->mutable_original_type()->set_value(*in.original_type);
    } else {
        out->clear_original_type();
    }
}

void proto_serde<ext::visual::proto::VisGroup, ext::visual::VisGroup>::
    read(
        ext::visual::proto::VisGroup const& in,
        ext::visual::VisGroup*              out) {
    proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::read(
        in.offset(), &out->offset);

    out->elements.clear();
    for (auto const& it : in.elements()) {
        ext::visual::VisElement el;
        proto_serde<
            ext::visual::proto::VisElement,
            ext::visual::VisElement>::read(it, &el);
        out->elements.push_back(el);
    }

    // FIXME: Refactor this by using proto_serde specialization for
    // containers. See [[proto-serde-extract-to-general]]
    out->subgroups.clear();
    for (auto const& it : in.subgroups()) {
        ext::visual::VisGroup g;
        proto_serde<ext::visual::proto::VisGroup, ext::visual::VisGroup>::
            read(it, &g);
        out->subgroups.push_back(g);
    }

    proto_serde<ext::visual::proto::VisCustom, ext::visual::VisCustom>::
        read(in.custom(), &out->custom);

    if (in.has_max_point()) {
        ext::geometry::Point p;
        proto_serde<ext::geometry::proto::Point, ext::geometry::Point>::
            read(in.max_point(), &p);
        out->max_point = p;
    } else {
        out->max_point = ::hstd::Opt<ext::geometry::Point>{};
    }

    if (in.has_original_id()) {
        out->original_id = in.original_id().value();
    } else {
        out->original_id = ::hstd::Opt<::hstd::u64>{};
    }

    if (in.has_original_type()) {
        out->original_type = in.original_type().value();
    } else {
        out->original_type = ::hstd::Opt<::hstd::u64>{};
    }
}

} // namespace hstd::serde
