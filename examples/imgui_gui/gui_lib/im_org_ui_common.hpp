#pragma once

#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/system/reflection.hpp>

struct EditableOrgText {
    std::string text;
    std::string edit_buffer;
    bool        is_editing = false;

    DECL_DESCRIBED_ENUM(Mode, Multiline, SingleLine);

    DECL_DESCRIBED_ENUM(
        Result,
        None,
        Changed,
        StartedEditing,
        CancelledEditing);

    static EditableOrgText from_adapter(org::ImmAdapter const it);
    Result render(ImVec2 const& size);
};
