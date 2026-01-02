#include <llvm/Support/VirtualFileSystem.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/Regex.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/ProfileData/InstrProfWriter.h>
#include <llvm/ProfileData/Coverage/CoverageMappingReader.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <boost/describe.hpp>
#include <llvm/ADT/Hashing.h>
#include <hstd/stdlib/Formatter.hpp>
#include <absl/hash/hash.h>
#include <hstd/system/aux_utils.hpp>
#include <llvm/ADT/SmallBitVector.h>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <llvm/Demangle/Demangle.h>
#include <fstream>
#include <execution>

#include <hstd/ext/perfetto_aux.hpp>
#include <absl/log/log.h>

#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VariantSerde.hpp>

#include "reflection_demangler.hpp"

#ifdef ORG_USE_PERFETTO

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("llvm").SetDescription("LLVM code execution time"),
    perfetto::Category("sql").SetDescription("SQLite data insertion"),
    perfetto::Category("transform").SetDescription("Data transform time"),
    perfetto::Category("main").SetDescription("Top execution steps")
    //
);


#endif

#define NO_COVERAGE                                                       \
    __attribute__((no_sanitize("coverage", "address", "thread")))


#pragma clang diagnostic error "-Wswitch"

#include <hstd/ext/perfetto_aux_impl_template.hpp>

namespace fs = std::filesystem;
using namespace llvm::coverage;
using namespace hstd;

namespace hstd {
template <>
struct JsonSerde<std::monostate> {
    static json to_json(std::monostate const& point) {
        return json::object();
    }

    static std::monostate from_json(json const& j) {
        return std::monostate{};
    }
};

} // namespace hstd


namespace llvm::coverage {
BOOST_DESCRIBE_STRUCT(
    CoverageSegment,
    (),
    (Line, Col, Count, HasCount, IsRegionEntry, IsGapRegion));
BOOST_DESCRIBE_STRUCT(ExpansionRecord, (), (FileID));
BOOST_DESCRIBE_STRUCT(
    FunctionRecord,
    (),
    (Name,
     Filenames,
     CountedRegions,
     CountedBranchRegions,
     MCDCRecords,
     ExecutionCount));

BOOST_DESCRIBE_STRUCT(
    CounterMappingRegion,
    (),
    (Count,
     FalseCount,
     MCDCParams,
     FileID,
     ExpandedFileID,
     LineStart,
     ColumnStart,
     LineEnd,
     ColumnEnd,
     Kind));

BOOST_DESCRIBE_STRUCT(
    CountedRegion,
    (CounterMappingRegion),
    (ExecutionCount, FalseExecutionCount, TrueFolded, FalseFolded));

BOOST_DESCRIBE_STRUCT(mcdc::BranchParameters, (), (ID, Conds));
BOOST_DESCRIBE_STRUCT(
    mcdc::DecisionParameters,
    (),
    (BitmapIdx, NumConditions));

BOOST_DESCRIBE_ENUM(
    CounterMappingRegion::RegionKind,
    CodeRegion,
    ExpansionRegion,
    SkippedRegion,
    GapRegion,
    BranchRegion,
    MCDCDecisionRegion,
    MCDCBranchRegion);


} // namespace llvm::coverage


NO_COVERAGE std::string read_file(fs::path const& path) {
    std::ifstream     file{path.native()};
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

NO_COVERAGE void llvm_unreachable_f(std::string const& msg) {
    llvm_unreachable(msg.c_str());
}


namespace {
NO_COVERAGE void CreateTables(SQLite::Database& db) {
    auto path = fs::path{__FILE__}.parent_path() / "profdata_merger.sql";
    std::string sql = read_file(path);
    db.exec(sql);
}
} // namespace

// std::ostream& LOG(std::string const& msg, int line = __builtin_LINE()) {
//     return std::cerr << std::format("[profmerge:{}] {}\n", line, msg);
// }


template <>
struct JsonSerde<Counter> {
    NO_COVERAGE static json to_json(Counter const& cnt) { return json(); }
};

template <>
struct JsonSerde<mcdc::DecisionParameters> {
    NO_COVERAGE static json to_json(mcdc::DecisionParameters const& cnt) {
        return json();
    }
};

template <>
struct JsonSerde<mcdc::BranchParameters> {
    NO_COVERAGE static json to_json(mcdc::BranchParameters const& cnt) {
        return json();
    }
};

template <>
struct JsonSerde<llvm::json::Object> {
    NO_COVERAGE static json to_json(llvm::json::Object const& obj);
};


template <>
struct JsonSerde<llvm::json::Array> {
    NO_COVERAGE static json to_json(llvm::json::Array const& obj);
};

template <>
struct JsonSerde<llvm::json::Value> {
    NO_COVERAGE static json to_json(llvm::json::Value const& value) {
        using K = llvm::json::Value::Kind;
        switch (value.kind()) {
            case K::Null: return json();
            case K::Number: return value.getAsNumber().value();
            case K::String: return value.getAsString().value();
            case K::Boolean: return value.getAsBoolean().value();
            case K::Array:
                return JsonSerde<llvm::json::Array>::to_json(
                    *value.getAsArray());
            case K::Object:
                return JsonSerde<llvm::json::Object>::to_json(
                    *value.getAsObject());
        }
    }
};


NO_COVERAGE json
    JsonSerde<llvm::json::Array>::to_json(const llvm::json::Array& obj) {
    json result = json::array();
    for (auto const& it : obj) {
        result.push_back(JsonSerde<llvm::json::Value>::to_json(it));
    }
    return result;
}


NO_COVERAGE json
    JsonSerde<llvm::json::Object>::to_json(const llvm::json::Object& obj) {
    json result = json::object();
    for (auto const& field : obj) {
        result[field.first.str()] = JsonSerde<llvm::json::Value>::to_json(
            field.second);
    }
    return result;
}


template <>
struct JsonSerde<FunctionRecord> {
    static json to_json(FunctionRecord const& func) {
        json result = JsonSerdeDescribedRecordBase<
            FunctionRecord>::to_json(func);

        result["DemangledName"] = llvm::demangle(func.Name);


        return result;
    }

    // static FunctionRecord from_json(json const& func) {
    //     return JsonSerdeDescribedRecordBase<FunctionRecord>::from_json(
    //         func);
    // }
};

template <>
struct JsonSerde<MCDCRecord> {
    static json to_json(MCDCRecord const& cnt) { return json(); }
};


template <>
struct JsonSerde<CoverageMapping> {
    NO_COVERAGE static json to_json(CoverageMapping const& map) {
        json result = json::object();
        for (auto const& it : map.getCoveredFunctions()) {
            result["functions"].push_back(to_json_eval(it));
        }
        return result;
    }
};


NO_COVERAGE static void loadInput(
    std::string const&     Filename,
    std::string const&     ProfiledBinary,
    llvm::InstrProfWriter* Writer) {

    auto FS          = llvm::vfs::getRealFileSystem();
    auto ReaderOrErr = llvm::InstrProfReader::create(Filename, *FS);
    if (llvm::Error E = ReaderOrErr.takeError()) {
        auto [ErrCode, Msg] = llvm::InstrProfError::take(std::move(E));
        if (ErrCode != llvm::instrprof_error::empty_raw_profile) {
            assert(false);
        }
        return;
    }

    auto Reader = std::move(ReaderOrErr.get());
    for (auto& I : *Reader) {
        const llvm::StringRef FuncName = I.Name;
        bool                  Reported = false;
        Writer->addRecord(std::move(I), 1, [&](llvm::Error E) {
            LOG(INFO) << std::format("{}", toString(std::move(E)));
        });
    }

    if (Reader->hasTemporalProfile()) {
        auto& Traces = Reader->getTemporalProfTraces();
        if (!Traces.empty()) {
            Writer->addTemporalProfileTraces(
                Traces, Reader->getTemporalProfTraceStreamSize());
        }
    }

    if (Reader->hasError()) {
        if (llvm::Error E = Reader->getError()) {
            LOG(INFO) << std::format(
                "{} {}", toString(std::move(E)), Filename);
            return;
        }
    }

    std::vector<llvm::object::BuildID> BinaryIds;
    if (llvm::Error E = Reader->readBinaryIds(BinaryIds)) {
        LOG(INFO) << std::format(
            "{} {}", toString(std::move(E)), Filename);
        return;
    }

    Writer->addBinaryIds(BinaryIds);
}

struct CoverageMappingLyt {
    llvm::DenseMap<size_t, llvm::DenseSet<size_t>> RecordProvenance;
    std::vector<FunctionRecord>                    Functions;
    llvm::DenseMap<size_t, llvm::SmallVector<unsigned, 0>>
        FilenameHash2RecordIndices;
    std::vector<std::pair<std::string, uint64_t>> FuncHashMismatches;
    std::optional<bool>                           SingleByteCoverage;
};

static_assert(sizeof(CoverageMappingLyt) == sizeof(CoverageMapping));

CoverageMappingLyt const* toCoverageMappingLyt(
    CoverageMapping const* Mapping) {
    return reinterpret_cast<CoverageMappingLyt const*>(Mapping);
}

NO_COVERAGE llvm::ArrayRef<unsigned> getImpreciseRecordIndicesForFilename(
    CoverageMapping const& Mapping,
    llvm::StringRef        Filename) {
    size_t FilenameHash = hash_value(Filename);
    auto   RecordIt     = toCoverageMappingLyt(&Mapping)
                        ->FilenameHash2RecordIndices.find(FilenameHash);
    if (RecordIt
        == toCoverageMappingLyt(&Mapping)
               ->FilenameHash2RecordIndices.end()) {
        return {};
    }
    return RecordIt->second;
}

NO_COVERAGE static std::optional<unsigned> findMainViewFileID(
    const FunctionRecord& Function) {
    llvm::SmallBitVector IsNotExpandedFile(
        Function.Filenames.size(), true);
    for (const auto& CR : Function.CountedRegions) {
        if (CR.Kind == CounterMappingRegion::ExpansionRegion) {
            IsNotExpandedFile[CR.ExpandedFileID] = false;
        }
    }
    int I = IsNotExpandedFile.find_first();
    if (I == -1) { return std::nullopt; }
    return I;
}

NO_COVERAGE static std::optional<unsigned> findMainViewFileID(
    llvm::StringRef       SourceFile,
    const FunctionRecord& Function) {
    std::optional<unsigned> I = findMainViewFileID(Function);
    if (I && SourceFile == Function.Filenames[*I]) { return I; }
    return std::nullopt;
}

NO_COVERAGE static llvm::SmallBitVector gatherFileIDs(
    llvm::StringRef       SourceFile,
    const FunctionRecord& Function) {
    llvm::SmallBitVector FilenameEquivalence(
        Function.Filenames.size(), false);
    for (unsigned I = 0, E = Function.Filenames.size(); I < E; ++I) {
        if (SourceFile == Function.Filenames[I]) {
            FilenameEquivalence[I] = true;
        }
    }
    return FilenameEquivalence;
}

namespace {
/// \brief Create a text for a `INSERT` statement with a given list of
/// column names and identical number of coverage instantiation
NO_COVERAGE std::string SqlInsert(
    std::string const&              Table,
    std::vector<std::string> const& Columns) {
    std::string result = std::format("INSERT INTO {} (", Table);
    for (auto it : llvm::enumerate(Columns)) {
        if (it.index() != 0) { result += ", "; }
        result += it.value();
    }

    result += ") VALUES (";

    for (auto it : llvm::enumerate(Columns)) {
        if (it.index() != 0) { result += ", "; }
        result += "?";
    }

    result += ")";
    return result;
}
} // namespace

struct queries {
    SQLite::Statement file_region;
    SQLite::Statement context;
    SQLite::Statement func;
    SQLite::Statement file;

    queries(SQLite::Database& db)
        : // ---
        file_region(
            db,
            SqlInsert(
                "CovFileRegion",
                {
                    "Id",                  // 1
                    "Context",             // 2
                    "ExecutionCount",      // 3
                    "FalseExecutionCount", // 4
                    "TrueFolded",          // 5
                    "FalseFolded",         // 6
                    "LineStart",           // 7
                    "ColumnStart",         // 8
                    "LineEnd",             // 9
                    "ColumnEnd",           // 10
                    "RegionKind",          // 11
                    "File",                // 12
                    "Function",            // 13
                    "ExpandedFrom",        // 14
                }))
        ,
        // ---
        context(
            db,
            SqlInsert(
                "CovContext",
                {
                    "Id",      // 1
                    "Name",    // 2
                    "Parent",  // 3
                    "Profile", // 4
                    "Params",  // 5
                    "Binary",  // 6
                }))
        ,
        // ---
        func(
            db,
            SqlInsert(
                "CovFunction",
                {
                    "Id",        // 1
                    "Mangled",   // 2
                    "Demangled", // 3
                    "Parsed",    // 4
                }))
        ,
        // ---
        file(
            db,
            SqlInsert(
                "CovFile",
                {
                    "Id",   // 1
                    "Path", // 2
                })) {}
};

struct CountedRegionHasher {
    size_t operator()(const CounterMappingRegion& region) const {
        return llvm::hash_combine(
            std::hash<unsigned>()(region.FileID),
            std::hash<unsigned>()(region.ExpandedFileID),
            std::hash<unsigned>()(region.LineStart),
            std::hash<unsigned>()(region.ColumnStart),
            std::hash<unsigned>()(region.LineEnd),
            std::hash<unsigned>()(region.ColumnEnd),
            std::hash<int>()(static_cast<int>(region.Kind)));
    }
};


struct CountedRegionComparator {
    size_t operator()(
        const CounterMappingRegion& lhs,
        const CounterMappingRegion& rhs) const {
        return lhs.FileID == rhs.FileID
            && lhs.ExpandedFileID == rhs.ExpandedFileID
            && lhs.LineStart == rhs.LineStart
            && lhs.ColumnStart == rhs.ColumnStart
            && lhs.LineEnd == rhs.LineEnd && lhs.ColumnEnd == rhs.ColumnEnd
            && lhs.Kind == rhs.Kind;
    }
};


struct FileSpan {
    unsigned int LineStart{};
    unsigned int LineEnd{};
    unsigned int ColStart{};
    unsigned int ColEnd{};
};

struct FileSpanHasher {
    size_t operator()(const FileSpan& region) const {
        return llvm::hash_combine(
            region.LineStart,
            region.LineEnd,
            region.ColStart,
            region.ColEnd);
    }
};


struct FileSpanComparator {
    size_t operator()(const FileSpan& lhs, const FileSpan& rhs) const {
        return lhs.LineStart == rhs.LineStart //
            && lhs.ColStart == rhs.ColStart   //
            && lhs.LineEnd == rhs.LineEnd     //
            && lhs.ColEnd == rhs.ColEnd;
    }
};


struct db_build_ctx {
    /// \brief DB ID generator for individual coverage contexts from the
    /// coverage configuration file.
    int                                  context_id{};
    int                                  instantiation_id{};
    std::unordered_map<std::string, int> function_ids{};
    /// \brief Absolute file path to the file ID.
    ///
    /// LLVM coverage contains `FileID` and `ExpandedFileID` fields in the
    /// counted regions. These fields are local to individual function
    /// records and are used for both real files and for macro expansion
    /// IDs pointing to the same file. A function with macro expansion
    /// might have multiple duplicate file names with different IDs.
    ///
    /// DB build uses absolute path to the file as a unique identifier for
    /// the file and is not directly mapped to the LLVM coverage file ID.
    std::unordered_map<std::string, int> file_ids{};
    /// \brief DB ID generator for coverage file regions
    int region_counter{};

    /// \brief Cache for the JSON value demangling.
    std::unordered_map<std::string, std::string> demangled_json_dumps{};

    /// \brief List of regexps to filter out from the input file coverage.
    /// Has secondary check order compared to blacklist. For a file to pass
    /// it must match the whitelist and then not fail on the blacklist.
    std::vector<llvm::Regex> file_blacklist;
    /// \brief List of regexps to allow for for the coverage extractor. Has
    /// first check order compared to blacklist.
    std::vector<llvm::Regex> file_whitelist;

    /// \brief Get JSON dump of the demangled function record name.
    NO_COVERAGE std::string getDemangledJson(FunctionRecord const& f) {
        // TODO: Get fully demangled JSON
        if (!demangled_json_dumps.contains(f.Name)) {
            BinarySymbolVisitContext ctx;
            demangled_json_dumps.insert_or_assign(
                f.Name,
                llvm::formatv("{0}", demangle_to_json(f.Name, ctx, 0, 200))
                    .str());
        }

        return demangled_json_dumps.at(f.Name);
    }


    /// \brief Check the file against provided white/black list of
    /// mappings.
    NO_COVERAGE bool file_matches(
        std::string const& path,
        std::string&       debug) const {
        bool result = false;
        if (file_whitelist.empty()) {
            throw std::logic_error(
                "file match whitelist cannot be empty -- specify at least "
                "`.*` as a pattern");
        }

        for (auto const& r : file_whitelist) {
            if (r.match(path)) {
                result = true;
                break;
            }
        }

        if (!result) {
            debug = "no matching whitelist";
            return false;
        }

        for (auto const& r : llvm::enumerate(file_blacklist)) {
            if (r.value().match(path)) {
                debug = std::format("blacklisted by #{}", r.index());
                return false;
            }
        }

        return result;
    }

    NO_COVERAGE int get_file_id(std::string const& path, queries& q) {
        if (!file_ids.contains(path)) {
            int id         = file_ids.size();
            file_ids[path] = id;

            q.file.bind(1, id);
            q.file.bind(2, path);
            q.file.exec();
            q.file.reset();
        }
        return file_ids.at(path);
    }
};

/// \brief Get an ID for the function from a database, insert a new entry
/// in DB if needed.
///
/// Functions are mapped based on their mangled names and are shared across
/// all execution contexts and all executed files.
NO_COVERAGE int get_function_id(
    FunctionRecord const& f,
    queries&              q,
    db_build_ctx&         ctx) {
    std::string readeable = llvm::demangle(f.Name);


    int function_id = -1;

    if (ctx.function_ids.contains(f.Name)) {
        function_id = ctx.function_ids.at(f.Name);
    } else {
        function_id              = ctx.function_ids.size();
        ctx.function_ids[f.Name] = function_id;

        q.func.bind(1, function_id);
        q.func.bind(2, f.Name); // mangled
        char const* demangled = llvm::itaniumDemangle(f.Name);
        if (demangled == nullptr) {
            q.func.bind(3, f.Name);
        } else {
            q.func.bind(3, demangled);
        }
        q.func.bind(4, ctx.getDemangledJson(f));
        q.func.exec();
        q.func.reset();
    }

    return function_id;
}


template <typename T, typename FormatContext>
NO_COVERAGE auto fmt_ctx_field(
    std::string const& field_name,
    T const&           field_value,
    FormatContext&     ctx) {
    fmt_ctx(" ", ctx);
    fmt_ctx(field_name, ctx);
    fmt_ctx(" = ", ctx);
    return fmt_ctx(field_value, ctx);
}

template <>
struct std::formatter<CountedRegion> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const CountedRegion& p, FormatContext& ctx) const {
        fmt_ctx("{", ctx);
        fmt_ctx_field("ExecutionCount", p.ExecutionCount, ctx);
        fmt_ctx_field("FalseExecutionCount", p.FalseExecutionCount, ctx);
        fmt_ctx_field(
            "Loc",
            fmt("[{}:{}..{}:{}]",
                p.LineStart,
                p.ColumnStart,
                p.LineEnd,
                p.ColumnEnd),
            ctx);
        fmt_ctx_field("FileId", p.FileID, ctx);
        fmt_ctx_field("ExpandedFileID", p.ExpandedFileID, ctx);
        fmt_ctx_field("Kind", p.Kind, ctx);
        return fmt_ctx("}", ctx);
    }
};

template <>
struct std::formatter<CoverageSegment> : std::formatter<std::string> {
    template <typename FormatContext>
    NO_COVERAGE auto format(const CoverageSegment& p, FormatContext& ctx)
        const {
        fmt_ctx("{", ctx);
        fmt_ctx_field("Line", p.Line, ctx);
        fmt_ctx_field("Col", p.Col, ctx);
        fmt_ctx_field("Count", p.Count, ctx);
        fmt_ctx_field("HasCount", p.HasCount, ctx);
        fmt_ctx_field("IsRegionEntry", p.IsRegionEntry, ctx);
        fmt_ctx_field("IsGapRegion", p.IsGapRegion, ctx);
        return fmt_ctx(" }", ctx);
    }
};


NO_COVERAGE void add_file_regions(
    CoverageMapping const& Mapping,
    std::string const&     Filename,
    queries&               q,
    db_build_ctx&          ctx) {

    // Look up the function records in the given file. Due to hash
    // collisions on the filename, we may get back some records that are
    // not in the file.
    llvm::ArrayRef<unsigned>
        RecordIndices = getImpreciseRecordIndicesForFilename(
            Mapping, Filename);
    auto Access = toCoverageMappingLyt(&Mapping);
    for (unsigned RecordIndex : RecordIndices) {
        const FunctionRecord& Function = Access->Functions[RecordIndex];
        auto MainFileID = findMainViewFileID(Filename, Function);
        auto FileIDs    = gatherFileIDs(Filename, Function);
        // `ExpandedFileID` in the expansion regions points to the file ID
        // of the macro body region. This map retains information on which
        // segment index introduced a new expanded file ID.
        UnorderedMap<int, int> expanded_from;

        bool dbg = false && Function.Name.contains("parseSubtree")
                && !(Function.Name.contains("parseSubtreeLogbook")
                     || Function.Name.contains("parseSubtreeProperties")
                     || Function.Name.contains("parseSubtreeTodo")
                     || Function.Name.contains("parseSubtreeTitle")
                     || Function.Name.contains("parseSubtreeUrgency")
                     || Function.Name.contains("parseSubtreeDrawer")
                     || Function.Name.contains("parseSubtreeTags")
                     || Function.Name.contains("parseSubtreeTimes")
                     || Function.Name.contains("parseSubtreeCompletion"));

        auto reg = [&](int region_index) -> CountedRegion const& {
            return Function.CountedRegions.at(region_index);
        };

        for (const auto& it : llvm::enumerate(Function.CountedRegions)) {
            if (it.value().Kind
                == CounterMappingRegion::RegionKind::ExpansionRegion) {
                expanded_from[it.value().ExpandedFileID] = it.index();
            }
        }

        auto getOriginalIndex = [&](int region) -> Opt<int> {
            if (expanded_from.contains(reg(region).FileID)) {
                // while (expanded_from.contains(reg(region).FileID)) {
                region = expanded_from.at(reg(region).FileID);
                // }
                return region;
            } else {
                return std::nullopt;
            }
        };

        // Map region indices for the function to the generated IDs. Each
        // function has its own, separate set of counted regions, so this
        // mapping is local for each function processing.
        UnorderedMap<int, int> file_region_ids;

        std::function<int(int)> addRegion;
        addRegion = [&](int region_index) -> int {
            CountedRegion const& r = reg(region_index);

            ++ctx.region_counter;
            int region_id = ctx.region_counter;

            Opt<int> expanded_from_id = std::nullopt;
            // <<expanded_from>>
            if (expanded_from.contains(r.FileID)) {
                auto original_index = getOriginalIndex(region_index);
                if (original_index.has_value()) {
                    auto id = *original_index;
                    // Protection against segments arriving out of order
                    // due to macro expansion magicks. If the region
                    // already mapped, existing ID must be reused.
                    if (file_region_ids.contains(id)) {
                        expanded_from_id = file_region_ids.at(id);
                    } else {
                        if (dbg) {
                            LOG(INFO)
                                << fmt("recursively adding region {} {} "
                                       ".contains({}) -> {}",
                                       id,
                                       file_region_ids,
                                       id,
                                       file_region_ids.contains(id));
                        }

                        expanded_from_id = addRegion(id);
                    }
                }
            }

            // Passing LLVM information directly
            q.file_region.bind(1, region_id);
            q.file_region.bind(2, ctx.context_id);
            q.file_region.bind(3, static_cast<int>(r.ExecutionCount));
            q.file_region.bind(4, static_cast<int>(r.FalseExecutionCount));
            q.file_region.bind(5, r.TrueFolded);
            q.file_region.bind(6, r.FalseFolded);
            q.file_region.bind(7, static_cast<int>(r.LineStart));
            q.file_region.bind(8, static_cast<int>(r.ColumnStart));
            q.file_region.bind(9, static_cast<int>(r.LineEnd));
            q.file_region.bind(10, static_cast<int>(r.ColumnEnd));
            q.file_region.bind(11, r.Kind);
            q.file_region.bind(
                12, ctx.get_file_id(Function.Filenames.at(r.FileID), q));
            // Addition to the LLVM info -- the function which contains the
            // segment
            q.file_region.bind(13, get_function_id(Function, q, ctx));
            // And optionally a location that was expanded to this segment
            // (for macro body).
            if (expanded_from_id) {
                q.file_region.bind(14, *expanded_from_id);
            }

            q.file_region.exec();
            q.file_region.reset();

            if (dbg) {
                LOG(INFO) << fmt(
                    "add region [{} -> {}] {} ",
                    region_index,
                    region_id,
                    r);
            }

            file_region_ids[region_index] = region_id;
            return region_id;
        };


        for (const auto& it : llvm::enumerate(Function.CountedRegions)) {
            if (FileIDs.test(it.value().FileID)) {
                addRegion(it.index());
            } else {
                if (dbg) {
                    LOG(INFO) << fmt(
                        "skip region [{}] {}", it.index(), it.value());
                }
            }
        }
    }
}

template <typename T>
NO_COVERAGE std::string format_range(T begin, T end) {
    bool        isFirst = true;
    std::string result  = "[";
    while (begin != end) {
        if (isFirst) {
            isFirst = false;
        } else {
            result += ", ";
        }
        result += std::format("{}", *begin);
        ++begin;
    }

    result += "]";
    return result;
}

NO_COVERAGE void add_file(
    CoverageMapping const* mapping,
    llvm::StringRef        file,
    queries&               q,
    db_build_ctx&          ctx) {
    __perf_trace("sql", "File coverage data");
    int file_id = ctx.get_file_id(file.str(), q);

    add_file_regions(*mapping, file.str(), q, ctx);
}

struct ProfdataCookie {
    std::string                test_binary;
    std::string                test_name;
    std::optional<std::string> test_class = std::nullopt;
    std::string                test_profile;
    json                       test_params;

    DESC_FIELDS(
        ProfdataCookie,
        (test_binary, test_name, test_class, test_profile, test_params));
};

static_assert(DescribedRecord<ProfdataCookie>, "dbg");

NO_COVERAGE void add_context(
    ProfdataCookie const& run,
    queries&              q,
    db_build_ctx&         ctx) {
    ++ctx.context_id;

    q.context.bind(1, ctx.context_id);
    q.context.bind(2, run.test_name);
    if (run.test_class) {
        q.context.bind(3, run.test_class.value());
    } else {
        q.context.bind(3, nullptr);
    }
    q.context.bind(4, run.test_profile);
    q.context.bind(5, run.test_params.dump());
    q.context.bind(6, run.test_binary);

    q.context.exec();
    q.context.reset();
}

NO_COVERAGE llvm::MD5::MD5Result getMD5Digest(
    const std::string& str1,
    const std::string& str2) {
    llvm::MD5 hash;
    hash.update(
        llvm::ArrayRef<uint8_t>(
            reinterpret_cast<const uint8_t*>(str1.data()), str1.size()));
    hash.update(
        llvm::ArrayRef<uint8_t>(
            reinterpret_cast<const uint8_t*>(str2.data()), str2.size()));
    llvm::MD5::MD5Result result;
    hash.final(result);
    return result;
}

NO_COVERAGE std::shared_ptr<CoverageMapping> get_coverage_mapping(
    std::string const& coverage_path,
    std::string const& binary_path) {
    __perf_trace(
        "llvm",
        "Profraw to coverage mapping",
        "coverage_path",
        coverage_path,
        "binary_path",
        binary_path);

    llvm::InstrProfWriter Writer;
    {
        __perf_trace("llvm", "Load raw profile coverage");
        loadInput(coverage_path, binary_path, &Writer);
        LOG(INFO) << std::format(
            "Loaded {} binary {}", coverage_path, binary_path);
    }

    std::string tmp_path = std::format(
        "/tmp/{}.profdata",
        getMD5Digest(coverage_path, binary_path).digest().str().str());

    std::vector<llvm::StringRef> ObjectFilenames;
    ObjectFilenames.push_back(binary_path);
    {
        __perf_trace("llvm", "Write converted profile data");
        std::error_code      EC;
        llvm::raw_fd_ostream Output(tmp_path, EC, llvm::sys::fs::OF_None);

        if (EC) {
            throw std::domain_error(
                std::format(
                    "Error while creating output stream {}",
                    EC.message()));
        }

        if (llvm::Error E = Writer.write(Output)) {
            throw std::domain_error(
                std::format("Failed write: {}", toString(std::move(E))));
        }
    }

    LOGIC_ASSERTION_CHECK_FMT(fs::exists(tmp_path), "{}", tmp_path);

    {
        __perf_trace("llvm", "Load coverage profile data");
        auto FS = llvm::vfs::getRealFileSystem();
        llvm::Expected<std::shared_ptr<CoverageMapping>>
            mapping_or_err = CoverageMapping::load(
                ObjectFilenames, tmp_path, *FS);

        if (llvm::Error E = mapping_or_err.takeError()) {
            throw std::domain_error(
                std::format(
                    "Failed to load profdata {} from {}",
                    toString(std::move(E)),
                    tmp_path));
        }

        fs::remove(tmp_path);

        return std::move(mapping_or_err.get());
    }
}

struct ProfdataCLIConfig {
    DECL_DESCRIBED_ENUM(Mode, RunProfileMerge, BuildProfileMerge);


    Mode                       mode = Mode::RunProfileMerge;
    std::string                coverage;
    std::string                coverage_db;
    std::optional<std::string> perf_trace     = std::nullopt;
    std::vector<std::string>   file_whitelist = {".*"};
    std::vector<std::string>   file_blacklist;
    std::optional<std::string> debug_file            = std::nullopt;
    std::optional<std::string> coverage_mapping_dump = std::nullopt;
    int                        run_group_batch_size  = 8;

    DESC_FIELDS(
        ProfdataCLIConfig,
        (mode,
         coverage,
         coverage_db,
         perf_trace,
         file_whitelist,
         file_blacklist,
         debug_file,
         coverage_mapping_dump));
};

struct ProfdataFullProfile {
    std::vector<ProfdataCookie> runs;
    DESC_FIELDS(ProfdataFullProfile, (runs));
};

struct ProfdataRun {
    int            index;
    ProfdataCookie run;
    DESC_FIELDS(ProfdataRun, (index, run));
};


const char* __asan_default_options() { return "detect_leaks=0"; }

void process_runs(
    Vec<ProfdataRun> const&  runs,
    ProfdataCLIConfig const& config,
    int                      full_run_size,
    std::function<void()>    flush_debug,
    db_build_ctx&            ctx,
    queries&                 q,
    json&                    debug,
    SQLite::Database&        db) {

    UnorderedMap<
        std::pair<std::string, std::string>,
        std::shared_ptr<CoverageMapping>,
        llvm::pair_hash<std::string, std::string>>
        coverage_map;

    {
        __perf_trace("llvm", "Parallel convert of coverage data");
        std::vector<std::pair<std::string, std::string>> paths{};

        for (auto const& run : runs) {
            paths.push_back({run.run.test_profile, run.run.test_binary});
        }

        std::mutex coverage_mutex;

        std::for_each(
            std::execution::par,
            paths.begin(),
            paths.end(),
            [&](const std::pair<std::string, std::string>& p) {
                __perf_trace("llvm", "Get coverage mapping task");
                auto coverage = get_coverage_mapping(p.first, p.second);
                std::scoped_lock lock{coverage_mutex};
                coverage_map.emplace(p, std::move(coverage));
            });
    }


    if (config.coverage_mapping_dump) {
        LOG(INFO) << fmt(
            "Coverage mapping dump to {}",
            config.coverage_mapping_dump.value());
    }

    for (auto const& run : runs) {
        __perf_trace("main", "Insert run data");
        finally{flush_debug};
        LOG(INFO) << fmt(
            "[{}/{}] Insert run data profile={} binary={}",
            run.index,
            full_run_size,
            run.run.test_profile,
            run.run.test_binary);

        add_context(run.run, q, ctx);

        std::shared_ptr<CoverageMapping> mapping = coverage_map.at(
            {run.run.test_profile, run.run.test_binary});


        if (mapping.get() == nullptr) {
            throw std::logic_error(
                fmt("Failed to load coverage mapping profile={} binary={}",
                    run.run.test_profile,
                    run.run.test_binary));
        }

        if (config.coverage_mapping_dump) {
            auto j = to_json_eval(*mapping);
            auto path //
                = fs::path{*config.coverage_mapping_dump}
                / fmt("coverage_mapping_{}.json", run.index);

            LOG(INFO) << fmt("coverage-mapping-dump={}", path);
            writeFile(path, j.dump(2));
        }

        json j_run = json::object();
        {
            __perf_trace("sql", "Full coverage run info");
            SQLite::Transaction transaction{db};
            {
                __perf_trace("sql", "Covered files");
                json j_files = json::object();
                for (auto const& file : mapping->getUniqueSourceFiles()) {
                    std::string debug;
                    if (!ctx.file_matches(file.str(), debug)) {
                        j_files["skipped"].push_back(
                            json::object({
                                {"file", file.str()},
                                {"reason", debug},
                            }));
                        continue;
                    }
                    __perf_trace("sql", "Add file", "File", file.str());
                    add_file(mapping.get(), file, q, ctx);
                }

                j_run["covered_files"] = j_files;
            }

            transaction.commit();
        }


        debug["runs"].push_back(j_run);
    }
}

struct BuildProfileEvent {
    int                  pid{};
    int                  tid{};
    hstd::Str            ph{};
    int                  ts{};
    int                  dur{};
    hstd::Str            name{};
    hstd::Opt<hstd::Str> cat{};
    json                 args{};

    DESC_FIELDS(
        BuildProfileEvent,
        (pid, tid, ph, ts, dur, name, cat, args));
};

struct BuildProfileFile {
    hstd::Vec<BuildProfileEvent> traceEvents;
    hstd::Str                    path;
    hstd::u64                    beginningOfTime;
    DESC_FIELDS(BuildProfileFile, (traceEvents, path, beginningOfTime));
};

struct BuildProfileCollection {
    hstd::Vec<BuildProfileFile> files;
    DESC_FIELDS(BuildProfileCollection, (files));
};

std::string generateInstantiateFunctionReport(
    const BuildProfileCollection& collection) {
    __perf_trace("main", "generateInstantiateFunctionReport");
    std::map<std::string, std::vector<BuildProfileEvent>> groupEvents;

    for (const auto& file : collection.files) {
        for (const auto& event : file.traceEvents) {
            if (event.name == "InstantiateFunction"
                && event.args.contains("detail")) {
                std::string detail = event.args.at("detail")
                                         .get<std::string>();
                // if (detail.length() > 120) {
                //     detail = detail.substr(0, 120) + "...";
                // }
                groupEvents[detail].push_back(event);
            }
        }
    }

    std::vector<std::pair<std::string, std::vector<BuildProfileEvent>>>
        sortedGroups;
    for (const auto& [detail, events] : groupEvents) {
        sortedGroups.push_back({detail, events});
    }

    std::sort(
        sortedGroups.begin(),
        sortedGroups.end(),
        [](const auto& a, const auto& b) {
            int totalDurA = 0;
            int totalDurB = 0;
            for (const auto& event : a.second) { totalDurA += event.dur; }
            for (const auto& event : b.second) { totalDurB += event.dur; }
            return totalDurB < totalDurA;
        });

    auto formatDuration = [](int microseconds) -> std::string {
        if (microseconds < 1000) {
            return std::format("{}µs", microseconds);
        }
        int ms          = microseconds / 1000;
        int remainingUs = microseconds % 1000;
        if (ms < 1000) {
            if (remainingUs == 0) { return std::format("{}ms", ms); }
            return std::format("{}ms {}µs", ms, remainingUs);
        }
        int s           = ms / 1000;
        int remainingMs = ms % 1000;
        if (remainingMs == 0 && remainingUs == 0) {
            return std::format("{}s", s);
        }
        if (remainingUs == 0) {
            return std::format("{}s {}ms", s, remainingMs);
        }
        if (remainingMs == 0) {
            return std::format("{}s {}µs", s, remainingUs);
        }
        return std::format("{}s {}ms {}µs", s, remainingMs, remainingUs);
    };

    std::string report;
    // int limit = std::min(40, static_cast<int>(sortedGroups.size()));
    for (int i = 0; i < sortedGroups.size(); ++i) {
        const auto& [detail, events] = sortedGroups.at(i);
        int totalDur                 = 0;
        for (const auto& event : events) { totalDur += event.dur; }
        int count  = static_cast<int>(events.size());
        int avgDur = totalDur / count;

        report += std::format(
            "{} = {} * {}: {}\n",
            formatDuration(totalDur),
            count,
            formatDuration(avgDur),
            detail);
    }

    return report;
}

NO_COVERAGE void build_build_coverage_merge(
    ProfdataCLIConfig const& config) {

    BuildProfileCollection collection;

    {
        __perf_trace("main", "Parse JSON files");
        int count = 0;
        for (const auto& entry :
             std::filesystem::recursive_directory_iterator{
                 config.coverage}) {
            if (entry.is_regular_file()
                && entry.path().extension() == ".json"
                && entry.path().stem().extension() == ".cpp") {
                // if (30 < ++count) { continue; }
                auto file = hstd::from_json_eval<BuildProfileFile>(
                    json::parse(hstd::readFile(entry.path())));
                file.path = entry.path().native();
                collection.files.push_back(file);
                LOG(INFO) << file.path << " OK";
            }
        }
    }

    auto report = generateInstantiateFunctionReport(collection);
    LOG(INFO) << "\n" << report;
    hstd::writeFile(config.coverage_db, report);
}

NO_COVERAGE void build_run_coverage_merge(
    ProfdataCLIConfig const& config) {
    json debug = json::object();

    auto flush_debug = [&]() {
        if (config.debug_file) {
            fs::path      out_path{config.debug_file.value()};
            std::ofstream os{out_path};
            os << debug.dump();
        }
    };

    finally{flush_debug};


    LOG(INFO) << std::format(
        "Using test summary file {}", config.coverage);

    if (config.debug_file) {
        LOG(INFO) << std::format(
            "Debug file enabled {}", config.debug_file);
    }

    auto summary = JsonSerde<ProfdataFullProfile>::from_json(
        json::parse(read_file(config.coverage)));

    fs::path db_file{config.coverage_db};


    if (fs::exists(db_file)) { fs::remove(db_file); }

    SQLite::Database db{
        db_file.native(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
    CreateTables(db);
    queries q{db};

    db_build_ctx ctx;
    auto         FS = llvm::vfs::getRealFileSystem();


    auto get_regex_list = [](std::vector<std::string> const& list)
        -> std::vector<llvm::Regex> {
        std::vector<llvm::Regex> result;

        for (auto const& filter : list) {
            llvm::Regex r{filter};
            std::string error;
            if (r.isValid(error)) {
                result.push_back(std::move(r));
            } else {
                throw std::domain_error(
                    "Failed to compile regex for " + filter + ": "
                    + error);
            }
        }

        return result;
    };

    ctx.file_blacklist = get_regex_list(config.file_blacklist);
    ctx.file_whitelist = get_regex_list(config.file_whitelist);

    Vec<Vec<ProfdataRun>> runGroups;
    for (auto const& [run_idx, run] : enumerate(summary.runs)) {
        if (run_idx % config.run_group_batch_size == 0) {
            runGroups.push_back({});
        }

        runGroups.back().push_back(
            ProfdataRun{
                .index = run_idx,
                .run   = run,
            });
    }

    for (auto const& group : runGroups) {
        process_runs(
            group,
            config,
            summary.runs.size(),
            flush_debug,
            ctx,
            q,
            debug,
            db);
    }
}

NO_COVERAGE int main(int argc, char** argv) {
    if (argc != 2) {
        throw std::logic_error(
            "Expected single positional argument -- JSON literal "
            "with parameters or absolute path to the JSON "
            "configuration file.");
    }

    std::string json_parameters;
    if (std::string{argv[1]}.starts_with("/")) {
        if (!fs::exists(argv[1])) {
            throw std::logic_error(
                std::format(
                    "Input configuration file '{}' does not exist",
                    argv[1]));
        }
        json_parameters = read_file(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    auto config = JsonSerde<ProfdataCLIConfig>::from_json(
        json::parse(json_parameters));

#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession> perfetto_session;
    if (config.perf_trace) {
        perfetto_session = StartProcessTracing("profdata_merger");
    }
#endif

    if (config.mode == ProfdataCLIConfig::Mode::RunProfileMerge) {
        build_run_coverage_merge(config);
    } else {
        build_build_coverage_merge(config);
    }

    if (config.perf_trace) {
        fs::path out_path{config.perf_trace.value()};
#ifdef ORG_USE_PERFETTO
        StopTracing(std::move(perfetto_session), out_path);
#endif
    }

    return 0;
}
