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
                    logic_todo_impl();
                    // auto edge = addNewItem<DiaSceneItemEdge>(
                    //     visualNode->staleAdapter, arrowSource,
                    //     visualNode);

                    // auto layer = findFirstLayer();
                    // if (layer) {
                    //     layer->add(std::move(edge));
                    // } else {
                    //     rootNode->add(std::move(edge));
                    // }
                    // updateTreeView();
                }
                arrowSource = nullptr;
            }
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void DiaScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (!selectedNode && (event->buttons() & Qt::LeftButton)) {
        auto img = dynamic_cast<DiaSceneItemImage*>(selectedNode);
        if (!img || !img->isResizing) {
            QPointF newPos = event->scenePos() - selectedNode->dragOffset;
            selectedNode->setPosition(newPos, gridSnap);
            return;
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

DiaSceneItem* DiaScene::setRootAdapter(const DiaAdapter& a) {
    TRACKED_FUNCTION("setRootAdapter");
    rootNode            = addAdapterRec(a);
    treeModel->rootNode = rootNode.get();
    return rootNode.get();
}

void DiaScene::applyPartialEditStep(DiaEdit const& edit) {
    TRACKED_SCOPE(hstd::fmt("Applying edit {}", edit));
    HSLOG_INFO(
        _cat,
        hstd::fmt(
            "SRC:{} DST:{}",
            edit.hasSrc()
                ? hstd::fmt(
                      "{} {}",
                      edit.getSrc().getSelfPathFromRoot(),
                      hstd::descObjectPtr(getItemForId(edit.getSrc().id)))
                : "<>"_ss,
            edit.hasDst() ? hstd::fmt(
                                "{} {}",
                                edit.getDst().getSelfPathFromRoot(),
                                edit.isInsert()
                                    ? hstd::fmt("insert")
                                    : hstd::descObjectPtr(
                                          getItemForId(edit.getDst().id)))
                          : "<>"_ss));


    switch (edit.getKind()) {
        case DiaEdit::Kind::Delete: {
            DiaSceneItem* item   = getItemForId(edit.getSrc().id);
            auto const&   del    = edit.getDelete();
            int           src    = del.srcIndex;
            auto          parent = item->getParent();

            LOGIC_ASSERTION_CHECK(
                parent->at(src) == item,
                "Delete of item at index {} should have removed the "
                "scene item {}, but the parent {} has item "
                "{} at this index",
                src,
                hstd::descObjectPtr(item),
                hstd::descObjectPtr(parent),
                hstd::descObjectPtr(parent->at(src)));

            treeModel->beginEditApply(edit);
            parent->removeSubnode(src);
            treeModel->endEditApply(edit);
            break;
        }

        case DiaEdit::Kind::Move: {
            auto srcParent       = edit.getDst().getParentPathFromRoot();
            auto dstParent       = edit.getDst().getParentPathFromRoot();
            DiaSceneItem* parent = getItemForPath(srcParent);
            LOGIC_ASSERTION_CHECK(
                srcParent == dstParent,
                "Destination node and source node have different "
                "parent paths. SRC node parent is at path {}, while "
                "DST node parent is at path {}",
                srcParent,
                dstParent);

            auto const& m = edit.getMove();
            if (parent->at(m.dstIndex)->getDiaId()
                == m.dstNode.getDiaId()) {
                HSLOG_INFO(
                    _cat,
                    hstd::fmt(
                        "Move operation is a no-op. Parent {} already "
                        "has item with ID {} placed at index {}",
                        parent->getDiaId(),
                        m.dstNode.getDiaId(),
                        m.dstIndex));
            } else {
                HSLOG_INFO(
                    _cat,
                    hstd::fmt(
                        "Move operation is required. Parent {} has "
                        "item with ID {} at index {}, but the move "
                        "operation requires item with ID {}",
                        parent->getDiaId(),
                        parent->at(m.dstIndex)->getDiaId(),
                        m.dstIndex,
                        m.dstNode.getDiaId()));
                treeModel->beginEditApply(edit);
                parent->moveSubnode(m.srcIndex, m.dstIndex);
                treeModel->endEditApply(edit);
            }
            break;
        }

        case DiaEdit::Kind::Insert: {
            treeModel->beginEditApply(edit);
            DiaSceneItem* parent = getItemForPath(
                edit.getDst().getParentPathFromRoot());
            auto newNode = addAdapterRec(edit.getDst());
            parent->insertSubnode(
                std::move(newNode), edit.getInsert().dstIndex);
            treeModel->endEditApply(edit);
            break;
        }

        case DiaEdit::Kind::Update: {
            treeModel->beginEditApply(edit);
            DiaSceneItem* item        = getItemForId(edit.getSrc().id);
            auto          oldSubnodes = item->moveSubnodes();
            auto          newNode     = addAdapterNonRec(edit.getDst());
            newNode->setSubnodes(std::move(oldSubnodes));
            DiaSceneItem::UPtr* target = getMutableUPtrAtPath(
                edit.getSrc().getSelfPathFromRoot());
            auto parent = target->get()->getParent();
            if (parent == nullptr) {
                *target = std::move(newNode);
            } else {
                parent->setSubnode(
                    std::move(newNode), edit.getUpdate().dstIndex);
            }

            treeModel->endEditApply(edit);
            break;
        }
        default: {
            logic_todo_impl();
        }
    }
}

DiaSceneItem* DiaScene::resetRootAdapter(const hstd::Vec<DiaEdit>& edits) {
    TRACKED_FUNCTION("resetRootAdapter");
    if (edits.empty()) { return root(); }
    DiaSceneItem* originalRoot = root();
    for (auto const& edit : edits) { applyPartialEditStep(edit); }

    LOGIC_ASSERTION_CHECK(
        originalRoot != rootNode.get(),
        "Non-empty set of edits is guaranteed to change the root node to "
        "a new structure, but the root update has not happened.");

    treeModel->rootNode = rootNode.get();

    return rootNode.get();
}

void DiaScene::diaRootChanged(
    DiaVersionStore::DiaRootChange const& change) {
    TRACKED_SLOT("diaRootChange");
    if (rootNode.get() == nullptr) {
        setRootAdapter(change.newRoot);
    } else {
        resetRootAdapter(change.edits);
    }
}

DiaSceneItem::UPtr DiaScene::addAdapterNonRec(const DiaAdapter& a) {
    switch (a.getKind()) {
        case DiaNodeKind::Group:
        case DiaNodeKind::Item: {
            auto it    = a->dyn_cast<DiaNodeItem>();
            auto node  = addNewItem<DiaSceneItemRectangle>(a);
            node->name = QString::fromStdString(
                it->getSubtree().getCleanTitle());
            auto pos = it->getPos();
            node->setPos(pos.x, pos.y);
            node->color = Qt::green;
            return node;
        }
        case DiaNodeKind::Canvas: {
            auto canvas = addNewItem<DiaSceneItemCanvas>(a);
            return canvas;
        }
        case DiaNodeKind::Layer: {
            auto layer = addNewItem<DiaSceneItemLayer>(a);
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

void DiaScene::deleteSelectedNode() {
    TRACKED_SLOT("deleteSelectedNode");
    if (selectedNode == nullptr) {
        throw hstd::logic_assertion_error::init("No node selected");
    } else {
        version_store->applyDiaEdits(
            DiaVersionStore::EditGroup::Remove1ExistingNode(
                selectedNode->getActiveAdapter().uniq()));
    }
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

    logic_todo_impl();

    // // Create new group
    // auto group = addNewItem<DiaSceneItemGroup>("Group");

    // // Add nodes to the group
    // for (auto node : nodesToGroup) { group->addToGroup(node); }

    // group->updateBoundsToFitNodes();

    // // Add to scene hierarchy
    // auto layer = findFirstLayer();
    // if (layer) {
    //     // Convert to shared_ptr if using shared_ptr management
    //     layer->add(std::move(group));
    // } else {
    //     rootNode->add(std::move(group));
    // }

    // // Clear selection
    // for (auto node : selectedNodes) { node->setSelected(false); }
    // selectedNodes.clear();

    updateTreeView();
}
