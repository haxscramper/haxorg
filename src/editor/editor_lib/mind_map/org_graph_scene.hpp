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
            updateItem(model->index(row, 0, parent));
        }
    }

    void onRowsShifted(int lastShifted);

    void validateItemRows();

    void resetSceneItem(int row) {
        QGraphicsItem* item = modelItems.at(row).get();
        Q_ASSERT(item != nullptr);
        Q_ASSERT(item->scene() == scene);
        scene->removeItem(item);
        modelItems.at(row).reset((QGraphicsItem*)nullptr);
    }

    void onRowsRemoved(const QModelIndex& parent, int first, int last);

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
