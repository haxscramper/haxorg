
#include "git_ir.hpp"


#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <fstream>

#include "repo_processing.hpp"
#include "program_state.hpp"
#include <absl/log/log.h>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Json.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <absl/log/log_sink_registry.h>
#include <absl/strings/str_split.h>
#include <absl/strings/str_format.h>
#include <absl/log/initialize.h>
#include <absl/log/internal/globals.h>

#include "repo_profile.hpp"

#include <hstd/wrappers/hstd_extra/perfetto_aux_impl_template.hpp>

void CreateTables(SQLite::Database& db) {
    auto        path = __CURRENT_FILE_DIR__ / "code_forensics.sql";
    std::string sql  = readFile(path);
    db.exec(sql);
}


i64 idcast(u64 value) { return static_cast<i64>(value); }

void InsertFilePaths(
    SQLite::Database&                                     db,
    const dod::InternStore<ir::FilePathId, ir::FilePath>& filePaths) {
    SQLite::Statement query(db, "INSERT INTO FilePath VALUES (?, ?)");

    for (const auto& [id, item] : filePaths.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(2, idcast(item->path.getValue()));

        query.exec();
        query.reset();
    }
}


// InsertCommits Function
void InsertCommits(
    SQLite::Database&                           db,
    const dod::Store<ir::CommitId, ir::Commit>& commits) {
    SQLite::Statement query(
        db, "INSERT INTO GitCommit VALUES (?, ?, ?, ?, ?, ?)");

    SQLite::Statement actions(
        db,
        "INSERT INTO GitCommitActions VALUES (?, ?, ?, ?, ?, ?, ?, ?)");


    for (const auto& [id, item] : commits.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(2, item->author.getValue());
        query.bind(3, static_cast<i64>(item->time));
        query.bind(4, item->timezone);
        query.bind(5, item->hash.toBase());
        query.bind(6, item->message.toBase());

        query.exec();
        query.reset();

        for (auto const& act : item->actions) {
            actions.bind(1, idcast(id.getValue()));
            actions.bind(2, (int)act.kind);
            actions.bind(3, idcast(act.track.getValue()));
            if (!act.old_path.isNil()) {
                actions.bind(4, idcast(act.old_path.getValue()));
            }

            if (!act.new_path.isNil()) {
                actions.bind(5, idcast(act.new_path.getValue()));
            }

            if (!act.file.isNil()) {
                actions.bind(6, idcast(act.file.getValue()));
            }

            if (act.kind == ir::Commit::ActionKind::Modify) {
                actions.bind(7, act.added);
                actions.bind(8, act.removed);
            }
            actions.exec();
            actions.reset();
        }
    }
}

void InsertFileTracks(
    SQLite::Database&                              db,
    CR<dod::Store<ir::FileTrackId, ir::FileTrack>> tracks) {
    SQLite::Statement query(db, "INSERT INTO FileTrack VALUES (?)");

    for (const auto& [id, item] : tracks.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.exec();
        query.reset();
    }
}

// InsertFileTrackSections Function
void InsertFileTrackSections(
    SQLite::Database& db,
    const dod::Store<ir::FileTrackSectionId, ir::FileTrackSection>&
        fileTrackSections) {
    SQLite::Statement query(
        db, "INSERT INTO FileTrackSection VALUES (?, ?, ?, ?)");

    SQLite::Statement lineQuery(
        db, "INSERT INTO FileSectionLines VALUES (?, ?, ?)");

    for (const auto& [id, item] : fileTrackSections.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(2, idcast(item->commit_id.getValue()));
        query.bind(3, idcast(item->path.getValue()));
        query.bind(4, idcast(item->track.getValue()));
        // Serialization for lines, added_lines, removed_lines is necessary
        // Assuming these are serialized to a string or blob

        query.exec();
        query.reset();

        int idx = 0;
        for (auto const& line : item->lines) {
            lineQuery.bind(1, idcast(id.getValue()));
            lineQuery.bind(2, idx);
            ++idx;
            lineQuery.bind(3, idcast(line.getValue()));
            lineQuery.exec();
            lineQuery.reset();
        }
    }
}

// InsertStrings Function
void InsertStrings(
    SQLite::Database&                                 db,
    const dod::InternStore<ir::StringId, ir::String>& strings) {
    SQLite::Statement query(db, "INSERT INTO String VALUES (?, ?)");

    for (const auto& [id, item] : strings.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(2, item->text.toBase());

        query.exec();
        query.reset();
    }
}

// InsertAuthors Function
void InsertAuthors(
    SQLite::Database&                                 db,
    const dod::InternStore<ir::AuthorId, ir::Author>& authors) {
    SQLite::Statement query(db, "INSERT INTO Author VALUES (?, ?, ?)");

    for (const auto& [id, item] : authors.pairs()) {
        query.bind(1, id.getValue());
        query.bind(2, item->name.toBase());
        query.bind(3, item->email.toBase());

        query.exec();
        query.reset();
    }
}

// InsertLineData Function
void InsertLineData(
    SQLite::Database&                                 db,
    const dod::InternStore<ir::LineId, ir::LineData>& lineData) {
    SQLite::Statement query(db, "INSERT INTO LineData VALUES (?, ?, ?)");

    for (const auto& [id, item] : lineData.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(2, idcast(item->content.getValue()));
        query.bind(3, idcast(item->commit.getValue()));

        query.exec();
        query.reset();
    }
}


#define GIT_SUCCESS 0


class LinePrinterLogSink : public absl::LogSink {
  public:
    LinePrinterLogSink(std::string const& path) : file(path) {}
    void Send(const absl::LogEntry& entry) override {
        for (absl::string_view line : absl::StrSplit(
                 entry.text_message_with_prefix(), absl::ByChar('\n'))) {
            // Overprint severe entries for emphasis:
            for (int i = static_cast<int>(absl::LogSeverity::kInfo);
                 i <= static_cast<int>(entry.log_severity());
                 i++) {
                file << line << std::endl;
            }
        }
    }

  private:
    std::ofstream file;
};


int main(int argc, char** argv) {
    auto config = UPtr<walker_config>(new walker_config{});

    config->cli = JsonSerde<cli_config>::from_json(json::parse(argv[1]));

    SPtr<LinePrinterLogSink> Sink;
    if (config->cli.out.log_file) {
        LOG(INFO)
            << "Log file configuration was provided, writing to file";
        Sink = std::make_shared<LinePrinterLogSink>(
            *config->cli.out.log_file);
        absl::AddLogSink(Sink.get());
        absl::log_internal::SetTimeZone(absl::LocalTimeZone());
        absl::log_internal::SetInitialized();
    } else {
        LOG(INFO)
            << "No log file configured, writing to regular logging output";
    }
#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession> perfetto_session;
    if (config->cli.out.perfetto) {
        perfetto_session = StartProcessTracing("code_forensics");
    }
#endif


    const bool use_fusion = false;


    git_libgit2_init();
    // Check whether threads can be enabled
    assert(git_libgit2_features() & GIT_FEATURE_THREADS);
    std::string heads = fmt(".git/refs/heads/{}", config->cli.repo.branch);

    auto heads_path = config->repo_path() / heads;
    if (!fs::is_directory(config->repo_path())) {
        LOG(ERROR) << "Input directory '" << config->cli.repo.path
                   << "' does not exist, aborting analysis";
        return 1;
    } else if (!fs::exists(heads_path)) {
        LOG(ERROR) << "The branch '" << config->cli.repo.branch
                   << "' does not exist in the repository at path "
                   << config->cli.repo.path << " the full path "
                   << heads_path << " does not exist";
        return 1;
    }

    ir::content_manager content;
    // Create main walker state used in the whole commit analysis state
    auto state = UPtr<walker_state>(new walker_state{
        .config = config.get(),
        .repo   = git::repository_open_ext(
                    config->cli.repo.path.c_str(), 0, nullptr)
                    .value(),
        .content = &content,
    });

    if (config->cli.config.verbose_consistency_checks) {
        LOG(INFO) << std::format(
            "Verbose consistency check was set to {}",
            config->cli.config.verbose_consistency_checks);
    }

    git_oid oid;
    // Initialize state of the commit walker
    open_walker(oid, *state);
    // Store finalized commit IDs from executed tasks
    Vec<ir::CommitId> commits{};
    CommitGraph       result = build_repo_graph(oid, state.get());
    if (config->cli.out.graphviz) {
        std::string graph_repr = result.toGraphviz();
        writeFile(fs::path(*config->cli.out.graphviz), graph_repr);
    }

    for_each_commit(result, state.get());

    LOG(INFO) << "Finished execution, DB written successfully";

    if (config->cli.out.text_dump) {
        LOG(INFO) << "Text dump option specified, writing debug";
        std::ofstream file{*config->cli.out.text_dump};
        for (auto const& [id, value] :
             state->content->multi.store<ir::FileTrack>().pairs()) {
            file << "File\n";
            for (ir::FileTrackSectionId section_id : value->sections) {
                auto& section = state->content->at(section_id);
                file << fmt(
                    "  Section [{}] = {} at {} +{} -{}\n",
                    section_id,
                    escape_literal(
                        state->content
                            ->at(state->content->at(section.path).path)
                            .text),
                    state->content->at(section.commit_id)
                        .hash.substr(0, 8),
                    section.added_lines,
                    section.removed_lines);

                for (auto const& [idx, line_id] :
                     enumerate(section.lines)) {
                    file << fmt(
                        "   [{}] = ({}) {} {}\n",
                        idx,
                        line_id,
                        rs::contains(section.added_lines, idx) ? "+" : " ",
                        escape_literal(
                            state->content
                                ->at(state->content->at(line_id).content)
                                .text));
                }
            }
        }
    }


    fs::path db_file{config->cli.out.db_path};
    if (fs::exists(db_file)) { fs::remove(db_file); }

    SQLite::Database db(
        db_file.native(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    CreateTables(db);
    LOG(INFO) << "Inserting data content, specified db path "
              << config->cli.out.db_path;
    db.exec("BEGIN");
    auto& m = state->content->multi;
    InsertFileTrackSections(db, m.store<ir::FileTrackSection>());
    InsertFileTracks(db, m.store<ir::FileTrack>());
    InsertStrings(db, m.store<ir::String>());
    InsertFilePaths(db, m.store<ir::FilePath>());
    InsertAuthors(db, m.store<ir::Author>());
    InsertCommits(db, m.store<ir::Commit>());
    InsertLineData(db, m.store<ir::LineData>());
    db.exec("COMMIT");

    LOG(INFO) << "Completed DB write";

#ifdef ORG_USE_PERFETTO
    if (config->cli.out.perfetto) {
        fs::path out_path{*config->cli.out.perfetto};
        LOG(INFO) << std::format("Perfetto output {}", out_path);
        StopTracing(std::move(perfetto_session), out_path);
    }
#endif

    return 0;
}
