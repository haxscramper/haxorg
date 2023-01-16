#include "common.hpp"
#include <hstd/stdlib/dod_base.hpp>
#include <bitset>

DECL_ID_TYPE_MASKED(Value1, Id1, u8, 2);

template <typename T>
std::string bits(T val) {
    return std::bitset<8 * sizeof(T)>(val).to_string();
}

TEST_CASE("DOD containers", "[dod]") {
    SECTION("Masked nodes") {
        Id1 id{0};
        id.setValue(1_u8);
        REQUIRE(id.getMaskSize() == 2);
        REQUIRE(id.getValue() == 1_u8);
        REQUIRE(id.getValue() == 0b1_u8);
        id.setMask(2_u8);
        REQUIRE(bits(id.getValue()) == "10000001");
        REQUIRE(id.getMask() == 2_u8);
        REQUIRE(id.getIndex() == 0);
        {
            u8 m = (1_u8) | (2_u8 << Id1::mask_offset);
            REQUIRE(id.getValue() == m);
        }
        REQUIRE(id.getUnmasked() == 1);
    }
}
