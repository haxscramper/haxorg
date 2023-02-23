#include "diffs.hpp"

Vec<BacktrackRes> longestCommonSubsequence(
    int                   lhsSize,
    int                   rhsSize,
    Func<bool(int, int)>  itemCmp,
    Func<float(int, int)> itemEqualityMetric) {

    if (lhsSize == 0 || rhsSize == 0) {
        return {{}};
    }

    UnorderedMap<Pair<int, int>, float> mem;
    Func<float(int, int)>               lcs;
    lcs = [&](int lhsIdx, int rhsIdx) -> float {
        if (mem.count({lhsIdx, rhsIdx}) == 0) {
            if (lhsIdx == -1 || rhsIdx == -1) {
                mem[{lhsIdx, rhsIdx}] = 0;
            } else if (itemCmp(lhsIdx, rhsIdx)) {
                mem[{lhsIdx, rhsIdx}] = lcs(lhsIdx - 1, rhsIdx - 1)
                                      + itemEqualityMetric(lhsIdx, rhsIdx);
            } else {
                mem[{lhsIdx, rhsIdx}] = std::max(
                    lcs(lhsIdx, rhsIdx - 1), lcs(lhsIdx - 1, rhsIdx));
            }
        }

        return mem[{lhsIdx, rhsIdx}];
    };

    Func<Vec<BacktrackRes>(int, int)> backtrack;

    backtrack = [&](int lhsIdx, int rhsIdx) -> Vec<BacktrackRes> {
        if (lcs(lhsIdx, rhsIdx) == 0) {
            return {{}};
        } else if (lhsIdx == 0) {
            int rhsIdxRes = rhsIdx;
            while (true) {
                if (mem.contains({lhsIdx, rhsIdxRes - 1})
                    && lcs(lhsIdx, rhsIdxRes - 1) == lcs(lhsIdx, rhsIdx)) {
                    --rhsIdxRes;
                } else {
                    break;
                }
            }

            return {
                {.lhsIndex = Vec<int>::FromValue({lhsIdx}),
                 .rhsIndex = Vec<int>::FromValue({rhsIdxRes})}};
        } else if (rhsIdx == 0) {
            int lhsIdxRes = lhsIdx;
            while (true) {
                if (mem.contains({lhsIdxRes - 1, rhsIdx})
                    && lcs(lhsIdxRes - 1, rhsIdx) == lcs(lhsIdx, rhsIdx)) {
                    --lhsIdxRes;
                } else {
                    break;
                }
            }

            return {
                {.lhsIndex = Vec<int>::FromValue({lhsIdxRes}),
                 .rhsIndex = Vec<int>::FromValue({rhsIdx})}};
        } else if (itemCmp(lhsIdx, rhsIdx)) {
            auto              back = backtrack(lhsIdx - 1, rhsIdx - 1);
            Vec<BacktrackRes> res;
            for (const auto& t : back) {
                res.push_back(
                    {.lhsIndex = t.lhsIndex + lhsIdx,
                     .rhsIndex = t.rhsIndex + rhsIdx});
            }

            return res;
        } else if (lcs(lhsIdx, rhsIdx - 1) > lcs(lhsIdx - 1, rhsIdx)) {
            return backtrack(lhsIdx, rhsIdx - 1);
        } else if (lcs(lhsIdx, rhsIdx - 1) < lcs(lhsIdx - 1, rhsIdx)) {
            return backtrack(lhsIdx - 1, rhsIdx);
        } else {
            return backtrack(lhsIdx - 1, rhsIdx)
                 + backtrack(lhsIdx - 1, rhsIdx);
        }
    };

    return backtrack(lhsSize - 1, rhsSize - 1);
}

Vec<SeqEdit> myersDiff(
    int                          lhsSize,
    int                          rhsSize,
    Func<bool(int lhs, int rhs)> itemCmp) {

    using sek = SeqEditKind;

    Vec<Pair<int, Vec<SeqEdit>>> front(lhsSize + rhsSize + 3);

    front[1].first = 0;

    for (int fullIdx = 0; fullIdx <= lhsSize + rhsSize; fullIdx++) {
        for (int backIdx = -fullIdx; backIdx <= fullIdx; backIdx += 2) {
            bool goDown
                = (backIdx == -fullIdx
                   || (backIdx != fullIdx
                       && front[backIdx - 1].first
                              < front[backIdx + 1].first));

            int          lhsIdx, rhsIdx;
            Vec<SeqEdit> history;

            if (goDown) {
                lhsIdx  = front[backIdx + 1].first;
                history = front[backIdx + 1].second;
            } else {
                lhsIdx  = front[backIdx - 1].first + 1;
                history = front[backIdx - 1].second;
            }

            rhsIdx = lhsIdx - backIdx;

            if (1 <= rhsIdx && rhsIdx <= rhsSize && goDown) {
                history.push_back(SeqEdit(sek::Insert, -1, rhsIdx - 1));
            } else if (1 <= lhsIdx && lhsIdx <= lhsSize) {
                history.push_back(SeqEdit(sek::Delete, lhsIdx - 1, -1));
            }

            while (lhsIdx < lhsSize && rhsIdx < rhsSize
                   && itemCmp(lhsIdx, rhsIdx)) {
                lhsIdx++;
                rhsIdx++;
                history.push_back(
                    SeqEdit(sek::Keep, lhsIdx - 1, rhsIdx - 1));
            }

            if (lhsSize <= lhsIdx && rhsSize <= rhsIdx) {
                return history;
            } else {
                front[backIdx].first  = lhsIdx;
                front[backIdx].second = history;
            }
        }
    }

    return Vec<SeqEdit>();
}


LevenshteinDistanceResult levenshteinDistance(
    int                  lhsMax,
    int                  rhsMax,
    Func<bool(int, int)> itemEq) {

    Vec<Vec<int>>                 m(lhsMax + 1, Vec<int>(rhsMax + 1, 0));
    Vec<Vec<std::pair<int, int>>> paths(
        lhsMax + 1, Vec<std::pair<int, int>>(rhsMax + 1, {0, 0}));

    for (int lsh = 0; lsh <= lhsMax; ++lsh) {
        m[lsh][0]     = lsh;
        paths[lsh][0] = {lsh - 1, 0};
    }

    for (int rhs = 0; rhs <= rhsMax; ++rhs) {
        m[0][rhs]     = rhs;
        paths[0][rhs] = {0, rhs - 1};
    }

    for (int lhs = 1; lhs <= lhsMax; ++lhs) {
        for (int rhs = 1; rhs <= rhsMax; ++rhs) {
            if (itemEq(lhs - 1, rhs - 1)) {
                m[lhs][rhs]     = m[lhs - 1][rhs - 1];
                paths[lhs][rhs] = {lhs - 1, rhs - 1};
            } else {
                int min_val = std::min(
                    {m[lhs - 1][rhs],
                     m[lhs][rhs - 1],
                     m[lhs - 1][rhs - 1]});
                m[lhs][rhs] = min_val + 1;
                if (m[lhs - 1][rhs] == min_val) {
                    paths[lhs][rhs] = {lhs - 1, rhs};
                } else if (m[lhs][rhs - 1] == min_val) {
                    paths[lhs][rhs] = {lhs, rhs - 1};
                } else if (m[lhs - 1][rhs - 1] == min_val) {
                    paths[lhs][rhs] = {lhs - 1, rhs - 1};
                }
            }
        }
    }

    struct Item {
        int         i;
        int         j;
        SeqEditKind t;
    };

    Vec<Item> levenpath;

    int i = lhsMax, j = rhsMax;
    while (i >= 0 && j >= 0) {
        j = rhsMax;
        while (i >= 0 && j >= 0) {
            levenpath.push_back({i, j, SeqEditKind::None});
            int t = i;
            i     = paths[i][j].first;
            j     = paths[t][j].second;
        }
    }

    std::reverse(levenpath.begin(), levenpath.end());
    Vec<SeqEdit> resultOperations;

    for (int i = 1; i < levenpath.size(); i++) {
        auto last = levenpath[i - 1];
        auto cur  = levenpath[i];

        if (i != 0) {
            if (cur.i == last.i + 1 && cur.j == last.j + 1
                && m[cur.i][cur.j] != m[last.i][last.j]) {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Replace, 0, 0});
            } else if (cur.i == last.i && cur.j == last.j + 1) {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Insert, 0, 0});
            } else if (cur.i == last.i + 1 && cur.j == last.j) {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Delete, 0, 0});
            } else {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Keep, 0, 0});
            }

            resultOperations.back().sourcePos = cur.i - 1;
            resultOperations.back().targetPos = cur.j - 1;
        }
    }

    return {m[levenpath.back().i][levenpath.back().j], resultOperations};
}
