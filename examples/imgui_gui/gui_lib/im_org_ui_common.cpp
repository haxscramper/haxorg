#include "im_org_ui_common.hpp"
#include <gui_lib/imgui_utils.hpp>
#include <gui_lib/scintilla_editor_widget.hpp>
#include "misc/cpp/imgui_stdlib.h"
#include <haxorg/sem/SemOrgFormat.hpp>


EditableOrgText EditableOrgText::from_adapter(const org::ImmAdapter& it) {
    EditableOrgText      res;
    sem::SemId<sem::Org> sem_ast = org::sem_from_immer(it.id, *it.ctx);
    res.value                    = sem::Formatter::format(sem_ast);
    return res;
}

namespace {
int edit_button_offset = 40;
}


int EditableOrgTextEntry::getHeight() const {
    LOGIC_ASSERTION_CHECK(
        assignedWidth != 0,
        "Cannot get editable text height without assigned width");
    return computedHeight + (text.is_editing ? edit_button_offset : 0);
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


int EditableOrgText::get_expected_height(int width, Mode mode) {
    Vec<Str>    wrapped = split_wrap_text(value, width);
    std::string _tmp{"Tt"};
    char const* _tmp_begin = _tmp.c_str();
    char const* _tmp_end   = _tmp_begin + _tmp.length();
    ImVec2      text_size  = ImGui::CalcTextSize(
        _tmp_begin, _tmp_end, false, width);

    if (mode == Mode::SingleLine) {
        return text_size.y;
    } else {
        return (
            0 < wrapped.size() ? text_size.y * (wrapped.size() + 1)
                               : text_size.y);
    }
}

EditableOrgText::Result EditableOrgText::render(
    ImVec2 const&         size,
    EditableOrgText::Mode edit,
    std::string const&    id) {
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

    if (edit == Mode::Multiline) {
        if (is_editing) {
            auto this_size = size - ImVec2(0, edit_button_offset);
            auto ed        = get_editor(this_size);
            ed->HandleInput();
            ed->Render();
            IM_FN_PRINT("Render done", "");

            if (IM_FN_EXPR(Button, "done")) {
                value      = ed->GetText();
                is_editing = false;
                return Result::Changed;
            } else if (ImGui::SameLine(); IM_FN_EXPR(Button, "cancel")) {
                is_editing = false;
                return Result::CancelledEditing;
            } else {
                return Result::None;
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
                return Result::StartedEditing;
            } else {
                return Result::None;
            }
        }
    } else {
        if (is_editing) {
            if (ImGui::Button("OK")) {
                value      = edit_buffer;
                is_editing = false;
                return Result::Changed;
            } else if (ImGui::SameLine(0.0f, 0.0f); ImGui::Button("X")) {
                is_editing = false;
                return Result::CancelledEditing;
            } else {
                ImGui::SameLine(0.0f, 0.0f);
                ImGui::SetNextItemWidth(size.x);
                ImGui::InputText(
                    fmt("##{}_edit", id).c_str(), &edit_buffer);
                return Result::None;
            }

        } else {
            IM_FN_STMT(Text, "%s", value.c_str());
            IM_FN_PRINT("Text render", value);
            if (ImGui::IsItemClicked()) {
                is_editing  = true;
                edit_buffer = value;
                return Result::StartedEditing;
            } else {
                return Result::None;
            }
        }
    }
}

int EditableOrgDocGroup::init_root(const sem::SemId<sem::Org>& id) {
    History& current = getCurrentHistory();
    auto     new_ast = current.ast.context.init(id);
    current.ast      = std::move(new_ast);
    int index = current.roots.push_back_idx(current.ast.getRootAdapter());
    add_history(std::move(current));
    return index;
}
