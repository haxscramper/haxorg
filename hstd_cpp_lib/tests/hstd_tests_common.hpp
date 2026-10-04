#pragma once

#include <hstd_cpp_lib/extra/error_format/gtest_utils.hpp>


namespace reflection_test {
struct reflection_named {
    int f1;
    int f2;
    DESC_FIELDS(reflection_named, (f1, f2));
};
} // namespace reflection_test
