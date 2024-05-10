#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAbstractItemModel>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QModelIndex>
#include <QSharedPointer>
#include <QHash>

#include <editor/editor_lib/org_graph_model.hpp>

class OrgGraphView : public QGraphicsView {
  private:
    Q_OBJECT

  public:
    OrgGraphView(
        QAbstractItemModel* model,
        OrgStore*           store,
        QWidget*            parent,
        QRect               graphBBox);

  private:
    OrgStore*                               store;
    QAbstractItemModel*                     model;
    QGraphicsScene*                         scene;
    QHash<QModelIndex, SPtr<QGraphicsItem>> indexItemMap;
    SPtr<QGraphicsItem>                     background;
    QRect                                   graphBBox;

    void populateScene() {
        int rowCount = model->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            addOrUpdateItem(model->index(row, 0));
        }
    }

    void addOrUpdateItem(const QModelIndex& index);

    void onRowsInserted(const QModelIndex& parent, int first, int last) {
        for (int row = first; row <= last; ++row) {
            addOrUpdateItem(model->index(row, 0, parent));
        }
    }

    void onRowsRemoved(const QModelIndex& parent, int first, int last) {
        for (int row = first; row <= last; ++row) {
            QModelIndex index = model->index(row, 0, parent);
            if (indexItemMap.contains(index)) {
                QGraphicsItem* item = indexItemMap.take(index).get();
                scene->removeItem(item);
            }
        }
    }

    void onDataChanged(
        const QModelIndex&  topLeft,
        const QModelIndex&  bottomRight,
        const QVector<int>& roles) {
        for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
            QModelIndex index = model->index(row, 0);
            if (indexItemMap.contains(index)) { addOrUpdateItem(index); }
        }
    }
};
