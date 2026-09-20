#pragma once

#include <boost/preprocessor/facilities/overload.hpp>
#include <google/protobuf/message.h>
#include <hstd_cpp_lib/logger/logger.hpp>
#include <hstd_cpp_lib/stdlib/Filesystem.hpp>
#include <hstd_cpp_lib/stdlib/Str.hpp>
#include <hstd_cpp_lib/stdlib/algorithms/diff/diffs.hpp>
#include <hstd_cpp_lib/stdlib/containers/Outcome.hpp>

#include <absl/log/initialize.h>
#include <absl/log/internal/globals.h>
#include <absl/log/log_sink_registry.h>
#include <absl/strings/str_split.h>
#include <sys/resource.h>

#include <fstream>
#include <gtest/gtest.h>
#include <hstd_cpp_lib/stdlib/formatting/Debug.hpp>
#include <hstd_cpp_lib/system/aux_utils.hpp>
#include <iostream>


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
// for every type. If this was a structure I could've used `fmt::format`
// with some form of concept here, if the library was actually written with
// this in mind.
//
// And this pile of vomit stopped working at random. Fuck this shit, I
// cannot believe anyone would even consider writing a library that would
// depend on ADL for customization points. It is a pure unmitigated
// disaster with no way to debug or consistently provide implementation.
#define GTEST_ADL_PRINT_TYPE(__type)                                                     \
    namespace testing {                                                                  \
    inline std::string PrintToString(__type const& value) { return hstd::fmt1(value); }  \
                                                                                         \
    namespace internal {                                                                 \
    template <typename Other>                                                            \
    class FormatForComparison<__type, Other> {                                           \
      public:                                                                            \
        static ::std::string Format(const __type& value) { return hstd::fmt1(value); }   \
    };                                                                                   \
    }                                                                                    \
    } // namespace testing


GTEST_ADL_PRINT_TYPE(hstd::Str);

namespace {
inline hstd::fs::path getDebugPath(
    hstd::Str const&           suffix,
    std::optional<std::string> value_param_override,
    std::optional<std::string> type_param_override) {
    auto* info = ::testing::UnitTest::GetInstance()->current_test_info();

    hstd::Str testId = info->name();

    if (auto const* valueParam = info->value_param(); valueParam != nullptr) {
        testId += hstd::fmt("/value-{}", value_param_override.value_or(valueParam));
    }

    if (auto const* typeParam = info->type_param(); typeParam != nullptr) {
        testId += hstd::fmt("/type-{}", type_param_override.value_or(typeParam));
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


inline hstd::fs::path getDebugFile(
    const hstd::Str&           suffix               = "",
    bool                       cleanParent          = false,
    std::optional<std::string> value_param_override = std::nullopt,
    std::optional<std::string> type_param_override  = std::nullopt) {
    auto file = getDebugPath(suffix, value_param_override, type_param_override);

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

inline hstd::fs::path getDebugDir(
    const hstd::Str&           suffix               = "",
    bool                       clean                = false,
    std::optional<std::string> value_param_override = std::nullopt,
    std::optional<std::string> type_param_override  = std::nullopt) {
    auto dir = getDebugPath(suffix, value_param_override, type_param_override);

    if (clean) {
        if (hstd::fs::exists(dir)) {
            hstd::fs::remove_all(dir);
            hstd::createDirectory(dir);
        }
    }

    hstd::createDirectory(dir);
    return dir;
}

inline hstd::log::log_sink_scope getDebugLogScope(
    hstd::Str const& suffix,
    bool             cleanParent) {
    return HSLOG_SINK_FACTORY_SCOPED(([suffix, cleanParent]() {
        return ::hstd::log::init_file_sink(getDebugFile(suffix, cleanParent));
    }));
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
#define EXPECT_EQ2(lhs, rhs) EXPECT_EQ(lhs, rhs) << format_test_fail(lhs, rhs, #lhs, #rhs)


template <typename T>
inline hstd::ColText __gtest_assert_eq_seq_fail_message(T const& lhs, T const& rhs) {
    return hstd::formatDiffed(
        lhs,
        rhs,
        hstd::FormattedDiff::Conf{
            .formatLine = hstd::FormattedDiff::getSequenceFormatterCb(&lhs, &rhs, true)});
}


template <typename T>
inline hstd::ColText __gtest_assert_eq_seq_format_text_compare(
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
inline hstd::ColText __gtest_assert_eq_seq_fail_message<std::string>(
    std::string const& lhs,
    std::string const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(
            hstd::split(lhs, '\n'), hstd::split(rhs, '\n')),
        lhs,
        rhs);
}

template <>
inline hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::Str>(
    hstd::Str const& lhs,
    hstd::Str const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(
            hstd::split(lhs, '\n'), hstd::split(rhs, '\n')),
        lhs,
        rhs);
}

template <>
inline hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::ColText>(
    hstd::ColText const& lhs,
    hstd::ColText const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(lhs.split('\n'), rhs.split('\n')), lhs, rhs);
}


#define GTEST_ASSERT_EQ_SEQ(__lhs_arg, __rhs_arg)                                        \
    {                                                                                    \
        auto const __lhs = __lhs_arg;                                                    \
        auto const __rhs = __rhs_arg;                                                    \
        if (!(__lhs == __rhs)) {                                                         \
            FAIL() << __gtest_assert_eq_seq_fail_message(__lhs, __rhs).toString(false);  \
        }                                                                                \
    }


#define EXPECT_OUTCOME_OK(...)                                                           \
    BOOST_PP_OVERLOAD(EXPECT_OUTCOME_OK_, __VA_ARGS__)(__VA_ARGS__)

#define EXPECT_OUTCOME_OK_1(expr)                                                        \
    do {                                                                                 \
        auto _outcome_result = (expr);                                                   \
        EXPECT_TRUE(_outcome_result.has_value())                                         \
            << "Expected success, got failure: " << _outcome_result.error().message();   \
    } while (0)

#define EXPECT_OUTCOME_OK_2(expr, extra)                                                 \
    do {                                                                                 \
        auto _outcome_result = (expr);                                                   \
        EXPECT_TRUE(_outcome_result.has_value())                                         \
            << "Expected success, got failure: " << _outcome_result.error().message()    \
            << " " << (extra);                                                           \
    } while (0)

#define ASSERT_OUTCOME_OK(...)                                                           \
    BOOST_PP_OVERLOAD(ASSERT_OUTCOME_OK_, __VA_ARGS__)(__VA_ARGS__)

#define ASSERT_OUTCOME_OK_1(expr)                                                        \
    do {                                                                                 \
        auto _outcome_result = (expr);                                                   \
        ASSERT_TRUE(_outcome_result.has_value())                                         \
            << "Expected success, got failure: " << _outcome_result.error().message();   \
    } while (0)

#define ASSERT_OUTCOME_OK_2(expr, extra)                                                 \
    do {                                                                                 \
        auto _outcome_result = (expr);                                                   \
        ASSERT_TRUE(_outcome_result.has_value())                                         \
            << "Expected success, got failure: " << _outcome_result.error().message()    \
            << " " << (extra);                                                           \
    } while (0)


inline ::testing::AssertionResult TextContainsAll(
    std::string_view                        text,
    std::initializer_list<std::string_view> substrings) {
    for (std::string_view part : substrings) {
        if (text.find(part) == std::string_view::npos) {
            std::ostringstream out;
            out << "expected text to contain substring: \"" << part << "\"\n"
                << "text was:\n"
                << text;
            return ::testing::AssertionFailure() << out.str();
        }
    }

    return ::testing::AssertionSuccess();
}

#define EXPECT_TEXT_CONTAINS(text, ...)                                                  \
    EXPECT_TRUE(TextContainsAll((text), {__VA_ARGS__}))

template <typename E>
inline std::string_view ExceptionText(E const& ex) {
    if constexpr (requires { ex.message(); }) {
        return ex.message();
    } else {
        return ex.what();
    }
}

template <typename Exception, typename Fn>
inline ::testing::AssertionResult ThrowsWithTextContainsAll(
    Fn&&                                    fn,
    std::initializer_list<std::string_view> substrings) {
    try {
        std::forward<Fn>(fn)();
        return ::testing::AssertionFailure()
            << "expected exception of type " << typeid(Exception).name()
            << " but no exception was thrown";
    } catch (Exception const& ex) {
        return TextContainsAll(ExceptionText(ex), substrings);
    } catch (std::exception const& ex) {
        return ::testing::AssertionFailure()
            << "expected exception of type " << typeid(Exception).name()
            << " but got std::exception: " << ex.what();
    } catch (...) {
        return ::testing::AssertionFailure()
            << "expected exception of type " << typeid(Exception).name()
            << " but got a non-std exception";
    }
}

#define EXPECT_THROW_TEXT_CONTAINS(exception_type, expr, ...)                            \
    EXPECT_TRUE((ThrowsWithTextContainsAll<exception_type>(                              \
        [&]() { (void)(expr); }, {__VA_ARGS__})))


class LinePrinterLogSink : public absl::LogSink {
  public:
    LinePrinterLogSink(char const* path) : file(path) {}
    void Send(absl::LogEntry const& entry) override {
        for (absl::string_view line :
             absl::StrSplit(entry.text_message_with_prefix(), absl::ByChar('\n'))) {
            // Overprint severe entries for emphasis:
            for (int i = static_cast<int>(absl::LogSeverity::kInfo);
                 i <= static_cast<int>(entry.log_severity());
                 i++) {
                file << line << std::endl;
            }
        }
    }

  private:
    std::ofstream file;
};

class QuietTestPrinter : public ::testing::EmptyTestEventListener {
    // Called after a failed assertion or a SUCCESS().
    void OnTestPartResult(::testing::TestPartResult const& test_part_result) override {
        if (test_part_result.failed()) {
            std::cout << ::hstd::fmt(
                "{} in {}:{}\n{}\n",
                test_part_result.failed() ? "*** Failure" : "Success",
                test_part_result.file_name() ? test_part_result.file_name() : "<none>",
                test_part_result.line_number(),
                test_part_result.summary());
        }
    }
};


inline void init_gtest_tests(int& argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    std::vector<char*> new_argv;
    new_argv.push_back(argv[0]);

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--hax_vscode_run") {
            // Removes the default console output listener from the list so
            // it will not receive events from Google Test and won't print
            // any output.
            ::testing::TestEventListeners& listeners //
                = ::testing::UnitTest::GetInstance()->listeners();

            // Adds a listener to the end. Google Test takes the ownership.
            delete listeners.Release(listeners.default_result_printer());
            listeners.Append(new QuietTestPrinter());
        } else {
            new_argv.push_back(argv[i]);
        }
    }

    argc = static_cast<int>(new_argv.size());
    for (int i = 0; i < argc; ++i) { argv[i] = new_argv[i]; }
}
