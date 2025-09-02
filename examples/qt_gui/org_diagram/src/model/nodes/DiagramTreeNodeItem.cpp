#include "DiagramTreeNodeItem.hpp"


hstd::SPtr<DiagramTreeNodeItem> DiagramTreeNodeItem::FromSubtreeItem(
    hstd::SPtr<Context> const&                         context,
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    auto position = getStructuredProperty<DiagramTreeNodeItem::Pos>(
        subtree, PropertyNames::diagramPosition);

    if (!position.has_value()
        || hasArgsProperty(subtree, PropertyNames::isDiagramNode)) {
        throw hstd::logic_assertion_error::init(hstd::fmt(
            "{} (title: {}) does not meet the criteria: top-level subtree "
            "for subtree item must have :prop_json:{} and :prop_args:{} "
            "properties. has position:{} has diagram node:{}",
            subtree.uniq(),
            subtree.getCleanTitle(),
            PropertyNames::diagramPosition,
            PropertyNames::isDiagramNode,
            position.has_value() ? "true" : position.error(),
            hasArgsProperty(subtree, PropertyNames::isDiagramNode)));
    }

    return std::make_shared<DiagramTreeNodeItem>(context, subtree);
}

hstd::SPtr<DiagramTreeNodeItem> DiagramTreeNodeItem::FromSubtreeItemRec(
    const hstd::SPtr<Context>&                         context,
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {

    auto result = FromSubtreeItem(context, subtree);

    for (auto const& sub : subtree.subAs<org::imm::ImmSubtree>()) {
        if (isSubtreeItem(sub)) {
            result->addSubnode(FromSubtreeItem(context, sub));
        }
    }

    return result;
}

bool DiagramTreeNodeItem::isSubtreeItem(
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    return getStructuredProperty<DiagramTreeNodeItem::Pos>(
               subtree, PropertyNames::diagramPosition)
               .has_value()
        && hasArgsProperty(subtree, PropertyNames::isDiagramNode);
}
