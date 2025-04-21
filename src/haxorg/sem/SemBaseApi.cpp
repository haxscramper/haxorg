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
#if ORG_DEPS_USE_PROTOBUF && !ORG_EMCC_BUILD
#    include <SemOrgProto.pb.h>
#endif

using namespace org::sem;
using namespace org;
using namespace hstd;
using osk = OrgSemKind;

hstd::Vec<org::OrgParseFragment> org::extractCommentBlocks(
    const std::string&            text,
    const hstd::Vec<std::string>& commentPrefixes) {

    Vec<OrgParseFragment> fragments;
    Vec<std::string>      lines;
    std::istringstream    stream(text);
    std::string           line;

    while (std::getline(stream, line)) { lines.push_back(line); }

    OrgParseFragment currentFragment{-1, -1, ""};

    for (size_t lineIdx = 0; lineIdx < lines.size(); ++lineIdx) {
        const std::string& currentLine  = lines[lineIdx];
        bool               foundComment = false;
        size_t             commentPos   = std::string::npos;
        std::string        matchedPrefix;

        for (const auto& prefix : commentPrefixes) {
            size_t pos = currentLine.find(prefix);
            if (pos != std::string::npos
                && (commentPos == std::string::npos || pos < commentPos)) {
                commentPos    = pos;
                matchedPrefix = prefix;
                foundComment  = true;
            }
        }

        if (foundComment) {
            std::string commentText = currentLine.substr(
                commentPos + matchedPrefix.length());

            // Check if this is a continuation of the previous comment
            // block
            if (currentFragment.baseLine != -1) {
                // Add the new comment text to the existing fragment
                currentFragment.text += "\n" + commentText;
            } else {
                // Start a new comment fragment
                currentFragment = {
                    static_cast<int>(lineIdx),
                    static_cast<int>(commentPos),
                    commentText};
            }
        } else if (currentFragment.baseLine != -1) {
            // No comment on this line, so the previous comment block is
            // complete
            fragments.push_back(currentFragment);
            currentFragment = {-1, -1, ""};
        }
    }

    // Add the last fragment if it exists
    if (currentFragment.baseLine != -1) {
        fragments.push_back(currentFragment);
    }

    // Process the fragments to clean up the text
    for (auto& fragment : fragments) {
        std::istringstream fragmentStream(fragment.text);
        std::string        processedText;
        std::string        fragmentLine;
        bool               isFirstLine = true;

        while (std::getline(fragmentStream, fragmentLine)) {
            if (!isFirstLine) { processedText += "\n"; }

            // For lines after the first, check if they start with a
            // comment prefix
            if (!isFirstLine) {
                for (const auto& prefix : commentPrefixes) {
                    size_t pos = fragmentLine.find(prefix);
                    if (pos != std::string::npos
                        && pos == fragmentLine.find_first_not_of(" \t")) {
                        fragmentLine = fragmentLine.substr(
                            pos + prefix.length());
                        break;
                    }
                }
            }

            // Remove at most one leading space if it exists
            if (!fragmentLine.empty() && fragmentLine[0] == ' ') {
                fragmentLine = fragmentLine.substr(1);
            }

            processedText += fragmentLine;
            isFirstLine = false;
        }

        fragment.text = processedText;
    }

    return fragments;
}

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

sem::SemId<sem::Org> org::parseFile(
    std::string               file,
    const OrgParseParameters& opts) {
    return parseStringOpts(readFile(fs::path{file}), opts);
}

sem::SemId<sem::Org> org::parseString(std::string text) {
    return parseStringOpts(text, OrgParseParameters{});
}

sem::SemId<sem::Org> org::parseStringOpts(
    const std::string         text,
    OrgParseParameters const& opts) {


    if (opts.getFragments) {
        auto                          fragments = opts.getFragments(text);
        Vec<OrgConverter::InFragment> toConvert;

        if (opts.baseTokenTracePath) {
            fs::remove(opts.baseTokenTracePath.value());
        }

        if (opts.parseTracePath) {
            fs::remove(opts.parseTracePath.value());
        }

        if (opts.semTracePath) { fs::remove(opts.semTracePath.value()); }

        if (opts.tokenTracePath) {
            fs::remove(opts.tokenTracePath.value());
        }

        Vec<org::parse::OrgTokenGroup> tokens;
        Vec<org::parse::OrgNodeGroup>  nodes;
        nodes.reserve(fragments.size());
        tokens.reserve(fragments.size());

        for (auto const& frag : fragments) {
            tokens.emplace_back();
            nodes.emplace_back(&tokens.back());
        }

        for (int i = 0; i < fragments.size(); ++i) {
            auto const&             frag = fragments.at(i);
            org::parse::LexerParams p;
            SPtr<std::ofstream>     fileTrace;
            if (opts.baseTokenTracePath) {
                p.setTraceFile(opts.baseTokenTracePath.value());
            }

            org::parse::OrgTokenGroup baseTokens = org::parse::tokenize(
                frag.text, p);
            org::parse::OrgTokenizer tokenizer{&tokens.at(i)};

            if (opts.tokenTracePath) {
                tokenizer.setTraceFile(*opts.tokenTracePath, false);
                tokenizer.traceColored = false;
            }

            tokenizer.convert(baseTokens);
            org::parse::Lexer<OrgTokenKind, org::parse::OrgFill> lex{
                &tokens.at(i)};

            org::parse::OrgParser parser{&nodes.at(i)};
            if (opts.parseTracePath) {
                parser.setTraceFile(*opts.parseTracePath, false);
                parser.traceColored = false;
            }

            auto id      = parser.parseFull(lex);
            auto adapter = org::parse::OrgAdapter(&nodes.at(i), id);

            // adapter.tr

            toConvert.push_back(OrgConverter::InFragment{
                .baseLine = frag.baseLine,
                .baseCol  = frag.baseCol,
                .node     = adapter,
            });
        }

        sem::OrgConverter converter{};
        if (opts.semTracePath) {
            converter.setTraceFile(*opts.semTracePath);
            converter.traceColored = false;
        }

        return converter.convertDocumentFragments(toConvert).unwrap();

    } else {


        org::parse::LexerParams p;
        SPtr<std::ofstream>     fileTrace;
        if (opts.baseTokenTracePath) {
            p.setTraceFile(opts.baseTokenTracePath.value());
        }

        org::parse::OrgTokenGroup baseTokens = org::parse::tokenize(
            text, p);

        org::parse::OrgTokenGroup tokens;
        org::parse::OrgTokenizer  tokenizer{&tokens};

        if (opts.tokenTracePath) {
            tokenizer.setTraceFile(*opts.tokenTracePath);
        }

        tokenizer.convert(baseTokens);
        org::parse::Lexer<OrgTokenKind, org::parse::OrgFill> lex{&tokens};

        org::parse::OrgNodeGroup nodes{&tokens};
        org::parse::OrgParser    parser{&nodes};
        if (opts.parseTracePath) {
            parser.setTraceFile(*opts.parseTracePath);
        }

        auto              id = parser.parseFull(lex);
        sem::OrgConverter converter{};
        if (opts.semTracePath) {
            converter.setTraceFile(*opts.semTracePath);
        }

        return converter
            .convertDocument(org::parse::OrgAdapter(&nodes, id))
            .unwrap();
    }
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
        if (fs::is_directory(target)) {
            sem::SemId<sem::Symlink> sym = sem::SemId<sem::Symlink>::New();
            sym->isDirectory             = true;
            sym->absPath                 = target.native();
            auto dir                     = parsePathAux(
                target, sym->absPath.toBase(), opts, state);
            if (dir) { sym->push_back(dir.value()); }
            return sym;

        } else if (fs::is_regular_file(target)) {
            sem::SemId<sem::Symlink> sym = sem::SemId<sem::Symlink>::New();
            sym->absPath                 = target.parent_path().native();
            auto file                    = parsePathAux(
                target, sym->absPath.toBase(), opts, state);
            if (file) { sym->push_back(file.value()); }
            return sym;
        } else {
            return std::nullopt;
        }


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
#if ORG_DEPS_USE_PROTOBUF && !ORG_EMCC_BUILD
    sem::SemId        read_node = sem::SemId<sem::Org>::Nil();
    std::ifstream     stream{file};
    orgproto::AnyNode result;
    result.ParseFromIstream(&stream);
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        org::algo::proto_write_accessor<sem::SemId<sem::Org>>::for_ref(
            read_node));
    return read_node.as<sem::Document>();
#elif ORG_EMCC_BUILD
    throw std::logic_error(
        "Protobuf file parsing is not supported for wasm");
#else
    throw std::logic_error(
        "haxorg was not compiled with protobuf support. Enable "
        "`ORG_DEPS_USE_PROTOBUF` and rebuild to enable protobuf serde.");
#endif
}

void org::exportToProtobufFile(
    sem::SemId<sem::Document> doc,
    const std::string&        file) {
#if ORG_DEPS_USE_PROTOBUF && !ORG_EMCC_BUILD
    std::ofstream     stream{file};
    orgproto::AnyNode result;
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        &result, doc.asOrg());
    result.SerializeToOstream(&stream);
#elif ORG_EMCC_BUILD
    throw std::logic_error(
        "Protobuf file writing is not supported for wasm");
#else
    throw std::logic_error(
        "haxorg was not compiled with protobuf support. Enable "
        "`ORG_DEPS_USE_PROTOBUF` and rebuild to enable protobuf serde.");
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

sem::SemId<Org> org::asOneNode(org::sem::SemId<org::sem::Org> const& arg) {
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

json sliceJson(
    const json&                                    input,
    const Vec<org::sem::AttrValue::DimensionSpan>& spans) {
    if (!input.is_array()) {
        throw std::invalid_argument("Input JSON must be an array");
    }

    if (spans.empty()) { return input; }

    std::vector<size_t> dimensions;
    auto                current = &input;
    while (current->is_array() && !current->empty()) {
        dimensions.push_back(current->size());
        current = &(*current)[0];
    }

    if (spans.size() > dimensions.size()) {
        throw std::invalid_argument(
            "More spans provided than dimensions in input");
    }

    std::vector<std::vector<int>> indices(spans.size());
    for (size_t i = 0; i < spans.size(); ++i) {
        const auto& span     = spans[i];
        int         dim_size = static_cast<int>(dimensions[i]);

        int first = span.first;
        if (first < 0) { first = dim_size + first; }
        if (first < 0 || first >= dim_size) {
            throw std::out_of_range("Span first index out of bounds");
        }

        int last = span.last.has_value() ? span.last.value() : first;
        if (last < 0) { last = dim_size + last; }
        if (last < 0 || last >= dim_size || last < first) {
            throw std::out_of_range("Span last index out of bounds");
        }

        for (int idx = first; idx <= last; ++idx) {
            indices[i].push_back(idx);
        }
    }

    std::function<json(const json&, size_t, const std::vector<int>&)>
        sliceRecursive;
    sliceRecursive = [&](const json&             arr,
                         size_t                  dim,
                         const std::vector<int>& path) -> json {
        if (dim == indices.size()) {
            const json* value = &arr;
            for (int idx : path) { value = &(*value)[idx]; }
            return *value;
        }

        json result = json::array();
        for (int idx : indices[dim]) {
            std::vector<int> newPath = path;
            newPath.push_back(idx);

            if (dim == indices.size() - 1) {
                result.push_back(sliceRecursive(arr, dim + 1, newPath));
            } else {
                json subArray = sliceRecursive(arr, dim + 1, newPath);
                result.push_back(subArray);
            }
        }
        return result;
    };

    return sliceRecursive(input, 0, {});
}

struct EvalContext {
    OrgCodeEvalParameters const& conf;
    imm::ImmAstVersion           version;
    Vec<imm::ImmAstVersion>      history;
    UnorderedMap<Str, json>      namedResults;

    imm::ImmAstContext::Ptr getContext() const { return version.context; }
    hstd::SPtr<imm::ImmAstTrackingMap> getTrack() const {
        return getContext()->currentTrack;
    }

    bool isTraceEnabled() const {
        return conf.debug && conf.debug->TraceState;
    }


#define EVAL_TRACE(msg)                                                   \
    if (isTraceEnabled()) { conf.debug->message(msg); }


#define EVAL_SCOPE()                                                      \
    auto CONCAT(__scope, __COUNTER__) = isTraceEnabled()                  \
                                          ? conf.debug->scopeLevel()      \
                                          : finally_std::nop();

    Opt<json> getTargetValue(imm::ImmId const& target_id, bool asFlatText)
        const {
        auto target = getContext()->adaptUnrooted(target_id);
        EVAL_TRACE(fmt("Target node is {}", target));
        EVAL_SCOPE();
        Opt<json> result;

        target.visitNodeValue(overloaded{
            [&](imm::ImmStmtList const& list) {
                json out = json::array();
                for (auto const& it : list) {
                    auto nested = getTargetValue(it, asFlatText);
                    if (nested) { out.push_back(nested.value()); }
                }

                if (out.size() == 0) {
                    result = std::nullopt;
                } else if (out.size() == 1) {
                    result = out.at(0);
                } else {
                    result = out;
                }
            },
            [&](imm::ImmTable const& t) {
                json out_table = json::array();
                for (auto const& row : t.rows) {
                    json out_row = json::array();
                    EVAL_TRACE(fmt("Row {}", row));
                    EVAL_SCOPE();
                    for (auto const& cell : getContext()
                                                ->adaptUnrooted(row)
                                                .as<imm::ImmRow>()
                                                ->cells) {
                        EVAL_TRACE(fmt("Cell {}", cell));
                        if (asFlatText) {
                            out_row.push_back(getCleanText(
                                getContext()->adaptUnrooted(cell)));
                        } else {
                            auto cell_sem = org::imm::sem_from_immer(
                                cell, *getContext());
                            auto json_res = algo::ExporterJson::toJson(
                                cell_sem);
                            out_row.push_back(json_res);
                        }
                    }
                    out_table.push_back(out_row);
                }
                result = out_table;
            },
            [&](imm::ImmBlockCode const& code) {
                if (code.result.empty()) {
                    EVAL_TRACE(
                        "Target code block was not evaluated, no result "
                        "field");
                } else {
                    auto value = getContext()
                                     ->adaptUnrooted(code.result.back())
                                     .as<imm::ImmBlockCodeEvalResult>();
                    EVAL_TRACE(
                        fmt("Target code block evaluated to {}", value));
                    // EVAL_TRACE()
                    result = getTargetValue(value->node, asFlatText);
                }
            },
            [&](auto const&) {},
        });

        return result;
    }

    Opt<json> getAttrValue(sem::AttrValue const& attr) const {
        EVAL_TRACE(fmt("Resolving attribute value to state {}", attr));
        EVAL_SCOPE();
        Str  name = attr.getString();
        auto node = getTrack()->names.get(name);
        if (!node) {
            EVAL_TRACE("No named nodes with the value");
            return std::nullopt;
        }
        auto paths = getContext()->getPathsFor(node.value());
        LOGIC_ASSERTION_CHECK(
            !paths.empty(), "Logic block {} has no paths", node.value());
        Opt<json> result = getTargetValue(paths.front().id, true);


        if (result) { result = sliceJson(result.value(), attr.span); }

        return result;
    }


    struct CallParams {
        imm::ImmAdapterT<imm::ImmBlockCode> block;
        Opt<org::sem::AttrGroup>            callsiteVars;
        Opt<org::sem::AttrGroup>            callsiteHeaderArgs;
    };

    CallParams getTargetBlock(imm::ImmAdapter const& adapter) {
        EVAL_SCOPE();
        CallParams res;
        if (adapter.is(OrgSemKind::BlockCode)) {
            res.block = adapter.as<imm::ImmBlockCode>();
        } else {
            auto command = adapter.as<imm::ImmCmdCall>();
            EVAL_TRACE(fmt(
                "Getting target code block for name '{}'", command->name));
            res.callsiteVars       = command->callAttrs;
            res.callsiteHeaderArgs = command->insideHeaderAttrs;
            if (auto opt_block = getTrack()->names.get(command->name)) {
                if (!opt_block->is(OrgSemKind::BlockCode)) {
                    EVAL_TRACE(
                        fmt("Name '{}' does not refer to a code block",
                            command->name));
                }

                auto paths = getContext()->getPathsFor(opt_block.value());
                LOGIC_ASSERTION_CHECK(
                    !paths.empty(),
                    "Logic block {} has no paths",
                    opt_block.value());
                res.block = getContext()
                                ->adapt(paths.front())
                                .as<imm::ImmBlockCode>();
            } else {
                EVAL_TRACE(
                    fmt("Name '{}' does not refer to a known document "
                        "entry",
                        command->name));
            }
        }


        return res;
    }

    sem::SemId<Org> convertOutput(
        sem::OrgCodeEvalOutput const& out,
        sem::OrgCodeEvalInput const&  in,
        const OrgCodeEvalParameters&  conf) {
        EVAL_SCOPE();
        EVAL_TRACE(fmt("Parsing stdout"));
        auto doc  = org::parseString(out.stdoutText);
        auto stmt = sem::SemId<sem::StmtList>::New();
        for (auto const& node : doc) {
            EVAL_TRACE(fmt("Result node {}", node->getKind()));
            stmt->subnodes.push_back(node);
        }
        return stmt;
    }

    sem::OrgCodeEvalInput convertInput(CallParams const& res) {
        EVAL_SCOPE();
        sem::OrgCodeEvalInput input;
        input.language = res.block->lang.get().value();

        using I = sem::OrgCodeEvalInput;

        input.resultHandling = I::ResultHandling::Replace;
        input.resultType     = I::ResultType::Scalar;


        Vec<Str> buf;
        for (auto const& line : res.block->lines) {
            buf.push_back("");
            for (auto const& part : line.parts) {
                using K = sem::BlockCodeLine::Part::Kind;
                switch (part.getKind()) {
                    case K::Raw: {
                        buf.back().append(part.getRaw().code);
                        break;
                    }
                    case K::Callout: {
                        // callouts are explicitly skipped
                        break;
                    }
                    case K::Tangle: {
                        logic_todo_impl();
                        break;
                    }
                }
            }
        }

        input.tangledCode = join("\n", buf);

        for (auto const& res : res.block.getAttrs("results")) {
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

        if (auto attr = res.block.getFirstAttr("result-export-language")) {
            input.exportType = attr->getString();
        }

        if (auto attr = res.block.getFirstAttr("result-code-language")) {
            input.exportType = attr->getString();
        }

        UnorderedMap<Str, sem::AttrValue> byVarname;
        if (auto default_vars = res.block->attrs.getNamed("var")) {
            for (auto const& var : default_vars->items) {
                EVAL_TRACE(fmt("Default variable {}", var));
                byVarname.insert_or_assign(var.varname.value(), var);
            }
        }

        if (res.callsiteVars) {
            for (auto const& var : res.callsiteVars->positional.items) {
                EVAL_TRACE(fmt("Callsite variable {}", var));
                if (var.varname) {
                    byVarname.insert_or_assign(var.varname.value(), var);
                }
            }
        }

        for (auto const& key : sorted(byVarname.keys())) {
            sem::OrgCodeEvalInput::Var var;
            auto const&                attr = byVarname.at(key);

            var.name = attr.varname.value();
            json value;
            if (auto named_value = getAttrValue(attr)) {
                value = named_value.value();
            } else {
                value = attr.getString();
            }
            EVAL_TRACE(
                fmt("Var '{}' value is '{}'", var.name, value.dump()));
            var.value = value;
            input.argList.push_back(var);
        }


        return input;
    }


    void setOutput(
        Vec<sem::OrgCodeEvalOutput> const& out,
        sem::OrgCodeEvalInput const&       input,
        imm::ImmUniqId const&              block,
        sem::SemId<sem::Org>               node) {
        EVAL_SCOPE();
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

                    auto assign_result = [&]<typename T>(T code) -> T {
                        using RH = sem::OrgCodeEvalInput::ResultHandling;
                        switch (input.resultHandling) {
                            case RH::Append:
                                code.result = code.result.push_back(id);
                                break;
                            case RH::Prepend:
                                code.result = code.result.insert(0, id);
                                break;
                            case RH::Replace: code.result = {id}; break;
                            case RH::Discard: break;
                            case RH::Silent:
                            case RH::None:
                                // TODO
                                break;
                        }

                        return code;
                    };

                    if (target.is(OrgSemKind::BlockCode)) {
                        return ctx.store().updateNode<imm::ImmBlockCode>(
                            target, ctx, [&](imm::ImmBlockCode code) {
                                return assign_result(code);
                            });
                    } else {
                        return ctx.store().updateNode<imm::ImmCmdCall>(
                            target, ctx, [&](imm::ImmCmdCall code) {
                                return assign_result(code);
                            });
                    }
                }
            });

        if (conf.isTraceEnabled()) { history.push_back(version); }
    };

    sem::SemId<Org> evalAll(sem::SemId<sem::Org> document) {
        auto imm_context = imm::ImmAstContext::init_start_context();
        // imm_context->debug->setTraceFile("/tmp/evaluateCodeBlocks.log");
        version = imm_context->init(document);

        auto collect_code_blocks =
            [](imm::ImmAdapter const& ad) -> Vec<imm::ImmUniqId> {
            Vec<imm::ImmUniqId> res;
            org::eachSubnodeRec(
                ad, true, [&](imm::ImmAdapter const& adapter) {
                    if (adapter.is(OrgSemKind::BlockCode)
                        || adapter.is(OrgSemKind::CmdCall)) {
                        res.push_back(adapter.uniq());
                    }
                });

            return res;
        };


        if (isTraceEnabled()) { history.push_back(version); }


        auto init_buffer = collect_code_blocks(version.getRootAdapter());
        std::deque<imm::ImmUniqId> codeBlockPaths{
            init_buffer.begin(), init_buffer.end()};

        while (!codeBlockPaths.empty()) {
            auto block = codeBlockPaths.front();
            codeBlockPaths.pop_front();
            imm::ImmAdapter adapter = version.context->adapt(block);

            CallParams call = getTargetBlock(adapter);

            if (!call.block.isNil()) {
                EVAL_TRACE(
                    fmt("Evaluating language '{}' at {}",
                        call.block->lang,
                        call.block->loc));
                EVAL_SCOPE();

                auto input  = convertInput(call);
                auto output = conf.evalBlock(input);

                for (auto const& it : output) {
                    if (!it.cmd) { EVAL_TRACE(fmt("cmd: {}", it.cmd)); }
                    if (!it.args.empty()) {
                        EVAL_TRACE(fmt("args: {}", it.args));
                    }
                    EVAL_TRACE(fmt("code: {}", it.code));
                    if (!it.cwd.empty()) {
                        EVAL_TRACE(fmt("cwd: {}", it.cwd));
                    }

                    if (!it.stderrText.empty()) {
                        EVAL_TRACE(fmt("stderr:\n{}", it.stderrText));
                    }

                    if (!it.stdoutText.empty()) {
                        EVAL_TRACE(fmt("stdout:\n{}", it.stdoutText));
                    }
                }

                if (!output.empty()) {
                    setOutput(
                        output,
                        input,
                        block,
                        convertOutput(output.back(), input, conf));
                }
            }
        }

        if (isTraceEnabled()) {
#if !ORG_EMCC_BUILD
            auto graph = org::imm::toGraphviz(history);
            graph.render("/tmp/CodeBlockEvalGraph.png");
#endif
        }

        imm::ImmAdapter::TreeReprConf repr_conf;
        repr_conf.withAuxFields  = true;
        repr_conf.withReflFields = true;
        writeFile(
            "/tmp/codeblock_eval_final.txt",
            version.getRootAdapter().treeRepr(repr_conf).toString(false));

        EVAL_TRACE(
            fmt("Converting final root result {} back to sem",
                version.getRoot()));
        return org::imm::sem_from_immer(
            version.getRoot(), *version.context);
    }
};

} // namespace

sem::SemId<Org> org::evaluateCodeBlocks(
    sem::SemId<sem::Org>         document,
    const OrgCodeEvalParameters& conf) {
    EvalContext ctx{.conf = conf};
    return ctx.evalAll(document);
}

std::shared_ptr<imm::ImmAstContext> org::initImmutableAstContext() {
    return imm::ImmAstContext::init_start_context();
}
