#include "im_org_ui_common.hpp"


EditableOrgText to_editable_text(const org::ImmAdapter it) {
    EditableOrgText res;


    return res;
}

EditableTextResult render_editable_text(
    std::string&             value,
    std::string&             edit_buffer,
    bool&                    is_editing,
    ImVec2 const&            size,
    TreeGridColumn::EditMode edit,
    std::string const&       id) {
    auto __scope = IM_SCOPE_BEGIN(
        "Editable text",
        fmt("size:{} editing:{} buffer:{}",
            size,
            is_editing,
            escape_literal(edit_buffer)));

    auto cell_prefix = fmt("{}", id);

    auto get_editor = [&](const ImVec2& size) {
        render_debug_rect(size, IM_COL32(255, 0, 0, 255));
        auto frameless_vars = push_frameless_window_vars();
        ImGui::BeginChild(
            fmt("##{}_container", id).c_str(),
            size,
            false,
            ImGuiWindowFlags_NoScrollbar);

        auto res = ImGui::ScInputText(c_fmt("sci_editor_{}", id));

        ImGui::EndChild();
        ImGui::PopStyleVar(frameless_vars);
        return res;
    };

    auto get_log = [](int         line     = __builtin_LINE(),
                      char const* function = __builtin_FUNCTION(),
                      char const* file     = __builtin_FILE())
        -> org_logging::log_builder {
        return std::move(SGR_LOG_ROOT("text", ol_trace)
                             .set_callsite(line, function, file));
    };

    if (edit == TreeGridColumn::EditMode::Multiline) {

        if (is_editing) {
            auto this_size = size - ImVec2(0, 40);
            auto ed        = get_editor(this_size);
            ed->HandleInput();
            ed->Render();
            IM_FN_PRINT("Render done", "");

            if (IM_FN_EXPR(Button, "done")) {
                get_log().message("Clicked 'done'");
                value      = ed->GetText();
                is_editing = false;
                return EditableTextResult::Changed;
            } else if (ImGui::SameLine(); IM_FN_EXPR(Button, "cancel")) {
                get_log().message("Clicked 'cancel'");
                is_editing = false;
                return EditableTextResult::CancelledEditing;
            } else {
                return EditableTextResult::None;
            }

        } else {
            auto frameless_vars = push_frameless_window_vars();
            ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + size.x);
            // NOTE: Using ID with runtime formatting here because
            // there is more than one cell that might potentially be
            // edited.
            if (IM_FN_BEGIN(
                    BeginChild,
                    fmt("##{}_wrap", cell_prefix).c_str(),
                    size,
                    ImGuiChildFlags_None,
                    ImGuiWindowFlags_NoScrollbar)) {
                IM_FN_PRINT("Child", fmt("size:{}", size));
                ImGui::PushID(fmt("##{}_view", cell_prefix).c_str());
                IM_FN_STMT(TextWrapped, "%s", value.c_str());
                IM_FN_PRINT("Wrapped text", value);
                ImGui::PopID();
            }

            IM_FN_END(EndChild);

            ImGui::PopTextWrapPos();
            ImGui::PopStyleVar(frameless_vars);

            if (ImGui::IsItemClicked()) {
                is_editing = true;
                auto ed    = get_editor(size);
                ed->WrapOnChar();
                ed->HideAllMargins();
                ed->SetText(value);
                return EditableTextResult::StartedEditing;
            } else {
                return EditableTextResult::None;
            }
        }
    } else {
        if (is_editing) {
            if (ImGui::Button("OK")) {
                value      = edit_buffer;
                is_editing = false;
                return EditableTextResult::Changed;
            } else if (ImGui::SameLine(0.0f, 0.0f); ImGui::Button("X")) {
                is_editing = false;
                return EditableTextResult::CancelledEditing;
            } else {
                ImGui::SameLine(0.0f, 0.0f);
                ImGui::SetNextItemWidth(size.x);
                ImGui::InputText(
                    fmt("##{}_edit", cell_prefix).c_str(), &edit_buffer);
                return EditableTextResult::None;
            }

        } else {
            IM_FN_STMT(Text, "%s", value.c_str());
            IM_FN_PRINT("Text render", value);
            if (ImGui::IsItemClicked()) {
                is_editing  = true;
                edit_buffer = value;
                return EditableTextResult::StartedEditing;
            } else {
                return EditableTextResult::None;
            }
        }
    }
}
