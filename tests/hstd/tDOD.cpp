//#include "common.hpp"
#include <gtest/gtest.h>
import std.stdlib.dod_base;
#include <bitset>

DECL_ID_TYPE_MASKED(Value1, Id1, u8, 2);

template <typename T>
std::string bits(T val) {
    return std::bitset<8 * sizeof(T)>(val).to_string();
}

TEST(DODContainersTest, MaskedNodes) {
    Id1 id{0};
    id.setValue(1_u8);
    EXPECT_EQ(id.getMaskSize(), 2);
    EXPECT_EQ(id.getValue(), 1_u8);
    EXPECT_EQ(id.getValue(), 0b1_u8);
    id.setMask(2_u8);
    EXPECT_EQ(bits(id.getValue()), std::string("10000001"));
    EXPECT_EQ(id.getMask(), 2_u8);
    EXPECT_EQ(id.getIndex(), 0);
    {
        u8 m = (1_u8) | (2_u8 << Id1::mask_offset);
        EXPECT_EQ(id.getValue(), m);
    }
    EXPECT_EQ(id.getUnmasked(), 1);
}
