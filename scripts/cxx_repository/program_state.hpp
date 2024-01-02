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
    DECL_FIELDS(
        cli_repo_config,
        (),
        ((Vec<std::string>), debug_commits, {}),
        ((std::string), path, ""),
        ((std::string), branch, ""));
};

struct cli_out_config {
    DECL_FIELDS(
        cli_out_config,
        (),
        ((std::string), db_path, ""),
        ((Opt<std::string>), log_file, std::nullopt),
        ((Opt<std::string>), text_dump, std::nullopt),
        ((Opt<std::string>), graphviz, std::nullopt),
        ((Opt<std::string>), perfetto, std::nullopt));
};

struct cli_config {
    DECL_FIELDS(
        cli_config,
        (),
        ((cli_repo_config), repo, cli_repo_config{}),
        ((bool), verbose_consistency_checks, false),
        ((cli_out_config), out, cli_out_config{}));
};


/// \brief runtime configuration state object
struct walker_config {
    cli_config cli;

    fs::path    repo_path() const { return fs::path{cli.repo.path}; }
    std::string heads_path() const {
        return fmt(".git/refs/heads/{}", cli.repo.branch);
    }

    /// Allow processing of a specific path in the repository
    Func<bool(CR<Str>)> allow_path;
    /// Check whether commits at the specified date should be analysed
    Func<bool(CR<PTime>, CR<Str>, CR<Str>)> allow_sample;
};

/// \brief stdlib time point alias
using TimePoint = stime::time_point<stime::system_clock>;


/// Mutable state passed around walker configurations
struct walker_state {
    CP<walker_config> config;

    SPtr<git_revwalk> walker;
    /// Current git repository
    SPtr<git_repository> repo;

    /// Ordered list of commits that were considered for the processing run
    Vec<git_oid>                              full_commits;
    std::unordered_map<git_oid, ir::CommitId> commit_ids;
    /// Mapping from the commit id to it's position in the whole list of
    /// considered commits
    std::unordered_map<git_oid, int> rev_index;

    /// Add preiod mapping of the commit to the walker. All information
    /// about line's *origin period* in further analysis will be based on
    /// the data provided to to this functino.
    void add_full_commit(CR<git_oid> oid ///< git ID of the commit
    ) {
        rev_index.insert({oid, full_commits.size()});
        full_commits.push_back(oid);
    }

    void add_id_mapping(CR<git_oid> oid, ir::CommitId id) {
        commit_ids.insert({oid, id});
    }

    bool do_checks() const {
        return config->cli.verbose_consistency_checks;
    }

    ir::CommitId get_id(CR<git_oid> oid) { return commit_ids.at(oid); }

    ir::content_manager* content;

    template <dod::IsIdType Id>
    auto at(Id id) -> typename dod::value_type_t<Id>& {
        return this->content->at(id);
    }

    Str const& str(ir::StringId id) { return this->at(id).text; }
    Str const& str(ir::FilePathId id) {
        return this->str(content->at(id).path);
    }
};

#endif // PROGRAM_STATE_HPP
