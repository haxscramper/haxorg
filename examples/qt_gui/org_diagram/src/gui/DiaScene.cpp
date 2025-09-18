#include "DiaScene.hpp"

void DiaScene::logSceneRoot() {
    if (rootNode == nullptr) {
        HSLOG_TRACE(_cat, "<nullptr>");
    } else {
        HSLOG_TRACE(_cat, rootNode->treeRepr().toString(false));
    }
}

void DiaScene::drawBackground(QPainter* painter, const QRectF& rect) {
    QGraphicsScene::drawBackground(painter, rect);

    if (!showGrid) { return; }

    painter->setPen(QPen{gridColor, 1});

    // Calculate grid bounds
    int left = static_cast<int>(rect.left())
             - (static_cast<int>(rect.left()) % gridSnap);
    int top = static_cast<int>(rect.top())
            - (static_cast<int>(rect.top()) % gridSnap);
    int right  = static_cast<int>(rect.right());
    int bottom = static_cast<int>(rect.bottom());

    // Draw vertical lines
    for (int x = left; x <= right; x += gridSnap) {
        painter->drawLine(
            x,
            static_cast<int>(rect.top()),
            x,
            static_cast<int>(rect.bottom()));
    }

    // Draw horizontal lines
    for (int y = top; y <= bottom; y += gridSnap) {
        painter->drawLine(
            static_cast<int>(rect.left()),
            y,
            static_cast<int>(rect.right()),
            y);
    }
}

void DiaScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem*      item = itemAt(event->scenePos(), QTransform{});
    DiaSceneItemVisual* clickedNode = dynamic_cast<DiaSceneItemVisual*>(
        item);

    if (event->modifiers() & Qt::ControlModifier) {
        // Multi-selection mode
        if (clickedNode
            && std::find(
                   selectedNodes.begin(), selectedNodes.end(), clickedNode)
                   == selectedNodes.end()) {
            selectedNodes.push_back(clickedNode);
            clickedNode->setSelected(true);
        }
    } else {
        // Single selection mode
        for (auto node : selectedNodes) { node->setSelected(false); }
        selectedNodes.clear();

        if (clickedNode) {
            selectedNodes.push_back(clickedNode);
            clickedNode->setSelected(true);
        }

        selectedNode = clickedNode;
        HSLOG_TRACKED_EMIT(get_tracker(), nodeSelected, selectedNode);
    }

    if (event->button() == Qt::RightButton && selectedNode) {
        auto visualNode = dynamic_cast<DiaSceneItemVisual*>(selectedNode);
        if (visualNode && !dynamic_cast<DiaSceneItemEdge*>(visualNode)) {
            if (arrowSource == nullptr) {
                arrowSource = visualNode;
            } else {
                if (arrowSource != visualNode) {
                    auto edge = new DiaSceneItemEdge(
                        arrowSource, visualNode);
                    addItem(edge);

                    auto layer = findFirstLayer();
                    if (layer) {
                        layer->addChild(edge);
                    } else {
                        rootNode->addChild(edge);
                    }
                    updateTreeView();
                }
                arrowSource = nullptr;
            }
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

DiaSceneItem::Ptr DiaScene::setRootAdapter(const DiaAdapter& a) {
    TRACKED_FUNCTION("setRootAdapter");
    rootNode            = addAdapterRec(a);
    treeModel->rootNode = rootNode;
    return rootNode;
}

DiaSceneItem::Ptr DiaScene::resetRootAdapter(
    const DiaAdapter&           a,
    const std::vector<DiaEdit>& edits) {
    TRACKED_FUNCTION("resetRootAdapter");
    if (edits.empty()) { return rootNode; }
    DiaSceneItem* rootUpdate = nullptr;
    for (auto const& edit : edits) {
        treeModel->beginEditApply(edit);
        switch (edit.getKind()) {
            case DiaEdit::Kind::Delete: {
                DiaSceneItem::Ptr item   = getItemForId(edit.getSrc().id);
                auto const&       del    = edit.getDelete();
                int               src    = del.srcIndex;
                auto              parent = item->parent;

                LOGIC_ASSERTION_CHECK(
                    item->parent->subnodes.at(src) == item,
                    "Delete of item at index {} should have removed the "
                    "scene item {}, but the parent {} has item "
                    "{} at this index",
                    src,
                    hstd::descObjectPtr(item),
                    hstd::descObjectPtr(parent),
                    hstd::descObjectPtr(parent->subnodes.at(src)));

                parent->subnodes.erase(parent->subnodes.begin() + src);
                deleteSceneItem(item);
                break;
            }
            case DiaEdit::Kind::Insert: {
                DiaSceneItem::Ptr item = getItemForId(edit.getSrc().id);
                break;
            }
            case DiaEdit::Kind::Update: {
                DiaSceneItem::Ptr item = getItemForId(edit.getSrc().id);
                auto              oldSubnodes = item->subnodes;
                break;
            }
            default: {
                logic_todo_impl();
            }
        }
        treeModel->endEditApply(edit);
    }

    LOGIC_ASSERTION_CHECK(
        rootUpdate != nullptr,
        "Non-empty set of edits is guaranteed to change the root node to "
        "a new structure, but the root update has not happened.");
    rootNode = rootUpdate;

    return rootUpdate;
}

DiaSceneItem::UPtr DiaScene::addAdapterNonRec(const DiaAdapter& a) {
    switch (a.getKind()) {
        case DiaNodeKind::Group:
        case DiaNodeKind::Item: {
            auto it   = a.as<DiaNodeItem>();
            auto node = addNewItem<DiaSceneItemRectangle>(
                QString::fromStdString(it->getSubtree().getCleanTitle()));
            auto pos = it->getPos();
            node->setPos(pos.x, pos.y);
            node->color = Qt::green;
            return node;
        }
        case DiaNodeKind::Canvas: {
            auto canvas = addNewItem<DiaSceneItemCanvas>();
            return canvas;
        }
        case DiaNodeKind::Layer: {
            auto layer = addNewItem<DiaSceneItemLayer>();
            return layer;
        }
    }
}

DiaSceneItemGroup* DiaScene::findGroupContaining(
    DiaSceneItemVisual* node) {
    for (auto item : items()) {
        if (auto group = dynamic_cast<DiaSceneItemGroup*>(item)) {
            if (std::find(
                    group->groupedNodes.begin(),
                    group->groupedNodes.end(),
                    node)
                != group->groupedNodes.end()) {
                return group;
            }
        }
    }
    return nullptr;
}

std::vector<DiaSceneItemVisual*> DiaScene::findCommonParentNodes(
    const std::vector<DiaSceneItemVisual*>& nodes) {
    std::vector<DiaSceneItemVisual*> result;
    std::set<DiaSceneItemVisual*>    processed;

    for (auto node : nodes) {
        if (dynamic_cast<DiaSceneItemEdge*>(node)) {
            continue; // Skip edges
        }
        if (processed.count(node)) { continue; }

        auto group = findGroupContaining(node);
        if (group) {
            // Check if all nodes in this group are in the selection
            bool allNodesSelected = true;
            for (auto groupNode : group->groupedNodes) {
                if (std::find(nodes.begin(), nodes.end(), groupNode)
                    == nodes.end()) {
                    allNodesSelected = false;
                    break;
                }
            }

            if (allNodesSelected) {
                result.push_back(group);
                for (auto groupNode : group->groupedNodes) {
                    processed.insert(groupNode);
                }
            } else {
                result.push_back(node);
                processed.insert(node);
            }
        } else {
            result.push_back(node);
            processed.insert(node);
        }
    }

    return result;
}

void DiaScene::createGroupFromSelection() {
    // Filter out edges and get only visual nodes
    std::vector<DiaSceneItemVisual*> visualNodes;
    for (auto node : selectedNodes) {
        if (!dynamic_cast<DiaSceneItemEdge*>(node)) {
            visualNodes.push_back(node);
        }
    }

    if (visualNodes.size() < 2) {
        QMessageBox::warning(
            nullptr,
            "Error",
            "Please select at least 2 non-edge nodes to create a "
            "group.");
        return;
    }

    // Find common parent nodes
    auto nodesToGroup = findCommonParentNodes(visualNodes);

    if (nodesToGroup.empty()) {
        QMessageBox::warning(nullptr, "Error", "No valid nodes to group.");
        return;
    }

    // Remove nodes from their current groups if any
    for (auto node : nodesToGroup) {
        auto currentGroup = findGroupContaining(node);
        if (currentGroup) { currentGroup->removeFromGroup(node); }
    }

    // Create new group
    auto group = new DiaSceneItemGroup{"Group"};
    addItem(group);

    // Add nodes to the group
    for (auto node : nodesToGroup) { group->addToGroup(node); }

    group->updateBoundsToFitNodes();

    // Add to scene hierarchy
    auto layer = findFirstLayer();
    if (layer) {
        // Convert to shared_ptr if using shared_ptr management
        layer->addChild(group);
    } else {
        rootNode->addChild(group);
    }

    // Clear selection
    for (auto node : selectedNodes) { node->setSelected(false); }
    selectedNodes.clear();

    updateTreeView();
}
