#include <range/v3/all.hpp>

#include "git_ir.hpp"


#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#include "repo_processing.hpp"
#include "program_state.hpp"
#include <absl/log/log.h>

namespace rv = ranges::views;


#define GIT_SUCCESS 0

struct cli_state {
    Str repo;
    Str branch;
    Str outfile;
};

auto main(int argc, const char** argv) -> int {
    cli_state in{
        .repo   = "/mnt/workspace/repos/haxorg",
        .branch = "test/code-forensics",
    };


    const bool use_fusion = false;

    // Provide implementation callback strategies
    auto config = UPtr<walker_config>(new walker_config{
        // Full process parallelization
        .use_threading = walker_config::async,
        .repo          = in.repo,
        .heads         = fmt(".git/refs/heads/{}", in.branch),
        .db_path       = in.outfile,
        .allow_path    = [](CR<Str> path) -> bool { return true; },
        .allow_sample  = [](CR<PTime> date, CR<Str> author, CR<Str> id)
            -> bool { return true; }});

    git_libgit2_init();
    // Check whether threads can be enabled
    assert(git_libgit2_features() & GIT_FEATURE_THREADS);

    auto heads_path = fs::path{config->repo.toBase()} / config->heads.toBase();
    if (!fs::exists(config->repo.toBase())) {
        LOG(ERROR) << "Input directory '" << config->repo
                   << "' does not exist, aborting analysis";
        return 1;
    } else if (!fs::exists(heads_path)) {
        LOG(ERROR) << "The branch '" << in.branch
                   << "' does not exist in the repository at path "
                   << config->repo << " the full path " << heads_path
                   << " does not exist";
        return 1;
    }

    ir::content_manager content;
    // Create main walker state used in the whole commit analysis state
    auto state = UPtr<walker_state>(new walker_state{
        .config = config.get(),
        .repo = git::repository_open_ext(config->repo.c_str(), 0, nullptr)
                    .value(),
        .content = &content,
    });

    git_oid oid;
    // Initialize state of the commit walker
    open_walker(oid, *state);
    // Store finalized commit IDs from executed tasks
    Vec<ir::CommitId> commits{};
    auto              result = launch_analysis(oid, state.get());
    for (auto& commit : result) {
        commits.push_back(commit);
    }

    LOG(INFO) << "Finished execution, DB written successfully";

    return 0;
}
