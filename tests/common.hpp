#pragma once

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Filesystem.hpp>

struct TestParameters {
    hstd::Str corpusGlob;
};

extern TestParameters testParameters;

#include <gtest/gtest.h>
// #include <gmock/gmock.h>

// adl-based customization points is the most disgusting degenerate idea
// you can possible have. The shit doesn't work reliably, you need to do
// some fucking magic with namespaces and whatever the fuck else, it does
// not work again, and with functions you need to specify the concrete type
// for every type. If this was a structure I could've used `std::format`
// with some form of concept here, if the library was actually written with
// this in mind.
//
// And this pile of vomit stopped working at random. Fuck this shit, I
// cannot believe anyone would even consider writing a library that would
// depend on ADL for customization points. It is a pure unmitigated
// disaster with no way to debug or consistently provide implementation.
#define GTEST_ADL_PRINT_TYPE(__type)                                      \
    namespace testing {                                                   \
        inline std::string PrintToString(__type const& value) {           \
            return hstd::fmt1(value);                                     \
        }                                                                 \
                                                                          \
        namespace internal {                                              \
            template <typename Other>                                     \
            class FormatForComparison<__type, Other> {                    \
              public:                                                     \
                static ::std::string Format(const __type& value) {        \
                    return hstd::fmt1(value);                             \
                }                                                         \
            };                                                            \
        }                                                                 \
    } // namespace testing


GTEST_ADL_PRINT_TYPE(hstd::Str);

inline hstd::Str getDebugFile(const hstd::Str& suffix = "") {
    auto dir      = hstd::fs::path{hstd::fmt(
        "/tmp/haxorg_tests/{}",
        ::testing::UnitTest::GetInstance()
            ->current_test_info()
            ->test_suite_name())};
    auto testname = ::testing::UnitTest::GetInstance()
                        ->current_test_info()
                        ->name();
    if (suffix.empty()) {
        hstd::Str result = hstd::fmt("{}/{}", dir.native(), testname);
        hstd::createDirectory(hstd::fs::path{result.toBase()});
        return result;
    } else {
        hstd::Str result = hstd::fmt(
            "{}/{}/{}", dir.native(), testname, suffix);
        hstd::createDirectory(
            hstd::fs::path{result.toBase()}.parent_path());
        return result;
    }
}
