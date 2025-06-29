#include <benchmark/benchmark.h>
#include <vector>
#include <immer/flex_vector.hpp>
#include <immer/vector.hpp>
#include <boost/container/small_vector.hpp>
#include <hstd/stdlib/RecursivePathTracker.hpp>
#pragma clang diagnostic ignored "-Wclang-analyzer-deadcode.DeadStores"

using namespace hstd;

template <typename Container>
struct VectorPathTracker {
    Container path;

    VectorPathTracker() = default;
    VectorPathTracker(const Container& p) : path{p} {}

    VectorPathTracker push(int value) const {
        Container new_path = path;
        new_path.push_back(value);
        return VectorPathTracker{new_path};
    }

    size_t size() const { return path.size(); }
    bool   empty() const { return path.empty(); }
    int    operator[](size_t index) const { return path[index]; }
    int    back() const { return path.back(); }
};

template <>
struct VectorPathTracker<immer::flex_vector<int>> {
    immer::flex_vector<int> path;

    VectorPathTracker() = default;
    VectorPathTracker(const immer::flex_vector<int>& p) : path{p} {}

    VectorPathTracker push(int value) const {
        return VectorPathTracker{path.push_back(value)};
    }

    size_t size() const { return path.size(); }
    bool   empty() const { return path.empty(); }
    int    operator[](size_t index) const { return path[index]; }
    int    back() const { return path.back(); }
};

template <>
struct VectorPathTracker<immer::vector<int>> {
    immer::vector<int> path;

    VectorPathTracker() = default;
    VectorPathTracker(const immer::vector<int>& p) : path{p} {}

    VectorPathTracker push(int value) const {
        return VectorPathTracker{path.push_back(value)};
    }

    size_t size() const { return path.size(); }
    bool   empty() const { return path.empty(); }
    int    operator[](size_t index) const { return path[index]; }
    int    back() const { return path.back(); }
};

template <typename PathTracker>
void recursiveTraversal(
    PathTracker path,
    int         depth,
    int         max_depth,
    int         branching_factor,
    int&        node_count) {
    node_count++;

    if (depth >= max_depth) { return; }

    for (int i = 0; i < branching_factor; ++i) {
        auto new_path = path.push(i);
        recursiveTraversal(
            new_path, depth + 1, max_depth, branching_factor, node_count);
    }
}

template <typename PathTracker>
void pathCopyingWorkload(
    PathTracker path,
    int         operations,
    int&        access_sum) {
    for (int i = 0; i < operations; ++i) {
        auto new_path = path.push(i);

        for (int j = 0; j < 5; ++j) {
            auto copied_path  = new_path;
            auto another_copy = copied_path.push(j + 100);

            if (!another_copy.empty()) {
                access_sum += another_copy.back();
            }
        }
    }
}

template <typename PathTracker>
void randomAccessWorkload(
    PathTracker path,
    int         path_length,
    int         access_count,
    int&        access_sum) {
    for (int i = 0; i < path_length; ++i) { path = path.push(i); }

    for (int i = 0; i < access_count; ++i) {
        size_t index = i % path_length;
        access_sum += path[index];
    }
}

static void BM_RecursiveTraversal_StdVector(benchmark::State& state) {
    int max_depth        = state.range(0);
    int branching_factor = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<std::vector<int>> initial_path;
        int                                 node_count = 0;
        recursiveTraversal(
            initial_path, 0, max_depth, branching_factor, node_count);
        benchmark::DoNotOptimize(node_count);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["depth"]     = state.range(0);
    state.counters["branching"] = state.range(1);
}

static void BM_RecursiveTraversal_ImmerFlex(benchmark::State& state) {
    int max_depth        = state.range(0);
    int branching_factor = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<immer::flex_vector<int>> initial_path;
        int                                        node_count = 0;
        recursiveTraversal(
            initial_path, 0, max_depth, branching_factor, node_count);
        benchmark::DoNotOptimize(node_count);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["depth"]     = state.range(0);
    state.counters["branching"] = state.range(1);
}

static void BM_RecursiveTraversal_ImmerVector(benchmark::State& state) {
    int max_depth        = state.range(0);
    int branching_factor = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<immer::vector<int>> initial_path;
        int                                   node_count = 0;
        recursiveTraversal(
            initial_path, 0, max_depth, branching_factor, node_count);
        benchmark::DoNotOptimize(node_count);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["depth"]     = state.range(0);
    state.counters["branching"] = state.range(1);
}

static void BM_RecursiveTraversal_RecursivePathTracker(
    benchmark::State& state) {
    int max_depth        = state.range(0);
    int branching_factor = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        RecursivePathTracker<int> initial_path;
        int                       node_count = 0;
        recursiveTraversal(
            initial_path, 0, max_depth, branching_factor, node_count);
        benchmark::DoNotOptimize(node_count);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["depth"]     = state.range(0);
    state.counters["branching"] = state.range(1);
}

static void BM_PathCopying_StdVector(benchmark::State& state) {
    int base_path_length = state.range(0);
    int operations       = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<std::vector<int>> base_path;
        for (int i = 0; i < base_path_length; ++i) {
            base_path = base_path.push(i);
        }

        int access_sum = 0;
        pathCopyingWorkload(base_path, operations, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["base_length"] = state.range(0);
    state.counters["operations"]  = state.range(1);
}

static void BM_PathCopying_ImmerFlex(benchmark::State& state) {
    int base_path_length = state.range(0);
    int operations       = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<immer::flex_vector<int>> base_path;
        for (int i = 0; i < base_path_length; ++i) {
            base_path = base_path.push(i);
        }

        int access_sum = 0;
        pathCopyingWorkload(base_path, operations, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["base_length"] = state.range(0);
    state.counters["operations"]  = state.range(1);
}

static void BM_PathCopying_ImmerVector(benchmark::State& state) {
    int base_path_length = state.range(0);
    int operations       = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<immer::vector<int>> base_path;
        for (int i = 0; i < base_path_length; ++i) {
            base_path = base_path.push(i);
        }

        int access_sum = 0;
        pathCopyingWorkload(base_path, operations, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["base_length"] = state.range(0);
    state.counters["operations"]  = state.range(1);
}

static void BM_PathCopying_RecursivePathTracker(benchmark::State& state) {
    int base_path_length = state.range(0);
    int operations       = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        RecursivePathTracker<int> base_path;
        for (int i = 0; i < base_path_length; ++i) {
            base_path = base_path.push(i);
        }

        int access_sum = 0;
        pathCopyingWorkload(base_path, operations, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["base_length"] = state.range(0);
    state.counters["operations"]  = state.range(1);
}

static void BM_RandomAccess_StdVector(benchmark::State& state) {
    int path_length  = state.range(0);
    int access_count = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<std::vector<int>> path;
        int                                 access_sum = 0;
        randomAccessWorkload(path, path_length, access_count, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["path_length"]  = state.range(0);
    state.counters["access_count"] = state.range(1);
}

static void BM_RandomAccess_ImmerFlex(benchmark::State& state) {
    int path_length  = state.range(0);
    int access_count = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<immer::flex_vector<int>> path;
        int                                        access_sum = 0;
        randomAccessWorkload(path, path_length, access_count, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["path_length"]  = state.range(0);
    state.counters["access_count"] = state.range(1);
}

static void BM_RandomAccess_ImmerVector(benchmark::State& state) {
    int path_length  = state.range(0);
    int access_count = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        VectorPathTracker<immer::vector<int>> path;
        int                                   access_sum = 0;
        randomAccessWorkload(path, path_length, access_count, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["path_length"]  = state.range(0);
    state.counters["access_count"] = state.range(1);
}

static void BM_RandomAccess_RecursivePathTracker(benchmark::State& state) {
    int path_length  = state.range(0);
    int access_count = state.range(1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
        RecursivePathTracker<int> path;
        int                       access_sum = 0;
        randomAccessWorkload(path, path_length, access_count, access_sum);
        benchmark::DoNotOptimize(access_sum);
    }

    state.SetComplexityN(state.range(0) * state.range(1));
    state.counters["path_length"]  = state.range(0);
    state.counters["access_count"] = state.range(1);
}

static void CustomArguments(benchmark::internal::Benchmark* b) {
    for (int depth = 2; depth <= 8; depth += 2) {
        if (depth < 5) {
            for (int width = 2; width <= 20; ++width) {
                b->Args({depth, width});
            }
        } else {
            for (int width = 2; width <= 4; ++width) {
                b->Args({depth, width});
            }
        }
    }
}

BENCHMARK(BM_RecursiveTraversal_StdVector)
    ->Apply(CustomArguments)
    ->Complexity()
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_RecursiveTraversal_ImmerFlex)
    ->Apply(CustomArguments)
    ->Complexity()
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_RecursiveTraversal_ImmerVector)
    ->Apply(CustomArguments)
    ->Complexity()
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_RecursiveTraversal_RecursivePathTracker)
    ->Apply(CustomArguments)
    ->Complexity()
    ->Unit(benchmark::kMillisecond);

static void PathLengthArguments(benchmark::internal::Benchmark* b) {
    for (int length : {10, 25, 50, 100, 250, 500}) {
        for (int ops : {50, 100, 200, 500}) { b->Args({length, ops}); }
    }
}

BENCHMARK(BM_PathCopying_StdVector)
    ->Apply(PathLengthArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_PathCopying_ImmerFlex)
    ->Apply(PathLengthArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_PathCopying_ImmerVector)
    ->Apply(PathLengthArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_PathCopying_RecursivePathTracker)
    ->Apply(PathLengthArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);

static void AccessPatternArguments(benchmark::internal::Benchmark* b) {
    for (int length : {50, 100, 500, 1000, 2000}) {
        for (int accesses : {1000, 5000, 10000}) {
            b->Args({length, accesses});
        }
    }
}

BENCHMARK(BM_RandomAccess_StdVector)
    ->Apply(AccessPatternArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_RandomAccess_ImmerFlex)
    ->Apply(AccessPatternArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_RandomAccess_ImmerVector)
    ->Apply(AccessPatternArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_RandomAccess_RecursivePathTracker)
    ->Apply(AccessPatternArguments)
    ->Complexity()
    ->Unit(benchmark::kMicrosecond);
