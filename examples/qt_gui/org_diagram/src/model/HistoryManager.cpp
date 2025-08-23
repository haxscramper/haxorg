#include "HistoryManager.hpp"

#include <hstd/stdlib/diffs.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace hstd;

struct SeqEditPairs {
    Vec<Pair<SeqEdit, SeqEdit>> matched;
    Vec<SeqEdit>                remaining;
};

SeqEditPairs extractDeleteInsertPairs(const Vec<SeqEdit>& edits) {
    SeqEditPairs result{};
    Vec<int>     used(edits.size(), false);

    for (int i = 0; i < edits.size(); ++i) {
        if (used.at(i) || edits.at(i).kind != SeqEditKind::Delete) {
            continue;
        }

        for (int j = i + 1; j < edits.size(); ++j) {
            if (used.at(j) || edits.at(j).kind != SeqEditKind::Insert) {
                continue;
            }

            if (edits.at(i).sourcePos == edits.at(j).targetPos) {
                result.matched.push_back({edits.at(i), edits.at(j)});
                used.at(i) = true;
                used.at(j) = true;
                break;
            }
        }
    }

    for (int i = 0; i < edits.size(); ++i) {
        if (!used.at(i)) { result.remaining.push_back(edits.at(i)); }
    }

    return result;
}

hstd::Vec<HistoryManager::AstEdit> HistoryManager::getDifference(
    int lhsVer,
    int rhsVer) const {
    hstd::Vec<AstEdit> result;

    // temporary placeholder -- registers a complete AST change between to
    // AST trees.
    result.push_back(AstEdit{AstEdit::Deleted{
        .id = getRoot(lhsVer).uniq(),
    }});

    result.push_back(AstEdit{AstEdit::Added{
        .id = getRoot(rhsVer).uniq(),
    }});

    return result;
}

HistoryManager::HistoryManager() {
    context = org::imm::ImmAstContext::init_start_context();
}

void HistoryManager::addHistory(const org::imm::ImmAstVersion& version) {
    if (active != history.high()) {
        history.erase(history.begin() + active, history.end());
    }

    active = history.push_back_idx(version);
}

void HistoryManager::setDocument(const std::string& document) {
    auto version = context->addRoot(org::parseString(document));
    addHistory(version);
}
