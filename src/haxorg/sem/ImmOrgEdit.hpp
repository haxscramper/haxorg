#pragma once

#include <haxorg/sem/ImmOrg.hpp>

namespace org {
// clang-format off

enum class SubtreeMove
{
    /// \brief Demote the subtree node without affecting any of the
    /// subnodes. The new subtree might be placed under a different
    /// parent and original subtrees might be reparented. This move
    /// emulates adding/removing one `*` in the org-mode file, without
    /// changing anything else.
    Physical,
    /// \brief Add/remove one level from the tree and all subtrees,
    /// irrespective of their relative levels.
    ForceLevels,
    /// \brief Add/remove level from the subtree if the current value
    /// would break hierarchy after demote. Otherwise leave the level
    /// as they are.
    ///
    /// ```
    /// // Demoting `*` will also demote `**`. otherwise the nesting
    /// // would've been broken.
    /// *
    /// **
    /// ```
    ///
    /// ```
    /// // Demoting `*` will not change the hierarchy, so `***` is not
    /// // demoted further.
    /// *
    /// ***
    /// ```
    EnsureLevels,
};

ImmAstReplaceGroup demoteSubtree(CR<ImmAdapter> node, SubtreeMove move, ImmAstEditContext& ctx);
Vec<ImmAstReplace> promoteSubtree(CR<ImmAdapter> node, SubtreeMove move, ImmAstEditContext& ctx);
ImmAstReplace setSubnode(CR<ImmAdapter> node, org::ImmId newSubnode, int position, ImmAstEditContext& ctx);
ImmAstReplace insertSubnode(CR<ImmAdapter> node, ImmId add, int position, ImmAstEditContext& ctx);
ImmAstReplace insertSubnodes(CR<ImmAdapter> node, Vec<ImmId> add, int position, ImmAstEditContext& ctx);
ImmAstReplace appendSubnode(CR<ImmAdapter> node, ImmId add, ImmAstEditContext& ctx);
ImmAstReplace dropSubnode(CR<ImmAdapter> node, int position, ImmAstEditContext& ctx);
ImmAstReplace dropSubnode(CR<ImmAdapter> node, org::ImmId subnode, ImmAstEditContext& ctx);
Opt<ImmAstReplace> moveSubnode(CR<ImmAdapter> node, int position, int offset, ImmAstEditContext& ctx, bool bounded = true);
Pair<ImmAstReplace, org::ImmId> popSubnode(CR<ImmAdapter> node, int position, ImmAstEditContext& ctx);
ImmAstReplace swapSubnode(CR<ImmAdapter> node, int from, int to, ImmAstEditContext& ctx);
/// \brief Move subnode up/down with the structural movements -- jumping over spaces, newlines etc.
Opt<ImmAstReplace> moveSubnodeStructural(CR<ImmAdapter> node, int position, int offset, ImmAstEditContext& ctx);

// clang-format on
} // namespace org
