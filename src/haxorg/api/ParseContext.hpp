#pragma once

#include <hstd/ext/error_write.hpp>
#include <haxorg/lexbase/SourceManager.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Str.hpp>
#include <haxorg/sem/SemOrg.hpp>


namespace org::parse {

/// \brief Documen fragment extracted from the larger text
struct [[refl]] OrgParseFragment {
    [[refl]] int         baseLine;
    [[refl]] int         baseCol;
    [[refl]] std::string text;
    DESC_FIELDS(OrgParseFragment, (baseLine, baseCol, text));
};

hstd::Vec<OrgParseFragment> extractCommentBlocks(
    const std::string&            text,
    const hstd::Vec<std::string>& commentPrefixes);


struct [[refl(
    R"({
  "backend": {
    "python": {
      "holder-type": "shared"
    },
    "wasm": {
      "holder-type": "shared"
    }
  }
})")]] OrgParseParameters : public hstd::SharedPtrApi<OrgParseParameters> {
    [[refl]] hstd::Opt<std::string>   baseTokenTracePath = std::nullopt;
    [[refl]] hstd::Opt<std::string>   tokenTracePath     = std::nullopt;
    [[refl]] hstd::Opt<std::string>   parseTracePath     = std::nullopt;
    [[refl]] hstd::Opt<std::string>   semTracePath       = std::nullopt;
    [[refl]] org::parse::SourceFileId currentFile        = org::parse::
        SourceFileId::Nil();

    hstd::Func<hstd::Vec<OrgParseFragment>(std::string const& text)>
        getFragments;

    BOOST_DESCRIBE_CLASS(
        OrgParseParameters,
        (),
        (baseTokenTracePath,
         tokenTracePath,
         parseTracePath,
         semTracePath,
         currentFile),
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
  }
})")]] OrgDirectoryParseParameters
    : public hstd::SharedPtrApi<OrgDirectoryParseParameters> {
    hstd::Func<sem::SemId<sem::Org>(std::string const& fullPath)>
        getParsedNode;

    hstd::Func<bool(std::string const& fullPath)> shouldProcessPath;
    hstd::Func<hstd::Opt<std::string>(std::string const& includePath)>
        findIncludeTarget;

    std::function<bool(std::string const&)>        isDirectoryImpl;
    std::function<bool(std::string const&)>        isSymlinkImpl;
    std::function<bool(std::string const&)>        isRegularFileImpl;
    std::function<std::string(std::string const&)> resolveSymlinkImpl;
    std::function<std::vector<std::string>(std::string const&)>
        getDirectoryEntriesImpl;

    bool                     isDirectory(std::string const& path) const;
    bool                     isSymlink(std::string const& path) const;
    bool                     isRegularFile(std::string const& path) const;
    std::string              resolveSymlink(std::string const& path) const;
    std::vector<std::string> getDirectoryEntries(
        std::string const& path) const;

    BOOST_DESCRIBE_CLASS(OrgDirectoryParseParameters, (), (), (), ());
};


struct [[refl]] ParseContext {
    hstd::SPtr<SourceManager> source;

    [[refl]] SourceFileId addSource(
        std::string const& path,
        std::string const& content) const {
        return source->addSource(path, content);
    }

    [[refl]] sem::SemId<sem::Org> parseFileOpts(
        std::string const&                         file,
        std::shared_ptr<OrgParseParameters> const& opts);

    [[refl]] sem::SemId<sem::Org> parseFile(std::string const& file);

    [[refl]] sem::SemId<sem::Org> parseString(
        std::string const& path,
        std::string const& text);

    [[refl]] sem::SemId<sem::Org> parseStringOpts(
        std::string const                          text,
        std::shared_ptr<OrgParseParameters> const& opts);

    [[refl]] hstd::Opt<sem::SemId<sem::Org>> parseDirectoryOpts(
        std::string const&                                  path,
        std::shared_ptr<OrgDirectoryParseParameters> const& opts);

    [[refl]] sem::SemId<sem::File> parseFileWithIncludes(
        std::string const&                                  file,
        std::shared_ptr<OrgDirectoryParseParameters> const& opts);

    void setDescriptionListItemBody(
        sem::SemId<sem::List>           list,
        hstd::CR<hstd::Str>             text,
        hstd::Vec<sem::SemId<sem::Org>> value);

    [[refl]] hstd::Vec<hstd::ext::Report> collectDiagnostics(
        org::sem::SemId<org::sem::Org> const& tree);

    [[refl]] hstd::Vec<sem::SemId<sem::ErrorGroup>> collectErrorNodes(
        org::sem::SemId<org::sem::Org> const& tree);
};
} // namespace org::parse
