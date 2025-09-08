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

std::vector<DiaEdit> getEdits(
    const DiaAdapter&  srcRoot,
    const DiaAdapter&  dstRoot,
    const DiaEditConf& confi) {
    std::vector<DiaEdit> results;

    std::function<void(const DiaAdapter&, const DiaAdapter&)> diffNodes =
        [&](const DiaAdapter& srcNode, const DiaAdapter& dstNode) {
            if (srcNode.getKind() != dstNode.getKind()) { return; }

            auto srcChildren = srcNode.sub(true);
            auto dstChildren = dstNode.sub(true);

            std::unordered_map<DiaId, std::vector<int>> srcChildrenByDiaId;
            std::unordered_map<DiaId, std::vector<int>> dstChildrenByDiaId;

            for (int i = 0; i < srcChildren.size(); ++i) {
                srcChildrenByDiaId[srcChildren.at(i).id.id].push_back(i);
            }

            for (int i = 0; i < dstChildren.size(); ++i) {
                dstChildrenByDiaId[dstChildren.at(i).id.id].push_back(i);
            }

            std::unordered_set<DiaUniqId> processedSrc;
            std::unordered_set<DiaUniqId> processedDst;

            for (int dstIndex = 0; dstIndex < dstChildren.size();
                 ++dstIndex) {
                const auto& dstChild = dstChildren.at(dstIndex);

                if (processedDst.contains(dstChild.id)) { continue; }

                auto srcIndicesIt = srcChildrenByDiaId.find(
                    dstChild.id.id);
                if (srcIndicesIt == srcChildrenByDiaId.end()) {
                    results.emplace_back(DiaEdit::Insert{
                        .dstNode = dstChild, .dstIndex = dstIndex});
                    processedDst.insert(dstChild.id);
                    continue;
                }

                std::optional<int> matchingSrcIndex;
                for (int srcIndex : srcIndicesIt->second) {
                    const auto& srcChild = srcChildren.at(srcIndex);
                    if (!processedSrc.contains(srcChild.id)
                        && srcChild.getKind() == dstChild.getKind()) {
                        if (srcChild.id == dstChild.id) {
                            matchingSrcIndex = srcIndex;
                            break;
                        }
                        if (!matchingSrcIndex.has_value()) {
                            matchingSrcIndex = srcIndex;
                        }
                    }
                }

                if (matchingSrcIndex.has_value()) {
                    const auto& srcChild = srcChildren.at(
                        matchingSrcIndex.value());

                    if (srcChild.id == dstChild.id) {
                        if (matchingSrcIndex.value() != dstIndex) {
                            results.emplace_back(DiaEdit::Move{
                                .srcNode  = srcChild,
                                .dstNode  = dstChild,
                                .srcIndex = matchingSrcIndex.value(),
                                .dstIndex = dstIndex});
                        }
                        diffNodes(srcChild, dstChild);
                    } else {
                        results.emplace_back(DiaEdit::Update{
                            .srcNode  = srcChild,
                            .dstNode  = dstChild,
                            .srcIndex = matchingSrcIndex.value(),
                            .dstIndex = dstIndex});
                        diffNodes(srcChild, dstChild);
                    }

                    processedSrc.insert(srcChild.id);
                    processedDst.insert(dstChild.id);
                }
            }

            for (int srcIndex = 0; srcIndex < srcChildren.size();
                 ++srcIndex) {
                const auto& srcChild = srcChildren.at(srcIndex);
                if (!processedSrc.contains(srcChild.id)) {
                    results.emplace_back(DiaEdit::Delete{
                        .srcNode = srcChild, .srcIndex = srcIndex});
                }
            }
        };

    if (srcRoot.getKind() != dstRoot.getKind()) {
        results.emplace_back(DiaEdit::Update{
            .srcNode  = srcRoot,
            .dstNode  = dstRoot,
            .srcIndex = 0,
            .dstIndex = 0});
    } else {
        diffNodes(srcRoot, dstRoot);
    }

    return results;
}

hstd::ColText DiaAdapter::format(const TreeReprConf& conf) const {
    hstd::ColStream                          os;
    hstd::Func<void(DiaAdapter const&, int)> aux;

    aux = [&](DiaAdapter const& node, int level) {
        os.indent(level * 2);
        os << hstd::fmt1(node.get()->getKind());
        os << "\n";
        for (auto const& sub : node.sub(true)) { aux(sub, level + 1); }
    };

    aux(*this, 0);
    return os;
}
