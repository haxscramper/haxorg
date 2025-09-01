#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemAstDiff.hpp>


struct HistoryManager {
    HistoryManager(org::imm::ImmAstContext::Ptr context);
    using AstEdit = org::algo::ImmNodeDiff::AstEdit;

    org::imm::ImmAstContext::Ptr       context;
    hstd::Vec<org::imm::ImmAstVersion> history;
    int                                active = 0;

    int addHistory(org::imm::ImmAstVersion const&);

    /// Set the current version of the document -- this will push a new
    /// history element, so the undo/redo sequence remaints intact.
    int addDocument(std::string const& document);

    org::imm::ImmAdapter getActiveRoot() const {
        return history.at(active).getRootAdapter();
    }

    org::imm::ImmAdapter getRoot(int index) const {
        return history.at(index).getRootAdapter();
    }

    hstd::Vec<AstEdit> getDifference(int lhsVer, int rhsVer) const;
};
