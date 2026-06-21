#include "common.hpp"

#include <google/protobuf/util/json_util.h>

namespace {
hstd::fs::path getDebugPath(hstd::Str const& suffix) {
    auto* info = ::testing::UnitTest::GetInstance()->current_test_info();

    hstd::Str testId = info->name();

    if (auto const* valueParam = info->value_param(); valueParam != nullptr) {
        testId += hstd::fmt("/value-{}", valueParam);
    }

    if (auto const* typeParam = info->type_param(); typeParam != nullptr) {
        testId += hstd::fmt("/type-{}", typeParam);
    }

    auto dir = std::filesystem::temp_directory_path()
             / hstd::fs::path{hstd::fmt("haxorg_tests/{}", info->test_suite_name())};

    if (suffix.empty()) {
        return hstd::fs::path{hstd::fmt("{}/{}", dir.native(), testId)};
    } else {
        return hstd::fs::path{hstd::fmt("{}/{}/{}", dir.native(), testId, suffix)};
    }
}
} // namespace


hstd::fs::path getDebugFile(hstd::Str const& suffix, bool cleanParent) {
    auto file = getDebugPath(suffix);

    if (cleanParent) {
        auto parent = file.parent_path();
        if (hstd::fs::exists(parent)) {
            hstd::fs::remove_all(parent);
            hstd::createDirectory(parent);
        }
    }


    if (suffix.empty()) {
        hstd::createDirectory(file);
    } else {
        hstd::createDirectory(file.parent_path());
    }

    return file;
}

hstd::fs::path getDebugDir(hstd::Str const& suffix, bool clean) {
    auto dir = getDebugPath(suffix);

    if (clean) {
        if (hstd::fs::exists(dir)) {
            hstd::fs::remove_all(dir);
            hstd::createDirectory(dir);
        }
    }

    hstd::createDirectory(dir);
    return dir;
}


hstd::log::log_sink_scope getDebugLogScope(hstd::Str const& suffix, bool cleanParent) {
    return HSLOG_SINK_FACTORY_SCOPED(([suffix, cleanParent]() {
        return ::hstd::log::init_file_sink(getDebugFile(suffix, cleanParent));
    }));
}


template <typename T>
hstd::ColText __gtest_assert_eq_seq_format_text_compare(
    hstd::ColText const& diff,
    T const&             lhs,
    T const&             rhs) {
    hstd::ColStream os;
    os << diff;
    os << "\nGiven lhs:\n";
    os << hstd::Str("+").repeated(32) << "\n";
    os << lhs;
    os << "\n" << hstd::Str("+").repeated(32) << "\n";
    os << "\nExpected rhs:\n";
    os << hstd::Str("-").repeated(32) << "\n";
    os << rhs;
    os << "\n" << hstd::Str("-").repeated(32) << "\n";
    return os.getBuffer();
}

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<std::string>(
    std::string const& lhs,
    std::string const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(
            hstd::split(lhs, '\n'), hstd::split(rhs, '\n')),
        lhs,
        rhs);
}

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::Str>(
    hstd::Str const& lhs,
    hstd::Str const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(
            hstd::split(lhs, '\n'), hstd::split(rhs, '\n')),
        lhs,
        rhs);
}

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::ColText>(
    hstd::ColText const& lhs,
    hstd::ColText const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(lhs.split('\n'), rhs.split('\n')), lhs, rhs);
}

std::string getJString(google::protobuf::Message const& message) {
    std::string                          json;
    google::protobuf::json::PrintOptions j_opts;
    j_opts.add_whitespace = true;
    auto status = google::protobuf::util::MessageToJsonString(message, &json, j_opts);

    EXPECT_TRUE(status.ok());
    return json;
}
