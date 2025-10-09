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
    inline std::string PrintToString(__type const& value) {               \
        return hstd::fmt1(value);                                         \
    }                                                                     \
                                                                          \
    namespace internal {                                                  \
    template <typename Other>                                             \
    class FormatForComparison<__type, Other> {                            \
      public:                                                             \
        static ::std::string Format(const __type& value) {                \
            return hstd::fmt1(value);                                     \
        }                                                                 \
    };                                                                    \
    }                                                                     \
    } // namespace testing


GTEST_ADL_PRINT_TYPE(hstd::Str);

inline hstd::fs::path getDebugFile(
    const hstd::Str& suffix      = "",
    bool             cleanParent = false) {
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


template <typename T>
struct TestValueFormat {
    static std::string format(T const& t) { return fmt1(t); }
};


template <typename T1, typename T2>
struct TestValueCompareFormat {
    static std::string format(
        T1 const&   t1,
        T2 const&   t2,
        char const* lhs,
        char const* rhs) {
        return ::hstd::fmt(
            "Expected equality of these values:\n  {}\n    {}\n  "
            "{}\n "
            "   {}",
            lhs,
            t1,
            rhs,
            t2);
    }
};

template <typename T1, typename T2>
std::string format_test_fail(
    T1 const&   t1,
    T2 const&   t2,
    char const* lhs,
    char const* rhs) {
    return TestValueCompareFormat<T1, T2>::format(t1, t2, lhs, rhs);
}

// use when shitty ADL lookup solution that 1000IQ shitbags from google
// cooked fails to work. Not like there are any other ways to make test
// suite print values in some sane capacity, greasy cumshots are splattered
// over the docs are not worth shit, they don't even match whatever is in
// the `gtest.h` header. `AbslStringify`, right. Fuck you.
#define EXPECT_EQ2(lhs, rhs)                                              \
    EXPECT_EQ(lhs, rhs) << format_test_fail(lhs, rhs, #lhs, #rhs)
