#include "astdiff_eager.hpp"
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/Set.hpp>

#define _cat "model.tree"

namespace hstd::ext::diff {


NodeStore::Id DiaEdit::getDst() const {
    if (isInsert()) { return getInsert().dstNode; }
    if (isMove()) { return getMove().dstNode; }
    return getUpdate().dstNode;
}

NodeStore::Id DiaEdit::getSrc() const {
    if (isDelete()) { return getDelete().srcNode; }
    if (isMove()) { return getMove().srcNode; }
    return getUpdate().srcNode;
}

namespace {
using ProcessedNodes = hstd::UnorderedSet<NodeStore::Id>;

struct MatchCandidate {
    int  srcIndex;
    bool isExactMatch;
    bool isMove;
    DESC_FIELDS(MatchCandidate, (srcIndex, isExactMatch, isMove));
};

struct EagerAstDiff {
    NodeStore& srcStore;
    NodeStore& dstStore;
    Func<bool(NodeStore::Id const& src, NodeStore::Id const& dst)> const&
                        areValuesEqual;
    hstd::Vec<DiaEdit>& results;

    hstd::Vec<NodeStore::Id> getSubnodes(
        NodeStore&           store,
        NodeStore::Id const& node) {
        hstd::Vec<NodeStore::Id> subnodes;
        int                      count = store.getSubnodeCount(node);
        subnodes.reserve(count);
        for (int i = 0; i < count; ++i) {
            subnodes.push_back(store.getSubnodeAt(node, i));
        }
        return subnodes;
    }

    int countUnprocessedMatching(
        NodeStore::Id const&            needle,
        hstd::Vec<NodeStore::Id> const& haystack,
        ProcessedNodes const&           processed) {
        int count = 0;
        for (auto const& id : haystack) {
            if (!processed.contains(id) && areValuesEqual(id, needle)) {
                ++count;
            }
        }
        return count;
    }

    std::optional<int> findMatchingByKind(
        NodeStore::Id const&            dstSubnode,
        hstd::Vec<NodeStore::Id> const& srcSubnodes,
        ProcessedNodes const&           processedSrc) {
        for (int srcIndex = 0; srcIndex < srcSubnodes.size(); ++srcIndex) {
            auto const& srcSubnode = srcSubnodes.at(srcIndex);
            if (!processedSrc.contains(srcSubnode)
                && srcStore.getNodeKind(srcSubnode)
                       == dstStore.getNodeKind(dstSubnode)) {
                return srcIndex;
            }
        }
        return std::nullopt;
    }

    bool shouldPreferInsert(
        NodeStore::Id const&            dstSubnode,
        hstd::Vec<NodeStore::Id> const& dstSubnodes,
        ProcessedNodes const&           processedDst,
        int                             unprocessedSrcCount) {
        int unprocessedDstCount = countUnprocessedMatching(
            dstSubnode, dstSubnodes, processedDst);
        return unprocessedDstCount > unprocessedSrcCount;
    }

    std::optional<MatchCandidate> findBestMatch(
        NodeStore::Id const&            dstSubnode,
        int                             dstIndex,
        hstd::Vec<NodeStore::Id> const& srcSubnodes,
        ProcessedNodes const&           processedSrc) {

        HSLOG_TRACE(
            "Finding best match for dstSubnode:{} at dstIndex:{}",
            dstSubnode,
            dstIndex);
        HSLOG_DEPTH_SCOPE_ANON();

        std::optional<MatchCandidate> exactMatch;
        std::optional<MatchCandidate> diaIdMatch;
        std::optional<MatchCandidate> moveCandidate;

        for (int srcIndex = 0; srcIndex < srcSubnodes.size(); ++srcIndex) {
            auto const& srcSubnode = srcSubnodes.at(srcIndex);
            if (processedSrc.contains(srcSubnode)
                || srcStore.getNodeKind(srcSubnode)
                       != dstStore.getNodeKind(dstSubnode)) {
                continue;
            }

            // Compare DiaId (content) instead of DiaUniqId (content +
            // position)
            bool isExact = areValuesEqual(srcSubnode, dstSubnode);
            bool isMove  = srcIndex != dstIndex;

            HSLOG_TRACE(
                "Evaluating srcIndex:{} isExact:{} isMove:{} "
                "srcSubnode:{}",
                srcIndex,
                isExact,
                isMove,
                srcSubnode);

            if (isExact) {
                if (isMove) {
                    if (!moveCandidate.has_value()
                        || !moveCandidate->isExactMatch) {
                        moveCandidate = MatchCandidate{
                            srcIndex, true, true};
                        HSLOG_TRACE(
                            "Found exact move candidate at srcIndex:{}",
                            srcIndex);
                    }
                } else {
                    exactMatch = MatchCandidate{srcIndex, true, false};
                    HSLOG_TRACE(
                        "Found exact match at srcIndex:{}", srcIndex);
                }
            } else if (
                !exactMatch.has_value() && !diaIdMatch.has_value()) {
                diaIdMatch = MatchCandidate{srcIndex, false, isMove};
                HSLOG_TRACE("Found DiaId match at srcIndex:{}", srcIndex);
            }
        }

        if (moveCandidate.has_value() && moveCandidate->isExactMatch) {
            HSLOG_TRACE("Selecting exact move candidate");
            return moveCandidate;
        }

        if (exactMatch.has_value()) {
            HSLOG_TRACE("Selecting exact match");
            return exactMatch;
        }

        if (diaIdMatch.has_value()) {
            HSLOG_TRACE("Selecting DiaId match");
            return diaIdMatch;
        }

        auto kindMatch = findMatchingByKind(
            dstSubnode, srcSubnodes, processedSrc);
        if (kindMatch.has_value()) {
            HSLOG_TRACE(
                "Selecting kind match at srcIndex:{}", kindMatch.value());
            return MatchCandidate{
                kindMatch.value(), false, kindMatch.value() != dstIndex};
        }

        HSLOG_TRACE("No match found");
        return std::nullopt;
    }

    void processMatchedSubnodes(
        NodeStore::Id const& srcSubnode,
        NodeStore::Id const& dstSubnode,
        int                  srcIndex,
        int                  dstIndex,
        ProcessedNodes&      processedSrc,
        ProcessedNodes&      processedDst) {

        diffSubnodes(srcSubnode, dstSubnode);

        // Compare DiaId (content) instead of DiaUniqId (content +
        // position)
        if (areValuesEqual(srcSubnode, dstSubnode)) {
            if (srcIndex != dstIndex) {
                HSLOG_TRACE(
                    "Creating Move edit from srcIndex:{} to dstIndex:{} "
                    "for node:{}",
                    srcIndex,
                    dstIndex,
                    srcSubnode);
                results.emplace_back(
                    DiaEdit::Move{
                        .srcNode  = srcSubnode,
                        .dstNode  = dstSubnode,
                        .srcIndex = srcIndex,
                        .dstIndex = dstIndex});
            } else {
                HSLOG_TRACE(
                    "Nodes identical at same position, no edit needed for "
                    "srcIndex:{}",
                    srcIndex);
            }
        } else {
            HSLOG_TRACE(
                "Creating Update edit from srcIndex:{} to dstIndex:{} "
                "srcSubnode:{} dstSubnode:{}",
                srcIndex,
                dstIndex,
                srcSubnode,
                dstSubnode);
            results.emplace_back(
                DiaEdit::Update{
                    .srcNode  = srcSubnode,
                    .dstNode  = dstSubnode,
                    .srcIndex = srcIndex,
                    .dstIndex = dstIndex});
        }

        processedSrc.incl(srcSubnode);
        processedDst.incl(dstSubnode);
    }

    bool recurseMatchCandidate(
        NodeStore::Id const&            dstSubnode,
        hstd::Vec<NodeStore::Id> const& srcSubnodes,
        hstd::Vec<NodeStore::Id> const& dstSubnodes,
        ProcessedNodes&                 processedSrc,
        ProcessedNodes&                 processedDst,
        MatchCandidate const&           matchCandidate,
        int                             dstIndex) {
        auto const& srcSubnode = srcSubnodes.at(matchCandidate.srcIndex);

        HSLOG_TRACE(
            "{} to match src:{} with dst:{}",
            matchCandidate,
            srcSubnode,
            dstSubnode);

        int unprocessedSrcCount = countUnprocessedMatching(
            dstSubnode, srcSubnodes, processedSrc);

        if (shouldPreferInsert(
                dstSubnode,
                dstSubnodes,
                processedDst,
                unprocessedSrcCount)) {
            HSLOG_TRACE(
                "Preferring insert over match due to "
                "duplicate handling");
            return false;
        }

        HSLOG_TRACE(
            "Processing match: srcIndex:{} -> dstIndex:{} "
            "isExact:{} isMove:{}",
            matchCandidate.srcIndex,
            dstIndex,
            matchCandidate.isExactMatch,
            matchCandidate.isMove);

        processMatchedSubnodes(
            srcSubnode,
            dstSubnode,
            matchCandidate.srcIndex,
            dstIndex,
            processedSrc,
            processedDst);

        return true;
    }

    void diffSubnodes(
        NodeStore::Id const& srcNode,
        NodeStore::Id const& dstNode) {

        if (srcStore.getSubnodeCount(srcNode) == 0
            && dstStore.getSubnodeCount(dstNode) == 0) {
            return;
        }

        HSLOG_TRACE("aux on src:{} dst:{}", srcNode, dstNode);
        HSLOG_DEPTH_SCOPE_ANON();

        if (srcStore.getNodeKind(srcNode)
            != dstStore.getNodeKind(dstNode)) {
            HSLOG_TRACE(
                "Node kind mismatch, early return {} != {}",
                srcStore.getNodeKind(srcNode),
                dstStore.getNodeKind(dstNode));
            return;
        }

        auto srcSubnodes = getSubnodes(srcStore, srcNode);
        auto dstSubnodes = getSubnodes(dstStore, dstNode);

        ProcessedNodes processedSrc;
        ProcessedNodes processedDst;

        for (int dstIndex = 0; dstIndex < dstSubnodes.size(); ++dstIndex) {
            HSLOG_TRACE("dst index {}", dstIndex);
            HSLOG_DEPTH_SCOPE_ANON();
            auto const& dstSubnode = dstSubnodes.at(dstIndex);

            if (processedDst.contains(dstSubnode)) {
                HSLOG_TRACE(
                    "Skipping already processed dstSubnode at index:{}",
                    dstIndex);
                continue;
            }

            hstd::Opt<MatchCandidate> const matchCandidate = findBestMatch(
                dstSubnode, dstIndex, srcSubnodes, processedSrc);

            bool matchAccepted = false;

            if (matchCandidate.has_value()) {
                matchAccepted = recurseMatchCandidate(
                    dstSubnode,
                    srcSubnodes,
                    dstSubnodes,
                    processedSrc,
                    processedDst,
                    matchCandidate.value(),
                    dstIndex);
            }

            if (!matchAccepted) {
                HSLOG_TRACE(
                    "Creating Insert edit for dstIndex:{} dstSubnode:{}",
                    dstIndex,
                    dstSubnode);
                results.emplace_back(
                    DiaEdit::Insert{
                        .dstNode = dstSubnode, .dstIndex = dstIndex});
                processedDst.incl(dstSubnode);
                continue;
            }
        }

        for (int srcIndex = 0; srcIndex < srcSubnodes.size(); ++srcIndex) {
            auto const& srcSubnode = srcSubnodes.at(srcIndex);
            if (!processedSrc.contains(srcSubnode)) {
                HSLOG_TRACE(
                    "Creating Delete edit for srcIndex:{} srcSubnode:{}",
                    srcIndex,
                    srcSubnode);
                results.emplace_back(
                    DiaEdit::Delete{
                        .srcNode = srcSubnode, .srcIndex = srcIndex});
            }
        }
    }

    void run(NodeStore::Id const& srcRoot, NodeStore::Id const& dstRoot) {
        diffSubnodes(srcRoot, dstRoot);

        if (!areValuesEqual(srcRoot, dstRoot)) {
            HSLOG_TRACE(
                "Creating root Update edit ID mismatch{} -> {}",
                srcRoot,
                dstRoot);
            results.emplace_back(
                DiaEdit::Update{
                    .srcNode  = srcRoot,
                    .dstNode  = dstRoot,
                    .srcIndex = 0,
                    .dstIndex = 0});
        }
    }
};
} // namespace

hstd::Vec<DiaEdit> getEdits(
    NodeStore& srcStore,
    NodeStore& dstStore,
    Func<bool(NodeStore::Id const& src, NodeStore::Id const& dst)> const&
        areValuesEqual) {
    hstd::Vec<DiaEdit> results;
    HSLOG_INFO(_cat, "getEdits");
    HSLOG_DEPTH_SCOPE_ANON();

    EagerAstDiff{
        .srcStore       = srcStore,
        .dstStore       = dstStore,
        .areValuesEqual = areValuesEqual,
        .results        = results,
    }
        .run(srcStore.getRoot(), dstStore.getRoot());

    return results;
}
} // namespace hstd::ext::diff
