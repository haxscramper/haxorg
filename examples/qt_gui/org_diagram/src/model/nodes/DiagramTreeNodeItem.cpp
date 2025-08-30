#include "DiagramTreeNodeItem.hpp"


hstd::SPtr<DiagramTreeNodeItem> DiagramTreeNodeItem::FromSubtreeItem(
    const org::imm::ImmAdapterT<org::imm::ImmSubtree>& subtree) {
    auto position = getStructuredProperty<DiagramTreeNodeItem::Pos>(
        subtree, PropertyNames::diagramPosition);

    if (!position.has_value()
        || hasProperty(subtree, PropertyNames::isDiagramNode)) {
        throw hstd::logic_assertion_error::init(hstd::fmt(
            "{} (title: {}) does not meet the criteria: top-level subtree "
            "for subtree item must have {} and {} properties.",
            subtree.uniq(),
            subtree.getCleanTitle(),
            PropertyNames::diagramPosition,
            PropertyNames::isDiagramNode));
    }

    auto item = std::make_shared<DiagramTreeNodeItem>(subtree);

    for (auto const& sub : subtree.subAs<org::imm::ImmSubtree>()) {
        if (hasProperty(sub, PropertyNames::isDiagramNode)) {
            item->addSubnode(FromSubtreeItem(sub));
        }
    }

    return item;
}
