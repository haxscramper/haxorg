#pragma once

#include <haxorg/imm/ImmOrg.hpp>

namespace org::imm {
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



[[refl]] ImmAstReplace replaceNode(ImmAdapter const& target, ImmId const& value, ImmAstEditContext &ctx);
[[refl]] ImmAstReplaceGroup demoteSubtree(hstd::ImmAdapter const& node, SubtreeMove move, ImmAstEditContext& ctx);
[[refl]] hstd::Vec<ImmAstReplace> promoteSubtree(hstd::ImmAdapter const& node, SubtreeMove move, ImmAstEditContext& ctx);
[[refl]] ImmAstReplace setSubnode(hstd::ImmAdapter const& node, org::imm::ImmId newSubnode, int position, ImmAstEditContext& ctx);
[[refl]] ImmAstReplace insertSubnode(hstd::ImmAdapter const& node, ImmId add, int position, ImmAstEditContext& ctx);
[[refl]] ImmAstReplace insertSubnodes(hstd::ImmAdapter const& node, hstd::Vec<ImmId> add, int position, ImmAstEditContext& ctx);
[[refl]] ImmAstReplace appendSubnode(hstd::ImmAdapter const& node, ImmId add, ImmAstEditContext& ctx);
[[refl]] ImmAstReplace dropSubnode(hstd::ImmAdapter const& node, int position, ImmAstEditContext& ctx);
[[refl]] ImmAstReplace dropSubnode(hstd::ImmAdapter const& node, org::imm::ImmId subnode, ImmAstEditContext& ctx);
[[refl]] hstd::Opt<ImmAstReplace> moveSubnode(hstd::ImmAdapter const& node, int position, int offset, ImmAstEditContext& ctx, bool bounded = true);
[[refl]] hstd::Pair<ImmAstReplace, org::imm::ImmId> popSubnode(hstd::ImmAdapter const& node, int position, ImmAstEditContext& ctx);
[[refl]] ImmAstReplace swapSubnode(hstd::ImmAdapter const& node, int from, int to, ImmAstEditContext& ctx);
/// \brief Move subnode up/down with the structural movements -- jumping over spaces, newlines etc.
[[refl]] hstd::Opt<ImmAstReplace> moveSubnodeStructural(hstd::ImmAdapter const& node, int position, int offset, ImmAstEditContext& ctx);

// clang-format on

[[refl]] hstd::Vec<hstd::Str> flatWords(ImmAdapter const& node);

/// \brief How to select next target for the selector search.
struct OrgSelectorLink {
    enum class Kind
    {
        DirectSubnode   = 0,
        IndirectSubnode = 1,
        FieldName       = 2,
    };

    BOOST_DESCRIBE_NESTED_ENUM(
        Kind,
        DirectSubnode,
        IndirectSubnode,
        FieldName);


    // 0
    struct DirectSubnode {};
    // 1
    struct IndirectSubnode {};
    // 2
    struct FieldName {
        ImmReflFieldId name;
    };

    using Data = hstd::Variant<DirectSubnode, IndirectSubnode, FieldName>;
    Data data;

    Kind getKind() const { return static_cast<Kind>(data.index()); }

    BOOST_DESCRIBE_CLASS(OrgSelectorLink, (), (), (), ());
};

struct OrgSelectorResult {
    bool isMatching     = false;
    bool tryNestedNodes = true;
    BOOST_DESCRIBE_CLASS(
        OrgSelectorResult,
        (),
        (isMatching, tryNestedNodes),
        (),
        ());
};

struct OrgSelectorCondition {
    using Predicate = hstd::Func<OrgSelectorResult(ImmAdapter const&)>;
    Predicate check;

    /// \brief Matched node should be added to the full match set
    bool                       isTarget = false;
    hstd::Opt<hstd::Str>       debug;
    hstd::Opt<OrgSelectorLink> link;

    BOOST_DESCRIBE_CLASS(OrgSelectorCondition, (), (), (), ());
};

struct OrgDocumentSelector : hstd::OperationsTracer {
    hstd::Vec<OrgSelectorCondition> path;
    bool                            debug = false;

    OrgDocumentSelector() {}

    hstd::Vec<ImmAdapter> getMatches(ImmAdapter const& node) const;

    OrgSelectorLink linkDirectSubnode() const {
        return OrgSelectorLink{.data = OrgSelectorLink::DirectSubnode{}};
    }

    OrgSelectorLink linkIndirectSubnode() const {
        return OrgSelectorLink{.data = OrgSelectorLink::IndirectSubnode{}};
    }

    OrgSelectorLink linkField(ImmReflFieldId const& name) const {
        return OrgSelectorLink{
            .data = OrgSelectorLink::FieldName{.name = name}};
    }

    void searchSubtreePlaintextTitle(
        hstd::Vec<hstd::Str> const& title,
        bool                        isTarget,
        hstd::Opt<OrgSelectorLink>  link = std::nullopt);

    void searchSubtreeId(
        hstd::Str const&           id,
        bool                       isTarget,
        hstd::Opt<int>             maxLevel = std::nullopt,
        hstd::Opt<OrgSelectorLink> link     = std::nullopt);

    void searchAnyKind(
        hstd::IntSet<OrgSemKind> const& kinds,
        bool                            isTarget,
        hstd::Opt<OrgSelectorLink>      link = std::nullopt);

    void searchPredicate(
        org::imm::OrgSelectorCondition::Predicate const& predicate,
        bool                                             isTarget,
        hstd::Opt<OrgSelectorLink> link = std::nullopt);

    BOOST_DESCRIBE_CLASS(OrgDocumentSelector, (), (path), (), ());
};

hstd::Vec<ImmAdapter> getAllMatching(
    ImmAdapter const&          node,
    OrgDocumentSelector const& selector);


} // namespace org::imm
