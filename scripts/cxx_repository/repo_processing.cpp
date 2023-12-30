/// \file repo_processing.cpp \brief repository processing algorithms
#include "repo_processing.hpp"
#include "git_interface.hpp"
#include "repo_graph.hpp"
#include <git2/patch.h>
#include <hstd/stdlib/Map.hpp>
#include <immer/flex_vector_transient.hpp>
#include <fstream>

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
    fs::path head_filepath = fs::path{state.config->repo.toBase()}
                           / fs::path{state.config->heads.toBase()};
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
    ir::FilePathId path;
    BOOST_DESCRIBE_CLASS(NameAction, (), (path), (), ());
};

using Action = Variant<
    NameAction,
    FileRenameAction,
    RemoveAction,
    AddAction,
    FileDeleteAction>;


struct CommitTask {
    CommitId       id;
    SPtr<git_tree> prev_tree;
    SPtr<git_tree> this_tree;
    Opt<git_oid>   prev_hash;
    git_oid        this_hash;
};

struct CommitActions {
    UnorderedMap<ir::FilePathId, Vec<Action>> actions;
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
    Vec<Action>&          actions) {
    auto new_path = state->content->getFilePath(delta->new_file.path);
    if (delta->old_file.path
        && strcmp(delta->old_file.path, delta->new_file.path) != 0) {
        auto old_path = state->content->getFilePath(delta->old_file.path);
        actions.push_back(FileRenameAction{
            .this_path = new_path,
            .prev_path = old_path,
        });
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

void file_name_actions(
    walker_state*  state,
    CommitActions& result,
    CR<CommitTask> task) {
    auto [trampoline, lambda] = git_callback_wrapper(
        Func<int(char const*, git_tree_entry const*)>(
            [&](char const* root, git_tree_entry const* entry) -> int {
                auto path  = fs::path{git_tree_entry_name(entry)};
                auto track = state->content->getFilePath(path);
                result.actions[track].push_back(
                    NameAction{.path = state->content->getFilePath(path)});
                result.actions[track];
                return 0;
            }));

    git_tree_walk(
        task.this_tree.get(), GIT_TREEWALK_PRE, trampoline, &lambda);
}

CommitActions get_commit_actions(
    walker_state*  state,
    CR<CommitTask> task) {
    CommitActions         result;
    git_diff_options      diffopts = GIT_DIFF_OPTIONS_INIT;
    git_diff_find_options findopts = GIT_DIFF_FIND_OPTIONS_INIT;
    // Assigned values are said to be 'default' in the libgit documentation
    findopts.rename_threshold              = 50;
    findopts.rename_from_rewrite_threshold = 50;
    findopts.copy_threshold                = 50;
    findopts.break_rewrite_threshold       = 60;
    findopts.rename_limit                  = 1000;

    file_name_actions(state, result, task);

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

        fs::path path{
            delta->old_file.path == nullptr ? delta->new_file.path
                                            : delta->old_file.path};
        ir::FilePathId track   = state->content->getFilePath(path);
        auto&          actions = result.actions[track];

        switch (delta->status) {
            case GIT_DELTA_DELETED: {
                actions.push_back(FileDeleteAction{
                    .path = state->content->getFilePath(path)});
                break;
            }
            default: {
                maybe_file_rename(state, delta, actions);
                file_edit_actions(patch, state, id_commit, actions);
            }
        }
    }

    return result;
}

struct ChangeIterationState {
    walker_state* state;

    FileTrack*            track;
    ir::FileTrackSection* section;

    // Keep track of the mapping between file path and file track IDs. When
    // a file is seen for the first time a track is created for, with later
    // renames adding a layer of indirection. `path1->path2->path3` -- when
    // changes are made to the `path3` in some commit, the corresponding
    // file track should be the same as `path1` and `path2`.
    UnorderedMap<ir::FilePathId, ir::FileTrackId> tracks;
    UnorderedMap<ir::FilePathId, ir::FilePathId>  active_track_renames;

    ir::FileTrackId which_track(ir::FilePathId path) {
        ir::FilePathId target_path = path;
        while (active_track_renames.contains(target_path)) {
            target_path = active_track_renames.at(target_path);
        }

        if (tracks.contains(target_path)) {
            return tracks.at(target_path);
        } else {
            ir::FileTrackId result = state->content->add(FileTrack{});
            tracks.insert({target_path, result});
            return result;
        }
    }

    UnorderedMap<ir::FileTrackId, Vec<Action>> actions;

    void apply(ir::CommitId commit_id, CR<FileRenameAction> rename) {
        active_track_renames.insert_or_assign(
            rename.this_path, rename.prev_path);
    }

    void apply(ir::CommitId commit_id, CR<FileDeleteAction> del) {
        // Active track renames are fully reset when a file is deleted --
        // all historical context is dropped when a file is cleaned up from
        // the index. If a new file is added with the same name, it will
        // have a new file track history.
        ir::FilePathId to_delete = del.path;
        while (active_track_renames.contains(to_delete)) {
            auto tmp  = to_delete;
            to_delete = active_track_renames.at(to_delete);
            active_track_renames.erase(tmp);
        }

        tracks.erase(to_delete);
    }

    void apply(ir::CommitId commit_id, CR<AddAction> add) {
        int to_add = add.added;
        CHECK(to_add <= section->lines.size())
            << "Cannot add line at index " << to_add
            << " from section version " << section->lines.size()
            << " path " << state->at(state->at(section->path).path).text
            << " commit " << state->at(section->commit_id).hash << " "
            << fmt1(add);

        section->added_lines.push_back(to_add);
        section->lines = section->lines.insert(to_add, add.id);
    }

    void apply(ir::CommitId commit_id, CR<RemoveAction> remove) {
        int to_remove  = remove.removed;
        int lines_size = section->lines.size();

        CHECK(
            state->at(section->lines.at(to_remove)).content == remove.id);

        CHECK(to_remove <= lines_size)
            << "Cannot remove line index " << to_remove
            << " from section version " << section->lines.size()
            << " path " << state->at(state->at(section->path).path).text
            << " commit " << state->at(section->commit_id).hash << " "
            << fmt1(remove);


        section->removed_lines.push_back(to_remove);
        section->lines = section->lines.erase(to_remove);
    }

    void apply(ir::CommitId commit_id, CR<NameAction> name) {
        ir::FileTrackId track_id = which_track(name.path);
        this->track              = &state->at(track_id);

        auto section_id = state->content->add(FileTrackSection{
            .commit_id = commit_id,
            .path      = name.path,
            .track     = track_id,
        });

        track->sections.push_back(section_id);

        section = &state->at(section_id);
        if (1 < track->sections.size()) {
            section->lines = state
                                 ->at(track->sections.at(
                                     track->sections.size() - 2))
                                 .lines;
        }
    }
};

void for_each_commit(CommitGraph& g, walker_state* state) {
    LOG(INFO) << "Getting list of files changed per each commit";

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

    auto expand_commit_task = [&](CommitTask const& task) {
        // `own_view` is used to avoid result of the commit
        // actions getter going out of scope.
        return own_view(std::move(get_commit_actions(state, task).actions))
             // Expand each commit action group into own
             // transformation range generator
             | rv::transform(
                   [id = task.id](const auto& pair)
                       -> std::tuple<ir::CommitId, Vec<Action>> {
                       return std::make_tuple(id, pair.second);
                   });
    };

    // Mutable iteration state internally implements state machine that
    // keeps track of the current file track, relevant renames and target
    // file section
    ChangeIterationState iter_state{.state = state};
    for (auto const& [commit_id, actions] :
         gen_view(g.commit_pairs())
             // make the commit pairs list reversible
             | make_collect()
             // start from the first commit
             | rv::reverse
             // TODO allow arbitrary N of commits
             // | rv::take(10)
             // package each commit pair into a commit processing task
             //
             // FIXME 'make task' is called twice in this pipeline. It does
             // not produce any extra values, but it looks like the whole
             // thing might be recomputated too many times. Tests for the
             // range algorithm logic are sorely missing at the moment.
             | rv::transform(make_task)
             // Filter out skipped commit tasks
             | rv::remove_if([](Opt<CommitTask> const& opt) -> bool {
                   return !opt.has_value();
               })
             | rv::transform([](Opt<CommitTask> const& opt) -> CommitTask {
                   return opt.value();
               })
             // Expand each commit task into list of actions applied to a
             // file in this particular commit -- list of events that state
             // machine will respond to.
             | rv::transform(expand_commit_task)
             // Flatten the list of commit processing actions
             | rv::join) {


        // Apply actions to the commit iteration state. It will insert new
        // file tracks, keep track of the historical context of the repo
        // changes and so on.
        rs::for_each(actions, [&](auto const& edit) {
            std::visit(
                [&](auto const& act) { iter_state.apply(commit_id, act); },
                edit);
        });
    }
}

CommitId process_commit(git_oid commit_oid, walker_state* state) {
    SPtr<git_commit> commit = git::commit_lookup(
                                  state->repo.get(), &commit_oid)
                                  .value();
    auto hash = oid_tostr(*git_commit_id(commit.get()));

    if (state->config->try_incremental) {
        for (auto& [id, commit] :
             state->content->multi.store<Commit>().pairs()) {
            if (commit->hash == hash) {
                return id;
            }
        }
    }

    {
        auto signature = const_cast<git_signature*>(
            git::commit_author(commit.get()));

        return state->content->add(Commit{
            .author   = state->content->add(Author{
                  .name  = Str{signature->name},
                  .email = Str{signature->email}}),
            .time     = git::commit_time(commit.get()),
            .timezone = git::commit_time_offset(commit.get()),
            .hash     = hash,
            .message  = Str{git_commit_message(commit.get())},
        });
    }
}


CommitGraph build_repo_graph(git_oid& oid, walker_state* state) {
    // All constructed information
    Vec<CommitId> processed{};
    // Walk over every commit in the history
    Vec<FullCommitData> full_commits;
    // TODO get commit count and tick here instead of `full_commit`
    // addition.
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

        // check if we can process it
        //
        // FIXME `commit_author` returns invalid signature here that causes
        // a segfault during conversion to a string. Otherwise
        // `commit_author(commit)->name` is the correct way (according to
        // the documentation least).
        if (state->config->allow_sample(date, "", oid_tostr(oid))) {
            // Store in the list of commits for sampling
            state->sampled_commits.insert({oid, id});
            // LOG(INFO) << fmt("Processing commit {} at {}", oid, date);
        }
    }

    std::reverse(full_commits.begin(), full_commits.end());

    // Push information about all known commits to the full list
    for (const auto& [commit, date, _, __] : full_commits) {
        state->add_full_commit(commit);
    }

    return CommitGraph{state->repo};
}
