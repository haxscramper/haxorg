#pragma once

#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/ext/hstd_geometry.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Xml.hpp>

namespace hstd::ext::visual {

using namespace hstd::ext::geometry;

struct VisColor {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;

    DESC_FIELDS(VisColor, (r, g, b, a));

    static VisColor fromRgb(uint8_t r, uint8_t g, uint8_t b) {
        return VisColor{r, g, b, 255};
    }

    static VisColor fromRgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        return VisColor{r, g, b, a};
    }

    static VisColor black() { return VisColor{0, 0, 0, 255}; }
    static VisColor white() { return VisColor{255, 255, 255, 255}; }
    static VisColor transparent() { return VisColor{0, 0, 0, 0}; }
    static VisColor red() { return VisColor{255, 0, 0, 255}; }
    static VisColor green() { return VisColor{0, 255, 0, 255}; }
    static VisColor blue() { return VisColor{0, 0, 255, 255}; }
};

struct VisPen {
    DECL_DESCRIBED_ENUM(LineStyle, Solid, Dash, Dot, DashDot, None);

    VisColor  color = VisColor::black();
    float     width = 1.0f;
    LineStyle style = LineStyle::Solid;

    DESC_FIELDS(VisPen, (color, width, style));

    static VisPen noPen() { return VisPen{.style = LineStyle::None}; }
};

struct VisBrush {
    DECL_DESCRIBED_ENUM(
        BrushStyle,
        Solid,
        None,
        Horizontal,
        Vertical,
        Cross,
        DiagonalForward,
        DiagonalBackward,
        DiagonalCross);

    VisColor   color = VisColor::white();
    BrushStyle style = BrushStyle::None;

    DESC_FIELDS(VisBrush, (color, style));

    static VisBrush noBrush() {
        return VisBrush{.style = BrushStyle::None};
    }

    static VisBrush solid(VisColor const& c) {
        return VisBrush{.color = c, .style = BrushStyle::Solid};
    }
};

struct VisFont {
    DECL_DESCRIBED_ENUM(Weight, Thin, Light, Normal, Bold, Black);
    DECL_DESCRIBED_ENUM(FontStyle, Normal, Italic, Oblique);

    hstd::Str family    = "Arial";
    float     pixelSize = 12.0f;
    Weight    weight    = Weight::Normal;
    FontStyle fontStyle = FontStyle::Normal;

    DESC_FIELDS(VisFont, (family, pixelSize, weight, fontStyle));
};

struct VisTextAlign {
    DECL_DESCRIBED_ENUM(HAlign, Left, Center, Right);

    DECL_DESCRIBED_ENUM(VAlign, Top, Center, Bottom);

    HAlign horizontal = HAlign::Left;
    VAlign vertical   = VAlign::Top;

    DESC_FIELDS(VisTextAlign, (horizontal, vertical));
};

struct VisElement {
    struct RectShape {
        Rect             geometry;
        VisPen           pen;
        VisBrush         brush;
        hstd::Opt<float> cornerRadius;

        DESC_FIELDS(RectShape, (geometry, pen, brush, cornerRadius));
    };

    struct EllipseShape {
        Rect     geometry;
        VisPen   pen;
        VisBrush brush;

        DESC_FIELDS(EllipseShape, (geometry, pen, brush));

        static EllipseShape fromCenter(
            Point const& center,
            float        rx,
            float        ry,
            VisPen       pen   = VisPen{},
            VisBrush     brush = VisBrush{}) {
            return EllipseShape{
                .geometry = Rect(
                    center.x() - rx,
                    center.y() - ry,
                    2.0f * rx,
                    2.0f * ry),
                .pen   = pen,
                .brush = brush,
            };
        }

        static EllipseShape circle(
            Point const& center,
            float        radius,
            VisPen       pen   = VisPen{},
            VisBrush     brush = VisBrush{}) {
            return fromCenter(center, radius, radius, pen, brush);
        }
    };

    struct LineShape {
        Point  p1;
        Point  p2;
        VisPen pen;

        DESC_FIELDS(LineShape, (p1, p2, pen));
    };

    struct PathShape {
        Path     path;
        VisPen   pen;
        VisBrush brush;

        DESC_FIELDS(PathShape, (path, pen, brush));
    };

    struct PolygonShape {
        hstd::Vec<Point> points;
        VisPen           pen;
        VisBrush         brush;

        DESC_FIELDS(PolygonShape, (points, pen, brush));
    };

    struct TextShape {
        hstd::Str       content;
        Point           anchor;
        hstd::Opt<Rect> boundingBox;
        VisFont         font;
        VisTextAlign    alignment;
        VisColor        color = VisColor::black();

        DESC_FIELDS(
            TextShape,
            (content, anchor, boundingBox, font, alignment, color));
    };

    struct PixmapShape {
        hstd::Str path;
        Rect      geometry;

        DESC_FIELDS(PixmapShape, (path, geometry));
    };

    struct PointShape {
        Point    position;
        VisPen   pen;
        VisBrush brush;
        float    radius = 2.0f;

        DESC_FIELDS(PointShape, (position, pen, brush, radius));
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        RectShape,
        EllipseShape,
        LineShape,
        PathShape,
        PolygonShape,
        TextShape,
        PixmapShape,
        PointShape);

    Data data;
    json extra;

    DESC_FIELDS(VisElement, (data, extra));
};

struct VisGroup {
    Point                 offset = Point{0.0f, 0.0f};
    hstd::Vec<VisElement> elements;
    hstd::Vec<VisGroup>   subgroups;

    DESC_FIELDS(VisGroup, (offset, elements, subgroups));
};

/// Convert a VisGroup hierarchy to an SVG string.
XmlNode toSvg(hstd::Vec<VisGroup> const& group, bool debug = false);

} // namespace hstd::ext::visual
