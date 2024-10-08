#pragma once
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Json.hpp>

namespace sem {

[[refl]] sem::SemId<sem::Time> newSemTimeStatic(
    UserTimeBreakdown const& breakdown,
    bool                     isActive = false);

struct [[refl]] OrgParseParameters {
    [[refl]] Opt<std::string> baseTokenTracePath = std::nullopt;
    [[refl]] Opt<std::string> tokenTracePath     = std::nullopt;
    [[refl]] Opt<std::string> parseTracePath     = std::nullopt;
    [[refl]] Opt<std::string> semTracePath       = std::nullopt;

    BOOST_DESCRIBE_CLASS(
        OrgParseParameters,
        (),
        (baseTokenTracePath, tokenTracePath, parseTracePath, semTracePath),
        (),
        ());
};

[[refl]] sem::SemId<sem::Document> parseFile(
    std::string               file,
    OrgParseParameters const& opts);
[[refl]] sem::SemId<sem::Document> parseString(std::string const text);
[[refl]] sem::SemId<sem::Document> parseStringOpts(
    std::string const         text,
    OrgParseParameters const& opts);


[[refl]] std::string formatToString(sem::SemId<sem::Org> arg);

struct [[refl]] OrgYamlExportOpts {
    [[refl]] bool skipNullFields  = false;
    [[refl]] bool skipFalseFields = false;
    [[refl]] bool skipZeroFields  = false;
    [[refl]] bool skipLocation    = false;
    [[refl]] bool skipId          = false;

    BOOST_DESCRIBE_CLASS(
        OrgYamlExportOpts,
        (),
        (skipNullFields,
         skipFalseFields,
         skipZeroFields,
         skipLocation,
         skipId),
        (),
        ());
};

[[refl]] std::string exportToYamlString(
    sem::SemId<sem::Org> const& node,
    OrgYamlExportOpts const&    opts);
[[refl]] void exportToYamlFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path,
    OrgYamlExportOpts const&    opts);

[[refl]] std::string exportToJsonString(sem::SemId<sem::Org> const& node);
[[refl]] void        exportToJsonFile(
           sem::SemId<sem::Org> const& node,
           std::string                 path);

[[refl]] sem::SemId<sem::Document> readProtobufFile(
    std::string const& file);

[[refl]] void exportToProtobufFile(
    sem::SemId<sem::Document> doc,
    std::string const&        file);

struct [[refl]] OrgTreeExportOpts {
    [[refl]] bool withLineCol     = true;
    [[refl]] bool withOriginalId  = true;
    [[refl]] bool withSubnodeIdx  = true;
    [[refl]] bool skipEmptyFields = true;
    [[refl]] int  startLevel      = 0;
    [[refl]] bool withColor       = true;
    [[refl]] int  maxDepth        = 40;

    BOOST_DESCRIBE_CLASS(
        OrgTreeExportOpts,
        (),
        (withLineCol,
         withOriginalId,
         withSubnodeIdx,
         skipEmptyFields,
         startLevel,
         withColor,
         maxDepth),
        (),
        ());
};

[[refl]] std::string exportToTreeString(
    sem::SemId<sem::Org> const& node,
    OrgTreeExportOpts const&    opts);

[[refl]] void exportToTreeFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path,
    OrgTreeExportOpts const&    opts);


using SubnodeVisitor = Func<void(SemId<Org>)>;
/// \brief Recursively visit each subnode in the tree and apply the
/// provided callback
void eachSubnodeRec(SemId<Org> id, SubnodeVisitor cb);


/// \brief Part of the parent node context path. When visiting a node this
/// path will contain an ordered list of all *parent* elements.
struct [[refl]] SubnodeVisitorCtxPart {
    enum class [[refl]] Kind
    {
        Field, ///< \brief Visiting named field
        Index, ///< \brief Visiting indexed subnode.
        Key,   ///< \brief Visiting Str->Node table
    };

    BOOST_DESCRIBE_NESTED_ENUM(Kind, Field, Index, Key);

    /// \brief Parent node for the currently visited one. Each node is
    /// encountered exactly once in the visitor context path, but when
    /// visiting multi-layered fields (vector field) the node is not,
    /// present.
    ///
    /// For vector fields the path will have two parts:
    /// `[node+field-name]+[index]` -- the first element from the actual
    /// field visit and the second is from accessing each particular index.
    [[refl]] Opt<SemId<Org>> node;
    /// \brief If the current visit is in vector field -- index of
    /// the node in parent list.
    [[refl]] Opt<int> index;
    /// \brief If the current visit is in the dedicated field (`.title` for
    /// example),
    [[refl]] Opt<Str> field;
    [[refl]] Kind     kind;

    BOOST_DESCRIBE_CLASS(
        SubnodeVisitorCtxPart,
        (),
        (node, index, field, kind),
        (),
        ());
};

struct [[refl]] SubnodeVisitorOpts {

    BOOST_DESCRIBE_CLASS(SubnodeVisitorOpts, (), (), (), ());
};

struct [[refl]] SubnodeVisitorResult {
    /// \brief After visting the current node, descend into it's node
    /// fields
    [[refl]] bool visitNextFields = true;
    /// \brief
    [[refl]] bool visitNextSubnodes = true;
    [[refl]] bool visitNextBases    = true;
    BOOST_DESCRIBE_CLASS(
        SubnodeVisitorResult,
        (),
        (visitNextFields, visitNextSubnodes, visitNextBases),
        (),
        ());
};

using SubnodeVisitorWithCtx = Func<
    SubnodeVisitorResult(SemId<Org>, Vec<SubnodeVisitorCtxPart> const&)>;

/// \brief Recursively visit each subnode in the tree and apply the
/// provided callback to all non-nil subnodes. Pass the current node index
/// in the parent tree, stack of the parent nodes and the node itself. If
/// visit is done to a node placed in a
void eachSubnodeRecWithContext(SemId<Org> id, SubnodeVisitorWithCtx);


struct Subtree;
struct Link;

/// \brief Statically computed context for the link, footnote and subtree
/// ID resolution.
///
/// \note All possible link targets are stored and returned as sequences,
/// so the decision about reaction to the duplicate links can be done by
/// the callsite. Order of elements in the returned links depends on the
/// order of node registration.
struct [[refl]] OrgDocumentContext {
    UnorderedMap<Str, Vec<SemId<Subtree>>>            subtreeIds;
    UnorderedMap<Str, Vec<SemId<Subtree>>>            subtreeCustomIds;
    UnorderedMap<Str, Vec<SemId<Org>>>                radioTargets;
    UnorderedMap<Str, Vec<SemId<AnnotatedParagraph>>> footnoteTargets;


    [[refl]] Vec<SemId<Subtree>> getSubtreeById(Str const& id) const;
    [[refl]] Vec<SemId<Org>> getLinkTarget(SemId<Link> const& link) const;
    [[refl]] Vec<SemId<Org>> getRadioTarget(Str const& name) const;

    /// \brief Recursively register all availble targets from the nodes.
    [[refl]] void addNodes(SemId<Org> const& node);

    BOOST_DESCRIBE_CLASS(OrgDocumentContext, (), (), (), ());
};

Opt<UserTime> getCreationTime(SemId<Org> const& node);


struct [[refl]] OrgSelectorLink {
    enum class [[refl]] Kind
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

struct [[refl]] OrgSelectorResult {
    bool isMatching     = false;
    bool tryNestedNodes = true;
    BOOST_DESCRIBE_CLASS(
        OrgSelectorResult,
        (),
        (isMatching, tryNestedNodes),
        (),
        ());
};

struct [[refl]] OrgSelectorCondition {
    using Predicate = Func<OrgSelectorResult(SemId<Org> const&)>;
    Predicate check;

    /// \brief Matched node should be added to the full match set
    [[refl]] bool                 isTarget = false;
    [[refl]] Opt<Str>             debug;
    [[refl]] Opt<OrgSelectorLink> link;

    BOOST_DESCRIBE_CLASS(OrgSelectorCondition, (), (), (), ());
};

struct [[refl]] OrgDocumentSelector {
    [[refl]] Vec<OrgSelectorCondition> path;
    [[refl]] bool                      debug = false;

    [[refl]] Vec<SemId<Org>> getMatches(SemId<Org> const& node) const;

    [[refl]] OrgSelectorLink linkDirectSubnode() const {
        return OrgSelectorLink{.data = OrgSelectorLink::DirectSubnode{}};
    }

    [[refl]] OrgSelectorLink linkIndirectSubnode() const {
        return OrgSelectorLink{.data = OrgSelectorLink::IndirectSubnode{}};
    }

    [[refl]] OrgSelectorLink linkField(Str const& name) const {
        return OrgSelectorLink{
            .data = OrgSelectorLink::FieldName{.name = name}};
    }

    [[refl]] void searchSubtreePlaintextTitle(
        Str const&           title,
        bool                 isTarget,
        Opt<OrgSelectorLink> link = std::nullopt);

    [[refl]] void searchSubtreeId(
        Str const&           id,
        bool                 isTarget,
        Opt<int>             maxLevel = std::nullopt,
        Opt<OrgSelectorLink> link     = std::nullopt);

    [[refl]] void searchAnyKind(
        const IntSet<OrgSemKind>& kinds,
        bool                      isTarget,
        Opt<OrgSelectorLink>      link = std::nullopt);

    [[refl]] void searchPredicate(
        sem::OrgSelectorCondition::Predicate const& predicate,
        bool                                        isTarget,
        Opt<OrgSelectorLink>                        link = std::nullopt);

    void dbg(Str const& msg, int depth, int line = __builtin_LINE()) const;


    BOOST_DESCRIBE_CLASS(OrgDocumentSelector, (), (path), (), ());
};

Vec<SemId<Org>> getAllMatching(
    SemId<Org> const&          node,
    OrgDocumentSelector const& selector);

} // namespace sem
