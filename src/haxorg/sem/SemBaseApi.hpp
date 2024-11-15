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
