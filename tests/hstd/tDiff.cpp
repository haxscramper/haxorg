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

using IVec = Vec<int>;


template <typename T>
Vec<T> expandOn(CR<BacktrackRes> back, CR<Vec<T>> in, bool onX) {
    Vec<T> result;
    if (onX) {
        for (int i : back.lhsIndex) { result.push_back(in[i]); }
    } else {
        for (int i : back.rhsIndex) { result.push_back(in[i]); }
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

class DiffTest : public ::testing::Test {
  protected:
    void SetUp() override {
        cmp = [](CR<int> lhs, CR<int> rhs) -> bool { return lhs == rhs; };

        cmpValue = [](CR<int> lhs, CR<int> rhs) -> float {
            return lhs == rhs ? 1.0 : 0.0;
        };
    }

    Func<bool(CR<int>, CR<int>)>  cmp;
    Func<float(CR<int>, CR<int>)> cmpValue;

    BacktrackRes lcs(CR<IVec> lhs, CR<IVec> rhs) {
        return longestCommonSubsequence(lhs, rhs, cmp, cmpValue)[0];
    }
};

TEST_F(DiffTest, BothInputSequencesAreEmpty) {
    IVec a1       = {};
    IVec b1       = {};
    IVec expected = {};
    EXPECT_EQ(expandOn(lcs(a1, b1), a1, true), expected);
}

TEST_F(DiffTest, OneOfTheInputSequencesIsEmpty) {
    IVec a2       = {1, 2, 3};
    IVec b2       = {};
    IVec expected = {};
    EXPECT_EQ(expandOn(lcs(a2, b2), a2, true), expected);
}

TEST_F(DiffTest, InputSequencesDoNotHaveAnyCommonElements) {
    IVec a4       = {1, 2, 3, 4};
    IVec b4       = {5, 6, 7, 8};
    IVec expected = {};
    EXPECT_EQ(expandOn(lcs(a4, b4), a4, true), expected);
}

TEST_F(DiffTest, InputSequencesNoDifference) {
    IVec a4       = {4, 5, 6, 7};
    IVec b4       = {4, 5, 6, 7};
    IVec expected = {0, 1, 2, 3};
    auto match    = lcs(a4, b4);

    EXPECT_EQ(match.lhsIndex, (IVec{0, 1, 2, 3}));
    EXPECT_EQ(match.rhsIndex, (IVec{0, 1, 2, 3}));
}

TEST_F(DiffTest, NoDifferenceShiftedDiff) {
    IVec        a = {1};
    IVec        b = {1};
    ShiftedDiff s{lcs(a, b), a.size(), b.size()};

    EXPECT_EQ(s.newShifted.size(), 1) << fmt1(s);
    EXPECT_EQ(s.newShifted.at(0).item, 0) << fmt1(s);
    EXPECT_EQ(s.newShifted.at(0).kind, SeqEditKind::Keep) << fmt1(s);

    EXPECT_EQ(s.oldShifted.size(), 1) << fmt1(s);
    EXPECT_EQ(s.oldShifted.at(0).item, 0) << fmt1(s);
    EXPECT_EQ(s.oldShifted.at(0).kind, SeqEditKind::Keep) << fmt1(s);
}

TEST_F(DiffTest, PartiallySimilarShiftedDiff) {
    IVec         a     = {1, 2, 3, 4};
    IVec         b     = {1, 2, 7, 8};
    BacktrackRes match = lcs(a, b);

    EXPECT_EQ(match.lhsIndex, (IVec{0, 1}));
    EXPECT_EQ(match.rhsIndex, (IVec{0, 1}));

    ShiftedDiff s{match, a.size(), b.size()};

    EXPECT_EQ(s.newShifted.size(), 6) << fmt1(s);
    EXPECT_EQ(s.oldShifted.size(), 6) << fmt1(s);
}

TEST_F(DiffTest, AlllDifferentShiftedDiff) {
    IVec         a     = {1, 2, 3, 4};
    IVec         b     = {5, 6, 7, 8};
    BacktrackRes match = lcs(a, b);

    EXPECT_EQ(match.lhsIndex, (IVec{}));
    EXPECT_EQ(match.rhsIndex, (IVec{}));

    ShiftedDiff s{match, a.size(), b.size()};

    EXPECT_EQ(s.newShifted.size(), 8) << fmt1(s);
    EXPECT_EQ(s.oldShifted.size(), 8) << fmt1(s);
}

TEST_F(DiffTest, EmptySequences) {
    Vec<int> lhsSeq;
    Vec<int> rhsSeq;
    auto     result = myersDiff<int>(
        lhsSeq, rhsSeq, [](const int&, const int&) { return true; });
    ASSERT_TRUE(result.empty());
}

TEST_F(DiffTest, IdenticalSequences) {
    Vec<int> lhsSeq = {1, 2, 3};
    Vec<int> rhsSeq = {1, 2, 3};
    auto     result = myersDiff<int>(
        lhsSeq, rhsSeq, [](const int& a, const int& b) { return a == b; });
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].kind, SeqEditKind::Keep);
    EXPECT_EQ(result[1].kind, SeqEditKind::Keep);
    EXPECT_EQ(result[2].kind, SeqEditKind::Keep);
}

TEST_F(DiffTest, Insertion) {
    Vec<int> lhsSeq = {1, 2, 3};
    Vec<int> rhsSeq = {1, 2, 3, 4};
    auto     result = myersDiff<int>(
        lhsSeq, rhsSeq, [](const int& a, const int& b) { return a == b; });
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[3].kind, SeqEditKind::Insert);
    EXPECT_EQ(result[3].targetPos, 3);
}

class DiffTestFuzzy : public ::testing::Test {
  protected:
    void SetUp() override {}

    FuzzyMatcher matcher;

    auto getMatches(const Str& lhs, const Str& rhs) -> Vec<int> {
        matcher.debug   = true;
        matcher.isEqual = [&](CR<int> lhsIdx, CR<int> rhsIdx) -> bool {
            return lhs.at(lhsIdx) == rhs.at(rhsIdx);
        };
        matcher.isSeparator = [](CR<char> sep) -> bool { return false; };
        int score           = 0;

        matcher.fuzzy_match(
            slice(0, lhs.size() - 1), slice(0, rhs.size() - 1), score
        );
        return matcher.matches;
    }
};

TEST_F(DiffTestFuzzy, FullMatch) {
    auto m = getMatches("123", "010233");
    LOG(INFO) << fmt1(m);
    EXPECT_EQ(m.at(0), 1);
    EXPECT_EQ(m.at(1), 3);
    EXPECT_EQ(m.at(0), 4);
}
