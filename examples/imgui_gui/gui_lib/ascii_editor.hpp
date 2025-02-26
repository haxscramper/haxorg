#pragma once

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Map.hpp>
#include <imgui/imgui_internal.h>
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

    hstd::Slice<int> widthSpan() const {
        return hstd::slice(pos.x, pos.x + width);
    }
    hstd::Slice<int> heightSpan() const {
        return hstd::slice(pos.y, pos.y + height);
    }

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

    void convex(Vec2i const& point);
};

inline bool contains(ImRect const& rect, ImVec2 const& pos) {
    return (rect.Min.x <= pos.x && pos.x <= rect.Max.x)
        && (rect.Min.y <= pos.y && pos.y <= rect.Max.y) //
        ;
}

template <>
struct std::hash<Vec2i> {
    std::size_t operator()(Vec2i const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.x);
        hstd::hax_hash_combine(result, it.y);
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
        hstd::hax_hash_combine(result, it.stack);
        hstd::hax_hash_combine(result, it.index);
        return result;
    }
};


struct BufferCell {
    hstd::ColRune text;
    ShapeOrigin   origin;
    DESC_FIELDS(BufferCell, (text, origin));
};

struct DisplayCell {
    hstd::Opt<BufferCell> content;
    Vec2i                 pos;
    DESC_FIELDS(DisplayCell, (content, pos));

    void render() const {
        if (content) { ImGui::Text("%s", content->text.rune.c_str()); }
    }
};

struct DisplayBuffer {
    hstd::UnorderedMap<Vec2i, BufferCell> runes;
    Rect2i                                size;

    DESC_FIELDS(DisplayBuffer, (runes, size));

    void set(
        Vec2i const&         pos,
        hstd::ColRune const& rune,
        ShapeOrigin const&   origin);

    hstd::Vec<hstd::Vec<DisplayCell>> toGrid();
};

struct Shape {
    struct Rectangle {
        Vec2i         size;
        hstd::ColRune upperLeft{"#"};
        hstd::ColRune lowerLeft{"#"};
        hstd::ColRune upperRight{"#"};
        hstd::ColRune lowerRight{"#"};
        hstd::ColRune topEdge{"#"};
        hstd::ColRune bottomEdge{"#"};
        hstd::ColRune leftEdge{"#"};
        hstd::ColRune rightEdge{"#"};
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
            ShapeOrigin const& self) const;
    };

    struct Freeform {
        hstd::UnorderedMap<Vec2i, hstd::ColRune> content;
        DESC_FIELDS(Freeform, (content));

        void render(
            DisplayBuffer&     buf,
            Vec2i              offset,
            ShapeOrigin const& self) const;
    };

    struct Line {
        Vec2i first;
        Vec2i last;
        DESC_FIELDS(Line, (first, last));

        void render(
            DisplayBuffer&     buf,
            Vec2i              offset,
            ShapeOrigin const& self) const;
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

using OffsetMap = hstd::UnorderedMap<ShapeOrigin, Vec2i>;

struct Layer {
    hstd::Vec<Shape> shapes;
    bool             isVisible = true;
    DESC_FIELDS(Layer, (shapes, isVisible));

    void render(
        DisplayBuffer&   buf,
        int              selfIndex,
        OffsetMap const& offsets);

    Shape& at(int const& index) { return shapes.at(index); }
    void   add(Shape const& shape) { shapes.push_back(shape); }
};

struct Stack {
    hstd::Vec<Layer> layers;
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

    hstd::Opt<DragInfo> dragging;
    hstd::Opt<Vec2i> getDragOffset2i() const;

    void render(DisplayBuffer& buf);

    Shape& at(ShapeOrigin const& pos) { return stack.at(pos); }

    void im_draw(
        ImVec2 const&        window_pos,
        ImFont*              font,
        DisplayBuffer const& buf);
};

void run_ascii_editor_widget_test(GLFWwindow* window);
