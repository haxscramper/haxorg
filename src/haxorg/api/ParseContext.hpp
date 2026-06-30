#pragma once

#include "haxorg/base_lexer/base_token_tokenize.hpp"
#include "haxorg/parse/OrgParserTypes.hpp"
#include <haxorg/lexbase/SourceManager.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/ext/error_write.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>


namespace org::parse {

/// \brief Documen fragment extracted from the larger text
struct [[refl]] OrgParseFragment {
    [[refl]] int         baseLine;
    [[refl]] int         baseCol;
    [[refl]] std::string text;
    DESC_FIELDS(OrgParseFragment, (baseLine, baseCol, text));
};

hstd::Vec<OrgParseFragment> extractCommentBlocks(
    std::string const&            text,
    hstd::Vec<std::string> const& commentPrefixes);


struct [[refl(
    R"({
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    }
  },
  "wrapper-name": "OrgParseParameters"
})")]] OrgParseParameters : public hstd::SharedPtrApi<OrgParseParameters> {
    [[refl]] hstd::Opt<std::string> baseTokenTracePath = std::nullopt;
    [[refl]] hstd::Opt<std::string> tokenTracePath     = std::nullopt;
    [[refl]] hstd::Opt<std::string> parseTracePath     = std::nullopt;
    [[refl]] hstd::Opt<std::string> semTracePath       = std::nullopt;
    hstd::Func<hstd::Vec<OrgParseFragment>(std::string const& text)> getFragments;

    /// \brief Callbacks are triggered when the full file is parsed, or when the
    /// individual fragment index is parsed. The indices for fragment iterations come from
    /// the result of the `getFragments`.
    hstd::Func<
        void(org::parse::OrgTokenGroup const& tokens, std::optional<int> fragmentIndex)>
        onBaseTokenizeDone;
    hstd::Func<
        void(org::parse::OrgTokenGroup const& tokens, std::optional<int> fragmentIndex)>
        onTokenizerDone;
    hstd::Func<
        void(org::parse::OrgNodeGroup const& nodes, std::optional<int> fragmentIndex)>
        onParseDone;

    BOOST_DESCRIBE_CLASS(
        OrgParseParameters,
        (),
        (baseTokenTracePath, tokenTracePath, parseTracePath, semTracePath),
        (),
        ());
};

struct [[refl(
    R"({
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    }
  },
  "wrapper-name": "OrgDirectoryParseParameters"
})")]] OrgDirectoryParseParameters
    : public hstd::SharedPtrApi<OrgDirectoryParseParameters> {
    /// \brief Get a single parsed node, without recursively tracking includes.
    hstd::Func<sem::SemId<sem::Org>(std::string const& fullPath)> getParsedNode;

    hstd::Func<bool(std::string const& fullPath)>                      shouldProcessPath;
    hstd::Func<hstd::Opt<std::string>(std::string const& includePath)> findIncludeTarget;

    std::function<bool(std::string const&)>                     isDirectoryImpl;
    std::function<bool(std::string const&)>                     isSymlinkImpl;
    std::function<bool(std::string const&)>                     isRegularFileImpl;
    std::function<std::string(std::string const&)>              resolveSymlinkImpl;
    std::function<std::vector<std::string>(std::string const&)> getDirectoryEntriesImpl;

    bool                     isDirectory(std::string const& path) const;
    bool                     isSymlink(std::string const& path) const;
    bool                     isRegularFile(std::string const& path) const;
    std::string              resolveSymlink(std::string const& path) const;
    std::vector<std::string> getDirectoryEntries(std::string const& path) const;

    BOOST_DESCRIBE_CLASS(OrgDirectoryParseParameters, (), (), (), ());
};


struct [[refl(
    R"({
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    }
  },
  "wrapper-name": "ParseContext"
})")]] ParseContext : public hstd::SharedPtrApi<ParseContext> {
    hstd::SPtr<SourceManager> source;

    [[refl(R"({"unique-name": "ParseContextDefault"})")]] ParseContext();
    [[refl(R"({"unique-name": "ParseContextWithManager"})")]] ParseContext(
        hstd::SPtr<SourceManager> const& source);

    BOOST_DESCRIBE_CLASS(ParseContext, (), (), (), ());

    [[refl]] std::shared_ptr<hstd::ext::Cache> getDiagnosticStrings();

    [[refl]] SourceFileId addSource(std::string const& path, std::string const& content)
        const;

    [[refl]] sem::SemId<sem::Org> parseFileOpts(
        std::string const&                         file,
        std::shared_ptr<OrgParseParameters> const& opts);

    [[refl]] sem::SemId<sem::Org> parseFile(std::string const& file);

    [[refl]] sem::SemId<sem::Org> parseString(
        std::string const& text,
        std::string const& file_name);

    [[refl]] sem::SemId<sem::Org> parseStringOpts(
        std::string const                          text,
        std::string const&                         file_name,
        std::shared_ptr<OrgParseParameters> const& opts);

    [[refl]] hstd::Opt<sem::SemId<sem::Org>> parseDirectory(std::string const& path);

    [[refl]] hstd::Opt<sem::SemId<sem::Org>> parseDirectoryOpts(
        std::string const&                                  path,
        std::shared_ptr<OrgDirectoryParseParameters> const& opts);

    [[refl]] sem::SemId<sem::File> parseFileWithIncludes(
        std::string const&                                  file,
        std::shared_ptr<OrgDirectoryParseParameters> const& opts);

    [[refl]] hstd::Vec<hstd::ext::Report> collectDiagnostics(
        org::sem::SemId<org::sem::Org> const&    tree,
        std::shared_ptr<hstd::ext::Cache> const& cache);

    [[refl]] hstd::Vec<sem::SemId<sem::ErrorGroup>> collectErrorNodes(
        org::sem::SemId<org::sem::Org> const& tree);
};

struct DiagnosticsParseContext : public hstd::ext::Cache {
    hstd::UnorderedMap<org::parse::SourceFileId, std::shared_ptr<hstd::ext::Source>>
        sources;

    std::shared_ptr<ParseContext> context;

    DiagnosticsParseContext(std::shared_ptr<ParseContext> const& context)
        : context{context} {};

    virtual std::shared_ptr<hstd::ext::Source> fetch(hstd::ext::Id const& id) override;
    virtual std::optional<std::string> display(hstd::ext::Id const& id) const override;
};


} // namespace org::parse
