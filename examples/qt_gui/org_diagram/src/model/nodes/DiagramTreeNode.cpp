#include "DiagramTreeNode.hpp"
#include "DiagramTreeNodeCanvas.hpp"
#include "DiagramTreeNodeItem.hpp"
#include "DiagramTreeNodeLayer.hpp"

#include <src/utils/common.hpp>


int DiagramTreeNode::getColumnCount() const { return 1; }

void DiagramTreeNode::addSubnode(std::shared_ptr<DiagramTreeNode> node) {
    node->parent = shared_from_this();
    subnodes.push_back(node);
    HSLOG_TRACKED_EMIT(
        get_tracker(),
        subnodeAdded,
        static_cast<int>(subnodes.size()) - 1);
}

void DiagramTreeNode::removeSubnode(int index) {
    if (index >= 0 && index < static_cast<int>(subnodes.size())) {
        subnodes.at(index)->parent.reset();
        HSLOG_TRACKED_EMIT(get_tracker(), subnodeAboutToBeRemoved, index);
        subnodes.erase(subnodes.begin() + index);
        HSLOG_TRACKED_EMIT(get_tracker(), subnodeRemoved);
    }
}

void DiagramTreeNode::updateData() {
    HSLOG_TRACKED_EMIT(get_tracker(), dataChanged);
}

void DiagramTreeNode::insertSubnode(
    const hstd::SPtr<DiagramTreeNode>& node,
    int                                index) {
    node->parent = shared_from_this();
    subnodes.insert(subnodes.begin() + index, node);
    HSLOG_TRACKED_EMIT(get_tracker(), subnodeAdded, index);
}

void DiagramTreeNode::apply(
    const hstd::Vec<HistoryManager::AstEdit>& edit) {}

hstd::ColText DiagramTreeNode::format() const {
    hstd::ColStream                                                 os;
    hstd::Func<void(hstd::SPtr<DiagramTreeNode const> const&, int)> aux;

    aux = [&](hstd::SPtr<DiagramTreeNode const> const& node, int level) {
        os.indent(level * 2);
        os << hstd::fmt1(node->id);
        os << "\n";

        for (auto const& sub : node->subnodes) { aux(sub, level + 1); }
    };

    aux(shared_from_this(), 0);

    return os;
}


DiagramTreeNode::DiagramTreeNode(const org::imm::ImmAdapter& id)
    : id{id} {}

DiagramTreeNode::Ptr DiagramTreeNode::FromDocument(
    org::imm::ImmAdapterT<org::imm::ImmDocument> const& root) {
    HSLOG_DEPTH_SCOPE_ANON();
    auto canvas = std::make_shared<DiagramTreeNodeCanvas>(root);
    HSLOG_INFO(_cat, hstd::fmt("Creating canvas from {}", root.uniq()));

    for (auto const& layerNode : root.subAs<org::imm::ImmSubtree>()) {
        auto layer = std::make_shared<DiagramTreeNodeLayer>(layerNode);
        for (auto const& subtreeNode :
             layerNode.subAs<org::imm::ImmSubtree>()) {
            layer->addSubnode(
                DiagramTreeNodeItem::FromSubtreeItem(subtreeNode));
        }

        canvas->addSubnode(layer);
    }

    return canvas;
}

#include "DiagramTreeNode.moc"

void DiagramTreeNode::Context::incl(
    const hstd::SPtr<DiagramTreeNode>& node) {
    LOGIC_ASSERTION_CHECK(
        !trackingTreeId.contains(node->uniq()),
        "Id {} is already tracked in the diagram tree context",
        node->uniq());
    trackingTreeId.insert_or_assign(node->uniq(), node->weak_from_this());
}

void DiagramTreeNode::Context::excl(const org::imm::ImmUniqId& id) {
    trackingTreeId.erase(id);
}
