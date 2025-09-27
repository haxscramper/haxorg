#include "DiaVersionStore.hpp"

#include <hstd/stdlib/diffs.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <vector>
#include <haxorg/sem/ImmOrgEdit.hpp>

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

hstd::Vec<DiaEdit> DiaVersionStore::getDiaEdits(
    int                lhsVer,
    int                rhsVer,
    DiaEditConf const& conf) {
    return ::getEdits(getDiaRoot(lhsVer), getDiaRoot(rhsVer), conf);
}

DiaAdapter DiaVersionStore::buildTree(
    org::imm::ImmAdapter const& adapter) {
    dia_trees.insert_or_assign(
        adapter.uniq(), FromDocument(dia_context, adapter));
    return dia_trees.at(adapter.uniq());
}

DiaVersionStore::DiaVersionStore(
    org::imm::ImmAstContext::Ptr context,
    DiaContext::Ptr              dia_context)
    : imm_context{context}, dia_context{dia_context} {}

void DiaVersionStore::stepEditForward(
    org::imm::ImmAstVersion& vEdit,
    const EditCmd&           edit) {
    TRACKED_SCOPE(hstd::fmt("Edit {}", edit));

    auto get_target = [&](EditTarget const& target) -> DiaAdapter {
        if (target.isExisting()) {
            return DiaAdapter{target.getExisting().target, dia_context};
        } else {
            logic_todo_impl();
        }
    };

    switch (edit.getKind()) {
        case EditCmd::Kind::RemoveDiaNode: {
            DiaAdapter adapter = get_target(
                edit.getRemoveDiaNode().target);

            hstd::Opt<DiaAdapter> parent = adapter.getParent();
            LOGIC_ASSERTION_CHECK(
                parent.has_value(),
                "Cannot remove node without parent: the adapter {} "
                "targets node with no parent",
                adapter);

            HSLOG_TRACE(
                _cat, hstd::fmt("adapter:{} parent:{}", adapter, parent));
            HSLOG_TRACE(
                _cat,
                hstd::fmt(
                    "imm-adapter:{} imm-parent:{}",
                    adapter.getImmAdapter(),
                    parent->getImmAdapter()));

            vEdit = vEdit.getEditVersion(
                [&](org::imm::ImmAstContext::Ptr ctx,
                    org::imm::ImmAstEditContext& edit)
                    -> org::imm::ImmAstReplaceGroup {
                    return org::imm::dropSubnode(
                        parent->getImmAdapter(),
                        adapter.getSelfIndex(),
                        edit);
                });

            HSLOG_TRACE(
                _cat,
                hstd::fmt(
                    "imm version:\n{}",
                    vEdit.getRootAdapter().treeRepr().toString(false)));


            break;
        }

        default: {
        }
    }
}

DiaVersionStore::EditApplyResult DiaVersionStore::applyDiaEdits(
    const EditGroup& edits) {
    TRACKED_FUNCTION("applyDiaEdits");

    DiaVersionStore::EditApplyResult res;

    auto vEdit = getActiveImmVersion();

    HSLOG_TRACE(
        _cat,
        hstd::fmt(
            "dia version:\n{}",
            getActiveDiaRoot().format().toString(false)));

    HSLOG_TRACE(
        _cat,
        hstd::fmt(
            "imm version:\n{}",
            vEdit.getRootAdapter().treeRepr().toString(false)));

    for (auto const& edit : edits.edits) { stepEditForward(vEdit, edit); }

    addHistory(vEdit);

    HSLOG_TRACE(
        _cat,
        hstd::fmt(
            "dia version:\n{}",
            getActiveDiaRoot().format().toString(false)));

    return res;
}

int DiaVersionStore::addHistory(const org::imm::ImmAstVersion& version) {
    if (active != history.high()) {
        history.erase(history.begin() + active, history.end());
    }

    int oldActive = active;
    active        = history.push_back_idx(version);
    DiaRootChange change;
    change.edits    = getDiaEdits(oldActive, active, DiaEditConf{});
    change.oldIndex = oldActive;
    change.newIndex = active;
    change.oldRoot  = getDiaRoot(oldActive);
    change.newRoot  = getDiaRoot(active);
    TRACKED_EMIT(diaRootChanged, change);

    log_collection(_cat, hstd::log::severity_level::trace, change.edits)
        .end();


    return active;
}

int DiaVersionStore::addDocument(const std::string& document) {
    auto version = imm_context->addRoot(org::parseString(document));
    return addHistory(version);
}

org::imm::ImmAstVersion DiaVersionStore::getEditVersion(
    std::function<org::imm::ImmAstReplaceGroup(
        org::imm::ImmAstContext::Ptr,
        org::imm::ImmAstEditContext&)> cb) {
    return getActiveImmVersion().getEditVersion(cb);
}


#include "DiaVersionStore.moc"
