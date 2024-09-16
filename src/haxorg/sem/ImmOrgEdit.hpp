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

Vec<Str> flatLeafNodes(ImmAdapter const& node);

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
        Str name;
    };

    using Data = Variant<DirectSubnode, IndirectSubnode, FieldName>;
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
    using Predicate = Func<OrgSelectorResult(ImmAdapter const&)>;
    Predicate check;

    /// \brief Matched node should be added to the full match set
    bool                 isTarget = false;
    Opt<Str>             debug;
    Opt<OrgSelectorLink> link;

    BOOST_DESCRIBE_CLASS(OrgSelectorCondition, (), (), (), ());
};

struct OrgDocumentSelector
    : OperationsTracer
    , OperationsScope {
    Vec<OrgSelectorCondition> path;
    bool                      debug = false;

    OrgDocumentSelector() {
        OperationsScope::TraceState = &(OperationsTracer::TraceState);
    }

    Vec<ImmAdapter> getMatches(ImmAdapter const& node) const;

    OrgSelectorLink linkDirectSubnode() const {
        return OrgSelectorLink{.data = OrgSelectorLink::DirectSubnode{}};
    }

    OrgSelectorLink linkIndirectSubnode() const {
        return OrgSelectorLink{.data = OrgSelectorLink::IndirectSubnode{}};
    }

    OrgSelectorLink linkField(Str const& name) const {
        return OrgSelectorLink{
            .data = OrgSelectorLink::FieldName{.name = name}};
    }

    void searchSubtreePlaintextTitle(
        Vec<Str> const&      title,
        bool                 isTarget,
        Opt<OrgSelectorLink> link = std::nullopt);

    void searchSubtreeId(
        Str const&           id,
        bool                 isTarget,
        Opt<int>             maxLevel = std::nullopt,
        Opt<OrgSelectorLink> link     = std::nullopt);

    void searchAnyKind(
        const IntSet<OrgSemKind>& kinds,
        bool                      isTarget,
        Opt<OrgSelectorLink>      link = std::nullopt);

    void searchPredicate(
        org::OrgSelectorCondition::Predicate const& predicate,
        bool                                        isTarget,
        Opt<OrgSelectorLink>                        link = std::nullopt);

    void dbg(Str const& msg, int depth, int line = __builtin_LINE()) const;


    BOOST_DESCRIBE_CLASS(OrgDocumentSelector, (), (path), (), ());
};

Vec<ImmAdapter> getAllMatching(
    ImmAdapter const&          node,
    OrgDocumentSelector const& selector);


} // namespace org
