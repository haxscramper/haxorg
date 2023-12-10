/// \file repo_processing.cpp \brief repository processing algorithms
#include "repo_processing.hpp"
#include "git_interface.hpp"
#include "repo_graph.hpp"
#include <git2/patch.h>
#include <hstd/stdlib/Map.hpp>
#include <immer/flex_vector_transient.hpp>

#include <boost/asio/thread_pool.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <boost/asio/post.hpp>


#include <range/v3/all.hpp>
#include <algorithm>


using ranges::operator|;
namespace rv = ranges::views;
namespace rs = ranges;
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

template <class T>
struct generator_view : rs::view_facade<generator_view<T>> {
  private:
    friend rs::range_access;
    struct Data {
        generator<T>           gen_;
        generator<T>::iterator iter;
        explicit Data(generator<T>&& gen)
            : gen_(std::move(gen)), iter(gen_.begin()) {
            ++iter;
        }
    };

    SPtr<Data> data;

    struct cursor {
      private:
        friend rs::range_access;
        using single_pass    = std::true_type;
        generator_view* rng_ = nullptr;

      public:
        cursor() = default;
        explicit cursor(generator_view* rng) : rng_(rng) {}

        void next() { rng_->next(); }
        T&   read() const noexcept { return rng_->cached(); }
        bool equal(rs::default_sentinel_t) const {
            return rng_->data->iter == rng_->data->gen_.end();
        }
    };

    void next() { ++data->iter; }

    cursor begin_cursor() { return cursor{this}; }

  public:
    generator_view() = default;
    explicit generator_view(generator<T>&& gen)
        : data(std::make_shared<Data>(std::move(gen))) {
        ++data->iter;
    }

    T& cached() noexcept { return *data->iter; }
};

template <typename T>
generator_view<T> gen_view(generator<T>&& gen) {
    return generator_view<T>(std::move(gen));
}

template <class T>
struct owning_range : rs::view_facade<owning_range<T>> {
    using iterator = std::remove_cvref_t<
        decltype(std::declval<T>().begin())>;
    using value_type = iterator::value_type;

  private:
    friend rs::range_access;
    struct Data {
        T        gen_;
        iterator iter;
        explicit Data(T&& gen)
            : gen_(std::move(gen)), iter(gen_.begin()) {}
    };

    SPtr<Data> data;

    struct cursor {
      private:
        friend rs::range_access;
        using single_pass  = std::true_type;
        owning_range* rng_ = nullptr;

      public:
        cursor() = default;
        explicit cursor(owning_range* rng) : rng_(rng) {}

        void        next() { rng_->next(); }
        value_type& read() const noexcept { return rng_->cached(); }
        bool        equal(rs::default_sentinel_t) const {
            return rng_->data->iter == rng_->data->gen_.end();
        }
    };

    void next() { ++data->iter; }

    cursor begin_cursor() { return cursor{this}; }

  public:
    owning_range() = default;
    explicit owning_range(T&& gen)
        : data(std::make_shared<Data>(std::move(gen))) {
        ++data->iter;
    }

    value_type& cached() noexcept { return *data->iter; }
};

template <typename T>
owning_range<T> own_view(T&& gen) {
    return owning_range<T>(std::move(gen));
}


template <class Rng>
struct transform_view
    : public rs::
          view_interface<transform_view<Rng>, rs::cardinality::finite> {

    using Collected      = std::vector<rs::range_value_t<Rng>>;
    using iterator       = typename Collected::iterator;
    using const_iterator = typename Collected::const_iterator;
    using value_type     = typename Collected::value_type;

    Collected values;
    iterator  iter;

    constexpr const_iterator begin() const noexcept {
        return values.begin();
    }

    constexpr const_iterator end() const noexcept { return values.end(); }
    constexpr iterator       begin() noexcept { return values.begin(); }
    constexpr iterator       end() noexcept { return values.end(); }
    constexpr bool           empty() const { return values.empty(); }
    constexpr auto           size() const { return values.size(); }
    void                     next() { ++iter; }
    void                     prev() { --iter; }
    constexpr auto&          advance(rs::iter_difference_t<iterator> n) {
        iter += n;
        return *this;
    }

    transform_view() = default;
    transform_view(Rng&& rng) {
        for (auto const& it : rng) {
            values.push_back(it);
        }
        iter = values.begin();
    }
};

template <class Rng>
transform_view<Rng> transform(Rng&& rng) {
    return {std::forward<Rng>(rng)};
}

template <typename Rng>
    requires rs::viewable_range<Rng>
void take_viewable_range(Rng const& r) {}

template <typename Rng>
    requires rs::bidirectional_range<Rng>
void take_bidirectional_range(Rng const& r) {}

auto make_collect() {
    auto tran = transform(rv::iota(1, 4));
    using T   = decltype(tran);
    take_viewable_range(tran);
    take_bidirectional_range(tran);
    rs::views::reverse(tran);

    return rs::make_pipeable([](auto&& rng) {
        auto tran = transform(rng);
        using T   = decltype(tran);
        static_assert(requires() { rs::bidirectional_range<T>; });
        static_assert(requires() { rs::viewable_range<T>; });
        return tran;
    });
}

template <typename T, typename In>
generator<T> indexed_get_iterator(
    In const&               in,
    Func<int(In const&)>    size_get,
    Func<T(In const&, int)> getter) {
    int size = size_get(in);
    for (int i = 0; i < size; ++i) {
        co_yield getter(in, i);
    }
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
    variant<NameAction, RemoveAction, AddAction, FileRenameAction>;


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
                                Str{line->content, line->content_len},
                                {},
                                {'\n'})}),
                            .commit  = id_commit,
                        });


                        actions.push_back(AddAction{
                            .added = line->new_lineno,
                            line_id,
                        });
                        break;
                    }

                    case GIT_DIFF_LINE_DELETION: {
                        actions.push_back(
                            RemoveAction{.removed = line->old_lineno});
                        break;
                    }
                }
            }
        }


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
        if (g.is_merge(main)) {
            return std::nullopt;
        } else {
            return CommitTask{
                .id        = state->get_id(g[main].oid),
                .prev_tree = base ? get_tree(base.value()) : nullptr,
                .this_tree = get_tree(main),
                .prev_hash = base ? Opt<git_oid>{g[base.value()].oid}
                                  : Opt<git_oid>{},
                .this_hash = g[main].oid,
            };
        }
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
                        section.added_lines.push_back(add.added);
                        section.lines = section.lines.insert(
                            add.added, add.id);
                    },
                    [&](RemoveAction const& remove) {
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
