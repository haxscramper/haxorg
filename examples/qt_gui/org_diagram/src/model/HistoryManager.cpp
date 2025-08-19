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


std::vector<HistoryManager::AstEdit> HistoryManager::topologicalSort(
    const std::vector<AstEdit>& edits,
    bool                        useLhsParent) {
    std::unordered_map<org::imm::ImmUniqId, std::vector<int>> children;
    std::unordered_map<org::imm::ImmUniqId, int>              parentCount;
    std::unordered_set<org::imm::ImmUniqId>                   allNodes;

    for (int i = 0; i < edits.size(); ++i) {
        const auto& edit = edits.at(i);

        org::imm::ImmUniqId nodeId;
        if (edit.isDeleted()) {
            nodeId = edit.getDeleted().id;
        } else if (edit.isAdded()) {
            nodeId = edit.getAdded().id;
        } else if (edit.isChanged()) {
            nodeId = useLhsParent ? edit.getChanged().prev
                                  : edit.getChanged().next;
        }

        allNodes.insert(nodeId);

        hstd::Opt<org::imm::ImmUniqId> parent = useLhsParent
                                                  ? edit.lhsParent
                                                  : edit.rhsParent;

        if (parent.has_value()) {
            allNodes.insert(parent.value());
            children[parent.value()].push_back(i);
            parentCount[nodeId] = parentCount[nodeId] + 1;
        }
    }

    for (const auto& node : allNodes) {
        if (parentCount.find(node) == parentCount.end()) {
            parentCount.insert_or_assign(node, 0);
        }
    }

    std::queue<int> queue;
    for (int i = 0; i < edits.size(); ++i) {
        const auto& edit = edits.at(i);

        org::imm::ImmUniqId nodeId;
        if (edit.isDeleted()) {
            nodeId = edit.getDeleted().id;
        } else if (edit.isAdded()) {
            nodeId = edit.getAdded().id;
        } else if (edit.isChanged()) {
            nodeId = useLhsParent ? edit.getChanged().prev
                                  : edit.getChanged().next;
        }

        if (parentCount.at(nodeId) == 0) { queue.push(i); }
    }

    std::vector<AstEdit>    result;
    std::unordered_set<int> processed;

    while (!queue.empty()) {
        int editIndex = queue.front();
        queue.pop();

        if (processed.find(editIndex) != processed.end()) { continue; }

        processed.insert(editIndex);
        result.push_back(edits.at(editIndex));

        const auto&         edit = edits.at(editIndex);
        org::imm::ImmUniqId nodeId;
        if (edit.isDeleted()) {
            nodeId = edit.getDeleted().id;
        } else if (edit.isAdded()) {
            nodeId = edit.getAdded().id;
        } else if (edit.isChanged()) {
            nodeId = useLhsParent ? edit.getChanged().prev
                                  : edit.getChanged().next;
        }

        if (children.find(nodeId) != children.end()) {
            for (int childEditIndex : children.at(nodeId)) {
                const auto& childEdit = edits.at(childEditIndex);

                org::imm::ImmUniqId childNodeId;
                if (childEdit.isDeleted()) {
                    childNodeId = childEdit.getDeleted().id;
                } else if (childEdit.isAdded()) {
                    childNodeId = childEdit.getAdded().id;
                } else if (childEdit.isChanged()) {
                    childNodeId = useLhsParent
                                    ? childEdit.getChanged().prev
                                    : childEdit.getChanged().next;
                }

                parentCount.insert_or_assign(
                    childNodeId, parentCount.at(childNodeId) - 1);
                if (parentCount.at(childNodeId) == 0) {
                    queue.push(childEditIndex);
                }
            }
        }
    }

    return result;
}
