#include "story_grid.hpp"


void TreeGridCell::render(
    StoryGridModel&        model,
    StoryNodeId const&     id,
    StoryGridConfig const& conf,
    ImVec2 const&          start,
    const std::string&     im_tag) {
    auto& ctx = model.ctx;

    IM_FN_PRINT("Cell", hstd::fmt("pos:{} size:{}", start, getSize()));
    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(start);
    if (IM_FN_BEGIN(
            BeginChild,
            c_fmt("cell_{}", im_tag),
            getSize(),
            ImGuiChildFlags_Borders,
            ImGuiWindowFlags_NoScrollbar)) {

        auto& val = getValue();
        auto  res = val.value.render(hstd::fmt("cell_{}_{}", id, im_tag));

        if (res) {
            ctx.action(GridAction::EditCell{
                .edit = res.value(),
                .id   = id,
            });
        }
    }

    IM_FN_END(EndChild);
    ImGui::PopStyleVar(frameless_vars);
}


void StoryNode::TreeGrid::render(
    StoryGridModel&        model,
    StoryNodeId const&     id,
    StoryGridConfig const& conf) {

    auto& ctx = model.ctx;
    ImGui::SetNextWindowPos(model.graph.getPosition(id) + model.shift);
    ImGui::SetNextWindowSize(
        getSize() + ImVec2(0, node.tableHeaderHeight));
    auto frameless_vars = push_frameless_window_vars();
    // Table is drawn in a separate window so it could have the widgets
    // inside, but otherwise is positioned completely independently on the
    // screen.
    if (IM_FN_BEGIN(
            Begin,
            "Standalone Table Window",
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
        node.render(model, id, conf);

        IM_FN_END(End);
    }
    ImGui::PopStyleVar(frameless_vars);
}

void TreeGridDocument::render(
    StoryGridModel&        model,
    StoryNodeId const&     id,
    StoryGridConfig const& conf) {
    auto& ctx       = model.ctx;
    auto  gridStart = ImGui::GetCursorScreenPos();

    // Table for the story grid node is drawn as a small floating window
    // that is overlaid exactly on top of the existing bar. I have no
    // fucking idea how to make the table header stick while scrolling
    // (yes, I saw the github replies etc., they don't work). Floating
    // window obviously solves this issue, as it is positioned completely
    // independently of the content in the grid table itself.
    ImGui::SetNextWindowPos(
        ImVec2(model.graph.getPosition(id) + model.shift));
    ImGui::SetNextWindowSize(ImVec2(getWidth(), 20));
    auto frameless_vars = push_frameless_window_vars();
    if (IM_FN_BEGIN(
            Begin,
            "HeaderOverlay",
            nullptr,
            ImGuiWindowFlags_NoDecoration
                | ImGuiWindowFlags_AlwaysAutoResize
                | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoScrollbar
                | ImGuiWindowFlags_NoScrollWithMouse)) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
        for (auto const& [idx, col] : enumerate(columns)) {
            ImGui::GetWindowDrawList()->AddText(
                gridStart + ImVec2(colPositions.at(idx), 0),
                IM_COL32(255, 255, 255, 255),
                col.name.data(),
                col.name.data() + col.name.size());
        }

        IM_FN_END(End);
    }
    ImGui::PopStyleVar(frameless_vars);

    // render_debug_rect(ImRect(gridStart, gridStart + gridSize));
    ImGui::SetNextWindowPos(gridStart);
    if (IM_FN_BEGIN(
            BeginChild,
            "table_ch",
            getSize(),
            ImGuiChildFlags_Borders,
            ImGuiWindowFlags_NoScrollbar
                | ImGuiWindowFlags_NoBackground)) {
        for (auto& sub : rows) {
            sub->render(this, model, id, conf, gridStart);
        }
    }
    IM_FN_END(EndChild);
}


void TreeGridRow::render(
    TreeGridDocument*      doc,
    StoryGridModel&        model,
    StoryNodeId const&     id,
    StoryGridConfig const& conf,
    ImVec2 const&          start) {
    // row is completely invisible, including its nested sub-rows
    if (!isVisible) { return; }
    bool  skipped = false;
    auto& ctx     = model.ctx;
    auto  __scope = ctx.scopeLevel();

    if (skipped && nested.empty()) { return; };

    auto __im_scope = IM_SCOPE_BEGIN(
        "Tree row", hstd::fmt("row [{}]", flatIdx));

    auto render_tree_columns = [&]() {

    };

    if (!nested.empty() || !skipped) {
        auto __scope = ctx.scopeLevel();
        int  colIdx  = 1;
        for (auto const& col : doc->columns) {
            if (columns.contains(col.name)) {
                auto __scope = ctx.scopeLevel();
                columns.at(col.name).render(
                    model,
                    id,
                    conf,
                    start + doc->getCellPos(flatIdx, col.name),
                    hstd::fmt("{}_{}", flatIdx, col));
            }
            ++colIdx;
        }
    }


    if (!nested.empty() && isOpen) {
        for (auto& sub : nested) {
            sub->render(doc, model, id, conf, start);
        }
    }

    ImRect cell_rect = ImRect(
        start + ImVec2(0, doc->getRowYPos(flatIdx)),
        start
            + ImVec2(
                doc->treeFoldWidth,
                doc->getRowYPos(flatIdx) + getHeight().value_or(0)));

    if (cell_rect.Contains(ImGui::GetMousePos())) {
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            ImGui::OpenPopup(hstd::fmt("ctx_{}", origin.id).c_str());
        }
    }

    if (ImGui::BeginPopup(hstd::fmt("ctx_{}", origin.id).c_str())) {
        if (ImGui::MenuItem("Copy")) {
            if (origin->treeId.get().has_value()) {
                ImGui::SetClipboardText(origin->treeId->value().c_str());
            }
        }
        ImGui::EndPopup();
    }

    ImVec2 cell_max  = cell_rect.Max;
    ImVec2 rect_size = ImVec2(
        std::ceil(
            ((6 - origin->level) / 6.0f)
            * (cell_rect.Max.x - cell_rect.Min.x)),
        cell_rect.Max.y - cell_rect.Min.y);
    float  pad      = 2.0f;
    ImVec2 rect_min = cell_max - rect_size + ImVec2(pad, pad);
    ImVec2 rect_max = cell_max - ImVec2(pad, pad);

    if (ImGui::IsMouseHoveringRect(cell_rect.Min, cell_rect.Max)) {
        ImGui::GetWindowDrawList()->AddRect(
            rect_min,
            rect_max,
            isOpen ? conf.foldCellHoverBackground_Open
                   : conf.foldCellHoverBackground_Closed,
            0.0f,
            0,
            1.0f);
        if (ImGui::IsMouseClicked(0)) {
            isOpen = !isOpen;
            ctx.action(GridAction::RowFolding{
                .isOpen  = isOpen,
                .flatIdx = flatIdx,
                .id      = id,
            });
        }
    }

    ImGui::GetWindowDrawList()->AddRectFilled(
        rect_min,
        rect_max,
        isOpen ? conf.foldCellForeground_Open
               : conf.foldCellForeground_Closed);
}
