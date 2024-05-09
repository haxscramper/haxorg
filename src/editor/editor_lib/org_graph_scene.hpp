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
    OrgGraphView(QAbstractItemModel* model, QWidget* parent)
        : QGraphicsView(parent), model(model) {
        scene = new QGraphicsScene(this);
        this->setScene(scene);
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
        populateScene();
    }

  private:
    QAbstractItemModel*                               model;
    QGraphicsScene*                                   scene;
    QHash<QModelIndex, QSharedPointer<QGraphicsItem>> indexItemMap;

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
                QGraphicsItem* item = indexItemMap.take(index).data();
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
