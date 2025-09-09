#include "DiagramTreeNode.hpp"
#include <src/utils/common.hpp>

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

DiaNodeItem FromSubtreeItem(
    hstd::SPtr<DiaContext> const&                      context,
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    auto position = getStructuredProperty<DiaNodeItem::Pos>(
        subtree, DiaPropertyNames::diagramPosition);

    if (!position.has_value()
        || hasArgsProperty(subtree, DiaPropertyNames::isDiagramNode)) {
        throw hstd::logic_assertion_error::init(hstd::fmt(
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

    DiaNodeItem item;
    item.id = subtree;
    return item;
}

bool isSubtreeItem(
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    return getStructuredProperty<DiaNodeItem::Pos>(
               subtree, DiaPropertyNames::diagramPosition)
               .has_value()
        && hasArgsProperty(subtree, DiaPropertyNames::isDiagramNode);
}


DiaId FromSubtreeItemRec(
    hstd::SPtr<DiaContext> const&                      context,
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {

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
    HSLOG_DEPTH_SCOPE_ANON();
    auto canvas = DiaNodeCanvas{};
    canvas.id   = root;
    HSLOG_INFO(_cat, hstd::fmt("Creating canvas from {}", root.uniq()));

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

void diffSubnodes(
    const DiaAdapter&     srcNode,
    const DiaAdapter&     dstNode,
    std::vector<DiaEdit>& results) {

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
        const auto& dstSubnode = dstSubnodes.at(dstIndex);

        if (processedDst.contains(dstSubnode.id)) { continue; }

        auto matchingSrcIndex = findMatchingByDiaId(
            dstSubnode, srcSubnodesByDiaId, srcSubnodes, processedSrc);

        if (matchingSrcIndex.has_value()) {
            auto srcIndicesIt = srcSubnodesByDiaId.find(dstSubnode.id.id);
            int  unprocessedSrcCount = countUnprocessedNodes(
                srcIndicesIt->second, srcSubnodes, processedSrc);

            if (shouldPreferInsert(
                    dstSubnode,
                    dstSubnodesByDiaId,
                    dstSubnodes,
                    processedDst,
                    unprocessedSrcCount)) {
                matchingSrcIndex.reset();
            }
        }

        if (!matchingSrcIndex.has_value()) {
            matchingSrcIndex = findMatchingByKind(
                dstSubnode, srcSubnodes, processedSrc);
        }

        if (!matchingSrcIndex.has_value()) {
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

        const auto& srcSubnode = srcSubnodes.at(matchingSrcIndex.value());
        processMatchedSubnodes(
            srcSubnode,
            dstSubnode,
            matchingSrcIndex.value(),
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

    if (srcSubnode.id == dstSubnode.id) {
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
