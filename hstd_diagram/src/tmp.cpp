
#if ORG_BUILD_WITH_CGRAPH
#    include <graphviz/cgraph.h>
#    include <graphviz/gvc.h>
#endif


#include <hstd/ext/graph/visual/graph_graphviz.hpp>


hstd::SPtr<hstd::ext::graph::gv::GraphGroup> graphviz_processor::get_graphviz(
    hstd::SPtr<hstd::ext::graph::layout::LayoutRun> const& run) {
    using namespace hstd::ext;
    using namespace hstd::ext::graph;
    auto graph = gv::GraphGroup::newStandaloneRootGraph("g"_ss);
    std::unordered_map<std::string, hstd::SPtr<gv::NodeAttribute>> graph_nodes{};
    std::unordered_map<std::string, hstd::SPtr<gv::GraphGroup>>    clusters{};

    graph->defaultNode.setNodeShape(gv::NodeShape::rect);

    auto get_node = [&](hstd::SPtr<gv::GraphGroup> const& g, std::string const& name) {
        if (!graph_nodes.contains(name)) {
            graph_nodes.insert_or_assign(name, g->node(name));
        }
        return graph_nodes.at(name);
    };

    for (auto const& [name, info] : nodes) {
        if (info.is_cluster) {
            std::string cluster_name = fmt::format("cluster_{}", name);
            auto        cluster      = graph->newSubgraph(cluster_name);
            cluster->setLabel(name);
            clusters.insert_or_assign(name, cluster);

            auto node = get_node(cluster, name);

            for (auto const& sub : info.subnodes) { get_node(cluster, sub); }
        } else {
            get_node(graph, name);
        }
    }

    for (auto const& [edge_key, call] : edges) {
        int         pos  = edge_key.find(" -> ");
        std::string from = edge_key.substr(0, pos);
        std::string to   = edge_key.substr(pos + 4);

        auto from_node = graph_nodes.at(from);
        auto to_node   = graph_nodes.at(to);
        auto edge      = graph->edge(*from_node, *to_node);

        std::string label{};
        if (!call.jump_description.empty() && call.count > 1) {
            label = fmt::format("{} ({})", call.jump_description, call.count);
        } else if (!call.jump_description.empty()) {
            label = call.jump_description;
        } else if (call.count > 1) {
            label = fmt::format("({})", call.count);
        }

        if (!label.empty()) { edge->setLabel(label); }
    }

    return graph;
}

// hstd_cpp/hstd_lib/tests/tGraphTracker.cpp
{
    layout::LayoutRun::TrivialState state;
    auto                            run = state.init();

    hstd::fs::path path = getDebugFile("result.png");
    processor->get_graphviz(run)->render(path);
    std::ifstream file{path};
    EXPECT_TRUE(file.good());
}
{
    layout::LayoutRun::TrivialState state;
    auto                            run  = state.init();
    hstd::fs::path                  path = getDebugFile("result.dot");
    processor->get_graphviz(run)->render(
        path, gv::LayoutType::dot, gv::RenderFormat::DOT);
    std::ifstream file{path};
    EXPECT_TRUE(file.good());
}


// tGraphTracker.cpp


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
        if (rand() % 3 == 0) { throw std::runtime_error("random exception"); }

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

void h(std::shared_ptr<log_graph_tracker> tracker) { h_impl<int>(tracker); }
} // namespace real_usage_test_func

TEST(LogGraphTrackerManual, real_usage_test) {
    auto tracker   = std::make_shared<log_graph_tracker>();
    auto processor = std::make_shared<graphviz_processor>();
    tracker->add_processor(processor);
    tracker->start_tracing();
    real_usage_test_func::a<2>(tracker);
    tracker->end_tracing();

    layout::LayoutRun::TrivialState state{};
    auto                            run = state.init();
    processor->get_graphviz(run)->render(getDebugFile("result.png"));
}
