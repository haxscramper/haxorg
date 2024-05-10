#include <editor/editor_lib/org_graph_scene.hpp>
#include <editor/editor_lib/org_document_render.hpp>

struct OrgEdgeItem : public QGraphicsItem {
    explicit OrgEdgeItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : QGraphicsItem(parent), store(store), index(index) {}

    QPainterPath getPoints() const {
        return qvariant_cast<QPainterPath>(
            index.data(OrgGraphModelRoles::EdgeShapeRole));
    }

    QRectF boundingRect() const override {
        return getPoints().boundingRect();
    }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        painter->setPen(QPen(Qt::red, 2));
        painter->drawPath(getPoints());
    }

    QModelIndex index;
    OrgStore*   store;
};

struct OrgNodeItem : public QGraphicsItem {
    explicit OrgNodeItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : QGraphicsItem(parent), store(store), index(index) {}

    OrgBoxId getBox() const {
        return qvariant_cast<OrgBoxId>(
            index.data(SharedModelRoles::IndexBoxRole));
    }

    QRect getRect() const {
        return qvariant_cast<QRect>(
            index.data(OrgGraphModelRoles::NodeShapeRole));
    }

    QRectF boundingRect() const override { return getRect().toRectF(); }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        auto rect = getRect();
        painter->drawRect(rect);

        QTextDocument doc;
        QString       text = qindex_get<QString>(index, Qt::DisplayRole);
        QTextOption   opt{};
        opt.setWrapMode(QTextOption::WrapAnywhere);
        doc.setDefaultTextOption(opt);
        doc.setHtml(text);
        doc.setTextWidth(rect.width());
        painter->save();
        painter->translate(rect.topLeft());
        doc.drawContents(painter);
        painter->restore();
    }


    QModelIndex index;
    OrgStore*   store;
};

void OrgGraphView::addOrUpdateItem(const QModelIndex& index) {
    bool isNode = model->data(index, OrgGraphModelRoles::IsNodeRole)
                      .toBool();
    QGraphicsItem* item = nullptr;

    if (indexItemMap.contains(index)) {
        item = indexItemMap.value(index).get();
    }

    if (isNode) {
        if (item) {
            item->update();
        } else {
            OrgNodeItem* polyline = new OrgNodeItem(store, index, nullptr);
            scene->addItem(polyline);
            indexItemMap.insert(index, SPtr<QGraphicsItem>(polyline));
        }
    } else {
        if (item) {
            item->update();
        } else {
            OrgEdgeItem* polyline = new OrgEdgeItem(store, index, nullptr);
            scene->addItem(polyline);
            indexItemMap.insert(index, SPtr<QGraphicsItem>(polyline));
        }
    }
}
