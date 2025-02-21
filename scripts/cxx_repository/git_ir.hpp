#pragma once

#include <cassert>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include "git_interface.hpp"
#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <immer/flex_vector.hpp>
#include <absl/log/log.h>

template <hstd::dod::IsIdType T>
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
DECL_ID_TYPE(String, StringId, std::size_t);
DECL_ID_TYPE(FileTrackSection, FileTrackSectionId, std::size_t);

} // namespace ir


namespace hstd::dod {
/// Provide struct specialization for string to be able to get it's id
/// type.
template <>
struct id_type<Str> {
    using type = ir::StringId;
};
} // namespace hstd::dod

namespace ir {

DECL_ID_TYPE(Author, AuthorId, std::size_t);

/// \defgroup db_mapped Mapped to the database

/// \brief file path with associated parent directory information
/// \ingroup db_mapped
struct FilePath {
    using id_type = FilePathId;
    ir::StringId path;

    bool operator==(FilePath const& other) const {
        return this->path == other.path;
    }
};

/// \brief single commit by author, taken at some point in time
/// \ingroup db_mapped
struct Commit {
    using id_type = CommitId;
    AuthorId  author;   /// references unique author id
    hstd::i64 time;     /// posix time
    int       timezone; /// timezone where commit was taken
    hstd::Str hash;     /// git hash of the commit
    hstd::Str message;  /// Commit message

    DECL_DESCRIBED_ENUM(ActionKind, Modify, Delete, Rename, Add);

    struct Action {
        ActionKind      kind;
        ir::FileTrackId track    = ir::FileTrackId::Nil();
        ir::FilePathId  old_path = ir::FilePathId::Nil();
        ir::FilePathId  new_path = ir::FilePathId::Nil();
        ir::FilePathId  file     = ir::FilePathId::Nil();
        int             added    = 0;
        int             removed  = 0;
    };

    hstd::Vec<Action> actions;
};

struct FileTrackSection {
    using id_type = FileTrackSectionId;
    /// Id of the commit this version of the file was recorded in
    ir::CommitId commit_id;
    /// What path was assigned to a file at the time this section was
    /// recorded?
    ir::FilePathId path;
    /// File track this section belongs to
    ir::FileTrackId track;
    /// List of all lines found in the file
    immer::flex_vector<LineId> lines;
    hstd::Vec<int>             added_lines;
    hstd::Vec<int>             removed_lines;
};

/// \brief single version of the file that appeared in some commit
/// \ingroup db_mapped
struct FileTrack {
    using id_type = FileTrackId;
    hstd::Vec<FileTrackSectionId> sections;
};

/// \brief Table of interned stirngs for different purposes
/// \ingroup db_mapped
struct String {
    using id_type = StringId;
    hstd::Str text; /// Textual content of the line
    auto      operator==(String const& other) const -> bool {
        return text == other.text;
    }
};

/// \brief Author - name and email found during the source code analysis.
/// \ingroup db_mapped
struct Author {
    using id_type = AuthorId;
    hstd::Str name;
    hstd::Str email;

    auto operator==(Author const& other) const -> bool {
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

    auto operator==(LineData const& other) const -> bool {
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
MAKE_HASHABLE(ir::String, it, it.text);
MAKE_HASHABLE(ir::FilePath, it, it.path);

namespace ir {
/// \brief Main store for repository analysis
struct content_manager {
    hstd::dod::MultiStore<
        hstd::dod::InternStore<AuthorId, Author>, // Full list of authors
        hstd::dod::InternStore<LineId, LineData>, // found lines
        hstd::dod::Store<FileTrackSectionId, FileTrackSection>,
        hstd::dod::Store<FileTrackId, FileTrack>,     // file tracks
        hstd::dod::InternStore<FilePathId, FilePath>, // file paths
        hstd::dod::Store<CommitId, Commit>,           // all commits
        hstd::dod::InternStore<StringId, String> // all interned strings
        >
        multi;

    FilePathId getFilePath(hstd::fs::path const& file) {
        if (file.native().starts_with(" ")) {
            std::cerr << file << std::endl;
            LOG(FATAL);
        }


        auto result = add(
            ir::FilePath{.path = add(String{file.native()})});

        CHECK(!at(at(result).path).text.starts_with(" "));
        CHECK(!result.isNil())
            << std::format("ID:{} PATH:{}", result, file);

        return result;
    }

    /// \brief Get reference to value pointed to by the ID
    template <hstd::dod::IsIdType Id>
    auto at(Id id) -> typename hstd::dod::value_type_t<Id>& {
        return multi.at<Id>(id);
    }

    template <hstd::dod::IsIdType Id>
    [[nodiscard]] auto at(Id id) const
        -> hstd::dod::value_type_t<Id> const& {
        return multi.at<Id>(id);
    }

    /// \brief Push in a value, return newly generated ID
    template <typename T>
    [[nodiscard]] auto add(T const& it) -> hstd::dod::id_type_t<T> {
        return multi.add<T>(it);
    }
};

} // namespace ir
