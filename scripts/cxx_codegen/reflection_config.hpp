#pragma once

#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

#define NO_COVERAGE                                                       \
    __attribute__((no_sanitize("coverage", "address", "thread")))


struct ProfdataConfig {
    std::string                coverage;
    std::string                coverage_db;
    std::vector<std::string>   file_whitelist = {".*"};
    std::vector<std::string>   file_blacklist;
    std::optional<std::string> debug_file            = std::nullopt;
    std::optional<std::string> coverage_mapping_dump = std::nullopt;
    int                        run_group_batch_size  = 8;

    DESC_FIELDS(
        ProfdataConfig,
        (coverage,
         coverage_db,
         file_whitelist,
         file_blacklist,
         debug_file,
         coverage_mapping_dump));
};

struct ReflectionConfig {
    /// \brief Path to the compilation database for the clang tool
    std::string                compilation_database;
    std::optional<std::string> toolchain_include;
    std::optional<std::string> clang_resource_dir = std::nullopt;

    /// \brief Disable standard library include path
    bool no_std_include = false;


    DESC_FIELDS(
        ReflectionConfig,
        (compilation_database,
         toolchain_include,
         clang_resource_dir,
         no_std_include));
};

struct ReflectionCLI {
    DECL_DESCRIBED_ENUM(
        Mode,
        /// \brief Generate summary report database for the runtime performance
        /// profiling of the project. 
        RunProfileMerge,
        /// \brief Generate summary report for the build performance profile
        /// of the project
        BuildProfileMerge,
        /// \brief Collect all symbols defined in the targeted files
        AllTargetedFiles,
        /// \brief Collect all symbols defined in the main translation units 
        /// of the files in compilation database. 
        AllMainSymbolsInCompilationDb,
        /// \brief Collect all symbols explicitly annotated with the `[[refl]]` 
        /// attirbute, no matter which file they are defined -- main file of the 
        /// translation unit or a transitive include. 
        AllAnotatedSymbols,
        /// \brief Collect all binary symbols with their sizes. 
        BinarySymbols);

    Mode                       mode = Mode::RunProfileMerge;
    ProfdataConfig             profdata;
    ReflectionConfig           reflection;
    std::optional<std::string> perf_path   = std::nullopt;
    std::optional<std::string> log_path    = std::nullopt;
    bool                       verbose_log = false;

    std::string            output;
    hstd::Vec<std::string> input;

    DESC_FIELDS(
        ReflectionCLI,
        (mode,
         profdata,
         reflection,
         perf_path,
         verbose_log,
         input,
         output));
};
