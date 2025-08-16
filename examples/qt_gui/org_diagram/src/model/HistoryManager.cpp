#include "HistoryManager.hpp"

#include <hstd/stdlib/diffs.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Debug.hpp>

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
    std::function<void(
        org::imm::ImmAdapter const&,
        org::imm::ImmAdapter const&,
        hstd::Opt<org::imm::ImmUniqId> const&,
        hstd::Opt<org::imm::ImmUniqId> const&)>
        aux;

    aux = [&](org::imm::ImmAdapter const&           lhs,
              org::imm::ImmAdapter const&           rhs,
              hstd::Opt<org::imm::ImmUniqId> const& lhsParent,
              hstd::Opt<org::imm::ImmUniqId> const& rhsParent) {
        if (lhs.id == rhs.id) {
            return;
        } else {
            // Sub-fields are not considered for the AST diff for the
            // diagram structure -- the node fields are considered a part
            // of the diagram node, so they are not used for recursion.
            result.push_back(AstEdit{
                .data      = AstEdit::Changed{lhs.uniq(), rhs.uniq()},
                .lhsParent = lhsParent,
                .rhsParent = rhsParent,
            });

            _dfmt("Changed", lhs, rhs);
            if (lhs.size() != 0 || rhs.size() != 0) {

                hstd::Vec<org::imm::ImmAdapter> lhsSubnodes = lhs.sub();
                hstd::Vec<org::imm::ImmAdapter> rhsSubnodes = rhs.sub();

                auto diff = hstd::myersDiffCbCmp<org::imm::ImmAdapter>(
                    lhsSubnodes,
                    rhsSubnodes,
                    [](org::imm::ImmAdapter const& lhs,
                       org::imm::ImmAdapter const& rhs) -> bool {
                        return lhs.id == rhs.id;
                    });

                auto pairs = extractDeleteInsertPairs(diff);

                for (auto const& [lhsEdit, rhsEdit] : pairs.matched) {
                    aux(lhsSubnodes.at(lhsEdit.sourcePos),
                        rhsSubnodes.at(rhsEdit.targetPos),
                        lhs.uniq(),
                        rhs.uniq());
                }

                for (auto const& it : pairs.remaining) {
                    if (it.kind == hstd::SeqEditKind::Delete) {
                        result.push_back(AstEdit{
                            .data      = AstEdit::Deleted{lhsSubnodes
                                                         .at(it.sourcePos)
                                                         .uniq()},
                            .lhsParent = lhsParent,
                            .rhsParent = rhsParent,
                        });
                    } else if (it.kind == hstd::SeqEditKind::Insert) {
                        result.push_back(AstEdit{
                            .data      = AstEdit::Added{rhsSubnodes
                                                       .at(it.targetPos)
                                                       .uniq()},
                            .lhsParent = lhsParent,
                            .rhsParent = rhsParent,
                        });
                    } else if (it.kind == hstd::SeqEditKind::Replace) {
                        aux(lhsSubnodes.at(it.sourcePos),
                            rhsSubnodes.at(it.targetPos),
                            lhs.uniq(),
                            rhs.uniq());
                    } else if (it.kind == hstd::SeqEditKind::Keep) {
                        // pass
                    } else {
                        logic_todo_impl();
                    }
                }
            }
        }
    };

    aux(getRoot(lhsVer), getRoot(rhsVer), std::nullopt, std::nullopt);

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
