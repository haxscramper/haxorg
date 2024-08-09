#include <editor/editor_lib/mind_map/org_graph_scene.hpp>
#include <editor/editor_lib/document/org_document_render.hpp>

using namespace org::mind_map;

namespace {
SPtr<QTextDocument> toDocument(QString const& text) {
    auto        doc = std::make_shared<QTextDocument>();
    QTextOption opt{};
    opt.setWrapMode(QTextOption::WrapAnywhere);
    doc->setDefaultTextOption(opt);
    doc->setHtml(text);
    doc->setTextWidth(200);
    return std::move(doc);
}
} // namespace

struct OrgBackgroundGridItem : public QGraphicsItem {
  public:
    explicit OrgBackgroundGridItem(int n, QAbstractItemModel* source)
        : n(n), source(source) {}

    QRectF boundingRect() const override {
        return qindex_get<QRect>(
                   source->index(0, 0),
                   GraphLayoutProxy::Role::LayoutBBoxRole)
            .marginsAdded(QMargins(20, 20, 20, 20));
        ;
    }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {

        auto bbox = boundingRect();

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

    int                 n;
    QAbstractItemModel* source;
};


struct OrgSubgraphItem : public OrgGraphElementItem {
    explicit OrgSubgraphItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : OrgGraphElementItem(store, index, parent) {
        updateStateFromIndex();
    }

    Opt<GraphLayoutProxy::Subgraph> path;

    void updateStateFromIndex() {
        path = qindex_get<GraphLayoutProxy::Subgraph>(
            index, GraphLayoutProxy::Role::Subgraph);
    }

    GraphLayoutProxy::Subgraph getSubgraph() const {
        if (path) {
            return path.value();
        } else {
            return GraphLayoutProxy::Subgraph{};
        }
    }

    QRectF boundingRect() const override {
        return getSubgraph().bbox.toRectF();
    }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        updateStateFromIndex();
        painter->setPen(QPen(Qt::red, 2));
        painter->drawRect(getSubgraph().bbox);
    }
};

struct OrgEdgeItem : public OrgGraphElementItem {
    explicit OrgEdgeItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : OrgGraphElementItem(store, index, parent) {
        updateStateFromIndex();
    }

    Opt<GraphLayoutIR::Edge> path;

    void updateStateFromIndex() {
        path = qindex_get<GraphLayoutIR::Edge>(
            index, OrgGraphRoles::EdgeShape);
    }

    GraphLayoutIR::Edge getEdge() const {
        if (path) {
            return path.value();
        } else {
            return GraphLayoutIR::Edge();
        }
    }

    QRectF boundingRect() const override {
        QRectF boundingRect;
        for (GraphPath const& path : getEdge().paths) {
            boundingRect = boundingRect.united(
                toQPainterPath(path).boundingRect());
        }
        return boundingRect;
    }


    QPolygonF getArrowHeadPolygon(
        const QPainterPath& path,
        qreal               arrowSize) {
        QPointF lastPoint = path.currentPosition();
        QPointF prevPoint = path.elementAt(path.elementCount() - 2);
        QLineF  line(prevPoint, lastPoint);

        qreal   angle   = std::atan2(-line.dy(), line.dx());
        QPointF arrowP1 = lastPoint
                        + QPointF(
                              -sin(angle + M_PI / 3) * arrowSize,
                              cos(angle + M_PI / 3) * arrowSize);

        QPointF arrowP2 = lastPoint
                        + QPointF(
                              -sin(angle + M_PI - M_PI / 3) * arrowSize,
                              cos(angle + M_PI - M_PI / 3) * arrowSize);

        QPolygonF arrowHead;
        arrowHead << arrowP1 << lastPoint << arrowP2;

        return arrowHead;
    }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        updateStateFromIndex();
        painter->setPen(QPen(Qt::red, 2));
        for (GraphPath const& path : getEdge().paths) {
            painter->drawPath(toQPainterPath(path));
        }

        painter->save();
        {
            painter->setBrush(QBrush{Qt::red});
            painter->drawPolygon(getArrowHeadPolygon(
                toQPainterPath(getEdge().paths.back()), 5.0));
        }
        painter->restore();

        if (auto rect = getEdge().labelRect) {
            painter->save();
            {
                painter->setPen(QPen{Qt::green, 2});
                painter->setBrush(QBrush{QColor{215, 214, 213}});
                painter->drawRoundedRect(toQRect(*rect), 5, 5);
            }
            painter->restore();

            painter->save();
            {
                QString text = qindex_get<QString>(index, Qt::DisplayRole);
                painter->translate(toQRect(*rect).topLeft());
                toDocument(text)->drawContents(painter);
            }
            painter->restore();
        }
    }
};

struct OrgNodeItem : public OrgGraphElementItem {
    explicit OrgNodeItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : OrgGraphElementItem(store, index, parent) {
        updateStateFromIndex();
    }

    Opt<QRect> rect;

    void updateStateFromIndex() {
        rect = qindex_get<QRect>(index, OrgGraphRoles::NodeShape);
    }

    OrgBoxId getBox() const {
        return qindex_get<OrgBoxId>(index, SharedModelRoles::IndexBox);
    }

    QRect getRect() const {
        if (rect) {
            return *rect;
        } else {
            return QRect();
        }
    }

    QRectF boundingRect() const override { return getRect().toRectF(); }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        updateStateFromIndex();


        auto rect = getRect();

        painter->save();
        {
            painter->setPen(QPen{Qt::black, 2});
            painter->setBrush(QBrush{QColor{215, 214, 213}});
            painter->drawRoundedRect(rect, 5, 5);
        }
        painter->restore();

        painter->save();
        if (false) {
            painter->setPen(QPen{Qt::black, 2});
            painter->drawText(
                rect.topLeft(),
                QString::fromStdString(qdebug_to_str(index)));
        }
        painter->restore();

        painter->save();
        sem::SemId<sem::Org> node = store->getBoxedNode(getBox());
        if (node->is(osk::AnnotatedParagraph)) {
            auto ap = node.as<sem::AnnotatedParagraph>();
            if (ap->getAnnotationKind()
                == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
                auto const& footnote = ap->getFootnote();
                QFont       current  = painter->font();
                QString     text     = QString("[%1]").arg(
                    QString::fromStdString(footnote.name));
                current.setPointSize(6);
                painter->setFont(current);

                QFontMetrics fm{current};
                QRect        textRect = fm.boundingRect(text)
                                     .translated(rect.topLeft())
                                     .marginsAdded(QMargins(2, 2, 2, 2));


                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(255, 0, 0));
                painter->drawRect(textRect);

                painter->setPen(Qt::black);
                painter->drawText(textRect, Qt::AlignCenter, text);
            }
        } else if (node->is(osk::Subtree)) {
            QFont   current = painter->font();
            QString text    = QString("*").repeated(
                node.as<sem::Subtree>()->level);
            current.setPointSize(12);
            current.setBold(true);
            painter->setFont(current);

            QFontMetrics fm{current};
            auto         pos = rect.topLeft();
            pos.setY(pos.y() + 7);
            QRect textRect = fm.boundingRect(text).translated(pos);

            painter->setPen(Qt::red);
            painter->drawText(textRect, Qt::AlignCenter, text);
        }

        painter->restore();

        painter->save();
        {
            QString text = qindex_get<QString>(index, Qt::DisplayRole);
            painter->translate(rect.topLeft());
            toDocument(text)->drawContents(painter);
        }
        painter->restore();
    }
};

OrgGraphView::OrgGraphView(
    GraphLayoutProxy* model,
    OrgStore*         store,
    QWidget*          parent)
    : QGraphicsView(parent)
    , store(store)
    , model(model)
//
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    background = std::make_shared<OrgBackgroundGridItem>(20, model);
    scene->addItem(background.get());

    setModel(model);
}

QSize OrgGraphView::getNodeSize(const QModelIndex& index) {
    GraphIndex gi{index};
    QString    text = gi.getDisplay();
    if (text.isEmpty()) {
        return QSize(20, 20);
    } else {
        return toDocument(text)->size().toSize();
    }
}

void OrgGraphView::updateItem(const QModelIndex& index) {
    QGraphicsItem* item = modelItems.at(index.row()).get();
    item->update();
    background->update();
}

void verifyModelGraph(QAbstractItemModel const* model) {
    auto const& roles = model->roleNames();
    Q_ASSERT_X(
        roles.contains((int)OrgGraphRoles::NodeShape),
        "verify model",
        "Model should pass through or directly provide a node and edge "
        "shape roles");


    Vec<QAbstractItemModel const*> models;
    while (model != nullptr) {
        models.push_back(model);
        if (auto dyn = qobject_cast<QSortFilterProxyModel const*>(model);
            dyn != nullptr) {
            model = dyn->sourceModel();
        } else {
            break;
        }
    }

    if (!rs::any_of(models, [](QAbstractItemModel const* m) {
            return qobject_cast<GraphLayoutProxy const*>(m) != nullptr;
        })) {
        Q_ASSERT_X(
            false,
            "verify model graph",
            "Abstract model does not have a layout provider in the filter "
            "chain.");
    }
}

void OrgGraphView::addItem(const QModelIndex& index) {
    GraphIndex gi{index};

    if (debug) { _qfmt("index:{} kind:{}", index, gi.getKind()); }

    verifyModelGraph(index.model());
    SPtr<OrgGraphElementItem> added;

    switch (gi.getKind()) {
        case OrgGraphElementKind::Node: {
            OrgNodeItem* polyline = new OrgNodeItem(store, index, nullptr);
            scene->addItem(polyline);
            added = SPtr<OrgGraphElementItem>(polyline);
            Q_ASSERT(polyline->scene() == scene);
            break;
        }

        case OrgGraphElementKind::Edge: {
            OrgEdgeItem* polyline = new OrgEdgeItem(store, index, nullptr);
            scene->addItem(polyline);
            added = SPtr<OrgGraphElementItem>(polyline);
            Q_ASSERT(polyline->scene() == scene);
            break;
        }

        case OrgGraphElementKind::Subgraph: {
            OrgSubgraphItem* subgraph = new OrgSubgraphItem(
                store, index, nullptr);
            scene->addItem(subgraph);
            added = SPtr<OrgGraphElementItem>(subgraph);
            break;
        }
    }

    if (index.row() < modelItems.size()) {
        modelItems.push_back(added);
    } else {
        modelItems.insert(modelItems.begin() + index.row(), added);
        onRowsShifted(index.row());
    }
}

void OrgGraphView::onRowsShifted(int lastShifted) {
    for (int row = lastShifted; row < modelItems.size(); ++row) {
        auto item = dynamic_cast<OrgGraphElementItem*>(
            modelItems.at(row).get());
        Q_ASSERT(item != nullptr);
        item->setIndex(model->index(row, 0));
        item->update();
    }
}

void OrgGraphView::validateItemRows() {
    for (int row = 0; row < std::min(modelItems.size(), model->rowCount());
         ++row) {
        QModelIndex index = model->index(row, 0);
        auto        item  = dynamic_cast<OrgGraphElementItem*>(
            modelItems.at(row).get());

        switch (GraphIndex{index}.getKind()) {
            case OrgGraphElementKind::Node: {
                auto item = dynamic_cast<OrgNodeItem*>(
                    modelItems.at(row).get());
                Q_ASSERT(item != nullptr);
                break;
            }

            case OrgGraphElementKind::Edge: {
                auto item = dynamic_cast<OrgEdgeItem*>(
                    modelItems.at(row).get());
                Q_ASSERT(item != nullptr);
                break;
            }


            case OrgGraphElementKind::Subgraph: {
                auto item = dynamic_cast<OrgSubgraphItem*>(
                    modelItems.at(row).get());
                Q_ASSERT(item != nullptr);
                break;
            }
        }

        Q_ASSERT_X(
            item->getIndex().row() == index.row(),
            "validateItemRows",
            fmt("item row: {}, index row: {}",
                item->getIndex().row(),
                index.row()));
    }

    Q_ASSERT_X(
        modelItems.size() == model->rowCount(),
        "validateItemRows",
        fmt("Base model {} has {} rows, list model items have {}",
            qdebug_to_str(model),
            model->rowCount(),
            modelItems.size()));
}

void OrgGraphView::removeSceneItem(int row) {
    QGraphicsItem* item = modelItems.at(row).get();
    Q_ASSERT(item != nullptr);
    Q_ASSERT(item->scene() == scene);
    scene->removeItem(item);
    modelItems.erase(modelItems.begin() + row);
}

void OrgGraphView::setModel(QAbstractItemModel* model) {
    verifyModelGraph(model);
    QObject::disconnect(this->model, nullptr, this, nullptr);
    this->model                                                    = model;
    dynamic_cast<OrgBackgroundGridItem*>(background.get())->source = model;
    connectModel();
}

void OrgGraphView::rebuildScene() {
    while (!modelItems.empty()) { removeSceneItem(modelItems.high()); }

    Q_ASSERT_X(
        modelItems.size() == 0,
        "rebuildScene",
        fmt("size:{}", modelItems.size()));

    Q_ASSERT_X(
        graphItems().size() == 0,
        "rebuildScene",
        fmt("scene:{}", graphItems()));

    int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        Q_ASSERT(model != nullptr);
        auto index = model->index(row, 0);
        addItem(index);
    }
}
