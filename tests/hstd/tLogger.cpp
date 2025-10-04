#include <gtest/gtest.h>
#include <hstd/ext/logger.hpp>

#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "../common.hpp"

using namespace hstd;

class buffer_sink
    : public boost::log::sinks::basic_sink_backend<
          boost::log::sinks::combine_requirements<
              boost::log::sinks::synchronized_feeding,
              boost::log::sinks::flushing>::type> {
  public:
    buffer_sink(std::vector<log::log_record>* buffer) : buffer(buffer) {}

    void consume(boost::log::record_view const& rec) {
        if (buffer && rec[HSLOG_RECORD_FIELD]) {
            auto ref = rec[HSLOG_RECORD_FIELD].extract<log::log_record>();
            if (ref) { buffer->push_back(ref.get()); }
        }
    }

    void flush() {}

  private:
    std::vector<log::log_record>* buffer;
};

log::sink_ptr init_buffer_sink(Vec<log::log_record>* buffer) {
    auto backend = boost::make_shared<buffer_sink>(buffer);
    auto sink    = boost::make_shared<
           boost::log::sinks::synchronous_sink<buffer_sink>>(backend);
    return sink;
}

struct LoggerTest : public ::testing::Test {
    Vec<log::log_record> buffer;
    log::log_sink_scope  scope;
    LoggerTest() {
        scope = HSLOG_SINK_FACTORY_SCOPED(
            [&]() { return init_buffer_sink(&buffer); });
    }

    void debug() {
        for (auto const& it : buffer) {
            std::cout << fmt1(it) << std::endl;
        }
    }
};

const hstd::log::log_category _cat = hstd::log::log_category{"cat"};

TEST_F(LoggerTest, SimpleLog) {
    HSLOG_TRACE(_cat, "trace");
    HSLOG_DEBUG(_cat, "debug");
    HSLOG_INFO(_cat, "info");
    HSLOG_WARNING(_cat, "warning");
    HSLOG_ERROR(_cat, "error");
    HSLOG_ERROR(_cat, "fatal");

    // debug();
    auto const& b = buffer;
    EXPECT_EQ(b.at(0).data.severity, log::l_trace);
    EXPECT_EQ(b.at(1).data.severity, log::l_debug);
    EXPECT_EQ(b.size(), 6);
}

TEST_F(LoggerTest, DifferentialDebug) {
    int  counter = 0;
    auto run     = [&]() {
        auto __log_diff = HSLOG_SINK_FACTORY_SCOPED(
            log::log_differential_sink_factory{getDebugFile("res.diff")});
        HSLOG_TRACE(_cat, "trace {}", counter);
        HSLOG_DEBUG(_cat, "debug {}", counter);
        HSLOG_INFO(_cat, "info {}", counter);
        HSLOG_WARNING(_cat, "warning {}", counter);
        HSLOG_ERROR(_cat, "error {}", counter);
        HSLOG_ERROR(_cat, "fatal {}", counter);
        ++counter;
    };

    run();
    run();
}

struct UnformattableType {
    int value;
};

struct StdFormattableType {
    int value;
};

template <>
struct std::formatter<StdFormattableType> : std::formatter<std::string> {
    auto format(const StdFormattableType& obj, format_context& ctx) const {
        return std::formatter<std::string>::format(
            "std_fmt:" + std::to_string(obj.value), ctx);
    }
};

struct LogFormattableType {
    int value;
};

namespace hstd::log {
template <>
struct log_value_formatter<LogFormattableType> {
    std::string format(const LogFormattableType& value) {
        return "log_fmt:" + std::to_string(value.value);
    }
};
} // namespace hstd::log

struct BothFormattableType {
    int value;
};

template <>
struct std::formatter<BothFormattableType> : std::formatter<std::string> {
    auto format(const BothFormattableType& obj, format_context& ctx)
        const {
        return std::formatter<std::string>::format(
            "std_both:" + std::to_string(obj.value), ctx);
    }
};

namespace hstd::log {
template <>
struct log_value_formatter<BothFormattableType> {
    std::string format(const BothFormattableType& value) {
        return "log_both:" + std::to_string(value.value);
    }
};
} // namespace hstd::log


TEST_F(LoggerTest, LogStringFormatting) {
    EXPECT_EQ(
        hstd::log::format_logger_arguments("Value: {}", 42), "Value: 42");

    static_assert(hstd::StdFormattable<StdFormattableType>);
    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "Value: {}", StdFormattableType{123}),
        "Value: std_fmt:123");


    static_assert(hstd::log::has_log_value_formatter<LogFormattableType>);
    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "Value: {}", LogFormattableType{456}),
        "Value: log_fmt:456");

    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "Value: {}", BothFormattableType{789}),
        "Value: log_both:789");

    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "Value: {}", UnformattableType{999}),
        "Value: <type unformattable>");

    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "Multiple: {} and {}", 10, LogFormattableType{20}),
        "Multiple: 10 and log_fmt:20");
}

TEST_F(LoggerTest, StdFormatterSpecifications) {
    EXPECT_EQ(
        hstd::log::format_logger_arguments("Hex: {:X}", 255), "Hex: FF");

    EXPECT_EQ(
        hstd::log::format_logger_arguments("Padded: {:05d}", 42),
        "Padded: 00042");

    EXPECT_EQ(
        hstd::log::format_logger_arguments("Float: {:.2f}", 3.14159),
        "Float: 3.14");

    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "String: {:>10}", std::string{"test"}),
        "String:       test");

    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "Mixed: {:X} and {:.1f}", 16, 2.718),
        "Mixed: 10 and 2.7");

    EXPECT_EQ(
        hstd::log::format_logger_arguments(
            "Custom with spec: {:>15}", StdFormattableType{100}),
        "Custom with spec:     std_fmt:100");
}
