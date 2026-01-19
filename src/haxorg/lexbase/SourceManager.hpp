#pragma once

#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <hstd/ext/bimap_wrap.hpp>

namespace org::parse {

DECL_ID_TYPE(SourceFile, SourceFileId, hstd::u32);

struct SourceFile {
    using id_type = SourceFileId;
    std::string content;
    std::string path;
};

struct SourceManager {
    hstd::dod::Store<SourceFileId, SourceFile>               store;
    hstd::ext::Unordered1to1Bimap<std::string, SourceFileId> path_ids;

    std::string getPath(SourceFileId const& id) const {
        return path_ids.at_left(id);
    }

    SourceFileId getId(std::string const& path) const {
        return path_ids.at_right(path);
    }

    std::string const& getSourceContent(SourceFileId const& id) const {
        return store.at(id).content;
    }

    std::string const& getContentTextForPath(
        std::string const& path) const {
        return store.at(getId(path)).content;
    }

    SourceFileId addSource(
        std::string const& path,
        std::string const& content) {
        auto result = store.add(
            SourceFile{.path = path, .content = content});
        path_ids.add_unique(path, result);
        return result;
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
