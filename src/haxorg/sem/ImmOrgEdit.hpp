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

ImmAstReplaceGroup demoteSubtree(org::ImmId target, SubtreeMove move, ImmAstEditContext &ctx);
Vec<ImmAstReplace> promoteSubtree(org::ImmId target, SubtreeMove move, ImmAstEditContext &ctx);
ImmAstReplace setSubnodes(org::ImmId target, ImmVec<org::ImmId> subnodes, ImmAstEditContext &ctx);
ImmAstReplace setSubnode(org::ImmId target, org::ImmId newSubnode, int position, ImmAstEditContext &ctx);
ImmAstReplace insertSubnode(ImmId target, ImmId add, int position, ImmAstEditContext &ctx);
ImmAstReplace insertSubnodes(ImmId target, Vec<ImmId> add, int position, ImmAstEditContext &ctx);
ImmAstReplace appendSubnode(ImmId target, ImmId add, ImmAstEditContext &ctx);
ImmAstReplace dropSubnode(org::ImmId target, int position, ImmAstEditContext &ctx);
ImmAstReplace dropSubnode(org::ImmId target, org::ImmId subnode, ImmAstEditContext &ctx);
Pair<ImmAstReplace, org::ImmId> popSubnode(org::ImmId target, int position, ImmAstEditContext &ctx);

// clang-format on
} // namespace org
