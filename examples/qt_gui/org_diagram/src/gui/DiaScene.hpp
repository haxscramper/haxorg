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
    int                                   gridSnap{10};
    DiaSceneItem::Ptr                     rootNode{};
    hstd::WPtr<DiaSceneItemVisual>        selectedNode{};
    hstd::WPtr<DiaSceneItemVisual>        arrowSource{};
    DiaSceneItemModel*                    treeModel{nullptr};
    std::vector<DiaSceneItemVisual::WPtr> selectedNodes{};
    bool                                  showGrid{true};
    QColor                                gridColor{Qt::lightGray};

    hstd::UnorderedMap<DiaUniqId, DiaSceneItem*> diaItemMap;

    template <typename T, typename... Args>
    std::shared_ptr<T> addNewItem(Args&&... args) {
        std::shared_ptr<T> result = std::shared_ptr<T>(
            new T{std::forward<Args>(args)...}, [this](T* deleter) {
                this->removeItem(deleter);
                HSLOG_TRACE(
                    _cat,
                    hstd::fmt(
                        "Deleting scene item {}",
                        hstd::descObjectPtr(deleter)));
                delete deleter;
            });
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
        if (!selectedNode.expired()
            && (event->buttons() & Qt::LeftButton)) {
            auto sel = hstd::safe_wptr_lock(selectedNode);
            hstd::SPtr<DiaSceneItemImage>
                imageNode = std::dynamic_pointer_cast<DiaSceneItemImage>(
                    sel);
            if (!imageNode || !imageNode->isResizing) {
                QPointF newPos = event->scenePos() - sel->dragOffset;
                sel->setPosition(newPos, gridSnap);
                return;
            }
        }
        QGraphicsScene::mouseMoveEvent(event);
    }

    void updateTreeView() {
        if (treeModel) { treeModel->refresh(); }
    }

    std::shared_ptr<DiaSceneItemLayer> findFirstLayer() {
        for (const auto& child : rootNode->subnodes) {
            if (auto it = std::dynamic_pointer_cast<DiaSceneItemLayer>(
                    child);
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

    DiaSceneItem::Ptr getItemForId(DiaUniqId const& id) {
        return rootNode->getItemAtPath(id.getSelfPathFromRoot());
    }

    DiaSceneItem::Ptr setRootAdapter(DiaAdapter const& a);

    /// \brief Swap the existing scene item structure with the new one
    /// based on the provided edits.
    DiaSceneItem::Ptr resetRootAdapter(
        DiaAdapter const&           a,
        std::vector<DiaEdit> const& edits);

    /// \brief Create a new scene item based on the adapter data and add it
    /// to the scene.
    DiaSceneItem::Ptr addAdapterNonRec(DiaAdapter const& a);

    /// \brief Create a new scene item, recursively, with all the nested
    /// items.
    DiaSceneItem::Ptr addAdapterRec(DiaAdapter const& a) {
        hstd::Func<DiaSceneItem::Ptr(DiaAdapter const&)> aux;
        aux = [&](DiaAdapter const& it) -> DiaSceneItem::Ptr {
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
        DiaSceneItemVisual::WPtr sourceNode,
        DiaSceneItemVisual::WPtr targetNode) {
        auto edge = addNewItem<DiaSceneItemEdge>(sourceNode, targetNode);

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

        DiaSceneItemVisual::WPtr sourceNode = selectedNodes.at(0);
        DiaSceneItemVisual::WPtr targetNode = selectedNodes.at(1);

        if (sourceNode.lock()->isinstance<DiaSceneItemEdge>()
            || targetNode.lock()->isinstance<DiaSceneItemEdge>()) {
            QMessageBox::warning(
                nullptr,
                "Error",
                "Cannot create edge from or to another edge.");
            return;
        }

        addEdge(sourceNode, targetNode);

        // Clear selection
        for (auto node : selectedNodes) {
            node.lock()->setSelected(false);
        }
        selectedNodes.clear();
        updateTreeView();
    }

    void addLayer() {
        auto layer = addNewItem<DiaSceneItemLayer>("New Layer");
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
            auto node = addNewItem<DiaSceneItemImage>("Image");
            node->setImage(
                QPixmap{fileName}.scaled(100, 100, Qt::KeepAspectRatio));
            node->setPos(150, 300);

            auto layer = findFirstLayer();
            if (layer) {
                layer->addChild(node);
            } else {
                rootNode->addChild(node);
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
