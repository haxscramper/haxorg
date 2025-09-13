#pragma once

#include <src/model/nodes/DiagramTreeNode.hpp>
#include <QGraphicsScene>
#include <src/gui/items/DiaSceneItemVisual.hpp>
#include <src/gui/DiaSceneItemsModel.hpp>
#include <src/gui/items/DiaSceneItemRectangle.hpp>
#include <src/gui/items/DiaSceneItemEdge.hpp>
#include <src/gui/items/DiaSceneItemImage.hpp>
#include <src/gui/items/DiaSceneItemGroup.hpp>
#include <QMessageBox>

struct DiaScene : public QGraphicsScene {
    Q_OBJECT

  public:
    int                              gridSnap{10};
    DiaSceneItem*                    rootNode{};
    DiaSceneItemVisual*              selectedNode{nullptr};
    DiaSceneItemVisual*              arrowSource{nullptr};
    DiaSceneItemsModel*              treeModel{nullptr};
    std::vector<DiaSceneItemVisual*> selectedNodes{};
    bool                             showGrid{true};
    QColor                           gridColor{Qt::lightGray};

    hstd::UnorderedMap<DiaUniqId, DiaSceneItem*> diaItemMap;

    DiaScene(DiaSceneItemsModel* treeModel, QObject* parent = nullptr)
        : QGraphicsScene{parent}, treeModel{treeModel} {}

    void drawBackground(QPainter* painter, const QRectF& rect) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (selectedNode && (event->buttons() & Qt::LeftButton)) {
            DiaSceneItemImage* imageNode = dynamic_cast<
                DiaSceneItemImage*>(selectedNode);
            if (!imageNode || !imageNode->isResizing) {
                QPointF newPos = event->scenePos()
                               - selectedNode->dragOffset;
                selectedNode->setPosition(newPos, gridSnap);
                return;
            }
        }
        QGraphicsScene::mouseMoveEvent(event);
    }

    void updateTreeView() {
        if (treeModel) { treeModel->refresh(); }
    }

    DiaSceneItemLayer* findFirstLayer() {
        for (const auto& child : rootNode->children) {
            if (auto it = dynamic_cast<DiaSceneItemLayer*>(child);
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

    DiaSceneItem* setRootAdapter(DiaAdapter const& a) {
        rootNode            = addAdapterRec(a);
        treeModel->rootNode = rootNode;
        return rootNode;
    }

    DiaSceneItem* addAdapterNonRec(DiaAdapter const& a);
    DiaSceneItem* addAdapterRec(DiaAdapter const& a) {
        hstd::Func<DiaSceneItem*(DiaAdapter const&)> aux;
        aux = [&](DiaAdapter const& it) -> DiaSceneItem* {
            auto root = addAdapterNonRec(it);
            for (auto const& sub : it.sub(true)) {
                root->addChild(aux(sub));
            }
            return root;
        };

        auto res = aux(a);
        updateTreeView();
        return res;
    }

    void removeAdapterNonRec(DiaAdapter const& a) {}
    void removeAdapterRec(DiaAdapter const& a) {}

    void addEdge(
        DiaSceneItemVisual* sourceNode,
        DiaSceneItemVisual* targetNode) {
        auto edge = new DiaSceneItemEdge{sourceNode, targetNode};
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

        DiaSceneItemVisual* sourceNode = selectedNodes.at(0);
        DiaSceneItemVisual* targetNode = selectedNodes.at(1);

        if (dynamic_cast<DiaSceneItemEdge*>(sourceNode)
            || dynamic_cast<DiaSceneItemEdge*>(targetNode)) {
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

    void addLayer() {
        auto layer = new DiaSceneItemLayer{"New Layer"};
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
            auto node = new DiaSceneItemImage{"Image"};
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

    DiaSceneItemGroup* findGroupContaining(DiaSceneItemVisual* node) {
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

    std::vector<DiaSceneItemVisual*> findCommonParentNodes(
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

  public slots:
    void createGroupFromSelection() {
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


  signals:
    void nodeSelected(DiaSceneItemVisual* node);
};
