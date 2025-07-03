#include "ascii_editor.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_utils.hpp"
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/ColText.hpp>
#include "misc/cpp/imgui_stdlib.h"
#include <hstd/stdlib/Debug.hpp>

using namespace hstd;

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


template <typename T>
struct ImFieldEditor {
    void static render(
        std::string const& field,
        T*                 value,
        ShapeOrigin const& origin) {}
};

template <>
struct ImFieldEditor<ColRune> {
    void static render(
        std::string const& field,
        ColRune*           value,
        ShapeOrigin const& origin) {
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("%s", field.c_str());
        ImGui::TableSetColumnIndex(1);
        ImGui::InputText(
            c_fmt("##{}_{}_{}", field, origin.stack, origin.index),
            &value->rune);
    }
};

template <typename T>
void field_editor(
    std::string const& field,
    T*                 value,
    ShapeOrigin const& origin) {
    ImGui::TableNextRow();
    ImFieldEditor<std::remove_cvref_t<T>>::render(field, value, origin);
}

template <typename T, typename F>
void shape_editor(T& t, F const&, ShapeOrigin const& origin) {
    if (ImGui::BeginTable(
            c_fmt("##table_{}_{}", origin.stack, origin.index),
            2,
            ImGuiTableFlags_Borders              //
                | ImGuiTableFlags_RowBg          //
                | ImGuiTableFlags_SizingFixedFit //
                | ImGuiTableFlags_NoHostExtendX)) {

        ImGui::TableSetupColumn(
            "Field", ImGuiTableColumnFlags_WidthFixed, 200);

        ImGui::TableSetupColumn(
            "Value", ImGuiTableColumnFlags_WidthFixed, 200);

        // no, std::add_const_t<T> does not work here
        for_each_field_with_bases<F>([&](auto const& field) {
            using FieldType = DESC_FIELD_TYPE(field);
            field_editor<FieldType>(
                field.name,
                const_cast<FieldType*>(&(t.*field.pointer)),
                origin);
        });

        ImGui::EndTable();
    }
}

void render_scene_tree(Scene& scene) {
    ImGui::Begin("scene");
    {
        for (int layer_idx = 0; layer_idx < scene.stack.layers.size();
             ++layer_idx) {
            auto const& layer = scene.stack.layers.at(layer_idx);
            if (ImGui::TreeNode(c_fmt("scene_layer_{}", layer_idx))) {
                for (int shape_idx = 0; shape_idx < layer.shapes.size();
                     ++shape_idx) {
                    auto&       shape = layer.shapes.at(shape_idx);
                    ShapeOrigin origin{
                        .stack = layer_idx,
                        .index = shape_idx,
                    };
                    if (ImGui::TreeNode(c_fmt(
                            "scene_shape_{}_{}", layer_idx, shape_idx))) {
                        std::visit(
                            [&](auto& d) { shape_editor(d, d, origin); },
                            shape.data);
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}

void run_ascii_editor_widget_test(GLFWwindow* window) {

    auto     font_path = get_fontconfig_path("Iosevka");
    ImGuiIO& io        = ImGui::GetIO();

    ImVector<ImWchar>        ranges;
    ImFontGlyphRangesBuilder builder;
    builder.AddChar(0x20B9);
    builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
    builder.BuildRanges(&ranges);

    auto metric = StbFontMetrics::FromPath(font_path.value(), 16);
    for (int codepoint = 0; codepoint <= 0x10FFFF; ++codepoint) {
        if (stbtt_FindGlyphIndex(&metric->font, codepoint)) {
            builder.AddChar(static_cast<ImWchar>(codepoint));
        }
    }

    auto font = io.Fonts->AddFontFromFileTTF(
        font_path->c_str(), 16, nullptr, ranges.Data);

    int            width, height;
    unsigned char* pixels = nullptr;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    ImGui_ImplOpenGL3_CreateFontsTexture();


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
            scene.im_draw(window_pos, font, buf);
        }

        ImGui::End();
        render_scene_tree(scene);


        frame_end(window);
    }
}

void Rect2i::convex(const Vec2i& point) {
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

void DisplayBuffer::set(
    const Vec2i&       pos,
    const ColRune&     rune,
    const ShapeOrigin& origin) {
    size.convex(pos);
    runes.insert_or_assign(
        pos,
        BufferCell{
            .text   = rune,
            .origin = origin,
        });
}

Vec<Vec<DisplayCell>> DisplayBuffer::toGrid() {
    Vec<Vec<DisplayCell>> result;
    for (auto const& [pos, rune] : runes) {
        auto& ref   = result.resize_at(pos.y).resize_at(pos.y);
        ref.content = rune;
        ref.pos     = pos;
    }
    return result;
}

void Shape::Rectangle::render(
    DisplayBuffer&     buf,
    Vec2i              offset,
    const ShapeOrigin& self) const {
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

void Shape::Freeform::render(
    DisplayBuffer&     buf,
    Vec2i              offset,
    const ShapeOrigin& self) const {}

void Shape::Line::render(
    DisplayBuffer&     buf,
    Vec2i              offset,
    const ShapeOrigin& self) const {}

void Layer::render(
    DisplayBuffer&   buf,
    int              selfIndex,
    const OffsetMap& offsets) {
    if (isVisible) {
        for (int i = 0; i < shapes.size(); ++i) {
            ShapeOrigin origin{.stack = selfIndex, .index = i};
            Vec2i       offset{0, 0};
            if (offsets.contains(origin)) { offset = offsets.at(origin); }

            shapes.at(i).render(buf, origin, offset);
        }
    }
}

Opt<Vec2i> Scene::getDragOffset2i() const {
    if (dragging) {
        auto offset = Vec2i::from(dragging->current - dragging->start);
        offset.x /= cellWidth;
        offset.y /= cellHeight;
        return offset;
    } else {
        return std::nullopt;
    }
}

void Scene::render(DisplayBuffer& buf) {
    OffsetMap offsets;
    if (dragging) {
        offsets.insert_or_assign(
            dragging->target, getDragOffset2i().value());
        stack.render(buf, offsets);
    }

    stack.render(buf, offsets);
}

void Scene::im_draw(
    const ImVec2&        window_pos,
    ImFont*              font,
    const DisplayBuffer& buf) {
    auto draw = ImGui::GetWindowDrawList();

    for (int x_pos : buf.size.widthSpan()) {
        for (int y_pos : buf.size.heightSpan()) {
            ImVec2 render_pos //
                = window_pos
                + ImVec2(x_pos * cellWidth, y_pos * cellHeight);

            draw->AddRect(
                render_pos,
                render_pos + ImVec2(cellWidth, cellHeight),
                IM_COL32(155, 155, 155, 255));
        }
    }

    for (auto const& [pos, rune] : buf.runes) {
        ImVec2 render_pos //
            = window_pos + ImVec2(pos.x * cellWidth, pos.y * cellHeight);
        ImRect rect{
            render_pos, render_pos + ImVec2(cellWidth, cellHeight)};

        if (ImGui::IsMouseClicked(0)) {
            auto pos = ImGui::GetMousePos();
            if (contains(rect, pos)) {
                dragging = Scene::DragInfo{
                    .target = rune.origin,
                    .start  = pos,
                };
                HSLOG_INFO(
                    "ascii-editor",
                    fmt("Clicked on shape {}", rune.origin));
            }
        }

        if (dragging && ImGui::IsMouseDragging(0)) {
            dragging.value().current = ImGui::GetMousePos();
        }

        if (ImGui::IsMouseReleased(0)) {
            if (dragging) {
                at(dragging->target).position //
                    += getDragOffset2i().value();
                dragging.reset();
            }
        }

        auto const& text = rune.text.rune;

        ImVec2 rect_center = rect.GetCenter();
        ImVec2 text_size   = ImGui::CalcTextSize(
            text.data(), text.data() + text.size());

        ImVec2 text_pos = ImVec2(
            rect_center.x - text_size.x * 0.5f,
            rect_center.y - text_size.y * 0.5f);

        std::u32string utf32_string = std::wstring_convert<
                                          std::codecvt_utf8<char32_t>,
                                          char32_t>{}
                                          .from_bytes(text);
        for (ImWchar ch : utf32_string) {
            auto g = font->FindGlyph(ch);
            if (g == nullptr) {
                HSLOG_INFO("ascii-editor", fmt("No glyph for {}", ch));
            }
        }

        draw->AddText(
            font,
            font->FontSize,
            text_pos,
            IM_COL32(255, 0, 0, 255),
            text.data(),
            text.data() + text.size());
    }
}
