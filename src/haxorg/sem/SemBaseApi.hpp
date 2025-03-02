#pragma once
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Json.hpp>

namespace org {

[[refl]] sem::SemId<sem::Time> newSemTimeStatic(
    hstd::UserTimeBreakdown const& breakdown,
    bool                           isActive = false);

struct [[refl]] OrgParseParameters {
    [[refl]] hstd::Opt<std::string> baseTokenTracePath = std::nullopt;
    [[refl]] hstd::Opt<std::string> tokenTracePath     = std::nullopt;
    [[refl]] hstd::Opt<std::string> parseTracePath     = std::nullopt;
    [[refl]] hstd::Opt<std::string> semTracePath       = std::nullopt;

    BOOST_DESCRIBE_CLASS(
        OrgParseParameters,
        (),
        (baseTokenTracePath, tokenTracePath, parseTracePath, semTracePath),
        (),
        ());
};

struct [[refl]] OrgDirectoryParseParameters {
    hstd::Func<sem::SemId<sem::Document>(std::string const& fullPath)>
        getParsedNode;

    hstd::Func<bool(std::string const& fullPath)> shouldProcessPath;
    hstd::Func<hstd::Opt<std::string>(std::string const& includePath)>
        findIncludeTarget;

    BOOST_DESCRIBE_CLASS(OrgDirectoryParseParameters, (), (), (), ());
};

[[refl]] sem::SemId<sem::Document> parseFile(
    std::string               file,
    OrgParseParameters const& opts);


[[refl]] sem::SemId<sem::Document> parseString(std::string const text);
[[refl]] sem::SemId<sem::Document> parseStringOpts(
    std::string const         text,
    OrgParseParameters const& opts);

[[refl]] hstd::Opt<sem::SemId<sem::Org>> parseDirectoryOpts(
    std::string const&                 path,
    OrgDirectoryParseParameters const& opts);

[[refl]] sem::SemId<sem::File> parseFileWithIncludes(
    std::string const&                 file,
    OrgDirectoryParseParameters const& opts);

struct OrgCodeEvalParameters {
    hstd::Func<sem::OrgCodeEvalOutput(sem::OrgCodeEvalInput)> evalBlock;
    hstd::OperationsTracer                                    debug;
};

sem::SemId<sem::Org> evaluateCodeBlocks(
    sem::SemId<sem::Org>         document,
    OrgCodeEvalParameters const& conf);

/// \brief Remove outer wrapper containers from a node and return its
/// single subnode.
///
/// Intended to be used for `asOneNode(parseString("some paragraph"))` --
/// remove the outer `Document` node and get to the actual paragraph entry
/// at hand.
[[refl]] sem::SemId<sem::Org> asOneNode(sem::OrgArg arg);

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

/// \brief Full path to an AST tracking target.
struct [[refl]] AstTrackingPath {
    [[refl]] hstd::Vec<sem::SemId<sem::Org>> path;
    DESC_FIELDS(AstTrackingPath, (path));

    [[refl]] org::sem::SemId<org::sem::Org> getParent(
        int offset = 0) const {
        int pos = path.high() - 1 - offset;
        LOGIC_ASSERTION_CHECK(
            path.has(pos),
            "Trying to get parent with offset {}, target index is {} but "
            "path only has {} items",
            offset,
            pos,
            path.size());

        return path.at(pos);
    }
    [[refl]] sem::SemId<sem::Org> getNode() const { return path.back(); }
};

/// \brief Group of the alternative AST tracking paths. If the list of
/// input subtrees has multiple elements with identical names, or IDs, all
/// of them are recorded, since it is not possible to know whether
/// duplicate IDs is an issue for the caller code, or it can resolve them.
struct [[refl]] AstTrackingAlternatives {
    hstd::Vec<AstTrackingPath> alternatives;
    DESC_FIELDS(AstTrackingAlternatives, (alternatives));

    /// \brief Return final nodes for all tracking alternatives.
    [[refl]] hstd::Vec<sem::SemId<sem::Org>> getAllNodes() const {
        return alternatives //
             | hstd::rv::transform(
                   [](AstTrackingPath const& p) { return p.getNode(); })
             | hstd::rs::to<hstd::Vec>();
    }

    /// \brief Return first node from the alternatives.
    [[refl]] sem::SemId<sem::Org> getNode() const {
        return alternatives.at(0).getNode();
    }
};

struct [[refl]] AstTrackingGroup {
    struct [[refl]] RadioTarget {
        [[refl]] AstTrackingPath                 target;
        [[refl]] hstd::Vec<sem::SemId<sem::Org>> nodes;
        DESC_FIELDS(RadioTarget, (nodes));
    };

    struct [[refl]] Single {
        [[refl]] sem::SemId<sem::Org> node;
        DESC_FIELDS(Single, (node));
    };

    struct [[refl]] TrackedHashtag {
        [[refl]] sem::SemId<sem::Org> tag;
        [[refl]] hstd::UnorderedMap<sem::HashTagFlat, AstTrackingPath>
            targets;
        DESC_FIELDS(TrackedHashtag, (tag, targets));
    };

    using Data = hstd::Variant<RadioTarget, Single, TrackedHashtag>;
    Data data;
    DESC_FIELDS(AstTrackingGroup, (data));

    enum class [[refl]] Kind
    {
        RadioTarget,
        Single,
        TrackedHashtag,
    };

    using variant_enum_type = Kind;
    using variant_data_type = Data;
    char const* sub_variant_get_name() const { return "data"; }
    Data const& sub_variant_get_data() const { return data; }
    Kind        sub_variant_get_kind() const { return getKind(); }

    BOOST_DESCRIBE_NESTED_ENUM(Kind, RadioTarget, Single, TrackedHashtag);

    Kind getKind() const { return static_cast<Kind>(data.index()); }

    [[refl]] RadioTarget const& getRadioTarget() const {
        return hstd::get_sub_variant<RadioTarget, AstTrackingGroup>(data);
    }


    [[refl]] TrackedHashtag const& getTrackedHashtag() const {
        return hstd::get_sub_variant<TrackedHashtag, AstTrackingGroup>(
            data);
    }

    [[refl]] TrackedHashtag& getTrackedHashtag() {
        return hstd::get_sub_variant<TrackedHashtag, AstTrackingGroup>(
            data);
    }

    [[refl]] Single const& getSingle() const {
        return hstd::get_sub_variant<Single, AstTrackingGroup>(data);
    }

    [[refl]] RadioTarget& getRadioTarget() {
        return hstd::get_sub_variant<RadioTarget, AstTrackingGroup>(data);
    }

    [[refl]] Single& getSingle() { return std::get<Single>(data); }

    [[refl]] bool isSingle() const { return getKind() == Kind::Single; }
    [[refl]] bool isTrackedHashtag() const {
        return getKind() == Kind::TrackedHashtag;
    }

    [[refl]] bool isRadioTarget() const {
        return getKind() == Kind::RadioTarget;
    }
};

/// \brief Fixed snapshot of all tracking information from a set of nodes.
/// Mirrors the `ImmAstTrackingMap` API for shared pointer AST.
struct [[refl]] AstTrackingMap {
    [[refl]] hstd::UnorderedMap<hstd::Str, AstTrackingAlternatives>
        footnotes;
    [[refl]] hstd::UnorderedMap<hstd::Str, AstTrackingAlternatives>
        subtrees;
    [[refl]] hstd::UnorderedMap<hstd::Str, AstTrackingAlternatives> names;
    [[refl]] hstd::UnorderedMap<hstd::Str, AstTrackingAlternatives>
        anchorTargets;
    [[refl]] hstd::UnorderedMap<hstd::Str, AstTrackingAlternatives>
        radioTargets;
    [[refl]] hstd::UnorderedMap<sem::HashTagFlat, AstTrackingAlternatives>
        hashtagDefinitions;

    DESC_FIELDS(
        AstTrackingMap,
        (footnotes,
         subtrees,
         names,
         anchorTargets,
         radioTargets,
         hashtagDefinitions));

    [[refl]] hstd::Opt<AstTrackingAlternatives> getIdPath(
        hstd::Str const& id) const {
        return subtrees.get(id);
    }

    [[refl]] hstd::Opt<AstTrackingAlternatives> getNamePath(
        hstd::Str const& id) const {
        return names.get(id);
    }


    [[refl]] hstd::Opt<AstTrackingAlternatives> getAnchorTarget(
        hstd::Str const& id) const {
        return anchorTargets.get(id);
    }

    [[refl]] hstd::Opt<AstTrackingAlternatives> getFootnotePath(
        hstd::Str const& id) const {
        return names.get(id);
    }
};

[[refl]] AstTrackingMap getAstTrackingMap(
    hstd::Vec<sem::SemId<sem::Org>> const& nodes);

[[refl]] hstd::Vec<AstTrackingGroup> getSubnodeGroups(
    sem::SemId<sem::Org>  node,
    AstTrackingMap const& map);

using SemSubnodeVisitor = hstd::Func<void(sem::SemId<sem::Org> const&)>;
using SemSubnodeVisitorSimplePath = hstd::Func<void(
    sem::SemId<sem::Org> const&,
    hstd::Vec<sem::SemId<sem::Org>> const& path)>;
/// \brief Recursively visit each subnode in the tree and apply the
/// provided callback
void eachSubnodeRec(sem::SemId<sem::Org> id, SemSubnodeVisitor cb);
void eachSubnodeRecSimplePath(
    sem::SemId<sem::Org>        id,
    SemSubnodeVisitorSimplePath cb);


using ImmSubnodeVisitor = hstd::Func<void(imm::ImmAdapter)>;
void eachSubnodeRec(
    org::imm::ImmAdapter id,
    bool                 withPath,
    ImmSubnodeVisitor    cb);

template <typename T, typename Func>
hstd::Vec<T> getDfsFuncEval(sem::SemId<sem::Org> id, Func const& cb) {
    hstd::Vec<T> dfs;
    eachSubnodeRec(id, [&](sem::SemId<sem::Org> const& sub) {
        hstd::Opt<T> res = cb(sub);
        if (res.has_value()) { dfs.push_back(res.value()); }
    });
    return dfs;
}

template <typename T, typename Func>
hstd::Vec<T> getDfsFuncEval(
    org::imm::ImmAdapter id,
    bool                 withPath,
    Func const&          cb) {
    hstd::Vec<T> dfs;
    org::eachSubnodeRec(
        id, withPath, [&](org::imm::ImmAdapter const& sub) {
            hstd::Opt<T> res = cb(sub);
            if (res.has_value()) { dfs.push_back(res.value()); }
        });
    return dfs;
}

hstd::Vec<hstd::Str> getDfsLeafText(
    sem::SemId<sem::Org> id,
    SemSet const&        filter);
hstd::Vec<hstd::Str> getDfsLeafText(
    org::imm::ImmAdapter const& id,
    SemSet const&               filter);
hstd::Str getCleanText(sem::SemId<sem::Org> const& id);
hstd::Str getCleanText(imm::ImmAdapter const& id);

/// \brief Get index of the list item with given text
int getListHeaderIndex(
    sem::SemId<sem::List> const& it,
    hstd::CR<hstd::Str>          text);
/// \brief Assign body to the list item at the given position.
void setListItemBody(
    sem::SemId<sem::List>           id,
    int                             index,
    hstd::Vec<sem::SemId<sem::Org>> value);

void setDescriptionListItemBody(
    sem::SemId<sem::List>           list,
    hstd::CR<hstd::Str>             text,
    hstd::Vec<sem::SemId<sem::Org>> value);

/// \brief Insert the list item at the specified position
void insertListItemBody(
    sem::SemId<sem::List>           id,
    int                             index,
    hstd::Vec<sem::SemId<sem::Org>> value);

void insertDescriptionListItem(
    sem::SemId<sem::List>           id,
    int                             index,
    sem::SemId<sem::Paragraph>      paragraph,
    hstd::Vec<sem::SemId<sem::Org>> value);


template <typename T>
hstd::Vec<T> getSubtreeProperties(sem::SemId<sem::Subtree> const& tree) {
    hstd::Vec<T> result;
    for (auto const& prop : tree->properties) {
        if (std::holds_alternative<T>(prop.data)) {
            result.push_back(std::get<T>(prop.data));
        }
    }

    return result;
}


template <typename T>
hstd::Vec<T> getSubtreeProperties(org::imm::ImmSubtree const& subtree) {
    hstd::Vec<T> result;
    for (auto const& prop : subtree.properties) {
        if (std::holds_alternative<T>(prop.data)) {
            result.push_back(std::get<T>(prop.data));
        }
    }

    return result;
}


hstd::Opt<hstd::UserTime> getCreationTime(
    sem::SemId<sem::Org> const& node);

hstd::Opt<sem::NamedProperty> getFinalProperty(
    hstd::CR<hstd::Vec<sem::SemId<sem::Org>>> nodes,
    hstd::CR<hstd::Str>                       kind,
    hstd::CR<hstd::Opt<hstd::Str>>            subKind = std::nullopt);

hstd::Opt<sem::NamedProperty> getFinalProperty(
    hstd::CR<hstd::Vec<imm::ImmAdapter>> nodes,
    hstd::CR<hstd::Str>                  kind,
    hstd::CR<hstd::Opt<hstd::Str>>       subKind = std::nullopt);

} // namespace org
