#include "DiagramTreeNode.hpp"
#include "DiagramTreeNodeCanvas.hpp"
#include "DiagramTreeNodeItem.hpp"
#include "DiagramTreeNodeLayer.hpp"

#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "model.tree"

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


DiagramTreeNode::DiagramTreeNode(
    const hstd::SPtr<Context>&  context,
    const org::imm::ImmAdapter& id)
    : id{id}, context{context->weak_from_this()} {}

DiagramTreeNode::Ptr DiagramTreeNode::FromDocument(
    hstd::SPtr<Context> const&                          context,
    org::imm::ImmAdapterT<org::imm::ImmDocument> const& root) {
    HSLOG_DEPTH_SCOPE_ANON();
    auto canvas = std::make_shared<DiagramTreeNodeCanvas>(context, root);
    HSLOG_INFO(_cat, hstd::fmt("Creating canvas from {}", root.uniq()));

    for (auto const& layerNode : root.subAs<org::imm::ImmSubtree>()) {
        auto layer = std::make_shared<DiagramTreeNodeLayer>(
            context, layerNode);
        for (auto const& subtreeNode :
             layerNode.subAs<org::imm::ImmSubtree>()) {
            layer->addSubnode(DiagramTreeNodeItem::FromSubtreeItem(
                context, subtreeNode));
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


void applyEdits(
    std::shared_ptr<DiagramTreeNode>            root,
    std::vector<HistoryManager::AstEdit> const& edits,
    std::shared_ptr<org::imm::ImmAstContext>    context) {
    HSLOG_DEPTH_SCOPE_ANON();

    using AstEdit      = HistoryManager::AstEdit;
    auto  tree_context = root->getContext();
    auto& nodeMap      = tree_context->trackingTreeId;

    for (auto const& key : hstd::sorted(nodeMap.keys())) {
        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "key:{} node:0x{:X}",
                key,
                reinterpret_cast<std::ptrdiff_t>(
                    hstd::safe_wptr_lock(nodeMap.at(key)).get())));
    }

    std::vector<AstEdit> sortedEdits = edits;
    std::sort(
        sortedEdits.begin(),
        sortedEdits.end(),
        [&](AstEdit const& a, AstEdit const& b) {
            auto getDepth = [&](org::imm::ImmUniqId const& id) -> int {
                int  depth   = 0;
                auto adapter = context->adapt(id);
                while (adapter.getParent()) {
                    ++depth;
                    adapter = adapter.getParent().value();
                }
                return depth;
            };

            int depthA = a.isReplace() ? getDepth(a.getReplace().src)
                       : a.isDelete()  ? getDepth(a.getDelete().id)
                                       : getDepth(a.getInsert().id);
            int depthB = b.isReplace() ? getDepth(b.getReplace().src)
                       : b.isDelete()  ? getDepth(b.getDelete().id)
                                       : getDepth(b.getInsert().id);

            return depthA < depthB;
        });

    for (auto const& edit : sortedEdits) {
        HSLOG_INFO(_cat, hstd::fmt("edit {}", edit));
        if (edit.isDelete()) {
            auto id = edit.getDelete().id;
            if (nodeMap.contains(id)) {
                auto node = hstd::safe_wptr_lock(nodeMap.at(id));
                for (auto& [parentId, parentNode] : nodeMap) {
                    auto& subs = hstd::safe_wptr_lock(parentNode)
                                     ->subnodes;
                    auto it = std::find(subs.begin(), subs.end(), node);
                    if (it != subs.end()) {
                        subs.erase(it);
                        break;
                    }
                }
                nodeMap.erase(id);
            } else {
                HSLOG_WARNING(
                    _cat,
                    "source node map does not contain delete operation");
            }
        } else if (edit.isInsert()) {
            auto id      = edit.getInsert().id;
            auto adapter = context->adapt(id);
            if (adapter.getParent()) {
                auto parentId = adapter.getParent().value().uniq();
                if (nodeMap.contains(parentId)) {
                    auto newNode = std::make_shared<DiagramTreeNode>(
                        tree_context, adapter);
                    hstd::safe_wptr_lock(nodeMap.at(parentId))
                        ->subnodes.push_back(newNode);
                    nodeMap.insert_or_assign(id, newNode);
                }
            }
        } else if (edit.isReplace()) {
            auto src = edit.getReplace().src;
            auto dst = edit.getReplace().dst;
            if (nodeMap.contains(src)) {
                auto oldNode    = hstd::safe_wptr_lock(nodeMap.at(src));
                auto newAdapter = context->adapt(dst);
                auto newNode    = std::make_shared<DiagramTreeNode>(
                    tree_context, newAdapter);
                newNode->subnodes = oldNode->subnodes;

                for (auto& [parentId, parentNode] : nodeMap) {
                    auto& subs = hstd::safe_wptr_lock(parentNode)
                                     ->subnodes;
                    auto it = std::find(subs.begin(), subs.end(), oldNode);
                    if (it != subs.end()) {
                        *it = newNode;
                        break;
                    }
                }

                nodeMap.erase(src);
                nodeMap.insert_or_assign(dst, newNode);

                if (oldNode == root) { root = newNode; }
            } else {
                HSLOG_WARNING(
                    _cat,
                    "node map does not contain ID for the replace source");
            }
        }
    }

    for (auto const& key : hstd::sorted(nodeMap.keys())) {
        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "key:{} node:0x{:X}",
                key,
                reinterpret_cast<std::ptrdiff_t>(
                    hstd::safe_wptr_lock(nodeMap.at(key)).get())));
    }
}
