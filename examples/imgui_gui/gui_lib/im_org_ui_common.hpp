#pragma once
#include "gui_lib/imgui_utils.hpp"
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

template <>
struct std::formatter<org::ImmAstVersion*>
    : std_format_ptr_as_hex<org::ImmAstVersion> {};

struct EditableOrgDocGroup {
    struct RootGroup {
        Vec<DocRootId> roots;
        int            historyIndex = 0;
        DESC_FIELDS(RootGroup, (roots, historyIndex));

        int getHistoryIndex() const { return historyIndex; }

        void add(DocRootId id);

        RootGroup() {}
        RootGroup(int history, Vec<DocRootId> roots);
    };

    struct History {
        SPtr<org::ImmAstVersion> ast;
        ImmVec<org::ImmUniqId>   roots;
        UnorderedMap<int, int>   transition;
        DESC_FIELDS(History, (ast, roots, transition));

        Opt<int> getTransition(int rootIdx) const {
            return transition.get(rootIdx);
        }

        org::ImmAdapter getNewRoot(org::ImmAdapter const& oldRoot) {
            auto mapped = ast->epoch.replaced.map.get(oldRoot.uniq());
            if (mapped) {
                return ast->context->adapt(mapped.value());
            } else {
                return oldRoot;
            }
        }

        History withNewVersion(org::ImmAstVersion const& updated) const;
        Pair<History, int> addRoot(sem::SemId<sem::Org> const& root) const;

        History() {}
        History(org::ImmAstContext::Ptr const& ctx)
            : ast{std::make_shared<org::ImmAstVersion>()} {
            ast->context = ctx;
        }

        org::ImmAdapter getRoot(int index) const {
            return ast->context->adapt(roots.at(index));
        }
    };

    Vec<History> history;

    EditableOrgDocGroup(org::ImmAstContext::Ptr const& ctx) {
        addHistory(History{ctx});
    }

    DocRootId resetWith(sem::SemId<sem::Org> const& id) {
        history.clear();
        return addRoot(id);
    }

    DocRootId addRoot(sem::SemId<sem::Org> const& id);

    int addHistory(History const& h) { return history.push_back_idx(h); }
    Opt<int> extendHistory(org::ImmAstVersion const& ast) {
        if (ast.epoch.replaced.map.empty()) {
            return std::nullopt;
        } else {
            return addHistory(getCurrentHistory().withNewVersion(ast));
        }
    }


    DESC_FIELDS(EditableOrgDocGroup, (history));

    bool isLatest(DocRootId const& id) const {
        return id.getMask() == history.high();
    }

    DocRootId               getLatest(DocRootId id) const;
    org::ImmAstContext::Ptr getContext() const {
        return getCurrentHistory().ast->context;
    }
    History&       getCurrentHistory() { return history.back(); }
    History const& getCurrentHistory() const { return history.back(); }
    Vec<org::ImmAdapter> getAdapters(RootGroup const& ids) const {
        Vec<org::ImmAdapter> res;
        for (auto const& id : ids.roots) { res.push_back(getRoot(id)); }
        return res;
    }

    Opt<RootGroup> migrate(
        RootGroup prev,
        Opt<int>  maxVersion = std::nullopt) const;

    org::ImmAdapter getRoot(DocRootId id) const {
        return history.at(id.getMask()).getRoot(id.getIndex());
    }

    org::ImmAdapter getCurrentRoot(DocRootId id) const {
        LOGIC_ASSERTION_CHECK(
            isLatest(id),
            "Provided doc root ID {} does not come from the latest "
            "history.",
            id);
        return history.back().getRoot(id.getIndex());
    }

    [[nodiscard]] org::ImmAstVersion replaceNode(
        org::ImmAdapter const&    origin,
        Vec<sem::SemId<sem::Org>> replace);

    [[nodiscard]] org::ImmAstVersion replaceNode(
        org::ImmAdapter const& origin,
        std::string const&     text);
};
