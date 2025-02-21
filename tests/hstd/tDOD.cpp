//#include "common.hpp"
#include <gtest/gtest.h>
#include <hstd/stdlib/dod_base.hpp>
#include <bitset>

using namespace hstd;

struct IdMask2;
struct IdMask2Value {
    using id_type = IdMask2;
};
DECL_ID_TYPE_MASKED(IdMask2Value, IdMask2, u8, 2);

struct IdMask0;
struct IdMask0Value {
    int field1;
    int field2;
    using id_type = IdMask0;
    bool operator==(IdMask0Value const& other) const {
        return field1 == other.field1 && field2 == other.field2;
    }
};

template <>
struct std::hash<IdMask0Value> {
    std::size_t operator()(IdMask0Value const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.field1);
        hax_hash_combine(result, it.field2);
        return result;
    }
};


DECL_ID_TYPE_MASKED(IdMask0Value, IdMask0, u8, 0);

template <typename T>
std::string bits(T val) {
    return std::bitset<8 * sizeof(T)>(val).to_string();
}


TEST(DODContainersTest, MaskedNodes) {
    IdMask2 id = IdMask2::FromValue(0);
    EXPECT_EQ(bits(id.getValue()), std::string("00000000"));
    id.setValue(1_u8);
    EXPECT_EQ(bits(id.getValue()), std::string("00000001"));
    EXPECT_EQ(id.getMaskSize(), 2);
    EXPECT_EQ(id.getValue(), 1_u8);
    EXPECT_EQ(id.getValue(), 0b1_u8);
    id.setMask(2_u8);
    EXPECT_EQ(bits(id.getValue()), std::string("10000001"));
    EXPECT_EQ(id.getMask(), 2_u8);
    EXPECT_EQ(bits(id.getMask()), std::string("00000010"));
    EXPECT_EQ(bits(id.getMaskUnshifed()), std::string("10000000"));
    EXPECT_EQ(id.getIndex(), 0);
    {
        u8 m = (1_u8) | (2_u8 << IdMask2::mask_offset);
        EXPECT_EQ(id.getValue(), m);
    }
    EXPECT_EQ(id.getUnmasked(), 1);

    id.setMask(3_u8);
    EXPECT_EQ(bits(id.getValue()), std::string("11000001"));
    EXPECT_EQ(id.getMask(), 3_u8);
    EXPECT_EQ(id.getIndex(), 0);
}

TEST(DODContainersTest, UnmaskedNodes) {
    IdMask0 id = IdMask0::FromValue(0);
    EXPECT_EQ(bits(id.getValue()), std::string("00000000"));
    EXPECT_TRUE(id.isNil());
    id.setValue(1_u8);
    EXPECT_EQ(bits(id.getValue()), std::string("00000001"));
    EXPECT_FALSE(id.isNil());
    EXPECT_EQ(id.getMask(), 0);
    EXPECT_EQ(id.getMaskSize(), 0);
    EXPECT_EQ(id.getMaskUnshifed(), 0);
}

TEST(DODContainersTest, InternStore) {
    using Store = dod::InternStore<IdMask0, IdMask0Value>;
    Store s;
    auto  id1 = s.add(IdMask0Value{.field1 = 0});
    EXPECT_FALSE(id1.isNil());
    auto id2 = s.add(IdMask0Value{.field1 = 0});
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(id1, id2);
    auto id3 = s.add(IdMask0Value{.field1 = 12});
    EXPECT_NE(id1, id3);
    EXPECT_EQ(s.size(), 2);
}

TEST(DODContainersTest, Store) {
    dod::Store<IdMask0, IdMask0Value> s;
    EXPECT_EQ(s.size(), 0);
    auto id1 = s.add(IdMask0Value{});
    EXPECT_FALSE(id1.isNil());
    EXPECT_EQ(s.size(), 1);
    auto id2 = s.add(IdMask0Value{});
    EXPECT_FALSE(id1.isNil());
    EXPECT_EQ(s.size(), 2);
    EXPECT_NE(id1, id2);

    s.at(id1).field1 = 0;
}

TEST(DODContainersTest, MultiStore) {
    dod::MultiStore<
        dod::InternStore<IdMask0, IdMask0Value>,
        dod::Store<IdMask2, IdMask2Value>>
        s;

    {
        auto id1 = s.add(IdMask0Value{.field1 = 0});
        EXPECT_FALSE(id1.isNil());
        auto id2 = s.add(IdMask0Value{.field1 = 0});
        EXPECT_EQ(s.store<IdMask0Value>().size(), 1);
        EXPECT_EQ(id1, id2);
        auto id3 = s.add(IdMask0Value{.field1 = 12});
        EXPECT_NE(id1, id3);
        EXPECT_EQ(s.store<IdMask0Value>().size(), 2);
    }

    {
        EXPECT_EQ(s.store<IdMask2Value>().size(), 0);
        auto id1 = s.add(IdMask2Value{});
        EXPECT_FALSE(id1.isNil());
        EXPECT_EQ(s.store<IdMask2Value>().size(), 1);
        auto id2 = s.add(IdMask2Value{});
        EXPECT_FALSE(id1.isNil());
        EXPECT_EQ(s.store<IdMask2Value>().size(), 2);
        EXPECT_NE(id1, id2);
    }
}
