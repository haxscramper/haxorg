#include "SemBaseApi.hpp"
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/sem/SemConvert.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/serde/SemOrgSerdeDeclarations.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <haxorg/base_lexer/base_token_tokenize.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <fstream>

#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC
#    include <SemOrgProto.pb.h>
#endif

using namespace org::sem;
using namespace org;
using namespace hstd;
using osk = OrgSemKind;


std::string org::exportToJsonString(sem::SemId<sem::Org> const& node) {
    return to_string(org::algo::ExporterJson{}.evalTop(node));
}

void org::exportToJsonFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path) {
    writeFile(fs::path{path}, exportToJsonString(node));
}

std::string org::exportToYamlString(
    sem::SemId<sem::Org> const& node,
    const OrgYamlExportOpts&    opts) {
    std::stringstream os;

    org::algo::ExporterYaml exp{
        .skipNullFields  = opts.skipNullFields,
        .skipFalseFields = opts.skipFalseFields,
        .skipZeroFields  = opts.skipZeroFields,
        .skipLocation    = opts.skipLocation,
        .skipId          = opts.skipId,
    };

    os << exp.evalTop(node);

    return os.str();
}

void org::exportToYamlFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path,
    const OrgYamlExportOpts&    opts) {
    writeFile(fs::path{path}, exportToYamlString(node, opts));
}

namespace {
void treeExportImpl(
    ColStream&                    os,
    sem::SemId<sem::Org> const&   node,
    org::OrgTreeExportOpts const& opts) {
    org::algo::ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.conf.maxTreeDepth    = opts.maxDepth;
    tree.evalTop(node);
}
} // namespace

std::string org::exportToTreeString(
    sem::SemId<sem::Org> const&   node,
    org::OrgTreeExportOpts const& opts) {
    ColStream os{};
    treeExportImpl(os, node, opts);

    std::string result = os.toString(opts.withColor);
    return result;
}

void org::exportToTreeFile(
    sem::SemId<sem::Org> const&   node,
    std::string                   path,
    org::OrgTreeExportOpts const& opts) {
    ColStream os{};
    treeExportImpl(os, node, opts);
    std::ofstream file{path};
    file << os.toString(opts.withColor);
}


sem::SemId<sem::Document> org::readProtobufFile(const std::string& file) {
#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC
    sem::SemId        read_node = sem::SemId<sem::Org>::Nil();
    std::ifstream     stream{file};
    orgproto::AnyNode result;
    result.ParseFromIstream(&stream);
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        org::algo::proto_write_accessor<sem::SemId<sem::Org>>::for_ref(
            read_node));
    return read_node.as<sem::Document>();
#elif ORG_BUILD_EMCC
    throw std::logic_error(
        "Protobuf file parsing is not supported for wasm");
#else
    throw std::logic_error(
        "haxorg was not compiled with protobuf support. Enable "
        "`ORG_BUILD_WITH_PROTOBUF` and rebuild to enable protobuf serde.");
#endif
}

void org::exportToProtobufFile(
    sem::SemId<sem::Document> doc,
    const std::string&        file) {
#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC
    std::ofstream     stream{file};
    orgproto::AnyNode result;
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        &result, doc.asOrg());
    result.SerializeToOstream(&stream);
#elif ORG_BUILD_EMCC
    throw std::logic_error(
        "Protobuf file writing is not supported for wasm");
#else
    throw std::logic_error(
        "haxorg was not compiled with protobuf support. Enable "
        "`ORG_BUILD_WITH_PROTOBUF` and rebuild to enable protobuf serde.");
#endif
}


std::string org::formatToString(sem::SemId<sem::Org> arg) {
    return org::algo::Formatter::format(arg);
}

namespace {
void eachSubnodeRecImpl(
    CR<org::SemSubnodeVisitor> visitor,
    SemId<Org>                 org,
    bool                       originalBase);

template <sem::NotOrg T>
void visitField(CR<org::SemSubnodeVisitor>, CR<T>) {}


void visitField(CR<org::SemSubnodeVisitor> visitor, SemId<Org> node) {
    if (!node.isNil()) { eachSubnodeRecImpl(visitor, node, true); }
}

template <sem::IsOrg T>
void visitField(CR<org::SemSubnodeVisitor> visitor, CR<T> node) {
    visitField(visitor, node.asOrg());
}


template <typename T>
void visitField(CR<org::SemSubnodeVisitor> visitor, CVec<T> value) {
    for (const auto& it : value) { visitField(visitor, it); }
}


template <typename T>
void visitField(CR<org::SemSubnodeVisitor> visitor, CR<Opt<T>> value) {
    if (value) { visitField(visitor, *value); }
}

template <typename T>
void recVisitOrgNodesImpl(
    CR<org::SemSubnodeVisitor> visitor,
    SemId<T>                   tree,
    bool                       originalBase) {
    if (tree.isNil()) { return; }
    if (originalBase) { visitor(tree); }
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        using BaseType = typename decltype(Base)::type;
        recVisitOrgNodesImpl<BaseType>(
            visitor, tree.template as<BaseType>(), false);
    });

    mp_for_each<Md>([&](auto const& field) {
        visitField(visitor, tree.get()->*field.pointer);
    });
}


void eachSubnodeRecImpl(
    CR<org::SemSubnodeVisitor> visitor,
    SemId<Org>                 org,
    bool                       originalBase) {
    std::visit(
        [&](const auto& node) {
            recVisitOrgNodesImpl(visitor, node, originalBase);
        },
        asVariant(org));
}
} // namespace


void org::eachSubnodeRec(SemId<Org> id, org::SemSubnodeVisitor cb) {
    eachSubnodeRecImpl(cb, id, true);
}


Opt<UserTime> org::getCreationTime(const SemId<Org>& node) {
    if (node->is(osk::Paragraph)) {
        auto time = node.as<sem::Paragraph>()->getTimestamps();
        return time.get(0);
    } else if (node->is(osk::Subtree)) {
        auto const& tree = node.as<Subtree>();
        for (auto const& period :
             tree->getTimePeriods({SubtreePeriod::Kind::Created})) {
            return period.from;
        }

        for (auto const& period :
             tree->getTimePeriods({SubtreePeriod::Kind::Titled})) {
            return period.from;
        }
    }

    return std::nullopt;
}

namespace {

template <sem::NotOrg T>
void addSubnodes(
    Vec<SemId<Org>>& result,
    char const*      field,
    T const&         value) {}


void addSubnodes(
    Vec<SemId<Org>>&       result,
    char const*            field,
    sem::SemId<Org> const& value) {
    result.push_back(value);
}

template <sem::IsOrg T>
void addSubnodes(
    Vec<SemId<Org>>&     result,
    char const*          field,
    sem::SemId<T> const& value) {
    result.push_back(value.asOrg());
}

void addSubnodes(
    Vec<SemId<Org>>&            result,
    char const*                 field,
    Vec<sem::SemId<Org>> const& value) {
    result.append(value);
}

template <sem::IsOrg T>
void addSubnodes(
    Vec<SemId<Org>>&          result,
    char const*               field,
    Vec<sem::SemId<T>> const& value) {
    rs::copy(
        value | rv::transform([](sem::SemId<T> const& id) {
            return id.asOrg();
        }),
        std::back_inserter(result));
}


template <typename T>
Vec<SemId<Org>> getDirectSubnodes(
    sem::SemId<T> node,
    CR<Opt<Str>>  targetField = std::nullopt) {
    Vec<SemId<Org>> result;
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;

    T const& object = *node.value;
    for_each_field_with_bases<T>([&](auto const& field) {
        if (!targetField.has_value()
            || targetField.value() == field.name) {
            addSubnodes(result, field.name, object.*field.pointer);
        }
    });

    return result;
}

Vec<SemId<Org>> getDirectSubnodes(
    sem::SemId<Org> node,
    CR<Opt<Str>>    targetField = std::nullopt) {
    switch (node->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        return getDirectSubnodes<sem::__Kind>(                            \
            node.as<sem::__Kind>(), targetField);                         \
    }


        EACH_SEM_ORG_KIND(_case);
#undef _case
    }
};


} // namespace


cctz::time_zone LoadTimeZone(CR<Str> name) {
    cctz::time_zone result;
    if (cctz::load_time_zone(name, &result)) {
        return result;
    } else {
        throw std::logic_error("Unknown time zone " + name);
    }
}

sem::SemId<Time> org::newSemTimeStatic(
    const UserTimeBreakdown& breakdown,
    bool                     isActive) {

    sem::SemId<Time> result = sem::SemId<Time>::New();
    result->isActive        = isActive;


    UserTime userTime{
        .time =            cctz::civil_second{
            breakdown.year.value_or(0),
            breakdown.month.value_or(0),
            breakdown.day.value_or(0),
            breakdown.hour.value_or(0),
            breakdown.minute.value_or(0),
            breakdown.second.value_or(0),
        },
        .zone = breakdown.zone ? LoadTimeZone(breakdown.zone.value())
                               : Opt<cctz::time_zone>{std::nullopt},
    };

    if (breakdown.second) {
        userTime.align = UserTime::Alignment::Second;
    } else if (breakdown.minute) {
        userTime.align = UserTime::Alignment::Minute;
    } else if (breakdown.hour) {
        userTime.align = UserTime::Alignment::Hour;
    } else if (breakdown.day) {
        userTime.align = UserTime::Alignment::Day;
    } else if (breakdown.month) {
        userTime.align = UserTime::Alignment::Month;
    } else if (breakdown.year) {
        userTime.align = UserTime::Alignment::Year;
    }

    {
        Time::Static s{};
        s.time       = userTime;
        result->time = s;
    }

    return result;
}

sem::SemId<Org> org::asOneNode(org::sem::SemId<org::sem::Org> const& arg) {
    switch (arg->getKind()) {
        case osk::StmtList:
        case osk::Document:
            LOGIC_ASSERTION_CHECK_FMT(
                arg.size() == 1,
                "`asOneNode` expects a node with a single nested element");
            return org::asOneNode(arg->at(0));
        default: return arg;
    }
}


int org::getListHeaderIndex(const sem::SemId<List>& it, CR<Str> text) {
    for (auto const& [idx, sub] : enumerate(it->subnodes)) {
        if (auto it = sub.asOpt<sem::ListItem>();
            it && it->isDescriptionItem()
            && it->getCleanHeader() == text) {
            return idx;
        }
    }

    return -1;
}

void org::setListItemBody(
    sem::SemId<sem::List> list,
    int                   index,
    Vec<sem::SemId<Org>>  value) {
    list->subnodes.at(index).as<sem::ListItem>()->subnodes = value;
}


void org::insertDescriptionListItem(
    sem::SemId<List>           id,
    int                        index,
    sem::SemId<sem::Paragraph> paragraph,
    Vec<sem::SemId<sem::Org>>  value) {
    auto item      = sem::SemId<sem::ListItem>::New();
    item->subnodes = value;
    item->header   = paragraph;
    id->subnodes.insert(id->subnodes.begin() + index, item);
}


void org::insertListItemBody(
    sem::SemId<List>     id,
    int                  index,
    Vec<sem::SemId<Org>> value) {
    auto item      = sem::SemId<sem::ListItem>::New();
    item->subnodes = value;
    id->subnodes.insert(id->subnodes.begin() + index, item);
}

void org::eachSubnodeRecSimplePath(
    SemId<Org>                       id,
    org::SemSubnodeVisitorSimplePath cb) {
    Func<void(sem::OrgArg, OrgVecArg path)> aux;

    aux = [&](sem::OrgArg node, OrgVecArg path) {
        cb(node, path);
        for (auto const& sub : node->getAllSubnodes()) {
            aux(sub, path + Vec<SemId<Org>>{node});
        }
    };

    aux(id, {});
}

AstTrackingMap org::getAstTrackingMap(const Vec<sem::SemId<Org>>& nodes) {
    AstTrackingMap res;

    for (auto const& node : nodes) {
        org::eachSubnodeRecSimplePath(
            node, [&](sem::OrgArg node, CR<Vec<SemId<Org>>> path) {
                auto add_string_tracking =
                    [&](UnorderedMap<Str, AstTrackingAlternatives>& map,
                        CR<Str>                                     key,
                        Vec<SemId<Org>> target) {
                        map.get_or_insert(key, AstTrackingAlternatives{})
                            .alternatives.push_back(
                                AstTrackingPath{.path = path + target});
                    };

                if (auto tree = node.asOpt<Subtree>()) {
                    if (auto id = tree->treeId) {
                        add_string_tracking(
                            res.subtrees, id.value(), {node});
                    }

                    for (auto const& radio :
                         getSubtreeProperties<sem::NamedProperty::RadioId>(
                             tree)) {
                        add_string_tracking(
                            res.radioTargets, radio.words.at(0), {node});
                    }

                    for (auto const& tag : org::getSubtreeProperties<
                             sem::NamedProperty::HashtagDef>(tree)) {
                        // only track fully resolved nodes, for node
                        // details see [[hashtag_track_set_minimization]]
                        for (auto const& hashtag :
                             tag.hashtag.getFlatHashes(false)) {
                            res.hashtagDefinitions
                                .get_or_insert(
                                    hashtag, AstTrackingAlternatives{})
                                .alternatives.push_back(
                                    AstTrackingPath{.path = path + node});
                        }
                    }

                } else if (auto par = node.asOpt<Paragraph>()) {
                    if (auto id = par->getFootnoteName()) {
                        add_string_tracking(
                            res.footnotes, id.value(), {par});
                    }

                    for (auto const& target :
                         par.subAs<sem::RadioTarget>()) {
                        add_string_tracking(
                            res.radioTargets,
                            target->words.at(0),
                            {par.asOrg(), target.asOrg()});
                    }
                }
            });
    }

    return res;
}

namespace {


struct RadioTargetSearchResult {
    Opt<AstTrackingGroup::RadioTarget> target;
    int                                nextGroupIdx{};
};

/// Mirror of the `tryRadioTargetSearch` implementation for immutable AST.
RadioTargetSearchResult tryRadioTargetSearch(
    auto const&         words,
    OrgVecArg           sub,
    CR<int>             groupingIdx,
    CR<AstTrackingPath> target) {
    // FIXME After this code is properly tested for both implementations I
    // might move it to the shared API in some form.
    int                     sourceOffset = 0;
    int                     radioOffset  = 0;
    RadioTargetSearchResult result;
    while (radioOffset < words.size()
           && (groupingIdx + sourceOffset) < sub.size()) {
        auto atSource   = sub.at(groupingIdx + sourceOffset);
        auto sourceWord = atSource->dyn_cast<sem::Leaf>();
        if (sourceWord == nullptr) {
            return result;
        } else if (sourceWord->text == words.at(radioOffset)) {
            if (radioOffset == (words.size() - 1)) {
                auto range = slice(
                    groupingIdx, groupingIdx + sourceOffset);
                result.target = AstTrackingGroup::RadioTarget{
                    .target = target,
                    .nodes  = Vec<SemIdOrg>{sub.at(range)}};
                result.nextGroupIdx = groupingIdx + sourceOffset;
                return result;
            } else {
                ++sourceOffset;
                ++radioOffset;
            }
        } else if (atSource->is(OrgSemKind::Space)) {
            ++sourceOffset;
        } else {
            return result;
        }
    }

    return result;
}

} // namespace

Vec<AstTrackingGroup> org::getSubnodeGroups(
    sem::SemId<Org>       node,
    const AstTrackingMap& map) {
    using G = AstTrackingGroup;
    Vec<G>      res;
    auto const& sub = node->subnodes;

    for (int idx = 0; idx < sub.size(); ++idx) {
        auto const& it = sub.at(idx);
        if (auto leaf = it->dyn_cast<sem::Leaf>();
            leaf != nullptr && !leaf->is(OrgSemKind::Space)) {
            auto radioTargets = map.radioTargets.find(leaf->text);
            if (radioTargets == map.radioTargets.end()) {
                res.push_back(G{G::Single{it}});
            } else {
                RadioTargetSearchResult search;
                for (CR<AstTrackingPath> alt :
                     radioTargets->second.alternatives) {
                    if (auto tree = alt.getNode().asOpt<Subtree>()) {
                        for (auto const& prop : org::getSubtreeProperties<
                                 sem::NamedProperty::RadioId>(tree)) {
                            search = tryRadioTargetSearch(
                                prop.words, sub, idx, alt);
                            if (search.target) { goto radio_search_exit; }
                        }
                    } else if (
                        auto target = alt.getNode().asOpt<RadioTarget>()) {
                        search = tryRadioTargetSearch(
                            target->words, sub, idx, alt);
                        if (search.target) { goto radio_search_exit; }
                    }
                }

            radio_search_exit:
                if (search.target) {
                    res.push_back(G{search.target.value()});
                    idx = search.nextGroupIdx;
                } else {
                    res.push_back(G{G::Single{it}});
                }
            }
        } else if (auto tag = it.asOpt<sem::HashTag>()) {
            G::TrackedHashtag rt;
            for (auto const& flat : tag->text.getFlatHashes(false)) {
                if (auto targets = map.hashtagDefinitions.get(flat)) {
                    for (auto const& target :
                         targets.value().alternatives) {
                        rt.targets.insert_or_assign(flat, target);
                    }
                }
            }

            if (rt.targets.empty()) {
                res.push_back(G{G::Single{.node = it}});
            } else {
                rt.tag = it;
                res.push_back(G{rt});
            }
        } else {
            res.push_back(G{G::Single{it}});
        }
    }

    return res;
}

std::shared_ptr<imm::ImmAstContext> org::initImmutableAstContext() {
    return imm::ImmAstContext::init_start_context();
}

hstd::Vec<sem::SemId<Org>> AstTrackingAlternatives::getAllNodes() const {
    return alternatives //
         | hstd::rv::transform(
               [](AstTrackingPath const& p) { return p.getNode(); })
         | hstd::rs::to<hstd::Vec>();
}
