#include "DiagramTreeNode.hpp"
#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "model.tree"


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


DiaId FromDocument(
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
    return context->add(canvas);
}
