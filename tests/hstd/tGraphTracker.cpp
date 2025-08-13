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
    { HSLOG_GRAPH_TRACK_FUNCTION(this->tracker, "test_macro_function"); }
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
        {

            hstd::fs::path path = getDebugFile("result.png");
            processor->get_graphviz().render(path);
            std::ifstream file{path};
            EXPECT_TRUE(file.good());
        }
        {
            hstd::fs::path path = getDebugFile("result.dot");
            processor->get_graphviz().render(
                path,
                hstd::ext::Graphviz::LayoutType::Dot,
                hstd::ext::Graphviz::RenderFormat::DOT);
            std::ifstream file{path};
            EXPECT_TRUE(file.good());
        }
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

namespace real_usage_test_func {


void b(std::shared_ptr<log_graph_tracker> tracker, int x);
void c(std::shared_ptr<log_graph_tracker> tracker);
void d(std::shared_ptr<log_graph_tracker> tracker);
void e(std::shared_ptr<log_graph_tracker> tracker);
void f(std::shared_ptr<log_graph_tracker> tracker);
void g(std::shared_ptr<log_graph_tracker> tracker);
void i(std::shared_ptr<log_graph_tracker> tracker);
void h(std::shared_ptr<log_graph_tracker> tracker);
void k(std::shared_ptr<log_graph_tracker> tracker);
void j(std::shared_ptr<log_graph_tracker> tracker);

template <int N>
void a(std::shared_ptr<log_graph_tracker> tracker);

template <>
void a<-1>(std::shared_ptr<log_graph_tracker> tracker) {}

template <>
void a<0>(std::shared_ptr<log_graph_tracker> tracker) {}

template <int N>
void a(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "a");
    if constexpr (N <= 0) { return; }

    tracker->notify_named_jump("template recursion");
    a<N - 1>(tracker);

    for (int i = 0; i < 2; ++i) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "loop-a");
        tracker->notify_named_jump("loop iteration");
        b(tracker, i);
    }

    tracker->notify_named_jump("calling c twice");
    c(tracker);
    c(tracker);
}

void b(std::shared_ptr<log_graph_tracker> tracker, int x) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "b");
    if (x == 0) {
        tracker->notify_named_jump("x is zero");
        return;
    }

    auto lambda = [tracker]() {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "lambda-in-b");
        d(tracker);
    };

    lambda();

    tracker->notify_named_jump("recursive call");
    b(tracker, x - 1);
}

void c(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "c");
    try {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "try-block");
        if (rand() % 3 == 0) {
            throw std::runtime_error("random exception");
        }

        tracker->notify_named_jump("no exception");
        e(tracker);
    } catch (...) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "catch-block");
        tracker->notify_named_jump("caught exception");
        f(tracker);
    }
}

void d(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "d");
    static int count = 0;
    count++;

    if (count > 3) {
        tracker->notify_named_jump("count limit reached");
        return;
    }

    {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "nested-scope-d");
        tracker->notify_named_jump("calling e from d");
        e(tracker);
    }

    tracker->notify_named_jump("calling f from d");
    f(tracker);
}

void e(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "e");
    for (int i = 0; i < 2; ++i) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "e-loop");
        if (i == 1) {
            tracker->notify_named_jump("second iteration calls g");
            g(tracker);
        }
    }

    auto nested_lambda = [tracker](int depth) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "nested-lambda");
        if (depth > 0) {
            tracker->notify_named_jump("lambda recursion");
            f(tracker);
        }
    };

    nested_lambda(1);
}

void f(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "f");
    static bool visited = false;

    if (!visited) {
        visited = true;
        tracker->notify_named_jump("first visit to f");
        g(tracker);
        g(tracker);
    }

    try {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "f-try-scope");
        if (rand() % 2 == 0) { throw std::logic_error("f exception"); }
        tracker->notify_named_jump("no f exception");
    } catch (std::logic_error&) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "f-catch-logic");
        tracker->notify_named_jump("caught logic error");
    } catch (...) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "f-catch-all");
        tracker->notify_named_jump("caught other error");
    }
}

void g(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "g");
    static int depth = 0;
    depth++;

    if (depth > 2) {
        depth--;
        tracker->notify_named_jump("depth limit in g");
        return;
    }

    {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "g-inner-scope");
        auto recursive_lambda = [tracker]() {
            HSLOG_GRAPH_TRACK_SCOPE(tracker, "recursive-lambda-g");
            tracker->notify_named_jump("lambda calls h");
            h(tracker);
        };
        recursive_lambda();
    }

    for (int i = 0; i < 3; ++i) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "g-loop");
        if (i == 2) {
            tracker->notify_named_jump("third iteration early exit");
            break;
        }
        tracker->notify_named_jump("g loop iteration");
        h(tracker);
    }

    depth--;
}

template <typename T>
void h_impl(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "h");
    static int calls = 0;
    calls++;

    if (calls > 5) {
        tracker->notify_named_jump("h call limit");
        return;
    }

    try {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "h-main-scope");
        if (calls % 2 == 0) {
            tracker->notify_named_jump("even call number");
            i(tracker);
        } else {
            tracker->notify_named_jump("odd call number");
            j(tracker);
        }
    } catch (...) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "h-exception-scope");
        tracker->notify_named_jump("h caught exception");
    }
}

void i(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "i");
    {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "i-scope-1");
        tracker->notify_named_jump("i calls j");
        j(tracker);
    }

    {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "i-scope-2");
        if (rand() % 4 == 0) { throw std::runtime_error("i exception"); }
        tracker->notify_named_jump("i calls k");
        k(tracker);
    }
}

void j(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "j");
    auto multi_lambda = [tracker](int x, int y) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "multi-param-lambda");
        if (x > y) {
            tracker->notify_named_jump("x greater than y");
            k(tracker);
        }
        return x + y;
    };

    multi_lambda(3, 1);
    multi_lambda(1, 3);

    for (int i = 0; i < 2; ++i) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "j-final-loop");
        tracker->notify_named_jump("j final iteration");
        k(tracker);
    }
}

void k(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_GRAPH_TRACK_FUNCTION(tracker, "k");
    static bool toggle = false;
    toggle             = !toggle;

    if (toggle) {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "k-toggle-true");
        tracker->notify_named_jump("toggle true path");
    } else {
        HSLOG_GRAPH_TRACK_SCOPE(tracker, "k-toggle-false");
        tracker->notify_named_jump("toggle false path");
    }
}

void h(std::shared_ptr<log_graph_tracker> tracker) {
    h_impl<int>(tracker);
}
} // namespace real_usage_test_func

TEST(graphviz_processor_test_manual, real_usage_test) {
    auto tracker   = std::make_shared<log_graph_tracker>();
    auto processor = std::make_shared<graphviz_processor>();
    tracker->add_processor(processor);
    tracker->start_tracing();
    real_usage_test_func::a<2>(tracker);
    tracker->end_tracing();
    processor->get_graphviz().render(getDebugFile("result.png"));
}
