#pragma once
#define NDEBUG 0

#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/system/reflection.hpp>
#include <imgui/imgui.h>

/// \brief Store current value of the editable text and the current edit
/// buffer.
struct EditableOrgText {
    std::string     value;
    std::string     edit_buffer;
    bool            is_editing = false;
    org::ImmAdapter origin;

    DESC_FIELDS(EditableOrgText, (value, edit_buffer, is_editing, origin));

    std::string getFinalValue() const {
        if (is_editing) {
            return edit_buffer;
        } else {
            return value;
        }
    }

    DECL_DESCRIBED_ENUM(Mode, Multiline, SingleLine);


    struct Result {
        DECL_DESCRIBED_ENUM(
            Kind,
            Changed,
            StartedEditing,
            CancelledEditing);
        Kind             kind;
        org::ImmAdapter  origin;
        Opt<std::string> value;

        DESC_FIELDS(Result, (kind, origin, value));

        bool isChanged() const { return kind == Kind::Changed; }
        bool isStartedEditing() const {
            return kind == Kind::StartedEditing;
        }
        bool isCancelledEditing() const {
            return kind == Kind::CancelledEditing;
        }
    };

    static EditableOrgText from_adapter(org::ImmAdapter const& it);

    int get_expected_height(int width, Mode mode);

    /// \brief Render editable text widget at the current position using
    /// provided size and edit mode. Edit state and buffer are stored in
    /// the object.
    Opt<Result> render(
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

    std::string     getFinalValue() const { return text.getFinalValue(); }
    org::ImmAdapter getOrigin() const { return text.origin; }

    int    getHeight() const;
    int    getWidth() const { return assignedWidth; }
    ImVec2 getSize() const { return ImVec2(getWidth(), getHeight()); }
    bool   isEditing() const { return text.is_editing; }

    void setWidth(int width) {
        assignedWidth = width;
        syncHeight();
    }

    void syncHeight() {
        computedHeight = text.get_expected_height(assignedWidth, mode);
    }

    Opt<EditableOrgText::Result> render(std::string const& id) {
        return text.render(getSize(), mode, id);
    }
};

DECL_ID_TYPE_MASKED(___RootId, DocRootId, u64, 32);

struct EditableOrgDocGroup {
    struct History {
        org::ImmAstVersion   ast;
        Vec<org::ImmAdapter> roots;
        DESC_FIELDS(History, (ast, roots));

        org::ImmAdapter getNewRoot(org::ImmAdapter const& oldRoot) {
            auto mapped = ast.epoch.replaced.map.get(oldRoot.uniq());
            if (mapped) {
                return ast.context->adapt(mapped.value());
            } else {
                return oldRoot;
            }
        }

        History withNewVersion(org::ImmAstVersion const& updated);
    };

    EditableOrgDocGroup(org::ImmAstContext::Ptr const& ctx) {
        addHistory(History{org::ImmAstVersion{.context = ctx}});
    }

    DocRootId resetWith(sem::SemId<sem::Org> const& id) {
        history.clear();
        return initRoot(id);
    }

    DocRootId initRoot(sem::SemId<sem::Org> const& id);

    int addHistory(History const& h) { return history.push_back_idx(h); }
    Opt<int> extendHistory(org::ImmAstVersion const& ast) {
        if (ast.epoch.replaced.map.empty()) {
            return std::nullopt;
        } else {
            return addHistory(getCurrentHistory().withNewVersion(ast));
        }
    }

    Vec<History> history;

    DESC_FIELDS(EditableOrgDocGroup, (history));

    bool isLatest(DocRootId const& id) const {
        return id.getMask() == history.high();
    }

    DocRootId          getLatest(DocRootId id) const;
    History&           getCurrentHistory() { return history.back(); }
    History const&     getCurrentHistory() const { return history.back(); }
    org::ImmAstVersion getCurrentAst() { return history.back().ast; }
    Vec<org::ImmAdapter> getAdapters(Vec<DocRootId> const& ids) const {
        Vec<org::ImmAdapter> res;
        for (auto const& id : ids) { res.push_back(getRoot(id)); }
        return res;
    }

    org::ImmAdapter getRoot(DocRootId id) const {
        return history.at(id.getMask()).roots.at(id.getIndex());
    }

    org::ImmAdapter getCurrentRoot(DocRootId id) const {
        LOGIC_ASSERTION_CHECK(
            isLatest(id),
            "Provided doc root ID {} does not come from the latest "
            "history.",
            id);
        return history.back().roots.at(id.getIndex());
    }

    [[nodiscard]] org::ImmAstVersion replaceNode(
        org::ImmAdapter const&    origin,
        Vec<sem::SemId<sem::Org>> replace);

    [[nodiscard]] org::ImmAstVersion replace_node(
        org::ImmAdapter const& origin,
        std::string const&     text);
};
