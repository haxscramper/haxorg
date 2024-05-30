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

    QModelIndex index;
};

template <>
struct std::formatter<OrgGraphElementItem> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const OrgGraphElementItem& p, FormatContext& ctx) const {
        return fmt_ctx(p.index, ctx);
    }
};

template <>
struct std::formatter<OrgGraphElementItem*> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(OrgGraphElementItem const* p, FormatContext& ctx) const {
        if (p) {
            return fmt_ctx(p->index, ctx);
        } else {
            return fmt_ctx("<nil>", ctx);
        }
    }
};

class OrgGraphView : public QGraphicsView {
  private:
    Q_OBJECT

  public:
    OrgGraphView(
        org::mind_map::GraphLayoutProxy* model,
        OrgStore*                        store,
        QWidget*                         parent);

    QSize getNodeSize(const QModelIndex& index);
    void  setModel(QAbstractItemModel* model);
    void  rebuildScene();
    bool  debug = false;

    void validateItemRows();

    Vec<OrgGraphElementItem*> graphItems() {
        Vec<OrgGraphElementItem*> result;
        for (auto it : items()) {
            if (auto p = dynamic_cast<OrgGraphElementItem*>(it)) {
                result.push_back(p);
            }
        }
        return result;
    }

    /// \brief Get graph element with a specified index. For testing
    /// purposes.
    Opt<OrgGraphElementItem*> graphItemForIndex(CR<QModelIndex> index) {
        for (auto const& it : graphItems()) {
            if (mapToNestedSource(it->index) == mapToNestedSource(index)) {
                return it;
            }
        }
        return std::nullopt;
    }

    void connectModel() {
        Q_ASSERT(connect(
            model,
            &QAbstractItemModel::layoutChanged,
            this,
            &OrgGraphView::onLayoutChanged,
            Qt::UniqueConnection));
    }

  private:
    OrgStore*                      store;
    QAbstractItemModel*            model;
    QGraphicsScene*                scene;
    SPtr<QGraphicsItem>            background;
    Vec<SPtr<OrgGraphElementItem>> modelItems;


    void updateItem(const QModelIndex& index);

    void addItem(QModelIndex const& index);
    void onRowsShifted(int lastShifted);

    void removeSceneItem(int row);

    void onLayoutChanged(
        const QList<QPersistentModelIndex>&  parents,
        QAbstractItemModel::LayoutChangeHint hint) {
        rebuildScene();
        validateItemRows();
    }
};
