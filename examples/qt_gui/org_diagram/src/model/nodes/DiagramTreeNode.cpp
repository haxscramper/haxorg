#include "DiagramTreeNode.hpp"
#include <src/utils/common.hpp>
#include <hstd/stdlib/Ranges.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "model.tree"

#define _kind(__Kind)                                                     \
    template <>                                                           \
    DiaNodeKindStore<DiaNode##__Kind> const* DiaNodeStore::getStoreImpl() \
        const {                                                           \
        return &store##__Kind;                                            \
    }
EACH_DIAGRAM_KIND(_kind)
#undef _kind


HSTD_REGISTER_TYPE_FIELD_NAMES(DiaNode);
HSTD_REGISTER_TYPE_FIELD_NAMES(DiaNodeLayer);
HSTD_REGISTER_TYPE_FIELD_NAMES(DiaNodeCanvas);
HSTD_REGISTER_TYPE_FIELD_NAMES(DiaNodeGroup);
HSTD_REGISTER_TYPE_FIELD_NAMES(DiaNodeItem);

hstd::described_predicate_result isSubtreeItem(
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    auto position = getStructuredProperty<DiaNodeItem::Pos>(
        subtree, DiaPropertyNames::diagramPosition);

    if (position.has_value()
        && hasArgsProperty(subtree, DiaPropertyNames::isDiagramNode)) {
        return true;
    } else {
        return hstd::described_predicate_error::init(hstd::fmt(
            "{} (title: {}) does not meet the criteria: top-level subtree "
            "for subtree item must have :prop_json:{} and :prop_args:{} "
            "properties. has position:{} has diagram node:{}",
            subtree.uniq(),
            subtree.getCleanTitle(),
            DiaPropertyNames::diagramPosition,
            DiaPropertyNames::isDiagramNode,
            position.has_value() ? "true" : position.error(),
            hasArgsProperty(subtree, DiaPropertyNames::isDiagramNode)));
    }
}

DiaNodeItem FromSubtreeItem(
    hstd::SPtr<DiaContext> const&                      context,
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    LOGIC_ASSERTION_CHECK_DESCRIBED(isSubtreeItem(subtree));

    DiaNodeItem item;
    item.id = subtree;
    return item;
}


DiaId FromSubtreeItemRec(
    hstd::SPtr<DiaContext> const&                      context,
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    HSLOG_INFO(_cat, hstd::fmt("Subtree item {}", subtree.uniq()));
    HSLOG_DEPTH_SCOPE_ANON();
    LOGIC_ASSERTION_CHECK_DESCRIBED(isSubtreeItem(subtree));

    auto result = FromSubtreeItem(context, subtree);

    auto tmp = result.subnodes.transient();

    for (auto const& sub : subtree.subAs<org::imm::ImmSubtree>()) {
        if (isSubtreeItem(sub)) {
            tmp.push_back(FromSubtreeItemRec(context, sub));
        }
    }

    result.subnodes = tmp.persistent();
    return context->add(result);
}


DiaAdapter FromDocument(
    hstd::SPtr<DiaContext> const&                       context,
    const org::imm::ImmAdapterT<org::imm::ImmDocument>& root) {
    HSLOG_INFO(_cat, hstd::fmt("Creating canvas from {}", root.uniq()));
    HSLOG_DEPTH_SCOPE_ANON();
    auto canvas = DiaNodeCanvas{};
    canvas.id   = root;

    auto canvas_tmp = canvas.subnodes.transient();
    for (auto const& layerNode : root.subAs<org::imm::ImmSubtree>()) {
        auto layer = DiaNodeLayer{};
        layer.id   = layerNode;
        auto tmp   = layer.subnodes.transient();
        for (auto const& subtreeNode :
             layerNode.subAs<org::imm::ImmSubtree>()) {
            tmp.push_back(FromSubtreeItemRec(context, subtreeNode));
        }
        layer.subnodes = tmp.persistent();
        canvas_tmp.push_back(context->add(layer));
    }

    canvas.subnodes = canvas_tmp.persistent();
    return DiaAdapter::Root(context->add(canvas), context);
}

namespace {
using ProcessedNodes = hstd::UnorderedSet<DiaUniqId>;
using NodesByDiaId   = hstd::UnorderedMap<DiaId, std::vector<int>>;

NodesByDiaId buildNodeIndex(const std::vector<DiaAdapter>& subnodes) {
    NodesByDiaId nodesByDiaId;
    for (int i = 0; i < subnodes.size(); ++i) {
        nodesByDiaId[subnodes.at(i).id.id].push_back(i);
    }
    return nodesByDiaId;
}

int countUnprocessedNodes(
    const std::vector<int>&        indices,
    const std::vector<DiaAdapter>& subnodes,
    const ProcessedNodes&          processed) {
    int count = 0;
    for (int idx : indices) {
        if (!processed.contains(subnodes.at(idx).id)) { count++; }
    }
    return count;
}

std::optional<int> findMatchingByDiaId(
    const DiaAdapter&              dstSubnode,
    const NodesByDiaId&            srcSubnodesByDiaId,
    const std::vector<DiaAdapter>& srcSubnodes,
    const ProcessedNodes&          processedSrc) {

    auto srcIndicesIt = srcSubnodesByDiaId.find(dstSubnode.id.id);
    if (srcIndicesIt == srcSubnodesByDiaId.end()) { return std::nullopt; }

    std::optional<int> matchingSrcIndex;
    for (int srcIndex : srcIndicesIt->second) {
        const auto& srcSubnode = srcSubnodes.at(srcIndex);
        if (!processedSrc.contains(srcSubnode.id)
            && srcSubnode.getKind() == dstSubnode.getKind()) {
            if (srcSubnode.id == dstSubnode.id) {
                matchingSrcIndex = srcIndex;
                break;
            }
            if (!matchingSrcIndex.has_value()) {
                matchingSrcIndex = srcIndex;
            }
        }
    }

    return matchingSrcIndex;
}

std::optional<int> findMatchingByKind(
    const DiaAdapter&              dstSubnode,
    const std::vector<DiaAdapter>& srcSubnodes,
    const ProcessedNodes&          processedSrc) {

    for (int srcIndex = 0; srcIndex < srcSubnodes.size(); ++srcIndex) {
        const auto& srcSubnode = srcSubnodes.at(srcIndex);
        if (!processedSrc.contains(srcSubnode.id)
            && srcSubnode.getKind() == dstSubnode.getKind()) {
            return srcIndex;
        }
    }
    return std::nullopt;
}

bool shouldPreferInsert(
    const DiaAdapter&              dstSubnode,
    const NodesByDiaId&            dstSubnodesByDiaId,
    const std::vector<DiaAdapter>& dstSubnodes,
    const ProcessedNodes&          processedDst,
    int                            unprocessedSrcCount) {

    auto dstIndicesIt = dstSubnodesByDiaId.find(dstSubnode.id.id);
    if (dstIndicesIt == dstSubnodesByDiaId.end()) { return false; }

    int unprocessedDstCount = countUnprocessedNodes(
        dstIndicesIt->second, dstSubnodes, processedDst);

    return unprocessedDstCount > unprocessedSrcCount;
}

void processMatchedSubnodes(
    const DiaAdapter&     srcSubnode,
    const DiaAdapter&     dstSubnode,
    int                   srcIndex,
    int                   dstIndex,
    std::vector<DiaEdit>& results,
    ProcessedNodes&       processedSrc,
    ProcessedNodes&       processedDst);

struct MatchCandidate {
    int  srcIndex;
    bool isExactMatch;
    bool isMove;
};

std::optional<MatchCandidate> findBestMatch(
    const DiaAdapter&              dstSubnode,
    int                            dstIndex,
    const NodesByDiaId&            srcSubnodesByDiaId,
    const std::vector<DiaAdapter>& srcSubnodes,
    const ProcessedNodes&          processedSrc) {

    HSLOG_TRACE(
        _cat,
        hstd::fmt(
            "Finding best match for dstSubnode:{} at dstIndex:{}",
            dstSubnode,
            dstIndex));
    HSLOG_DEPTH_SCOPE_ANON();

    auto srcIndicesIt = srcSubnodesByDiaId.find(dstSubnode.id.id);
    if (srcIndicesIt == srcSubnodesByDiaId.end()) {
        HSLOG_TRACE(
            _cat,
            hstd::fmt("No DiaId match found for {}", dstSubnode.id.id));
        return findMatchingByKind(dstSubnode, srcSubnodes, processedSrc)
            .transform(
                [](int idx) { return MatchCandidate{idx, false, false}; });
    }

    std::optional<MatchCandidate> exactMatch;
    std::optional<MatchCandidate> diaIdMatch;
    std::optional<MatchCandidate> moveCandidate;

    for (int srcIndex : srcIndicesIt->second) {
        const auto& srcSubnode = srcSubnodes.at(srcIndex);
        if (processedSrc.contains(srcSubnode.id)
            || srcSubnode.getKind() != dstSubnode.getKind()) {
            continue;
        }

        // Compare DiaId (content) instead of DiaUniqId (content +
        // position)
        bool isExact = srcSubnode.id.id == dstSubnode.id.id;
        bool isMove  = srcIndex != dstIndex;

        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Evaluating srcIndex:{} isExact:{} isMove:{} "
                "srcSubnode:{}",
                srcIndex,
                isExact,
                isMove,
                srcSubnode));

        if (isExact) {
            if (isMove) {
                if (!moveCandidate.has_value()
                    || !moveCandidate->isExactMatch) {
                    moveCandidate = MatchCandidate{srcIndex, true, true};
                    HSLOG_TRACE(
                        _cat,
                        hstd::fmt(
                            "Found exact move candidate at srcIndex:{}",
                            srcIndex));
                }
            } else {
                exactMatch = MatchCandidate{srcIndex, true, false};
                HSLOG_TRACE(
                    _cat,
                    hstd::fmt(
                        "Found exact match at srcIndex:{}", srcIndex));
            }
        } else if (!exactMatch.has_value() && !diaIdMatch.has_value()) {
            diaIdMatch = MatchCandidate{srcIndex, false, isMove};
            HSLOG_TRACE(
                _cat,
                hstd::fmt("Found DiaId match at srcIndex:{}", srcIndex));
        }
    }

    if (moveCandidate.has_value() && moveCandidate->isExactMatch) {
        HSLOG_TRACE(_cat, hstd::fmt("Selecting exact move candidate"));
        return moveCandidate;
    }

    if (exactMatch.has_value()) {
        HSLOG_TRACE(_cat, hstd::fmt("Selecting exact match"));
        return exactMatch;
    }

    if (diaIdMatch.has_value()) {
        HSLOG_TRACE(_cat, hstd::fmt("Selecting DiaId match"));
        return diaIdMatch;
    }

    auto kindMatch = findMatchingByKind(
        dstSubnode, srcSubnodes, processedSrc);
    if (kindMatch.has_value()) {
        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Selecting kind match at srcIndex:{}", kindMatch.value()));
        return MatchCandidate{
            kindMatch.value(), false, kindMatch.value() != dstIndex};
    }

    HSLOG_TRACE(_cat, hstd::fmt("No match found"));
    return std::nullopt;
}

void diffSubnodes(
    const DiaAdapter&     srcNode,
    const DiaAdapter&     dstNode,
    std::vector<DiaEdit>& results) {

    if (srcNode.get()->subnodes.empty()
        && dstNode.get()->subnodes.empty()) {
        return;
    }

    HSLOG_TRACE(_cat, hstd::fmt("aux on src:{} dst:{}", srcNode, dstNode));
    HSLOG_DEPTH_SCOPE_ANON();

    if (srcNode.getKind() != dstNode.getKind()) {
        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Node kind mismatch, early return {} != {}",
                srcNode.getKind(),
                dstNode.getKind()));
        return;
    }

    auto srcSubnodes = srcNode.sub(true);
    auto dstSubnodes = dstNode.sub(true);

    auto srcSubnodesByDiaId = buildNodeIndex(srcSubnodes);
    auto dstSubnodesByDiaId = buildNodeIndex(dstSubnodes);

    ProcessedNodes processedSrc;
    ProcessedNodes processedDst;

    for (int dstIndex = 0; dstIndex < dstSubnodes.size(); ++dstIndex) {
        HSLOG_TRACE(_cat, hstd::fmt("dst index {}", dstIndex));
        HSLOG_DEPTH_SCOPE_ANON();
        const auto& dstSubnode = dstSubnodes.at(dstIndex);

        if (processedDst.contains(dstSubnode.id)) {
            HSLOG_TRACE(
                _cat,
                hstd::fmt(
                    "Skipping already processed dstSubnode at index:{}",
                    dstIndex));
            continue;
        }

        auto matchCandidate = findBestMatch(
            dstSubnode,
            dstIndex,
            srcSubnodesByDiaId,
            srcSubnodes,
            processedSrc);

        if (matchCandidate.has_value()) {
            auto srcIndicesIt = srcSubnodesByDiaId.find(dstSubnode.id.id);
            if (srcIndicesIt != srcSubnodesByDiaId.end()) {
                int unprocessedSrcCount = countUnprocessedNodes(
                    srcIndicesIt->second, srcSubnodes, processedSrc);

                if (shouldPreferInsert(
                        dstSubnode,
                        dstSubnodesByDiaId,
                        dstSubnodes,
                        processedDst,
                        unprocessedSrcCount)) {
                    HSLOG_TRACE(
                        _cat,
                        hstd::fmt("Preferring insert over match due to "
                                  "duplicate handling"));
                    matchCandidate.reset();
                }
            }
        }

        if (!matchCandidate.has_value()) {
            HSLOG_TRACE(
                _cat,
                hstd::fmt(
                    "Creating Insert edit for dstIndex:{} dstSubnode:{}",
                    dstIndex,
                    dstSubnode));
            results.emplace_back(DiaEdit::Insert{
                .dstNode = dstSubnode, .dstIndex = dstIndex});
            processedDst.insert(dstSubnode.id);
            continue;
        }

        const auto& srcSubnode = srcSubnodes.at(matchCandidate->srcIndex);
        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Processing match: srcIndex:{} -> dstIndex:{} isExact:{} "
                "isMove:{}",
                matchCandidate->srcIndex,
                dstIndex,
                matchCandidate->isExactMatch,
                matchCandidate->isMove));

        processMatchedSubnodes(
            srcSubnode,
            dstSubnode,
            matchCandidate->srcIndex,
            dstIndex,
            results,
            processedSrc,
            processedDst);
    }

    for (int srcIndex = 0; srcIndex < srcSubnodes.size(); ++srcIndex) {
        const auto& srcSubnode = srcSubnodes.at(srcIndex);
        if (!processedSrc.contains(srcSubnode.id)) {
            HSLOG_TRACE(
                _cat,
                hstd::fmt(
                    "Creating Delete edit for srcIndex:{} srcSubnode:{}",
                    srcIndex,
                    srcSubnode));
            results.emplace_back(DiaEdit::Delete{
                .srcNode = srcSubnode, .srcIndex = srcIndex});
        }
    }
}

void processMatchedSubnodes(
    const DiaAdapter&     srcSubnode,
    const DiaAdapter&     dstSubnode,
    int                   srcIndex,
    int                   dstIndex,
    std::vector<DiaEdit>& results,
    ProcessedNodes&       processedSrc,
    ProcessedNodes&       processedDst) {

    // Compare DiaId (content) instead of DiaUniqId (content + position)
    if (srcSubnode.id.id == dstSubnode.id.id) {
        if (srcIndex != dstIndex) {
            HSLOG_TRACE(
                _cat,
                hstd::fmt(
                    "Creating Move edit from srcIndex:{} to dstIndex:{} "
                    "for node:{}",
                    srcIndex,
                    dstIndex,
                    srcSubnode));
            results.emplace_back(DiaEdit::Move{
                .srcNode  = srcSubnode,
                .dstNode  = dstSubnode,
                .srcIndex = srcIndex,
                .dstIndex = dstIndex});
        } else {
            HSLOG_TRACE(
                _cat,
                hstd::fmt(
                    "Nodes identical at same position, no edit needed for "
                    "srcIndex:{}",
                    srcIndex));
        }
        diffSubnodes(srcSubnode, dstSubnode, results);
    } else {
        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Creating Update edit from srcIndex:{} to dstIndex:{} "
                "srcSubnode:{} dstSubnode:{}",
                srcIndex,
                dstIndex,
                srcSubnode,
                dstSubnode));
        results.emplace_back(DiaEdit::Update{
            .srcNode  = srcSubnode,
            .dstNode  = dstSubnode,
            .srcIndex = srcIndex,
            .dstIndex = dstIndex});
        diffSubnodes(srcSubnode, dstSubnode, results);
    }

    processedSrc.insert(srcSubnode.id);
    processedDst.insert(dstSubnode.id);
}
} // namespace

std::vector<DiaEdit> getEdits(
    const DiaAdapter&  srcRoot,
    const DiaAdapter&  dstRoot,
    const DiaEditConf& confi) {
    std::vector<DiaEdit> results;
    HSLOG_INFO(_cat, "getEdits");
    HSLOG_DEPTH_SCOPE_ANON();

    if (srcRoot.getKind() != dstRoot.getKind()) {
        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Creating root Update edit for kind mismatch {} -> {}",
                srcRoot.getKind(),
                dstRoot.getKind()));
        results.emplace_back(DiaEdit::Update{
            .srcNode  = srcRoot,
            .dstNode  = dstRoot,
            .srcIndex = 0,
            .dstIndex = 0});
    } else {
        diffSubnodes(srcRoot, dstRoot, results);
    }

    return results;
}

hstd::ColText DiaAdapter::format(const TreeReprConf& conf) const {
    hstd::ColStream                          os;
    hstd::Func<void(DiaAdapter const&, int)> aux;

    aux = [&](DiaAdapter const& node, int level) {
        os.indent(level * 2);
        std::size_t node_hash{};
        switch_dia_ptr(
            node.ctx->at(node.id.id), [&]<typename T>(T const* p) {
                node_hash = std::hash<T>{}(*p);
            });

        os << hstd::fmt(
            "{} ID:{} HASH:0x{:X} UNIQ-ID:{}\n",
            node.get()->getKind(),
            node.id.id,
            node_hash,
            node.id);
        for (auto const& sub : node.sub(true)) { aux(sub, level + 1); }
    };

    aux(*this, 0);
    return os;
}

hstd::ext::Graphviz::Graph getEditMappingGraphviz(
    const DiaAdapter&           src,
    const DiaAdapter&           dst,
    const std::vector<DiaEdit>& edits) {
    using namespace hstd::ext;
    using G = Graphviz;

    auto g = G::Graph{"g"_ss};
    g.defaultNode.setShape(G::Node::Shape::rectangle);
    g.setRankDirection(G::Graph::RankDirection::LR);

    hstd::UnorderedMap<DiaUniqId, G::Node>                       gvNodes;
    hstd::UnorderedMap<std::pair<DiaUniqId, DiaUniqId>, G::Edge> gvEdges;

    hstd::Func<G::Node(G::Graph&, DiaAdapter const& it)> aux;
    aux = [&](G::Graph& gvCluster, DiaAdapter const& it) -> G::Node {
        std::string label;
        if (it.getKind() == DiaNodeKind::Item) {
            auto item = it.get()->dyn_cast<DiaNodeItem>();
            label += item->getSubtree().getCleanTitle();
            label += "\n";
        }
        label += hstd::fmt1(it.id);
        G::Node res = gvCluster.node(
            hstd::fmt("0x{:X}", std::hash<std::string>{}(label)));
        res.setLabel(label);
        gvNodes.insert_or_assign(it.id, res);
        auto tmp = it.sub(true);
        std::reverse(tmp.begin(), tmp.end());
        for (auto const& sub : tmp) {
            auto gvSub = aux(gvCluster, sub);
            auto edge  = gvCluster.edge(res, gvSub);
            edge.setStyle("invis");
        }

        return res;
    };


    auto g1 = g.newSubgraph("g1");
    aux(g1, src);
    auto g2 = g.newSubgraph("g2");
    aux(g2, dst);

    for (auto const& edit : edits) {
        if (edit.isDelete()) {
            gvNodes.at(edit.getSrcAffected().id).setColor("red");
        } else if (edit.isInsert()) {
            gvNodes.at(edit.getDstAffected().id).setColor("green");
        } else if (edit.isUpdate()) {
            auto gvSrc    = gvNodes.at(edit.getSrcAffected().id);
            auto gvDst    = gvNodes.at(edit.getDstAffected().id);
            auto gvUpdate = g.edge(gvSrc, gvDst);
            gvSrc.setColor("purple");
            gvDst.setColor("purple");
            gvUpdate.setConstraint(false);
            gvUpdate.setAttr("headport", "e"_ss);
            gvUpdate.setAttr("tailport", "e"_ss);
        } else {
            auto gvSrc  = gvNodes.at(edit.getSrcAffected().id);
            auto gvDst  = gvNodes.at(edit.getDstAffected().id);
            auto gvMove = g.edge(gvSrc, gvDst);
            gvSrc.setColor("cyan");
            gvDst.setColor("cyan");
            gvMove.setConstraint(false);
            gvMove.setAttr("headport", "e"_ss);
            gvMove.setAttr("tailport", "e"_ss);
        }
    }

    return g;
}
