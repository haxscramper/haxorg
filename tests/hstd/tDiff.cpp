#include <gtest/gtest.h>
#include <hstd/stdlib/diffs.hpp>

template <typename T>
Str formatDiffedEx(CR<Vec<SeqEdit>> ops, Span<T> oldSeq, Span<T> newSeq) {
    Str result;
    for (const auto& op : ops) {
        switch (op.kind) {
            case SeqEditKind::Keep:
                result += fmt1(oldSeq[op.sourcePos]);
                break;
            case SeqEditKind::Delete:
                result += "[del " + fmt1(oldSeq[op.sourcePos]) + "]";
                break;
            case SeqEditKind::Insert:
                result += "[ins " + fmt1(newSeq[op.targetPos]) + "]";
                break;
            case SeqEditKind::Transpose:
                result += "[trans " + fmt1(oldSeq[op.sourcePos]) + " <> "
                        + fmt1(newSeq[op.targetPos]) + "]";
                break;
            case SeqEditKind::Replace:
                result += "[repl " + fmt1(oldSeq[op.sourcePos]) + " -> "
                        + fmt1(newSeq[op.targetPos]) + "]";
                break;
            case SeqEditKind::None: assert(false); break;
        }
    }
    return result;
}


template <typename T>
Vec<T> expandOn(CR<BacktrackRes> back, CR<Vec<T>> in, bool onX) {
    Vec<T> result;
    if (onX) {
        for (int i : back.lhsIndex) {
            result.push_back(in[i]);
        }
    } else {
        for (int i : back.rhsIndex) {
            result.push_back(in[i]);
        }
    }
    return result;
}


Str levEditText(const Str& a, const Str& b) {
    Vec<SeqEdit> ops = levenshteinDistance<const char>(
                           a.toSpan(), b.toSpan())
                           .operations;
    return formatDiffedEx(ops, a.toSpan(), b.toSpan());
}

class LevenshteinEditOperationsTest : public ::testing::Test {};

TEST_F(LevenshteinEditOperationsTest, SimpleEdits) {
    const Vec<std::tuple<Str, Str, Str>> testCases = {
        {"a", "b", "[repl a -> b]"},
        {"ab", "b", "[del a]b"},
        {"ab", "bb", "[repl a -> b]b"},
        {"a", "aa", "[ins a]a"}};

    for (const auto& [a, b, edit] : testCases) {
        const Str lev = levEditText(a, b);
        EXPECT_EQ(lev, edit);
    }
}

class LongestCommonSubsequenceTest : public ::testing::Test {
  protected:
    void SetUp() override {
        cmp = [](CR<int> lhs, CR<int> rhs) -> bool { return lhs == rhs; };

        cmpValue = [](CR<int> lhs, CR<int> rhs) -> float {
            return lhs == rhs ? 1.0 : 0.0;
        };
    }

    Func<bool(CR<int>, CR<int>)>  cmp;
    Func<float(CR<int>, CR<int>)> cmpValue;
};

TEST_F(LongestCommonSubsequenceTest, BothInputSequencesAreEmpty) {
    Vec<int> a1       = {};
    Vec<int> b1       = {};
    Vec<int> expected = {};
    EXPECT_EQ(
        expandOn(
            longestCommonSubsequence(a1, b1, cmp, cmpValue)[0], a1, true),
        expected);
}

TEST_F(LongestCommonSubsequenceTest, OneOfTheInputSequencesIsEmpty) {
    Vec<int> a2       = {1, 2, 3};
    Vec<int> b2       = {};
    Vec<int> expected = {};
    EXPECT_EQ(
        expandOn(
            longestCommonSubsequence(a2, b2, cmp, cmpValue)[0], a2, true),
        expected);
}

TEST_F(
    LongestCommonSubsequenceTest,
    InputSequencesDoNotHaveAnyCommonElements) {
    Vec<int> a4       = {1, 2, 3, 4};
    Vec<int> b4       = {5, 6, 7, 8};
    Vec<int> expected = {};
    EXPECT_EQ(
        expandOn(
            longestCommonSubsequence(a4, b4, cmp, cmpValue)[0], a4, true),
        expected);
}

class FuzzyMatchConfigurableTest : public ::testing::Test {
  protected:
    void SetUp() override {
        matcher.isEqual = [](CR<char> lhs, CR<char> rhs) -> bool {
            return lhs == rhs;
        };
        matcher.isSeparator = [](CR<char> sep) -> bool { return false; };
    }

    FuzzyMatcher<char const> matcher;

    auto getMatches(const Str& lhs, const Str& rhs) -> Array<int, 256> {
        return matcher.matches;
    }
};

TEST_F(FuzzyMatchConfigurableTest, FullMatch) {
    auto m = getMatches("123", "010233");
}
