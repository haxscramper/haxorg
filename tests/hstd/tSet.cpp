import std.stdlib.Set;
import std.stdlib.Str;
#include <gtest/gtest.h>

TEST(UnorderedSetOperationsTest, Correctness) {
    using S = UnorderedSet<Str>;
    S set1{"1"};
    S set2{"2"};

    // Test incl method
    {
        set1.incl("10");
        set2.incl("20");
        EXPECT_TRUE(set1.contains("10"));
        EXPECT_TRUE(set2.contains("20"));
    }

    // Test excl method
    {
        set1.excl("1");
        EXPECT_FALSE(set1.contains("1"));
        EXPECT_TRUE(set2.contains("2"));
    }

    // Test addition operator
    {
        S tmp;
        tmp.incl("2");
        EXPECT_TRUE(tmp.contains("2"));
        tmp.incl(S{"3", "4"});
        EXPECT_TRUE(tmp.contains("3"));
        EXPECT_TRUE(tmp.contains("4"));
        S set3 = S{"2"} + S{"3", "4"};
        EXPECT_TRUE(set3.contains("2"));
        EXPECT_TRUE(set3.contains("3"));
        EXPECT_TRUE(set3.contains("4"));
    }

    // Test subtraction operator
    {
        S q = S{"2", "3", "4"};
        EXPECT_TRUE(q.contains("2"));
        EXPECT_TRUE(q.contains("3"));
        EXPECT_TRUE(q.contains("4"));
        q.excl("2");
        EXPECT_FALSE(q.contains("2"));
        q.incl("2");
        S set3 = q - S{"3", "4"};
        EXPECT_TRUE(set3.contains("2"));
        EXPECT_FALSE(set3.contains("3"));
        EXPECT_FALSE(set3.contains("4"));
    }

    // Test symmetric difference operator
    {
        S set3 = S{"2", "3", "4"} ^ S { "2" };
        EXPECT_FALSE(set3.contains("2"));
        EXPECT_TRUE(set3.contains("3"));
        EXPECT_TRUE(set3.contains("4"));
    }

    // Test intersection operator
    {
        S set3 = S{"2", "0", "9"} & S{"2", "1", "3"};
        EXPECT_TRUE(set3.contains("2"));
        EXPECT_FALSE(set3.contains("1"));
        EXPECT_FALSE(set3.contains("3"));
    }
}
