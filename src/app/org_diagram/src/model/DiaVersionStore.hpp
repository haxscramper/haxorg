#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemAstDiff.hpp>
#include <org_diagram/src/model/nodes/DiagramTreeNode.hpp>
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

    /// \brief Single command to modify the current diagram scene tree.
    /// Commands should be grouped in `EditGroup` and applied in batches.
    struct EditCmd {
        /// \brief Remove the target node from the current subtree.
        struct RemoveDiaNode {
            EditTarget target;
            DESC_FIELDS(RemoveDiaNode, (target));
        };

        /// \brief Insert a new, empty subtree with minimal properties at
        /// the `index` of the `newParent`. Last inserted node can be
        /// referred to as the `EditTarget::LastCreated`.
        ///
        /// Adding new node with some specific properties is a two-step
        /// operation. First, an empty node is inserted into the tree,
        /// followed by the edit operation.
        struct InsertDiaNode {
            EditTarget newParent;
            /// \brief Index to insert at. If not provided, the node will
            /// be appended to the parent.
            hstd::Opt<int> index;
            DESC_FIELDS(InsertDiaNode, (newParent, index));
        };

        /// \brief Replace a `target` node with an new immutable ast
        /// subtree created from `value`. The conversion is not recursive,
        /// and none of the direct `.subnodes` of the value will be
        /// transferred. Instead, the update will only replace the subtree
        /// and re-use all the older nodes.
        struct UpdateImmOrg {
            EditTarget                     target;
            org::sem::SemId<org::sem::Org> value;
            DESC_FIELDS(UpdateImmOrg, (target, value));
        };

        /// \brief Move the list of old nodes to the new parent at index.
        struct MoveDiaNode {
            /// \brief List of nodes to move under a new parent. The nodes
            /// do not have to be under the same parent originally, and can
            /// be randomly scattered in the tree.
            ///
            /// \warning The only requirement is that no node will be a
            /// direct ancestor of the other one.
            hstd::Vec<EditTarget> nodeToMove;
            /// \brief Target node to move to. Can be existing node, can be
            /// a newly created one.
            EditTarget newParent;
            /// \brief New index to move nodes to. If not provided, append
            /// nodes to the parent.
            std::optional<int> newIndex;
            DESC_FIELDS(MoveDiaNode, (nodeToMove, newParent, newIndex));
        };

        /// \brief Convenience function to construct a remove command.
        static EditCmd Remove(EditTarget const& target) {
            return EditCmd{RemoveDiaNode{target}};
        }

        /// \brief Convenience function to construct an update command.
        static EditCmd Update(
            EditTarget const&              target,
            org::sem::SemId<org::sem::Org> value) {
            return EditCmd{UpdateImmOrg{.target = target, .value = value}};
        }

        /// \brief Convenience function to construct an insert command.
        static EditCmd Insert(
            EditTarget const&     target,
            hstd::Opt<int> const& index = std::nullopt) {
            return EditCmd{
                InsertDiaNode{.newParent = target, .index = index}};
        }

        /// \brief Convenience function to construct a move command.
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


    /// \brief Collection of the edit operations that should be applied in
    /// batch. This is the structure that mutable GUI layer sends to the
    /// version store to trigger updates.
    struct EditGroup {
        hstd::Vec<EditCmd> edits;
        DESC_FIELDS(EditGroup, (edits));

        static EditGroup Remove1ExistingNode(DiaUniqId const& id);
        static EditGroup Create1NewNode(DiaUniqId const& id, int index);
        static EditGroup Append1NewNode(DiaUniqId const& id);
        static EditGroup Create1NewNodeWithValue(
            DiaUniqId const&                      id,
            int                                   index,
            org::sem::SemId<org::sem::Org> const& value);
        static EditGroup Append1NewNodeWithValue(
            DiaUniqId const&                      id,
            org::sem::SemId<org::sem::Org> const& value);
        static EditGroup MoveNodesUnderExisting(
            DiaUniqId const&            parent,
            hstd::Vec<DiaUniqId> const& nodes,
            int                         index);

        static EditGroup UpdateExisting(
            DiaUniqId const&                      id,
            org::sem::SemId<org::sem::Org> const& node);
    };

    struct EditApplyResult {
        DESC_FIELDS(EditApplyResult, ());
    };

    /// \brief Apply all diagram edits in sequence and returnt he final
    /// application result. This method will add one item to the history,
    /// triggering the update.
    EditApplyResult applyDiaEdits(EditGroup const& edits);
    void            stepEditForward(
                   org::imm::ImmAstVersion& vEdit,
                   EditCmd const&           edit);

    org::imm::ImmAstContext::Ptr                        imm_context;
    DiaContext::Ptr                                     dia_context;
    hstd::Vec<org::imm::ImmAstVersion>                  history;
    int                                                 active = -1;
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
        hstd::Vec<DiaEdit>    edits;
        DiaAdapter            newRoot;
        hstd::Opt<DiaAdapter> oldRoot;
        int                   newIndex;
        int                   oldIndex;
        DESC_FIELDS(
            DiaRootChange,
            (edits, newRoot, oldRoot, newIndex, oldIndex));
    };


    /// \brief Create list of edits
    hstd::Vec<DiaEdit> getDiaEdits(
        int                lhsVer,
        int                rhsVer,
        const DiaEditConf& conf);

  signals:
    /// \brief Emitted every time the active tree changes. Returns the root
    /// change object with the edits necessary to transform the original
    /// diagram tree into the current version.
    void diaRootChanged(DiaVersionStore::DiaRootChange const& change);
};

Q_DECLARE_METATYPE(DiaVersionStore::EditTarget);
Q_DECLARE_METATYPE(DiaVersionStore::EditCmd);
Q_DECLARE_METATYPE(DiaVersionStore::EditGroup);
Q_DECLARE_METATYPE(DiaVersionStore::EditApplyResult);
Q_DECLARE_METATYPE(DiaVersionStore::DiaRootChange);
