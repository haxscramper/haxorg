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

#include <boost/asio/thread_pool.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <boost/asio/post.hpp>

#include <algorithm>

#include <hstd/stdlib/Ranges.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Variant.hpp>

using namespace ir;

int get_nesting(CR<Str> line) {
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
    fs::path head_filepath = state.config->repo_path()
                           / state.config->heads_path();
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
            std::error_code{},
            fmt("Error reading from {}", head_filepath)};
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
    BOOST_DESCRIBE_CLASS(RemoveAction, (), (removed), (), ());
};

struct AddAction {
    int        added;
    ir::LineId id;
    BOOST_DESCRIBE_CLASS(AddAction, (), (added, id), (), ());
};

struct FileRenameAction {
    ir::FilePathId prev_path;
    ir::FilePathId this_path;
    BOOST_DESCRIBE_CLASS(
        FileRenameAction,
        (),
        (prev_path, this_path),
        (),
        ());
};

struct FileDeleteAction {
    ir::FilePathId path;
    BOOST_DESCRIBE_CLASS(FileDeleteAction, (), (path), (), ());
};

struct NameAction {
    NameAction(ir::FilePathId path) : path(path) { CHECK(!path.isNil()); }
    BOOST_DESCRIBE_CLASS(NameAction, (), (path), (), ());
    ir::FilePathId getPath() const {
        CHECK(!path.isNil());
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
};

struct CommitActionGroup : Vec<Action> {
    Opt<NameAction>       leading_name;
    Opt<FileRenameAction> rename_action;
    Opt<FileDeleteAction> delete_action;
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
    if (delta->old_file.path
        && strcmp(delta->old_file.path, delta->new_file.path) != 0) {
        auto old_path = state->content->getFilePath(delta->old_file.path);

        if (state->do_checks()) {
            LOG(INFO) << std::format(
                "[actions] File rename from '{}' to '{}', ID mapping is: "
                "new:{} -> old:{}",
                delta->old_file.path,
                delta->new_file.path,
                new_path,
                old_path);
        }

        actions.rename_action = FileRenameAction{
            .this_path = new_path,
            .prev_path = old_path,
        };
    }
}

void line_edit_action(
    walker_state*        state,
    git_diff_line const* line,
    Vec<Action>&         delete_actions,
    Vec<Action>&         add_actions,
    ir::CommitId         id_commit) {
    ir::StringId string_id = state->content->add(String{strip(
        Str{line->content, static_cast<int>(line->content_len)},
        {},
        {'\n'})});

    switch (line->origin) {
        case GIT_DIFF_LINE_ADDITION: {
            ir::LineId line_id = state->content->add(LineData{
                .content = string_id,
                .commit  = id_commit,
            });


            add_actions.push_back(AddAction{
                .added = line->new_lineno - 1,
                .id    = line_id,
            });
            break;
        }

        case GIT_DIFF_LINE_DELETION: {
            delete_actions.push_back(RemoveAction{
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
            git_patch_get_line_in_hunk(
                &line, patch.get(), hunk_idx, line_idx);
            line_edit_action(
                state, line, delete_actions, add_actions, id_commit);
        }
    }

    std::reverse(delete_actions.begin(), delete_actions.end());
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
        result.this_tree,
        [&](char const* root, git_tree_entry const* entry) -> int {
            const git_object_t entry_type = git_tree_entry_type(entry);
            auto               path       = fs::path{root}
                      / fs::path{git_tree_entry_name(entry)};
            if (entry_type == GIT_OBJECT_BLOB) {

                auto  track   = state->content->getFilePath(path);
                auto& actions = result.actions[track];
                CHECK(!actions.leading_name);
                actions.leading_name = NameAction{
                    state->content->getFilePath(path)};
            } else if (
                entry_type == GIT_OBJECT_TREE
                || entry_type == GIT_OBJECT_COMMIT) {
                result.directory_paths.incl(path.native());
            } else {
                LOG(INFO) << std::format(
                    "Commit has '{}' with type {}",
                    path.native(),
                    entry_type);
            }
            return 0;
        });
}

CommitActions get_commit_actions(
    walker_state*  state,
    CR<CommitTask> task) {
    CommitActions result{.id = task.id, .this_tree = task.this_tree};
    LOG_IF(INFO, state->should_debug_commit(task.id)) << std::format(
        "[actions] Generating list of actions for commit {}",
        state->str(task.id));

    git_diff_options      diffopts         = GIT_DIFF_OPTIONS_INIT;
    git_diff_find_options findopts         = GIT_DIFF_FIND_OPTIONS_INIT;
    findopts.rename_threshold              = 50;
    findopts.rename_from_rewrite_threshold = 50;
    findopts.copy_threshold                = 50;
    findopts.break_rewrite_threshold       = 60;
    findopts.rename_limit                  = 1000;

    file_name_actions(state, result);

    SPtr<git_diff> diff = git::diff_tree_to_tree(
                              state->repo.get(),
                              task.prev_tree.get(),
                              task.this_tree.get(),
                              &diffopts)
                              .value();

    git_diff_find_similar(diff.get(), &findopts);

    int  deltas    = git::diff_num_deltas(diff.get());
    auto id_commit = task.id;

    for (int i = 0; i < deltas; ++i) {
        SPtr<git_patch> patch = git::patch_from_diff(diff.get(), i)
                                    .value();
        const git_diff_delta* delta = git::patch_get_delta(patch.get());
        fs::path              path{delta->new_file.path};

        bool should_debug_path = state->do_checks()
                              && (state->should_check_file(path.native())
                                  || state->should_debug_commit(task.id));


        if (result.directory_paths.contains(path.native())) {
            LOG_IF(INFO, should_debug_path) << std::format(
                "Delta contained directory-related changes (submodule "
                "addition) that were ignored. Path '{}' on commit {} with "
                "delta kind {}.",
                path,
                state->at(task.id).hash,
                delta->status);

            continue;
        }

        ir::FilePathId path_id = state->content->getFilePath(path);

        if (delta->status == GIT_DELTA_DELETED) {
            CHECK(!result.actions.contains(path_id));
            result.actions[state->content->getFilePath(path)].leading_name = NameAction{
                state->content->getFilePath(path)};
        }

        CHECK(result.actions.contains(path_id)) << std::format(
            "Missing action group for path '{}' path_id {} for commit {}, "
            "delta kind {}. The path is a known directory: {}",
            path,
            path_id,
            state->at(task.id).hash,
            delta->status,
            result.directory_paths.contains(path.native()));

        auto& actions = result.actions.at(path_id);

        LOG_IF(INFO, should_debug_path) << std::format(
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
                break;
            }
            default: {
            }
        }
    }

    return result;
}

struct ChangeIterationState {
    walker_state* state;


    // Keep track of the mapping between file path and file track IDs.
    // When a file is seen for the first time a track is created for,
    // with later renames adding a layer of indirection.
    // `path1->path2->path3` -- when changes are made to the `path3` in
    // some commit, the corresponding file track should be the same as
    // `path1` and `path2`.
    UnorderedMap<ir::FilePathId, ir::FileTrackId> tracks;
    UnorderedMap<ir::FilePathId, ir::FilePathId>  active_track_renames;

    ir::FileTrackId which_track(ir::FilePathId path) {
        ir::FilePathId target_path = path;

        Vec<ir::FilePathId> track_history;
        track_history.push_back(target_path);

        while (active_track_renames.contains(target_path)) {
            target_path = active_track_renames.at(target_path);
            track_history.push_back(target_path);
        }

        if (state->do_checks() && state->should_check_file(path)) {
            LOG(INFO) << std::format(
                "[state] File path ID {} '{}' resolved via {} to {} '{}' "
                "has known track:{}",
                path,
                state->str(path),
                track_history,
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

    void apply(ir::CommitId commit_id, CR<FileRenameAction> rename) {
        active_track_renames.insert_or_assign(
            rename.this_path, rename.prev_path);

        if (state->do_checks()
            && (state->should_check_file(rename.this_path)
                || state->should_check_file(rename.prev_path))) {
            LOG(INFO) << std::format(
                "[apply] File rename action, track renames: {}",
                active_track_renames);
        }
    }

    void apply(ir::CommitId commit_id, CR<FileDeleteAction> del) {
        // Active track renames are fully reset when a file is deleted
        // -- all historical context is dropped when a file is cleaned
        // up from the index. If a new file is added with the same
        // name, it will have a new file track history.
        ir::FilePathId to_delete = del.path;
        while (active_track_renames.contains(to_delete)) {
            auto tmp  = to_delete;
            to_delete = active_track_renames.at(to_delete);
            active_track_renames.erase(tmp);
        }

        tracks.erase(to_delete);
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
        CR<AddAction>          add) {
        ir::FileTrackSection& section = state->at(section_id);

        if (state->do_checks() && state->should_check_file(section.path)) {
            LOG(INFO) << std::format("[apply] {}", add);
        }

        int to_add = add.added;
        LOG_IF(INFO, !(to_add <= section.lines.size()))
            << "[apply] Cannot add line at index " << to_add
            << " from section of size " << section.lines.size()
            << " path '" << state->str(state->at(section.path).path)
            << "' commit " << state->at(commit_id).hash << " " << fmt1(add)
            << std::format(" on track:{}", track)
            << format_section_lines(section_id);

        CHECK(to_add <= section.lines.size());

        section.added_lines.push_back(to_add);
        section.lines = section.lines.insert(to_add, add.id);
    }

    void apply(
        ir::FileTrackId        track,
        ir::FileTrackSectionId section_id,
        ir::CommitId           commit_id,
        CR<RemoveAction>       remove) {

        ir::FileTrackSection& section = state->at(section_id);
        if (state->do_checks() && state->should_check_file(section.path)) {
            LOG(INFO) << std::format("[apply] {}", remove);
        }

        int to_remove  = remove.removed;
        int lines_size = section.lines.size();

        CHECK(to_remove < lines_size)
            << "[apply] Cannot remove line index " << to_remove
            << " from section version " << section.lines.size()
            << " path '" << state->str(state->at(section.path).path)
            << "' commit " << state->at(commit_id).hash << " "
            << fmt1(remove) << std::format(" on track:{}", track)
            << format_section_lines(section_id);

        auto remove_content = state->at(section.lines.at(to_remove))
                                  .content;

        LOG_IF(INFO, remove_content != remove.id)
            << "[apply] Cannot remove line " << to_remove << " on path '"
            << state->str(state->at(section.path).path)
            << "' because string content IDs are mismatched. Current "
               "line content is "
            << fmt1(remove_content)
            << " and trying to remove it by a line with content "
            << fmt1(remove.id)
            << std::format(
                   " line value compare '{}' != '{}'",
                   state->str(remove_content),
                   state->str(remove.id))
            << " commit " << state->at(commit_id).hash
            << std::format(" on track:{}", track)
            << format_section_lines(section_id);

        CHECK(remove_content == remove.id);

        section.removed_lines.push_back(to_remove);
        section.lines = section.lines.erase(to_remove);
    }

    auto apply(ir::CommitId commit_id, CR<NameAction> name)
        -> Pair<ir::FileTrackId, ir::FileTrackSectionId> {
        CHECK(!name.getPath().isNil());
        ir::FileTrackId track = which_track(name.getPath());

        if (state->do_checks()
            && state->should_check_file(name.getPath())) {
            LOG(INFO) << std::format(
                "[apply] Applying name action, path name '{}' track {}",
                state->str(name.getPath()),
                track);
        }


        ir::FileTrack& tmp_track = state->at(track);

        auto section_id = state->content->add(FileTrackSection{
            .commit_id = commit_id,
            .path      = name.getPath(),
            .track     = track,
        });

        ir::FileTrackSection& section = state->at(section_id);

        tmp_track.sections.push_back(section_id);

        CHECK(!section.path.isNil());
        if (1 < tmp_track.sections.size()) {
            ir::FileTrackSectionId prev_section = tmp_track.sections.at(
                tmp_track.sections.size() - 2);
            section.lines = state->at(prev_section).lines;
            CHECK(
                state->at(prev_section).track
                == state->at(section_id).track)
                << std::format(
                       "[apply] New track section copied lines from the "
                       "wrong "
                       "track. Section {} is placed in track {}, but the "
                       "previous section {} had track {}",
                       section_id,
                       state->at(section_id).track,
                       prev_section,
                       state->at(prev_section).track);
        }

        return {track, section_id};
    }
};

template <typename R1, typename R2>
auto zip_longest(const R1& r1, const R2& r2) {
    using OptionalT1 = Opt<rs::range_value_t<R1>>;
    using OptionalT2 = Opt<rs::range_value_t<R2>>;

    auto pad1 = rv::repeat_n(
        OptionalT1{},
        std::max<int>(0, rs::distance(r2) - rs::distance(r1)));

    auto pad2 = rv::repeat_n(
        OptionalT2{},
        std::max<int>(0, rs::distance(r1) - rs::distance(r2)));

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
    if (entry_type != GIT_OBJECT_BLOB) {
        return;
    }

    fs::path path = fs::path{root} / fs::path{git_tree_entry_name(entry)};
    ir::FilePathId path_id = state->content->getFilePath(path);

    if (!commit_actions.actions.contains(path_id)) {
        LOG(INFO) << "[state-verify] No file actions recorded for path "
                  << path << " on commit "
                  << state->at(commit_actions.id).hash;
        return;
    }

    if (!state->should_check_file(path.native())) {
        return;
    }

    ir::FileTrackId        track_id   = iter_state.which_track(path_id);
    ir::FileTrackSectionId section_id = state->at(track_id)
                                            .sections.back();

    // Get the blob from the tree entry
    const git_oid* oid  = git_tree_entry_id(entry);
    SPtr<git_blob> blob = git::blob_lookup(state->repo.get(), oid).value();

    // Get the blob content
    const char* content_ptr = (const char*)git_blob_rawcontent(blob.get());

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
            [&](auto const& line_pair)
                -> std::tuple<int, std::string, std::string> {
                return std::tuple(
                    line_pair.first,
                    line_pair.second.first ? state->str(
                        state->at(*line_pair.second.first).content)
                                           : "",
                    line_pair.second.second ? *line_pair.second.second
                                            : "");
            })
        | rv::transform([](auto const& line_tuple) -> std::string {
              return std::format(
                  "[{:<4}] [{}] '{:<100}' '{:<100}'",
                  std::get<0>(line_tuple),
                  std::get<1>(line_tuple) == std::get<2>(line_tuple)
                      ? "ok"
                      : "er",
                  std::get<1>(line_tuple),
                  std::get<2>(line_tuple));
          })
        | rv::intersperse("\n") //
        | rv::join              //
        | rs::to<std::string>();

    LOG_IF(INFO, content_lines.size() != section.lines.size())
        << std::format(
               "[state-verify] Section lines size and content lines size "
               "mismatch: "
               "commit-hash:{} section:{} "
               "content:{} where:{}\nfull content:\n{}",
               state->at(commit_actions.id).hash,
               section.lines.size(),
               content_lines.size(),
               where,
               concat_content);

    CHECK(content_lines.size() == section.lines.size());

    for (auto const& [idx, pair] :
         rv::zip(section.lines, content_lines) | rv::enumerate) {

        Str const& section_line = state->str(
            state->at(pair.first).content);
        Str const& content_line{pair.second};

        LOG_IF(INFO, section_line != content_line) << std::format(
            "[state-verify] Line {} compare at did not match, "
            "section:'{}' != "
            "content:'{}', file '{}', {}\nfull content:\n{}",
            idx,
            section_line,
            content_line,
            path,
            where,
            concat_content);
        CHECK(section_line == content_line);
    }

    LOG(INFO) << std::format(
        "[state-verify] {} ok at commit {} line count {}",
        where,
        state->at(commit_actions.id).hash,
        section.lines.size());
}

void for_each_commit(CommitGraph& g, walker_state* state) {
    LOG(INFO) << "Getting list of files changed per each commit";
    TRACE_EVENT("repo", "For each commit");

    git_commit*     prev = nullptr;
    Vec<CommitTask> tasks;

    using VDesc = CommitGraph::VDesc;

    std::unordered_map<VDesc, SPtr<git_tree>> trees;

    auto get_tree = [&trees, state, &g](VDesc v) -> SPtr<git_tree> {
        if (trees.find(v) == trees.end()) {
            auto commit = git::commit_lookup(state->repo.get(), &g[v].oid)
                              .value();
            trees[v] = git::commit_tree(commit.get()).value();
        }
        return trees[v];
    };

    auto make_task =
        [&](Pair<VDesc, Opt<VDesc>> const& pair) -> Opt<CommitTask> {
        auto [main, base] = pair;

        auto task = CommitTask{
            .id        = state->get_id(g[main].oid),
            .prev_tree = base ? get_tree(base.value()) : nullptr,
            .this_tree = get_tree(main),
            .prev_hash = base ? Opt<git_oid>{g[base.value()].oid}
                              : Opt<git_oid>{},
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
             | rv::remove_if([](Opt<CommitTask> const& opt) -> bool {
                   return !opt.has_value();
               })
             | rv::transform([](Opt<CommitTask> const& opt) -> CommitTask {
                   return opt.value();
               })
             // Expand each commit task into list of actions applied to
             // a file in this particular commit -- list of events that
             // state machine will respond to.
             | rv::transform([&state](CR<CommitTask> task) {
                   return get_commit_actions(state, task);
               })) {

        TRACE_EVENT(
            "repo",
            "Actions for commit",
            "hash",
            state->at(commit_actions.id).hash);

        if (state->do_checks()
            && state->should_debug_commit(commit_actions.id)) {
            LOG(INFO) << std::format(
                "[mainloop] Processing commit {}",
                state->at(commit_actions.id).hash);
        }

        for (auto const& [file_id, actions] : commit_actions.actions) {
            TRACE_EVENT(
                "repo",
                "Actions for file",
                "path",
                state->str(state->at(file_id).path));
            if (state->do_checks() && state->should_check_file(file_id)) {
                LOG(INFO) << std::format(
                    "[mainloop] New action on file {} {}",
                    file_id,
                    state->str(state->at(file_id).path));
            }

            if (actions.rename_action) {
                iter_state.apply(
                    commit_actions.id, *actions.rename_action);
            }

            if (actions.delete_action) {
                iter_state.apply(
                    commit_actions.id, *actions.delete_action);
            }

            auto [track_id, section_id] = iter_state.apply(
                commit_actions.id, actions.leading_name.value());
            // Apply actions to the commit iteration state. It will
            // insert new file tracks, keep track of the historical
            // context of the repo changes and so on.
            rs::for_each(actions, [&](auto const& edit) {
                std::visit(
                    [&](auto const& act) {
                        iter_state.apply(
                            track_id, section_id, commit_actions.id, act);
                    },
                    edit);
            });
        }


        if (state->do_checks()
            || state->should_debug_commit(commit_actions.id)) {
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
    SPtr<git_commit> commit = git::commit_lookup(
                                  state->repo.get(), &commit_oid)
                                  .value();
    auto hash      = oid_tostr(*git_commit_id(commit.get()));
    auto signature = const_cast<git_signature*>(
        git::commit_author(commit.get()));

    return state->content->add(Commit{
        .author   = state->content->add(Author{
              .name = Str{signature->name}, .email = Str{signature->email}}),
        .time     = git::commit_time(commit.get()),
        .timezone = git::commit_time_offset(commit.get()),
        .hash     = hash,
        .message  = Str{git_commit_message(commit.get())},
    });
}


CommitGraph build_repo_graph(git_oid& oid, walker_state* state) {
    TRACE_EVENT("repo", "build repo graph main");
    // All constructed information
    Vec<CommitId> processed{};
    // Walk over every commit in the history
    Vec<FullCommitData> full_commits;
    while (git::revwalk_next(&oid, state->walker.get()) == 0) {
        // Get commit from the provided oid
        SPtr<git_commit>
            commit = git::commit_lookup(state->repo.get(), &oid).value();
        // Convert from unix timestamp used by git to humane format
        PTime date = boost::posix_time::from_time_t(
            git::commit_time(commit.get()));

        auto id = process_commit(oid, state);
        full_commits.push_back({oid, date, commit, id});
        state->add_id_mapping(oid, id);
    }

    std::reverse(full_commits.begin(), full_commits.end());

    // Push information about all known commits to the full list
    for (const auto& [commit, date, _, __] : full_commits) {
        state->add_full_commit(commit);
    }

    TRACE_EVENT("repo", "construct repo graph structure");
    return CommitGraph{state->repo, state->config->cli.repo.branch};
}
