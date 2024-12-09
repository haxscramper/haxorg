#pragma once

#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/system/reflection.hpp>
#include <imgui/imgui.h>

struct EditableOrgText {
    std::string value;
    std::string edit_buffer;
    bool        is_editing = false;

    DESC_FIELDS(EditableOrgText, (value, edit_buffer, is_editing));

    std::string getFinalValue() const {
        if (is_editing) {
            return edit_buffer;
        } else {
            return value;
        }
    }

    DECL_DESCRIBED_ENUM(Mode, Multiline, SingleLine);

    DECL_DESCRIBED_ENUM(
        Result,
        None,
        Changed,
        StartedEditing,
        CancelledEditing);

    static EditableOrgText from_adapter(org::ImmAdapter const it);

    int get_expected_height(int width, Mode mode);

    Result render(
        ImVec2 const&         size,
        EditableOrgText::Mode edit,
        std::string const&    id);
};

struct EditableOrgDocGroup {
    struct History {
        org::ImmAstVersion   ast;
        Vec<org::ImmAdapter> roots;
        DESC_FIELDS(History, (ast, roots));
    };

    int init_root(sem::SemId<sem::Org> const& id) {
        History current = getCurrentHistory();
        auto    new_ast = current.ast.context.init(id);
        current.ast     = new_ast;
        int index = current.roots.push_back_idx(new_ast.getRootAdapter());
        add_history(current);
        return index;
    }

    void add_history(History const& h) { history.push_back(h); }

    Vec<History> history;

    DESC_FIELDS(EditableOrgDocGroup, (history));

    History const&     getCurrentHistory() { return history.back(); }
    org::ImmAstVersion getCurrentAst() { return history.back().ast; }
    org::ImmAdapter    getCurrentRoot(int index) {
        return history.back().roots.at(index);
    }
};
