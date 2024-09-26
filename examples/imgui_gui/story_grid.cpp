#include "story_grid.hpp"

#include <haxorg/sem/ImmOrgEdit.hpp>
#include "imgui_internal.h"
#include "imgui_utils.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "imgui.h"

#include <fontconfig/fontconfig.h>


Opt<Str> get_fontconfig_path(std::string const& fontname) {
    FcInit();
    FcPattern* pattern = FcNameParse((const FcChar8*)fontname.c_str());
    FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult   result;
    FcPattern* match = FcFontMatch(nullptr, pattern, &result);

    FcChar8* font_path = nullptr;
    if (match) { FcPatternGetString(match, FC_FILE, 0, &font_path); }
    Opt<Str> opt_result;
    if (font_path != nullptr) { opt_result = (char const*)font_path; }
    FcPatternDestroy(pattern);
    FcPatternDestroy(match);
    FcFini();
    return opt_result;
}

Vec<Str> split_wrap_text(std::string const& unwrapped, int width) {
    Vec<Str>    result;
    const char* text = unwrapped.c_str();
    while (*text) {
        const char* line_start = text;
        float       line_width = 0.0f;
        while (*text && line_width < width) {
            uint        __out_char = 0;
            auto        size = ImTextCharFromUtf8(&__out_char, text, NULL);
            const char* next = text + size;
            if (next == text) { break; }
            auto width = ImGui::CalcTextSize(text, next).x;
            line_width += width;
            text = next;
        }
        result.emplace_back(line_start, text - line_start);
    }

    return result;
}

#define CTX_MSG(...)                                                      \
    if (ctx.OperationsTracer::TraceState) { ctx.message(__VA_ARGS__); }

#define CTX_MSG_ALL(...) ctx.message(__VA_ARGS__);


void render_debug_rect(ImVec2 const& size, int border = 2) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - border);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - border);
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(
        p0.x + size.x + (2 * border), p0.y + size.y + (2 * border));
    ImGui::GetWindowDrawList()->AddRect(
        p0, p1, IM_COL32(255, 255, 255, 255));
}

bool render_editable_cell(GridCell& cell, GridContext& ctx) {
    auto  cell_prefix = fmt("{:p}", static_cast<const void*>(&cell));
    auto& val         = cell.getValue();
    if (val.is_editing) {
        ImGui::InputTextMultiline(
            fmt("##{}_edit", cell_prefix).c_str(),
            &val.edit_buffer,
            ImVec2(cell.width, cell.height + 10),
            ImGuiInputTextFlags_None);


        if (ImGui::Button("done")) {
            val.value             //
                = val.edit_buffer //
                | rv::remove_if(
                      [](char c) { return c == '\n' || c == '\r'; })
                | rs::to<std::string>;
            val.is_editing = false;
            return true;
        } else if (ImGui::SameLine(); ImGui::Button("cancel")) {
            val.is_editing = false;
            return false;
        } else {
            return false;
        }


    } else {
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
            ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + cell.width);
            // NOTE: Using ID with runtime formatting here because there is
            // more than one cell that might potentially be edited.
            ImGui::BeginChild(
                fmt("##{}_wrap", cell_prefix).c_str(),
                ImVec2(cell.width, cell.height),
                false,
                ImGuiWindowFlags_NoScrollbar);
            ImGui::PushID(fmt("##{}_view", cell_prefix).c_str());
            ImGui::TextWrapped("%s", val.value.c_str());
            ImGui::PopID();
            ImGui::EndChild();
            ImGui::PopTextWrapPos();
            ImGui::PopStyleVar(3);
        }
        if (ImGui::IsItemClicked()) {
            val.is_editing = true;
            val.edit_buffer.clear();
            CTX_MSG(fmt("Value:{}", val.value));
            auto __scope    = ctx.scopeLevel();
            val.edit_buffer = join(
                "\n", split_wrap_text(val.value, cell.width));
        }
        return false;
    }
}


Opt<GridAction> render_cell(GridCell& cell, GridContext& ctx) {
    Opt<GridAction> result;

    if (render_editable_cell(cell, ctx)) {
        result = GridAction{GridAction::EditCell{
            .cell    = cell,
            .updated = cell.getValue().value,
        }};
    }

    return result;
}

void render_tree_columns(
    GridRow&         row,
    Vec<GridAction>& result,
    GridContext&     ctx) {
    auto __scope = ctx.scopeLevel();
    int  colIdx  = 1;
    for (auto const& col : ctx.columnNames) {
        if (row.columns.contains(col)) {
            ImGui::TableSetColumnIndex(colIdx);
            render_cell(row.columns.at(col), ctx);
            CTX_MSG(fmt("{} = {}", col, row.columns.at(col)));
        }
        ++colIdx;
    }
}

void render_tree_row(
    GridRow&         row,
    Vec<GridAction>& result,
    GridContext&     ctx) {
    bool skipped = false;
    CTX_MSG(fmt("row {}", row.columns.at("title")));

    if (!skipped || !row.nested.empty()) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
    }

    if (!row.nested.empty()) {
        ImGui::PushID(fmt("{}", row.origin.id).c_str());
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        bool node_open = ImGui::TreeNodeEx(
            fmt("[{}]", row.origin->level).c_str(),
            ImGuiTreeNodeFlags_SpanFullWidth);
        ImGui::PopID();
        render_tree_columns(row, result, ctx);
        if (node_open) {
            for (auto& sub : row.nested) {
                render_tree_row(sub, result, ctx);
            }

            ImGui::TreePop();
        }
    } else if (!skipped) {
        render_tree_columns(row, result, ctx);
    }
}

Vec<GridAction> render_story_grid(GridDocument& doc, GridContext& ctx) {
    Vec<GridAction> result;
    CTX_MSG(fmt("doc rows {}", doc.rows.size()));

    if (ImGui::BeginTable(
            "TreeTable",
            1 + ctx.columnNames.size(),
            ImGuiTableFlags_ScrollY       //
                | ImGuiTableFlags_Borders //
                | ImGuiTableFlags_RowBg   //
                | ImGuiTableFlags_SizingFixedFit)) {

        ImGui::TableSetupColumn(
            "Tree", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        for (auto const& col : ctx.columnNames) {
            ImGui::TableSetupColumn(
                col.c_str(),
                ImGuiTableColumnFlags_WidthFixed,
                ctx.widths.get(col).value_or(120));
        }
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();

        for (auto& sub : doc.rows) { render_tree_row(sub, result, ctx); }

        ImGui::EndTable();
    }

    return result;
}

void story_grid_loop(GLFWwindow* window, sem::SemId<sem::Org> node) {


    GridModel          model;
    org::ImmAstContext start;
    model.history.push_back(GridState{
        .ast = start.init(node),
    });


    model.conf.setTraceFile("/tmp/story_grid_trace.txt");
    model.conf.columnNames = {
        "title",
        "location",
        "value",
        "note",
        "event",
        "turning_point",
    };

    model.conf.widths["title"]    = 300;
    model.conf.widths["location"] = 240;
    model.conf.widths["event"]    = 400;
    model.conf.widths["time"]     = 120;
    model.conf.widths["note"]     = 120;

    bool first = true;

    auto font_path = get_fontconfig_path("Iosevka");
    if (font_path) {
        LOG(INFO) << fmt("Using font file {}", *font_path);
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF(font_path->c_str(), 16);
    } else {
        LOG(ERROR) << "Could not load font path";
    }

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();
        if (first) {
            first = false;
            model.updateDocument();
        }

        Vec<GridAction> updates = render_story_grid(
            model.document, model.conf);
        ImGui::End();
        frame_end(window);
        if (!updates.empty()) {
            for (auto const& update : updates) { model.apply(update); }
            model.updateDocument();
        }

        model.conf.OperationsTracer::TraceState = false;
    }
}


GridCell build_editable_cell(
    org::ImmAdapter    adapter,
    int                width,
    GridContext const& ctx);

GridRow build_row(
    org::ImmAdapterT<org::ImmSubtree> tree,
    GridContext&                      conf) {
    GridRow result;
    result.columns["title"] = build_editable_cell(
        tree.getTitle(), conf.widths.at("title"), conf);
    result.origin = tree;
    for (auto const& sub : tree.subAs<org::ImmList>()) {
        if (sub.isDescriptionList()) {
            for (auto const& item : sub.subAs<org::ImmListItem>()) {
                auto flat = flatWords(item.getHeader().value());
                for (auto const& word : flat) {
                    if (word.starts_with("story_")) {
                        auto column = word.dropPrefix("story_");
                        if (!conf.widths.contains(column)) {
                            conf.widths[column] = 120;
                        }
                        result.columns[column] = build_editable_cell(
                            item.at(0), conf.widths.at(column), conf);

                        if (!conf.columnNames.contains(column)) {
                            conf.columnNames.push_back(column);
                        }
                    }
                }
            }
        }
    }

    for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
        result.nested.push_back(build_row(sub, conf));
    }

    return result;
}

Vec<GridRow> build_rows(org::ImmAdapter root, GridContext& conf) {
    Vec<GridRow> result;
    for (auto const& tree : root.subAs<org::ImmSubtree>()) {
        result.push_back(build_row(tree, conf));
    }

    return result;
}

GridCell build_editable_cell(
    org::ImmAdapter    adapter,
    int                width,
    GridContext const& ctx) {
    GridCell result{GridCell::Value{}};
    auto&    v   = result.getValue();
    v.value      = join(" ", flatWords(adapter));
    v.origin     = adapter;
    result.width = width;


    Vec<Str> wrapped = split_wrap_text(v.value, width);

    {
        std::string _tmp{"Tt"};
        char const* _tmp_begin = _tmp.c_str();
        char const* _tmp_end   = _tmp_begin + _tmp.length();
        ImVec2      text_size  = ImGui::CalcTextSize(
            _tmp_begin, _tmp_end, false, width);

        result.height = 0 < wrapped.size() ? text_size.y * wrapped.size()
                                           : text_size.y;
    }

    CTX_MSG(
        fmt("width:{} height:{} text:{} wrapped:{}",
            width,
            result.height,
            escape_literal(v.value),
            wrapped));

    return result;
}

void GridModel::updateDocument() {
    document.rows = build_rows(
        getCurrentState().ast.getRootAdapter(), conf);
}

void GridModel::apply(const GridAction& act) {
    switch (act.getKind()) {
        case GridAction::Kind::EditCell: {
            auto edit = act.getEditCell();
            org::ImmAstVersion vNext = getCurrentState().ast.getEditVersion(
                [&](org::ImmAstContext& ast, org::ImmAstEditContext& ctx)
                    -> org::ImmAstReplaceGroup {
                    org::ImmAstReplaceGroup result;
                    result.incl(org::replaceNode(
                        edit.cell.getValue().origin,
                        ast.add(
                            sem::asOneNode(sem::parseString(edit.updated)),
                            ctx),
                        ctx));
                    return result;
                });
            history.push_back(GridState{
                .ast = vNext,
            });
            break;
        }
    }
}

void GridContext::message(
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) const {
    OperationsTracer::message(value, activeLevel, line, function, file);
}
