#pragma once

#include <hstd/stdlib/Table.hpp>
#include <hstd/stdlib/Func.hpp>

struct BacktrackRes {
    Vec<int> xIndex = {};
    Vec<int> yIndex = {};
};


template <typename T>
Vec<BacktrackRes> lcs(
    CR<Vec<T>>               x,
    CR<Vec<T>>               y,
    Func<bool(CR<T>, CR<T>)> itemCmp) {

    if (x.empty() || y.empty()) {
        return {{}};
    }

    Table<Pair<int, int>, int> mem;
    Func<int(int, int)>        lcs;
    lcs = [&](int i, int j) -> int {
        if (mem.count({i, j}) == 0) {
            if (i == -1 || j == -1) {
                mem[{i, j}] = 0;
            } else if (itemCmp(x[i], y[j])) {
                mem[{i, j}] = lcs(i - 1, j - 1) + 1;
            } else {
                mem[{i, j}] = std::max(lcs(i, j - 1), lcs(i - 1, j));
            }
        }

        return mem[{i, j}];
    };

    int m = x.size() - 1;
    int n = y.size() - 1;

    Func<Vec<BacktrackRes>(int, int)> backtrack;

    backtrack = [&](int i, int j) -> Vec<BacktrackRes> {
        if (lcs(i, j) == 0) {
            return {{}};
        } else if (i == 0) {
            int jRes = j;
            while (true) {
                if (mem.contains({i, jRes - 1})
                    && lcs(i, jRes - 1) == lcs(i, j)) {
                    --jRes;
                } else {
                    break;
                }
            }

            return {
                {.xIndex = Vec<int>::FromValue({i}),
                 .yIndex = Vec<int>::FromValue({jRes})}};
        } else if (j == 0) {
            int iRes = i;
            while (true) {
                if (mem.contains({iRes - 1, j})
                    && lcs(iRes - 1, j) == lcs(i, j)) {
                    --iRes;
                } else {
                    break;
                }
            }

            return {
                {.xIndex = Vec<int>::FromValue({iRes}),
                 .yIndex = Vec<int>::FromValue({j})}};
        } else if (itemCmp(x[i], y[j])) {
            auto              back = backtrack(i - 1, j - 1);
            Vec<BacktrackRes> res;
            for (const auto& t : back) {
                res.push_back(
                    {.xIndex = t.xIndex + i, .yIndex = t.yIndex + j});
            }

            return res;
        } else if (lcs(i, j - 1) > lcs(i - 1, j)) {
            return backtrack(i, j - 1);
        } else if (lcs(i, j - 1) < lcs(i - 1, j)) {
            return backtrack(i - 1, j);
        } else {
            return backtrack(i - 1, j) + backtrack(i - 1, j);
        }
    };

    return backtrack(m, n);
}
