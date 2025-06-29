#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <hstd/stdlib/RecursivePathTracker.hpp>

using namespace hstd;

struct TestStep {
    int         value;
    std::string name;

    TestStep(int v, const std::string& n = "") : value{v}, name{n} {}

    bool operator==(const TestStep& other) const {
        return value == other.value && name == other.name;
    }
};

class RecursivePathTrackerTest : public ::testing::Test {
  protected:
    RecursivePathTracker<TestStep>    empty_tracker;
    RecursivePathTracker<int>         int_tracker;
    RecursivePathTracker<std::string> string_tracker;
};

TEST_F(RecursivePathTrackerTest, DefaultConstruction) {
    EXPECT_TRUE(empty_tracker.empty());
    EXPECT_EQ(empty_tracker.size(), 0);
}

TEST_F(RecursivePathTrackerTest, PushSingleElement) {
    auto tracker = empty_tracker.push(TestStep{42, "test"});

    EXPECT_FALSE(tracker.empty());
    EXPECT_EQ(tracker.size(), 1);
    EXPECT_EQ(tracker.back().value, 42);
    EXPECT_EQ(tracker.back().name, "test");
}

TEST_F(RecursivePathTrackerTest, PushMultipleElements) {
    auto tracker = empty_tracker.push(TestStep{1, "first"})
                       .push(TestStep{2, "second"})
                       .push(TestStep{3, "third"});

    EXPECT_EQ(tracker.size(), 3);
    EXPECT_EQ(tracker[0].value, 1);
    EXPECT_EQ(tracker[1].value, 2);
    EXPECT_EQ(tracker[2].value, 3);
    EXPECT_EQ(tracker.back().value, 3);
}

TEST_F(RecursivePathTrackerTest, PopElements) {
    auto tracker = empty_tracker.push(TestStep{1})
                       .push(TestStep{2})
                       .push(TestStep{3});

    auto popped = tracker.pop();
    EXPECT_EQ(popped.size(), 2);
    EXPECT_EQ(popped.back().value, 2);

    auto double_popped = popped.pop();
    EXPECT_EQ(double_popped.size(), 1);
    EXPECT_EQ(double_popped.back().value, 1);

    auto empty = double_popped.pop();
    EXPECT_TRUE(empty.empty());
}

TEST_F(RecursivePathTrackerTest, CopySemantics) {
    auto original = empty_tracker.push(TestStep{1, "a"})
                        .push(TestStep{2, "b"});

    auto copy          = original;
    auto modified_copy = copy.push(TestStep{3, "c"});

    EXPECT_EQ(original.size(), 2);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(modified_copy.size(), 3);

    EXPECT_EQ(original.back().value, 2);
    EXPECT_EQ(modified_copy.back().value, 3);
}

TEST_F(RecursivePathTrackerTest, SharedStructure) {
    auto base    = empty_tracker.push(TestStep{1}).push(TestStep{2});
    auto branch1 = base.push(TestStep{3});
    auto branch2 = base.push(TestStep{4});

    EXPECT_EQ(base.size(), 2);
    EXPECT_EQ(branch1.size(), 3);
    EXPECT_EQ(branch2.size(), 3);

    EXPECT_EQ(branch1[0].value, 1);
    EXPECT_EQ(branch1[1].value, 2);
    EXPECT_EQ(branch1[2].value, 3);

    EXPECT_EQ(branch2[0].value, 1);
    EXPECT_EQ(branch2[1].value, 2);
    EXPECT_EQ(branch2[2].value, 4);
}

TEST_F(RecursivePathTrackerTest, VectorConversion) {
    auto tracker = empty_tracker.push(TestStep{10, "ten"})
                       .push(TestStep{20, "twenty"})
                       .push(TestStep{30, "thirty"});

    std::vector<TestStep> vec          = tracker.toVector();
    std::vector<TestStep> implicit_vec = tracker;

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(implicit_vec.size(), 3);

    EXPECT_EQ(vec[0].value, 10);
    EXPECT_EQ(vec[1].value, 20);
    EXPECT_EQ(vec[2].value, 30);

    EXPECT_EQ(implicit_vec[0].name, "ten");
    EXPECT_EQ(implicit_vec[1].name, "twenty");
    EXPECT_EQ(implicit_vec[2].name, "thirty");
}

TEST_F(RecursivePathTrackerTest, Indexing) {
    auto tracker = empty_tracker.push(TestStep{100})
                       .push(TestStep{200})
                       .push(TestStep{300});

    EXPECT_EQ(tracker[0].value, 100);
    EXPECT_EQ(tracker[1].value, 200);
    EXPECT_EQ(tracker[2].value, 300);
}

TEST_F(RecursivePathTrackerTest, Iteration) {
    auto tracker = empty_tracker.push(TestStep{5, "five"})
                       .push(TestStep{10, "ten"})
                       .push(TestStep{15, "fifteen"});

    std::vector<int>         values;
    std::vector<std::string> names;

    for (const auto& step : tracker) {
        values.push_back(step.value);
        names.push_back(step.name);
    }

    EXPECT_EQ(values, std::vector<int>({5, 10, 15}));
    EXPECT_EQ(names, std::vector<std::string>({"five", "ten", "fifteen"}));
}

TEST_F(RecursivePathTrackerTest, IteratorOperations) {
    auto tracker = empty_tracker.push(TestStep{1})
                       .push(TestStep{2})
                       .push(TestStep{3})
                       .push(TestStep{4});

    auto it = tracker.begin();
    EXPECT_EQ(it->value, 1);

    ++it;
    EXPECT_EQ(it->value, 2);

    it += 2;
    EXPECT_EQ(it->value, 4);

    --it;
    EXPECT_EQ(it->value, 3);

    EXPECT_EQ(tracker.end() - tracker.begin(), 4);
}

TEST_F(RecursivePathTrackerTest, IntegerType) {
    auto int_path = int_tracker.push(1).push(2).push(3);

    EXPECT_EQ(int_path.size(), 3);
    EXPECT_EQ(int_path[0], 1);
    EXPECT_EQ(int_path[1], 2);
    EXPECT_EQ(int_path[2], 3);
    EXPECT_EQ(int_path.back(), 3);
}

TEST_F(RecursivePathTrackerTest, StringType) {
    auto string_path = string_tracker.push("hello").push("world").push(
        "test");

    EXPECT_EQ(string_path.size(), 3);
    EXPECT_EQ(string_path[0], "hello");
    EXPECT_EQ(string_path[1], "world");
    EXPECT_EQ(string_path[2], "test");
    EXPECT_EQ(string_path.back(), "test");
}

TEST_F(RecursivePathTrackerTest, EmptyPopBehavior) {
    auto empty_pop = empty_tracker.pop();
    EXPECT_TRUE(empty_pop.empty());
    EXPECT_EQ(empty_pop.size(), 0);
}

TEST_F(RecursivePathTrackerTest, BackOnEmptyThrows) {
    EXPECT_THROW(empty_tracker.back(), std::out_of_range);
}

TEST_F(RecursivePathTrackerTest, LargePathPerformance) {
    auto tracker = empty_tracker;

    for (int i = 0; i < 1000; ++i) { tracker = tracker.push(TestStep{i}); }

    EXPECT_EQ(tracker.size(), 1000);
    EXPECT_EQ(tracker.back().value, 999);
    EXPECT_EQ(tracker[0].value, 0);
    EXPECT_EQ(tracker[500].value, 500);

    auto vec = tracker.toVector();
    EXPECT_EQ(vec.size(), 1000);
    EXPECT_EQ(vec[999].value, 999);
}

TEST_F(RecursivePathTrackerTest, DeepBranching) {
    auto base = empty_tracker;
    for (int i = 0; i < 10; ++i) { base = base.push(TestStep{i}); }

    std::vector<RecursivePathTracker<TestStep>> branches;
    for (int i = 0; i < 5; ++i) {
        branches.push_back(base.push(TestStep{100 + i}));
    }

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(branches[i].size(), 11);
        EXPECT_EQ(branches[i][9].value, 9);
        EXPECT_EQ(branches[i].back().value, 100 + i);
    }
}
