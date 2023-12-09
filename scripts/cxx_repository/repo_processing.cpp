/// \file repo_processing.cpp \brief repository processing algorithms
#include "repo_processing.hpp"
#include "git_interface.hpp"
#include "repo_graph.hpp"
#include <git2/patch.h>

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>


#include <algorithm>

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

void for_each_commit(walker_state* state) {
    CommitGraph g{state->repo};

    LOG(INFO) << "Getting list of files changed per each commit";
    git_commit*           prev     = nullptr;
    git_diff_options      diffopts = GIT_DIFF_OPTIONS_INIT;
    git_diff_find_options findopts = GIT_DIFF_FIND_OPTIONS_INIT;
    // TODO expose configuration metrics via the CLI or some other
    // solution. IDEA with boost/descrive it should be possible to
    // automatically map a structure fields to the command-line flags with
    // the default values. Documentation is going to be a little more
    // problematic, but I think adding `name->description` map of the
    // content will be sufficient.
    //
    // Assigned values are said to be 'default' in the libgith
    // documentation
    findopts.rename_threshold              = 50;
    findopts.rename_from_rewrite_threshold = 50;
    findopts.copy_threshold                = 50;
    findopts.break_rewrite_threshold       = 60;
    findopts.rename_limit                  = 1000;


    struct CommitTask {
        CommitId       id;
        SPtr<git_tree> prev_tree;
        SPtr<git_tree> this_tree;
        Opt<git_oid>   prev_hash;
        git_oid        this_hash;
    };

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

    for (auto [main, base] : g.commit_pairs()) {
        if (!g.is_merge(main)) {
            tasks.push_back(CommitTask{
                .id        = state->get_id(g[main].oid),
                .prev_tree = base ? get_tree(base.value()) : nullptr,
                .this_tree = get_tree(main),
                .prev_hash = base ? Opt<git_oid>{g[base.value()].oid}
                                  : Opt<git_oid>{},
                .this_hash = g[main].oid,
            });
        }
    }

    std::mutex tick_mutex;
    auto       task_executor =
        [state, &tick_mutex, &diffopts, &findopts](CR<CommitTask> task) {
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
                const git_diff_delta* delta = git::patch_get_delta(
                    patch.get());

                SLock lock{tick_mutex};

                auto new_path = state->content->getFilePath(
                    delta->new_file.path);
                if (delta->old_file.path
                    && strcmp(delta->old_file.path, delta->new_file.path)
                           != 0) {
                    auto old_path = state->content->getFilePath(
                        delta->old_file.path);
                    // File rename registered
                }
            }
        };
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
