
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

void CreateTables(SQLite::Database& db) {
    auto path = __CURRENT_FILE_DIR__ / "code_forensics.sql";
    LOG(INFO) << "Loading the DB creation query " << path.native();
    std::string sql = readFile(path);
    db.exec(sql);
    LOG(INFO) << "Created table";
}


i64 idcast(u64 value) { return static_cast<i64>(value); }

void InsertFilePaths(
    SQLite::Database&                                     db,
    const dod::InternStore<ir::FilePathId, ir::FilePath>& filePaths) {
    SQLite::Statement query(db, "INSERT INTO FilePath VALUES (?, ?, ?)");

    for (const auto& [id, item] : filePaths.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(2, idcast(item->path.getValue()));
        query.bind(
            3,
            idcast(
                item->dir.has_value() ? item->dir.value().getValue()
                                      : 0) // TOOD NULL
        );

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

    for (const auto& [id, item] : commits.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(2, item->author.getValue());
        query.bind(3, static_cast<i64>(item->time));
        query.bind(4, item->timezone);
        query.bind(5, item->hash.toBase());
        query.bind(6, item->message.toBase());

        query.exec();
        query.reset();
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

// InsertDirectories Function
void InsertDirectories(
    SQLite::Database&                                       db,
    const dod::InternStore<ir::DirectoryId, ir::Directory>& directories) {
    SQLite::Statement query(db, "INSERT INTO Directory VALUES (?, ?, ?)");

    for (const auto& [id, item] : directories.pairs()) {
        query.bind(1, idcast(id.getValue()));
        query.bind(
            2,
            idcast(
                item->parent.has_value() ? item->parent.value().getValue()
                                         : 0)
            // TODO NULL
        );
        query.bind(3, item->name.toBase());

        query.exec();
        query.reset();
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

struct cli_state {
    Str repo;
    Str branch;
    Str outfile;
};

auto main(int argc, const char** argv) -> int {
    LOG(INFO) << "Input JSON cofig value is " << argv[1];
    json in_config = json::parse(argv[1]);
    LOG(INFO) << "Parsed input JSON to " << in_config.dump();
    cli_state in{
        .repo   = in_config["repo"]["path"],
        .branch = in_config["repo"]["branch"],
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

    auto heads_path = fs::path{config->repo.toBase()}
                    / config->heads.toBase();
    if (!fs::is_directory(config->repo.toBase())) {
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

    std::ofstream file{in_config["out"]["text_dump"].get<std::string>()};
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
                state->content->at(section.commit_id).hash.substr(0, 8),
                section.added_lines,
                section.removed_lines);

            for (auto const& [idx, line_id] : enumerate(section.lines)) {
                file << fmt(
                    "   [{}] = ({}) {} {}\n",
                    idx,
                    line_id,
                    (rs::contains(section.added_lines, idx) ? "+" : " "),
                    escape_literal(
                        state->content
                            ->at(state->content->at(line_id).content)
                            .text));
            }
        }
    }

    fs::path db_file = "/tmp/result.sqlite";
    if (fs::exists(db_file)) {
        fs::remove(db_file);
    }

    SQLite::Database db(
        db_file.native(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    CreateTables(db);
    LOG(INFO) << "Inserting data content";
    db.exec("BEGIN");
    auto& m = state->content->multi;
    InsertFileTrackSections(db, m.store<ir::FileTrackSection>());
    InsertFileTracks(db, m.store<ir::FileTrack>());
    InsertStrings(db, m.store<ir::String>());
    InsertFilePaths(db, m.store<ir::FilePath>());
    InsertAuthors(db, m.store<ir::Author>());
    InsertCommits(db, m.store<ir::Commit>());
    InsertDirectories(db, m.store<ir::Directory>());
    db.exec("COMMIT");

    LOG(INFO) << "Completed DB write";

    return 0;
}
