#pragma once

#include <QGraphicsScene>
#include "DiagramNodeVisual.hpp"
#include "DiagramTreeModel.hpp"
#include "DiagramNodeRectangle.hpp"
#include "DiagramNodeEdge.hpp"
#include "DiagramNodeImage.hpp"
#include "DiagramNodeGroup.hpp"
#include <QMessageBox>

struct DiagramScene : public QGraphicsScene {
    Q_OBJECT

  public:
    int                             gridSnap{10};
    DiagramNode*                    rootNode{};
    DiagramNodeVisual*              selectedNode{nullptr};
    DiagramNodeVisual*              arrowSource{nullptr};
    DiagramTreeModel*               treeModel{nullptr};
    std::vector<DiagramNodeVisual*> selectedNodes{};
    bool                            showGrid{true};
    QColor                          gridColor{Qt::lightGray};

    DiagramScene(QObject* parent = nullptr) : QGraphicsScene{parent} {
        rootNode = new DiagramNodeCanvas{"Canvas"};
        setupExampleDiagram();
    }

    void drawBackground(QPainter* painter, const QRectF& rect) override {
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


    void setupExampleDiagram() {
        auto layer1 = new DiagramNodeLayer{"Layer 1"};

        auto node1 = new DiagramNodeRectangle{"Node 1"};
        node1->setPos(100, 100);
        node1->color = Qt::cyan;
        addItem(node1);

        auto node2 = new DiagramNodeRectangle{"Node 2"};
        node2->setPos(250, 150);
        node2->color = Qt::yellow;
        addItem(node2);

        layer1->addChild(node1);
        layer1->addChild(node2);
        rootNode->addChild(layer1);

        addEdge(node1, node2);

        updateTreeView();
    }


    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsItem*     item = itemAt(event->scenePos(), QTransform{});
        DiagramNodeVisual* clickedNode = dynamic_cast<DiagramNodeVisual*>(
            item);

        if (event->modifiers() & Qt::ControlModifier) {
            // Multi-selection mode
            if (clickedNode
                && std::find(
                       selectedNodes.begin(),
                       selectedNodes.end(),
                       clickedNode)
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
            emit nodeSelected(selectedNode);
        }

        if (event->button() == Qt::RightButton && selectedNode) {
            auto visualNode = dynamic_cast<DiagramNodeVisual*>(
                selectedNode);
            if (visualNode
                && !dynamic_cast<DiagramNodeEdge*>(visualNode)) {
                if (arrowSource == nullptr) {
                    arrowSource = visualNode;
                } else {
                    if (arrowSource != visualNode) {
                        auto edge = new DiagramNodeEdge(
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

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (selectedNode && (event->buttons() & Qt::LeftButton)) {
            DiagramNodeImage* imageNode = dynamic_cast<DiagramNodeImage*>(
                selectedNode);
            if (!imageNode || !imageNode->isResizing) {
                QPointF newPos = event->scenePos()
                               - selectedNode->dragOffset;
                selectedNode->setPosition(newPos, gridSnap);
                return;
            }
        }
        QGraphicsScene::mouseMoveEvent(event);
    }
    void setTreeModel(DiagramTreeModel* model) {
        treeModel = model;
        updateTreeView();
    }

    void updateTreeView() {
        if (treeModel) { treeModel->refresh(); }
    }

    DiagramNodeLayer* findFirstLayer() {
        for (const auto& child : rootNode->children) {
            if (auto it = dynamic_cast<DiagramNodeLayer*>(child);
                it != nullptr) {
                return it;
            }
        }
        return nullptr;
    }

  public slots:
    void setShowGrid(bool show) {
        showGrid = show;
        invalidate(); // Force redraw
    }

    void setGridColor(const QColor& color) {
        gridColor = color;
        invalidate(); // Force redraw
    }

    void setGridSnap(int snap) { gridSnap = snap; }

    void addEdge(
        DiagramNodeVisual* sourceNode,
        DiagramNodeVisual* targetNode) {
        auto edge = new DiagramNodeEdge{sourceNode, targetNode};
        addItem(edge);

        auto layer = findFirstLayer();
        if (layer) {
            layer->addChild(edge);
        } else {
            rootNode->addChild(edge);
        }
    }

    void createEdgeFromSelection() {
        if (selectedNodes.size() != 2) {
            QMessageBox::warning(
                nullptr,
                "Error",
                "Please select exactly 2 nodes to create an edge.");
            return;
        }

        DiagramNodeVisual* sourceNode = selectedNodes.at(0);
        DiagramNodeVisual* targetNode = selectedNodes.at(1);

        if (dynamic_cast<DiagramNodeEdge*>(sourceNode)
            || dynamic_cast<DiagramNodeEdge*>(targetNode)) {
            QMessageBox::warning(
                nullptr,
                "Error",
                "Cannot create edge from or to another edge.");
            return;
        }

        addEdge(sourceNode, targetNode);

        // Clear selection
        for (auto node : selectedNodes) { node->setSelected(false); }
        selectedNodes.clear();
        updateTreeView();
    }


    void addRectangle() {
        auto node = new DiagramNodeRectangle{"Rectangle"};
        node->setPos(200, 200);
        node->color = Qt::green;
        addItem(node);

        auto layer = findFirstLayer();
        if (layer) {
            layer->addChild(node);
        } else {
            rootNode->addChild(node);
        }
        updateTreeView();
    }

    void addLayer() {
        auto layer = new DiagramNodeLayer{"New Layer"};
        rootNode->addChild(layer);
        updateTreeView();
    }

    void addImage() {
        QString fileName = QFileDialog::getOpenFileName(
            nullptr,
            "Open Image",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!fileName.isEmpty()) {
            auto node = new DiagramNodeImage{"Image"};
            node->setImage(
                QPixmap{fileName}.scaled(100, 100, Qt::KeepAspectRatio));
            node->setPos(150, 300);
            addItem(node);

            auto layer = findFirstLayer();
            if (layer) {
                layer->addChild(node);
            } else {
                rootNode->addChild(node);
            }
            updateTreeView();
        }
    }

    DiagramNodeGroup* findGroupContaining(DiagramNodeVisual* node) {
        for (auto item : items()) {
            if (auto group = dynamic_cast<DiagramNodeGroup*>(item)) {
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

    std::vector<DiagramNodeVisual*> findCommonParentNodes(
        const std::vector<DiagramNodeVisual*>& nodes) {
        std::vector<DiagramNodeVisual*> result;
        std::set<DiagramNodeVisual*>    processed;

        for (auto node : nodes) {
            if (dynamic_cast<DiagramNodeEdge*>(node)) {
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

  public slots:
    void createGroupFromSelection() {
        // Filter out edges and get only visual nodes
        std::vector<DiagramNodeVisual*> visualNodes;
        for (auto node : selectedNodes) {
            if (!dynamic_cast<DiagramNodeEdge*>(node)) {
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
            QMessageBox::warning(
                nullptr, "Error", "No valid nodes to group.");
            return;
        }

        // Remove nodes from their current groups if any
        for (auto node : nodesToGroup) {
            auto currentGroup = findGroupContaining(node);
            if (currentGroup) { currentGroup->removeFromGroup(node); }
        }

        // Create new group
        auto group = new DiagramNodeGroup{"Group"};
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


  signals:
    void nodeSelected(DiagramNodeVisual* node);
};
