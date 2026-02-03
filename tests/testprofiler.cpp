#include "testprofiler.hpp"

#include <xray/xray_interface.h>
#include <xray/xray_log_interface.h>
#include <xray/xray_records.h>
#include <regex>
#include <filesystem>
#include <hstd/stdlib/JsonSerde.hpp>

#include <haxorg/sem/perfetto_org.hpp>

namespace fs = std::filesystem;

extern "C" void __llvm_profile_reset_counters(void);
extern "C" void __llvm_profile_set_filename(char*);
extern "C" int  __llvm_profile_write_file(void);

hstd::Vec<TestProfiler::RunRecord> TestProfiler::runRecords;

json TestProfiler::getJsonRecords() {
    return to_json_eval(TestProfiler::runRecords);
}

std::string get_current_program_name() {
    return fs::read_symlink("/proc/self/exe").filename().string();
}

void safe_move(const fs::path& from, const fs::path& to) {
    std::error_code ec_remove, ec_rename, ec_copy;

    // Check if the target file exists, if it does, delete it.
    if (fs::exists(to)) {
        fs::remove(to, ec_remove);
        if (ec_remove) {
            throw std::runtime_error(
                "Failed to remove existing destination file: "
                + ec_remove.message());
        }
    }

    // Try to rename (move) the file.
    fs::rename(from, to, ec_rename);
    if (ec_rename) {
        // If rename failed, try to copy and then delete
        fs::copy(from, to, ec_copy);
        if (ec_copy) {
            throw std::runtime_error(
                "Failed to copy file after rename failed: "
                + ec_copy.message());
        }
        fs::remove(from);
    }
}


bool move_latest_xray_log_to_path(const std::string& path) {

    // Get the program name
    std::string program_name = get_current_program_name();

    // Build the regex pattern
    std::regex pattern("xray-log\\." + program_name + "\\.\\w{6}");

    fs::path           latest_file;
    fs::file_time_type latest_time;

    bool found = false;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (std::regex_match(entry.path().filename().string(), pattern)) {
            // If it's the first match or the file is newer than the
            // previous match
            if (!found || entry.last_write_time() > latest_time) {
                latest_time = entry.last_write_time();
                latest_file = entry.path();
                found       = true;
            }
        }
    }

    if (found) {
        // Move the latest file to the specified path
        safe_move(latest_file, path);
        return true;

    } else {
        std::cerr
            << ("No matching xray-log files found for program name '"
                + program_name + "'")
            << std::endl;
        return false;
    }
}


void TestProfiler::SetUp() {
#ifdef ORG_USE_PERFETTO
    TRACE_EVENT_BEGIN("cli", "Execute test");
#endif
    __perf_trace("cli", "Setup test");

#ifdef ORG_USE_PGO
    if (fs::exists(pgo_path)) { fs::remove(pgo_path); }
    __llvm_profile_set_filename(pgo_path.data());
#endif

#ifdef ORG_USE_XRAY
    {
        __perf_trace("cli", "XRay setup for test");
        {
            __perf_trace("cli", "Log select mode ");
            XRayLogRegisterStatus select = __xray_log_select_mode(
                "xray-fdr");
            if (select != XRayLogRegisterStatus::XRAY_REGISTRATION_OK) {
                throw std::logic_error(
                    std::format(
                        "Failed to select xray-basic mode, the code was "
                        "'{}'",
                        (int)select));
            }
        }


        {
            __perf_trace("cli", "Log init mode");
            std::string options = std::format(
                "buffer_size=16384:"
                "buffer_max={}",
                (1 << 16));

            XRayLogInitStatus init_mode_status = __xray_log_init_mode(
                "xray-fdr", options.data());

            if (init_mode_status
                != XRayLogInitStatus::XRAY_LOG_INITIALIZED) {
                throw std::logic_error(
                    std::format(
                        "__xray_log_init_mode() failed, the code was '{}'",
                        (int)init_mode_status));
            }
        }
        {
            __perf_trace("cli", "Remove custom event handlers");
            __xray_remove_customevent_handler();
        }
        {
            __perf_trace("cli", "Xray patch");
            auto patch_status = __xray_patch();
            if (patch_status != XRayPatchingStatus::SUCCESS) {
                throw std::logic_error(
                    std::format(
                        "__xray_patch() failed, the code was '{}'",
                        (int)patch_status));
            }
        }
    }
#endif

#ifdef ORG_USE_PGO
    {
        __perf_trace("cli", "Remove LLVM counters");
        __llvm_profile_reset_counters();
    }
#endif
}

void TestProfiler::TearDown() {
    __perf_trace("cli", "Finalize test");

#ifdef ORG_USE_PGO
    {
        __perf_trace("cli", "Write PGO profile data");
        int profile_result = __llvm_profile_write_file();
        if (profile_result != 0) {
            throw std::logic_error(
                std::format(
                    "Failed to write PGO data to '{}'", pgo_path.data()));
        }
    }
#endif

#ifdef ORG_USE_XRAY
    {
        __perf_trace("cli", "XRay finalize data");
        auto finalize_status = __xray_log_finalize();
        if (finalize_status != XRAY_LOG_FINALIZED) {
            throw std::logic_error(
                std::format(
                    "Failed to finalize XRAY Log, the status is, the code "
                    "was "
                    "'{}'",
                    (int)finalize_status));
        }
    }

    {
        __perf_trace("cli", "XRay flush log");
        auto flush_status = __xray_log_flushLog();
        if (flush_status != XRAY_LOG_FLUSHED) {
            throw std::logic_error(
                std::format(
                    "Failed to flush XRAY log, the status is "
                    "'{}'",
                    (int)flush_status));
        }
    }

    {
        __perf_trace("cli", "XRay unpatch");
        XRayPatchingStatus status = __xray_unpatch();
        if (status != XRayPatchingStatus::SUCCESS) {
            throw std::logic_error(
                std::format(
                    "Failed to unpatch xray, the status is "
                    "'{}'",
                    (int)status));
        }
    }

    bool hasXray = false;
    {
        __perf_trace("cli", "XRay move log to target");
        hasXray = move_latest_xray_log_to_path(xray_path);
    }
    {
        __perf_trace("cli", "Remove xray log implementation");
        __xray_remove_log_impl();
    }
#endif


    RunRecord& rec = runRecords.emplace_back();
    rec.metadata   = metadata;

#ifdef ORG_USE_XRAY
    if (hasXray) { rec.xray_path = xray_path; }
#endif

#ifdef ORG_USE_PGO
    rec.pgo_path = pgo_path;
#endif


#ifdef ORG_USE_PERFETTO
    TRACE_EVENT_END("cli");
#endif
}
