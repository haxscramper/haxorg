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
