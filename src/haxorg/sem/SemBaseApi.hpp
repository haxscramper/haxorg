#pragma once
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/ImmOrg.hpp>
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
    [[refl]] Vec<sem::SemId<sem::Org>> path;
    DESC_FIELDS(AstTrackingPath, (path));

    [[refl]] sem::SemId<sem::Org> getNode() const { return path.back(); }
};

/// \brief Group of the alternative AST tracking paths. If the list of
/// input subtrees has multiple elements with identical names, or IDs, all
/// of them are recorded, since it is not possible to know whether
/// duplicate IDs is an issue for the caller code, or it can resolve them.
struct [[refl]] AstTrackingAlternatives {
    Vec<AstTrackingPath> alternatives;
    DESC_FIELDS(AstTrackingAlternatives, (alternatives));

    /// \brief Return final nodes for all tracking alternatives.
    [[refl]] Vec<sem::SemId<sem::Org>> getAllNodes() const {
        return alternatives //
             | rv::transform(
                   [](AstTrackingPath const& p) { return p.getNode(); })
             | rs::to<Vec>();
    }

    /// \brief Return first node from the alternatives.
    [[refl]] sem::SemId<sem::Org> getNode() const {
        return alternatives.at(0).getNode();
    }
};

struct [[refl]] AstTrackingGroup {
    struct RadioTarget {
        Vec<sem::SemId<sem::Org>> subnodes;
        DESC_FIELDS(RadioTarget, (subnodes));
    };

    struct Single {
        sem::SemId<sem::Org> node;
        DESC_FIELDS(Single, (node));
    };

    Variant<RadioTarget, Single> data;

    enum class [[refl]] Kind
    {
        RadioTarget,
        Single,
    };

    BOOST_DESCRIBE_NESTED_ENUM(Kind, RadioTarget, Single);

    [[refl]] Kind getKind() const {
        return static_cast<Kind>(data.index());
    }

    [[refl]] RadioTarget const& getRadioTarget() const {
        return std::get<RadioTarget>(data);
    }

    [[refl]] Single const& getSingle() const {
        return std::get<Single>(data);
    }

    [[refl]] RadioTarget& getRadioTarget() {
        return std::get<RadioTarget>(data);
    }

    [[refl]] Single& getSingle() { return std::get<Single>(data); }

    [[refl]] bool isSingle() const { return getKind() == Kind::Single; }

    [[refl]] bool isRadioTarget() const {
        return getKind() == Kind::RadioTarget;
    }
};

/// \brief Fixed snapshot of all tracking information from a set of nodes.
/// Mirrors the `ImmAstTrackingMap` API for shared pointer AST.
struct [[refl]] AstTrackingMap {
    [[refl]] UnorderedMap<Str, AstTrackingAlternatives> footnotes;
    [[refl]] UnorderedMap<Str, AstTrackingAlternatives> subtrees;
    [[refl]] UnorderedMap<Str, AstTrackingAlternatives> names;
    [[refl]] UnorderedMap<Str, AstTrackingAlternatives> anchorTargets;
    [[refl]] UnorderedMap<Str, AstTrackingAlternatives> radioTargets;

    [[refl]] Opt<AstTrackingAlternatives> getIdPath(Str const& id) const {
        return subtrees.get(id);
    }

    [[refl]] Opt<AstTrackingAlternatives> getNamePath(
        Str const& id) const {
        return names.get(id);
    }


    [[refl]] Opt<AstTrackingAlternatives> getAnchorTarget(
        Str const& id) const {
        return anchorTargets.get(id);
    }

    [[refl]] Opt<AstTrackingAlternatives> getFootnotePath(
        Str const& id) const {
        return names.get(id);
    }
};

[[refl]] AstTrackingMap getAstTrackingMap(
    Vec<sem::SemId<sem::Org>> const& nodes);

[[refl]] Vec<AstTrackingGroup> getSubnodeGroups(
    sem::SemId<sem::Org>  node,
    AstTrackingMap const& map);

using SubnodeVisitor = Func<void(SemId<Org> const&)>;
/// \brief Recursively visit each subnode in the tree and apply the
/// provided callback
void eachSubnodeRec(SemId<Org> id, SubnodeVisitor cb);

template <typename T, typename Func>
Vec<T> getDfsFuncEval(SemId<Org> id, Func const& cb) {
    Vec<T> dfs;
    eachSubnodeRec(id, [&](SemId<Org> const& sub) {
        Opt<T> res = cb(sub);
        if (res.has_value()) { dfs.push_back(res.value()); }
    });
    return dfs;
}

template <typename T, typename Func>
Vec<T> getDfsFuncEval(org::ImmAdapter id, bool withPath, Func const& cb) {
    Vec<T> dfs;
    org::eachSubnodeRec(id, withPath, [&](org::ImmAdapter const& sub) {
        Opt<T> res = cb(sub);
        if (res.has_value()) { dfs.push_back(res.value()); }
    });
    return dfs;
}

Vec<Str> getDfsLeafText(SemId<Org> id, SemSet const& filter);
Vec<Str> getDfsLeafText(org::ImmAdapter const& id, SemSet const& filter);
Str      getCleanText(sem::SemId<sem::Org> const& id);
Str      getCleanText(org::ImmAdapter const& id);

/// \brief Get index of the list item with given text
int getListHeaderIndex(sem::SemId<sem::List> const& it, CR<Str> text);
/// \brief Assign body to the list item at the given position.
void setListItemBody(
    sem::SemId<sem::List>     id,
    int                       index,
    Vec<sem::SemId<sem::Org>> value);

void setDescriptionListItemBody(
    sem::SemId<sem::List>     list,
    CR<Str>                   text,
    Vec<sem::SemId<sem::Org>> value);

/// \brief Insert the list item at the specified position
void insertListItemBody(
    sem::SemId<sem::List>     id,
    int                       index,
    Vec<sem::SemId<sem::Org>> value);

void insertDescriptionListItem(
    sem::SemId<sem::List>      id,
    int                        index,
    sem::SemId<sem::Paragraph> paragraph,
    Vec<sem::SemId<sem::Org>>  value);


template <typename T>
Vec<T> getSubtreeProperties(sem::SemId<sem::Subtree> const& tree) {
    Vec<T> result;
    for (auto const& prop : tree->properties) {
        if (std::holds_alternative<T>(prop.data)) {
            result.push_back(std::get<T>(prop.data));
        }
    }

    return result;
}

Opt<UserTime> getCreationTime(SemId<Org> const& node);

Opt<sem::NamedProperty> getFinalProperty(
    CR<Vec<sem::SemId<sem::Org>>> nodes,
    CR<Str>                       kind,
    CR<Opt<Str>>                  subKind = std::nullopt);

Opt<sem::NamedProperty> getFinalProperty(
    CR<Vec<org::ImmAdapter>> nodes,
    CR<Str>                  kind,
    CR<Opt<Str>>             subKind = std::nullopt);


} // namespace sem
