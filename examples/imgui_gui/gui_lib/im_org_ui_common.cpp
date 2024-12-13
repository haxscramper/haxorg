#include "im_org_ui_common.hpp"
#include <gui_lib/imgui_utils.hpp>
#include <gui_lib/scintilla_editor_widget.hpp>
#include "misc/cpp/imgui_stdlib.h"
#include <haxorg/sem/ImmOrgEdit.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>


EditableOrgText EditableOrgText::from_adapter(const org::ImmAdapter& it) {
    EditableOrgText      res;
    sem::SemId<sem::Org> sem_ast = org::sem_from_immer(
        it.id, *it.ctx.lock());
    res.value  = sem::Formatter::format(sem_ast);
    res.origin = it;
    return res;
}

namespace {
int edit_button_offset = 40;

org_logging::log_builder gr_log(
    org_logging::severity_level __severity,
    int                         line     = __builtin_LINE(),
    char const*                 function = __builtin_FUNCTION(),
    char const*                 file     = __builtin_FILE()) {
    return std::move(::org_logging::log_builder{}
                         .set_callsite(line, function, file)
                         .severity(__severity)
                         .source_scope({"gui", "logic", "shared"}));
}
} // namespace


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
    auto     new_ast = current.ast.context->init(id);
    current.ast      = std::move(new_ast);
    int index = current.roots.push_back_idx(current.ast.getRootAdapter());
    add_history(std::move(current));
    return index;
}

org::ImmAstVersion EditableOrgDocGroup::replace_node(
    const org::ImmAdapter&    origin,
    Vec<sem::SemId<sem::Org>> replace) {
    // gr_log(ol_trace).message(origin.treeRepr().toString(false));
    LOGIC_ASSERTION_CHECK(!origin.isNil(), "Cannot replace nil node");
    org::ImmAstVersion vNext = getCurrentAst().getEditVersion(
        [&](org::ImmAstContext::Ptr ast,
            org::ImmAstEditContext& ast_ctx) -> org::ImmAstReplaceGroup {
            org::ImmAstReplaceGroup result;

            if (replace.size() == 1) {
                auto id = ast->add(replace.at(0), ast_ctx);
                if (id != origin.id) {
                    result.incl(org::replaceNode(origin, id, ast_ctx));
                } else {
                    gr_log(ol_info).fmt_message(
                        "Original node {} has the same ID as replacement "
                        "target {} == {}",
                        origin,
                        origin.id,
                        id);

                    gr_log(ol_trace).message(
                        origin.treeRepr().toString(false));
                }
            } else {
                auto opt_parent = origin.getParent();
                LOGIC_ASSERTION_CHECK(
                    opt_parent.has_value(),
                    "Attempting to replace origin node {} with {} items, "
                    "but the origin node does not have a proper parent.",
                    origin,
                    replace.size());

                auto parent = opt_parent.value();
                LOGIC_ASSERTION_CHECK(
                    parent.isDirectParentOf(origin),
                    "Origin node is {}, computed parent is {}",
                    origin,
                    parent);

                int index = origin.getSelfIndex();


                LOGIC_ASSERTION_CHECK(
                    index != -1,
                    "Failed to compute self-index for origin node {}",
                    origin);


                Vec<org::ImmId> new_nodes;

                for (int i = 0; i < index; ++i) {
                    new_nodes.push_back(parent.at(i).id);
                }

                for (auto const& it : replace) {
                    new_nodes.push_back(ast->add(it, ast_ctx));
                }

                for (int i = index + 1; i < parent.size(); ++i) {
                    new_nodes.push_back(parent.at(i).id);
                }

                result.incl(org::setSubnodes(
                    parent,
                    {new_nodes.begin(), new_nodes.end()},
                    ast_ctx));
            }


            return result;
        });

    return vNext;
}

org::ImmAstVersion EditableOrgDocGroup::replace_node(
    const org::ImmAdapter& origin,
    const std::string&     text) {
    auto parse = sem::parseString(text);
    if (parse->is(OrgSemKind::Document)
        || parse->is(OrgSemKind::StmtList)) {
        return replace_node(
            origin, Vec<sem::SemId<sem::Org>>{parse.begin(), parse.end()});
    } else {
        return replace_node(origin, Vec<sem::SemId<sem::Org>>{parse});
    }
}


EditableOrgDocGroup::History EditableOrgDocGroup::History::withNewVersion(
    const org::ImmAstVersion& updated) {
    History res;
    res.ast = updated;

    for (auto const& root : roots) {
        auto id = root.uniq();
        if (auto root1 = updated.epoch.replaced.map.get(id)) {
            res.roots.push_back(updated.context->adapt(root1.value()));
        } else {
            res.roots.push_back(root);
        }
    }


    return res;
}
