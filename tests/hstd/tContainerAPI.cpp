#include <hstd/stdlib/Vec.hpp>
#include <gtest/gtest.h>
#include <hstd/ext/immer.hpp>
#include <hstd/stdlib/Map.hpp>


using namespace hstd;

template <typename T>
SequentialContainerAdapter<T> to_seq_adapter(T const* p) {
    return SequentialContainerAdapter<T>(p);
}

template <HasSequentialContainerAdapter T>
void sequential_api_user(
    SequentialContainerAdapter<T>      a,
    Vec<typename T::value_type> const& items) {
    a.clear();
    for (auto it = a.begin(); it != a.end(); ++it) {}
    a.begin_insert();
    for (auto const& it : items) { a.add(it); }
    a.end_insert();
}

TEST(ContainerAdapterAPI, SequentialContainerAPI) {
    {
        Vec<int> v;
        auto     a = to_seq_adapter(&v);
        sequential_api_user(a, {1, 2});
        EXPECT_EQ(a.size(), 2);
    }
    {
        immer::vector<int> v;
        auto               a = to_seq_adapter(&v);
        sequential_api_user(a, {1, 2});
        EXPECT_EQ(a.size(), 2);
    }
    {
        immer::flex_vector<int> v;
        auto                    a = to_seq_adapter(&v);
        sequential_api_user(a, {1, 2});
        EXPECT_EQ(a.size(), 2);
    }
    {
        immer::map<int, int> v;
        auto                 a = to_seq_adapter(&v);
        sequential_api_user(a, {{1, 2}, {2, 3}});
        EXPECT_EQ(a.size(), 2);
    }
    {
        ext::ImmMap<int, int> v;
        auto                  a = to_seq_adapter(&v);
        sequential_api_user(a, {{1, 2}, {2, 3}});
        EXPECT_EQ(a.size(), 2);
    }
    {
        std::map<int, int> v;
        auto               a = to_seq_adapter(&v);
        sequential_api_user(a, {{1, 2}, {2, 3}});
        EXPECT_EQ(a.size(), 2);
    }
    {
        std::unordered_map<int, int> v;
        auto                         a = to_seq_adapter(&v);
        sequential_api_user(a, {{1, 2}, {2, 3}});
        EXPECT_EQ(a.size(), 2);
    }

    {
        hstd::SortedMap<int, int> v;
        auto                      a = to_seq_adapter(&v);
        sequential_api_user(a, {{1, 2}, {2, 3}});
        EXPECT_EQ(a.size(), 2);
    }
    {
        hstd::UnorderedMap<int, int> v;
        auto                         a = to_seq_adapter(&v);
        sequential_api_user(a, {{1, 2}, {2, 3}});
        EXPECT_EQ(a.size(), 2);
    }
}


template <typename T>
void assoc_api_user(
    SequentialContainerAdapter<T>      a,
    Vec<typename T::value_type> const& items) {
    sequential_api_user(a, items);
}

template <typename T>
AssociativeContainerAdapter<T> to_assoc_adapter(T const* p) {
    return AssociativeContainerAdapter<T>(p);
}
TEST(ContainerAdapterAPI, AssociativeContainerAPI) {
    {
        ext::ImmMap<int, int> v;
        auto                  a = to_assoc_adapter(&v);
        assoc_api_user(a, {{1, 2}, {2, 3}});
        EXPECT_EQ(a.size(), 2);

        a.begin_insert();
        a.insert_or_assign(123, 3);
        a.end_insert();
        EXPECT_EQ(a.size(), 3);
    }
}
