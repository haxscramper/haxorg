#pragma once

#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/TraceBase.hpp>

#include <hstd/system/reflection.hpp>

using std::operator""s;

struct BacktrackRes {
    Vec<int> lhsIndex = {};
    Vec<int> rhsIndex = {};
    DESC_FIELDS(BacktrackRes, (lhsIndex, rhsIndex));
};

enum class SeqEditKind : u8
{
    None,     ///< Empty edit operation
    Keep,     ///< Keep original element unchanged
    Insert,   ///< Insert new element into target sequence
    Replace,  ///< Replace source element with the target
    Delete,   ///< Delete element from the source sequence
    Transpose ///< Transpose two elements
};

struct SeqEdit {
    SeqEditKind kind;      /// Sequence edit operation kind
    int         sourcePos; /// Position in the original sequence
    int         targetPos; /// Position in the target sequence

    SeqEdit(SeqEditKind kind, int sourcePos = -1, int targetPos = -1)
        : kind(kind), sourcePos(sourcePos), targetPos(targetPos) {}
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


bool hasInvisibleChanges(
    Vec<SeqEdit>& diff,
    Vec<Str>&     oldSeq,
    Vec<Str>&     newSeq);

inline bool hasInvisible(
    std::string text,
    CharSet     startSet = Invis + CharSet{' '}) {
    // Does string have significant invisible characters?
    CharSet invisSet = startSet;
    if (scanInvisible(text, invisSet)) { return true; }
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
        if (scanInvisible(text[idx], invisSet)) { return true; }
    }
    return false;
}

inline Str toVisibleNames(CR<DiffFormatConf> conf, const Str& str) {
    Str result;
    // Convert all characters in the string into visible ones
    for (const auto& ch : str) { result += conf.explainChar(ch); }
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
        BOOST_DESCRIBE_CLASS(Item, (), (kind, item), (), ());
    };

    Vec<Item> oldShifted;
    Vec<Item> newShifted;

    BOOST_DESCRIBE_CLASS(
        ShiftedDiff,
        (),
        (oldShifted, newShifted),
        (),
        ());

    /// \brief Construct shifted diff pairing from LCS trace information
    ShiftedDiff(CR<BacktrackRes> track, int lhsMax, int rhsMax);

    ShiftedDiff(CR<Vec<SeqEdit>>& diff);
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
        for (const auto& line : stacked().elements) { co_yield line; }
    }

    generator<Pair<DiffLine, DiffLine>> unifiedLines() const {
        assert(unified().lhs.size() == unified().rhs.size());
        for (int i = 0; i < unified().lhs.size(); ++i) {
            co_yield {unified().lhs.at(i), unified().rhs.at(i)};
        }
    }

    FormattedDiff(
        const ShiftedDiff& shifted,
        DiffFormatConf     conf = DiffFormatConf{});

    FormattedDiff(
        const Vec<BufItem>&   oldText,
        const Vec<BufItem>&   newText,
        const DiffFormatConf& conf = DiffFormatConf{});
};


ColText formatInlineDiff(
    const Vec<Str>&     src,
    const Vec<Str>&     target,
    const Vec<SeqEdit>& diffed,
    DiffFormatConf      conf);


struct FuzzyMatcher : OperationsTracer {
    using Range     = Slice<int>;
    using ScoreFunc = Func<
        int(Range const& str, int nextMatch, Vec<int> const& matches)>;

    Func<bool(int lhsIdx, int rhsIdx)> isEqual;

    ScoreFunc matchScore;


    int recursionLimit = 10;

    struct LinearScoreConfig {
        /// bonus for adjacent matches
        int sequential_bonus = 15;
        /// bonus if match occurs after a separator
        int separator_bonus = 30;
        /// bonus if the first letter is matched
        int first_letter_bonus = 15;
        /// penalty applied for every letter in str before the first match
        int leading_letter_penalty = -5;
        /// maximum penalty for leading letters
        int max_leading_letter_penalty = -15;
        /// penalty for every letter that doesn't matter
        int                 unmatched_letter_penalty = -1;
        int                 start_score              = 100;
        Func<bool(int idx)> isSeparator;

        DESC_FIELDS(
            LinearScoreConfig,
            (sequential_bonus,
             separator_bonus,
             first_letter_bonus,
             leading_letter_penalty,
             max_leading_letter_penalty,
             unmatched_letter_penalty,
             start_score));
    };

    ScoreFunc getLinearScore(LinearScoreConfig const& conf);


    DESC_FIELDS(FuzzyMatcher, (recursionLimit, matches));

    Vec<int> matches;

    bool fuzzy_match(
        Range     pattern,
        Range     str,
        int&      outScore,
        Vec<int>& matches);

    bool fuzzy_match(Range pattern, Range str, int& outScore) {
        matches.resize(pattern.last + 1);
        return fuzzy_match(pattern, str, outScore, matches);
    }

    int get_score(Range item, Range pattern) {
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
