#include <hstd/stdlib/Vec.hpp>
#include <gtest/gtest.h>
#include <hstd/ext/immer.hpp>
#include <hstd/stdlib/Map.hpp>


using namespace hstd;

template <HasSequentialContainerAdapter T>
SequentialContainerAdapter<T> to_seq_adapter(T const* p) {
    return SequentialContainerAdapter<T>(p);
}

template <HasSequentialContainerAdapter T, typename It>
void sequential_api_user(
    SequentialContainerAdapter<T> a,
    Vec<It> const&                items) {
    a.clear();
    int count = 0;

    for (auto it = a.begin(); it != a.end(); ++it) {
        It tmp = *it;
        ++count;
    }

    ASSERT_EQ(count, 0);

    a.begin_insert();
    for (auto const& it : items) { a.add(it); }
    a.end_insert();

    for (auto it = a.begin(); it != a.end(); ++it) {
        It tmp = *it;
        ++count;
    }

    ASSERT_EQ(count, items.size());
}

template <typename T>
class SequentialContainerAdapterTest : public ::testing::Test {
  public:
    using ContainerType = T;
};

using SequentialContainerTypes = ::testing::Types<
    Vec<int>,
    immer::vector<int>,
    immer::flex_vector<int>,
    immer::map<int, int>,
    ext::ImmMap<int, int>,
    std::map<int, int>,
    std::unordered_map<int, int>,
    hstd::SortedMap<int, int>,
    hstd::UnorderedMap<int, int>>;

TYPED_TEST_SUITE(SequentialContainerAdapterTest, SequentialContainerTypes);

TYPED_TEST(SequentialContainerAdapterTest, SequentialContainerAPI) {
    using Container = typename TestFixture::ContainerType;


    for (int count : Vec<int>{0, 2, 4, 8, 64, 512, 2048}) {
        Container v;
        auto      a = to_seq_adapter(&v);
        if constexpr (
            std::is_same_v<Container, Vec<int>>
            || std::is_same_v<Container, immer::vector<int>>
            || std::is_same_v<Container, immer::flex_vector<int>>) {
            Vec<int> seq_items;
            for (int i = 0; i < count; ++i) { seq_items.push_back(i); }
            sequential_api_user(a, seq_items);
        } else {
            Vec<std::pair<int, int>> seq_items;
            for (int i = 0; i < count; ++i) {
                seq_items.push_back({i, i + 1});
            }
            sequential_api_user(a, seq_items);
        }

        EXPECT_EQ(a.size(), count);
    }
}

template <HasAssociativeContainerAdapter T>
void assoc_api_user(
    SequentialContainerAdapter<T>      a,
    Vec<typename T::value_type> const& items) {
    sequential_api_user(a, items);
}

template <HasAssociativeContainerAdapter T>
AssociativeContainerAdapter<T> to_assoc_adapter(T const* p) {
    return AssociativeContainerAdapter<T>(p);
}

template <typename T>
class AssociativeContainerAdapterTest : public ::testing::Test {
  public:
    using ContainerType = T;
};

using AssociativeContainerTypes = ::testing::Types<
    ext::ImmMap<int, int>,
    immer::map<int, int>,
    std::map<int, int>,
    std::unordered_map<int, int>,
    hstd::SortedMap<int, int>,
    hstd::UnorderedMap<int, int>>;

TYPED_TEST_SUITE(
    AssociativeContainerAdapterTest,
    AssociativeContainerTypes);

TYPED_TEST(AssociativeContainerAdapterTest, AssociativeContainerAPI) {
    using Container = typename TestFixture::ContainerType;
    Container v;
    auto      a = to_assoc_adapter(&v);

    assoc_api_user(a, {{1, 2}, {2, 3}});
    EXPECT_EQ(a.size(), 2);

    a.begin_insert();
    a.insert_or_assign(123, 3);
    a.end_insert();
    EXPECT_EQ(a.size(), 3);
    EXPECT_TRUE(a.contains(123));

    EXPECT_EQ(a.keys().size(), 3);
    EXPECT_EQ(a.at(123), 3);
    EXPECT_EQ(a.at(1), 2);
    EXPECT_EQ(a.at(2), 3);
}
