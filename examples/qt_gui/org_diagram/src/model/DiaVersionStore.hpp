#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemAstDiff.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>
#include <QObject>
#include <hstd/stdlib/Ranges.hpp>

template <>
struct std::formatter<org::imm::ImmOrg*>
    : hstd::std_format_ptr_as_hex<org::imm::ImmOrg> {};

/// \brief Central class to store all versions of the diagram node tree,
/// switch between active versions and generate edit signals.
struct DiaVersionStore
    : public QObject
    , public hstd::SharedPtrApi<DiaVersionStore> {
    Q_OBJECT
  public:
    DiaVersionStore(
        org::imm::ImmAstContext::Ptr context,
        DiaContext::Ptr              dia_context);

    struct EditTarget {
        struct Existing {
            DiaUniqId target;
            DESC_FIELDS(Existing, (target));
        };
        struct LastCreated {
            DESC_FIELDS(LastCreated, ());
        };
        SUB_VARIANTS(Kind, Data, data, getKind, Existing, LastCreated);
        Data data;
        DESC_FIELDS(EditTarget, (data));

        static EditTarget FromExisting(DiaUniqId const& id) {
            return EditTarget{Existing{id}};
        }

        static EditTarget FromLastCreated() {
            return EditTarget{LastCreated{}};
        }
    };

    struct EditCmd {
        struct RemoveDiaNode {
            EditTarget target;
            DESC_FIELDS(RemoveDiaNode, (target));
        };

        struct InsertDiaNode {
            EditTarget     target;
            hstd::Opt<int> index;
            DESC_FIELDS(InsertDiaNode, (target, index));
        };

        struct UpdateImmOrg {
            EditTarget                        target;
            std::shared_ptr<org::imm::ImmOrg> value;
            DESC_FIELDS(UpdateImmOrg, (target, value));
        };

        struct MoveDiaNode {
            hstd::Vec<EditTarget> nodeToMove;
            EditTarget            newParent;
            std::optional<int>    newIndex;
            DESC_FIELDS(MoveDiaNode, (nodeToMove, newParent, newIndex));
        };

        static EditCmd Remove(EditTarget const& target) {
            return EditCmd{RemoveDiaNode{target}};
        }

        static EditCmd Update(
            EditTarget const&            target,
            hstd::SPtr<org::imm::ImmOrg> value) {
            return EditCmd{UpdateImmOrg{.target = target, .value = value}};
        }

        static EditCmd Insert(
            EditTarget const&     target,
            hstd::Opt<int> const& index = std::nullopt) {
            return EditCmd{
                InsertDiaNode{.target = target, .index = index}};
        }

        static EditCmd Move(
            hstd::Vec<EditTarget>     nodeToMove,
            EditTarget                newParent,
            std::optional<int> const& newIndex = std::nullopt) {
            return EditCmd{EditCmd::MoveDiaNode{
                .nodeToMove = nodeToMove,
                .newParent  = newParent,
                .newIndex   = newIndex,
            }};
        }

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            RemoveDiaNode,
            InsertDiaNode,
            UpdateImmOrg,
            MoveDiaNode);

        Data data;
        DESC_FIELDS(EditCmd, (data));
    };

    struct EditGroup {
        hstd::Vec<EditCmd> edits;
        DESC_FIELDS(EditGroup, (edits));

        static EditGroup Remove1ExistingNode(DiaUniqId const& id);
        static EditGroup Create1NewNode(DiaUniqId const& id, int index);
        static EditGroup Append1NewNode(DiaUniqId const& id);
        static EditGroup Create1NewNodeWithValue(
            DiaUniqId const&                    id,
            int                                 index,
            hstd::SPtr<org::imm::ImmOrg> const& initialValue);
        static EditGroup Append1NewNodeWithValue(
            DiaUniqId const&                    id,
            hstd::SPtr<org::imm::ImmOrg> const& initialValue);
        static EditGroup MoveNodesUnderExisting(
            DiaUniqId const&            parent,
            hstd::Vec<DiaUniqId> const& nodes,
            int                         index);
    };

    struct EditApplyResult {
        DESC_FIELDS(EditApplyResult, ());
    };

    EditApplyResult applyDiaEdits(EditGroup const& edits);
    void            stepEditForward(
                   org::imm::ImmAstVersion& vEdit,
                   EditCmd const&           edit);

    org::imm::ImmAstContext::Ptr                        imm_context;
    DiaContext::Ptr                                     dia_context;
    hstd::Vec<org::imm::ImmAstVersion>                  history;
    int                                                 active = 0;
    hstd::UnorderedMap<org::imm::ImmUniqId, DiaAdapter> dia_trees;

    org::imm::ImmAstVersion getEditVersion(
        std::function<org::imm::ImmAstReplaceGroup(
            org::imm::ImmAstContext::Ptr,
            org::imm::ImmAstEditContext&)> cb);

    DiaAdapter buildTree(org::imm::ImmAdapter const& adapter);

    org::imm::ImmAstVersion getActiveImmVersion() const {
        return history.at(active);
    }

    int addHistory(org::imm::ImmAstVersion const&);

    /// Set the current version of the document -- this will push a new
    /// history element, so the undo/redo sequence remaints intact.
    int addDocument(std::string const& document);

    org::imm::ImmAdapter getActiveImmRoot() const {
        return history.at(active).getRootAdapter();
    }

    org::imm::ImmAdapter getImmRoot(int index) const {
        return history.at(index).getRootAdapter();
    }

    DiaAdapter getActiveDiaRoot() { return getDiaRoot(active); }

    DiaAdapter getDiaRoot(int index);

    struct DiaRootChange {
        hstd::Vec<DiaEdit> edits;
        DiaAdapter         newRoot;
        DiaAdapter         oldRoot;
        int                newIndex;
        int                oldIndex;
        DESC_FIELDS(
            DiaRootChange,
            (edits, newRoot, oldRoot, newIndex, oldIndex));
    };


    hstd::Vec<DiaEdit> getDiaEdits(
        int                lhsVer,
        int                rhsVer,
        const DiaEditConf& conf);

  signals:
    void diaRootChanged(DiaRootChange const& change);
};

Q_DECLARE_METATYPE(DiaVersionStore::EditTarget);
Q_DECLARE_METATYPE(DiaVersionStore::EditCmd);
Q_DECLARE_METATYPE(DiaVersionStore::EditGroup);
Q_DECLARE_METATYPE(DiaVersionStore::EditApplyResult);
Q_DECLARE_METATYPE(DiaVersionStore::DiaRootChange);
