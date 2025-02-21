#include <gtest/gtest.h>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Ranges.hpp>

using namespace hstd;

TEST(Algorithms, Partitioning) {
    Vec<int> it{1, 1, 2, 2, 3, 3, 4, 4, 3};
    auto     spans = partition<int, int>(
        it, [](CR<int> v) -> int { return v; });
    EXPECT_EQ(spans.size(), 5);
    EXPECT_EQ(spans[0].size(), 2);
    EXPECT_EQ(spans[1].size(), 2);
    EXPECT_EQ(spans[1_B].size(), 1);
}

TEST(Algorithms, PartitioningEmptyVector) {
    Vec<int> input;
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_TRUE(result.empty());
}

TEST(Algorithms, PartitioningSingleElementVector) {
    Vec<int> input  = {1};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], input);
}

TEST(Algorithms, PartitioningOddEvenNumbers) {
    Vec<int> input  = {1, 2, 3, 4, 5};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0], Vec<int>({1}));
    EXPECT_EQ(result[1], Vec<int>({2}));
}

TEST(Algorithms, PartitioningPositiveNegativeNumbers) {
    Vec<int> input  = {-1, -2, 3, 4, -5};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return 0 <= i; });
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], Vec<int>({-1, -2}));
    EXPECT_EQ(result[1], Vec<int>({3, 4}));
    EXPECT_EQ(result[2], Vec<int>({-5}));
}

TEST(Algorithms, CarthesianProduct) {
    Vec<int>  lhs = {1, 2};
    Vec<char> rhs = {'a', 'b'};
    auto      gen = gen_view(carthesian(lhs, rhs)) | rs::to<Vec>();
    auto      it  = gen.begin();
    ASSERT_EQ(*(it->first), 1);
    ASSERT_EQ(*(it->second), 'a');
    ++it;
    ASSERT_EQ(*(it->first), 1);
    ASSERT_EQ(*(it->second), 'b');
    ++it;
    ASSERT_EQ(*(it->first), 2);
    ASSERT_EQ(*(it->second), 'a');
    ++it;
    ASSERT_EQ(*(it->first), 2);
    ASSERT_EQ(*(it->second), 'b');
}

TEST(Algorithms, Reverse) {
    Vec<int> vec = {1, 2, 3};
    reverse(vec);
    ASSERT_EQ(vec, (Vec<int>{3, 2, 1}));
}

TEST(Algorithms, Sort) {
    Vec<int> vec = {3, 1, 2};
    sort(vec, [](int a, int b) { return a < b; });
    ASSERT_EQ(vec, (Vec<int>{1, 2, 3}));
}

TEST(Algorithms, ReversedCopy) {
    Vec<int> vec    = {1, 2, 3};
    auto     revVec = reversed(vec);
    ASSERT_EQ(revVec, (Vec<int>{3, 2, 1}));
    ASSERT_EQ(vec, (Vec<int>{1, 2, 3}));
}

TEST(Algorithms, SortedCopy) {
    Vec<int> vec       = {3, 1, 2};
    auto     sortedVec = sorted(vec);
    ASSERT_EQ(sortedVec, (Vec<int>{1, 2, 3}));
    ASSERT_EQ(vec, (Vec<int>{3, 1, 2}));
}


TEST(Algorithms, SortedBy) {
    struct Person {
        std::string name;
        int         age;
    };
    Vec<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    auto        sortedPeople = sortedBy(
        people, [](const Person& p) { return p.age; });
    ASSERT_EQ(sortedPeople[0].name, "Bob");
    ASSERT_EQ(sortedPeople[1].name, "Alice");
    ASSERT_EQ(sortedPeople[2].name, "Charlie");
}

TEST(Algorithms, MapOptional) {
    Opt<int> opt    = 5;
    auto     result = map(opt, [](int x) { return x * 2; });
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), 10);
}

TEST(Algorithms, MapVector) {
    Vec<int> vec    = {1, 2, 3};
    auto     result = map(vec, [](int x) { return x * 2; });
    ASSERT_EQ(result, (Vec<int>{2, 4, 6}));
}

TEST(Algorithms, RangeAuxAlgorithms) {
    {
        Vec<Opt<int>> v1{1, std::nullopt, 2, std::nullopt};
        Vec<Opt<int>> v2 = v1 | drop_if_nullopt() | rs::to<Vec>();
        EXPECT_EQ(v2.size(), 2);
        EXPECT_EQ(v2.at(0), std::make_optional(1));
        EXPECT_EQ(v2.at(1), std::make_optional(2));
        Vec<int> v3 = v2 | unpack_optional() | rs::to<Vec>();
    }

    {
        auto tmp1 = own_view(Vec<int>{1})
                  | rv::transform([](int const& value) { return value; })
                  | rs::to<Vec>();

        EXPECT_EQ(tmp1, Vec<int>{1});
    }

    {
        int  call_count = 0;
        auto gen_func   = [&]() {
            ++call_count;
            return Vec<int>{1, 2, 3};
        };

        auto tmp1 = own_view(gen_func())
                  | rv::transform(
                        [](int const& value) { return value * 2; })
                  | rs::to<Vec>();
        EXPECT_EQ(call_count, 1);
        EXPECT_EQ(tmp1.size(), 3);
        EXPECT_EQ(tmp1, (Vec<int>{2, 4, 6}));
    }
}
