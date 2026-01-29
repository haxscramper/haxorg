#include <haxorg/api/ParseContext.hpp>
#include <haxorg/sem/SemConvert.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/base_lexer/base_token_tokenize.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

using namespace hstd;
using namespace org::parse;
using namespace org;
using namespace org::sem;

hstd::Vec<org::parse::OrgParseFragment> org::parse::extractCommentBlocks(
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


ParseContext::ParseContext() : source{std::make_shared<SourceManager>()} {}

ParseContext::ParseContext(const hstd::SPtr<SourceManager>& source)
    : source{source} {}

std::shared_ptr<hstd::ext::Cache> ParseContext::getDiagnosticStrings() {
    return std::make_shared<org::parse::DiagnosticsParseContext>(
        shared_from_this());
}

SourceFileId ParseContext::addSource(
    const std::string& path,
    const std::string& content) const {
    LOGIC_ASSERTION_CHECK_FMT(
        path.contains("/")
            || (path.starts_with("<") && path.ends_with(">")),
        "Source name must be a properly formatted path with `/`, or a "
        "temporary path name `<something>`");

    return source->addSource(path, content);
}

sem::SemId<sem::Org> ParseContext::parseFileOpts(
    const std::string&                         file,
    std::shared_ptr<OrgParseParameters> const& opts) {
    auto text = readFile(fs::path{file});
    return parseStringOpts(text, file, opts);
}

sem::SemId<sem::Org> ParseContext::parseFile(const std::string& file) {
    auto opts = OrgParseParameters::shared();
    auto text = readFile(fs::path{file});
    return parseStringOpts(text, file, opts);
}

sem::SemId<sem::Org> ParseContext::parseString(
    std::string const& text,
    std::string const& file_name) {
    auto opts = OrgParseParameters::shared();
    return parseStringOpts(text, file_name, opts);
}

sem::SemId<sem::Org> ParseContext::parseStringOpts(
    const std::string                          text,
    std::string const&                         string_id,
    const std::shared_ptr<OrgParseParameters>& opts) {

    auto file_id = addSource(string_id, text);

    if (opts->getFragments) {
        auto                          fragments = opts->getFragments(text);
        Vec<OrgConverter::InFragment> toConvert;

        if (opts->baseTokenTracePath) {
            fs::remove(opts->baseTokenTracePath.value());
        }

        if (opts->parseTracePath) {
            fs::remove(opts->parseTracePath.value());
        }

        if (opts->semTracePath) { fs::remove(opts->semTracePath.value()); }

        if (opts->tokenTracePath) {
            fs::remove(opts->tokenTracePath.value());
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
            if (opts->baseTokenTracePath) {
                p.setTraceFile(opts->baseTokenTracePath.value());
                p.traceColored = false;
            }

            org::parse::OrgTokenGroup baseTokens = org::parse::tokenize(
                frag.text, p, file_id);
            org::parse::OrgTokenizer tokenizer{&tokens.at(i)};

            if (opts->tokenTracePath) {
                tokenizer.setTraceFile(*opts->tokenTracePath, false);
                tokenizer.traceColored = false;
            }

            tokenizer.convert(baseTokens);
            org::parse::Lexer<OrgTokenKind, org::parse::OrgFill> lex{
                &tokens.at(i)};

            org::parse::OrgParser parser{&nodes.at(i)};
            if (opts->parseTracePath) {
                parser.setTraceFile(*opts->parseTracePath, false);
                parser.traceColored = false;
            }

            auto id      = parser.parseFull(lex);
            auto adapter = org::parse::OrgAdapter(&nodes.at(i), id);

            // adapter.tr

            toConvert.push_back(
                OrgConverter::InFragment{
                    .baseLine = frag.baseLine,
                    .baseCol  = frag.baseCol,
                    .node     = adapter,
                });
        }

        sem::OrgConverter converter{};
        if (opts->semTracePath) {
            converter.setTraceFile(*opts->semTracePath);
            converter.traceColored = false;
        }

        return converter.convertDocumentFragments(toConvert).unwrap();

    } else {


        org::parse::LexerParams p;
        SPtr<std::ofstream>     fileTrace;
        if (opts->baseTokenTracePath) {
            p.setTraceFile(opts->baseTokenTracePath.value());
            p.traceColored = false;
        }

        org::parse::OrgTokenGroup baseTokens = org::parse::tokenize(
            text, p, file_id);

        org::parse::OrgTokenGroup tokens;
        org::parse::OrgTokenizer  tokenizer{&tokens};

        if (opts->tokenTracePath) {
            tokenizer.setTraceFile(*opts->tokenTracePath);
            tokenizer.traceColored = false;
        }

        tokenizer.convert(baseTokens);
        org::parse::Lexer<OrgTokenKind, org::parse::OrgFill> lex{&tokens};

        org::parse::OrgNodeGroup nodes{&tokens};
        org::parse::OrgParser    parser{&nodes};
        if (opts->parseTracePath) {
            parser.setTraceFile(*opts->parseTracePath);
            parser.traceColored = false;
        }

        auto              id = parser.parseFull(lex);
        sem::OrgConverter converter{};
        if (opts->semTracePath) {
            converter.setTraceFile(*opts->semTracePath);
            converter.traceColored = false;
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
    ParseContext*                                       ctx,
    fs::path const&                                     path,
    fs::path const&                                     activeRoot,
    sem::OrgArg                                         parsed,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts,
    DirectoryParseState&                                state);

Opt<sem::SemId<sem::File>> parseFileAux(
    ParseContext*                                       ctx,
    fs::path const&                                     path,
    fs::path const&                                     activeRoot,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts,
    DirectoryParseState&                                state) {
    LOGIC_ASSERTION_CHECK_FMT(
        opts->isRegularFile(path),
        "'{}' should be a regular text file",
        path);

    __perf_trace("parsing", "Parse file", path, path.native());

    auto parsed = opts->getParsedNode ? opts->getParsedNode(path)
                                      : ctx->parseFile(path.native());

    // _dbg(parsed.isNil());
    if (parsed.isNil()) { return std::nullopt; }
    postProcessFileReferences(ctx, path, activeRoot, parsed, opts, state);

    sem::SemId<File> file = sem::SemId<File>::New();
    file->relPath         = fs::relative(path, activeRoot).native();
    file->absPath         = path.native();
    file->push_back(parsed);
    return file;
}

Opt<sem::SemId<Org>> parsePathAux(
    ParseContext*                                       ctx,
    fs::path const&                                     path,
    fs::path const&                                     activeRoot,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts,
    DirectoryParseState&                                state) {
    // _dfmt(path, activeRoot);
    if (state.visited.contains(path.native())) {
        // _dbg("Already visited");
        return std::nullopt;
    }
    state.visited.incl(path.native());

    if (opts->shouldProcessPath && !opts->shouldProcessPath(path)) {
        // _dbg("Should not process path");
        return std::nullopt;
    } else if (opts->isSymlink(path)) {
        auto target = fs::path{opts->resolveSymlink(path)};
        if (opts->isDirectory(target)) {
            sem::SemId<sem::Symlink> sym = sem::SemId<sem::Symlink>::New();
            sym->isDirectory             = true;
            sym->absPath                 = target.native();
            auto dir                     = parsePathAux(
                ctx, target, sym->absPath.toBase(), opts, state);
            if (dir) { sym->push_back(dir.value()); }
            return sym;

        } else if (opts->isRegularFile(target)) {
            sem::SemId<sem::Symlink> sym = sem::SemId<sem::Symlink>::New();
            sym->absPath                 = target.parent_path().native();
            auto file                    = parsePathAux(
                ctx, target, sym->absPath.toBase(), opts, state);
            if (file) { sym->push_back(file.value()); }
            return sym;
        } else {
            return std::nullopt;
        }


    } else if (opts->isDirectory(path)) {
        sem::SemId<Directory> dir = sem::SemId<Directory>::New();
        dir->relPath = fs::relative(path, activeRoot).native();
        dir->absPath = path.native();
        __perf_trace(
            "parsing", "Parse directory", dir, dir->absPath.toBase());
        for (const auto& entry : opts->getDirectoryEntries(path)) {
            auto nested = parsePathAux(
                ctx, entry, activeRoot, opts, state);
            if (nested) { dir->push_back(nested.value()); }
        }

        return dir;
    } else if (opts->isRegularFile(path)) {
        if (normalize(path.extension().native()) == "org") {
            return parseFileAux(ctx, path, activeRoot, opts, state);
        } else {
            return std::nullopt;
        }

    } else {
        return std::nullopt;
    }
}

Opt<fs::path> resolvePath(
    fs::path const&                                     workdir,
    CR<Str>                                             target,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts) {
    LOGIC_ASSERTION_CHECK_FMT(
        opts->isDirectory(workdir),
        "Workdir must be a directory, but got '{}'",
        workdir);

    fs::path full //
        = fs::path{target.toBase()}.is_absolute()
            ? fs::path{target.toBase()}
            : (workdir / target.toBase());

    if (!fs::exists(full) && opts->findIncludeTarget) {
        auto includeFound = opts->findIncludeTarget(target);
        if (includeFound) { full = includeFound.value(); }
    }

    if (fs::exists(full)) {
        return full;
    } else {
        return std::nullopt;
    }
}

void postProcessInclude(
    ParseContext*                                       ctx,
    sem::SemId<sem::Org>                                arg,
    fs::path const&                                     filePath,
    fs::path const&                                     activeRoot,
    sem::OrgArg                                         parsed,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts,
    DirectoryParseState&                                state) {
    auto incl = arg.as<sem::CmdInclude>();
    auto full = resolvePath(filePath.parent_path(), incl->path, opts);

    if (full) {
        switch (incl->getIncludeKind()) {
            case sem::CmdInclude::Kind::OrgDocument: {
                auto parsed = parsePathAux(
                    ctx, full.value(), activeRoot, opts, state);
                if (parsed) { arg->push_back(parsed.value()); }
                break;
            }
            case sem::CmdInclude::Kind::Src: {
                LOGIC_ASSERTION_CHECK_FMT(
                    incl.at(0)->is(OrgSemKind::BlockCode), "");

                auto code   = incl.as<sem::BlockCode>();
                auto source = readFile(full.value());
                for (auto const& line : split(source, '\n')) {
                    sem::BlockCodeLine lineNode;
                    lineNode.parts.push_back(
                        sem::BlockCodeLine::Part{
                            sem::BlockCodeLine::Part::Raw{.code = line}});
                    code->lines.push_back(lineNode);
                }
                break;
            }
            case sem::CmdInclude::Kind::Example: {
                LOGIC_ASSERTION_CHECK_FMT(
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
                LOGIC_ASSERTION_CHECK_FMT(
                    incl.at(0)->is(OrgSemKind::BlockExport), "");

                auto code     = incl.as<sem::BlockExport>();
                code->content = readFile(full.value());
                break;
            }
            case sem::CmdInclude::Kind::Custom: {
                break;
            }
        }
    } else {
        auto group = sem::SemId<sem::ErrorGroup>::New();
        auto error = sem::SemId<sem::ErrorItem>::New();
        org::sem::OrgDiagnostics::IncludeError inc{};
        inc.brief       = "Could not resolve include target";
        inc.targetPath  = inc.brief;
        inc.workingFile = filePath.native();
        error->diag     = org::sem::OrgDiagnostics{inc};
        arg->push_back(error);
    }
}

void postProcessFileLink(
    sem::SemId<sem::Org>                                arg,
    fs::path const&                                     documentPath,
    fs::path const&                                     activeRoot,
    sem::OrgArg                                         parsed,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts,
    DirectoryParseState&                                state) {
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
    ParseContext*                                       ctx,
    fs::path const&                                     path,
    fs::path const&                                     activeRoot,
    sem::OrgArg                                         parsed,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts,
    DirectoryParseState&                                state) {
    org::eachSubnodeRec(parsed, [&](sem::SemId<sem::Org> arg) {
        if (auto incl = arg.asOpt<sem::CmdInclude>()) {
            postProcessInclude(
                ctx, arg, path, activeRoot, parsed, opts, state);
        } else if (auto link = arg.asOpt<sem::Link>()) {
            postProcessFileLink(
                arg, path, activeRoot, parsed, opts, state);
        }
    });
}
} // namespace


Opt<sem::SemId<Org>> ParseContext::parseDirectoryOpts(
    const std::string&                                  root,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts) {

    DirectoryParseState state;
    return parsePathAux(this, fs::absolute(root), root, opts, state);
}

hstd::Opt<sem::SemId<Org>> ParseContext::parseDirectory(
    const std::string& path) {
    return parseDirectoryOpts(
        path, org::parse::OrgDirectoryParseParameters::shared());
}

sem::SemId<File> ParseContext::parseFileWithIncludes(
    const std::string&                                  file,
    std::shared_ptr<OrgDirectoryParseParameters> const& opts) {
    DirectoryParseState state;
    auto                parsed = parseFileAux(
        this, file, fs::path{file}.parent_path(), opts, state);
    if (parsed) {
        return parsed.value();
    } else {
        return sem::SemId<sem::File>::New();
    }
}

bool OrgDirectoryParseParameters::isDirectory(
    const std::string& path) const {
    if (isDirectoryImpl) {
        return isDirectoryImpl(path);
    } else {
        return fs::is_directory(path);
    }
}

bool OrgDirectoryParseParameters::isSymlink(
    const std::string& path) const {
    if (isSymlinkImpl) {
        return isSymlinkImpl(path);
    } else {
        return fs::is_symlink(path);
    }
}

bool OrgDirectoryParseParameters::isRegularFile(
    const std::string& path) const {
    if (isRegularFileImpl) {
        return isRegularFileImpl(path);
    } else {
        return fs::is_regular_file(path);
    }
}

std::string OrgDirectoryParseParameters::resolveSymlink(
    const std::string& path) const {
    if (resolveSymlinkImpl) {
        return resolveSymlinkImpl(path);
    } else {
        return fs::read_symlink(path);
    }
}

std::vector<std::string> OrgDirectoryParseParameters::getDirectoryEntries(
    const std::string& path) const {
    if (getDirectoryEntriesImpl) {
        return getDirectoryEntriesImpl(path);
    } else {
        std::vector<std::string> content;
        for (auto const& it : fs::directory_iterator(path)) {
            content.push_back(it.path().native());
        }
        return content;
    }
}


hstd::Vec<ext::Report> ParseContext::collectDiagnostics(
    const org::sem::SemId<sem::Org>&         tree,
    std::shared_ptr<hstd::ext::Cache> const& cache) {
    hstd::Vec<ext::Report> result;

    org::eachSubnodeRec(tree, [&](sem::SemId<sem::Org> const& node) {
        if (auto group = node.asOpt<org::sem::ErrorGroup>(); group) {
            for (auto const& item : group->diagnostics) {
                using K       = org::sem::OrgDiagnostics::Kind;
                auto const& d = item->diag;

                auto getId = [&](org::parse::SourceLoc const& loc) {
                    return loc.file_id.getValue();
                };

                switch (d.getKind()) {
                    case K::ConvertError: {
                        auto const& err = d.getConvertError();
                        auto        id  = getId(err.loc.value());

                        result.push_back(
                            ext::Report(ext::ReportKind::Error, id, 0)
                                .with_message(err.brief)
                                .with_code(err.errCode)
                                .with_note(
                                    hstd::to_compact_json(
                                        hstd::to_json_eval(err)))
                                .with_label(
                                    ext::Label{1}
                                        .with_span(id, slice(1, 2))
                                        .with_message(err.detail)));
                        break;
                    }

                    case K::ParseError: {
                        auto const& err = d.getParseError();
                        auto        id  = getId(err.loc.value());
                        auto        l   = //
                            ext::Label{1}
                                .with_span(
                                    id,
                                    slice(err.loc->pos, err.loc->pos + 1))
                                .with_message(err.detail);

                        result.push_back(
                            ext::Report(ext::ReportKind::Error, id, 0)
                                .with_message(err.brief)
                                .with_code(err.errCode)
                                .with_note(
                                    hstd::to_compact_json(
                                        hstd::to_json_eval(err)))
                                .with_label(l));
                        break;
                    }

                    case K::ParseTokenError: {
                        auto const& err = d.getParseTokenError();
                        auto        id  = getId(err.loc);
                        auto        l   = //
                            ext::Label{1}
                                .with_span(
                                    id,
                                    slice(
                                        err.loc.pos,
                                        err.loc.pos
                                            + err.tokenText.size()))
                                .with_message(err.detail);

                        result.push_back(
                            ext::Report(ext::ReportKind::Error, id, 0)
                                .with_message(err.brief)
                                .with_code(err.errCode)
                                .with_note(
                                    hstd::to_compact_json(
                                        hstd::to_json_eval(err)))
                                .with_label(l));
                        break;
                    }

                    case K::InternalError: {
                        break;
                    }

                    default: {
                        throw hstd::logic_unhandled_kind_error::init(
                            d.getKind());
                    }
                }
            }
        }
    });

    return result;
}

hstd::Vec<sem::SemId<ErrorGroup>> ParseContext::collectErrorNodes(
    const org::sem::SemId<sem::Org>& tree) {
    hstd::Vec<sem::SemId<ErrorGroup>> res;
    org::eachSubnodeRec(tree, [&](sem::SemId<sem::Org> const& node) {
        if (auto group = node.asOpt<org::sem::ErrorGroup>(); group) {
            res.push_back(group);
        }
    });
    return res;
}

std::shared_ptr<ext::Source> DiagnosticsParseContext::fetch(
    const hstd::ext::Id& id) {
    auto file_id = org::parse::SourceFileId::FromValue(id);
    if (!sources.contains(file_id)) {
        sources.insert_or_assign(
            file_id,
            std::make_shared<hstd::ext::Source>(
                context->source->getSourceContent(file_id)));
    }

    return sources.at(file_id);
}

std::optional<std::string> DiagnosticsParseContext::display(
    const hstd::ext::Id& id) const {
    return context->source->getPath(
        org::parse::SourceFileId::FromValue(id));
}
