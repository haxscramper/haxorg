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

using p = log_graph_processor;

struct mock_log_graph_processor : public log_graph_processor {
    MOCK_METHOD(
        void,
        track_function_start,
        (function_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_function_end,
        (function_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_scope_enter,
        (scope_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_scope_exit,
        (scope_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_started,
        (tracked_info const& info),
        (override));
    MOCK_METHOD(void, track_ended, (tracked_info const& info), (override));
    MOCK_METHOD(
        void,
        track_named_text,
        (named_text_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_named_jump,
        (named_jump_info const& info),
        (override));

#if ORG_USE_QT
    MOCK_METHOD(
        void,
        track_qobject,
        (qobject_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_connect,
        (connect_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_signal_emit,
        (signal_emit_info const& info),
        (override));
    MOCK_METHOD(
        void,
        track_slot_trigger,
        (slot_trigger_info const& info),
        (override));
#endif
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

TEST_F(
    log_graph_tracker_test,
    function_tracking_when_not_started_ignored) {
    EXPECT_CALL(
        *mock_processor,
        track_function_start(
            testing::Field(&p::function_info::name, "test_scope")))
        .Times(0);
    EXPECT_CALL(
        *mock_processor,
        track_function_end(
            testing::Field(&p::function_info::name, "test_scope")))
        .Times(0);

    tracker->notify_function_start(
        p::function_info(
            "test_function", {}, p::callsite::this_callsite()));
    tracker->notify_function_end(
        p::function_info(
            "test_function", {}, p::callsite::this_callsite()));
}

TEST_F(log_graph_tracker_test, function_tracking_when_started) {
    EXPECT_CALL(*mock_processor, track_started(_)).Times(1);
    EXPECT_CALL(
        *mock_processor,
        track_function_start(
            testing::Field(&p::function_info::name, "test_function")))
        .Times(1);
    EXPECT_CALL(
        *mock_processor,
        track_function_end(
            testing::Field(&p::function_info::name, "test_function")))
        .Times(1);

    tracker->start_tracing();
    tracker->notify_function_start(
        p::function_info(
            "test_function", {}, p::callsite::this_callsite()));
    tracker->notify_function_end(
        p::function_info(
            "test_function", {}, p::callsite::this_callsite()));
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
        p::function_info(
            "conditional_function", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info(
            "conditional_function", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info("main", {}, p::callsite::this_callsite()));

    finalize_files();
}

TEST_F(LogGraphTracker, recursive_calls) {
    processor->track_function_start(
        p::function_info(
            "recursive_func", {}, p::callsite::this_callsite()));
    processor->track_function_start(
        p::function_info(
            "recursive_func", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info(
            "recursive_func", {}, p::callsite::this_callsite()));
    processor->track_function_end(
        p::function_info(
            "recursive_func", {}, p::callsite::this_callsite()));

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
    HSLOG_TRACKED_FUNCTION(tracker, "a");
    if constexpr (N <= 0) { return; }

    HSLOG_TRACKED_JUMP(tracker, "template recursion");
    a<N - 1>(tracker);

    for (int i = 0; i < 2; ++i) {
        HSLOG_TRACKED_SCOPE(tracker, "loop-a");
        HSLOG_TRACKED_JUMP(tracker, "loop iteration");
        b(tracker, i);
    }

    HSLOG_TRACKED_JUMP(tracker, "calling c twice");
    c(tracker);
    c(tracker);
}

void b(std::shared_ptr<log_graph_tracker> tracker, int x) {
    HSLOG_TRACKED_FUNCTION(tracker, "b");
    if (x == 0) {
        HSLOG_TRACKED_JUMP(tracker, "x is zero");
        return;
    }

    auto lambda = [tracker]() {
        HSLOG_TRACKED_SCOPE(tracker, "lambda-in-b");
        d(tracker);
    };

    lambda();

    HSLOG_TRACKED_JUMP(tracker, "recursive call");
    b(tracker, x - 1);
}

void c(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "c");
    try {
        HSLOG_TRACKED_SCOPE(tracker, "try-block");
        if (rand() % 3 == 0) {
            throw std::runtime_error("random exception");
        }

        HSLOG_TRACKED_JUMP(tracker, "no exception");
        e(tracker);
    } catch (...) {
        HSLOG_TRACKED_SCOPE(tracker, "catch-block");
        HSLOG_TRACKED_JUMP(tracker, "caught exception");
        f(tracker);
    }
}

void d(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "d");
    static int count = 0;
    count++;

    if (count > 3) {
        HSLOG_TRACKED_JUMP(tracker, "count limit reached");
        return;
    }

    {
        HSLOG_TRACKED_SCOPE(tracker, "nested-scope-d");
        HSLOG_TRACKED_JUMP(tracker, "calling e from d");
        e(tracker);
    }

    HSLOG_TRACKED_JUMP(tracker, "calling f from d");
    f(tracker);
}

void e(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "e");
    for (int i = 0; i < 2; ++i) {
        HSLOG_TRACKED_SCOPE(tracker, "e-loop");
        if (i == 1) {
            HSLOG_TRACKED_JUMP(tracker, "second iteration calls g");
            g(tracker);
        }
    }

    auto nested_lambda = [tracker](int depth) {
        HSLOG_TRACKED_SCOPE(tracker, "nested-lambda");
        if (depth > 0) {
            HSLOG_TRACKED_JUMP(tracker, "lambda recursion");
            f(tracker);
        }
    };

    nested_lambda(1);
}

void f(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "f");
    static bool visited = false;

    if (!visited) {
        visited = true;
        HSLOG_TRACKED_JUMP(tracker, "first visit to f");
        g(tracker);
        g(tracker);
    }

    try {
        HSLOG_TRACKED_SCOPE(tracker, "f-try-scope");
        if (rand() % 2 == 0) { throw std::logic_error("f exception"); }
        HSLOG_TRACKED_JUMP(tracker, "no f exception");
    } catch (std::logic_error&) {
        HSLOG_TRACKED_SCOPE(tracker, "f-catch-logic");
        HSLOG_TRACKED_JUMP(tracker, "caught logic error");
    } catch (...) {
        HSLOG_TRACKED_SCOPE(tracker, "f-catch-all");
        HSLOG_TRACKED_JUMP(tracker, "caught other error");
    }
}

void g(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "g");
    static int depth = 0;
    depth++;

    if (depth > 2) {
        depth--;
        HSLOG_TRACKED_JUMP(tracker, "depth limit in g");
        return;
    }

    {
        HSLOG_TRACKED_SCOPE(tracker, "g-inner-scope");
        auto recursive_lambda = [tracker]() {
            HSLOG_TRACKED_SCOPE(tracker, "recursive-lambda-g");
            HSLOG_TRACKED_JUMP(tracker, "lambda calls h");
            h(tracker);
        };
        recursive_lambda();
    }

    for (int i = 0; i < 3; ++i) {
        HSLOG_TRACKED_SCOPE(tracker, "g-loop");
        if (i == 2) {
            HSLOG_TRACKED_JUMP(tracker, "third iteration early exit");
            break;
        }
        HSLOG_TRACKED_JUMP(tracker, "g loop iteration");
        h(tracker);
    }

    depth--;
}

template <typename T>
void h_impl(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "h");
    static int calls = 0;
    calls++;

    if (calls > 5) {
        HSLOG_TRACKED_JUMP(tracker, "h call limit");
        return;
    }

    try {
        HSLOG_TRACKED_SCOPE(tracker, "h-main-scope");
        if (calls % 2 == 0) {
            HSLOG_TRACKED_JUMP(tracker, "even call number");
            i(tracker);
        } else {
            HSLOG_TRACKED_JUMP(tracker, "odd call number");
            j(tracker);
        }
    } catch (...) {
        HSLOG_TRACKED_SCOPE(tracker, "h-exception-scope");
        HSLOG_TRACKED_JUMP(tracker, "h caught exception");
    }
}

void i(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "i");
    {
        HSLOG_TRACKED_SCOPE(tracker, "i-scope-1");
        HSLOG_TRACKED_JUMP(tracker, "i calls j");
        j(tracker);
    }

    {
        HSLOG_TRACKED_SCOPE(tracker, "i-scope-2");
        if (rand() % 4 == 0) { throw std::runtime_error("i exception"); }
        HSLOG_TRACKED_JUMP(tracker, "i calls k");
        k(tracker);
    }
}

void j(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "j");
    auto multi_lambda = [tracker](int x, int y) {
        HSLOG_TRACKED_SCOPE(tracker, "multi-param-lambda");
        if (x > y) {
            HSLOG_TRACKED_JUMP(tracker, "x greater than y");
            k(tracker);
        }
        return x + y;
    };

    multi_lambda(3, 1);
    multi_lambda(1, 3);

    for (int i = 0; i < 2; ++i) {
        HSLOG_TRACKED_SCOPE(tracker, "j-final-loop");
        HSLOG_TRACKED_JUMP(tracker, "j final iteration");
        k(tracker);
    }
}

void k(std::shared_ptr<log_graph_tracker> tracker) {
    HSLOG_TRACKED_FUNCTION(tracker, "k");
    static bool toggle = false;
    toggle             = !toggle;

    if (toggle) {
        HSLOG_TRACKED_SCOPE(tracker, "k-toggle-true");
        HSLOG_TRACKED_JUMP(tracker, "toggle true path");
    } else {
        HSLOG_TRACKED_SCOPE(tracker, "k-toggle-false");
        HSLOG_TRACKED_JUMP(tracker, "toggle false path");
    }
}

void h(std::shared_ptr<log_graph_tracker> tracker) {
    h_impl<int>(tracker);
}
} // namespace real_usage_test_func

TEST(LogGraphTrackerManual, real_usage_test) {
    auto tracker   = std::make_shared<log_graph_tracker>();
    auto processor = std::make_shared<graphviz_processor>();
    tracker->add_processor(processor);
    tracker->start_tracing();
    real_usage_test_func::a<2>(tracker);
    tracker->end_tracing();
    processor->get_graphviz().render(getDebugFile("result.png"));
}
