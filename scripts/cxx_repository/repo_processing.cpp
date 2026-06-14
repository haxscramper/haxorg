/// \file repo_processing.cpp \brief repository processing algorithms
#include "repo_processing.hpp"
#include "git_interface.hpp"
#include "repo_graph.hpp"
#include <git2/patch.h>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Set.hpp>
#include <immer/flex_vector_transient.hpp>
#include <fstream>
#include "repo_profile.hpp"
#include <hstd/ext/logger.hpp>
#include <boost/asio/thread_pool.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <boost/asio/post.hpp>

#include <algorithm>

#include <hstd/stdlib/Ranges.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>

using namespace ir;
using namespace hstd;

int get_nesting(Str const& line) {
    int result = 0;
    for (char c : line) {
        if (c == ' ') {
            ++result;
        } else if (c == '\t') {
            result += 4;
        } else {
            break;
        }
    }

    return result;
}

void open_walker(git_oid& oid, walker_state& state) {
    // Read HEAD on master
    fs::path head_filepath = state.config->repo_path() / state.config->heads_path();
    // REFACTOR this part was copied from the SO example and I'm pretty
    // sure it can be implemented in a cleaner manner, but I haven't
    // touched this part yet.
    FILE*                head_fileptr = nullptr;
    std::array<char, 41> head_rev;

    if ((head_fileptr = fopen(head_filepath.c_str(), "r")) == nullptr) {
        throw std::system_error{
            std::error_code{}, fmt("Error opening {}", head_filepath)};
    }

    if (fread(head_rev.data(), 40, 1, head_fileptr) != 1) {
        throw std::system_error{
            std::error_code{}, fmt("Error reading from {}", head_filepath)};
        fclose(head_fileptr);
    }

    fclose(head_fileptr);

    oid = git::oid_fromstr(head_rev.data()).value();
    // Initialize revision walker
    state.walker = git::revwalk_new(state.repo.get()).value();
    // Iterate all commits in the topological order
    git::revwalk_sorting(state.walker.get(), GIT_SORT_NONE);
    git::revwalk_push_head(state.walker.get());
}


struct FullCommitData {
    git_oid          oid;
    PTime            time;
    SPtr<git_commit> commit;
    CommitId         id;
};


struct RemoveAction {
    int          removed;
    ir::StringId id;
    DESC_FIELDS(RemoveAction, (removed));
};

struct AddAction {
    int        added;
    ir::LineId id;
    DESC_FIELDS(AddAction, (added, id));
};

struct FileRenameAction {
    ir::FilePathId prev_path;
    ir::FilePathId this_path;
    DESC_FIELDS(FileRenameAction, (prev_path, this_path));
};

struct FileDeleteAction {
    ir::FilePathId path;
    DESC_FIELDS(FileDeleteAction, (path));
};

struct FileModifyAction {
    ir::FilePathId path;
    int            added;
    int            removed;
    DESC_FIELDS(FileModifyAction, (path, added, removed));
};

struct NameAction {
    NameAction(ir::FilePathId path) : path(path) {
        LOGIC_ASSERTION_CHECK_FMT(!path.isNil(), "");
    }

    BOOST_DESCRIBE_CLASS(NameAction, (), (path), (), ());
    ir::FilePathId getPath() const {
        LOGIC_ASSERTION_CHECK_FMT(!path.isNil(), "");
        return path;
    }

  private:
    ir::FilePathId path = ir::FilePathId::Nil();
};

using Action = Variant<RemoveAction, AddAction>;


struct CommitTask {
    CommitId       id;
    SPtr<git_tree> prev_tree;
    SPtr<git_tree> this_tree;
    Opt<git_oid>   prev_hash;
    git_oid        this_hash;
    DESC_FIELDS(CommitTask, (id, prev_tree, this_tree, prev_hash, this_hash));
};

struct CommitActionGroup : Vec<Action> {
    Opt<NameAction>       leading_name;
    Opt<FileRenameAction> rename_action;
    Opt<FileDeleteAction> delete_action;
    Opt<FileModifyAction> modify_action;

    bool hasAny() const { return rename_action || delete_action || modify_action; }

    DESC_FIELDS(
        CommitActionGroup,
        (leading_name, rename_action, delete_action, modify_action));
};

struct CommitActions {
    CommitId                                        id;
    SPtr<git_tree>                                  this_tree;
    UnorderedMap<ir::FilePathId, CommitActionGroup> actions;
    UnorderedSet<Str>                               directory_paths;
};

template <typename Res, typename... CallbackArgs>
Pair<Res (*)(CallbackArgs..., void*), Func<Res(CallbackArgs...)>> git_callback_wrapper(
    Func<Res(CallbackArgs...)> lambda) {
    auto trampoline = [](CallbackArgs... args, void* payload) -> Res {
        auto& lambda = *static_cast<Func<Res(CallbackArgs...)>*>(payload);
        return lambda(std::forward<CallbackArgs>(args)...);
    };

    return {trampoline, lambda};
}

void maybe_file_rename(
    walker_state*         state,
    git_diff_delta const* delta,
    CommitActionGroup&    actions) {
    auto new_path = state->content->getFilePath(delta->new_file.path);
    if (delta->old_file.path && strcmp(delta->old_file.path, delta->new_file.path) != 0) {
        auto old_path = state->content->getFilePath(delta->old_file.path);

        if (state->should_debug()) {
            HSLOG_INFO(
                "[actions] File rename from '{}' to '{}', ID mapping is: "
                "new:{} -> old:{}",
                delta->old_file.path,
                delta->new_file.path,
                new_path,
                old_path);
        }

        actions.rename_action = FileRenameAction{
            .prev_path = old_path,
            .this_path = new_path,
        };
    }
}

void line_edit_action(
    walker_state*        state,
    git_diff_line const* line,
    Vec<Action>&         delete_actions,
    Vec<Action>&         add_actions,
    ir::CommitId         id_commit) {
    ir::StringId string_id = state->content->add(
        String{
            strip(Str{line->content, static_cast<int>(line->content_len)}, {}, {'\n'})});

    switch (line->origin) {
        case GIT_DIFF_LINE_ADDITION: {
            ir::LineId line_id = state->content->add(
                LineData{
                    .content = string_id,
                    .commit  = id_commit,
                });


            add_actions.push_back(
                AddAction{
                    .added = line->new_lineno - 1,
                    .id    = line_id,
                });
            break;
        }

        case GIT_DIFF_LINE_DELETION: {
            delete_actions.push_back(
                RemoveAction{
                    .removed = line->old_lineno - 1,
                    .id      = string_id,
                });
            break;
        }
    }
}

void file_edit_actions(
    SPtr<git_patch> patch,
    walker_state*   state,
    ir::CommitId    id_commit,
    Vec<Action>&    actions) {
    Vec<Action> delete_actions;
    Vec<Action> add_actions;

    int num_hunks = git_patch_num_hunks(patch.get());
    for (int hunk_idx = 0; hunk_idx < num_hunks; ++hunk_idx) {
        const git_diff_hunk* hunk;
        git_patch_get_hunk(&hunk, NULL, patch.get(), hunk_idx);

        int num_lines = git_patch_num_lines_in_hunk(patch.get(), hunk_idx);
        for (int line_idx = 0; line_idx < num_lines; ++line_idx) {
            const git_diff_line* line;
            git_patch_get_line_in_hunk(&line, patch.get(), hunk_idx, line_idx);
            line_edit_action(state, line, delete_actions, add_actions, id_commit);
        }
    }

    std::ranges::reverse(delete_actions);
    actions.append(delete_actions);
    actions.append(add_actions);
}

void git_tree_walk_lambda(
    SPtr<git_tree>                                this_tree,
    Func<int(char const*, git_tree_entry const*)> callback) {
    auto [trampoline, lambda] = git_callback_wrapper(
        Func<int(char const*, git_tree_entry const*)>(callback));

    git_tree_walk(this_tree.get(), GIT_TREEWALK_PRE, trampoline, &lambda);
}

void file_name_actions(walker_state* state, CommitActions& result) {
    git_tree_walk_lambda(
        result.this_tree, [&](char const* root, git_tree_entry const* entry) -> int {
            const git_object_t entry_type = git_tree_entry_type(entry);
            auto path = fs::path{root} / fs::path{git_tree_entry_name(entry)};
            if (entry_type == GIT_OBJECT_BLOB) {

                auto  track   = state->content->getFilePath(path);
                auto& actions = result.actions[track];
                LOGIC_ASSERTION_CHECK_FMT(!actions.leading_name, "");
                actions.leading_name = NameAction{state->content->getFilePath(path)};
            } else if (entry_type == GIT_OBJECT_TREE || entry_type == GIT_OBJECT_COMMIT) {
                result.directory_paths.incl(path.native());
            } else {
                HSLOG_INFO("Commit has '{}' with type {}", path.native(), entry_type);
            }
            return 0;
        });
}

CommitActions get_commit_actions(walker_state* state, CommitTask const& task) {
    CommitActions result{.id = task.id, .this_tree = task.this_tree};
    HSLOG_IF(
        info,
        state->should_debug_commit(task.id),
        "[actions] Generating list of actions for commit {}",
        state->str(task.id));

    auto const&           c_diff     = state->config->cli.config.diffopts;
    git_diff_options      diffopts   = GIT_DIFF_OPTIONS_INIT;
    git_diff_find_options findopts   = GIT_DIFF_FIND_OPTIONS_INIT;
    findopts.rename_threshold        = c_diff.rename_threshold;
    findopts.copy_threshold          = c_diff.copy_threshold;
    findopts.break_rewrite_threshold = c_diff.break_rewrite_threshold;
    findopts.rename_limit            = c_diff.rename_limit;

    findopts.rename_from_rewrite_threshold = //
        c_diff.rename_from_rewrite_threshold;

    file_name_actions(state, result);

    SPtr<git_diff> diff = //
        git::diff_tree_to_tree(
            state->repo.get(), task.prev_tree.get(), task.this_tree.get(), &diffopts)
            .value();

    git_diff_find_similar(diff.get(), &findopts);

    int  deltas    = git::diff_num_deltas(diff.get());
    auto id_commit = task.id;

    for (int i = 0; i < deltas; ++i) {
        SPtr<git_patch>       patch = git::patch_from_diff(diff.get(), i).value();
        git_diff_delta const* delta = git::patch_get_delta(patch.get());

        char const* action_path = (delta->status == GIT_DELTA_DELETED)
                                    ? delta->old_file.path
                                    : delta->new_file.path;

        fs::path path{action_path};


        bool should_debug_path = state->should_debug()
                              && (state->should_check_file(path.native())
                                  || state->should_debug_commit(task.id));


        if (result.directory_paths.contains(path.native())) {
            HSLOG_IF(
                info,
                should_debug_path,
                "Delta contained directory-related changes (submodule "
                "addition) that were ignored. Path '{}' on commit {} with "
                "delta kind {}.",
                path,
                state->at(task.id).hash,
                delta->status);
            continue;
        }

        ir::FilePathId path_id = state->content->getFilePath(path);
        if (!result.actions.contains(path_id)) {
            result.actions[path_id] = CommitActionGroup{};
        }
        auto& actions = result.actions.at(path_id);

        LOGIC_ASSERTION_CHECK_FMT(
            result.actions.contains(path_id),
            "Missing action group for path '{}' path_id {} for commit {}, "
            "delta kind {}. The path is a known directory: {}",
            path,
            path_id,
            state->at(task.id).hash,
            delta->status,
            result.directory_paths.contains(path.native()));


        HSLOG_IF(
            info,
            should_debug_path,
            "[actions] File '{}' change {} at commit '{}'",
            path,
            delta->status,
            state->str(task.id));

        switch (delta->status) {
            case GIT_DELTA_DELETED: {
                actions.delete_action = FileDeleteAction{
                    .path = state->content->getFilePath(path)};
                break;
            }

            case GIT_DELTA_RENAMED:
            case GIT_DELTA_ADDED:
            case GIT_DELTA_MODIFIED: {
                maybe_file_rename(state, delta, actions);
                file_edit_actions(patch, state, id_commit, actions);
                if (delta->status == GIT_DELTA_MODIFIED) {
                    actions.modify_action = FileModifyAction{
                        .path  = state->content->getFilePath(path),
                        .added = (int)rs::count_if(
                            actions,
                            [](Action const& act) {
                                return std::holds_alternative<AddAction>(act);
                            }),
                        .removed = (int)rs::count_if(actions, [](Action const& act) {
                            return std::holds_alternative<RemoveAction>(act);
                        })};
                }
                break;
            }
            default: {
            }
        }
    }

    return result;
}

struct ChangeIterationState {
    walker_state*                                 state;
    UnorderedMap<ir::FilePathId, ir::FileTrackId> tracks;

    ir::FileTrackId which_track(ir::FilePathId path) {
        ir::FilePathId target_path = path;
        if (state->should_debug() && state->should_debug_file(path)) {
            HSLOG_INFO(
                "[state] File path ID {} '{}' resolved to {} '{}' "
                "has known track:{}",
                path,
                state->str(path),
                target_path,
                state->str(target_path),
                tracks.contains(target_path));
        }

        if (tracks.contains(target_path)) {
            return tracks.at(target_path);

        } else {
            ir::FileTrackId result = state->content->add(FileTrack{});
            tracks.insert({target_path, result});
            return result;
        }
    }

    void apply(ir::CommitId commit_id, FileRenameAction const& rename) {
        ir::FileTrackId prev_track = tracks.at(rename.prev_path);
        tracks.erase(rename.prev_path);
        tracks.insert_or_assign(rename.this_path, prev_track);

        state->at(commit_id).actions.push_back(
            ir::Commit::Action{
                .kind     = ir::Commit::ActionKind::Rename,
                .track    = prev_track,
                .old_path = rename.prev_path,
                .new_path = rename.this_path,
            });

        if (state->should_debug_file(rename.this_path)
            || state->should_debug_file(rename.prev_path)) {
            HSLOG_INFO(
                "[apply] File rename action, track {} moved from path "
                "'{}' to '{}'",
                prev_track,
                state->str(rename.prev_path),
                state->str(rename.this_path));
        }
    }

    void apply(ir::CommitId commit_id, FileDeleteAction const& del) {
        // FIXME main repository has commit that deletes already deleted
        // path
        if (tracks.contains(del.path)) {
            state->at(commit_id).actions.push_back(
                ir::Commit::Action{
                    .kind  = ir::Commit::ActionKind::Delete,
                    .track = tracks.at(del.path),
                    .file  = del.path,
                });

            tracks.erase(del.path);
        }
    }

    void apply(ir::CommitId commit_id, FileModifyAction const& del) {
        state->at(commit_id).actions.push_back(
            ir::Commit::Action{
                .kind    = ir::Commit::ActionKind::Modify,
                .track   = tracks.at(del.path),
                .file    = del.path,
                .added   = del.added,
                .removed = del.removed,
            });
    }

    std::string format_section_lines(ir::FileTrackSectionId section_id) {
        auto const& section = state->at(section_id);
        if (section.lines.empty()) {
            return "<no-lines>";
        } else {
            return std::string{"\n"}
                 + (state->at(section_id).lines //
                    | rv ::enumerate            //
                    | rv::transform([&](auto const& line) {
                          return std::format(
                              "[{:<4}] '{:<100}'",
                              line.first,
                              state->str(state->at(line.second).content));
                      })
                    | rv::intersperse("\n") //
                    | rv::join              //
                    | rs::to<std::string>());
        }
    }

    void apply(
        ir::FileTrackId        track,
        ir::FileTrackSectionId section_id,
        ir::CommitId           commit_id,
        AddAction const&       add) {

        ir::FileTrackSection& section = state->at(section_id);

        if (state->should_debug() && state->should_debug_file(section.path)) {
            HSLOG_INFO("[apply] {} '{}'", add, state->str(state->at(add.id).content));
        }

        int to_add = add.added;
        HSLOG_IF(
            info,
            !(to_add <= section.lines.size()),
            "[apply] Cannot add line at index {} from section of size {} path '{}' "
            "commit {} on track:{} {}",
            to_add,
            section.lines.size(),
            state->str(state->at(section.path).path),
            state->at(commit_id).hash,
            fmt1(add),
            track,
            format_section_lines(section_id));

        LOGIC_ASSERTION_CHECK_FMT(to_add <= section.lines.size(), "");

        section.added_lines.push_back(to_add);
        section.lines = section.lines.insert(to_add, add.id);
    }

    void apply(
        ir::FileTrackId        track,
        ir::FileTrackSectionId section_id,
        ir::CommitId           commit_id,
        RemoveAction const&    remove) {

        ir::FileTrackSection& section = state->at(section_id);
        if (state->should_debug() && state->should_debug_file(section.path)) {
            HSLOG_INFO("[apply] {}", remove);
        }

        int to_remove  = remove.removed;
        int lines_size = section.lines.size();

        if (!(to_remove < lines_size)) { state->dump_text_if_enabled(); }

        LOGIC_ASSERTION_CHECK_FMT(
            to_remove < lines_size,
            "[apply] Cannot apply remove {} on section {} path '{}' commit {} {} on "
            "track:{} {}",
            remove,
            section_id,
            state->str(state->at(section.path).path),
            state->at(commit_id).hash,
            remove,
            track,
            format_section_lines(section_id));

        auto remove_content = state->at(section.lines.at(to_remove)).content;

        HSLOG_IF(
            info,
            remove_content != remove.id,
            "[apply] Cannot remove line {} on path '{}' because string content IDs are "
            "mismatched. Current line content is {} and trying to remove it by a line "
            "with content {} line value compare '{}' != '{}' commit {} on track:{}{}",
            to_remove,
            state->str(state->at(section.path).path),
            fmt1(remove_content),
            fmt1(remove.id),
            state->str(remove_content),
            state->str(remove.id),
            state->at(commit_id).hash,
            track,
            format_section_lines(section_id));

        LOGIC_ASSERTION_CHECK_FMT(remove_content == remove.id, "");

        section.removed_lines.push_back(to_remove);
        section.lines = section.lines.erase(to_remove);
    }

    auto apply(ir::CommitId commit_id, NameAction const& name, CommitActionGroup const& g)
        -> Pair<ir::FileTrackId, ir::FileTrackSectionId> {
        LOGIC_ASSERTION_CHECK_FMT(!name.getPath().isNil(), "");
        auto const      p     = name.getPath();
        ir::FileTrackId track = which_track(p);

        if (state->should_debug_file(p) || state->should_debug_commit(commit_id)) {
            HSLOG_INFO(
                "[apply] Applying name action, path name '{}' track {}",
                state->str(p),
                track);
        }


        ir::FileTrack& tmp_track = state->at(track);

        auto section_id = state->content->add(
            FileTrackSection{
                .commit_id = commit_id,
                .path      = p,
                .track     = track,
            });

        ir::FileTrackSection& section = state->at(section_id);

        tmp_track.sections.push_back(section_id);

        if (state->should_debug_file(p)) {
            HSLOG_TRACE("track {} size {}", section_id, tmp_track.sections.size());
        }

        LOGIC_ASSERTION_CHECK_FMT(!section.path.isNil(), "");
        if (1 < tmp_track.sections.size()) {
            ir::FileTrackSectionId prev_section = tmp_track.sections.at(
                tmp_track.sections.size() - 2);
            if (state->should_debug_file(p)) {
                HSLOG_TRACE(
                    "prev section lines size {} at commit {}",
                    state->at(prev_section).lines.size(),
                    state->str(state->at(prev_section).commit_id));
            }

            if (g.rename_action) {
                HSLOG_INFO(
                    "Rename operation {} -> {} lines {}",
                    state->str(g.rename_action->prev_path),
                    state->str(g.rename_action->this_path),
                    state->at(prev_section).lines.size());
            }

            section.lines = state->at(prev_section).lines;
            LOGIC_ASSERTION_CHECK_FMT(
                state->at(prev_section).track == state->at(section_id).track,
                "[apply] New track section copied lines from the "
                "wrong track. Section {} is placed in track {}, but the previous section "
                "{} had track {}",
                section_id,
                state->at(section_id).track,
                prev_section,
                state->at(prev_section).track);
        }

        return {track, section_id};
    }
};

template <typename R1, typename R2>
auto zip_longest(R1 const& r1, R2 const& r2) {
    using OptionalT1 = Opt<rs::range_value_t<R1>>;
    using OptionalT2 = Opt<rs::range_value_t<R2>>;

    auto pad1 = rv::repeat_n(
        OptionalT1{}, std::max<int>(0, rs::distance(r2) - rs::distance(r1)));

    auto pad2 = rv::repeat_n(
        OptionalT2{}, std::max<int>(0, rs::distance(r1) - rs::distance(r2)));

    auto padded1 = rv::concat(
        r1 | rv::transform([](auto&& v) -> OptionalT1 {
            return OptionalT1{std::forward<decltype(v)>(v)};
        }),
        pad1);

    auto padded2 = rv::concat(
        r2 | rv::transform([](auto&& v) -> OptionalT2 {
            return OptionalT2{std::forward<decltype(v)>(v)};
        }),
        pad2);

    return rv::zip(padded1, padded2);
}

void check_tree_entry_consistency(
    walker_state*         state,
    ChangeIterationState& iter_state,
    CommitActions const&  commit_actions,
    char const*           root,
    git_tree_entry const* entry) {
    const git_object_t entry_type = git_tree_entry_type(entry);
    if (entry_type != GIT_OBJECT_BLOB) { return; }

    fs::path       path    = fs::path{root} / fs::path{git_tree_entry_name(entry)};
    ir::FilePathId path_id = state->content->getFilePath(path);

    if (!commit_actions.actions.contains(path_id)) {
        HSLOG_TRACE(
            "[state-verify] No file actions recorded for path {} on commit {}",
            path,
            state->at(commit_actions.id).hash);
        return;
    }

    if (!state->should_check_file(path.native())) { return; }

    ir::FileTrackId        track_id   = iter_state.which_track(path_id);
    ir::FileTrackSectionId section_id = state->at(track_id).sections.back();

    // Get the blob from the tree entry
    git_oid const* oid  = git_tree_entry_id(entry);
    SPtr<git_blob> blob = git::blob_lookup(state->repo.get(), oid).value();

    // Get the blob content
    char const* content_ptr = (const char*)git_blob_rawcontent(blob.get());

    ir::FileTrackSection const& section = state->at(section_id);

    std::string where = std::format(
        "section:{} track:{} file-path:\"{}\" "
        "section-path:{} track:{} section-index:{}",
        section_id,
        track_id,
        // state->at(commit_actions.id).hash,
        path,
        section.path,
        section.track,
        state->at(track_id).sections.size() - 1);

    auto content_lines = Str{content_ptr}.split('\n');

    std::string concat_content =                  //
        zip_longest(section.lines, content_lines) //
        | rv::enumerate                           //
        | rv::transform(
            [&](auto const& line_pair) -> std::tuple<int, std::string, std::string> {
                return std::tuple(
                    line_pair.first,
                    line_pair.second.first
                        ? state->str(state->at(*line_pair.second.first).content)
                        : "",
                    line_pair.second.second ? *line_pair.second.second : "");
            })
        | rv::transform([](auto const& line_tuple) -> std::string {
              return std::format(
                  "[{:<4}] [{}] '{:<100}' '{:<100}'",
                  std::get<0>(line_tuple),
                  std::get<1>(line_tuple) == std::get<2>(line_tuple) ? "ok" : "er",
                  std::get<1>(line_tuple),
                  std::get<2>(line_tuple));
          })
        | rv::intersperse("\n") //
        | rv::join              //
        | rs::to<std::string>();

    HSLOG_IF(
        warning,
        content_lines.size() != section.lines.size(),
        "[state-verify] Section lines size and content lines size mismatch: "
        "commit-hash:{} section:{} content:{} where:{}\nfull content:\n{}",
        state->at(commit_actions.id).hash,
        section.lines.size(),
        content_lines.size(),
        where,
        concat_content);

    LOGIC_ASSERTION_CHECK_FMT(content_lines.size() == section.lines.size(), "");

    for (auto const& [idx, pair] :
         rv::zip(section.lines, content_lines) | rv::enumerate) {

        Str const& section_line = state->str(state->at(pair.first).content);
        Str const& content_line{pair.second};

        HSLOG_IF(
            warning,
            section_line != content_line,
            "[state-verify] Line {} compare at did not match, "
            "section:'{}' != "
            "content:'{}', file '{}', {}\nfull content:\n{}",
            idx,
            section_line,
            content_line,
            path,
            where,
            concat_content);
        LOGIC_ASSERTION_CHECK_FMT(section_line == content_line, "");
    }

    if (false) {
        HSLOG_INFO(
            "[state-verify] {} ok at commit {} line count {}",
            where,
            state->at(commit_actions.id).hash,
            section.lines.size());
    }
}

void for_each_commit(CommitGraph& g, walker_state* state) {
    HSLOG_INFO("Getting list of files changed per each commit");
    __perf_trace("repo", "For each commit");

    git_commit*     prev = nullptr;
    Vec<CommitTask> tasks;

    using VDesc = CommitGraph::VDesc;

    std::unordered_map<VDesc, SPtr<git_tree>> trees;

    auto get_tree = [&trees, state, &g](VDesc v) -> SPtr<git_tree> {
        if (trees.find(v) == trees.end()) {
            auto commit = git::commit_lookup(state->repo.get(), &g[v].oid).value();
            trees[v]    = git::commit_tree(commit.get()).value();
        }
        return trees[v];
    };

    auto make_task = [&](Pair<VDesc, Opt<VDesc>> const& pair) -> Opt<CommitTask> {
        auto [main, base] = pair;

        auto task = CommitTask{
            .id        = state->get_id(g[main].oid),
            .prev_tree = base ? get_tree(base.value()) : nullptr,
            .this_tree = get_tree(main),
            .prev_hash = base ? Opt<git_oid>{g[base.value()].oid} : Opt<git_oid>{},
            .this_hash = g[main].oid,
        };

        return task;
    };

    auto commit_ordering = g.commit_pairs();
    // Mutable iteration state internally implements state machine that
    // keeps track of the current file track, relevant renames and
    // target file section
    ChangeIterationState iter_state{.state = state};
    for (CommitActions const& commit_actions :
         commit_ordering
             // package each commit pair into a commit processing task
             //
             // FIXME 'make task' is called twice in this pipeline. It
             // does not produce any extra values, but it looks like
             // the whole thing might be recomputated too many times.
             // Tests for the range algorithm logic are sorely missing
             // at the moment.
             | rv::transform(make_task)
             // Filter out skipped commit tasks
             | rv::remove_if(
                 [](Opt<CommitTask> const& opt) -> bool { return !opt.has_value(); })
             | rv::transform(
                 [](Opt<CommitTask> const& opt) -> CommitTask { return opt.value(); })
             // Expand each commit task into list of actions applied to
             // a file in this particular commit -- list of events that
             // state machine will respond to.
             | rv::transform([&state](CommitTask const& task) {
                   LOGIC_ASSERTION_CHECK_FMT(
                       !task.id.isNil(), "commit task ID cannot be nil");
                   return get_commit_actions(state, task);
               })) {

        __perf_trace(
            "repo", "Actions for commit", "hash", state->at(commit_actions.id).hash);

        if (state->should_debug_commit(commit_actions.id)) {
            HSLOG_INFO(
                "[mainloop] Processing commit {}", state->at(commit_actions.id).hash);
        }

        for (auto const& [file_id, actions] : commit_actions.actions) {
            __perf_trace(
                "repo", "Actions for file", "path", state->str(state->at(file_id).path));
            if (state->should_debug_file(file_id)
                || state->should_debug_commit(commit_actions.id)) {
                HSLOG_INFO(
                    "[mainloop] New action on file {} {} in commit {}: {}",
                    file_id,
                    state->str(state->at(file_id).path),
                    state->str(commit_actions.id),
                    actions);
                // for (auto const& a : actions) { HSLOG_TRACE("  {}", a); }
            }

            if (actions.rename_action) {
                iter_state.apply(commit_actions.id, *actions.rename_action);
            }

            if (actions.delete_action) {
                iter_state.apply(commit_actions.id, *actions.delete_action);
            }

            if (actions.modify_action) {
                iter_state.apply(commit_actions.id, *actions.modify_action);
            }

            // Apply actions to the commit iteration state. It will
            // insert new file tracks, keep track of the historical
            // context of the repo changes and so on.
            Opt<Pair<ir::FileTrackId, ir::FileTrackSectionId>> target_section;
            if (actions.leading_name) {
                target_section = iter_state.apply(
                    commit_actions.id, *actions.leading_name, actions);
            }

            rs::for_each(actions, [&](auto const& edit) {
                LOGIC_ASSERTION_CHECK_FMT(target_section.has_value(), "");
                std::visit(
                    [&](auto const& act) {
                        iter_state.apply(
                            target_section->first,
                            target_section->second,
                            commit_actions.id,
                            act);
                    },
                    edit);
            });
        }


        if (state->should_debug() || state->should_debug_commit(commit_actions.id)) {
            git_tree_walk_lambda(
                commit_actions.this_tree,
                [&](char const* root, git_tree_entry const* entry) -> int {
                    check_tree_entry_consistency(
                        state, iter_state, commit_actions, root, entry);
                    return 0;
                });
        }
    }
}

CommitId process_commit(git_oid commit_oid, walker_state* state) {
    SPtr<git_commit> commit = git::commit_lookup(state->repo.get(), &commit_oid).value();
    auto             hash   = oid_tostr(*git_commit_id(commit.get()));
    auto signature = const_cast<git_signature*>(git::commit_author(commit.get()));

    return state->content->add(
        Commit{
            .author = state->content->add(
                Author{.name = Str{signature->name}, .email = Str{signature->email}}),
            .time     = git::commit_time(commit.get()),
            .timezone = git::commit_time_offset(commit.get()),
            .hash     = hash,
            .message  = Str{git_commit_message(commit.get())},
        });
}


CommitGraph build_repo_graph(git_oid& oid, walker_state* state) {
    __perf_trace("repo", "build repo graph main");
    // All constructed information
    Vec<CommitId> processed{};
    // Walk over every commit in the history
    Vec<FullCommitData> full_commits;
    while (git::revwalk_next(&oid, state->walker.get()) == 0) {
        // Get commit from the provided oid
        SPtr<git_commit> commit = git::commit_lookup(state->repo.get(), &oid).value();
        // Convert from unix timestamp used by git to humane format
        PTime date = boost::posix_time::from_time_t(git::commit_time(commit.get()));

        auto id = process_commit(oid, state);
        full_commits.push_back({oid, date, commit, id});
        state->add_id_mapping(oid, id);
    }

    std::ranges::reverse(full_commits);

    // Push information about all known commits to the full list
    for (const auto& [commit, date, _, id] : full_commits) {
        if (state->config->cli.config.target_commit_subset.empty()
            || state->config->cli.config.target_commit_subset.contains(state->str(id))) {
            state->add_full_commit(commit);
        }
    }

    __perf_trace("repo", "construct repo graph structure");
    return CommitGraph{state->repo, state->config->cli.repo.branch};
}
