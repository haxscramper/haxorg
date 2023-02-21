#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <hstd/system/reflection.hpp>

struct BacktrackRes {
    Vec<int> lhsIndex = {};
    Vec<int> rhsIndex = {};
};

BOOST_DESCRIBE_STRUCT(BacktrackRes, (), (lhsIndex, rhsIndex));

inline std::ostream& operator<<(
    std::ostream&       os,
    BacktrackRes const& value) {
    return os << described_class_printer(os, value);
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

template <>
inline SeqEditKind low() {
    return SeqEditKind::None;
}

template <>
inline SeqEditKind high() {
    return SeqEditKind::Transpose;
}

inline Str toPrefix(SeqEditKind kind) {
    switch (kind) {
        case SeqEditKind::None: return "?";
        case SeqEditKind::Keep: return "~";
        case SeqEditKind::Insert: return "+";
        case SeqEditKind::Replace: return "-+";
        case SeqEditKind::Delete: return "-";
        case SeqEditKind::Transpose: return "^v";
    }
}

inline ColStyle toStyle(SeqEditKind kind) {
    switch (kind) {
        case SeqEditKind::None: return TermColorFg8Bit::Default;
        case SeqEditKind::Keep: return TermColorFg8Bit::Default;
        case SeqEditKind::Insert: return TermColorFg8Bit::Green;
        case SeqEditKind::Replace: return TermColorFg8Bit::Yellow;
        case SeqEditKind::Delete: return TermColorFg8Bit::Red;
        case SeqEditKind::Transpose: return TermColorFg8Bit::Yellow;
    }
}

struct SeqEdit {
    SeqEditKind kind;      /// Sequence edit operation kind
    int         sourcePos; /// Position in the original sequence
    int         targetPos; /// Position in the target sequence

    SeqEdit(SeqEditKind kind, int sourcePos = -1, int targetPos = -1)
        : kind(kind), sourcePos(sourcePos), targetPos(targetPos) {}
};


/// Diff formatting configuration
struct DiffFormatConf {
    /// Max number of the unchanged lines after which they will be no
    /// longer show. Can be used to compact large diffs with small
    /// mismatched parts.
    ///
    /// By default set to high int in order to avoid hiding lines
    int maxUnchanged = high<int>();
    /// Max number of the unchanged words in a single line. Can be used
    /// to compact long lines with small mismatches
    int maxUnchangedWords = high<int>();
    /// Show line numbers in the generated diffs
    bool showLines = false;
    /// Show line diff with side-by-side (aka github 'split' view) or
    /// on top of each other (aka 'unified')
    bool sideBySide = true;
    /// If diff contains invisible characters - trailing whitespaces,
    /// control characters, escapes and ANSI SGR formatting - show them
    /// directly.
    bool explainInvisible = true;
    /// Text to separate words in the inline split
    ColText inlineDiffSeparator;
    /// For multiline edit operations - group consecutive Edit
    /// operations into single chunks.
    bool groupLine = false;
    /// For inline edit operations - group consecutive edit operations
    /// into single chunks.
    bool groupInline = true;
    /// Piece of text that is placed into resulting sequence in place of
    /// 'None' operation -- empty space that does not correspond to any
    /// sequence edit operation.
    ColText emptyChunk;
    /// Format mismatched text. `mode` is the mismatch kind,
    /// `secondary` is used for `sekChanged` to annotated which part
    /// was deleted and which part was added.
    Func<ColText(CR<Str>, SeqEditKind, SeqEditKind, bool)> formatChunk =
        [](CR<Str>     word,
           SeqEditKind mode,
           SeqEditKind secondary,
           bool        isInline) {
            using fg = TermColorFg8Bit;
            switch (mode) {
                case SeqEditKind::Delete: return ColText(fg::Red, word);
                case SeqEditKind::Insert: return ColText(fg::Green, word);
                case SeqEditKind::Keep: return ColText(fg::Default, word);
                case SeqEditKind::None: return ColText(fg::Default, word);
                case SeqEditKind::Replace:
                case SeqEditKind::Transpose:
                    if (isInline && secondary == SeqEditKind::Delete) {
                        return "[" + ColText(fg::Yellow, word) + " -> ";
                    } else if (
                        isInline && secondary == SeqEditKind::Insert) {
                        return ColText(fg::Yellow, word) + "]";
                    } else {
                        return ColText(fg::Yellow, word);
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
        bool        isInline = false) const {
        return formatChunk(text, mode, secondary, isInline);
    }

    /// Check if config is used to build unified diff
    bool unified() const { return !sideBySide; }
};


/// TODO use 'indexable' concept that will work with stdlib vectors,
/// arrays, other data structures, plain text blocks, wide strings and so
/// on.
template <typename T>
Vec<BacktrackRes> longestCommonSubsequence(
    CVec<T>                   lhs,
    CVec<T>                   rhs,
    Func<bool(CR<T>, CR<T>)>  itemCmp,
    Func<float(CR<T>, CR<T>)> itemEqualityMetric) {

    if (lhs.empty() || rhs.empty()) {
        return {{}};
    }

    UnorderedMap<Pair<int, int>, float> mem;
    Func<float(int, int)>               lcs;
    lcs = [&](int lhsIdx, int rhsIdx) -> float {
        if (mem.count({lhsIdx, rhsIdx}) == 0) {
            if (lhsIdx == -1 || rhsIdx == -1) {
                mem[{lhsIdx, rhsIdx}] = 0;
            } else if (itemCmp(lhs[lhsIdx], rhs[rhsIdx])) {
                mem[{lhsIdx, rhsIdx}] = lcs(lhsIdx - 1, rhsIdx - 1)
                                      + itemEqualityMetric(
                                            lhs[lhsIdx], rhs[rhsIdx]);
            } else {
                mem[{lhsIdx, rhsIdx}] = std::max(
                    lcs(lhsIdx, rhsIdx - 1), lcs(lhsIdx - 1, rhsIdx));
            }
        }

        return mem[{lhsIdx, rhsIdx}];
    };

    int m = lhs.size() - 1;
    int n = rhs.size() - 1;

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
        } else if (itemCmp(lhs[lhsIdx], rhs[rhsIdx])) {
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

    return backtrack(m, n);
}


template <typename T>
Vec<BacktrackRes> longestCommonSubsequence(
    CVec<T>                  lhs,
    CVec<T>                  rhs,
    Func<bool(CR<T>, CR<T>)> itemCmp) {
    return longestCommonSubsequence<T>(
        lhs, rhs, itemCmp, [&itemCmp](CR<T> lhs, CR<T> rhs) -> float {
            return itemCmp(lhs, rhs) ? 1.0 : 0.0;
        });
}

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
generator<Pair<T const*, T const*>> zip(CVec<T> lhs, CVec<T> rhs) {
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

template <typename T>
struct ZipToMaxResult {
    T    lhs;
    T    rhs;
    bool rhsDefault;
    bool lhsDefault;
    int  idx;
};


/// Iterate each argument to the end, filling in missing values with `fill`
/// argument. This is an opposite of the std built-in `zip` which iterates
/// up until `min(lhs.len, rhs.len)`.
template <typename T>
generator<ZipToMaxResult<T>> zipToMax(
    CVec<T> lhs,
    CVec<T> rhs,
    T       fill = T()) {
    int idx = 0;
    while (idx < std::max(lhs.size(), rhs.size())) {
        if (idx < lhs.size() && idx < rhs.size()) {
            co_yield {lhs[idx], rhs[idx], false, false, idx};
        } else if (idx < lhs.size()) {
            co_yield {lhs[idx], fill, false, true, idx};
        } else {
            co_yield {fill, rhs[idx], true, false, idx};
        }
        ++idx;
    }
}

struct LevenshteinDistanceResult {
    int          score;
    Vec<SeqEdit> operations;
};

template <typename T>
LevenshteinDistanceResult levenshteinDistance(Span<T> str1, Span<T> str2) {
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

Const<CharSet> Invis{slice('\x00', '\x1F'), '\x7F'};


inline bool scanInvisible(CR<Str> text, CharSet& invisSet) {
    // Scan string for invisible characters from right to left,
    // updating active invisible set as needed.
    for (int chIdx = text.length() - 1; chIdx >= 0; --chIdx) {
        // If character is in the 'invisible' set return true
        if (invisSet.contains(text[chIdx])) {
            return true;
        } else {
            // Otherwise reset to the default set - this ensures that
            // we react to trailing whitespace only if is the rightmost
            // character.
            invisSet = Invis;
        }
    }
    return false;
}


inline bool hasInvisibleChanges(
    Vec<SeqEdit>& diff,
    Vec<Str>&     oldSeq,
    Vec<Str>&     newSeq) {
    // Is any change in the edit sequence invisible?
    IntSet<char> start = Invis + ' ';

    auto invis = [&start](Str text) { return scanInvisible(text, start); };

    // Iterate over all edits from right to left, updating active set of
    // invisible characters as we got.
    int idx = diff.size() - 1;
    while (idx >= 0) {
        SeqEdit& edit = diff[idx];
        switch (edit.kind) {
            case SeqEditKind::Delete:
                if (invis(oldSeq[edit.sourcePos])) {
                    return true;
                }
                break;
            case SeqEditKind::Insert:
                if (invis(newSeq[edit.targetPos])) {
                    return true;
                }
                break;
            case SeqEditKind::None:
            case SeqEditKind::Transpose: break;
            case SeqEditKind::Keep:
                // Check for kept characters - this will update 'invisible'
                // set if any found, so edits like `" X" -> "X"` are not
                // considered as 'has invisible'
                if (invis(oldSeq[edit.sourcePos])) {}
                break;
            case SeqEditKind::Replace:
                if (invis(oldSeq[edit.sourcePos])
                    || invis(newSeq[edit.targetPos])) {
                    return true;
                }
                break;
        }
        idx--;
    }
    return false;
}

inline bool hasInvisible(
    std::string  text,
    IntSet<char> startSet = Invis + CharSet{' '}) {
    // Does string have significant invisible characters?
    IntSet<char> invisSet = startSet;
    if (scanInvisible(text, invisSet)) {
        return true;
    }
    return false;
}

inline bool hasInvisible(CR<Vec<Str>> text) {
    // Do any of strings in text have signficant invisible characters.
    IntSet<char> invisSet = Invis + CharSet{' '};
    for (int idx = text.size() - 1; idx >= 0; idx--) {
        // Iterate over all items from right to left - until we find the
        // first visible character, space is also considered significant,
        // but removed afterwards, so `" a"/"a"` is not considered to have
        // invisible characters.
        if (scanInvisible(text[idx], invisSet)) {
            return true;
        }
    }
    return false;
}

inline Str toVisibleNames(CR<DiffFormatConf> conf, const Str& str) {
    Str result;
    // Convert all characters in the string into visible ones
    for (const char& ch : str) {
        result += conf.explainChar(ch);
    }
    return result;
}

inline Vec<Str> toVisibleNames(
    CR<DiffFormatConf> conf,
    const Vec<Str>&    split) {
    Vec<Str> result;
    // Convert all characters in all strings into visible ones.
    if (split.size() > 0) {
        for (const Str& part : split) {
            result.push_back(toVisibleNames(conf, part));
        }
    }
    return result;
}


/// \brief Intermediate version of shifted diff sequences.
struct ShiftedDiff {
    struct Item {
        SeqEditKind kind;
        int         item;
    };

    Vec<Item> oldShifted;
    Vec<Item> newShifted;

    /// \brief Construct shifted diff pairing from LCS trace information
    inline ShiftedDiff(CR<BacktrackRes> track, int oldMax, int newMax) {
        using sek = SeqEditKind;
        if (!track.lhsIndex.empty()) {
            int fullSize = std::max(oldMax, newMax);
            int prevLhs  = 0;
            int prevRhs  = 0;
            for (int pos = 0; pos < track.lhsIndex.size(); ++pos) {
                int lhsPos = track.lhsIndex.at(pos);
                int rhsPos = track.rhsIndex.at(pos);
                for (int i = prevLhs; i < lhsPos; ++i) {
                    newShifted.push_back(Item{sek::None, 0});
                    oldShifted.push_back(Item{sek::Delete, i});
                }

                for (int i = prevRhs; i < rhsPos; ++i) {
                    newShifted.push_back(Item{sek::Insert, i});
                    oldShifted.push_back(Item{sek::None, i});
                }

                newShifted.push_back(Item{sek::Keep, rhsPos});
                oldShifted.push_back(Item{sek::Keep, lhsPos});
                prevLhs = lhsPos + 1;
                prevRhs = rhsPos + 1;
            }
        }
    }

    inline ShiftedDiff(CR<Vec<SeqEdit>>& diff) {
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
};

struct BufItem {
    int         originalIndex;
    bool        changed;
    SeqEditKind kind;

    Opt<int> lineIndex;
};


template <typename T>
Pair<ColText, ColText> formatDiffed(
    const Vec<SeqEdit>&   ops,
    Span<T>               oldSeq,
    Span<T>               newSeq,
    const DiffFormatConf& conf = DiffFormatConf{}) {
    int unchanged = 0;
    using sek     = SeqEditKind;
    Vec<ColText> oldLine;
    Vec<ColText> newLine;
    for (int i = 0; i < ops.size(); ++i) {
        switch (ops[i].kind) {
            case sek::None:
                oldLine.push_back(conf.emptyChunk);
                newLine.push_back(conf.emptyChunk);
                break;

            case sek::Keep:
                if (unchanged < conf.maxUnchanged) {
                    oldLine.push_back(conf.chunk(
                        oldSeq[ops[i].sourcePos], sek::Keep, sek::Keep));
                    newLine.push_back(conf.chunk(
                        newSeq[ops[i].targetPos], sek::Keep, sek::Keep));
                    ++unchanged;
                }
                break;
            case sek::Delete:
                oldLine.push_back(conf.chunk(
                    oldSeq[ops[i].sourcePos], sek::Delete, sek::Delete));
                unchanged = 0;
                break;
            case sek::Insert:
                newLine.push_back(conf.chunk(
                    newSeq[ops[i].targetPos], sek::Insert, sek::Insert));
                unchanged = 0;
                break;
            case sek::Replace:
                oldLine.push_back(conf.chunk(
                    oldSeq[ops[i].sourcePos], sek::Replace, sek::Delete));
                newLine.push_back(conf.chunk(
                    newSeq[ops[i].targetPos], sek::Replace, sek::Insert));
                unchanged = 0;
                break;
            case sek::Transpose: break;
        }
    }

    return {
        join(conf.inlineDiffSeparator, oldLine),
        join(conf.inlineDiffSeparator, newLine)};
}


inline Pair<ColText, ColText> formatLineDiff(
    const Str&            oldLine,
    const Str&            newLine,
    const DiffFormatConf& conf) {
    // Format single line diff into oldLine/newLine line edits. Optionally
    // explain all differences using options from `conf`

    auto oldLineSplit = conf.lineSplit(oldLine);
    auto newLineSplit = conf.lineSplit(newLine);
    auto diffed = levenshteinDistance<Str>(oldLineSplit, newLineSplit);

    ColText oldLineLine, newLineLine;

    if (conf.explainInvisible
        && (hasInvisibleChanges(
                diffed.operations, oldLineSplit, newLineSplit)
            || hasInvisible(oldLineSplit) || hasInvisible(newLineSplit))) {

        auto oldVisible = toVisibleNames(conf, oldLineSplit);
        auto newVisible = toVisibleNames(conf, newLineSplit);

        const auto& [oldLineLine, newLineLine] = formatDiffed(
            diffed.operations,
            oldVisible.toSpan(),
            newVisible.toSpan(),
            conf);

    } else {
        const auto& [oldLineLine, newLineLine] = formatDiffed(
            diffed.operations,
            oldLineSplit.toSpan(),
            newLineSplit.toSpan(),
            conf);
    }

    return {oldLineLine, newLineLine};
}

struct FormattedDiff {
    /// Single line of unified/stacked diff
    struct DiffLine {
        /// Visible numeration on the resulting line
        Opt<int> lineIndex;
        /// Type of the line operation
        SeqEditKind prefix;
        /// Whether line represents element from the lhs sequence of rhs
        /// one
        bool isLhs;

        bool     empty() const { return prefix == SeqEditKind::None; }
        Opt<int> index() const {
            if (empty()) {
                return std::nullopt;
            } else {
                return originalIndex;
            }
        }

        /// Index of the item in original (lhs/rhs) sequence
        int originalIndex = -1;
    };

    struct StackedDiff {
        Vec<DiffLine> elements;
    };

    struct UnifiedDiff {
        Vec<DiffLine> lhs;
        Vec<DiffLine> rhs;
    };

    Variant<StackedDiff, UnifiedDiff> content;

    StackedDiff&       stacked() { return std::get<StackedDiff>(content); }
    UnifiedDiff&       unified() { return std::get<UnifiedDiff>(content); }
    StackedDiff const& stacked() const {
        return std::get<StackedDiff>(content);
    }
    UnifiedDiff const& unified() const {
        return std::get<UnifiedDiff>(content);
    }

    int maxLineNumber() const {
        int result = 0;
        if (isUnified()) {
            for (const auto& it : unified().lhs) {
                if (it.lineIndex.has_value()) {
                    result = std::max(result, it.lineIndex.value());
                }
            }
            for (const auto& it : unified().rhs) {
                if (it.lineIndex.has_value()) {
                    result = std::max(result, it.lineIndex.value());
                }
            }
        } else {
            for (const auto& it : stacked().elements) {
                if (it.lineIndex.has_value()) {
                    result = std::max(result, it.lineIndex.value());
                }
            }
        }
        return result;
    }

    bool isUnified() const {
        return std::holds_alternative<UnifiedDiff>(content);
    }

    generator<DiffLine> stackedLines() {
        for (const auto& line : stacked().elements) {
            co_yield line;
        }
    }

    generator<Pair<DiffLine, DiffLine>> unifiedLines() {
        assert(unified().lhs.size() == unified().rhs.size());
        for (int i = 0; i < unified().lhs.size(); ++i) {
            co_yield {unified().lhs.at(i), unified().rhs.at(i)};
        }
    }

    FormattedDiff(
        const ShiftedDiff& shifted,
        DiffFormatConf     conf = DiffFormatConf{}) {
        Vec<BufItem> oldText, newText;

        using sek     = SeqEditKind;
        int unchanged = 0;

        for (auto [lhs, rhs, lhsDefault, rhsDefault, idx] :
             zipToMax(shifted.oldShifted, shifted.newShifted)) {
            if (lhs.kind == sek::Keep && rhs.kind == sek::Keep) {
                if (unchanged < conf.maxUnchanged) {
                    ++unchanged;
                } else {
                    continue;
                }
            } else {
                unchanged = 0;
            }
            // Start new entry on the old line
            oldText.push_back(BufItem{
                .originalIndex = lhs.item,
                // Only case where lhs can have unchanged lines is for
                // unified diff+filler
                .changed = conf.unified() && lhs.kind != sek::None,
                .kind    = lhs.kind});

            // New entry on the new line
            newText.push_back(BufItem{
                .originalIndex = rhs.item,
                // Only newly inserted lines need to be formatted for the
                // unified diff, everything else is displayed on the
                // 'original' version.
                .changed = conf.unified() && rhs.kind == sek::Insert,
                .kind    = rhs.kind});
        }

        *this = FormattedDiff(oldText, newText, conf);
    }

    FormattedDiff(
        const Vec<BufItem>&   oldText,
        const Vec<BufItem>&   newText,
        const DiffFormatConf& conf = DiffFormatConf{}) {
        bool first = true;

        if (conf.groupLine) {
            assert(!conf.sideBySide);
            // Grouping line edits is not possible in the side-by-side
            // representation, so going directly for unified one.
            Vec<BufItem> lhsBuf = {oldText[0]};
            Vec<BufItem> rhsBuf = {newText[0]};

            auto addBuffers = [this, &lhsBuf, &rhsBuf]() {
                for (const BufItem& line : lhsBuf) {
                    if (line.changed) {
                        stacked().elements.push_back(
                            {.lineIndex     = line.lineIndex,
                             .prefix        = line.kind,
                             .isLhs         = true,
                             .originalIndex = line.originalIndex});
                    }
                }

                for (const BufItem& line : rhsBuf) {
                    if (line.changed) {
                        stacked().elements.push_back(
                            {.lineIndex     = line.lineIndex,
                             .prefix        = line.kind,
                             .isLhs         = false,
                             .originalIndex = line.originalIndex});
                    }
                }
            };

            for (auto it = oldText.begin() + 1, jt = newText.begin() + 1;
                 it != oldText.end() - 1;
                 ++it, ++jt) {
                if (it->kind != lhsBuf.back().kind
                    || jt->kind != rhsBuf.back().kind) {
                    // If one of the edit streaks finished, dump both
                    // results to output and continue
                    //
                    // - removed + added    - removed
                    // - removed + added    - removed
                    // - removed ?          + added
                    // ~ kept    ~ kept     + added
                    // ~ kept    ~ kept     - removed
                    //                      ~ kept
                    //                      ~ kept
                    addBuffers();
                    lhsBuf = {*it};
                    rhsBuf = {*jt};
                } else {
                    lhsBuf.push_back(*it);
                    rhsBuf.push_back(*jt);
                }
            }

            addBuffers();

        } else {
            // Ungrouped lines either with unified or side-by-side
            // representation
            int lhsMax = 0;
            content    = FormattedDiff::UnifiedDiff{};

            for (auto oldIt = oldText.begin(), newIt = newText.begin();
                 oldIt != oldText.end();
                 ++oldIt, ++newIt) {
                if (conf.sideBySide) {
                    unified().lhs.push_back(FormattedDiff::DiffLine{
                        .originalIndex = oldIt->originalIndex,
                        .isLhs         = true,
                        .prefix        = oldIt->kind,
                        .lineIndex     = oldIt->lineIndex});

                    unified().rhs.push_back(FormattedDiff::DiffLine{
                        .originalIndex = newIt->originalIndex,
                        .isLhs         = false,
                        .prefix        = newIt->kind,
                        .lineIndex     = newIt->lineIndex});
                } else {
                    unified().lhs.push_back(FormattedDiff::DiffLine{
                        .originalIndex = oldIt->originalIndex,
                        .isLhs         = true,
                        .prefix        = oldIt->kind,
                        .lineIndex     = oldIt->lineIndex});

                    if (newIt->changed) {
                        unified().rhs.push_back(FormattedDiff::DiffLine{
                            .originalIndex = newIt->originalIndex,
                            .isLhs         = false,
                            .prefix        = newIt->kind,
                            .lineIndex     = newIt->lineIndex});
                    }
                }
            }
        }
    }
};


inline ColText formatInlineDiff(
    const Vec<Str>&     src,
    const Vec<Str>&     target,
    const Vec<SeqEdit>& diffed,
    DiffFormatConf      conf) {
    CharSet      start = Invis + CharSet{' '};
    Vec<ColText> chunks;

    auto push = [&](const Str&  text,
                    SeqEditKind mode,
                    SeqEditKind secondary,
                    bool        toLast   = false,
                    bool        isInline = false) {
        ColText chunk;
        if (conf.explainInvisible && scanInvisible(text, start)) {
            chunk = conf.chunk(
                toVisibleNames(conf, text), mode, secondary, isInline);
        } else {
            chunk = conf.chunk(text, mode, secondary, isInline);
        }

        if (toLast) {
            chunks.back().append(chunk);
        } else {
            chunks.push_back(chunk);
        }
    };

    Vec<Span<SeqEdit const>> groups;
    if (conf.groupInline) {
        groups = partition<SeqEdit, SeqEditKind>(
            diffed, [](CR<SeqEdit> edit) { return edit.kind; });
    } else {
        for (int i = 0; i < diffed.size(); ++i) {
            groups[i] = {diffed[slice(i, i)]};
        }
    }

    using sek = SeqEditKind;
    int gIdx  = groups.size() - 1;
    while (0 <= gIdx) {
        switch (groups[gIdx][0].kind) {
            case sek::Keep: {
                Str buf;
                for (const auto& op : groups[gIdx]) {
                    buf.append(src[op.sourcePos]);
                }
                push(buf, sek::Keep, sek::Keep);
                break;
            }
            case sek::None:
            case sek::Transpose: break;
            case sek::Insert: {
                Str buf;
                for (const auto& op : groups[gIdx]) {
                    buf.append(target[op.targetPos]);
                }
                push(buf, sek::Insert, sek::Insert);
                break;
            }
            case sek::Delete: {
                Str buf;
                for (const auto& op : groups[gIdx]) {
                    buf.append(src[op.sourcePos]);
                }
                push(buf, sek::Delete, sek::Delete);
                break;
            }
            case sek::Replace: {
                Str sourceBuf, targetBuf;
                for (const auto& op : groups[gIdx]) {
                    sourceBuf.append(src[op.sourcePos]);
                    targetBuf.append(target[op.targetPos]);
                }
                push(sourceBuf, sek::Replace, sek::Delete, true);
                push(targetBuf, sek::Replace, sek::Insert, true, true);
                break;
            }
        }
        gIdx--;
    }

    // Because we iterated from right to left, all edit operations are
    // placed in reverse as well, so this needs to be fixed
    return join(conf.inlineDiffSeparator, chunks);
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

        // Detect end of Strs
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

template <typename T>
ColText formatDiffed(
    const Vec<T>&                  oldSeq,
    const Vec<T>&                  newSeq,
    const DiffFormatConf&          conf = DiffFormatConf{},
    Func<bool(const T&, const T&)> eqCmp =
        [](const T& a, const T& b) { return a == b; },
    Func<Str(const T&)> strConv =
        [](const T& a) { return to_string(a); }) {

    auto          diff = myersDiff(oldSeq, newSeq, eqCmp);
    ShiftedDiff   shifted{diff};
    FormattedDiff formatted{shifted, conf};
    return ColText{};
    // map(oldSeq, strConv), map(newSeq, strConv),
}

inline ColText formatDiffed(
    const Str&            text1,
    const Str&            text2,
    const DiffFormatConf& conf = DiffFormatConf{}) {
    return formatDiffed(split(text1, '\n'), split(text2, '\n'), conf);
}
