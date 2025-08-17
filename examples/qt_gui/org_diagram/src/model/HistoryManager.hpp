#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <haxorg/sem/ImmOrg.hpp>


struct HistoryManager {
    struct AstEdit {
        struct Deleted {
            org::imm::ImmUniqId id;
            DESC_FIELDS(Deleted, (id));
        };
        struct Added {
            org::imm::ImmUniqId id;
            DESC_FIELDS(Added, (id));
        };
        struct Changed {
            org::imm::ImmUniqId prev;
            org::imm::ImmUniqId next;
            DESC_FIELDS(Changed, (prev, next));
        };

        SUB_VARIANTS(Kind, Data, data, getKind, Deleted, Added, Changed);
        Data data;
        /// \brief Parent node for the edit operations.
        hstd::Opt<org::imm::ImmUniqId> lhsParent;
        hstd::Opt<org::imm::ImmUniqId> rhsParent;
        DESC_FIELDS(AstEdit, (data, lhsParent, rhsParent));
    };

    static std::vector<AstEdit> topologicalSort(
        const std::vector<AstEdit>& edits,
        bool                        useLhsParent);

    HistoryManager();

    org::imm::ImmAstContext::Ptr       context;
    hstd::Vec<org::imm::ImmAstVersion> history;
    int                                active = 0;

    void addHistory(org::imm::ImmAstVersion const&);

    /// Set the current version of the document -- this will push a new
    /// history element, so the undo/redo sequence remaints intact.
    void setDocument(std::string const& document);

    org::imm::ImmAdapter getActiveRoot() const {
        return history.at(active).getRootAdapter();
    }

    org::imm::ImmAdapter getRoot(int index) const {
        return history.at(index).getRootAdapter();
    }

    hstd::Vec<AstEdit> getDifference(int lhsVer, int rhsVer) const;
};
