#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <fstream>

#include "../common.hpp"

#include <hstd/ext/log_graph_tracker.hpp>

using namespace hstd::log;

using testing::_;

struct mock_log_graph_processor : public log_graph_processor {
    MOCK_METHOD(
        void,
        track_function_start,
        (std::string const& function_name,
         int                line,
         char const*        function,
         char const*        file),
        (override));
    MOCK_METHOD(
        void,
        track_function_end,
        (std::string const& function_name,
         int                line,
         char const*        function,
         char const*        file),
        (override));
    MOCK_METHOD(
        void,
        track_signal_emit,
        (std::string const&              signal_name,
         std::vector<std::string> const& args,
         int                             line,
         char const*                     function,
         char const*                     file),
        (override));
    MOCK_METHOD(
        void,
        track_slot_trigger,
        (std::string const&              slot_name,
         std::vector<std::string> const& args,
         int                             line,
         char const*                     function,
         char const*                     file),
        (override));
    MOCK_METHOD(
        void,
        track_scope_enter,
        (std::string const& scope_name,
         int                line,
         char const*        function,
         char const*        file),
        (override));
    MOCK_METHOD(
        void,
        track_scope_exit,
        (std::string const& scope_name,
         int                line,
         char const*        function,
         char const*        file),
        (override));
    MOCK_METHOD(
        void,
        track_started,
        (int line, char const* function, char const* file),
        (override));
    MOCK_METHOD(
        void,
        track_ended,
        (int line, char const* function, char const* file),
        (override));
    MOCK_METHOD(
        void,
        track_named_text,
        (std::string const& key,
         std::string const& value,
         int                line,
         char const*        function,
         char const*        file),
        (override));
    MOCK_METHOD(
        void,
        track_named_jump,
        (std::string const& description,
         int                line,
         char const*        function,
         char const*        file),
        (override));
};

struct log_graph_tracker_test : public ::testing::Test {
    std::shared_ptr<log_graph_tracker> tracker;
    void                               SetUp() override {
        tracker = std::make_shared<log_graph_tracker>();
        mock_processor = std::make_shared<
                                          ::testing::NiceMock<mock_log_graph_processor>>();
        tracker->add_processor(mock_processor);
    }

    void TearDown() override {
        try {
            tracker->end_tracing();
        } catch (...) {}
    }

    std::shared_ptr<::testing::NiceMock<mock_log_graph_processor>>
        mock_processor;
};


TEST_F(log_graph_tracker_test, start_tracing_calls_processors) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    tracker->start_tracing();
}

TEST_F(log_graph_tracker_test, end_tracing_calls_processors) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_ended(_, _, _)).Times(1);

    tracker->start_tracing();
    tracker->end_tracing();
}

TEST_F(log_graph_tracker_test, double_start_throws_exception) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);

    tracker->start_tracing();
    EXPECT_THROW(tracker->start_tracing(), std::runtime_error);
}

TEST_F(log_graph_tracker_test, double_end_throws_exception) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_ended(_, _, _)).Times(1);

    tracker->start_tracing();
    tracker->end_tracing();
    EXPECT_THROW(tracker->end_tracing(), std::runtime_error);
}

TEST_F(log_graph_tracker_test, end_without_start_throws_exception) {
    EXPECT_THROW(tracker->end_tracing(), std::runtime_error);
}

TEST_F(
    log_graph_tracker_test,
    function_tracking_when_not_started_ignored) {
    EXPECT_CALL(*mock_processor, track_function_start(_, _, _, _))
        .Times(0);
    EXPECT_CALL(*mock_processor, track_function_end(_, _, _, _)).Times(0);

    tracker->notify_function_start("test_function");
    tracker->notify_function_end("test_function");
}

TEST_F(log_graph_tracker_test, function_tracking_when_started) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(
        *mock_processor, track_function_start("test_function", _, _, _))
        .Times(1);
    EXPECT_CALL(
        *mock_processor, track_function_end("test_function", _, _, _))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_function_start("test_function");
    tracker->notify_function_end("test_function");
}

TEST_F(log_graph_tracker_test, signal_tracking_when_started) {
    std::vector<std::string> args{"arg1", "arg2"};

    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(
        *mock_processor, track_signal_emit("test_signal", args, _, _, _))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_signal_emit("test_signal", args);
}

TEST_F(log_graph_tracker_test, slot_tracking_when_started) {
    std::vector<std::string> args{"arg1", "arg2"};

    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(
        *mock_processor, track_slot_trigger("test_slot", args, _, _, _))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_slot_trigger("test_slot", args);
}

TEST_F(log_graph_tracker_test, scope_tracking_when_started) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_scope_enter("test_scope", _, _, _))
        .Times(1);
    EXPECT_CALL(*mock_processor, track_scope_exit("test_scope", _, _, _))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_scope_enter("test_scope");
    tracker->notify_scope_exit("test_scope");
}

TEST_F(log_graph_tracker_test, named_text_tracking_when_started) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_named_text("key", "value", _, _, _))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_named_text("key", "value");
}

TEST_F(log_graph_tracker_test, named_jump_tracking_when_started) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(
        *mock_processor, track_named_jump("jump_description", _, _, _))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_named_jump("jump_description");
}

TEST_F(log_graph_tracker_test, multiple_processors_all_called) {
    auto mock_processor2 = std::make_shared<mock_log_graph_processor>();
    tracker->add_processor(mock_processor2);

    EXPECT_CALL(*mock_processor2, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_function_start("test", _, _, _))
        .Times(1);
    EXPECT_CALL(*mock_processor2, track_function_start("test", _, _, _))
        .Times(1);
    EXPECT_CALL(*mock_processor2, track_ended(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_ended(_, _, _)).Times(1);

    tracker->start_tracing();
    tracker->notify_function_start("test");
}

TEST_F(log_graph_tracker_test, function_tracker_raii) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(
        *mock_processor, track_function_start("test_function", _, _, _))
        .Times(1);
    EXPECT_CALL(
        *mock_processor, track_function_end("test_function", _, _, _))
        .Times(1);

    tracker->start_tracing();
    { function_tracker tracker{this->tracker, "test_function"}; }
}

TEST_F(log_graph_tracker_test, scope_tracker_raii) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_scope_enter("test_scope", _, _, _))
        .Times(1);
    EXPECT_CALL(*mock_processor, track_scope_exit("test_scope", _, _, _))
        .Times(1);

    tracker->start_tracing();
    { scope_tracker tracker{this->tracker, "test_scope"}; }
}

TEST_F(log_graph_tracker_test, macro_function_tracking) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(
        *mock_processor,
        track_function_start("test_macro_function", _, _, _))
        .Times(1);
    EXPECT_CALL(
        *mock_processor,
        track_function_end("test_macro_function", _, _, _))
        .Times(1);

    tracker->start_tracing();
    { HSLOG_GRAPH_TRACK_FUNCTION(this->tracker, test_macro_function); }
}

TEST_F(log_graph_tracker_test, macro_scope_tracking) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(
        *mock_processor, track_scope_enter("test_macro_scope", _, _, _))
        .Times(1);
    EXPECT_CALL(
        *mock_processor, track_scope_exit("test_macro_scope", _, _, _))
        .Times(1);

    tracker->start_tracing();
    { HSLOG_GRAPH_TRACK_SCOPE(this->tracker, "test_macro_scope"); }
}

TEST_F(log_graph_tracker_test, concurrent_start_stop_throws) {
    std::vector<std::thread>        threads{};
    std::vector<std::exception_ptr> exceptions{};
    std::mutex                      exception_mutex{};

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&]() {
            try {
                tracker->start_tracing();
                std::this_thread::sleep_for(std::chrono::milliseconds{10});
                tracker->end_tracing();
            } catch (...) {
                std::lock_guard<std::mutex> lock{exception_mutex};
                exceptions.push_back(std::current_exception());
            }
        });
    }

    for (auto& thread : threads) { thread.join(); }

    EXPECT_EQ(exceptions.size(), 18);
}

TEST_F(log_graph_tracker_test, thread_safety_notifications) {
    EXPECT_CALL(*mock_processor, track_started(_, _, _)).Times(1);
    EXPECT_CALL(*mock_processor, track_function_start(_, _, _, _))
        .Times(testing::AtLeast(100));
    EXPECT_CALL(*mock_processor, track_function_end(_, _, _, _))
        .Times(testing::AtLeast(100));
    EXPECT_CALL(*mock_processor, track_ended(_, _, _)).Times(1);

    tracker->start_tracing();

    std::vector<std::thread> threads{};
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&, i]() {
            for (int j = 0; j < 10; ++j) {
                std::string func_name = std::format(
                    "function_{}_{}", i, j);
                tracker->notify_function_start(func_name);
                tracker->notify_function_end(func_name);
            }
        });
    }

    for (auto& thread : threads) { thread.join(); }

    tracker->end_tracing();
}

#define CALL_LOC() __LINE__, __func__, __FILE__

struct graphviz_processor_test : public ::testing::Test {
    void SetUp() override {
        processor = std::make_unique<graphviz_processor>();
        processor->track_started(__LINE__, __func__, __FILE__);
    }

    std::unique_ptr<graphviz_processor> processor;

    void finalize_files() {
        std::string path = getDebugFile("result.dot").native();
        processor->write_graphviz(path);
        std::ifstream file{path};
        EXPECT_TRUE(file.good());
    }
};

TEST_F(graphviz_processor_test, function_call_chain) {
    processor->track_function_start("main", CALL_LOC());
    processor->track_function_start("helper", CALL_LOC());
    processor->track_function_end("helper", CALL_LOC());
    processor->track_function_end("main", CALL_LOC());

    finalize_files();
}

TEST_F(graphviz_processor_test, signal_slot_tracking) {
    processor->track_signal_emit(
        "button_clicked", {"button1"}, CALL_LOC());
    processor->track_slot_trigger(
        "on_button_clicked", {"button1"}, CALL_LOC());
    processor->track_function_end("on_button_clicked", CALL_LOC());

    finalize_files();
}

TEST_F(graphviz_processor_test, named_jump_tracking) {
    processor->track_named_jump("condition met", CALL_LOC());
    processor->track_function_start("main", CALL_LOC());
    processor->track_function_start("conditional_function", CALL_LOC());
    processor->track_function_end("conditional_function", CALL_LOC());
    processor->track_function_end("main", CALL_LOC());

    finalize_files();
}

TEST_F(graphviz_processor_test, recursive_calls) {
    processor->track_function_start("recursive_func", CALL_LOC());
    processor->track_function_start("recursive_func", CALL_LOC());
    processor->track_function_end("recursive_func", CALL_LOC());
    processor->track_function_end("recursive_func", CALL_LOC());

    finalize_files();
}
