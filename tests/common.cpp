#include "common.hpp"

hstd::fs::path getDebugFile(const hstd::Str& suffix, bool cleanParent) {
    auto dir = std::filesystem::temp_directory_path()
             / hstd::fs::path{hstd::fmt(
                 "haxorg_tests/{}",
                 ::testing::UnitTest::GetInstance()
                     ->current_test_info()
                     ->test_suite_name())};

    auto testname = ::testing::UnitTest::GetInstance()
                        ->current_test_info()
                        ->name();
    hstd::fs::path outPath;

    if (suffix.empty()) {
        hstd::Str result = hstd::fmt("{}/{}", dir.native(), testname);
        hstd::createDirectory(hstd::fs::path{result.toBase()});
        outPath = result.toBase();
    } else {
        hstd::Str result = hstd::fmt(
            "{}/{}/{}", dir.native(), testname, suffix);
        hstd::createDirectory(
            hstd::fs::path{result.toBase()}.parent_path());
        outPath = result.toBase();
    }

    if (cleanParent) {
        auto parent = outPath.parent_path();
        if (hstd::fs::exists(parent)) {
            hstd::fs::remove_all(parent);
            hstd::createDirectory(parent);
        }
    }

    return outPath;
}


hstd::log::log_sink_scope getDebugLogScope(
    const hstd::Str& suffix,
    bool             cleanParent) {
    return HSLOG_SINK_FACTORY_SCOPED(([suffix, cleanParent]() {
        return ::hstd::log::init_file_sink(
            getDebugFile(suffix, cleanParent).native());
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
        __gtest_assert_eq_seq_fail_message(
            lhs.split('\n'), lhs.split('\n')),
        lhs,
        rhs);
}
