#include <editor/editor_lib/org_graph_scene.hpp>
#include <editor/editor_lib/org_document_render.hpp>


struct OrgBackgroundGridItem : public QGraphicsItem {
  public:
    explicit OrgBackgroundGridItem(int n, const QRectF& bbox)
        : n(n), bbox(bbox.marginsAdded(QMargins(20, 20, 20, 20))) {}

    QRectF boundingRect() const override { return bbox; }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        Q_UNUSED(option)
        Q_UNUSED(widget)

        painter->setBrush(QColor{245, 245, 220, 150});
        painter->setPen(QPen{Qt::black, 2});
        painter->drawRect(bbox);

        QPen gridPen{QColor{169, 169, 169, 150}, 1, Qt::DashLine};
        painter->setPen(gridPen);

        for (int row = 1; row < bbox.width() / n; ++row) {
            painter->drawLine(
                bbox.left() + row * n,
                bbox.top(),
                bbox.left() + row * n,
                bbox.bottom());
        }

        for (int col = 1; col < bbox.height() / n; ++col) {
            painter->drawLine(
                bbox.left(),
                bbox.top() + col * n,
                bbox.right(),
                bbox.top() + col * n);
        }
    }

    int    n;
    QRectF bbox;
};

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
        painter->save();
        {
            painter->setPen(QPen{Qt::black, 2});
            painter->setBrush(QBrush{QColor{215, 214, 213}});
            painter->drawRoundedRect(rect, 5, 5);
        }
        painter->restore();

        painter->save();
        {
            QTextDocument doc;
            QString     text = qindex_get<QString>(index, Qt::DisplayRole);
            QTextOption opt{};
            opt.setWrapMode(QTextOption::WrapAnywhere);
            doc.setDefaultTextOption(opt);
            doc.setHtml(text);
            doc.setTextWidth(rect.width());
            painter->translate(rect.topLeft());
            doc.drawContents(painter);
        }
        painter->restore();
    }


    QModelIndex index;
    OrgStore*   store;
};

OrgGraphView::OrgGraphView(
    QAbstractItemModel* model,
    OrgStore*           store,
    QWidget*            parent,
    QRect               graphBBox)
    : QGraphicsView(parent)
    , store(store)
    , model(model)
//
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    background = std::make_shared<OrgBackgroundGridItem>(20, graphBBox);
    scene->addItem(background.get());

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
