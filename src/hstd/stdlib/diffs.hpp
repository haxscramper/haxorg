#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/algorithms.hpp>
import hstd.stdlib.Vec;
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <hstd/system/reflection.hpp>

using std::operator""s;

struct BacktrackRes {
    Vec<int> lhsIndex = {};
    Vec<int> rhsIndex = {};
};

BOOST_DESCRIBE_STRUCT(BacktrackRes, (), (lhsIndex, rhsIndex));
REFL_DEFINE_DESCRIBED_FORMATTER(BacktrackRes);

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
struct value_domain<SeqEditKind>
    : value_domain_ungapped<
          SeqEditKind,
          SeqEditKind::None,
          SeqEditKind::Transpose> {};

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
    int maxUnchanged = value_domain<int>::high();
    /// Max number of the unchanged words in a single line. Can be used
    /// to compact long lines with small mismatches
    int maxUnchangedWords = value_domain<int>::high();
    /// Show line numbers in the generated diffs
    bool showLines = false;
    /// Show line diff with side-by-side (aka github 'split' view)
    /// or on top of each other (aka 'unified')
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
    /// 'None' operation -- empty space that does not correspond to
    /// any sequence edit operation.
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
                        return "["s + ColText(fg::Yellow, word) + " -> "s;
                    } else if (
                        isInline && secondary == SeqEditKind::Insert) {
                        return ColText(fg::Yellow, word) + "]"s;
                    } else {
                        return ColText(fg::Yellow, word);
                    }
            }
        };
    /// Split line into chunks for formatting
    Func<Vec<Str>(CR<Str>)> lineSplit = [](CR<Str> a) -> Vec<Str> {
        return split_keep_separator(a, char('\n'));
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


Vec<BacktrackRes> longestCommonSubsequence(
    int                   lhsSize,
    int                   rhsSize,
    Func<bool(int, int)>  itemCmp,
    Func<float(int, int)> itemEqualityMetric);


template <typename T>
Vec<BacktrackRes> longestCommonSubsequence(
    CVec<T>                   lhs,
    CVec<T>                   rhs,
    Func<bool(CR<T>, CR<T>)>  itemCmp,
    Func<float(CR<T>, CR<T>)> itemEqualityMetric) {
    return longestCommonSubsequence(
        lhs.size(),
        rhs.size(),
        [&lhs, &rhs, &itemCmp](int lhsIdx, int rhsIdx) -> bool {
            return itemCmp(lhs[lhsIdx], rhs[rhsIdx]);
        },
        [&lhs, &rhs, &itemEqualityMetric](
            int lhsIdx, int rhsIdx) -> float {
            return itemEqualityMetric(lhs[lhsIdx], rhs[rhsIdx]);
        });
}


template <typename T>
Vec<BacktrackRes> longestCommonSubsequence(
    CVec<T>                  lhs,
    CVec<T>                  rhs,
    Func<bool(CR<T>, CR<T>)> itemCmp) {
    return longestCommonSubsequence<T>(
        lhs,
        rhs,
        itemCmp,
        [&lhs, &rhs, &itemCmp](CR<T> lhsIt, CR<T> rhsIt) -> float {
            return itemCmp(lhsIt, rhsIt) ? 1.0 : 0.0;
        });
}


Vec<SeqEdit> myersDiff(
    int                          aSize,
    int                          bSize,
    Func<bool(int lhs, int rhs)> itemCmp);


template <typename T>
Vec<SeqEdit> myersDiff(
    const Vec<T>&                    lhsSeq,
    const Vec<T>&                    rhsSeq,
    Func<bool(const T& x, const T&)> itemCmp) {
    return myersDiff(
        lhsSeq.size(),
        rhsSeq.size(),
        [&lhsSeq, &rhsSeq, &itemCmp](int lhs, int rhs) -> bool {
            return itemCmp(lhsSeq[lhs], rhsSeq[rhs]);
        });
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

LevenshteinDistanceResult levenshteinDistance(
    int                  lhsMax,
    int                  rhsMax,
    Func<bool(int, int)> itemEq);


template <typename T>
LevenshteinDistanceResult levenshteinDistance(Span<T> str1, Span<T> str2) {
    return levenshteinDistance(
        str1.size(), str2.size(), [&](int lhs, int rhs) -> bool {
            return str1[lhs] == str2[rhs];
        });
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
    CharSet start = Invis + ' ';

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
                // Check for kept characters - this will update
                // 'invisible' set if any found, so edits like `" X"
                // -> "X"` are not considered as 'has invisible'
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
    std::string text,
    CharSet     startSet = Invis + CharSet{' '}) {
    // Does string have significant invisible characters?
    CharSet invisSet = startSet;
    if (scanInvisible(text, invisSet)) {
        return true;
    }
    return false;
}

inline bool hasInvisible(CR<Vec<Str>> text) {
    // Do any of strings in text have signficant invisible characters.
    CharSet invisSet = Invis + CharSet{' '};
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
    for (const auto& ch : str) {
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
    inline ShiftedDiff(CR<BacktrackRes> track, int lhsMax, int rhsMax) {
        using sek = SeqEditKind;
        if (!track.lhsIndex.empty()) {
            int fullSize = std::max(lhsMax, rhsMax);
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
                    oldShifted.push_back(Item{sek::None, 0});
                }

                newShifted.push_back(Item{sek::Keep, rhsPos});
                oldShifted.push_back(Item{sek::Keep, lhsPos});
                prevLhs = lhsPos + 1;
                prevRhs = rhsPos + 1;
            }


            if (prevLhs < lhsMax) {
                for (int lhsPos = prevLhs; lhsPos < lhsMax; ++lhsPos) {
                    oldShifted.push_back(Item{sek::Delete, lhsPos});
                    newShifted.push_back(Item{sek::None, 0});
                }
            }

            if (prevRhs < rhsMax) {
                for (int rhsPos = prevRhs; rhsPos < rhsMax; ++rhsPos) {
                    oldShifted.push_back(Item{sek::None, 0});
                    newShifted.push_back(Item{sek::Insert, rhsPos});
                }
            }
        } else {
            // IMPLEMENT for case with zero common elements between diffs
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

    generator<Pair<DiffLine, DiffLine>> unifiedLines() const {
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
        [](const T& a) { return std::format("{}", a); }) {

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
