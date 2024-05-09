#include <editor/editor_lib/org_graph_scene.hpp>

struct EdgePolylineItem : public QGraphicsItem {
    explicit EdgePolylineItem(
        const QPainterPath& points,
        QGraphicsItem*      parent = nullptr)
        : QGraphicsItem(parent), points(points) {}

    QRectF boundingRect() const override { return points.boundingRect(); }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        painter->setPen(QPen(Qt::red, 2));
        painter->drawPath(points);
    }

    QPainterPath points;
};

void OrgGraphView::addOrUpdateItem(const QModelIndex& index) {
    bool isNode = model->data(index, OrgGraphModelRoles::IsNodeRole)
                      .toBool();
    QGraphicsItem* item = nullptr;

    if (indexItemMap.contains(index)) {
        item = indexItemMap.value(index).data();
    }

    if (isNode) {
        QRect nodeRect = qvariant_cast<QRect>(
            model->data(index, OrgGraphModelRoles::NodeShapeRole));
        qDebug() << "Add node rect" << nodeRect << "for index" << index;
        if (item) {
            dynamic_cast<QGraphicsRectItem*>(item)->setRect(nodeRect);
        } else {
            item = scene->addRect(nodeRect);
            indexItemMap.insert(
                index, QSharedPointer<QGraphicsItem>(item));
        }
    } else {
        QPainterPath edgeShape = qvariant_cast<QPainterPath>(
            model->data(index, OrgGraphModelRoles::EdgeShapeRole));
        if (item) {
            dynamic_cast<EdgePolylineItem*>(item)->points = edgeShape;
        } else {
            EdgePolylineItem* polyline = new EdgePolylineItem(edgeShape);
            scene->addItem(polyline);
            indexItemMap.insert(
                index, QSharedPointer<QGraphicsItem>(polyline));
        }
    }
}
