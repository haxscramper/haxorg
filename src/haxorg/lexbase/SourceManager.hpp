#pragma once

#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>

namespace org::parse {

DECL_ID_TYPE(SourceFile, SourceFileId, hstd::u32);

struct SourceFile {
    using id_type = SourceFileId;
    std::string content;
    std::string path;
};

struct SourceManager {
    hstd::dod::Store<SourceFileId, SourceFile> store;

    std::string const& getSourceContent(SourceFileId const& id) const {
        return store.at(id).content;
    }

    SourceFileId addSource(
        std::string const& path,
        std::string const& content) {
        return store.add(SourceFile{.path = path, .content = content});
    }
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
