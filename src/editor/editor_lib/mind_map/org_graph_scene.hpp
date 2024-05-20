#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAbstractItemModel>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QModelIndex>
#include <QSharedPointer>
#include <QHash>

#include <editor/editor_lib/mind_map/org_graph_model.hpp>

struct OrgGraphElementItem : public QGraphicsItem {
  public:
    explicit OrgGraphElementItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : QGraphicsItem(parent), store(store), index(index) {}

    OrgStore* store;

    void setIndex(QModelIndex index) {
        Q_ASSERT(index.isValid());
        this->index = index;
    }

    QModelIndex const& getIndex() const { return this->index; }

  protected:
    QModelIndex index;
};

class OrgGraphView : public QGraphicsView {
  private:
    Q_OBJECT

  public:
    OrgGraphView(
        QAbstractItemModel* model,
        OrgStore*           store,
        QWidget*            parent);

    QSize getNodeSize(const QModelIndex& index);
    void  setModel(QAbstractItemModel* model);
    void  rebuildScene();
    bool  debug = false;

    Vec<OrgGraphElementItem*> graphItems() {
        Vec<OrgGraphElementItem*> result;
        for (auto it : items()) {
            if (auto p = dynamic_cast<OrgGraphElementItem*>(it)) {
                result.push_back(p);
            }
        }
        return result;
    }

    void connectModel() {
        connect(
            model,
            &QAbstractItemModel::rowsInserted,
            this,
            &OrgGraphView::onRowsInserted);
        connect(
            model,
            &QAbstractItemModel::rowsRemoved,
            this,
            &OrgGraphView::onRowsRemoved);
        connect(
            model,
            &QAbstractItemModel::dataChanged,
            this,
            &OrgGraphView::onDataChanged);
        connect(
            model,
            &QAbstractItemModel::layoutChanged,
            this,
            &OrgGraphView::onLayoutChanged);
    }

  private:
    OrgStore*                store;
    QAbstractItemModel*      model;
    QGraphicsScene*          scene;
    SPtr<QGraphicsItem>      background;
    Vec<SPtr<QGraphicsItem>> modelItems;


    void updateItem(const QModelIndex& index);

    void addItem(QModelIndex const& index);

    void onRowsInserted(const QModelIndex& parent, int first, int last) {
        for (int row = first; row <= last; ++row) {
            addItem(model->index(row, 0, parent));
        }
    }

    void onRowsShifted(int lastShifted);

    void validateItemRows();

    void removeSceneItem(int row);

    void onRowsRemoved(const QModelIndex& parent, int first, int last);

    void onLayoutChanged(
        const QList<QPersistentModelIndex>&  parents,
        QAbstractItemModel::LayoutChangeHint hint) {
        validateItemRows();
    }

    void onDataChanged(
        const QModelIndex&  topLeft,
        const QModelIndex&  bottomRight,
        const QVector<int>& roles) {
        for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
            QModelIndex index = model->index(row, 0);
            updateItem(index);
        }
    }
};
