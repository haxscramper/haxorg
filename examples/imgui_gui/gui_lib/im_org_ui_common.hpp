#pragma once
#define NDEBUG 0

#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/system/reflection.hpp>
#include <imgui/imgui.h>

/// \brief Store current value of the editable text and the current edit
/// buffer.
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

    static EditableOrgText from_adapter(org::ImmAdapter const& it);

    int get_expected_height(int width, Mode mode);

    /// \brief Render editable text widget at the current position using
    /// provided size and edit mode. Edit state and buffer are stored in
    /// the object.
    Result render(
        ImVec2 const&         size,
        EditableOrgText::Mode edit,
        std::string const&    id);
};

/// \brief Wrap editable text with information about size and edit mode
struct EditableOrgTextEntry {
    EditableOrgText text;
    /// \brief Text width is set as parameter
    int                   assignedWidth;
    EditableOrgText::Mode mode;

    /// \brief Text height is computed based off the current width and the
    /// text.
    int computedHeight;

    DESC_FIELDS(
        EditableOrgTextEntry,
        (text, mode, assignedWidth, computedHeight));

    static EditableOrgTextEntry from_adapter(
        org::ImmAdapter const& it,
        int                    width,
        EditableOrgText::Mode  mode = EditableOrgText::Mode::Multiline) {
        EditableOrgTextEntry result{
            .text = EditableOrgText::from_adapter(it)};
        result.setWidth(width);
        result.mode = mode;
        return result;
    }

    std::string getFinalValue() const { return text.getFinalValue(); }

    int    getHeight() const { return computedHeight; }
    int    getWidth() const { return assignedWidth; }
    ImVec2 getSize() const {
        return ImVec2(assignedWidth, computedHeight);
    }

    void setWidth(int width) {
        assignedWidth = width;
        syncHeight();
    }

    void syncHeight() {
        computedHeight = text.get_expected_height(assignedWidth, mode);
    }

    EditableOrgText::Result render(std::string const& id) {
        return text.render(getSize(), mode, id);
    }
};

struct EditableOrgDocGroup {
    struct History {
        org::ImmAstVersion   ast;
        Vec<org::ImmAdapter> roots;
        DESC_FIELDS(History, (ast, roots));
    };

    EditableOrgDocGroup() { add_history(History{org::ImmAstContext{}}); }

    int init_root(sem::SemId<sem::Org> const& id);

    void add_history(History const& h) { history.push_back(h); }

    Vec<History> history;

    DESC_FIELDS(EditableOrgDocGroup, (history));

    History&           getCurrentHistory() { return history.back(); }
    History const&     getCurrentHistory() const { return history.back(); }
    org::ImmAstVersion getCurrentAst() { return history.back().ast; }
    org::ImmAdapter    getCurrentRoot(int index) {
        return history.back().roots.at(index);
    }
};
