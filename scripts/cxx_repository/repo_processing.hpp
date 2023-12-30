/// \file repo_processing.hpp \brief Headers for the repository processing
/// algorithms

#ifndef REPO_PROCESSING_HPP
#define REPO_PROCESSING_HPP

#include <mutex>
#include <boost/process.hpp>

#include "git_ir.hpp"
#include "program_state.hpp"
#include "repo_graph.hpp"

using SLock = std::scoped_lock<std::mutex>;

auto get_nesting(CR<Str> line) -> int;

/// Append new line to the file and update related counteres (total
/// complexity, line count and so on)
void push_line(
    ir::FileTrackId  id,
    walker_state*    walker,
    CR<ir::LineData> line,
    bool             changed,
    int              period);

struct SubTaskParams {
    git_oid      commit_oid; ///< Original git commit iD
    ir::CommitId out_commit; ///< ID of the commit to append resulting file
                             ///< to
    Str                  root;      ///< Root path for the analyzed entry
    SPtr<git_tree_entry> entry;     ///< Entry to analyze
    int                  index;     ///< Task index in the global sequence
    int                  max_count; ///< Maximum number of task to process
};

/// Implementaiton of the commit processing function. Walks files that were
/// available in the repository at the time and process each file
/// individually, filling data into the content store.
ir::CommitId process_commit(git_oid commit_oid, walker_state* state);

void open_walker(git_oid& oid, walker_state& state);

void for_each_commit(CommitGraph& g, walker_state* state);

CommitGraph build_repo_graph(git_oid& oid, walker_state* state);

#endif // REPO_PROCESSING_HPP
