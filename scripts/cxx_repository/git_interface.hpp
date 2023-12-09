#pragma once

#include <git2.h>

#include <hstd/stdlib/Str.hpp>
#include <array>
#include <hstd/stdlib/Func.hpp>
#include <expected>
#include <hstd/stdlib/Ptrs.hpp>

/// \brief Convert git ID object to it's string representation
inline Str oid_tostr(git_oid oid) {
    std::array<char, GIT_OID_HEXSZ + 1> result;
    git_oid_tostr(result.data(), sizeof(result), &oid);
    return Str{result.data(), result.size() - 1};
}

template <>
struct std::formatter<git_oid> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(git_oid const& p, FormatContext& ctx)
        const {
        return std::formatter<std::string>{}.format(oid_tostr(p), ctx);
    }
};


struct GitFail {
    Str message;
    int klass;
};

template <typename T>
using GitResult [[nodiscard]] = std::expected<T, GitFail>;


// NOLINTNEXTLINE
#define __GIT_THROW_EXCEPTION(code, function)                             \
    throw git::exception(code, function);

namespace git {

inline GitFail get_fail() {
    const git_error* e = git_error_last();
    return GitFail{e->message, e->klass};
}

inline GitResult<void> from_result(int result) {
    if (result < 0) {
        return std::unexpected(get_fail());
    } else {
        return GitResult<void>{};
    }
}

template <typename T>
GitResult<T> from_result(int result, T const& value) {
    if (result < 0) {
        return std::unexpected(get_fail());
    } else {
        return value;
    }
}

template <typename T, typename... Args>
GitResult<SPtr<T>> wrap_ptr_result(
    int (*allocator)(T**, Args...),
    void (*deleter)(T*),
    Args... args) {
    T*  out    = nullptr;
    int result = allocator(&out, std::forward<Args>(args)...);
    if (result < 0) {
        return std::unexpected(get_fail());
    } else {
        return std::shared_ptr<T>(out, deleter);
    }
}

inline GitResult<SPtr<git_revwalk>> revwalk_new(git_repository* repo) {
    return wrap_ptr_result<git_revwalk, git_repository*>(
        git_revwalk_new, git_revwalk_free, repo);
}

inline GitResult<SPtr<git_annotated_commit>> annotated_commit_lookup(
    git_repository* repo,
    const git_oid*  id) {
    return wrap_ptr_result<
        git_annotated_commit,
        git_repository*,
        git_oid const*>(
        git_annotated_commit_lookup, git_annotated_commit_free, repo, id);
}

inline GitResult<SPtr<git_object>> tree_entry_to_object(
    git_repository*       repo,
    const git_tree_entry* entry) {
    return wrap_ptr_result<
        git_object,
        git_repository*,
        const git_tree_entry*>(
        git_tree_entry_to_object, git_object_free, repo, entry);
}

inline int commit_time_offset(const git_commit* commit) {
    auto __result = git_commit_time_offset(commit);
    return __result;
}

inline const char* commit_message(const git_commit* commit) {
    auto __result = git_commit_message(commit);
    return __result;
}

inline GitResult<SPtr<git_patch>> patch_from_diff(
    git_diff* diff,
    size_t    idx) {
    return wrap_ptr_result<git_patch, git_diff*, size_t>(
        git_patch_from_diff, git_patch_free, diff, idx);
}

inline const git_signature* commit_author(const git_commit* commit) {
    auto __result = git_commit_author(commit);
    return __result;
}


inline GitResult<SPtr<git_diff>> diff_tree_to_tree(
    git_repository*         repo,
    git_tree*               old_tree,
    git_tree*               new_tree,
    const git_diff_options* opts) {
    return wrap_ptr_result(
        git_diff_tree_to_tree,
        git_diff_free,
        repo,
        old_tree,
        new_tree,
        opts);
}


inline GitResult<SPtr<git_tree>> commit_tree(const git_commit* commit) {
    return wrap_ptr_result(git_commit_tree, git_tree_free, commit);
}


inline git_time_t commit_time(const git_commit* commit) {
    auto __result = git_commit_time(commit);
    return __result;
}


inline const char* tree_entry_name(const git_tree_entry* entry) {
    auto __result = git_tree_entry_name(entry);
    return __result;
}

inline int revwalk_next(git_oid* out, git_revwalk* walk) {
    auto __result = git_revwalk_next(out, walk);
    return __result;
}

inline git_object_t tree_entry_type(const git_tree_entry* entry) {
    auto __result = git_tree_entry_type(entry);
    return __result;
}

inline GitResult<SPtr<git_tree_entry>> tree_entry_dup(
    const git_tree_entry* source) {
    return wrap_ptr_result(
        git_tree_entry_dup, git_tree_entry_free, source);
}


inline GitResult<git_oid> oid_fromstr(const char* str) {
    git_oid out;
    auto    __result = git_oid_fromstr(&out, str);
    return from_result(__result, out);
}

inline size_t diff_num_deltas(const git_diff* diff) {
    auto __result = git_diff_num_deltas(diff);
    return __result;
}

inline const git_diff_delta* patch_get_delta(const git_patch* patch) {
    auto __result = git_patch_get_delta(patch);
    return __result;
}


inline GitResult<SPtr<git_repository>> repository_open(const char* path) {
    return wrap_ptr_result<git_repository, const char*>(
        git_repository_open, git_repository_free, path);
}


inline GitResult<SPtr<git_repository>> repository_open_ext(
    const char*  path,
    unsigned int flags,
    const char*  ceiling_dirs) {
    return wrap_ptr_result<
        git_repository,
        const char*,
        unsigned int,
        const char*>(
        git_repository_open_ext,
        git_repository_free,
        path,
        flags,
        ceiling_dirs);
}


inline GitResult<SPtr<git_commit>> commit_lookup(
    git_repository* repo,
    const git_oid*  id) {
    return wrap_ptr_result<git_commit, git_repository*, git_oid const*>(
        git_commit_lookup, git_commit_free, repo, id);
}

inline GitResult<void> revwalk_push_head(git_revwalk* walk) {
    return from_result(git_revwalk_push_head(walk));
}

inline unsigned int commit_parentcount(const git_commit* commit) {
    auto __result = git_commit_parentcount(commit);
    return __result;
}

inline const git_oid* commit_parent_id(
    const git_commit* commit,
    unsigned int      n) {
    auto __result = git_commit_parent_id(commit, n);
    return __result;
}


inline GitResult<void> tree_walk(
    const git_tree*   tree,
    git_treewalk_mode mode,
    git_treewalk_cb   callback,
    void*             payload) {
    auto __result = git_tree_walk(tree, mode, callback, payload);
    return from_result(__result);
}

inline GitResult<void> diff_foreach(
    git_diff*          diff,
    git_diff_file_cb   file_cb,
    git_diff_binary_cb binary_cb,
    git_diff_hunk_cb   hunk_cb,
    git_diff_line_cb   line_cb,
    void*              payload) {
    auto __result = git_diff_foreach(
        diff, file_cb, binary_cb, hunk_cb, line_cb, payload);
    return from_result(__result);
}

inline GitResult<void> revwalk_sorting(
    git_revwalk* walk,
    unsigned int sort_mode) {
    auto __result = git_revwalk_sorting(walk, sort_mode);
    return from_result(__result);
}

inline int oid_cmp(const git_oid* a, const git_oid* b) {
    auto __result = git_oid_cmp(a, b);
    return __result;
}


}; // namespace git


/// \brief Iterate over the git tree in specified order using provided
/// callback
inline void tree_walk(
    const git_tree*   tree, ///< Pointer to the git tree to walk over
    git_treewalk_mode mode, ///< Order of the tree walk
    Func<int(const char*, const git_tree_entry*)> callback /// Callback to
    /// execute on each entry in the tree. Should return GIT_OK value in
    /// order continue the iteration. \note both arguments are managed by
    /// the tree walk algorithm - if you need to store the root (1st
    /// argument) or the entry itself for some post-walk processing you
    /// need to use copy the string or use `git::entry_dup` for each
    /// argument respectively.
) {
    using CB      = decltype(callback);
    CB* allocated = new CB;
    *allocated    = std::move(callback);
    git::tree_walk(
        tree,
        mode,
        [](const char*           root,
           const git_tree_entry* entry,
           void*                 payload) -> int {
            CB* impl = static_cast<CB*>(payload);
            try {
                auto __result = (*impl)(root, entry);
                return __result;
            } catch (...) { throw; }
        },
        allocated);
}


struct DiffForeachParams {
    /// Callback function to make per file in the diff.
    using file_cb_t = Func<int(const git_diff_delta*, float)>;

    file_cb_t file_cb;

    /// Optional callback to make for binary files.
    using binary_cb_t = Func<
        int(const git_diff_delta*, const git_diff_binary*)>;

    binary_cb_t binary_cb;

    /// Optional callback to make per hunk of text diff. This callback is
    /// called to describe a range of lines in the diff. It will not be
    /// issued for binary files.
    using hunk_cb_t = Func<
        int(const git_diff_delta*, const git_diff_hunk*)>;

    hunk_cb_t hunk_cb;

    /// Optional callback to make per line of diff text. This same callback
    /// will be made for context lines, added, and removed lines, and even
    /// for a deleted trailing newline.
    using line_cb_t = Func<int(
        const git_diff_delta*,
        const git_diff_hunk*,
        const git_diff_line*)>;

    line_cb_t line_cb;
};

inline void diff_foreach(
    git_diff* diff, ///< A git_diff generated by one of the above
                    ///< functions.
    CR<DiffForeachParams> foreach) {
    git::diff_foreach(
        diff,
        [](const git_diff_delta* delta, float progress, void* payload) {
            auto l = static_cast<DiffForeachParams*>(payload);
            if (l->file_cb) {
                return l->file_cb(delta, progress);
            } else {
                return 0;
            }
        },
        [](const git_diff_delta*  delta,
           const git_diff_binary* binary,
           void*                  payload) {
            auto l = static_cast<DiffForeachParams*>(payload);
            if (l->binary_cb) {
                return l->binary_cb(delta, binary);
            } else {
                return 0;
            }
        },
        [](const git_diff_delta* delta,
           const git_diff_hunk*  hunk,
           void*                 payload) {
            auto l = static_cast<DiffForeachParams*>(payload);
            if (l->hunk_cb) {
                return l->hunk_cb(delta, hunk);
            } else {
                return 0;
            }
        },
        [](const git_diff_delta* delta,
           const git_diff_hunk*  hunk,
           const git_diff_line*  line,
           void*                 payload) {
            auto l = static_cast<DiffForeachParams*>(payload);
            if (l->line_cb) {
                return l->line_cb(delta, hunk, line);
            } else {
                return 0;
            }
        },
        (void*)&foreach);
}

namespace std {
/// \brief Hash for git OID
template <>
struct hash<git_oid> {
    inline std::size_t operator()(const git_oid& it) const {
        return std::hash<Str>()(
            Str(reinterpret_cast<const char*>(&it.id[0]), sizeof(it.id)));
    }
};
} // namespace std

/// \brief Compare git OID for equality
inline bool operator==(CR<git_oid> lhs, CR<git_oid> rhs) {
    return git::oid_cmp(&lhs, &rhs) == 0;
}

inline bool operator<(CR<git_oid> lhs, CR<git_oid> rhs) {
    return git::oid_cmp(&lhs, &rhs) < 0;
}


inline std::ostream& operator<<(std::ostream& out, git_oid const& oid) {
    out << oid_tostr(oid);
    return out;
}
