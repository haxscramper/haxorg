#pragma once

#include <cassert>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include "git_interface.hpp"
import std.stdlib.dod_base;
import std.stdlib.Str;
import std.stdlib.Opt;
import std.stdlib.Filesystem;
#include <immer/flex_vector.hpp>

template <dod::IsIdType T>
auto operator<<(std::ostream& stream, T id) -> std::ostream& {
    if (id.isNil()) {
        stream << "NULL";
    } else {
        stream << id.getValue();
    }
    return stream;
}

namespace ir {

DECL_ID_TYPE(LineData, LineId, std::size_t);
DECL_ID_TYPE(Commit, CommitId, std::size_t);
DECL_ID_TYPE(FileTrack, FileTrackId, std::size_t);
DECL_ID_TYPE(FilePath, FilePathId, std::size_t);
DECL_ID_TYPE(Directory, DirectoryId, std::size_t);
DECL_ID_TYPE(String, StringId, std::size_t);
DECL_ID_TYPE(FileTrackSection, FileTrackSectionId, std::size_t);

} // namespace ir


namespace dod {
/// Provide struct specialization for string to be able to get it's id
/// type.
template <>
struct id_type<Str> {
    using type = ir::StringId;
};
} // namespace dod

namespace ir {

DECL_ID_TYPE(Author, AuthorId, int);

/// \defgroup db_mapped Mapped to the database

/// \brief file path with associated parent directory information
/// \ingroup db_mapped
struct FilePath {
    using id_type = FilePathId;
    ir::StringId         path;
    Opt<ir::DirectoryId> dir;

    bool operator==(CR<FilePath> other) const {
        return this->path == other.path;
    }
};

/// \brief single commit by author, taken at some point in time
/// \ingroup db_mapped
struct Commit {
    using id_type = CommitId;
    AuthorId author;   /// references unique author id
    i64      time;     /// posix time
    int      timezone; /// timezone where commit was taken
    Str      hash;     /// git hash of the commit
    Str      message;  /// Commit message
};

struct FileTrackSection {
    using id_type = FileTrackSectionId;
    /// Id of the commit this version of the file was recorded in
    ir::CommitId commit_id;
    /// What path was assigned to a file at the time this section was
    /// recorded?
    ir::FilePathId path;
    /// List of all lines found in the file
    immer::flex_vector<LineId> lines;
    Vec<int>                   added_lines;
    Vec<int>                   removed_lines;
};

/// \brief single version of the file that appeared in some commit
/// \ingroup db_mapped
struct FileTrack {
    using id_type = FileTrackId;
    Vec<FileTrackSectionId> sections;
};

/// \brief Full directory path and it's parent ID
/// \ingroup db_mapped
struct Directory {
    using id_type = DirectoryId;
    Opt<DirectoryId> parent; /// Parent directory ID
    Str              name;   /// Id of the string

    auto operator==(CR<Directory> other) const -> bool {
        return name == other.name && parent == other.parent;
    }
};

/// \brief Table of interned stirngs for different purposes
/// \ingroup db_mapped
struct String {
    using id_type = StringId;
    Str  text; /// Textual content of the line
    auto operator==(CR<String> other) const -> bool {
        return text == other.text;
    }
};

/// \brief Author - name and email found during the source code analysis.
/// \ingroup db_mapped
struct Author {
    using id_type = AuthorId;
    Str name;
    Str email;

    auto operator==(CR<Author> other) const -> bool {
        return name == other.name && email == other.email;
    }
};


/// \brief Unique combination of author+time+content for some line in
/// database
/// \ingroup db_mapped
///
/// Single line in a file with all the information that can be relevang for
/// the further analysis. Provides information about the /content/ found at
/// some line. Interned in the main storage.
struct LineData {
    using id_type = LineId;
    StringId content; /// Content of the line
    CommitId commit;

    auto operator==(CR<LineData> other) const -> bool {
        return commit == other.commit && content == other.content;
    }
};
} // namespace ir


// Taken from the SO answer
// https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
inline void hash_combine(std::size_t& seed) {}

/// \brief Mix list of hashes
template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    hash_combine(seed, rest...);
}

/// \brief Declare boilerplate type hasing using list of fields
#define MAKE_HASHABLE(__type, __varname, ...)                             \
    namespace std {                                                       \
        template <>                                                       \
        struct hash<__type> {                                             \
            auto operator()(const __type& __varname) const                \
                -> std::size_t {                                          \
                std::size_t ret = 0;                                      \
                hash_combine(ret, __VA_ARGS__);                           \
                return ret;                                               \
            }                                                             \
        };                                                                \
    }

// Add hashing declarations for the author and line data - they will be
// interned. `std::string` already has the hash structure.
MAKE_HASHABLE(ir::Author, it, it.name, it.email);
MAKE_HASHABLE(ir::LineData, it, it.content);
MAKE_HASHABLE(ir::Directory, it, it.name, it.parent);
MAKE_HASHABLE(ir::String, it, it.text);
MAKE_HASHABLE(ir::FilePath, it, it.path);

namespace ir {
/// \brief Main store for repository analysis
struct content_manager {
    dod::MultiStore<
        dod::InternStore<AuthorId, Author>, // Full list of authors
        dod::InternStore<LineId, LineData>, // found lines
        dod::Store<FileTrackSectionId, FileTrackSection>,
        dod::Store<FileTrackId, FileTrack>,       // file tracks
        dod::InternStore<FilePathId, FilePath>,   // file paths
        dod::Store<CommitId, Commit>,             // all commits
        dod::InternStore<DirectoryId, Directory>, // all directories
        dod::InternStore<StringId, String>        // all interned strings
        >
        multi;

    std::unordered_map<Str, DirectoryId> prefixes;

    /// \brief Get *optional* parent directory Id from the path
    auto parentDirectory(CR<fs::path> dir) -> Opt<DirectoryId> {
        if (dir.has_parent_path()) {
            auto parent = dir.parent_path();
            auto native = parent.native();
            if (prefixes.contains(native)) {
                return prefixes.at(native);
            } else {
                auto result = getDirectory(parent);
                prefixes.insert({parent.native(), result});
                return result;
            }
        } else {
            return Opt<DirectoryId>{};
        }
    }

    /// \brief Get directory ID from the provided path
    auto getDirectory(CR<fs::path> dir) -> DirectoryId {
        return add(ir::Directory{
            .parent = parentDirectory(dir), .name = dir.native()});
    }

    FilePathId getFilePath(CR<fs::path> file) {
        if (file.native().starts_with(" ")) {
            std::cerr << file << std::endl;
            assert(false);
        }


        auto result = add(ir::FilePath{
            .path = add(String{file.native()}),
            .dir  = parentDirectory(file)});

        assert(!at(at(result).path).text.starts_with(" "));

        return result;
    }

    /// \brief Get reference to value pointed to by the ID
    template <dod::IsIdType Id>
    auto at(Id id) -> typename dod::value_type_t<Id>& {
        return multi.at<Id>(id);
    }

    template <dod::IsIdType Id>
    [[nodiscard]] auto at(Id id) const -> CR<dod::value_type_t<Id>> {
        return multi.at<Id>(id);
    }

    /// \brief Push in a value, return newly generated ID
    template <typename T>
    [[nodiscard]] auto add(CR<T> it) -> dod::id_type_t<T> {
        return multi.add<T>(it);
    }
};

} // namespace ir
