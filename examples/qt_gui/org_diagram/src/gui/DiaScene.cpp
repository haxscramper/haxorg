#include "DiaScene.hpp"

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

DiaSceneItem* DiaScene::addAdapterNonRec(const DiaAdapter& a) {
    switch (a.getKind()) {
        case DiaNodeKind::Group:
        case DiaNodeKind::Item: {
            auto it   = a.as<DiaNodeItem>();
            auto node = new DiaSceneItemRectangle{
                QString::fromStdString(it->getSubtree().getCleanTitle())};
            auto pos = it->getPos();
            node->setPos(pos.x, pos.y);
            node->color = Qt::green;
            addItem(node);
            return node;
        }
        case DiaNodeKind::Canvas: {
            auto canvas = new DiaSceneItemCanvas{};
            return canvas;
        }
        case DiaNodeKind::Layer: {
            auto layer = new DiaSceneItemLayer{};
            return layer;
        }
    }
}
