#include "DiaScene.hpp"
#include <hstd/stdlib/VariantFormatter.hpp>

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

void DiaScene::updateLayoutForAdapter(const DiaAdapter& a) {
    layout = DiaLayout::FromDiagram(a);
}

DiaSceneItem* DiaScene::setRootAdapter(const DiaAdapter& a) {
    TRACKED_FUNCTION("setRootAdapter");
    rootNode            = addAdapterRec(a);
    treeModel->rootNode = rootNode.get();
    return rootNode.get();
}

void DiaScene::applyPartialEditStep(
    DiaEdit const&         edit,
    DiaEditTransientState& state) {

    if (edit.hasSrc()) {
        hstd::Opt<DiaSceneItem*> item = getItemForId(edit.getSrc().id);
        HSLOG_TRACE(
            "SRC:{} {}",
            edit.getSrc().getSelfPathFromRoot(),
            item.has_value()
                ? hstd::descObjectPtr(item.value())
                : hstd::fmt("<no item for ID:{}>", edit.getSrc().id));
    }

    if (edit.hasDst()) {
        hstd::Opt<DiaSceneItem*> item = getItemForId(edit.getDst().id);
        HSLOG_TRACE(
            "DST:{} {}",
            edit.getDst().getSelfPathFromRoot(),
            item.has_value()
                ? hstd::descObjectPtr(item.value())
                : hstd::fmt("<no item for ID:{}>", edit.getDst().id));
    }

    auto getParent = [&](DiaAdapter const& adapter) {
        auto parentPath = adapter.getParentPathFromRoot();
        hstd::Opt<DiaSceneItem*> parentItem = getItemForPath(parentPath);

        LOGIC_ASSERTION_CHECK_FMT(
            parentItem.has_value(),
            "No node found at path {}, cannot execute insert "
            "operation",
            parentPath);

        return std::pair{parentPath, parentItem.value()};
    };

    auto getIndex = [&](int index, hstd::Vec<int> const& path) -> int {
        return state.updateIdx(index, path);
    };

    switch (edit.getKind()) {
        case DiaEdit::Kind::Delete: {
            auto [parentPath, parentItem] = getParent(edit.getSrc());

            auto const& del = edit.getDelete();
            int         src = getIndex(del.srcIndex, parentPath);

            LOGIC_ASSERTION_CHECK_FMT(
                parentItem->at(src)->getDiaId() == del.srcNode.getDiaId(),
                "Delete of item at index {} should have removed the "
                "scene item with ID {}, but the parent {} {} has item "
                "with ID {} at this index",
                src,
                del.srcNode.getDiaId(),
                parentPath,
                hstd::descObjectPtr(parentItem),
                parentItem->at(src)->getDiaId());

            treeModel->beginEditApply(edit, state);
            parentItem->removeSubnode(src);
            treeModel->endEditApply(edit, state);

            state.applied[parentPath].push_back(edit);

            break;
        }


        case DiaEdit::Kind::Insert: {
            auto [parentPath, parentItem] = getParent(edit.getDst());
            int index                     = edit.getInsert().dstIndex;

            auto newNode = addAdapterRec(edit.getDst());

            treeModel->beginEditApply(edit, state);
            parentItem->insertSubnode(std::move(newNode), index);
            treeModel->endEditApply(edit, state);

            state.applied[parentPath].push_back(edit);
            break;
        }


        case DiaEdit::Kind::Move: {
            auto srcParent = edit.getDst().getParentPathFromRoot();
            auto dstParent = edit.getDst().getParentPathFromRoot();
            auto [parentPath, parentItem] = getParent(edit.getSrc());
            auto const& m                 = edit.getMove();
            int         dstIndex          = m.dstIndex;
            int         srcIndex = getIndex(m.srcIndex, parentPath);

            LOGIC_ASSERTION_CHECK_FMT(
                srcParent == dstParent,
                "Destination node and source node have different "
                "parent paths. SRC node parent is at path {}, while "
                "DST node parent is at path {}",
                srcParent,
                dstParent);

            if (parentItem->at(dstIndex)->getDiaId()
                == m.dstNode.getDiaId()) {
                HSLOG_INFO(
                    "Move operation is a no-op. Parent {} already "
                    "has item with ID {} placed at index {}",
                    parentItem->getDiaId(),
                    m.dstNode.getDiaId(),
                    dstIndex);
            } else {
                HSLOG_INFO(
                    "Move operation is required. Parent {} has "
                    "item with ID {} at index {}, but the move "
                    "operation requires item with ID {}",
                    parentItem->getDiaId(),
                    parentItem->at(dstIndex)->getDiaId(),
                    dstIndex,
                    m.dstNode.getDiaId());
                treeModel->beginEditApply(edit, state);
                parentItem->moveSubnode(srcIndex, dstIndex);
                treeModel->endEditApply(edit, state);
            }
            state.applied[parentPath].push_back(edit);
            break;
        }

        case DiaEdit::Kind::Update: {
            treeModel->beginEditApply(edit, state);
            if (edit.getSrc().hasParent()) {
                TRACKED_SCOPE("update node with parent");
                auto [parentPath, parentItem] = getParent(edit.getSrc());
                auto const& upd               = edit.getUpdate();
                int         srcIndex = getIndex(upd.srcIndex, parentPath);
                LOGIC_ASSERTION_CHECK_FMT(
                    srcIndex == upd.dstIndex,
                    "Update position mismatch. Source index for the edit "
                    "operation was:{}, adjusted for preceding edits:{}, "
                    "operation destination index is:{}",
                    upd.srcIndex,
                    srcIndex,
                    upd.dstIndex);

                DiaSceneItem* item = parentItem->at(srcIndex);

                auto oldSubnodes = item->moveSubnodes();
                auto newNode     = addAdapterNonRec(edit.getDst());
                newNode->setSubnodes(std::move(oldSubnodes));
                DiaSceneItem::UPtr* target = getMutableUPtrAtPath(
                    parentPath + hstd::Vec<int>{srcIndex});
                auto parent = target->get()->getParent();

                parent->setSubnode(std::move(newNode), srcIndex);

            } else {
                TRACKED_SCOPE("update node without parent");
                hstd::Opt<DiaSceneItem*> item = getItemForId(
                    edit.getSrc().id);
                HSLOG_INFO(
                    "target item\n{}",
                    item.value()->treeRepr().toString(false));
                auto oldSubnodes = item.value()->moveSubnodes();
                auto newNode     = addAdapterNonRec(edit.getDst());
                newNode->setSubnodes(std::move(oldSubnodes));
                DiaSceneItem::UPtr* target = getMutableUPtrAtPath({});
                *target                    = std::move(newNode);
            }

            HSLOG_INFO("{}", rootNode->treeRepr().toString(false));


            treeModel->endEditApply(edit, state);
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
    DiaSceneItem*         originalRoot = root();
    DiaEditTransientState state;
    HSLOG_INFO("{}", rootNode->treeRepr().toString(false));
    for (auto const& edit : hstd::enumerator(edits)) {
        TRACKED_SCOPE(
            hstd::fmt("Applying edit {}", edit.value().getKind()));
        HSLOG_TRACE("[{}] EDIT:{}", edit.index(), edit.value());
        applyPartialEditStep(edit.value(), state);
        HSLOG_INFO("{}", rootNode->treeRepr().toString(false));
    }

    LOGIC_ASSERTION_CHECK_FMT(
        originalRoot != rootNode.get(),
        "Non-empty set of edits is guaranteed to change the root node to "
        "a new structure, but the root update has not happened.");

    treeModel->rootNode = rootNode.get();

    return rootNode.get();
}

void DiaScene::diaRootChanged(
    DiaVersionStore::DiaRootChange const& change) {
    TRACKED_SLOT("diaRootChange");
    updateLayoutForAdapter(change.newRoot);
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
            auto pos = layout.getRelPos(a.uniq());
            node->setPos(pos.x(), pos.y());
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

        case DiaNodeKind::Edge: {
            throw hstd::logic_unreachable_error::init(
                "Edges should not be created directly from the scene "
                "adapter");
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
