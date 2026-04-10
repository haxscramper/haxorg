#include "hstd_visual.hpp"
#include <fmt/format.h>

namespace hstd::ext::visual {

namespace {

std::string colorToSvg(VisColor const& c) {
    if (c.a == 255) {
        return fmt::format("#{:02x}{:02x}{:02x}", c.r, c.g, c.b);
    } else {
        return fmt::format(
            "rgba({},{},{},{})", c.r, c.g, c.b, c.a / 255.0f);
    }
}

std::string penToSvgAttrs(VisPen const& pen) {
    if (pen.style == VisPen::LineStyle::None) {
        return R"(stroke="none")";
    }

    std::string result = fmt::format(
        R"(stroke="{}" stroke-width="{}")",
        colorToSvg(pen.color),
        pen.width);

    switch (pen.style) {
        case VisPen::LineStyle::Dash:
            result += fmt::format(
                R"svg( stroke-dasharray="{},{})")svg",
                pen.width * 4,
                pen.width * 2);
            break;
        case VisPen::LineStyle::Dot:
            result += fmt::format(
                R"svg( stroke-dasharray="{},{})")svg",
                pen.width,
                pen.width * 2);
            break;
        case VisPen::LineStyle::DashDot:
            result += fmt::format(
                R"svg( stroke-dasharray="{},{},{},{})")svg",
                pen.width * 4,
                pen.width * 2,
                pen.width,
                pen.width * 2);
            break;
        default: break;
    }

    return result;
}

std::string brushToSvgAttr(VisBrush const& brush) {
    if (brush.style == VisBrush::BrushStyle::None) {
        return R"(fill="none")";
    }
    // For pattern fills in SVG we'd need <defs>/<pattern> elements.
    // For the initial implementation, solid fill covers the common case.
    // Pattern fills are rendered as solid with the specified color.
    return fmt::format(R"(fill="{}")", colorToSvg(brush.color));
}

std::string fontWeightToSvg(VisFont::Weight w) {
    switch (w) {
        case VisFont::Weight::Thin: return "100";
        case VisFont::Weight::Light: return "300";
        case VisFont::Weight::Normal: return "400";
        case VisFont::Weight::Bold: return "700";
        case VisFont::Weight::Black: return "900";
    }
    return "400";
}

std::string fontStyleToSvg(VisFont::FontStyle s) {
    switch (s) {
        case VisFont::FontStyle::Normal: return "normal";
        case VisFont::FontStyle::Italic: return "italic";
        case VisFont::FontStyle::Oblique: return "oblique";
    }
    return "normal";
}

std::string textAnchorToSvg(VisTextAlign::HAlign h) {
    switch (h) {
        case VisTextAlign::HAlign::Left: return "start";
        case VisTextAlign::HAlign::Center: return "middle";
        case VisTextAlign::HAlign::Right: return "end";
    }
    return "start";
}

std::string dominantBaselineToSvg(VisTextAlign::VAlign v) {
    switch (v) {
        case VisTextAlign::VAlign::Top: return "hanging";
        case VisTextAlign::VAlign::Center: return "central";
        case VisTextAlign::VAlign::Bottom: return "alphabetic";
    }
    return "hanging";
}

std::string pathToSvgD(Path const& path) {
    std::string d;
    for (auto const& cmd : path.commands) {
        switch (cmd.type) {
            case Path::CommandType::MoveTo:
                d += fmt::format("M {} {} ", cmd.p1.x(), cmd.p1.y());
                break;
            case Path::CommandType::LineTo:
                d += fmt::format("L {} {} ", cmd.p1.x(), cmd.p1.y());
                break;
            case Path::CommandType::QuadTo:
                d += fmt::format(
                    "Q {} {} {} {} ",
                    cmd.p1.x(),
                    cmd.p1.y(),
                    cmd.p2.x(),
                    cmd.p2.y());
                break;
            case Path::CommandType::CubicTo:
                d += fmt::format(
                    "C {} {} {} {} {} {} ",
                    cmd.p1.x(),
                    cmd.p1.y(),
                    cmd.p2.x(),
                    cmd.p2.y(),
                    cmd.p3.x(),
                    cmd.p3.y());
                break;
            case Path::CommandType::CloseSubpath: d += "Z "; break;
        }
    }
    return d;
}

struct SvgWriter {
    std::string output;
    float       globalOffsetX = 0;
    float       globalOffsetY = 0;

    void writeElement(VisElement const& elem, float ox, float oy) {
        std::visit(
            [&](auto const& shape) { writeShape(shape, ox, oy); },
            elem.data);
    }

    void writeShape(VisElement::RectShape const& r, float ox, float oy) {
        float x = r.geometry.x() + ox;
        float y = r.geometry.y() + oy;
        output += fmt::format(
            R"(<rect x="{}" y="{}" width="{}" height="{}" {} {})",
            x,
            y,
            r.geometry.width(),
            r.geometry.height(),
            penToSvgAttrs(r.pen),
            brushToSvgAttr(r.brush));
        if (r.cornerRadius) {
            output += fmt::format(
                R"( rx="{}" ry="{}")", *r.cornerRadius, *r.cornerRadius);
        }
        output += "/>\n";
    }

    void writeShape(
        VisElement::EllipseShape const& e,
        float                           ox,
        float                           oy) {
        float cx = e.geometry.x() + e.geometry.width() / 2.0f + ox;
        float cy = e.geometry.y() + e.geometry.height() / 2.0f + oy;
        float rx = e.geometry.width() / 2.0f;
        float ry = e.geometry.height() / 2.0f;
        output += fmt::format(
            R"(<ellipse cx="{}" cy="{}" rx="{}" ry="{}" {} {}/>)"
            "\n",
            cx,
            cy,
            rx,
            ry,
            penToSvgAttrs(e.pen),
            brushToSvgAttr(e.brush));
    }

    void writeShape(VisElement::LineShape const& l, float ox, float oy) {
        output += fmt::format(
            R"(<line x1="{}" y1="{}" x2="{}" y2="{}" {}/>)"
            "\n",
            l.p1.x() + ox,
            l.p1.y() + oy,
            l.p2.x() + ox,
            l.p2.y() + oy,
            penToSvgAttrs(l.pen));
    }

    void writeShape(VisElement::PathShape const& p, float ox, float oy) {
        // Apply offset by wrapping in a translated group
        output += fmt::format(
            R"svg(<g transform="translate({},{})">)svg"
            "\n",
            ox,
            oy);
        output += fmt::format(
            R"(<path d="{}" {} {}/>)"
            "\n",
            pathToSvgD(p.path),
            penToSvgAttrs(p.pen),
            brushToSvgAttr(p.brush));
        output += "</g>\n";
    }

    void writeShape(
        VisElement::PolygonShape const& poly,
        float                           ox,
        float                           oy) {
        std::string points;
        for (auto const& pt : poly.points) {
            points += fmt::format("{},{} ", pt.x() + ox, pt.y() + oy);
        }
        output += fmt::format(
            R"(<polygon points="{}" {} {}/>)"
            "\n",
            points,
            penToSvgAttrs(poly.pen),
            brushToSvgAttr(poly.brush));
    }

    void writeShape(VisElement::TextShape const& t, float ox, float oy) {
        output += fmt::format(
            R"(<text x="{}" y="{}" )"
            R"(font-family="{}" font-size="{}" )"
            R"(font-weight="{}" font-style="{}" )"
            R"(text-anchor="{}" dominant-baseline="{}" )"
            R"(fill="{}">)",
            t.anchor.x() + ox,
            t.anchor.y() + oy,
            t.font.family,
            t.font.pixelSize,
            fontWeightToSvg(t.font.weight),
            fontStyleToSvg(t.font.fontStyle),
            textAnchorToSvg(t.alignment.horizontal),
            dominantBaselineToSvg(t.alignment.vertical),
            colorToSvg(t.color));
        output += fmt::format("{}</text>\n", t.content);
    }

    void writeShape(
        VisElement::PixmapShape const& px,
        float                          ox,
        float                          oy) {
        output += fmt::format(
            R"(<image href="{}" x="{}" y="{}" width="{}" height="{}"/>)"
            "\n",
            px.path,
            px.geometry.x() + ox,
            px.geometry.y() + oy,
            px.geometry.width(),
            px.geometry.height());
    }

    void writeShape(VisElement::PointShape const& pt, float ox, float oy) {
        output += fmt::format(
            R"(<circle cx="{}" cy="{}" r="{}" {} {}/>)"
            "\n",
            pt.position.x() + ox,
            pt.position.y() + oy,
            pt.radius,
            penToSvgAttrs(pt.pen),
            brushToSvgAttr(pt.brush));
    }

    void writeGroup(VisGroup const& group, float ox, float oy) {
        float gx = ox + group.offset.x();
        float gy = oy + group.offset.y();

        for (auto const& elem : group.elements) {
            writeElement(elem, gx, gy);
        }
        for (auto const& sub : group.subgroups) {
            writeGroup(sub, gx, gy);
        }
    }

    /// Compute the bounding box of the entire group hierarchy.
    Rect computeBounds(VisGroup const& group, float ox, float oy) {
        float gx   = ox + group.offset.x();
        float gy   = oy + group.offset.y();
        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::lowest();
        float maxY = std::numeric_limits<float>::lowest();

        auto expand = [&](float x, float y) {
            minX = std::min(minX, x);
            minY = std::min(minY, y);
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);
        };

        auto expandRect = [&](Rect const& r, float ex, float ey) {
            expand(r.x() + ex, r.y() + ey);
            expand(r.x() + r.width() + ex, r.y() + r.height() + ey);
        };

        for (auto const& elem : group.elements) {
            std::visit(
                hstd::overloaded{
                    [&](VisElement::RectShape const& s) {
                        expandRect(s.geometry, gx, gy);
                    },
                    [&](VisElement::EllipseShape const& s) {
                        expandRect(s.geometry, gx, gy);
                    },
                    [&](VisElement::LineShape const& s) {
                        expand(s.p1.x() + gx, s.p1.y() + gy);
                        expand(s.p2.x() + gx, s.p2.y() + gy);
                    },
                    [&](VisElement::PathShape const& s) {
                        for (auto const& cmd : s.path.commands) {
                            expand(cmd.p1.x() + gx, cmd.p1.y() + gy);
                            if (cmd.type == Path::CommandType::QuadTo
                                || cmd.type
                                       == Path::CommandType::CubicTo) {
                                expand(cmd.p2.x() + gx, cmd.p2.y() + gy);
                            }
                            if (cmd.type == Path::CommandType::CubicTo) {
                                expand(cmd.p3.x() + gx, cmd.p3.y() + gy);
                            }
                        }
                    },
                    [&](VisElement::PolygonShape const& s) {
                        for (auto const& pt : s.points) {
                            expand(pt.x() + gx, pt.y() + gy);
                        }
                    },
                    [&](VisElement::TextShape const& s) {
                        expand(s.anchor.x() + gx, s.anchor.y() + gy);
                        if (s.boundingBox) {
                            expandRect(*s.boundingBox, gx, gy);
                        }
                    },
                    [&](VisElement::PixmapShape const& s) {
                        expandRect(s.geometry, gx, gy);
                    },
                    [&](VisElement::PointShape const& s) {
                        expand(
                            s.position.x() - s.radius + gx,
                            s.position.y() - s.radius + gy);
                        expand(
                            s.position.x() + s.radius + gx,
                            s.position.y() + s.radius + gy);
                    },
                },
                elem.data);
        }

        for (auto const& sub : group.subgroups) {
            Rect subBounds = computeBounds(sub, gx, gy);
            expand(subBounds.x(), subBounds.y());
            expand(
                subBounds.x() + subBounds.width(),
                subBounds.y() + subBounds.height());
        }

        if (minX > maxX) { return Rect(0, 0, 0, 0); }
        return Rect(minX, minY, maxX - minX, maxY - minY);
    }
};
} // namespace

hstd::Str toSvg(VisGroup const& group) {
    SvgWriter writer;
    Rect      bounds = writer.computeBounds(group, 0, 0);

    float margin = 4.0f;
    float viewX  = bounds.x() - margin;
    float viewY  = bounds.y() - margin;
    float viewW  = bounds.width() + 2 * margin;
    float viewH  = bounds.height() + 2 * margin;

    writer.output = fmt::format(
        R"(<?xml version="1.0" encoding="UTF-8"?>)"
        "\n"
        R"(<svg xmlns="http://www.w3.org/2000/svg" )"
        R"(xmlns:xlink="http://www.w3.org/1999/xlink" )"
        R"(viewBox="{} {} {} {}" )"
        R"(width="{}" height="{}">)"
        "\n",
        viewX,
        viewY,
        viewW,
        viewH,
        viewW,
        viewH);

    writer.writeGroup(group, 0, 0);

    writer.output += "</svg>\n";
    return hstd::Str{writer.output};
}

} // namespace hstd::ext::visual
