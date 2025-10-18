#pragma once

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/diffs.hpp>

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

hstd::fs::path getDebugFile(
    const hstd::Str& suffix      = "",
    bool             cleanParent = false);

hstd::fs::path getDebugDir(
    const hstd::Str& suffix = "",
    bool             clean  = false);

hstd::log::log_sink_scope getDebugLogScope(
    hstd::Str const& suffix      = "execution.log",
    bool             cleanParent = false);


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


template <typename T>
hstd::ColText __gtest_assert_eq_seq_fail_message(
    T const& lhs,
    T const& rhs) {
    return hstd::formatDiffed(
        lhs,
        rhs,
        hstd::FormattedDiff::Conf{
            .formatLine = hstd::FormattedDiff::getSequenceFormatterCb(
                &lhs, &rhs, true)});
}

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<std::string>(
    std::string const& lhs,
    std::string const& rhs);

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::Str>(
    hstd::Str const& lhs,
    hstd::Str const& rhs);

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::ColText>(
    hstd::ColText const& lhs,
    hstd::ColText const& rhs);

#define GTEST_ASSERT_EQ_SEQ(__lhs_arg, __rhs_arg)                         \
    {                                                                     \
        auto const __lhs = __lhs_arg;                                     \
        auto const __rhs = __rhs_arg;                                     \
        if (!(__lhs == __rhs)) {                                          \
            FAIL() << __gtest_assert_eq_seq_fail_message(__lhs, __rhs)    \
                          .toString(false);                               \
        }                                                                 \
    }
