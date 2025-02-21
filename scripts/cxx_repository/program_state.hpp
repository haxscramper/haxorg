/// \file program_state.hpp \brief Main code analysis state and
/// configuration classes

#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

#include <chrono>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <hstd/system/Formatter.hpp>

#include "git_ir.hpp"
#include <hstd/system/reflection.hpp>

using Date         = boost::gregorian::date;
using PTime        = boost::posix_time::ptime;
using TimeDuration = boost::posix_time::time_duration;
namespace stime    = std::chrono;
namespace bd       = boost::describe;

template <>
struct std::formatter<Date> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(Date const& p, FormatContext& ctx)
        const {
        return fmt_ctx(boost::gregorian::to_iso_extended_string(p), ctx);
    }
};

template <>
struct std::formatter<PTime> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(PTime const& p, FormatContext& ctx)
        const {
        return fmt_ctx(boost::posix_time::to_iso_extended_string(p), ctx);
    }
};

struct cli_repo_config {
    /// Absolute path to input directory
    std::string path = "";
    /// Which branch to analyze
    std::string branch = "";

    DESC_FIELDS(cli_repo_config, (path, branch));
};

struct cli_out_config {
    /// Mandatory option, path for the sqlite database to write to
    std::string db_path = "";
    /// Redirect internal logging into the specified file
    hstd::Opt<std::string> log_file = std::nullopt;
    /// Dump file version representation at the end of the processing
    /// run.
    hstd::Opt<std::string> text_dump = std::nullopt;
    /// Write an analyzed commit graph of the repository into the file
    hstd::Opt<std::string> graphviz = std::nullopt;
    /// Enable perfetto profiling and write trace results into a file.
    hstd::Opt<std::string> perfetto = std::nullopt;

    DESC_FIELDS(
        cli_out_config,
        (db_path, log_file, text_dump, graphviz, perfetto));
};

struct cli_diff_config {
    int rename_threshold              = 50;
    int break_rewrite_threshold       = 60;
    int copy_threshold                = 50;
    int rename_limit                  = 1000;
    int rename_from_rewrite_threshold = 50;

    DESC_FIELDS(
        cli_diff_config,
        (rename_threshold,
         break_rewrite_threshold,
         copy_threshold,
         rename_limit,
         rename_from_rewrite_threshold));
};

struct cli_config_config {
    /// Enable internal data consistency check and verbose logging of
    /// the processes. NOTE: This is a debug option and it slows down
    /// processing by a lot.
    bool verbose_consistency_checks = false;
    /// Trigger verbose consistency file checks for these commits --
    /// can be used for debugging issues in a larger repository where
    /// enabling the full check sequence will make it impossible to
    /// process in a reasonable time.
    hstd::Vec<std::string> debug_commits = {};
    /// If verbose consistency checks are enabled (either explicitly or
    /// via debug commits), narrow down comparison verification to
    /// paths in this list.
    hstd::Vec<std::string> debug_paths = {};
    cli_diff_config        diffopts    = cli_diff_config{};

    DESC_FIELDS(
        cli_config_config,
        (verbose_consistency_checks,
         debug_commits,
         debug_paths,
         diffopts));
};

struct cli_config {
    cli_repo_config   repo   = cli_repo_config{};
    cli_config_config config = cli_config_config{};
    cli_out_config    out    = cli_out_config{};
    DESC_FIELDS(cli_config, (repo, config, out));
};


/// \brief runtime configuration state object
struct walker_config {
    cli_config cli;

    hstd::fs::path repo_path() const {
        return hstd::fs::path{cli.repo.path};
    }
    std::string heads_path() const {
        return hstd::fmt(".git/refs/heads/{}", cli.repo.branch);
    }
};

/// \brief stdlib time point alias
using TimePoint = stime::time_point<stime::system_clock>;


/// Mutable state passed around walker configurations
struct walker_state {
    walker_config const* config;

    hstd::SPtr<git_revwalk> walker;
    /// Current git repository
    hstd::SPtr<git_repository> repo;

    /// Ordered list of commits that were considered for the processing run
    hstd::Vec<git_oid>                        full_commits;
    std::unordered_map<git_oid, ir::CommitId> commit_ids;
    /// Mapping from the commit id to it's position in the whole list of
    /// considered commits
    std::unordered_map<git_oid, int> rev_index;

    /// Add preiod mapping of the commit to the walker. All information
    /// about line's *origin period* in further analysis will be based on
    /// the data provided to to this functino.
    void add_full_commit(git_oid const& oid ///< git ID of the commit
    ) {
        rev_index.insert({oid, full_commits.size()});
        full_commits.push_back(oid);
    }

    void add_id_mapping(git_oid const& oid, ir::CommitId id) {
        LOGIC_ASSERTION_CHECK(!id.isNil(), "commit ID cannot be nil");
        commit_ids.insert({oid, id});
    }

    bool should_debug() const {
        return config->cli.config.verbose_consistency_checks;
    }

    bool should_check_file(hstd::Str const& path) {
        return config->cli.config.debug_paths.empty()
            || config->cli.config.debug_paths.contains(path);
    }

    bool should_debug_file(ir::FilePathId id) {
        return should_check_file(str(id));
    }

    bool should_debug_commit(ir::CommitId id) {
        return config->cli.config.debug_commits.contains(at(id).hash);
    }

    ir::CommitId get_id(git_oid const& oid) { return commit_ids.at(oid); }

    ir::content_manager* content;

    template <hstd::dod::IsIdType Id>
    auto at(Id id) -> typename hstd::dod::value_type_t<Id>& {
        return this->content->at(id);
    }

    hstd::Str const& str(ir::CommitId id) { return this->at(id).hash; }
    hstd::Str const& str(ir::StringId id) { return this->at(id).text; }
    hstd::Str const& str(ir::FilePathId id) {
        return this->str(content->at(id).path);
    }
};

#endif // PROGRAM_STATE_HPP
