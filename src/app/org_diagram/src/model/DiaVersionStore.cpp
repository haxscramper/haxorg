#include "DiaVersionStore.hpp"

#include <hstd/stdlib/diffs.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <vector>
#include <haxorg/imm/ImmOrgEdit.hpp>
#include <algorithm>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <haxorg/sem/SemOrgTypesFormatter.hpp>

using namespace hstd;
using namespace org;

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
    if (lhsVer == -1) {
        return {DiaEdit{
            .data = DiaEdit::Insert{
                .dstNode  = getDiaRoot(rhsVer),
                .dstIndex = rhsVer,
            }}};
    } else {
        return ::getEdits(getDiaRoot(lhsVer), getDiaRoot(rhsVer), conf);
    }
}

DiaAdapter DiaVersionStore::buildTree(imm::ImmAdapter const& adapter) {
    dia_trees.insert_or_assign(
        adapter.uniq(), FromDocument(dia_context, adapter));
    return dia_trees.at(adapter.uniq());
}

DiaVersionStore::DiaVersionStore(
    imm::ImmAstContext::Ptr       context,
    DiaContext::Ptr               dia_context,
    org::parse::ParseContext::Ptr parse_context)
    : imm_context{context}
    , dia_context{dia_context}
    , parse_context{parse_context} {}

void DiaVersionStore::stepEditForward(
    imm::ImmAstVersion& vEdit,
    const EditCmd&      edit) {
    TRACKED_SCOPE(hstd::fmt("Edit {}", edit));

    hstd::Opt<imm::ImmAdapter> lastInserted;

    auto get_target = [&](EditTarget const& target) -> imm::ImmAdapter {
        if (target.isExisting()) {
            return DiaAdapter{target.getExisting().target, dia_context}
                .getImmAdapter();
        } else {
            return lastInserted.value();
        }
    };

    switch (edit.getKind()) {
        case EditCmd::Kind::RemoveDiaNode: {
            imm::ImmAdapter adapter = get_target(
                edit.getRemoveDiaNode().target);

            hstd::Opt<imm::ImmAdapter> parent = adapter.getParent();
            LOGIC_ASSERTION_CHECK_FMT(
                parent.has_value(),
                "Cannot remove node without parent: the adapter {} "
                "targets node with no parent",
                adapter);

            HSLOG_TRACE("imm-adapter:{} imm-parent:{}", adapter, parent);


            vEdit = vEdit.getEditVersion(
                [&](imm::ImmAstContext::Ptr ctx,
                    imm::ImmAstEditContext& edit)
                    -> imm::ImmAstReplaceGroup {
                    return imm::dropSubnode(
                        parent.value(), adapter.getSelfIndex(), edit);
                });


            break;
        }

        case EditCmd::Kind::UpdateImmOrg: {
            EditCmd::UpdateImmOrg const& upd     = edit.getUpdateImmOrg();
            imm::ImmAdapter              adapter = get_target(upd.target);
            HSLOG_TRACE("imm-adapter:{}", adapter);


            vEdit = vEdit.getEditVersion(
                [&](imm::ImmAstContext::Ptr ctx,
                    imm::ImmAstEditContext& edit)
                    -> imm::ImmAstReplaceGroup {
                    ext::ImmVec<imm::ImmId> stationarySubnodes;

                    imm::switch_node_value(
                        adapter.id, imm_context, [&](auto const& value) {
                            stationarySubnodes = value.subnodes;
                        });

                    imm::ImmId tmpNoSubnodes = imm_context->store->add(
                        upd.value, edit);

                    imm::ImmAstReplaceGroup result;

                    imm::switch_node_value(
                        tmpNoSubnodes, imm_context, [&](auto value) {
                            value.subnodes = stationarySubnodes;

                            imm::ImmId withSubnodes = //
                                imm_context->store->add(value, edit);

                            result = imm::replaceNode(
                                adapter, withSubnodes, edit);
                        });

                    return result;
                });

            break;
        }

        case EditCmd::Kind::MoveDiaNode: {
            EditCmd::MoveDiaNode const& mov    = edit.getMoveDiaNode();
            imm::ImmAdapter             target = get_target(mov.newParent);

            hstd::Vec<imm::ImmAdapter>
                toMove = mov.nodeToMove
                       | rv::transform(
                             [&](EditTarget const& t) -> imm::ImmAdapter {
                                 return get_target(t);
                             })
                       | rs::to<Vec>();

            HSLOG_INFO("node collection to move");
            hstd::log::log_sequential_collection(toMove).as_trace().end();

            vEdit = vEdit.getEditVersion(
                [&](imm::ImmAstContext::Ptr ctx,
                    imm::ImmAstEditContext& edit)
                    -> imm::ImmAstReplaceGroup {
                    imm::ImmAstReplaceGroup result;

                    struct Hasher {
                        std::size_t operator()(
                            imm::ImmAdapter const& it) const {
                            return std::hash<imm::ImmUniqId>{}(it.uniq());
                        }
                    };

                    struct Equator {
                        bool operator()(
                            imm::ImmAdapter const& lhs,
                            imm::ImmAdapter const& rhs) const {
                            return lhs.uniq() == rhs.uniq();
                        }
                    };

                    std::unordered_map<
                        imm::ImmAdapter,
                        hstd::Vec<imm::ImmAdapter>,
                        Hasher,
                        Equator>
                        parentGroup;

                    for (auto const& it : toMove) {
                        parentGroup[it.getParent().value()].push_back(it);
                    }

                    for (auto const& [parent, subnodesToRemove] :
                         parentGroup) {
                        hstd::Vec<int> subnodeIndices;
                        for (auto const& node : subnodesToRemove) {
                            subnodeIndices.push_back(
                                parent->indexOf(node.id));
                        }
                        std::sort(
                            subnodeIndices.begin(), subnodeIndices.end());

                        HSLOG_INFO(
                            "Removing subnodes {} under {}",
                            subnodeIndices,
                            parent);

                        auto tmpSubnodes = hstd::Vec<imm::ImmId>{
                            parent->subnodes.begin(),
                            parent->subnodes.end()};
                        for (int i : subnodeIndices) {
                            tmpSubnodes.erase(tmpSubnodes.begin() + i);
                        }

                        HSLOG_INFO(
                            "New subnodes under {}: {}",
                            parent,
                            tmpSubnodes);

                        result.incl(setSubnodes(
                            parent,
                            ext::ImmVec<imm::ImmId>{
                                tmpSubnodes.begin(), tmpSubnodes.end()},
                            edit));
                    }

                    hstd::Vec<imm::ImmId> movedIds;
                    for (auto const& moved : toMove) {
                        movedIds.push_back(moved.id);
                    }

                    result.incl(
                        imm::insertSubnodes(
                            target,
                            movedIds,
                            mov.newIndex.value_or(target.size()),
                            edit));

                    return result;
                });


            break;
        }

        case EditCmd::Kind::InsertDiaNode: {
            EditCmd::InsertDiaNode const& ins = edit.getInsertDiaNode();
            imm::ImmAdapter adapter           = get_target(ins.newParent);

            HSLOG_TRACE("imm-adapter:{}", adapter);


            vEdit = vEdit.getEditVersion(
                [&](imm::ImmAstContext::Ptr ctx,
                    imm::ImmAstEditContext& edit)
                    -> imm::ImmAstReplaceGroup {
                    imm::ImmId title = imm_context->store->add(
                        imm::ImmParagraph{}, edit);
                    auto subtree       = imm::ImmSubtree{};
                    subtree.title      = title.as<imm::ImmParagraph>();
                    subtree.properties = hstd::ext::ImmVec<
                        sem::NamedProperty>{
                        sem::NamedProperty{
                            sem::NamedProperty::CustomSubtreeJson{
                                .name  = DiaPropertyNames::diagramGeometry,
                                .value = hstd::to_json_eval(
                                    DiaNodeItem::Geometry{})}},
                        sem::NamedProperty{
                            sem::NamedProperty::CustomSubtreeFlags{
                                .name = DiaPropertyNames::isDiagramNode,
                            }},
                    };
                    imm::ImmId addedNode = imm_context->store->add(
                        subtree, edit);

                    return imm::insertSubnode(
                        adapter,
                        addedNode,
                        ins.index.value_or(adapter.size()),
                        edit);
                });

            break;
        }

        default: {
            throw hstd::logic_unhandled_kind_error::init(edit.getKind());
        }
    }

    hstd::ColStream os;
    vEdit.getContext()->store->format(os, "  ");
    HSLOG_TRACE("imm store:\n{}", os.toString(false));

    HSLOG_TRACE(
        "imm version:\n{}",
        hstd::indent(
            vEdit.getRootAdapter().treeRepr().toString(false), 2));
}

DiaVersionStore::EditApplyResult DiaVersionStore::applyDiaEdits(
    const EditGroup& edits) {
    TRACKED_FUNCTION("applyDiaEdits");

    DiaVersionStore::EditApplyResult res;

    auto vEdit = getActiveImmVersion();

    HSLOG_TRACE(
        "dia version:\n{}", getActiveDiaRoot().format().toString(false));

    HSLOG_TRACE(
        "imm version:\n{}",
        vEdit.getRootAdapter().treeRepr().toString(false));

    for (auto const& edit : edits.edits) { stepEditForward(vEdit, edit); }

    addHistory(vEdit);

    HSLOG_TRACE(
        "dia version:\n{}", getActiveDiaRoot().format().toString(false));

    return res;
}

int DiaVersionStore::addHistory(const imm::ImmAstVersion& version) {
    if (active != history.high()) {
        history.erase(history.begin() + active, history.end());
    }

    int oldActive = active;
    active        = history.push_back_idx(version);
    DiaRootChange change;
    change.edits    = getDiaEdits(oldActive, active, DiaEditConf{});
    change.oldIndex = oldActive;
    change.newIndex = active;
    if (oldActive != -1) { change.oldRoot = getDiaRoot(oldActive); }
    change.newRoot = getDiaRoot(active);
    TRACKED_EMIT(diaRootChanged, change);

    hstd::log::log_sequential_collection(change.edits).as_trace().end();


    return active;
}

int DiaVersionStore::addDocument(const std::string& document) {
    auto node    = parse_context->parseString(document, "<text>");
    auto reports = parse_context->collectDiagnostics(node);
    auto cache   = parse_context->getDiagnosticStrings();

    if (!reports.empty()) {
        HSLOG_WARNING("Input document was parsed with diagnostics");
        for (auto const& report : reports) {
            try {
                HSLOG_ERROR("{}", report.to_string(cache, false));
            } catch (std::exception& e) {
                HSLOG_ERROR(
                    "Failed to format report {}\n{}", e.what(), report);
            }
        }
    }


    auto version = imm_context->addRoot(node);
    return addHistory(version);
}

DiaAdapter DiaVersionStore::getDiaRoot(int index) {
    imm::ImmAdapter immAdapter = getImmRoot(index);
    auto            id         = immAdapter.uniq();
    if (!dia_trees.contains(id)) {
        dia_trees.insert_or_assign(
            id,
            FromDocument(dia_context, immAdapter.as<imm::ImmDocument>()));
    }

    return dia_trees.at(id);
}

imm::ImmAstVersion DiaVersionStore::getEditVersion(
    std::function<imm::ImmAstReplaceGroup(
        imm::ImmAstContext::Ptr,
        imm::ImmAstEditContext&)> cb) {
    return getActiveImmVersion().getEditVersion(cb);
}


#include "DiaVersionStore.moc"

DiaVersionStore::EditGroup DiaVersionStore::EditGroup::
    MoveNodesUnderExisting(
        const DiaUniqId&            parent,
        const hstd::Vec<DiaUniqId>& nodes,
        int                         index) {
    hstd::Vec<EditTarget>
        targets = nodes
                | hstd::rv::transform(
                      [](DiaUniqId const& id) -> EditTarget {
                          return EditTarget{
                              EditTarget::Existing{.target = id}};
                      })
                | hstd::rs::to<hstd::Vec>();
    return EditGroup{
        .edits = {EditCmd::Move(
            targets, EditTarget::FromExisting(parent), index)}};
}

DiaVersionStore::EditGroup DiaVersionStore::EditGroup::Append1NewNode(
    const DiaUniqId& id) {
    return EditGroup{
        .edits = {EditCmd::Insert(EditTarget::FromExisting(id))}};
}

DiaVersionStore::EditGroup DiaVersionStore::EditGroup::UpdateExisting(
    DiaUniqId const&            id,
    sem::SemId<sem::Org> const& node) {
    return EditGroup{
        .edits = {EditCmd::Update(EditTarget::FromExisting(id), node)}};
}

DiaVersionStore::EditGroup DiaVersionStore::EditGroup::Create1NewNode(
    const DiaUniqId& id,
    int              index) {
    return EditGroup{
        .edits = {EditCmd::Insert(EditTarget::FromExisting(id), index)}};
}

DiaVersionStore::EditGroup DiaVersionStore::EditGroup::Remove1ExistingNode(
    const DiaUniqId& id) {
    return EditGroup{
        .edits = {EditCmd::Remove(EditTarget::FromExisting(id))}};
}

DiaVersionStore::EditGroup DiaVersionStore::EditGroup::
    Create1NewNodeWithValue(
        const DiaUniqId&            id,
        int                         index,
        const sem::SemId<sem::Org>& value) {
    return EditGroup{
        .edits = {
            EditCmd::Insert(EditTarget::FromExisting(id), index),
            EditCmd::Update(EditTarget::FromLastCreated(), value),
        }};
}

DiaVersionStore::EditGroup DiaVersionStore::EditGroup::
    Append1NewNodeWithValue(
        const DiaUniqId&            id,
        const sem::SemId<sem::Org>& value) {
    return EditGroup{
        .edits = {
            EditCmd::Insert(EditTarget::FromExisting(id)),
            EditCmd::Update(EditTarget::FromLastCreated(), value),
        }};
}
