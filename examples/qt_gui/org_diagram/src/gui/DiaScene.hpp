#pragma once

#include "src/model/DiaVersionStore.hpp"
#include <src/model/nodes/DiagramTreeNode.hpp>
#include <QGraphicsScene>
#include <src/gui/items/DiaSceneItemVisual.hpp>
#include <src/gui/DiaSceneItemModel.hpp>
#include <src/gui/items/DiaSceneItemRectangle.hpp>
#include <src/gui/items/DiaSceneItemEdge.hpp>
#include <src/gui/items/DiaSceneItemImage.hpp>
#include <src/gui/items/DiaSceneItemGroup.hpp>
#include <hstd/stdlib/Set.hpp>
#include <QMessageBox>

struct DiaScene : public QGraphicsScene {
    Q_OBJECT

  public:
    int                  gridSnap{10};
    DiaSceneItem::UPtr   rootNode{};
    DiaSceneItemVisual*  selectedNode{};
    DiaSceneItemVisual*  arrowSource{};
    DiaSceneItemModel*   treeModel{nullptr};
    DiaVersionStore::Ptr version_store;

    std::vector<DiaSceneItemVisual*> selectedNodes{};
    bool                             showGrid{true};
    QColor                           gridColor{Qt::lightGray};

    hstd::UnorderedMap<DiaUniqId, DiaSceneItem*> diaItemMap;

    template <typename T, typename... Args>
    std::unique_ptr<T, SelfRemDiaScene> addNewItem(
        DiaAdapter const& staleAdapter,
        Args&&... args) {
        std::unique_ptr<T, SelfRemDiaScene>
            result = std::unique_ptr<T, SelfRemDiaScene>(
                new T{staleAdapter, std::forward<Args>(args)...});
        addItem(result.get());

        HSLOG_TRACE(
            _cat,
            hstd::fmt(
                "Create scene item {}", hstd::descObjectPtr(result)));
        return result;
    }

    void logSceneRoot();

    DiaScene(
        DiaSceneItemModel*   treeModel,
        DiaVersionStore::Ptr version_store,
        QObject*             parent = nullptr)
        : QGraphicsScene{parent}
        , version_store{version_store}
        , treeModel{treeModel} {}

    void drawBackground(QPainter* painter, const QRectF& rect) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

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

    DiaSceneItem* root() {
        hstd::logic_assertion_check_not_nil(rootNode.get());
        return rootNode.get();
    }

    DiaSceneItem::UPtr* getMutableUPtrAtPath(hstd::Vec<int> const& path) {
        DiaSceneItem::UPtr* result = &rootNode;
        for (auto const& it : path) {
            result = (**result).getMutableUPtr(it);
        }
        return result;
    }

    hstd::Opt<DiaSceneItem*> getItemForPath(hstd::Vec<int> const& path) {
        return root()->getItemAtPath(path);
    }

    hstd::Opt<DiaSceneItem*> getItemForId(DiaUniqId const& id) {
        return root()->getItemAtPath(id.getSelfPathFromRoot());
    }

    DiaSceneItem* setRootAdapter(DiaAdapter const& a);

    /// \brief Swap the existing scene item structure with the new one
    /// based on the provided edits.
    DiaSceneItem* resetRootAdapter(hstd::Vec<DiaEdit> const& edits);

    struct TransientEditState {
        hstd::UnorderedMap<hstd::Vec<int>, std::vector<DiaEdit>> applied;
    };

    void applyPartialEditStep(
        DiaEdit const&      edit,
        TransientEditState& state);

    /// \brief Create a new scene item based on the adapter data and
    /// add it to the scene.
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
        DiaAdapter const&   adapter,
        DiaSceneItemVisual* sourceNode,
        DiaSceneItemVisual* targetNode) {
        auto edge = addNewItem<DiaSceneItemEdge>(
            adapter, sourceNode, targetNode);

        auto layer = findFirstLayer();
        if (layer) {
            layer->add(std::move(edge));
        } else {
            root()->add(std::move(edge));
        }
    }

    DiaSceneItemGroup* findGroupContaining(DiaSceneItemVisual* node);

    std::vector<DiaSceneItemVisual*> findCommonParentNodes(
        const std::vector<DiaSceneItemVisual*>& nodes);

  public slots:
    void setShowGrid(bool show) {
        showGrid = show;
        invalidate(); // Force redraw
    }

    void setGridColor(const QColor& color) {
        gridColor = color;
        invalidate(); // Force redraw
    }

    void deleteSelectedNode();

    void setGridSnap(int snap) { gridSnap = snap; }

    void diaRootChanged(DiaVersionStore::DiaRootChange const& change);

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

        logic_todo_impl();
        // addEdge(sourceNode, targetNode);

        // Clear selection
        for (auto node : selectedNodes) { node->setSelected(false); }
        selectedNodes.clear();
        updateTreeView();
    }

    void addLayer() {}
    void addImage() {}


  public slots:
    void createGroupFromSelection();


  signals:
    void nodeSelected(DiaSceneItemVisual* node);
};
