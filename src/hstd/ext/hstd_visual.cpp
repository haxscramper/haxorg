#include "hstd_visual.hpp"
#include <fmt/format.h>
#include <hstd/stdlib/Xml.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>

namespace hstd::ext::visual {

namespace {

bool is_empty(json const& j) {
    return j.is_null()
        || ((j.is_object()   //
             || j.is_array() //
             || j.is_string())
            && !j.empty());
}

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

struct ShapeWriteResult {
    XmlNode node;
    Point   coord;
};

struct SvgWriter {
    bool    debug;
    XmlNode writeShape(VisElement::RectShape const& r) {
        double x = r.geometry.x();
        double y = r.geometry.y();

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

        return std::move(rect);
    }

    XmlNode writeShape(VisElement::EllipseShape const& e) {
        double cx = e.geometry.x() + e.geometry.width() / 2.0f;
        double cy = e.geometry.y() + e.geometry.height() / 2.0f;
        double rx = e.geometry.width() / 2.0f;
        double ry = e.geometry.height() / 2.0f;

        XmlNode ellipse("ellipse");
        ellipse.set_attr("cx", hstd::fmt("{}", cx));
        ellipse.set_attr("cy", hstd::fmt("{}", cy));
        ellipse.set_attr("rx", hstd::fmt("{}", rx));
        ellipse.set_attr("ry", hstd::fmt("{}", ry));
        applyPenAttrs(ellipse, e.pen);
        applyBrushAttrs(ellipse, e.brush);

        return std::move(ellipse);
    }

    XmlNode writeShape(VisElement::LineShape const& l) {
        double x1 = l.p1.x();
        double y1 = l.p1.y();
        double x2 = l.p2.x();
        double y2 = l.p2.y();

        XmlNode line("line");
        line.set_attr("x1", hstd::fmt("{}", x1));
        line.set_attr("y1", hstd::fmt("{}", y1));
        line.set_attr("x2", hstd::fmt("{}", x2));
        line.set_attr("y2", hstd::fmt("{}", y2));
        applyPenAttrs(line, l.pen);

        return std::move(line);
    }

    XmlNode writeShape(VisElement::PathShape const& p) {
        XmlNode path("path");
        path.set_attr("d", pathToSvgD(p.path));
        applyPenAttrs(path, p.pen);
        applyBrushAttrs(path, p.brush);
        return std::move(path);
    }

    XmlNode writeShape(VisElement::PolygonShape const& poly) {
        std::string points;
        for (auto const& pt : poly.points) {
            points += hstd::fmt("{},{} ", pt.x(), pt.y());
        }

        XmlNode polygon("polygon");
        polygon.set_attr("points", points);
        applyPenAttrs(polygon, poly.pen);
        applyBrushAttrs(polygon, poly.brush);

        return std::move(polygon);
    }

    XmlNode writeShape(VisElement::TextShape const& t) {
        double x = t.anchor.x();
        double y = t.anchor.y();

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

        if (debug && t.boundingBox) {
            XmlNode               result{"g"};
            VisElement::RectShape dr;
            dr.geometry = t.boundingBox.value();
            // dr.pen .
            result.push_back(writeShape(dr));
            result.push_back(buildDebugMarker(
                dr.geometry.min_corner(),
                hstd::fmt(
                    "({:.2f},{:.2f}+{},{})",
                    dr.geometry.x(),
                    dr.geometry.y(),
                    dr.geometry.width(),
                    dr.geometry.height()),
                json{},
                2));

            result.push_back(text);
            return result;
        } else {
            return std::move(text);
        }
    }

    XmlNode writeShape(VisElement::PixmapShape const& px) {
        double x = px.geometry.x();
        double y = px.geometry.y();

        XmlNode image("image");
        image.set_attr("href", px.path);
        image.set_attr("x", hstd::fmt("{}", x));
        image.set_attr("y", hstd::fmt("{}", y));
        image.set_attr("width", hstd::fmt("{}", px.geometry.width()));
        image.set_attr("height", hstd::fmt("{}", px.geometry.height()));

        return std::move(image);
    }

    XmlNode writeShape(VisElement::PointShape const& pt) {
        double cx = pt.position.x();
        double cy = pt.position.y();

        XmlNode circle("circle");
        circle.set_attr("cx", hstd::fmt("{}", cx));
        circle.set_attr("cy", hstd::fmt("{}", cy));
        circle.set_attr("r", hstd::fmt("{}", pt.radius));
        applyPenAttrs(circle, pt.pen);
        applyBrushAttrs(circle, pt.brush);

        return std::move(circle);
    }

    XmlNode buildDebugMarker(
        Point const&     coord,
        hstd::Str const& message,
        json const&      extra     = json{},
        int              font_size = 4) {
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
        label.set_attr("font-size", font_size);
        label.set_attr("fill", "#aa0066");
        label.set_attr("text-anchor", "start");
        label.set_attr("dominant-baseline", "alphabetic");
        label.set_text(message);
        g.push_back(std::move(label));

        return g;
    }

    XmlNode writeElement(
        VisElement const&     elem,
        hstd::Vec<int> const& path) {
        XmlNode result = std::visit(
            [&](auto const& shape) -> XmlNode {
                return writeShape(shape);
            },
            elem.data);

        return result;
    }

    XmlNode writeGroup(
        VisGroup const&       group,
        double                ox,
        double                oy,
        hstd::Vec<int> const& path) {
        double gx = ox + group.offset.x();
        double gy = oy + group.offset.y();

        XmlNode g("g");
        g.set_attr(
            "transform",
            hstd::fmt(
                "translate({},{})", group.offset.x(), group.offset.y()));

        for (auto const& elem : group.elements) {
            for (auto const& comment : elem.comment) {
                g.push_back(XmlNode::comment(comment));
            }
            g.push_back(writeElement(elem, path));
        }

        if (!is_empty(group.extra)) {
            g.push_back(XmlNode::comment(hstd::fmt("// {}", group.extra)));
        }

        for (int i = 0; i < group.subgroups.size(); ++i) {
            auto const& sg = group.subgroups[i];
            for (auto const& comment : sg.comment) {
                g.push_back(XmlNode::comment(comment));
            }
            g.push_back(writeGroup(sg, gx, gy, path + hstd::Vec<int>{i}));
        }

        if (debug) {
            g.push_back(buildDebugMarker(
                {0, 0},
                hstd::fmt(
                    "{} @ ({:.2f},{:.2f}){}",
                    pathToString(path),
                    group.offset.x(),
                    group.offset.y(),
                    is_empty(group.extra)
                        ? ""
                        : hstd::fmt(" extra={}", group.extra.dump())),
                group.extra));
        }

        return g;
    }
};

} // namespace

Rect VisGroup::computeBounds(double ox, double oy) const {
    double gx   = ox + offset.x();
    double gy   = oy + offset.y();
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    auto expand = [&](double x, double y) {
        minX = std::min(minX, x);
        minY = std::min(minY, y);
        maxX = std::max(maxX, x);
        maxY = std::max(maxY, y);
    };

    auto expandRect = [&](Rect const& r, double ex, double ey) {
        expand(r.x() + ex, r.y() + ey);
        expand(r.x() + r.width() + ex, r.y() + r.height() + ey);
    };

    for (auto const& elem : elements) {
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
                            || cmd.type == Path::CommandType::CubicTo) {
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

    for (auto const& sub : subgroups) {
        Rect subBounds = sub.computeBounds(gx, gy);
        expand(subBounds.x(), subBounds.y());
        expand(
            subBounds.x() + subBounds.width(),
            subBounds.y() + subBounds.height());
    }

    if (minX > maxX) { return Rect(0, 0, 0, 0); }
    return Rect(minX, minY, maxX - minX, maxY - minY);
}

ColText VisGroup::treeRepr() const {
    auto aux = [](this auto&&           self,
                  VisGroup const&       group,
                  hstd::ColStream&      os,
                  int                   level,
                  hstd::Vec<int> const& path) -> void {
        os.indent(level * 2);
        os << hstd::fmt(
            "group [{}] {}", hstd::join("/", path), group.offset);
        if (!is_empty(group.extra)) {
            os.newline();
            os.indent((level + 1) * 2);
            os << hstd::fmt("// {}", group.extra);
        }
        for (auto const& comment : group.comment) {
            os.newline();
            os.indent((level + 1) * 2);
            os << hstd::fmt("# {}", comment);
        }
        for (auto const& [idx, elem] : hstd::enumerate(group.elements)) {
            os.newline();
            os.indent((level + 1) * 2);
            os << hstd::fmt("[{}] {} {}", idx, elem.getKind(), elem);
        }

        for (auto const& [idx, sub] : hstd::enumerate(group.subgroups)) {
            os.newline();
            self(sub, os, level + 1, path + hstd::as_vec(idx));
        }
    };

    hstd::ColStream res;
    aux(*this, res, 0, {});
    return res.getBuffer();
}

Rect computeBounds(hstd::Vec<VisGroup> const& groups) {
    double minX = 0.0f;
    double minY = 0.0f;
    double maxX = 0.0f;
    double maxY = 0.0f;

    if (!groups.empty()) {
        Rect first = groups.front().computeBounds(0, 0);
        minX       = first.x();
        minY       = first.y();
        maxX       = first.x() + first.width();
        maxY       = first.y() + first.height();

        for (int i = 1; i < groups.size(); ++i) {
            Rect b = groups[i].computeBounds(0, 0);
            minX   = std::min<double>(minX, b.x());
            minY   = std::min<double>(minY, b.y());
            maxX   = std::max<double>(maxX, b.x() + b.width());
            maxY   = std::max<double>(maxY, b.y() + b.height());
        }
    }

    return Rect(minX, minY, maxX - minX, maxY - minY);
}

XmlNode toSvg(hstd::Vec<VisGroup> const& groups, bool debug) {
    SvgWriter writer;
    writer.debug = debug;

    Rect bounds = computeBounds(groups);

    double margin = 4.0f;
    double viewX  = bounds.x() - margin;
    double viewY  = bounds.y() - margin;
    double viewW  = bounds.width() + 2.0f * margin;
    double viewH  = bounds.height() + 2.0f * margin;

    XmlNode svg("svg");
    svg.set_attr("xmlns", "http://www.w3.org/2000/svg");
    svg.set_attr("xmlns:xlink", "http://www.w3.org/1999/xlink");
    svg.set_attr("style", "background-color: white");
    svg.set_attr(
        "viewBox", hstd::fmt("{} {} {} {}", viewX, viewY, viewW, viewH));
    svg.set_attr("width", hstd::fmt("{}", viewW));
    svg.set_attr("height", hstd::fmt("{}", viewH));

    for (int i = 0; i < groups.size(); ++i) {
        svg.push_back(writer.writeGroup(groups[i], 0.0f, 0.0f, {i}));
    }

    return svg;
}

} // namespace hstd::ext::visual
