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

const std::string _cat = "cat";

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
        HSLOG_TRACE(_cat, "trace ", counter);
        HSLOG_DEBUG(_cat, "debug ", counter);
        HSLOG_INFO(_cat, "info ", counter);
        HSLOG_WARNING(_cat, "warning ", counter);
        HSLOG_ERROR(_cat, "error ", counter);
        HSLOG_ERROR(_cat, "fatal ", counter);
        ++counter;
    };

    run();
    run();
}
