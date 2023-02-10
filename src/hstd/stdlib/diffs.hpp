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

enum class SeqEditKind : u8
{
    None,     /// Empty edit operation
    Keep,     /// Keep original element unchanged
    Insert,   /// Insert new element into target sequence
    Replace,  /// Replace source element with the target
    Delete,   /// Delete element from the source sequence
    Transpose /// Transpose two elements
};

struct SeqEdit {
    SeqEditKind kind;      /// Sequence edit operation kind
    int         sourcePos; /// Position in the original sequence
    int         targetPos; /// Position in the target sequence

    SeqEdit(SeqEditKind kind, int sourcePos = -1, int targetPos = -1)
        : kind(kind), sourcePos(sourcePos), targetPos(targetPos) {}
};

template <typename T>
Vec<SeqEdit> myersDiff(
    const Vec<T>&                    aSeq,
    const Vec<T>&                    bSeq,
    Func<bool(const T& x, const T&)> itemCmp) {
    using sek = SeqEditKind;

    Vec<Pair<int, Vec<SeqEdit>>> front(aSeq.size() + bSeq.size() + 3);

    front[1].first = 0;

    int aMax = aSeq.size();
    int bMax = bSeq.size();

    for (int d = 0; d <= aMax + bMax; d++) {
        for (int k = -d; k <= d; k += 2) {
            bool goDown
                = (k == -d
                   || (k != d && front[k - 1].first < front[k + 1].first));
            int          x, y;
            Vec<SeqEdit> history;

            if (goDown) {
                x       = front[k + 1].first;
                history = front[k + 1].second;
            } else {
                x       = front[k - 1].first + 1;
                history = front[k - 1].second;
            }
            y = x - k;

            if (y >= 1 && y <= bMax && goDown) {
                history.push_back(SeqEdit(sek::Insert, -1, y - 1));
            } else if (x >= 1 && x <= aMax) {
                history.push_back(SeqEdit(sek::Delete, x - 1, -1));
            }

            while (x < aMax && y < bMax && itemCmp(aSeq[x], bSeq[y])) {
                x++;
                y++;
                history.push_back(SeqEdit(sek::Keep, x - 1, y - 1));
            }

            if (x >= aMax && y >= bMax) {
                return history;
            } else {
                front[k].first  = x;
                front[k].second = history;
            }
        }
    }

    return Vec<SeqEdit>();
}

template <typename T>
generator<Pair<T const*, T const*>> zip(CR<Vec<T>> lhs, CR<Vec<T>> rhs) {
    int max = std::max<int>(lhs.size(), rhs.size());
    for (int i = 0; i < max; ++i) {
        if (i < lhs.size() && i < rhs.size()) {
            co_yield {&lhs[i], &rhs[i]};
        } else if (i < lhs.size()) {
            co_yield {&lhs[i], nullptr};
        } else if (i < rhs.size()) {
            co_yield {nullptr, &rhs[i]};
        }
    }
}


struct ShiftedDiff {
    struct Item {
        SeqEditKind kind;
        int         item;
    };

    Vec<Item> oldShifted;
    Vec<Item> newShifted;

    ShiftedDiff(CR<Vec<SeqEdit>>& diff) {
        // Align diff operations against each other, for further
        // formatting.
        using sek = SeqEditKind;
        for (auto line : diff) {
            switch (line.kind) {
                case sek::Replace:
                    oldShifted.push_back({sek::Replace, line.sourcePos});
                    break;

                case sek::None:
                    assert(false && "Input diff sequence should not contain empty operations");
                    break;

                case sek::Transpose:
                    assert(false && "Input diff sequence should not contain transpose operations");
                    break;

                case sek::Delete:
                    oldShifted.push_back({sek::Delete, line.sourcePos});
                    break;

                case sek::Insert:
                    newShifted.push_back({sek::Insert, line.targetPos});
                    break;

                case sek::Keep:
                    int oldLen = oldShifted.size();
                    int newLen = newShifted.size();

                    if (oldLen < newLen) {
                        while (oldLen < newLen) {
                            oldShifted.push_back({sek::None, 0});
                            oldLen++;
                        }

                    } else if (newLen < oldLen) {
                        while (newLen < oldLen) {
                            newShifted.push_back({sek::None, 0});
                            newLen++;
                        }
                    }

                    oldShifted.push_back({sek::Keep, line.sourcePos});
                    newShifted.push_back({sek::Keep, line.targetPos});
                    break;
            }
        }
    }


    Str formatDiffed(
        CR<Vec<Str>> oldSeq,
        CR<Vec<Str>> newSeq,
        bool         sideBySide,
        bool         showLineNumbers = false) {

        using sek = SeqEditKind;

        /// Diffed sequence of items
        struct Item {
            Str  text;    /// formatted line
            bool changed; /// Whether line has changed. Used in unified
                          /// diff formatting to avoid duplicate string
                          /// printing.
        };

        Vec<Item> oldText;
        Vec<Item> newText;

        int maxLhsIdx = std::to_string(oldShifted[1_B].item).size();
        int maxRhsIdx = std::to_string(newShifted[1_B].item).size();

        auto editFmt =
            [showLineNumbers, maxLhsIdx, maxRhsIdx](
                SeqEditKind fmt, int idx, bool isLhs) -> std::string {
            if (showLineNumbers) {
                std::string num;
                if (fmt == sek::None) {
                    left_aligned(std::to_string(' '), maxLhsIdx);
                } else if (isLhs) {
                    num = left_aligned(std::to_string(idx), maxLhsIdx);
                } else {
                    num = left_aligned(std::to_string(idx), maxRhsIdx);
                }

                switch (fmt) {
                    case sek::Delete: return "-" + num;
                    case sek::Insert: return "+" + num;
                    case sek::Keep: return "~" + num;
                    case sek::None: return "?" + num;
                    case sek::Replace: return "-+" + num;
                    case sek::Transpose: return "^v" + num;
                    default: return "";
                }
            } else {
                switch (fmt) {
                    case sek::Delete: return "-";
                    case sek::Insert: return "+";
                    case sek::Replace: return "-+";
                    case sek::Keep: return "~";
                    case sek::Transpose: return "^v";
                    case sek::None: return (isLhs ? "?" : "");
                    default: return "";
                }
            }
        };

        int lhsMax = 0;

        for (int i = 0; i < oldShifted.size(); i++) {
            auto& lhs        = oldShifted[i];
            auto& rhs        = newShifted[i];
            auto  lhsDefault = oldShifted.size() <= i;
            auto  rhsDefault = newShifted.size() <= i;

            oldText.push_back({editFmt(lhs.kind, lhs.item, true), true});
            newText.push_back(
                {editFmt(rhs.kind, rhs.item, false),
                 !sideBySide && rhs.kind == sek::Insert});

            if (!lhsDefault && !rhsDefault && lhs.kind == sek::Delete
                && rhs.kind == sek::Insert) {
                oldText.back().text.append(oldSeq[lhs.item]);
                newText.back().text.append(newSeq[rhs.item]);
            } else if (rhs.kind == sek::Insert) {
                newText.back().text.append(newSeq[rhs.item]);
            } else if (lhs.kind == sek::Delete) {
                oldText.back().text.append(oldSeq[lhs.item]);
            } else {
                oldText.back().text.append(oldSeq[lhs.item]);
                newText.back().text.append(newSeq[rhs.item]);
            }

            lhsMax = std::max<int>(oldText.back().text.size(), lhsMax);
        }

        Str  result;
        bool first = true;
        for (const auto& [lhs, rhs] : zip(oldText, newText)) {
            if (lhs != nullptr && rhs != nullptr) {
                if (!first) {
                    result.append("\n");
                }
                first = false;

                if (sideBySide) {
                    result.append(left_aligned(lhs->text, lhsMax + 3));
                    result.append(rhs->text);
                } else {
                    result.append(lhs->text);
                    if (rhs->changed) {
                        result.append("\n");
                        result.append(rhs->text);
                    }
                }
            }
        }
    }
};

Vec<Str> split_keep_separator(const Str& str, IntSet<char> sep = {' '}) {
    Vec<Str> result;
    int      prev = 0, curr = 0;
    while (curr < str.length()) {
        if (sep.contains(str[curr])) {
            if (prev != curr) {
                result.push_back(str.substr(prev, curr - prev));
            }
            prev = curr;
            while (curr < str.length() - 1 && str[curr + 1] == str[curr]) {
                curr++;
            }
            result.push_back(str.substr(prev, curr - prev + 1));
            curr++;
            prev = curr;
        } else {
            curr++;
        }
    }
    if (prev < curr) {
        result.push_back(str.substr(prev, curr - prev));
    }
    return result;
}

/// Diff formatting configuration
struct DiffFormatConf {
    /// Max number of the unchanged lines after which they will be no
    /// longer show. Can be used to compact large diffs with small
    /// mismatched parts.
    ///
    /// By default set to high int in order to avoid hiding lines
    int maxUnchanged = high<int>();
    /// Max number of the unchanged words in a single line. Can be used to
    /// compact long lines with small mismatches
    int maxUnchangedWords = high<int>();
    /// Show line numbers in the generated diffs
    bool showLines = false;
    /// Show line diff with side-by-side (aka github 'split' view) or on
    /// top of each other (aka 'unified')
    bool sideBySide = false;
    /// If diff contains invisible characters - trailing whitespaces,
    /// control characters, escapes and ANSI SGR formatting - show them
    /// directly.
    bool explainInvisible = true;
    /// Text to separate words in the inline split
    ColText inlineDiffSeparator;
    /// For multiline edit operations - group consecutive Edit operations
    /// into single chunks.
    bool groupLine = true;
    /// For inline edit operations - group consecutive edit operations into
    /// single chunks.
    bool groupInline = true;
    /// Format mismatched text. `mode` is the mismatch kind, `secondary` is
    /// used for `sekChanged` to annotated which part was deleted and which
    /// part was added.
    Func<ColText(CR<Str>, SeqEditKind, SeqEditKind, bool)> formatChunk =
        [](CR<Str>     word,
           SeqEditKind mode,
           SeqEditKind secondary,
           bool        isInline) {
            using fg = TermColorFg8Bit;
            switch (mode) {
                case SeqEditKind::Delete: return merge(fg::Red, word);
                case SeqEditKind::Insert: return merge(fg::Green, word);
                case SeqEditKind::Keep: return merge(fg::Default, word);
                case SeqEditKind::None: return merge(fg::Default, word);
                case SeqEditKind::Replace:
                case SeqEditKind::Transpose:
                    if (isInline && secondary == SeqEditKind::Delete) {
                        return "[" + merge(fg::Yellow, word) + " -> ";
                    } else if (
                        isInline && secondary == SeqEditKind::Insert) {
                        return merge(fg::Yellow, word) + "]";
                    } else {
                        return merge(fg::Yellow, word);
                    }
            }
        };
    /// Split line into chunks for formatting
    Func<Vec<Str>(CR<Str>)> lineSplit = [](CR<Str> a) -> Vec<Str> {
        return split_keep_separator(a, '\n');
    };
    /// Convert invisible character (whitespace or control) to
    /// human-readable representation -
    Func<Str(char)> explainChar = [](char ch) -> Str {
        const auto [uc, ascii] = visibleName(ch);
        return uc;
    };


    /// Format text mismatch chunk using `formatChunk` callback
    ColText chunk(
        Str         text,
        SeqEditKind mode,
        SeqEditKind secondary,
        bool        isInline) {
        return formatChunk(text, mode, secondary, isInline);
    }
};


//! Generate colored formatting for the levenshtein edit operation using
//! format configuration. Return old formatted line and new formatted
//! line.
template <typename T>
Pair<ColText, ColText> formatDiffed(
    const Vec<SeqEdit>&   ops,
    const Vec<T>&         oldSeq,
    const Vec<T>&         newSeq,
    const DiffFormatConf& conf) {

    using sek              = SeqEditKind;
    int          unchanged = 0;
    Vec<ColText> oldLine, newLine;
    for (int idx = 0; idx < ops.size(); ++idx) {
        const SeqEdit& op = ops[idx];
        switch (op.kind) {
            case sek::Keep:
                if (unchanged < conf.maxUnchanged) {
                    oldLine.push_back(
                        conf.chunk(oldSeq[op.sourcePos], sek::Keep));
                    newLine.push_back(
                        conf.chunk(newSeq[op.targetPos], sek::Keep));
                    ++unchanged;
                }
                break;
            case sek::Delete:
                oldLine.push_back(
                    conf.chunk(oldSeq[op.sourcePos], sek::Delete));
                unchanged = 0;
                break;
            case sek::Insert:
                newLine.push_back(
                    conf.chunk(newSeq[op.targetPos], sek::Insert));
                unchanged = 0;
                break;
            case sek::Replace:
                oldLine.push_back(conf.chunk(
                    oldSeq[op.sourcePos], sek::Replace, sek::Delete));
                newLine.push_back(conf.chunk(
                    newSeq[op.targetPos], sek::Replace, sek::Insert));
                unchanged = 0;
                break;
            case sek::None:
                assert(false && "Original formatting sequence should not contain 'none' fillers");
                break;
            case sek::Transpose: break;
        }
    }

    return {
        join(conf.inlineDiffSeparator, oldLine),
        join(conf.inlineDiffSeparator, newLine)};
}


template <typename T>
Pair<int, Vec<SeqEdit>> levenshteinDistance(
    const Vec<T>& str1,
    const Vec<T>& str2) {
    int l1 = str1.size();
    int l2 = str2.size();

    Vec<Vec<int>>                 m(l1 + 1, Vec<int>(l2 + 1, 0));
    Vec<Vec<std::pair<int, int>>> paths(
        l1 + 1, Vec<std::pair<int, int>>(l2 + 1, {0, 0}));

    for (int i = 0; i <= l1; ++i) {
        m[i][0]     = i;
        paths[i][0] = {i - 1, 0};
    }

    for (int j = 0; j <= l2; ++j) {
        m[0][j]     = j;
        paths[0][j] = {0, j - 1};
    }

    for (int i = 1; i <= l1; ++i) {
        for (int j = 1; j <= l2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                m[i][j]     = m[i - 1][j - 1];
                paths[i][j] = {i - 1, j - 1};
            } else {
                int min_val = std::min(
                    {m[i - 1][j], m[i][j - 1], m[i - 1][j - 1]});
                m[i][j] = min_val + 1;
                if (m[i - 1][j] == min_val) {
                    paths[i][j] = {i - 1, j};
                } else if (m[i][j - 1] == min_val) {
                    paths[i][j] = {i, j - 1};
                } else if (m[i - 1][j - 1] == min_val) {
                    paths[i][j] = {i - 1, j - 1};
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

    int i = l1, j = l2;
    while (i >= 0 && j >= 0) {
        j = l2;
        while (i >= 0 && j >= 0) {
            levenpath.emplace_back(i, j, SeqEditKind::None);
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


template <
    typename T,
    int MatchBufferSize        = 256,
    typename MatchPositionType = int>
struct FuzzyMatcher {
    Func<bool(CR<T>, CR<T>)> isEqual;
    Func<bool(CR<T>)>        isSeparator;

    int recursionLimit = 10;
    /// bonus for adjacent matches
    int sequential_bonus = 15;
    /// bonus if match occurs after a separator
    int separator_bonus = 30;
    /// bonus if match is uppercase and prev is lower
    int camel_bonus = 30;
    /// bonus if the first letter is matched
    int first_letter_bonus = 15;
    /// penalty applied for every letter in str before the first match
    int leading_letter_penalty = -5;
    /// maximum penalty for leading letters
    int max_leading_letter_penalty = -15;
    /// penalty for every letter that doesn't matter
    int unmatched_letter_penalty = -1;
    int start_score              = 100;

    Array<MatchPositionType, MatchBufferSize> matches;

    bool fuzzy_match_recursive(
        Span<T>                  pattern,
        Span<T>                  str,
        int&                     outScore,
        Span<T>                  strBegin,
        const MatchPositionType* srcMatches,
        MatchPositionType*       matches,
        int                      nextMatch,
        int&                     recursionCount) {
        // Count recursions
        ++recursionCount;
        if (recursionLimit <= recursionCount) {
            return false;
        }

        // Detect end of strings
        if (!pattern.hasData() || !str.hasData()) {
            return false;
        }

        // Recursion params
        bool              recursiveMatch = false;
        MatchPositionType bestRecursiveMatches[MatchBufferSize];
        int               bestRecursiveScore = 0;

        // Loop through pattern and str looking for a match
        bool first_match = true;
        while (pattern.hasData() && str.hasData()) {

            // Found match
            if (this->isEqual(pattern.front(), str.front())) {

                // Supplied matches buffer was too short
                if (MatchBufferSize <= nextMatch) {
                    return false;
                }

                // "Copy-on-Write" srcMatches into matches
                if (first_match && srcMatches) {
                    memcpy(matches, srcMatches, nextMatch);
                    first_match = false;
                }

                // Recursive call that "skips" this match
                MatchPositionType recursiveMatches[MatchBufferSize];
                int               recursiveScore;
                str.moveStart(1);
                if (fuzzy_match_recursive(
                        pattern,
                        str,
                        recursiveScore,
                        strBegin,
                        matches,
                        recursiveMatches,
                        nextMatch,
                        recursionCount)) {

                    // Pick best recursive score
                    if (!recursiveMatch
                        || bestRecursiveScore < recursiveScore) {
                        memcpy(
                            bestRecursiveMatches,
                            recursiveMatches,
                            MatchBufferSize);
                        bestRecursiveScore = recursiveScore;
                    }
                    recursiveMatch = true;
                }

                // Advance
                matches[nextMatch++] = std::distance(
                    str.data(), strBegin.data());
                pattern.moveStart(1);
            }
            str.moveStart(1);
        }

        // Determine if full pattern was matched
        bool matched = !pattern.hasData();

        // Calculate score
        if (matched) {

            // Iterate str to end
            while (str.hasData()) {
                str.moveStart(1);
            }

            // Initialize score
            outScore = start_score;

            // Apply leading letter penalty
            int penalty = leading_letter_penalty * matches[0];
            if (penalty < max_leading_letter_penalty) {
                penalty = max_leading_letter_penalty;
            }
            outScore += penalty;

            // Apply unmatched penalty
            int unmatched = std::distance(str.data(), strBegin.data())
                          - nextMatch;
            outScore += unmatched_letter_penalty * unmatched;

            // Apply ordering bonuses
            for (int i = 0; i < nextMatch; ++i) {
                MatchPositionType currIdx = matches[i];

                if (i > 0) {
                    MatchPositionType prevIdx = matches[i - 1];

                    // Sequential
                    if (currIdx == (prevIdx + 1)) {
                        outScore += sequential_bonus;
                    }
                }

                // Check for bonuses based on neighbor character value
                if (0 < currIdx) {
                    // Camel case
                    const T& neighbor = strBegin[currIdx - 1];
                    const T& curr     = strBegin[currIdx];
                    // TODO implement in generic manner
                    // if (neighbor.isLower() && curr.isLower()) {
                    //     outScore += camel_bonus;
                    // }

                    // Separator
                    if (isSeparator(neighbor)) {
                        outScore += separator_bonus;
                    }
                } else {
                    // First letter
                    outScore += first_letter_bonus;
                }
            }
        }

        // Return best result
        if (recursiveMatch
            && (!matched || outScore < bestRecursiveScore)) {
            // Recursive score is better than "this"
            memcpy(matches, bestRecursiveMatches, MatchBufferSize);
            outScore = bestRecursiveScore;
            return true;
        } else if (matched) {
            // "this" score is better than recursive
            return true;
        } else {
            // no match
            return false;
        }
    }


    bool fuzzy_match(
        Span<T>            pattern,
        Span<T>            str,
        int&               outScore,
        MatchPositionType* matches) {
        int recursionCount = 0;

        return fuzzy_match_recursive(
            pattern,
            str,
            outScore,
            str,
            nullptr,
            matches,
            0,
            recursionCount);
    }

    bool fuzzy_match(Span<T> pattern, Span<T> str, int& outScore) {
        return fuzzy_match(pattern, str, outScore, &matches[0]);
    }

    int get_score(Span<T> item, Span<T> pattern) {
        int score;
        if (fuzzy_match(pattern, item, score)) {
            return score;
        } else {
            return -1;
        }
    }
};
