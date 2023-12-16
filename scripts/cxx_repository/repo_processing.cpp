/// \file repo_processing.cpp \brief repository processing algorithms
#include "repo_processing.hpp"
#include "git_interface.hpp"
#include "repo_graph.hpp"
#include <git2/patch.h>
import std.stdlib.Map;
#include <immer/flex_vector_transient.hpp>
#include <fstream>

#include <boost/asio/thread_pool.hpp>
import std.stdlib.strutils;
#include <boost/asio/post.hpp>

#include <algorithm>

import std.stdlib.Ranges;

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
    int removed;
};

struct AddAction {
    int        added;
    ir::LineId id;
};

struct FileRenameAction {};
struct NameAction {
    ir::FilePathId path;
};

using Action = std::
    variant<NameAction, FileRenameAction, RemoveAction, AddAction>;


struct CommitTask {
    CommitId       id;
    SPtr<git_tree> prev_tree;
    SPtr<git_tree> this_tree;
    Opt<git_oid>   prev_hash;
    git_oid        this_hash;
};

struct CommitActions {
    UnorderedMap<ir::FileTrackId, Vec<Action>> actions;
};

struct CommitWalkState {
    UnorderedMap<ir::FilePathId, ir::FileTrackId> tracks;

    ir::FileTrackId getTrack(walker_state* state, fs::path const& path) {
        auto path_id = state->content->getFilePath(path);
        if (tracks.contains(path_id)) {
            return tracks.at(path_id);
        } else {
            ir::FileTrackId result = state->content->add(FileTrack{});
            tracks.insert({path_id, result});
            return result;
        }
    }
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

CommitActions get_commit_actions(
    walker_state*    state,
    CR<CommitTask>   task,
    CommitWalkState& commit_walk) {
    CommitActions         result;
    git_diff_options      diffopts = GIT_DIFF_OPTIONS_INIT;
    git_diff_find_options findopts = GIT_DIFF_FIND_OPTIONS_INIT;
    // Assigned values are said to be 'default' in the libgit documentation
    findopts.rename_threshold              = 50;
    findopts.rename_from_rewrite_threshold = 50;
    findopts.copy_threshold                = 50;
    findopts.break_rewrite_threshold       = 60;
    findopts.rename_limit                  = 1000;


    {
        auto [trampoline, lambda] = git_callback_wrapper(
            Func<int(char const*, git_tree_entry const*)>(
                [&](char const* root, git_tree_entry const* entry) -> int {
                    auto path  = fs::path{git_tree_entry_name(entry)};
                    auto track = commit_walk.getTrack(state, path);
                    result.actions[track].push_back(NameAction{
                        .path = state->content->getFilePath(path)});
                    result.actions[track];
                    return 0;
                }));

        git_tree_walk(
            task.this_tree.get(), GIT_TREEWALK_PRE, trampoline, &lambda);
    }

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
        fs::path              path{
            delta->old_file.path == nullptr ? delta->new_file.path
                                                         : delta->old_file.path};

        ir::FileTrackId track = commit_walk.getTrack(state, path);

        auto& actions = result.actions[track];

        actions.push_back(
            NameAction{.path = state->content->getFilePath(path)});
        Vec<Action> delete_actions;
        Vec<Action> add_actions;

        int num_hunks = git_patch_num_hunks(patch.get());
        for (int hunk_idx = 0; hunk_idx < num_hunks; ++hunk_idx) {
            const git_diff_hunk* hunk;
            git_patch_get_hunk(&hunk, NULL, patch.get(), hunk_idx);

            int num_lines = git_patch_num_lines_in_hunk(
                patch.get(), hunk_idx);
            for (int line_idx = 0; line_idx < num_lines; ++line_idx) {
                const git_diff_line* line;
                git_patch_get_line_in_hunk(
                    &line, patch.get(), hunk_idx, line_idx);

                switch (line->origin) {
                    case GIT_DIFF_LINE_ADDITION: {
                        ir::LineId line_id = state->content->add(LineData{
                            .content = state->content->add(String{strip(
                                Str{line->content,
                                    static_cast<int>(line->content_len)},
                                {},
                                {'\n'})}),
                            .commit  = id_commit,
                        });


                        add_actions.push_back(AddAction{
                            .added = line->new_lineno - 1,
                            .id    = line_id,
                        });
                        break;
                    }

                    case GIT_DIFF_LINE_DELETION: {
                        delete_actions.push_back(
                            RemoveAction{.removed = line->old_lineno - 1});
                        break;
                    }
                }
            }
        }

        actions.append(delete_actions);
        actions.append(add_actions);

        auto new_path = state->content->getFilePath(delta->new_file.path);
        if (delta->old_file.path
            && strcmp(delta->old_file.path, delta->new_file.path) != 0) {
            auto old_path = state->content->getFilePath(
                delta->old_file.path);
            // result.push_back(FileRenameAction{});
        }
    }

    return result;
}

void for_each_commit(walker_state* state) {
    CommitGraph g{state->repo};

    LOG(INFO) << "Getting list of files changed per each commit";

    {
        std::ofstream file{"/tmp/graph.dot"};
        file << g.toGraphviz();
    }


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
        return CommitTask{
            .id        = state->get_id(g[main].oid),
            .prev_tree = base ? get_tree(base.value()) : nullptr,
            .this_tree = get_tree(main),
            .prev_hash = base ? Opt<git_oid>{g[base.value()].oid}
                              : Opt<git_oid>{},
            .this_hash = g[main].oid,
        };
    };

    CommitWalkState commit_walk;

    for (auto const& [commit_id, track_id, actions] :
         gen_view(g.commit_pairs())     //
             | make_collect()           //
             | rv::reverse              //
             | rv::take(10)             //
             | rv::transform(make_task) //
             | rv::remove_if([](Opt<CommitTask> const& opt) -> bool {
                   return !opt.has_value();
               })
             | rv::transform([](Opt<CommitTask> const& opt) -> CommitTask {
                   return opt.value();
               })
             | rv::transform([&](CommitTask const& task) {
                   return own_view(
                              get_commit_actions(state, task, commit_walk)
                                  .actions)
                        | rv::transform([id = task.id](const auto& pair) {
                              return std::make_tuple(
                                  id, pair.first, pair.second);
                          });
               })
             | rv::join) {


        auto is_naming = [](Action const& v) -> bool {
            return std::holds_alternative<NameAction>(v);
        };

        CHECK(rs::any_of(actions, is_naming));

        FileTrack& track      = state->content->at(track_id);
        auto       section_id = state->content->add(FileTrackSection{
                  .commit_id = commit_id,
                  .path = std::get<NameAction>(*rs::find_if(actions, is_naming))
                        .path,
        });

        track.sections.push_back(section_id);

        ir::FileTrackSection& section = state->content->at(section_id);
        if (1 < track.sections.size()) {
            section.lines = state->content
                                ->at(track.sections.at(
                                    track.sections.size() - 2))
                                .lines;
        }

        rs::for_each(actions, [&](auto const& edit) {
            std::visit(
                overloaded{
                    [&](AddAction const& add) {
                        CHECK(add.added <= section.lines.size())
                            << "Cannot add line at index " << add.added
                            << " from section version "
                            << section.lines.size();

                        section.added_lines.push_back(add.added);
                        section.lines = section.lines.insert(
                            add.added, add.id);
                    },
                    [&](RemoveAction const& remove) {
                        CHECK(remove.removed <= section.lines.size())
                            << "Cannot remove line index "
                            << remove.removed << " from section version "
                            << section.lines.size() << " path "
                            << state->content
                                   ->at(state->content->at(section.path)
                                            .path)
                                   .text
                            << " commit "
                            << state->content->at(section.commit_id).hash;

                        section.removed_lines.push_back(remove.removed);
                        section.lines = section.lines.erase(
                            remove.removed);
                    },
                    [&](FileRenameAction const& rename) {},
                    [&](NameAction const& rename) {},
                },
                edit);
        });
    }
}

CommitId process_commit(git_oid commit_oid, walker_state* state) {
    SPtr<git_commit> commit = git::commit_lookup(
                                  state->repo.get(), &commit_oid)
                                  .value();
    // commit information should be cleaned up when we exit the scope
    finally close{[commit]() {
        // FIXME freeing the commit causes segmentation fault and I have no
        // idea what is causing this - the issue occurs even in the
        // sequential, non-parallelized mode. The issue was introduces in
        // the commit '4e0bda9'
        //
        // commit_free(commit);
    }};

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


Vec<CommitId> launch_analysis(git_oid& oid, walker_state* state) {
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

    for_each_commit(state);

    return processed;
}
