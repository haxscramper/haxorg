#include "ascii_editor.hpp"
#include "imgui_utils.hpp"
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/ColText.hpp>


struct Vec2i {
    int x = 0;
    int y = 0;

    DESC_FIELDS(Vec2i, (x, y));

    Vec2i operator+(Vec2i const& other) const {
        return {x + other.x, y + other.y};
    }

    Vec2i operator-(Vec2i const& other) const {
        return {x - other.x, y - other.y};
    }

    Vec2i without_x() const { return Vec2i{0, y}; }
    Vec2i without_y() const { return Vec2i{x, 0}; }

    Vec2i with_x(int newX) const { return Vec2i{newX, y}; }
    Vec2i with_y(int newY) const { return Vec2i{x, newY}; }

    Vec2i with_x_offset(int diff) const { return Vec2i{diff + x, y}; }
    Vec2i with_y_offset(int diff) const { return Vec2i{x, diff + y}; }

    Vec2i operator*(int scalar) const { return {x * scalar, y * scalar}; }

    Vec2i operator/(int scalar) const { return {x / scalar, y / scalar}; }

    bool operator==(Vec2i const& other) const {
        return x == other.x && y == other.y;
    }

    Vec2i& operator+=(Vec2i const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2i& operator-=(Vec2i const& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2i& operator*=(int scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2i& operator/=(int scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vec2i operator-() const { return {-x, -y}; }

    explicit operator ImVec2() const {
        return ImVec2(static_cast<float>(x), static_cast<float>(y));
    }

    static Vec2i from(ImVec2 const& v) {
        return {static_cast<int>(v.x), static_cast<int>(v.y)};
    }
};

struct Rect2i {
    Vec2i pos;
    int   width  = 0;
    int   height = 0;

    Slice<int> widthSpan() const { return slice(pos.x, pos.x + width); }
    Slice<int> heightSpan() const { return slice(pos.y, pos.y + height); }

    bool contains(Vec2i const& pos) const {
        return widthSpan().contains(pos.x) && heightSpan().contains(pos.y);
    }

    void expandX(int offset) {
        if (offset < 0) { pos.x += offset; }
        width += std::abs(offset);
    }

    void expandY(int offset) {
        if (offset < 0) { pos.y += offset; }
        height += std::abs(offset);
    }

    void convex(Vec2i const& point) {
        auto w = widthSpan();
        auto h = heightSpan();

        if (w.isBefore(point.x)) {
            expandX(point.x - w.first);
        } else if (w.isAfter(point.x)) {
            expandX(point.x - w.last);
        }

        if (h.isBefore(point.y)) {
            expandY(point.y - h.first);
        } else if (h.isAfter(point.y)) {
            expandY(point.y - h.last);
        }
    }
};

bool contains(ImRect const& rect, ImVec2 const& pos) {
    return (rect.Min.x <= pos.x && pos.x <= rect.Max.x)
        && (rect.Min.y <= pos.y && pos.y <= rect.Max.y) //
        ;
}

template <>
struct std::hash<Vec2i> {
    std::size_t operator()(Vec2i const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.x);
        hax_hash_combine(result, it.y);
        return result;
    }
};

struct ShapeOrigin {
    int stack = 0;
    int index = 0;
    DESC_FIELDS(ShapeOrigin, (stack, index));

    bool operator==(ShapeOrigin const& o) const {
        return stack == o.stack && index == o.index;
    }
};

template <>
struct std::hash<ShapeOrigin> {
    std::size_t operator()(ShapeOrigin const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.stack);
        hax_hash_combine(result, it.index);
        return result;
    }
};


struct BufferCell {
    ColRune     text;
    ShapeOrigin origin;
    DESC_FIELDS(BufferCell, (text, origin));
};

struct DisplayCell {
    Opt<BufferCell> content;
    Vec2i           pos;
    DESC_FIELDS(DisplayCell, (content, pos));

    void render() const {
        if (content) { ImGui::Text("%s", content->text.rune.c_str()); }
    }
};

struct DisplayBuffer {
    UnorderedMap<Vec2i, BufferCell> runes;
    Rect2i                          size;

    DESC_FIELDS(DisplayBuffer, (runes, size));

    void set(
        Vec2i const&       pos,
        ColRune const&     rune,
        ShapeOrigin const& origin) {
        size.convex(pos);
        runes.insert_or_assign(
            pos,
            BufferCell{
                .text   = rune,
                .origin = origin,
            });
    }

    Vec<Vec<DisplayCell>> toGrid() {
        Vec<Vec<DisplayCell>> result;
        for (auto const& [pos, rune] : runes) {
            auto& ref   = result.resize_at(pos.y).resize_at(pos.y);
            ref.content = rune;
            ref.pos     = pos;
        }
        return result;
    }
};

generator<Vec2i> line_points(Vec2i start, Vec2i end) {
    int dx = abs(end.x - start.x), dy = abs(end.y - start.y);
    int sx  = (start.x < end.x) ? 1 : -1;
    int sy  = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        co_yield start;
        if (start.x == end.x && start.y == end.y) { break; }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

struct Shape {
    struct Rectangle {
        Vec2i   size;
        ColRune upperLeft{'+'};
        ColRune lowerLeft{'+'};
        ColRune upperRight{'+'};
        ColRune lowerRight{'+'};
        ColRune topEdge{'-'};
        ColRune bottomEdge{'-'};
        ColRune leftEdge{'|'};
        ColRune rightEdge{'|'};
        DESC_FIELDS(
            Rectangle,
            (size,
             upperLeft,
             lowerLeft,
             upperRight,
             lowerRight,
             topEdge,
             bottomEdge,
             leftEdge,
             rightEdge));

        void render(
            DisplayBuffer&     buf,
            Vec2i              offset,
            ShapeOrigin const& self) const {
            for (auto const& pt : line_points(
                     offset.with_x_offset(1),
                     offset.with_x_offset(-1) + size.without_y())) {
                buf.set(pt, topEdge, self);
            }

            buf.set(offset + size.without_y(), lowerLeft, self);
            buf.set(offset + size.without_x(), upperRight, self);
            buf.set(offset + size, lowerRight, self);
            buf.set(offset, upperLeft, self);
        }
    };

    struct Freeform {
        UnorderedMap<Vec2i, ColRune> content;
        DESC_FIELDS(Freeform, (content));

        void render(
            DisplayBuffer&     buf,
            Vec2i              offset,
            ShapeOrigin const& self) const {}
    };

    struct Line {
        Vec2i first;
        Vec2i last;
        DESC_FIELDS(Line, (first, last));

        void render(
            DisplayBuffer&     buf,
            Vec2i              offset,
            ShapeOrigin const& self) const {}
    };

    SUB_VARIANTS(Kind, Data, data, getKind, Rectangle, Freeform, Line);

    Vec2i position;
    Data  data;
    DESC_FIELDS(Shape, (position, data));

    void render(
        DisplayBuffer&     buf,
        ShapeOrigin const& origin,
        Vec2i              offset) {
        std::visit(
            [&](auto const& shape) {
                shape.render(buf, position + offset, origin);
            },
            data);
    }
};

using OffsetMap = UnorderedMap<ShapeOrigin, Vec2i>;

struct Layer {
    Vec<Shape> shapes;
    bool       isVisible = true;
    DESC_FIELDS(Layer, (shapes, isVisible));

    void render(
        DisplayBuffer&   buf,
        int              selfIndex,
        OffsetMap const& offsets) {
        if (isVisible) {
            for (int i = 0; i < shapes.size(); ++i) {
                ShapeOrigin origin{.stack = selfIndex, .index = i};
                Vec2i       offset{0, 0};
                if (offsets.contains(origin)) {
                    offset = offsets.at(origin);
                }

                shapes.at(i).render(buf, origin, offset);
            }
        }
    }

    Shape& at(int const& index) { return shapes.at(index); }
    void   add(Shape const& shape) { shapes.push_back(shape); }
};

struct Stack {
    Vec<Layer> layers;
    DESC_FIELDS(Stack, (layers));
    void render(DisplayBuffer& buf, OffsetMap const& offsets) {
        for (int i = 0; i < layers.size(); ++i) {
            layers.at(i).render(buf, i, offsets);
        }
    }

    Shape& at(ShapeOrigin const& pos) {
        return layers.at(pos.stack).at(pos.index);
    }
};


struct Scene {
    Stack stack;
    int   cellWidth  = 20;
    int   cellHeight = 20;
    DESC_FIELDS(Scene, (stack, cellWidth, cellHeight));

    struct DragInfo {
        ShapeOrigin target;
        ImVec2      start;
        ImVec2      current;
        DESC_FIELDS(DragInfo, (target, start, current));
    };

    Opt<DragInfo> dragging;

    Opt<Vec2i> getDragOffset2i() const {
        if (dragging) {
            auto offset = Vec2i::from(dragging->current - dragging->start);
            offset.x /= cellWidth;
            offset.y /= cellHeight;
            return offset;
        } else {
            return std::nullopt;
        }
    }

    void render(DisplayBuffer& buf) {
        OffsetMap offsets;
        if (dragging) {
            offsets.insert_or_assign(
                dragging->target, getDragOffset2i().value());
            stack.render(buf, offsets);
        }

        stack.render(buf, offsets);
    }

    Shape& at(ShapeOrigin const& pos) { return stack.at(pos); }
};

#define c_fmt(__fmt_expr, ...) fmt(__fmt_expr, __VA_ARGS__).c_str()

void run_ascii_editor_widget_test(GLFWwindow* window) {
    ImGuiIO& io = ImGui::GetIO();

    auto font_path = get_fontconfig_path("Iosevka");
    auto font      = io.Fonts->AddFontFromFileTTF(font_path->c_str(), 24);
    auto metric    = StbFontMetrics::FromPath(font_path.value(), 24);

    Scene scene;

    scene.stack.layers.push_back(Layer{});

    auto& l0 = scene.stack.layers.at(0);
    l0.add(Shape{
        .position = Vec2i{2, 2},
        .data     = Shape::Rectangle{.size = Vec2i{10, 10}}});

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();
        {
            DisplayBuffer buf;
            scene.render(buf);
            ImVec2 window_pos = ImGui::GetWindowPos() + ImVec2{50, 50};

            auto draw = ImGui::GetWindowDrawList();

            LOG_EVERY_POW_2(INFO) << fmt(
                "{}x{}", buf.size.widthSpan(), buf.size.heightSpan());

            for (int x_pos : buf.size.widthSpan()) {
                for (int y_pos : buf.size.heightSpan()) {
                    ImVec2 render_pos //
                        = window_pos
                        + ImVec2(
                              x_pos * scene.cellWidth,
                              y_pos * scene.cellHeight);

                    draw->AddRect(
                        render_pos,
                        render_pos
                            + ImVec2(scene.cellWidth, scene.cellHeight),
                        IM_COL32(155, 155, 155, 255));
                }
            }

            for (auto const& [pos, rune] : buf.runes) {
                ImVec2 render_pos //
                    = window_pos
                    + ImVec2(
                          pos.x * scene.cellWidth,
                          pos.y * scene.cellHeight);
                ImRect rect{
                    render_pos,
                    render_pos
                        + ImVec2(scene.cellWidth, scene.cellHeight)};

                if (ImGui::IsMouseClicked(0)) {
                    auto pos = ImGui::GetMousePos();
                    if (contains(rect, pos)) {
                        scene.dragging = Scene::DragInfo{
                            .target = rune.origin,
                            .start  = pos,
                        };
                        LOG(INFO)
                            << fmt("Clicked on shape {}", rune.origin);
                    }
                }

                if (scene.dragging && ImGui::IsMouseDragging(0)) {
                    scene.dragging.value().current = ImGui::GetMousePos();
                }

                if (ImGui::IsMouseReleased(0)) {
                    if (scene.dragging) {
                        scene.at(scene.dragging->target).position //
                            += scene.getDragOffset2i().value();
                        scene.dragging.reset();
                    }
                }

                auto const& text = rune.text.rune;

                ImVec2 rect_center = rect.GetCenter();
                ImVec2 text_size   = ImGui::CalcTextSize(
                    text.data(), text.data() + text.size());

                ImVec2 text_pos = ImVec2(
                    rect_center.x - text_size.x * 0.5f,
                    rect_center.y - text_size.y * 0.5f);

                draw->AddText(
                    font,
                    font->FontSize,
                    text_pos,
                    IM_COL32(255, 0, 0, 255),
                    text.data(),
                    text.data() + text.size());
            }
        }
        ImGui::End();
        frame_end(window);
    }
}
