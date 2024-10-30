//#include "common.hpp"
#include <gtest/gtest.h>
#include <hstd/stdlib/dod_base.hpp>
#include <bitset>

struct IdMask2Value {};
DECL_ID_TYPE_MASKED(IdMask2Value, IdMask2, u8, 2);

struct IdMask0Value {};
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
