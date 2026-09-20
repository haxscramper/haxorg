#include <chrono>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include <vector>

#include <hstd/extra/error_format/gtest_utils.hpp>

#include <hstd/logger/log_graph_tracker.hpp>

using namespace hstd::log;

using testing::_;

using p = log_graph_processor;

struct mock_log_graph_processor : public log_graph_processor {
    MOCK_METHOD(void, track_function_start, (function_info const& info), (override));
    MOCK_METHOD(void, track_function_end, (function_info const& info), (override));
    MOCK_METHOD(void, track_scope_enter, (scope_info const& info), (override));
    MOCK_METHOD(void, track_scope_exit, (scope_info const& info), (override));
    MOCK_METHOD(void, track_started, (tracked_info const& info), (override));
    MOCK_METHOD(void, track_ended, (tracked_info const& info), (override));
    MOCK_METHOD(void, track_named_text, (named_text_info const& info), (override));
    MOCK_METHOD(void, track_named_jump, (named_jump_info const& info), (override));

#if ORG_BUILD_WITH_QT
    MOCK_METHOD(void, track_qobject, (qobject_info const& info), (override));
    MOCK_METHOD(void, track_connect, (connect_info const& info), (override));
    MOCK_METHOD(void, track_signal_emit, (signal_emit_info const& info), (override));
    MOCK_METHOD(void, track_slot_trigger, (slot_trigger_info const& info), (override));
#endif
};

struct log_graph_tracker_test : public ::testing::Test {
    std::shared_ptr<log_graph_tracker> tracker;
    void                               SetUp() override {
        tracker        = std::make_shared<log_graph_tracker>();
        mock_processor = std::make_shared<
            ::testing::NiceMock<mock_log_graph_processor>>();
        tracker->add_processor(mock_processor);
    }

    void TearDown() override {
        try {
            tracker->end_tracing();
        } catch (...) {}
    }

    std::shared_ptr<::testing::NiceMock<mock_log_graph_processor>> mock_processor;
};


TEST_F(log_graph_tracker_test, start_tracing_calls_processors) {
    EXPECT_CALL(*mock_processor, track_started(_)).Times(1);
    tracker->start_tracing();
}

TEST_F(log_graph_tracker_test, end_tracing_calls_processors) {
    EXPECT_CALL(*mock_processor, track_started(_)).Times(1);
    EXPECT_CALL(*mock_processor, track_ended(_)).Times(1);

    tracker->start_tracing();
    tracker->end_tracing();
}

TEST_F(log_graph_tracker_test, double_start_throws_exception) {
    EXPECT_CALL(*mock_processor, track_started(_)).Times(1);

    tracker->start_tracing();
    EXPECT_THROW(tracker->start_tracing(), std::runtime_error);
}

TEST_F(log_graph_tracker_test, double_end_throws_exception) {
    EXPECT_CALL(*mock_processor, track_started(_)).Times(1);
    EXPECT_CALL(*mock_processor, track_ended(_)).Times(1);

    tracker->start_tracing();
    tracker->end_tracing();
    EXPECT_THROW(tracker->end_tracing(), std::runtime_error);
}

TEST_F(log_graph_tracker_test, end_without_start_throws_exception) {
    EXPECT_THROW(tracker->end_tracing(), std::runtime_error);
}

TEST_F(log_graph_tracker_test, function_tracking_when_not_started_ignored) {
    EXPECT_CALL(
        *mock_processor,
        track_function_start(testing::Field(&p::function_info::name, "test_scope")))
        .Times(0);
    EXPECT_CALL(
        *mock_processor,
        track_function_end(testing::Field(&p::function_info::name, "test_scope")))
        .Times(0);

    tracker->notify_function_start(
        p::function_info("test_function", {}, p::callsite::this_callsite()));
    tracker->notify_function_end(
        p::function_info("test_function", {}, p::callsite::this_callsite()));
}

TEST_F(log_graph_tracker_test, function_tracking_when_started) {
    EXPECT_CALL(*mock_processor, track_started(_)).Times(1);
    EXPECT_CALL(
        *mock_processor,
        track_function_start(testing::Field(&p::function_info::name, "test_function")))
        .Times(1);
    EXPECT_CALL(
        *mock_processor,
        track_function_end(testing::Field(&p::function_info::name, "test_function")))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_function_start(
        p::function_info("test_function", {}, p::callsite::this_callsite()));
    tracker->notify_function_end(
        p::function_info("test_function", {}, p::callsite::this_callsite()));
}


TEST_F(log_graph_tracker_test, multiple_processors_all_called) {
    auto mock_processor2 = std::make_shared<mock_log_graph_processor>();
    tracker->add_processor(mock_processor2);

    EXPECT_CALL(*mock_processor2, track_started(_)).Times(1);
    EXPECT_CALL(*mock_processor, track_started(_)).Times(1);
    EXPECT_CALL(*mock_processor, track_function_start(_)).Times(1);
    EXPECT_CALL(*mock_processor2, track_function_start(_)).Times(1);
    EXPECT_CALL(*mock_processor2, track_ended(_)).Times(1);
    EXPECT_CALL(*mock_processor, track_ended(_)).Times(1);

    tracker->start_tracing();
    tracker->notify_function_start(
        p::function_info("test", {}, p::callsite::this_callsite()));
}


struct LogGraphTracker : public ::testing::Test {
    void SetUp() override {
        processor = std::make_unique<graphviz_processor>();
        processor->track_started(p::callsite::this_callsite());
    }

    std::unique_ptr<graphviz_processor> processor;

    void finalize_files() {}
};

TEST_F(LogGraphTracker, function_call_chain) {
    processor->track_function_start(
        p::function_info("main", {}, p::callsite::this_callsite()));
    processor->track_function_start(
        p::function_info("helper", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info("helper", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info("main", {}, p::callsite::this_callsite()));

    finalize_files();
}


TEST_F(LogGraphTracker, named_jump_tracking) {
    processor->track_named_jump(
        p::named_jump_info("condition met", p::callsite::this_callsite()));
    processor->track_function_start(
        p::function_info("main", {}, p::callsite::this_callsite()));
    processor->track_function_start(
        p::function_info("conditional_function", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info("conditional_function", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info("main", {}, p::callsite::this_callsite()));

    finalize_files();
}

TEST_F(LogGraphTracker, recursive_calls) {
    processor->track_function_start(
        p::function_info("recursive_func", {}, p::callsite::this_callsite()));
    processor->track_function_start(
        p::function_info("recursive_func", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info("recursive_func", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info("recursive_func", {}, p::callsite::this_callsite()));

    finalize_files();
}
