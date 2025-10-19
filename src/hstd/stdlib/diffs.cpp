#include "diffs.hpp"
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Ranges.hpp>

#pragma clang diagnostic ignored "-Wreorder-init-list"

using namespace hstd;

Vec<BacktrackRes> hstd::longestCommonSubsequence(
    int                   lhsSize,
    int                   rhsSize,
    Func<bool(int, int)>  itemCmp,
    Func<float(int, int)> itemEqualityMetric) {

    if (lhsSize == 0 || rhsSize == 0) { return {{}}; }

    UnorderedMap<Pair<int, int>, float> mem;
    Func<float(int, int)>               lcs;
    lcs = [&](int lhsIdx, int rhsIdx) -> float {
        if (!mem.contains({lhsIdx, rhsIdx})) {
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

    int cnt   = 0;
    backtrack = [&](int lhsIdx, int rhsIdx) -> Vec<BacktrackRes> {
        if (lcs(lhsIdx, rhsIdx) == 0) {
            return {};
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
                // + backtrack(lhsIdx - 1, rhsIdx)
                ;
        }
    };

    auto result = backtrack(lhsSize - 1, rhsSize - 1);
    if (result.empty()) {
        return Vec{BacktrackRes{}};
    } else {
        return result;
    }
}

Vec<SeqEdit> hstd::myersDiff(
    int                          lhsSize,
    int                          rhsSize,
    Func<bool(int lhs, int rhs)> itemCmp) {

    using sek = SeqEditKind;

    if (lhsSize == 0 && rhsSize == 0) { return Vec<SeqEdit>{}; }

    int                          maxD = lhsSize + rhsSize;
    Vec<Pair<int, Vec<SeqEdit>>> front(2 * maxD + 1);

    int offset             = maxD;
    front.at(offset).first = 0;

    for (int fullIdx = 0; fullIdx <= maxD; fullIdx++) {
        for (int backIdx = -fullIdx; backIdx <= fullIdx; backIdx += 2) {
            int frontIndex = backIdx + offset;

            bool goDown
                = (backIdx == -fullIdx
                   || (backIdx != fullIdx
                       && front.at(frontIndex - 1).first
                              < front.at(frontIndex + 1).first));

            int          lhsIdx = 0;
            int          rhsIdx = 0;
            Vec<SeqEdit> history{};

            if (goDown) {
                lhsIdx  = front.at(frontIndex + 1).first;
                history = front.at(frontIndex + 1).second;
            } else {
                lhsIdx  = front.at(frontIndex - 1).first + 1;
                history = front.at(frontIndex - 1).second;
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
                front.at(frontIndex).first  = lhsIdx;
                front.at(frontIndex).second = history;
            }
        }
    }

    return Vec<SeqEdit>{};
}

LevenshteinDistanceResult hstd::levenshteinDistance(
    int                  lhsMax,
    int                  rhsMax,
    Func<bool(int, int)> itemEq) {

    Vec<Vec<int>> table(lhsMax + 1, Vec<int>(rhsMax + 1, 0));
    Vec<Vec<std::pair<int, int>>> paths(
        lhsMax + 1, Vec<std::pair<int, int>>(rhsMax + 1, {0, 0}));

    for (int lsh = 0; lsh <= lhsMax; ++lsh) {
        table[lsh][0] = lsh;
        paths[lsh][0] = {lsh - 1, 0};
    }

    for (int rhs = 0; rhs <= rhsMax; ++rhs) {
        table[0][rhs] = rhs;
        paths[0][rhs] = {0, rhs - 1};
    }

    for (int lhs = 1; lhs <= lhsMax; ++lhs) {
        for (int rhs = 1; rhs <= rhsMax; ++rhs) {
            if (itemEq(lhs - 1, rhs - 1)) {
                table[lhs][rhs] = table[lhs - 1][rhs - 1];
                paths[lhs][rhs] = {lhs - 1, rhs - 1};
            } else {
                int min_val = std::min(
                    {table[lhs - 1][rhs],
                     table[lhs][rhs - 1],
                     table[lhs - 1][rhs - 1]});
                table[lhs][rhs] = min_val + 1;
                if (table[lhs - 1][rhs] == min_val) {
                    paths[lhs][rhs] = {lhs - 1, rhs};
                } else if (table[lhs][rhs - 1] == min_val) {
                    paths[lhs][rhs] = {lhs, rhs - 1};
                } else if (table[lhs - 1][rhs - 1] == min_val) {
                    paths[lhs][rhs] = {lhs - 1, rhs - 1};
                }
            }
        }
    }

    struct Item {
        int         lhsIdx;
        int         rhsIdx;
        SeqEditKind kind;
    };

    Vec<Item> levenpath;

    int lhsIdx = lhsMax, rhsIdx = rhsMax;
    while (0 <= lhsIdx && 0 <= rhsIdx) {
        rhsIdx = rhsMax;
        while (0 <= lhsIdx && 0 <= rhsIdx) {
            levenpath.push_back({lhsIdx, rhsIdx, SeqEditKind::None});
            int t  = lhsIdx;
            lhsIdx = paths[lhsIdx][rhsIdx].first;
            rhsIdx = paths[t][rhsIdx].second;
        }
    }

    std::reverse(levenpath.begin(), levenpath.end());
    Vec<SeqEdit> resultOperations;

    for (int pathIdx = 1; pathIdx < levenpath.size(); pathIdx++) {
        auto last = levenpath[pathIdx - 1];
        auto cur  = levenpath[pathIdx];

        if (pathIdx != 0) {
            if (cur.lhsIdx == last.lhsIdx + 1
                && cur.rhsIdx == last.rhsIdx + 1
                && table[cur.lhsIdx][cur.rhsIdx]
                       != table[last.lhsIdx][last.rhsIdx]) {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Replace, 0, 0});
            } else if (
                cur.lhsIdx == last.lhsIdx
                && cur.rhsIdx == last.rhsIdx + 1) {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Insert, 0, 0});
            } else if (
                cur.lhsIdx == last.lhsIdx + 1
                && cur.rhsIdx == last.rhsIdx) {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Delete, 0, 0});
            } else {
                resultOperations.push_back(
                    SeqEdit{SeqEditKind::Keep, 0, 0});
            }

            resultOperations.back().sourcePos = cur.lhsIdx - 1;
            resultOperations.back().targetPos = cur.rhsIdx - 1;
        }
    }

    return {
        table[levenpath.back().lhsIdx][levenpath.back().rhsIdx],
        resultOperations};
}

hstd::ShiftedDiff::ShiftedDiff(
    CR<BacktrackRes> track,
    int              lhsMax,
    int              rhsMax) {
    using sek    = SeqEditKind;
    int prevLhs  = 0;
    int prevRhs  = 0;
    int fullSize = std::max(lhsMax, rhsMax);
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
}

hstd::ShiftedDiff::ShiftedDiff(CR<Vec<SeqEdit>>& diff) {
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

bool hstd::hasInvisibleChanges(
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
                if (invis(oldSeq[edit.sourcePos])) { return true; }
                break;
            case SeqEditKind::Insert:
                if (invis(newSeq[edit.targetPos])) { return true; }
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

int FormattedDiff::maxLineNumber() const {
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

hstd::FormattedDiff::FormattedDiff(
    const ShiftedDiff& shifted,
    const Conf&        conf)
    : conf{conf} {
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

hstd::FormattedDiff::FormattedDiff(
    const Vec<BufItem>& oldText,
    const Vec<BufItem>& newText,
    const Conf&         conf)
    : conf{conf} {
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

ColText FormattedDiff::format() {
    ColStream os;
    if (isUnified()) {
        Vec<Pair<FormattedDiff::DiffLine, FormattedDiff::DiffLine>> lines;
        Vec<Pair<ColText, ColText>> formattedLines;
        for (auto const& pair : unifiedLines()) {
            lines.push_back(pair);
            auto lhsLine = conf.formatLine(pair.first);
            auto rhsLine = conf.formatLine(pair.second);
            if (conf.maxLhsSize) {
                lhsLine = lhsLine.at(slice(
                    0, std::min(lhsLine.size(), conf.maxLhsSize.value())));
            }

            if (conf.maxRhsSize) {
                rhsLine = rhsLine.at(slice(
                    0, std::min(rhsLine.size(), conf.maxRhsSize.value())));
            }

            formattedLines.push_back({lhsLine, rhsLine});
        }

        int lhsSize = std::max(
            conf.minLhsSize.value_or(0),
            rs::max(
                formattedLines
                | rv::transform([](Pair<ColText, ColText> const& elem) {
                      return elem.first.size();
                  })));

        int rhsSize = std::max(
            conf.minRhsSize.value_or(0),
            rs::max(
                formattedLines
                | rv::transform([](Pair<ColText, ColText> const& elem) {
                      return elem.second.size();
                  })));

        int const linePrefixSize = 2;

        ColText splitSeparator{" "_ss};

        os << (ColText{""} <<= linePrefixSize) //
           << (ColText("Given") <<= lhsSize)   //
           << splitSeparator                   //
           << (ColText{""} <<= linePrefixSize) //
           << (ColText("Expected"))            //
           << "\n";


        if (lines.empty()) {
            os << "No diff content to compare\n";
            return os;
        }

        Slice<int> range = slice(0, lines.size() - 1);
        if (conf.dropLeadingKeep) {
            for (int i = 0; i <= range.last; ++i) {
                if (lines[i].first.prefix == SeqEditKind::Keep
                    && lines[i].second.prefix == SeqEditKind::Keep) {
                    range.first = i;
                } else {
                    // two lines of context before diff
                    range.first = std::max(0, i - 1);
                    break;
                }
            }
        }

        if (conf.dropTrailingKeep) {
            for (int i = range.last; range.first < i; --i) {
                if (lines[i].first.prefix == SeqEditKind::Keep
                    && lines[i].second.prefix == SeqEditKind::Keep) {
                    range.last = i;
                } else {
                    range.last = std::min(lines.high(), i + 1);
                    break;
                }
            }
        }

        for (const auto& i : range) {
            auto const& lhs = lines[i].first;
            auto const& rhs = lines[i].second;

            auto lhsStyle = toStyle(lhs.prefix);
            auto rhsStyle = toStyle(rhs.prefix);

            os << (ColText(lhsStyle, toPrefix(lhs.prefix)) <<= linePrefixSize)
               << ((lhs.empty() ? ColText("")
                                : formattedLines.at(lhs.index().value())
                                      .first.withStyle(lhsStyle))
                   <<= lhsSize)
               << splitSeparator //
               << (ColText(rhsStyle, toPrefix(rhs.prefix)) <<= linePrefixSize)
               << ((rhs.empty() ? ColText("")
                                : formattedLines.at(rhs.index().value())
                                      .second.withStyle(rhsStyle))
                   <<= rhsSize)
               << "\n";
        }
    } else {
        logic_todo_impl();
    }

    return os;
}

hstd::ColText formatInlineDiff(
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

namespace {
struct fuzzy_result {
    bool has_match;
    int  score;
};

#define LG(__msg)                                                         \
    if (m.TraceState) {                                                   \
        m.message(OperationsMsg{                                          \
            .line     = __LINE__,                                         \
            .function = __func__,                                         \
            .msg      = indent(__msg, recursionCount),                    \
            .file     = __FILE__,                                         \
        });                                                               \
    }

fuzzy_result fuzzy_match_recursive(
    FuzzyMatcher&       m,
    FuzzyMatcher::Range pattern,
    FuzzyMatcher::Range str,
    FuzzyMatcher::Range strBegin,
    Vec<int> const&     srcMatches,
    Vec<int>&           matches,
    int                 nextMatch,
    int&                recursionCount,
    int                 matchSize) {

    LG(fmt("Match recursive count:{}", recursionCount));

    // Count recursions
    ++recursionCount;
    if (m.recursionLimit <= recursionCount) {
        LG("Rearched recursion limit");
        return {.has_match = false};
    }

    // Detect end of Strs
    if (!pattern.isValid() || !str.isValid()) {
        LG("End of the pattern/string detected");
        return {.has_match = false};
    }

    // Recursion params
    bool     recursiveMatch = false;
    Vec<int> bestRecursiveMatches;
    int      bestRecursiveScore = 0;

    // Loop through pattern and str looking for a match
    bool first_match = true;
    while (pattern.isValid() && str.isValid()) {
        LG(fmt("str:{} pattern:{}", str, pattern));
        LOGIC_ASSERTION_CHECK(
            m.isEqual, "Missing item equality compare function");
        // Found match
        if (m.isEqual(pattern.first, str.first)) {
            LG(fmt("pattern[{}] == str[{}]", pattern.first, str.first));
            // "Copy-on-Write" srcMatches into matches
            if (first_match) {
                matches     = srcMatches;
                first_match = false;
            }

            // Recursive call that "skips" this match
            Vec<int> recursiveMatches;
            recursiveMatches.resize(matchSize);
            FuzzyMatcher::Range recurseRange = str;
            ++recurseRange.first;
            fuzzy_result recurse = fuzzy_match_recursive(
                m,
                pattern,
                recurseRange,
                strBegin,
                matches,
                recursiveMatches,
                nextMatch,
                recursionCount,
                matchSize);

            LG(
                fmt("Recursive call result score:{} match:{}",
                    recurse.score,
                    recurse.has_match));

            if (recurse.has_match) {
                // Pick best recursive score
                if (!recursiveMatch
                    || bestRecursiveScore < recurse.score) {
                    bestRecursiveMatches = recursiveMatches;
                    bestRecursiveScore   = recurse.score;
                }
                recursiveMatch = true;
            }

            // Advance
            LG(_dfmt_expr(nextMatch, str.first));
            matches.at(nextMatch) = str.first;
            ++nextMatch;
            ++pattern.first;
            LG(fmt1(matches));
        } else {
            LG(fmt("pattern[{}] != str[{}]", pattern.first, str.first));
        }
        ++str.first;
    }

    // Determine if full pattern was matched
    bool matched  = !pattern.isValid();
    int  outScore = 0;

    LOGIC_ASSERTION_CHECK(
        m.matchScore, "Match score callback implementation is missing");
    // Calculate score
    if (matched) { outScore = m.matchScore(str, nextMatch, matches); }

    // Return best result
    if (recursiveMatch && (!matched || outScore < bestRecursiveScore)) {
        // Recursive score is better than "this"
        matches = bestRecursiveMatches;
        return {
            .has_match = true,
            .score     = bestRecursiveScore,
        };
    } else if (matched) {
        // "this" score is better than recursive
        return {
            .has_match = true,
            .score     = outScore,
        };
    } else {
        // no match
        return {.has_match = false};
    }
}
} // namespace

FuzzyMatcher::ScoreFunc hstd::FuzzyMatcher::getLinearScore(
    const LinearScoreConfig& conf) {
    return [&conf](
               Range const&    _str,
               int             nextMatch,
               Vec<int> const& matches) -> int {
        auto str      = _str;
        int  outScore = 0;
        // Iterate str to end
        while (str.isValid()) { ++str.first; }

        // Initialize score
        outScore = conf.start_score;

        // Apply leading letter penalty
        int penalty = conf.leading_letter_penalty * matches[0];
        if (penalty < conf.max_leading_letter_penalty) {
            penalty = conf.max_leading_letter_penalty;
        }
        outScore += penalty;

        // Apply unmatched penalty
        int unmatched = str.first - nextMatch;
        outScore += conf.unmatched_letter_penalty * unmatched;

        // Apply ordering bonuses
        for (int i = 0; i < nextMatch; ++i) {
            int currIdx = matches[i];

            if (i > 0) {
                int prevIdx = matches[i - 1];

                // Sequential
                if (currIdx == (prevIdx + 1)) {
                    outScore += conf.sequential_bonus;
                }
            }

            if (0 == currIdx) {
                outScore += conf.first_letter_bonus;
            } else if (conf.isSeparator && conf.isSeparator(currIdx)) {
                outScore += conf.separator_bonus;
            }
        }
        return outScore;
    };
}

bool hstd::FuzzyMatcher::fuzzy_match(
    Range     pattern,
    Range     str,
    int&      outScore,
    Vec<int>& matches) {
    int      recursionCount = 0;
    Vec<int> srcMatches;
    srcMatches.resize(pattern.last + 1);

    fuzzy_result result = fuzzy_match_recursive(
        *this,
        pattern,
        str,
        str,
        srcMatches,
        matches,
        0,
        recursionCount,
        pattern.last + 1);

    outScore = result.score;

    return result.has_match;
}
