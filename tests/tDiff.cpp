#include "common.hpp"

#include <hstd/stdlib/diffs.hpp>

template <typename T>
Str formatDiffedEx(CR<Vec<SeqEdit>> ops, Span<T> oldSeq, Span<T> newSeq) {
    Str result;
    for (const auto& op : ops) {
        switch (op.kind) {
            case SeqEditKind::Keep:
                result += to_string(oldSeq[op.sourcePos]);
                break;
            case SeqEditKind::Delete:
                result += "[del " + to_string(oldSeq[op.sourcePos]) + "]";
                break;
            case SeqEditKind::Insert:
                result += "[ins " + to_string(newSeq[op.targetPos]) + "]";
                break;
            case SeqEditKind::Transpose:
                result += "[trans " + to_string(oldSeq[op.sourcePos])
                        + " <> " + to_string(newSeq[op.targetPos]) + "]";
                break;
            case SeqEditKind::Replace:
                result += "[repl " + to_string(oldSeq[op.sourcePos])
                        + " -> " + to_string(newSeq[op.targetPos]) + "]";
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
    Vec<SeqEdit> ops = levenshteinDistance<const QChar>(
                           a.toSpan(), b.toSpan())
                           .operations;
    return formatDiffedEx(ops, a.toSpan(), b.toSpan());
}

TEST_CASE("Levenshtein edit operations", "[TARGET]") {
    SECTION("Simple edits") {
        const Vec<std::tuple<Str, Str, Str>> testCases = {
            {"a", "b", "[repl a -> b]"},
            {"ab", "b", "[del a]b"},
            {"ab", "bb", "[repl a -> b]b"},
            {"a", "aa", "[ins a]a"}};

        for (const auto& [a, b, edit] : testCases) {
            const Str lev = levEditText(a, b);
            // REQUIRE(lev == edit);
        }
    }
}


TEST_CASE("longestCommonSubsequence", "[LCS]") {
    Func<bool(CR<int>, CR<int>)> cmp =
        [](CR<int> lhs, CR<int> rhs) -> bool { return lhs == rhs; };

    Func<float(CR<int>, CR<int>)> cmpValue = [](CR<int> lhs,
                                                CR<int> rhs) -> float {
        return lhs == rhs ? 1.0 : 0.0;
    };

    SECTION("Both input sequences are empty") {
        Vec<int> a1       = {};
        Vec<int> b1       = {};
        Vec<int> expected = {};
        REQUIRE(
            expandOn(
                longestCommonSubsequence(a1, b1, cmp, cmpValue)[0],
                a1,
                true)
            == expected);
    }

    SECTION("One of the input sequences is empty") {
        Vec<int> a2       = {1, 2, 3};
        Vec<int> b2       = {};
        Vec<int> expected = {};
        REQUIRE(
            expandOn(
                longestCommonSubsequence(a2, b2, cmp, cmpValue)[0],
                a2,
                true)
            == expected);
    }

    // SECTION("Input sequences have common elements") {
    //     Vec<int> a3       = {1, 2, 3, 4};
    //     Vec<int> b3       = {2, 4, 3, 1};
    //     Vec<int> expected = {1, 2, 3, 4};
    //     REQUIRE(expandOn(longestCommonSubsequence(a3, b3, cmp)[0], a3,
    //     true) == expected);
    // }

    SECTION("Input sequences do not have any common elements") {
        Vec<int> a4       = {1, 2, 3, 4};
        Vec<int> b4       = {5, 6, 7, 8};
        Vec<int> expected = {};
        REQUIRE(
            expandOn(
                longestCommonSubsequence(a4, b4, cmp, cmpValue)[0],
                a4,
                true)
            == expected);
    }
}

TEST_CASE("Fuzzy match configurable", "[fuzzy]") {
    FuzzyMatcher<char const> matcher;
    matcher.isEqual = [](CR<char> lhs, CR<char> rhs) -> bool {
        // std::cout << lhs << " == " << rhs << "\n";
        return lhs == rhs;
    };
    matcher.isSeparator = [](CR<char> sep) -> bool { return false; };

    auto getMatches = [&](Str lhs, Str rhs) -> Array<int, 256> {
        // std::cout << "score "
        //           << matcher.get_score(lhs.toSpan(), rhs.toSpan()) <<
        //           "\n";
        return matcher.matches;
    };

    SECTION("Full match") {
        auto m = getMatches("123", "010233");
        // std::cout << std::endl << "---\n" << m << std::endl;
    }
}
