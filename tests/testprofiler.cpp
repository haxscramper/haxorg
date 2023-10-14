#include "testprofiler.hpp"

#include <xray/xray_interface.h>
#include <xray/xray_log_interface.h>
#include <xray/xray_records.h>
#include <format>
#include <exception>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

extern "C" void __llvm_profile_reset_counters(void);
extern "C" void __llvm_profile_set_filename(char*);
extern "C" int  __llvm_profile_write_file(void);

Vec<TestProfiler::RunRecord> TestProfiler::runRecords;

json TestProfiler::getJsonRecords() {
    json res;
    to_json(res, TestProfiler::runRecords);
    return res;
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

void move_latest_xray_log_to_path(const std::string& path) {

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

    if (!found) {
        throw std::logic_error(
            "No matching xray-log files found for program name '"
            + program_name + "'");
    }

    // Move the latest file to the specified path
    safe_move(latest_file, path);
}


void TestProfiler::SetUp() {
    if (fs::exists(pgo_path)) {
        fs::remove(pgo_path);
    }
    __llvm_profile_set_filename(pgo_path.data());


    XRayLogRegisterStatus select = __xray_log_select_mode("xray-basic");
    if (select != XRayLogRegisterStatus::XRAY_REGISTRATION_OK) {
        throw std::logic_error(std::format(
            "Failed to select xray-basic mode, the code was '{}'",
            (int)select));
    }


    std::string options = std::format(
        "verbosity=1 no_file_flush=true xray_logfile_base={}", xray_path);

    XRayLogInitStatus init_mode_status = __xray_log_init_mode(
        "xray-basic", options.data());

    if (init_mode_status != XRayLogInitStatus::XRAY_LOG_INITIALIZED) {
        throw std::logic_error(std::format(
            "__xray_log_init_mode() failed, the code was '{}'",
            (int)init_mode_status));
    }

    __xray_remove_customevent_handler();

    auto patch_status = __xray_patch();
    if (patch_status != XRayPatchingStatus::SUCCESS) {
        throw std::logic_error(std::format(
            "__xray_patch() failed, the code was '{}'",
            (int)patch_status));
    }

    __llvm_profile_reset_counters();
}

void TestProfiler::TearDown() {
    int profile_result = __llvm_profile_write_file();
    if (profile_result != 0) {
        throw std::logic_error(std::format(
            "Failed to write PGO data to '{}'", pgo_path.data()));
    }

    auto finalize_status = __xray_log_finalize();
    if (finalize_status != XRAY_LOG_FINALIZED) {
        throw std::logic_error(std::format(
            "Failed to finalize XRAY Log, the status is, the code was "
            "'{}'",
            (int)finalize_status));
    }

    auto flush_status = __xray_log_flushLog();
    if (flush_status != XRAY_LOG_FLUSHED) {
        throw std::logic_error(std::format(
            "Failed to flush XRAY log, the status is "
            "'{}'",
            (int)flush_status));
    }

    __xray_unpatch();
    move_latest_xray_log_to_path(xray_path);
    RunRecord& rec = runRecords.emplace_back();
    rec.xray_path  = xray_path;
    rec.pgo_path   = pgo_path;
    rec.metadata   = metadata;
}
