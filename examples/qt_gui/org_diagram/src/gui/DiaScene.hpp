#pragma once

#include <src/model/nodes/DiagramTreeNode.hpp>
#include <QGraphicsScene>
#include <src/gui/items/DiaSceneItemVisual.hpp>
#include <src/gui/DiaSceneItemModel.hpp>
#include <src/gui/items/DiaSceneItemRectangle.hpp>
#include <src/gui/items/DiaSceneItemEdge.hpp>
#include <src/gui/items/DiaSceneItemImage.hpp>
#include <src/gui/items/DiaSceneItemGroup.hpp>
#include <QMessageBox>

struct DiaScene : public QGraphicsScene {
    Q_OBJECT

  public:
    int                              gridSnap{10};
    DiaSceneItem::UPtr               rootNode{};
    DiaSceneItemVisual*              selectedNode{};
    DiaSceneItemVisual*              arrowSource{};
    DiaSceneItemModel*               treeModel{nullptr};
    std::vector<DiaSceneItemVisual*> selectedNodes{};
    bool                             showGrid{true};
    QColor                           gridColor{Qt::lightGray};

    hstd::UnorderedMap<DiaUniqId, DiaSceneItem*> diaItemMap;

    template <typename T, typename... Args>
    std::unique_ptr<T, SelfRemDiaScene> addNewItem(Args&&... args) {
        std::unique_ptr<T, SelfRemDiaScene>
            result = std::unique_ptr<T, SelfRemDiaScene>(
                new T{std::forward<Args>(args)...});
        addItem(result.get());

        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Create scene item {}", hstd::descObjectPtr(result)));
        return result;
    }

    void logSceneRoot();

    DiaScene(DiaSceneItemModel* treeModel, QObject* parent = nullptr)
        : QGraphicsScene{parent}, treeModel{treeModel} {}

    void drawBackground(QPainter* painter, const QRectF& rect) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (!selectedNode && (event->buttons() & Qt::LeftButton)) {
            auto img = dynamic_cast<DiaSceneItemImage*>(selectedNode);
            if (!img || !img->isResizing) {
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
        for (const auto& child : rootNode->getSubnodes()) {
            if (auto it = dynamic_cast<DiaSceneItemLayer*>(child.get());
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

    DiaSceneItem* getItemForId(DiaUniqId const& id) {
        return rootNode->getItemAtPath(id.getSelfPathFromRoot());
    }

    DiaSceneItem* setRootAdapter(DiaAdapter const& a);

    /// \brief Swap the existing scene item structure with the new one
    /// based on the provided edits.
    DiaSceneItem* resetRootAdapter(
        DiaAdapter const&           a,
        std::vector<DiaEdit> const& edits);

    /// \brief Create a new scene item based on the adapter data and add it
    /// to the scene.
    DiaSceneItem::UPtr addAdapterNonRec(DiaAdapter const& a);

    /// \brief Create a new scene item, recursively, with all the nested
    /// items.
    DiaSceneItem::UPtr addAdapterRec(DiaAdapter const& a) {
        hstd::Func<DiaSceneItem::UPtr(DiaAdapter const&)> aux;
        aux = [&](DiaAdapter const& it) -> DiaSceneItem::UPtr {
            auto root = addAdapterNonRec(it);
            for (auto const& sub : it.sub(true)) { root->add(aux(sub)); }
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
        auto edge = addNewItem<DiaSceneItemEdge>(sourceNode, targetNode);

        auto layer = findFirstLayer();
        if (layer) {
            layer->add(std::move(edge));
        } else {
            rootNode->add(std::move(edge));
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

        if (sourceNode->isinstance<DiaSceneItemEdge>()
            || targetNode->isinstance<DiaSceneItemEdge>()) {
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
        auto layer = addNewItem<DiaSceneItemLayer>("New Layer");
        rootNode->add(std::move(layer));
        updateTreeView();
    }

    void addImage() {
        QString fileName = QFileDialog::getOpenFileName(
            nullptr,
            "Open Image",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!fileName.isEmpty()) {
            auto node = addNewItem<DiaSceneItemImage>("Image");
            node->setImage(
                QPixmap{fileName}.scaled(100, 100, Qt::KeepAspectRatio));
            node->setPos(150, 300);

            auto layer = findFirstLayer();
            if (layer) {
                layer->add(std::move(node));
            } else {
                rootNode->add(std::move(node));
            }
            updateTreeView();
        }
    }

    DiaSceneItemGroup* findGroupContaining(DiaSceneItemVisual* node);

    std::vector<DiaSceneItemVisual*> findCommonParentNodes(
        const std::vector<DiaSceneItemVisual*>& nodes);

  public slots:
    void createGroupFromSelection();


  signals:
    void nodeSelected(DiaSceneItemVisual* node);
};
