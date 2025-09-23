#include "DiaContextStore.hpp"

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

std::vector<DiaEdit> DiaContextStore::getDiaEdits(
    int                lhsVer,
    int                rhsVer,
    DiaEditConf const& conf) const {
    return ::getEdits(getDiaRoot(lhsVer), getDiaRoot(rhsVer), conf);
}

DiaContextStore::DiaContextStore(
    org::imm::ImmAstContext::Ptr context,
    DiaContext::Ptr              dia_context)
    : imm_context{context}, dia_context{dia_context} {}

DiaContextStore::EditApplyResult DiaContextStore::applyDiaEdits(
    const EditGroup& edits) {

    DiaContextStore::EditApplyResult res;

    return res;
}

int DiaContextStore::addHistory(const org::imm::ImmAstVersion& version) {
    if (active != history.high()) {
        history.erase(history.begin() + active, history.end());
    }

    active = history.push_back_idx(version);
    return active;
}

int DiaContextStore::addDocument(const std::string& document) {
    auto version = imm_context->addRoot(org::parseString(document));
    return addHistory(version);
}


#include "DiaContextStore.moc"
