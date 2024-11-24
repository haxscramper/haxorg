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
    int stack;
    int index;
    DESC_FIELDS(ShapeOrigin, (stack, index));
};

struct DisplayCell {
    ColRune     text;
    ShapeOrigin origin;
    DESC_FIELDS(DisplayCell, (text, origin));
};

struct DisplayBuffer {
    UnorderedMap<Vec2i, DisplayCell> runes;
    Vec2i                            size;

    DESC_FIELDS(DisplayBuffer, (runes, size));

    void set(
        Vec2i const&       pos,
        ColRune const&     rune,
        ShapeOrigin const& origin) {
        runes.insert_or_assign(pos, rune);
    }

    Vec<Vec<ColRune>> toGrid() {
        Vec<Vec<ColRune>> result;
        for (auto const& [pos, rune] : runes) {
            result.resize_at(pos.y).resize_at(pos.y) = rune.text;
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

    void render(DisplayBuffer& buf, ShapeOrigin const& origin) {
        std::visit(
            [&](auto const& shape) {
                shape.render(buf, position, origin);
            },
            data);
    }
};

struct Layer {
    Vec<Shape> shapes;
    DESC_FIELDS(Layer, (shapes));

    void render(DisplayBuffer& buf, int selfIndex) {
        for (int i = 0; i < shapes.size(); ++i) {
            shapes.at(i).render(
                buf,
                ShapeOrigin{
                    .stack = selfIndex,
                    .index = i,
                });
        }
    }
};

struct Stack {
    Vec<Layer> layers;
    DESC_FIELDS(Stack, (layers));
    void render(DisplayBuffer& buf) {
        for (int i = 0; i < layers.size(); ++i) {
            layers.at(i).render(buf, i);
        }
    }
};


struct Scene {
    Stack stack;
    DESC_FIELDS(Scene, (stack));

    void render(DisplayBuffer& buf) { stack.render(buf); }
};


void run_ascii_editor_widget_test(GLFWwindow* window) {
    Scene scene;
    while (!glfwWindowShouldClose(window)) {
        frame_start();
        ImGui::Begin("Fullscreen Window", nullptr);
        {
            //
        }
        ImGui::End();
        frame_end(window);
    }
}
