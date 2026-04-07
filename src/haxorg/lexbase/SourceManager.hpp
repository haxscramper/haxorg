#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <hstd/ext/bimap_wrap.hpp>

namespace org::parse {

DECL_ID_TYPE_MASKED_WITH_ATTR(
    SourceFile,
    SourceFileId,
    hstd::u32,
    0,
    [[refl(R"({"default-constructor": false})")]]);

struct SourceFile {
    using id_type = SourceFileId;
    std::string content;
    std::string path;
};

struct [[refl]] SourceManager {
    hstd::dod::Store<SourceFileId, SourceFile>               store;
    hstd::ext::Unordered1to1Bimap<std::string, SourceFileId> path_ids;

    [[refl]] std::string        getPath(SourceFileId const& id) const;
    [[refl]] SourceFileId       getId(std::string const& path) const;
    [[refl]] std::string const& getSourceContent(
        SourceFileId const& id) const;

    [[refl]] std::string const& getContentTextForPath(
        std::string const& path) const;

    [[refl]] SourceFileId addSource(
        std::string const& path,
        std::string const& content);
};


struct [[refl]] SourceLoc {
    [[refl]] int          line;
    [[refl]] int          column;
    [[refl]] int          pos     = -1;
    [[refl]] SourceFileId file_id = SourceFileId::Nil();

    bool operator==(SourceLoc const& other) const {
        return line == other.line && column == other.column
            && pos == other.pos && file_id == other.file_id;
    }

    BOOST_DESCRIBE_CLASS(
        SourceLoc,
        (),
        (line, column, pos, file_id),
        (),
        ());
};


} // namespace org::parse
