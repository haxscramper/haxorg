#include <absl/flags/parse.h>
#include <gtest/gtest.h>

#include <hstd_cpp_lib/extra/error_format/gtest_utils.hpp>

#include "hstd_tests_common.hpp"
#include <hstd_cpp_lib/stdlib/algorithms/reflection/reflection_visitor.hpp>

HSTD_REGISTER_TYPE_FIELD_NAMES(reflection_test::reflection_named);

int main(int argc, char** argv) {
    hstd::log::clear_sink_backends();
    hstd::log::push_sink(hstd::log::init_file_sink("/tmp/t_hstd_test.log"));
    HSLOG_INFO("test");
    init_gtest_tests(argc, argv);

    ::absl::ParseCommandLine(argc, argv);

    auto result = RUN_ALL_TESTS();
    return result;
}
