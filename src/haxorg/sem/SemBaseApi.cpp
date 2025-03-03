#include "SemBaseApi.hpp"
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/sem/SemConvert.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <fstream>
#include <haxorg/sem/perfetto_org.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <haxorg/sem/SemOrgSerdeDeclarations.hpp>
#include <SemOrgProto.pb.h>

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

sem::SemId<sem::Document> org::parseFile(
    std::string               file,
    const OrgParseParameters& opts) {
    return parseStringOpts(readFile(fs::path{file}), opts);
}

sem::SemId<sem::Document> org::parseString(std::string text) {
    return parseStringOpts(text, OrgParseParameters{});
}

sem::SemId<sem::Document> org::parseStringOpts(
    const std::string         text,
    OrgParseParameters const& opts) {
    org::parse::LexerParams p;
    SPtr<std::ofstream>     fileTrace;
    if (opts.baseTokenTracePath) {
        fileTrace = std::make_shared<std::ofstream>(
            *opts.baseTokenTracePath);
    }
    p.traceStream                        = fileTrace.get();
    org::parse::OrgTokenGroup baseTokens = org::parse::tokenize(
        text.data(), text.size(), p);
    org::parse::OrgTokenGroup tokens;
    org::parse::OrgTokenizer  tokenizer{&tokens};

    if (opts.tokenTracePath) {
        tokenizer.setTraceFile(*opts.tokenTracePath);
    }

    tokenizer.convert(baseTokens);
    org::parse::Lexer<OrgTokenKind, org::parse::OrgFill> lex{&tokens};

    org::parse::OrgNodeGroup nodes{&tokens};
    org::parse::OrgParser    parser{&nodes};
    if (opts.parseTracePath) { parser.setTraceFile(*opts.parseTracePath); }

    (void)parser.parseFull(lex);

    sem::OrgConverter converter{};
    if (opts.semTracePath) { converter.setTraceFile(*opts.semTracePath); }

    return converter.toDocument(
        org::parse::OrgAdapter(&nodes, org::parse::OrgId(0)));
}


namespace {

struct DirectoryParseState {
    UnorderedSet<std::string> visited;
};

void postProcessFileReferences(
    fs::path const&                    path,
    fs::path const&                    activeRoot,
    sem::OrgArg                        parsed,
    const OrgDirectoryParseParameters& opts,
    DirectoryParseState&               state);

Opt<sem::SemId<sem::File>> parseFileAux(
    fs::path const&                    path,
    fs::path const&                    activeRoot,
    const OrgDirectoryParseParameters& opts,
    DirectoryParseState&               state) {
    LOGIC_ASSERTION_CHECK(
        fs::is_regular_file(path),
        "'{}' should be a regular text file",
        path);

    auto parsed = opts.getParsedNode
                    ? opts.getParsedNode(path)
                    : org::parseFile(
                          path.native(), org::OrgParseParameters{});

    if (parsed.isNil()) { return std::nullopt; }
    postProcessFileReferences(path, activeRoot, parsed, opts, state);

    sem::SemId<File> file = sem::SemId<File>::New();
    file->relPath         = fs::relative(path, activeRoot).native();
    file->absPath         = path.native();
    file->push_back(parsed);
    return file;
}

Opt<sem::SemId<Org>> parsePathAux(
    fs::path const&                    path,
    fs::path const&                    activeRoot,
    const OrgDirectoryParseParameters& opts,
    DirectoryParseState&               state) {
    if (state.visited.contains(path.native())) { return std::nullopt; }
    state.visited.incl(path.native());

    if (opts.shouldProcessPath && !opts.shouldProcessPath(path)) {
        return std::nullopt;
    } else if (fs::is_symlink(path)) {
        auto target = fs::read_symlink(path);
        LOG(INFO) << fmt("Symlink '{}' targets '{}'", path, target);
        sem::SemId<sem::Symlink> sym = sem::SemId<sem::Symlink>::New();
        if (fs::is_directory(target)) {
            sym->isDirectory = true;
            sym->absPath     = target.native();
            auto dir         = parsePathAux(
                target, sym->absPath.toBase(), opts, state);
            if (dir) { sym->push_back(dir.value()); }

        } else if (fs::is_regular_file(target)) {
            sym->absPath = target.parent_path().native();
            auto file    = parsePathAux(
                target, sym->absPath.toBase(), opts, state);
            if (file) { sym->push_back(file.value()); }
        } else {
            logic_todo_impl();
        }

        return sym;

    } else if (fs::is_directory(path)) {
        sem::SemId<Directory> dir = sem::SemId<Directory>::New();
        dir->relPath = fs::relative(path, activeRoot).native();
        dir->absPath = path.native();
        for (const auto& entry : fs::directory_iterator(path)) {
            auto nested = parsePathAux(entry, activeRoot, opts, state);
            if (nested) { dir->push_back(nested.value()); }
        }

        return dir;
    } else if (fs::is_regular_file(path)) {
        if (normalize(path.extension().native()) == "org") {
            return parseFileAux(path, activeRoot, opts, state);
        } else {
            return std::nullopt;
        }

    } else {
        return std::nullopt;
    }
}

Opt<fs::path> resolvePath(
    fs::path const&                    workdir,
    CR<Str>                            target,
    const OrgDirectoryParseParameters& opts) {
    LOGIC_ASSERTION_CHECK(
        fs::is_directory(workdir),
        "Workdir must be a directory, but got '{}'",
        workdir);

    fs::path full //
        = fs::path{target.toBase()}.is_absolute()
            ? fs::path{target.toBase()}
            : (workdir / target.toBase());

    if (!fs::exists(full) && opts.findIncludeTarget) {
        auto includeFound = opts.findIncludeTarget(target);
        if (includeFound) { full = includeFound.value(); }
    }

    if (fs::exists(full)) {
        return full;
    } else {
        return std::nullopt;
    }
}

void postProcessInclude(
    sem::SemId<sem::Org>               arg,
    fs::path const&                    filePath,
    fs::path const&                    activeRoot,
    sem::OrgArg                        parsed,
    const OrgDirectoryParseParameters& opts,
    DirectoryParseState&               state) {
    auto incl = arg.as<sem::CmdInclude>();
    auto full = resolvePath(filePath.parent_path(), incl->path, opts);

    if (full) {
        switch (incl->getIncludeKind()) {
            case sem::CmdInclude::Kind::OrgDocument: {
                auto parsed = parsePathAux(
                    full.value(), activeRoot, opts, state);
                if (parsed) { arg->push_back(parsed.value()); }
                break;
            }
            case sem::CmdInclude::Kind::Src: {
                LOGIC_ASSERTION_CHECK(
                    incl.at(0)->is(OrgSemKind::BlockCode), "");

                auto code   = incl.as<sem::BlockCode>();
                auto source = readFile(full.value());
                for (auto const& line : split(source, '\n')) {
                    sem::BlockCodeLine lineNode;
                    lineNode.parts.push_back(sem::BlockCodeLine::Part{
                        sem::BlockCodeLine::Part::Raw{.code = line}});
                    code->lines.push_back(lineNode);
                }
                break;
            }
            case sem::CmdInclude::Kind::Example: {
                LOGIC_ASSERTION_CHECK(
                    incl.at(0)->is(OrgSemKind::BlockExample), "");

                auto code   = incl.as<sem::BlockExample>();
                auto source = readFile(full.value());
                for (auto const& line : split(source, '\n')) {
                    auto raw  = sem::SemId<sem::RawText>();
                    raw->text = line;
                    code->push_back(raw);
                }
                break;
            }
            case sem::CmdInclude::Kind::Export: {
                LOGIC_ASSERTION_CHECK(
                    incl.at(0)->is(OrgSemKind::BlockExport), "");

                auto code     = incl.as<sem::BlockExport>();
                code->content = readFile(full.value());
                break;
            }
        }
    } else {
        auto group     = sem::SemId<sem::ErrorGroup>::New();
        auto error     = sem::SemId<sem::ErrorItem>::New();
        error->message = fmt(
            "Could not resolve include target '{}' from working file '{}'",
            incl->path,
            filePath);
        arg->push_back(error);
    }
}

void postProcessFileLink(
    sem::SemId<sem::Org>               arg,
    fs::path const&                    documentPath,
    fs::path const&                    activeRoot,
    sem::OrgArg                        parsed,
    const OrgDirectoryParseParameters& opts,
    DirectoryParseState&               state) {
    auto link = arg.as<sem::Link>();
    auto t    = link->target;
    switch (t.getKind()) {
        case sem::LinkTarget::Kind::Attachment:
        case sem::LinkTarget::Kind::File: {
            Str target;
            if (t.isFile()) {
                target = t.getFile().file;
            } else if (t.isAttachment()) {
                target = t.getAttachment().file;
            }

            auto full = resolvePath(
                documentPath.parent_path(), target, opts);
            if (full) {
                auto file     = sem::SemId<sem::File>::New();
                file->relPath = fs::relative(full.value(), activeRoot)
                                    .native();
                file->absPath = full.value().native();
                link->push_back(file);
            }
            break;
        }
        default: {
        }
    }
}

void postProcessFileReferences(
    fs::path const&                    path,
    fs::path const&                    activeRoot,
    sem::OrgArg                        parsed,
    const OrgDirectoryParseParameters& opts,
    DirectoryParseState&               state) {
    org::eachSubnodeRec(parsed, [&](sem::SemId<sem::Org> arg) {
        if (auto incl = arg.asOpt<sem::CmdInclude>()) {
            postProcessInclude(arg, path, activeRoot, parsed, opts, state);
        } else if (auto link = arg.asOpt<sem::Link>()) {
            postProcessFileLink(
                arg, path, activeRoot, parsed, opts, state);
        }
    });
}
} // namespace


Opt<sem::SemId<Org>> org::parseDirectoryOpts(
    const std::string&                 root,
    const OrgDirectoryParseParameters& opts) {

    DirectoryParseState state;
    return parsePathAux(fs::absolute(root), root, opts, state);
}

sem::SemId<File> org::parseFileWithIncludes(
    const std::string&                 file,
    const OrgDirectoryParseParameters& opts) {
    DirectoryParseState state;
    auto                parsed = parseFileAux(
        file, fs::path{file}.parent_path(), opts, state);
    if (parsed) {
        return parsed.value();
    } else {
        return sem::SemId<sem::File>::New();
    }
}


sem::SemId<sem::Document> org::readProtobufFile(const std::string& file) {
    sem::SemId        read_node = sem::SemId<sem::Org>::Nil();
    std::ifstream     stream{file};
    orgproto::AnyNode result;
    result.ParseFromIstream(&stream);
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        org::algo::proto_write_accessor<sem::SemId<sem::Org>>::for_ref(
            read_node));
    return read_node.as<sem::Document>();
}

void org::exportToProtobufFile(
    sem::SemId<sem::Document> doc,
    const std::string&        file) {
    std::ofstream     stream{file};
    orgproto::AnyNode result;
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        &result, doc.asOrg());
    result.SerializeToOstream(&stream);
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


absl::TimeZone LoadTimeZone(CR<Str> name) {
    absl::TimeZone result;
    if (absl::LoadTimeZone(name, &result)) {
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
        .time = absl::FromCivil(
            absl::CivilSecond{
                breakdown.year.value_or(0),
                breakdown.month.value_or(0),
                breakdown.day.value_or(0),
                breakdown.hour.value_or(0),
                breakdown.minute.value_or(0),
                breakdown.second.value_or(0),
            },
            absl::UTCTimeZone()),
        .zone = breakdown.zone ? LoadTimeZone(breakdown.zone.value())
                               : Opt<absl::TimeZone>{std::nullopt},
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

    result->time = Time::Static{.time = userTime};

    return result;
}

sem::SemId<Org> org::asOneNode(OrgArg arg) {
    switch (arg->getKind()) {
        case osk::StmtList:
        case osk::Document:
            LOGIC_ASSERTION_CHECK(
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

void org::setDescriptionListItemBody(
    sem::SemId<List>     list,
    CR<Str>              text,
    Vec<sem::SemId<Org>> value) {
    int idx = getListHeaderIndex(list, text);
    if (idx == -1) {
        auto key = parseString(text);
        auto par = asOneNode(key);
        insertDescriptionListItem(
            list, list.size(), par.as<sem::Paragraph>(), value);
    } else {
        setListItemBody(list, idx, value);
    }
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
    int                                nextGroupIdx;
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

namespace {
sem::SemId<Org> convertOutput(
    sem::OrgCodeEvalOutput const& out,
    sem::OrgCodeEvalInput const&  in,
    const OrgCodeEvalParameters&  conf) {
    conf.debug.message(fmt("Parsing stdout {}", out.stdout));
    auto doc  = org::parseString(out.stdout);
    auto stmt = sem::SemId<sem::StmtList>::New();
    for (auto const& node : doc) {
        conf.debug.message(fmt("Result node {}", node->getKind()));
        stmt->subnodes.push_back(node);
    }
    return stmt;
}

sem::OrgCodeEvalInput convertInput(
    imm::ImmAdapterT<imm::ImmBlockCode> block) {
    sem::OrgCodeEvalInput input;
    input.language = block->lang.get().value();

    using I = sem::OrgCodeEvalInput;

    input.resultHandling = I::ResultHandling::Replace;
    input.resultType     = I::ResultType::Scalar;

    for (auto const& res : block.getAttrs("results")) {
        auto norm = normalize(res.getString());
        if (norm == "table" || norm == "vector") {
            input.resultType = I::ResultType::Table;
        } else if (norm == "list") {
            input.resultType = I::ResultType::List;
        } else if (norm == "scalar" || norm == "verbatim") {
            input.resultType = I::ResultType::Scalar;
        } else if (norm == "file") {
            input.resultType = I ::ResultType::SaveFile;
        } else if (norm == "raw") {
            input.resultFormat = I::ResultFormat::Raw;
        } else if (norm == "code") {
            input.resultFormat = I::ResultFormat::Code;
        } else if (norm == "drawer") {
            input.resultFormat = I::ResultFormat::Drawer;
        } else if (norm == "html") {
            input.resultFormat = I::ResultFormat::ExportType;
            input.exportType   = "html";
        } else if (norm == "latex") {
            input.resultFormat = I::ResultFormat::ExportType;
            input.exportType   = "latex";
        } else if (norm == "link" || norm == "graphics") {
            input.resultFormat = I::ResultFormat::Link;
        } else if (norm == "org") {
            input.resultFormat = I::ResultFormat::Code;
            input.exportType   = "org";
        } else if (norm == "pp") {
            input.resultFormat = I::ResultFormat::Code;
        } else if (norm == "replace") {
            input.resultHandling = I::ResultHandling::Replace;
        } else if (norm == "silent") {
            input.resultHandling = I::ResultHandling::Silent;
        } else if (norm == "none") {
            input.resultHandling = I::ResultHandling::None;
        } else if (norm == "discard") {
            input.resultHandling = I::ResultHandling::Discard;
        } else if (norm == "append") {
            input.resultHandling = I::ResultHandling::Append;
        } else if (norm == "prepend") {
            input.resultHandling = I::ResultHandling::Prepend;
        }
    }

    if (auto attr = block.getFirstAttr("result-export-language")) {
        input.exportType = attr->getString();
    }

    if (auto attr = block.getFirstAttr("result-code-language")) {
        input.exportType = attr->getString();
    }

    return input;
}

} // namespace

sem::SemId<Org> org::evaluateCodeBlocks(
    sem::SemId<sem::Org>         document,
    const OrgCodeEvalParameters& conf) {
    auto imm_context = imm::ImmAstContext::init_start_context();
    // imm_context->debug->setTraceFile("/tmp/evaluateCodeBlocks.log");
    auto version = imm_context->init(document);

    auto& d = conf.debug;

#define EVAL_TRACE(msg)                                                   \
    if (d.TraceState) { d.message(msg); }

    Vec<imm::ImmUniqId> codeBlockPaths;
    org::eachSubnodeRec(
        version.getRootAdapter(),
        true,
        [&](imm::ImmAdapter const& adapter) {
            if (adapter.is(OrgSemKind::BlockCode)) {
                codeBlockPaths.push_back(adapter.uniq());
            }
        });

    Vec<imm::ImmAstVersion> history;
    if (d.TraceState) { history.push_back(version); }

    auto set_output = [&](sem::OrgCodeEvalOutput const& out,
                          sem::OrgCodeEvalInput const&  input,
                          imm::ImmUniqId const&         block,
                          sem::SemId<sem::Org>          node) {
        auto target_id = block.update(version.context->at(block.path));
        auto target    = version.context->adapt(target_id);
        auto result    = sem::SemId<sem::BlockCodeEvalResult>::New();

        result->raw  = out;
        result->node = node;

        version = version.getEditVersion(
            [&](imm::ImmAstContext::Ptr ast,
                imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
                auto id = ast->add(result, ctx)
                              .as<imm::ImmBlockCodeEvalResult>();

                if (id == target_id.id) {
                    EVAL_TRACE("No changes in the code eval");
                    return imm::ImmAstReplaceGroup{};
                } else {
                    EVAL_TRACE(
                        fmt("Updating AST with new eval result, target "
                            "{}, result handling {} result format {} new "
                            "node {}",
                            target.uniq(),
                            input.resultHandling,
                            input.resultFormat,
                            id));
                    return ctx.store().updateNode<imm::ImmBlockCode>(
                        target, ctx, [&](imm::ImmBlockCode code) {
                            using RH = sem::OrgCodeEvalInput::
                                ResultHandling;
                            switch (input.resultHandling) {
                                case RH::Append:
                                    code.result = code.result.push_back(
                                        id);
                                    break;
                                case RH::Prepend:
                                    code.result = code.result.insert(
                                        0, id);
                                    break;
                                case RH::Replace:
                                    code.result = {id};
                                    break;
                                case RH::Discard: break;
                                case RH::Silent:
                                case RH::None:
                                    // TODO
                                    break;
                            }

                            return code;
                        });
                }
            });

        if (d.TraceState) { history.push_back(version); }
    };

    for (auto const& block : codeBlockPaths) {
        auto adapter = version.context->adapt(block)
                           .as<imm::ImmBlockCode>();
        EVAL_TRACE(
            fmt("Evaluating language '{}' at {}",
                adapter->lang,
                adapter->loc));

        auto __scope = conf.debug.scopeLevel();
        auto input   = convertInput(adapter);
        auto output  = conf.evalBlock(input);

        if (!output.stderr.empty()) {
            EVAL_TRACE(fmt("stderr:\n{}", output.stderr));
        }

        if (!output.stdout.empty()) {
            EVAL_TRACE(fmt("stdout:\n{}", output.stdout));
        }

        set_output(
            output, input, block, convertOutput(output, input, conf));
    }

    if (d.TraceState) {
        auto graph = org::imm::toGraphviz(history);
        graph.render("/tmp/CodeBlockEvalGraph.png");
    }

    EVAL_TRACE(fmt(
        "Converting final root result {} back to sem", version.getRoot()));
    return org::imm::sem_from_immer(version.getRoot(), *version.context);
}
