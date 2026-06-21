#pragma once

#include <string>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/JsonUse.hpp>

struct TestProfiler {
    std::string xray_path;
    std::string pgo_path;
    json        metadata;

    struct RunRecord {
        std::string xray_path = "";
        std::string pgo_path  = "";
        json        metadata  = json{};
        DESC_FIELDS(RunRecord, (xray_path, pgo_path, metadata));
    };

    static hstd::Vec<RunRecord> runRecords;
    static json                 getJsonRecords();

    TestProfiler(
        std::string const& xray_path,
        std::string const& pgo_path,
        json const&        metadata = json())
        : xray_path(xray_path), pgo_path(pgo_path), metadata(metadata) {}

    [[clang::xray_never_instrument, gnu::no_profile_instrument_function]] void SetUp();

    [[clang::xray_never_instrument, gnu::no_profile_instrument_function]] void TearDown();
};
