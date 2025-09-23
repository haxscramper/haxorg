#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemAstDiff.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>
#include <QObject>

/// \brief Central class to store all versions of the diagram node tree,
/// switch between active versions and generate edit signals.
struct DiaContextStore
    : public QObject
    , public hstd::SharedPtrApi<DiaContextStore> {
    Q_OBJECT
  public:
    DiaContextStore(
        org::imm::ImmAstContext::Ptr context,
        DiaContext::Ptr              dia_context);

    struct EditTarget {
        struct Existing {
            DiaUniqId target;
            DESC_FIELDS(Existing, (target));
        };
        struct LastInserted {
            DESC_FIELDS(LastInserted, ());
        };
        SUB_VARIANTS(Kind, Data, data, getKind, Existing, LastInserted);
        Data data;
    };

    struct EditCmd {
        struct RemoveDiaNode {
            EditTarget target;
            DESC_FIELDS(RemoveDiaNode, (target));
        };

        struct InsertDiaNode {
            EditTarget target;
            DESC_FIELDS(InsertDiaNode, (target));
        };

        struct UpdateImmOrg {
            EditTarget                        target;
            std::shared_ptr<org::imm::ImmOrg> value;
            DESC_FIELDS(UpdateImmOrg, (target, value));
        };

        struct MoveDiaNode {
            EditTarget         nodeToMove;
            EditTarget         newParent;
            std::optional<int> newIndex;
            DESC_FIELDS(MoveDiaNode, (nodeToMove, newParent, newIndex));
        };

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
    };

    struct EditApplyResult {
        DESC_FIELDS(EditApplyResult, ());
    };

    EditApplyResult applyDiaEdits(EditGroup const& edits);

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

    DiaAdapter getDiaRoot(int index) const {
        return dia_trees.at(getImmRoot(index).uniq());
    }


    std::vector<DiaEdit> getDiaEdits(
        int                lhsVer,
        int                rhsVer,
        const DiaEditConf& conf) const;
};

Q_DECLARE_METATYPE(DiaContextStore::EditTarget);
Q_DECLARE_METATYPE(DiaContextStore::EditCmd);
Q_DECLARE_METATYPE(DiaContextStore::EditGroup);
Q_DECLARE_METATYPE(DiaContextStore::EditApplyResult);
