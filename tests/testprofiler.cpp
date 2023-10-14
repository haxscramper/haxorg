#include "testprofiler.hpp"

#include <xray/xray_interface.h>
#include <xray/xray_log_interface.h>
#include <xray/xray_records.h>
#include <format>
#include <exception>

extern "C" void __llvm_profile_reset_counters(void);
extern "C" void __llvm_profile_set_filename(char*);
extern "C" int  __llvm_profile_write_file(void);

Vec<TestProfiler::RunRecord> TestProfiler::runRecords;

json TestProfiler::getJsonRecords() {
    json res;
    to_json(res, TestProfiler::runRecords);
    return res;
}

void TestProfiler::SetUp() {
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


    auto patch_status = __xray_patch();
    if (patch_status != XRayPatchingStatus::SUCCESS) {
        throw std::logic_error(std::format(
            "__xray_patch() failed, the code was '{}'",
            (int)patch_status));
    }

    __llvm_profile_reset_counters();
}

void TestProfiler::TearDown() {
    __llvm_profile_set_filename(pgo_path.data());
    __llvm_profile_write_file();

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
    RunRecord& rec = runRecords.emplace_back();
    rec.xray_path  = xray_path;
    rec.pgo_path   = pgo_path;
    rec.metadata   = metadata;
}
