#include "hstd_visual.hpp"
#include <fmt/format.h>
#include <hstd/stdlib/Xml.hpp>

namespace hstd::ext::visual {

namespace {

std::string colorToSvg(VisColor const& c) {
    if (c.a == 255) {
        return hstd::fmt("#{:02x}{:02x}{:02x}", c.r, c.g, c.b);
    } else {
        return hstd::fmt("rgba({},{},{},{})", c.r, c.g, c.b, c.a / 255.0f);
    }
}

void applyPenAttrs(XmlNode& node, VisPen const& pen) {
    if (pen.style == VisPen::LineStyle::None) {
        node.set_attr("stroke", "none");
        return;
    }

    node.set_attr("stroke", colorToSvg(pen.color));
    node.set_attr("stroke-width", hstd::fmt("{}", pen.width));

    switch (pen.style) {
        case VisPen::LineStyle::Dash:
            node.set_attr(
                "stroke-dasharray",
                hstd::fmt("{},{}", pen.width * 4, pen.width * 2));
            break;
        case VisPen::LineStyle::Dot:
            node.set_attr(
                "stroke-dasharray",
                hstd::fmt("{},{}", pen.width, pen.width * 2));
            break;
        case VisPen::LineStyle::DashDot:
            node.set_attr(
                "stroke-dasharray",
                hstd::fmt(
                    "{},{},{},{}",
                    pen.width * 4,
                    pen.width * 2,
                    pen.width,
                    pen.width * 2));
            break;
        default: break;
    }
}

void applyBrushAttrs(XmlNode& node, VisBrush const& brush) {
    if (brush.style == VisBrush::BrushStyle::None) {
        node.set_attr("fill", "none");
        return;
    }
    node.set_attr("fill", colorToSvg(brush.color));
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
                d += hstd::fmt("M {} {} ", cmd.p1.x(), cmd.p1.y());
                break;
            case Path::CommandType::LineTo:
                d += hstd::fmt("L {} {} ", cmd.p1.x(), cmd.p1.y());
                break;
            case Path::CommandType::QuadTo:
                d += hstd::fmt(
                    "Q {} {} {} {} ",
                    cmd.p1.x(),
                    cmd.p1.y(),
                    cmd.p2.x(),
                    cmd.p2.y());
                break;
            case Path::CommandType::CubicTo:
                d += hstd::fmt(
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

std::string pathToString(hstd::Vec<int> const& path) {
    std::string result;
    for (int idx : path) { result += hstd::fmt("{}/", idx); }
    return result.empty() ? "/" : result;
}

struct SvgWriter {
    Point writeShape(
        XmlNode&                     parent,
        VisElement::RectShape const& r,
        float                        ox,
        float                        oy) {
        float x = r.geometry.x() + ox;
        float y = r.geometry.y() + oy;

        XmlNode rect("rect");
        rect.set_attr("x", hstd::fmt("{}", x));
        rect.set_attr("y", hstd::fmt("{}", y));
        rect.set_attr("width", hstd::fmt("{}", r.geometry.width()));
        rect.set_attr("height", hstd::fmt("{}", r.geometry.height()));
        applyPenAttrs(rect, r.pen);
        applyBrushAttrs(rect, r.brush);
        if (r.cornerRadius) {
            rect.set_attr("rx", hstd::fmt("{}", *r.cornerRadius));
            rect.set_attr("ry", hstd::fmt("{}", *r.cornerRadius));
        }
        parent.push_back(std::move(rect));

        return Point(
            x + r.geometry.width() / 2.0f, y + r.geometry.height() / 2.0f);
    }

    Point writeShape(
        XmlNode&                        parent,
        VisElement::EllipseShape const& e,
        float                           ox,
        float                           oy) {
        float cx = e.geometry.x() + e.geometry.width() / 2.0f + ox;
        float cy = e.geometry.y() + e.geometry.height() / 2.0f + oy;
        float rx = e.geometry.width() / 2.0f;
        float ry = e.geometry.height() / 2.0f;

        XmlNode ellipse("ellipse");
        ellipse.set_attr("cx", hstd::fmt("{}", cx));
        ellipse.set_attr("cy", hstd::fmt("{}", cy));
        ellipse.set_attr("rx", hstd::fmt("{}", rx));
        ellipse.set_attr("ry", hstd::fmt("{}", ry));
        applyPenAttrs(ellipse, e.pen);
        applyBrushAttrs(ellipse, e.brush);
        parent.push_back(std::move(ellipse));

        return Point(cx, cy);
    }

    Point writeShape(
        XmlNode&                     parent,
        VisElement::LineShape const& l,
        float                        ox,
        float                        oy) {
        float x1 = l.p1.x() + ox;
        float y1 = l.p1.y() + oy;
        float x2 = l.p2.x() + ox;
        float y2 = l.p2.y() + oy;

        XmlNode line("line");
        line.set_attr("x1", hstd::fmt("{}", x1));
        line.set_attr("y1", hstd::fmt("{}", y1));
        line.set_attr("x2", hstd::fmt("{}", x2));
        line.set_attr("y2", hstd::fmt("{}", y2));
        applyPenAttrs(line, l.pen);
        parent.push_back(std::move(line));

        return Point((x1 + x2) * 0.5f, (y1 + y2) * 0.5f);
    }

    Point writeShape(
        XmlNode&                     parent,
        VisElement::PathShape const& p,
        float                        ox,
        float                        oy) {
        XmlNode g("g");
        g.set_attr("transform", hstd::fmt("translate({},{})", ox, oy));

        XmlNode path("path");
        path.set_attr("d", pathToSvgD(p.path));
        applyPenAttrs(path, p.pen);
        applyBrushAttrs(path, p.brush);
        g.push_back(std::move(path));
        parent.push_back(std::move(g));

        if (!p.path.commands.empty()) {
            auto const& c = p.path.commands.front();
            return Point(c.p1.x() + ox, c.p1.y() + oy);
        } else {
            return Point(ox, oy);
        }
    }

    Point writeShape(
        XmlNode&                        parent,
        VisElement::PolygonShape const& poly,
        float                           ox,
        float                           oy) {
        std::string points;
        for (auto const& pt : poly.points) {
            points += hstd::fmt("{},{} ", pt.x() + ox, pt.y() + oy);
        }

        XmlNode polygon("polygon");
        polygon.set_attr("points", points);
        applyPenAttrs(polygon, poly.pen);
        applyBrushAttrs(polygon, poly.brush);
        parent.push_back(std::move(polygon));

        if (!poly.points.empty()) {
            return Point(
                poly.points.front().x() + ox,
                poly.points.front().y() + oy);
        } else {
            return Point(ox, oy);
        }
    }

    Point writeShape(
        XmlNode&                     parent,
        VisElement::TextShape const& t,
        float                        ox,
        float                        oy) {
        float x = t.anchor.x() + ox;
        float y = t.anchor.y() + oy;

        XmlNode text("text");
        text.set_attr("x", hstd::fmt("{}", x));
        text.set_attr("y", hstd::fmt("{}", y));
        text.set_attr("font-family", t.font.family);
        text.set_attr("font-size", hstd::fmt("{}", t.font.pixelSize));
        text.set_attr("font-weight", fontWeightToSvg(t.font.weight));
        text.set_attr("font-style", fontStyleToSvg(t.font.fontStyle));
        text.set_attr(
            "text-anchor", textAnchorToSvg(t.alignment.horizontal));
        text.set_attr(
            "dominant-baseline",
            dominantBaselineToSvg(t.alignment.vertical));
        text.set_attr("fill", colorToSvg(t.color));
        text.set_text(t.content);
        parent.push_back(std::move(text));

        return Point(x, y);
    }

    Point writeShape(
        XmlNode&                       parent,
        VisElement::PixmapShape const& px,
        float                          ox,
        float                          oy) {
        float x = px.geometry.x() + ox;
        float y = px.geometry.y() + oy;

        XmlNode image("image");
        image.set_attr("href", px.path);
        image.set_attr("x", hstd::fmt("{}", x));
        image.set_attr("y", hstd::fmt("{}", y));
        image.set_attr("width", hstd::fmt("{}", px.geometry.width()));
        image.set_attr("height", hstd::fmt("{}", px.geometry.height()));
        parent.push_back(std::move(image));

        return Point(
            x + px.geometry.width() / 2.0f,
            y + px.geometry.height() / 2.0f);
    }

    Point writeShape(
        XmlNode&                      parent,
        VisElement::PointShape const& pt,
        float                         ox,
        float                         oy) {
        float cx = pt.position.x() + ox;
        float cy = pt.position.y() + oy;

        XmlNode circle("circle");
        circle.set_attr("cx", hstd::fmt("{}", cx));
        circle.set_attr("cy", hstd::fmt("{}", cy));
        circle.set_attr("r", hstd::fmt("{}", pt.radius));
        applyPenAttrs(circle, pt.pen);
        applyBrushAttrs(circle, pt.brush);
        parent.push_back(std::move(circle));

        return Point(cx, cy);
    }

    void appendDebugMarker(
        XmlNode&              parent,
        hstd::Vec<int> const& path,
        Point const&          coord,
        json const&           extra) {
        XmlNode g("g");
        g.set_attr("class", "debug-node");

        XmlNode marker("circle");
        marker.set_attr("cx", hstd::fmt("{}", coord.x()));
        marker.set_attr("cy", hstd::fmt("{}", coord.y()));
        marker.set_attr("r", "2.5");
        marker.set_attr("fill", "#ff00ff");
        marker.set_attr("stroke", "none");
        g.push_back(std::move(marker));

        XmlNode label("text");
        label.set_attr("x", hstd::fmt("{}", coord.x() + 4.0f));
        label.set_attr("y", hstd::fmt("{}", coord.y() - 4.0f));
        label.set_attr("font-family", "monospace");
        label.set_attr("font-size", "4");
        label.set_attr("fill", "#aa0066");
        label.set_attr("text-anchor", "start");
        label.set_attr("dominant-baseline", "alphabetic");
        label.set_text(
            hstd::fmt(
                "{} @ ({:.2f},{:.2f}){}",
                pathToString(path),
                coord.x(),
                coord.y(),
                extra.is_null() ? ""
                                : hstd::fmt(" extra={}", extra.dump())));
        g.push_back(std::move(label));

        parent.push_back(std::move(g));
    }

    void writeElement(
        XmlNode&              parent,
        VisElement const&     elem,
        float                 ox,
        float                 oy,
        hstd::Vec<int> const& path,
        bool                  debug) {
        Point coord = std::visit(
            [&](auto const& shape) {
                return writeShape(parent, shape, ox, oy);
            },
            elem.data);

        if (debug) { appendDebugMarker(parent, path, coord, elem.extra); }
    }

    void writeGroup(
        XmlNode&              parent,
        VisGroup const&       group,
        float                 ox,
        float                 oy,
        hstd::Vec<int> const& path,
        bool                  debug) {
        float gx = ox + group.offset.x();
        float gy = oy + group.offset.y();

        for (auto const& elem : group.elements) {
            writeElement(parent, elem, gx, gy, path, debug);
        }

        for (int i = 0; i < group.subgroups.size(); ++i) {
            writeGroup(
                parent,
                group.subgroups[i],
                gx,
                gy,
                path + hstd::Vec<int>{i},
                debug);
        }

        if (debug) {
            appendDebugMarker(parent, path, {ox, oy}, group.extra);
        }
    }

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

XmlNode toSvg(hstd::Vec<VisGroup> const& groups, bool debug) {
    SvgWriter writer;

    float minX = 0.0f;
    float minY = 0.0f;
    float maxX = 0.0f;
    float maxY = 0.0f;

    if (!groups.empty()) {
        Rect first = writer.computeBounds(groups.front(), 0, 0);
        minX       = first.x();
        minY       = first.y();
        maxX       = first.x() + first.width();
        maxY       = first.y() + first.height();

        for (int i = 1; i < groups.size(); ++i) {
            Rect b = writer.computeBounds(groups[i], 0, 0);
            minX   = std::min(minX, b.x());
            minY   = std::min(minY, b.y());
            maxX   = std::max(maxX, b.x() + b.width());
            maxY   = std::max(maxY, b.y() + b.height());
        }
    }

    float margin = 4.0f;
    float viewX  = minX - margin;
    float viewY  = minY - margin;
    float viewW  = (maxX - minX) + 2.0f * margin;
    float viewH  = (maxY - minY) + 2.0f * margin;

    XmlNode svg("svg");
    svg.set_attr("xmlns", "http://www.w3.org/2000/svg");
    svg.set_attr("xmlns:xlink", "http://www.w3.org/1999/xlink");
    svg.set_attr("style", "background-color: white");
    svg.set_attr(
        "viewBox", hstd::fmt("{} {} {} {}", viewX, viewY, viewW, viewH));
    svg.set_attr("width", hstd::fmt("{}", viewW));
    svg.set_attr("height", hstd::fmt("{}", viewH));

    for (int i = 0; i < groups.size(); ++i) {
        writer.writeGroup(svg, groups[i], 0.0f, 0.0f, {i}, debug);
    }

    return svg;
}

} // namespace hstd::ext::visual
