#pragma once

#include "common.hpp"
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>

namespace hstd::ext::diff {


/// \brief Single edit operation on the path to transform the source
/// diagram node tree into the destination diagram node tree.
struct DiaEdit {
    /// \brief Create a new scene item with the information from `dstNode`.
    /// This operation inserts a whole new subtree, recursively.
    struct Insert {
        /// \brief Node to insert. The parent can be inferred from the
        /// `dstNode` data.
        NodeStore::Id dstNode; // NOTE: usage of the dia adapter should be
                               // replaced by a newly introduced `NodeId`
                               // strong typedef type.
        /// \brief Target index of the `dstNode`
        int dstIndex;
        DESC_FIELDS(Insert, (dstNode, dstIndex));
    };

    /// \brief Delete the source node. This operation deletes teh whole new
    /// subtree recursively.
    struct Delete {
        /// \brief Node to delete. Parent can be inferred from the
        /// `srcNode` data.
        NodeStore::Id srcNode;
        /// \brief The index of the node to delete.
        int srcIndex;
        DESC_FIELDS(Delete, (srcNode, srcIndex));
    };

    /// \brief Move the source node from the provided index to the
    /// destination node at index. Both nodes must be under the same
    /// parent. For cross-parent moves the diff will issue delete and
    /// insert operation.
    struct Move {
        /// \brief Node to move.
        NodeStore::Id srcNode;
        NodeStore::Id dstNode;
        int           srcIndex;
        int           dstIndex;
        DESC_FIELDS(Move, (srcNode, dstNode, srcIndex, dstIndex));
    };

    /// \brief Replace the source node from the provided index with the
    /// destination node. Does not perform recursive update: subnodes might
    /// have had their own updates and updating parent should not overwrite
    /// them.
    struct Update {
        NodeStore::Id srcNode;
        NodeStore::Id dstNode;
        int           srcIndex;
        int           dstIndex;
        DESC_FIELDS(Update, (srcNode, dstNode, srcIndex, dstIndex));
    };

    /// \brief Check if the diff has an associated source node.
    bool hasSrc() const { return isDelete() || isMove() || isUpdate(); }
    /// \brief Check if the diff has an associated target node.
    bool hasDst() const { return isInsert() || isMove() || isUpdate(); }
    /// \brief Get associated destination diagram node
    NodeStore::Id getDst() const;
    /// \brief Get associated source diagram node.
    NodeStore::Id getSrc() const;
    /// \brief Shorthand to get unique ID for the source node.
    NodeStore::Id getSrcUniq() const { return getSrc(); }
    /// \brief Shorthand to get unique ID for the destination node.
    NodeStore::Id getDstUniq() const { return getDst(); }

    SUB_VARIANTS(Kind, Data, data, getKind, Delete, Insert, Update, Move);
    Data data;
    DESC_FIELDS(DiaEdit, (data));
};

hstd::Vec<DiaEdit> getEdits(
    NodeStore& srcStore,
    NodeStore& dstStore,
    hstd::Func<bool(NodeStore::Id const& src, NodeStore::Id const& dst)> const&
        areValuesEqual);
} // namespace hstd::ext::diff
