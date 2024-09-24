#include "story_grid.hpp"

#include <haxorg/sem/ImmOrgEdit.hpp>
#include "imgui_internal.h"
#include "imgui_utils.hpp"
#include "imgui.h"

#define CTX_MSG(...)                                                      \
    if (ctx.OperationsTracer::TraceState) { ctx.message(__VA_ARGS__); }


Opt<GridAction> render_cell(GridCell& cell, GridContext& ctx) {
    // ImGui::PushTextWrapPos();
    // ImGui::BeginChild(
    //     "##editable_text", ImVec2(cell.width, cell.height), true);
    Opt<GridAction> result;
    push_ptr_id((void*)&cell.value[0]);
    ImGui::Text("%s", cell.value.c_str());


    // if (ImGui::InputTextMultiline(
    //         "##input",
    //         &cell.value[0],
    //         cell.value.capacity() + 1,
    //         ImVec2(-FLT_MIN, -FLT_MIN),
    //         ImGuiInputTextFlags_AllowTabInput)) {
    //     cell.value.resize(strlen(cell.value.c_str()));
    //     result = GridAction{GridAction::EditCell{
    //         .cell    = cell,
    //         .updated = cell.value,
    //     }};
    // }
    ImGui::PopID();
    // ImGui::EndChild();
    // ImGui::PopTextWrapPos();
    return result;
}

void render_tree_columns(
    GridRow&         row,
    Vec<GridAction>& result,
    GridContext&     ctx) {
    int colIdx = 1;
    for (auto const& col : ctx.columnNames) {
        if (row.columns.contains(col)) {
            ImGui::TableSetColumnIndex(colIdx);
            render_cell(row.columns.at(col), ctx);
        }
        ++colIdx;
    }
}

void render_tree_row(
    GridRow&         row,
    Vec<GridAction>& result,
    GridContext&     ctx) {
    bool skipped = false;
    CTX_MSG(fmt("row {}", row.title));

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
            ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg
                | ImGuiTableFlags_SizingFixedFit)) {

        ImGui::TableSetupColumn(
            "Tree", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        for (auto const& col : ctx.columnNames) {
            ImGui::TableSetupColumn(
                col.c_str(),
                ImGuiTableColumnFlags_WidthFixed,
                ctx.widths.at(col));
        }
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
        "event",
        "location",
        "time",
    };

    model.conf.widths["title"]    = 120;
    model.conf.widths["location"] = 120;
    model.conf.widths["event"]    = 120;
    model.conf.widths["time"]     = 120;
    model.conf.widths["note"]     = 120;

    bool first = true;

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


GridRow buildRow(
    org::ImmAdapterT<org::ImmSubtree> tree,
    const GridContext&                conf) {
    GridRow result;
    result.title  = buildCell(tree.getTitle(), conf.widths.at("title"));
    result.origin = tree;
    for (auto const& sub : tree.subAs<org::ImmList>()) {
        if (sub.isDescriptionList()) {
            for (auto const& item : sub.subAs<org::ImmListItem>()) {
                auto flat = flatWords(item.getHeader().value());
                for (auto const& word : flat) {
                    if (word.starts_with("story_")) {
                        auto column            = word.dropPrefix("story_");
                        result.columns[column] = buildCell(
                            item.at(0), conf.widths.at(column));
                    }
                }
            }
        }
    }

    for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
        result.nested.push_back(buildRow(sub, conf));
    }

    return result;
}

Vec<GridRow> buildRows(org::ImmAdapter root, const GridContext& conf) {
    Vec<GridRow> result;
    for (auto const& tree : root.subAs<org::ImmSubtree>()) {
        result.push_back(buildRow(tree, conf));
    }

    return result;
}

GridCell buildCell(org::ImmAdapter adapter, int width) {
    GridCell result;
    result.value  = join(" ", flatWords(adapter));
    result.origin = adapter;
    result.width  = width;

    ImGuiContext& g          = *ImGui::GetCurrentContext();
    ImFont*       font       = g.Font;
    const char*   text_begin = result.value.c_str();
    const char*   text_end   = text_begin + result.value.length();

    ImVec2 text_size = font->CalcTextSizeA(
        font->FontSize, width, 0.0f, text_begin, text_end, nullptr);

    result.height = text_size.y + 2;

    return result;
}

void GridModel::updateDocument() {
    document.rows = buildRows(
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
                        edit.cell.origin,
                        ast.add(
                            sem::asOneNode(
                                sem::parseString(edit.cell.value)),
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
