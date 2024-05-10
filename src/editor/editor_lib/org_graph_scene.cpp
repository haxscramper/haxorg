#include <editor/editor_lib/org_graph_scene.hpp>
#include <editor/editor_lib/org_document_render.hpp>

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
                   OrgGraphLayoutProxy::LayoutBBoxRole)
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


struct OrgGraphElementItem : public QGraphicsItem {
    explicit OrgGraphElementItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : QGraphicsItem(parent), store(store), index(index) {}

    QModelIndex index;
    OrgStore*   store;
};


struct OrgEdgeItem : public OrgGraphElementItem {
    explicit OrgEdgeItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : OrgGraphElementItem(store, index, parent) {}

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

struct OrgNodeItem : public OrgGraphElementItem {
    explicit OrgNodeItem(
        OrgStore*          store,
        QModelIndex const& index,
        QGraphicsItem*     parent)
        : OrgGraphElementItem(store, index, parent) {
        updateRect();
    }

    Opt<QRect> rect;

    void updateRect() {
        rect = qvariant_cast<QRect>(
            index.data(OrgGraphModelRoles::NodeShapeRole));
    }

    OrgBoxId getBox() const {
        return qvariant_cast<OrgBoxId>(
            index.data(SharedModelRoles::IndexBoxRole));
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
        updateRect();

        auto rect = getRect();
        painter->save();
        {
            painter->setPen(QPen{Qt::black, 2});
            painter->setBrush(QBrush{QColor{215, 214, 213}});
            painter->drawRoundedRect(rect, 5, 5);
        }
        painter->restore();

        painter->save();
        sem::SemId<sem::Org> node = store->node(getBox());
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
    QAbstractItemModel* model,
    OrgStore*           store,
    QWidget*            parent)
    : QGraphicsView(parent)
    , store(store)
    , model(model)
//
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    background = std::make_shared<OrgBackgroundGridItem>(20, model);
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
    setModel(model);
}

QSize OrgGraphView::getNodeSize(const QModelIndex& index) {
    if (qindex_get<bool>(index, OrgGraphModelRoles::IsNodeRole)) {
        QString text = qindex_get<QString>(index, Qt::DisplayRole);
        if (text.isEmpty()) {
            return QSize(20, 20);
        } else {
            return toDocument(text)->size().toSize();
        }
    } else {
        return QSize(-1, -1);
    }
}

void OrgGraphView::updateItem(const QModelIndex& index) {
    QGraphicsItem* item = modelItems.at(index.row()).get();
    item->update();
    background->update();
}

void OrgGraphView::addItem(const QModelIndex& index) {
    SPtr<QGraphicsItem> added;
    if (qindex_get<bool>(index, OrgGraphModelRoles::IsNodeRole)) {
        OrgNodeItem* polyline = new OrgNodeItem(store, index, nullptr);
        scene->addItem(polyline);
        added = SPtr<QGraphicsItem>(polyline);
        Q_ASSERT(polyline->scene() == scene);
    } else {
        OrgEdgeItem* polyline = new OrgEdgeItem(store, index, nullptr);
        scene->addItem(polyline);
        added = SPtr<QGraphicsItem>(polyline);
        Q_ASSERT(polyline->scene() == scene);
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
        item->index = model->index(row, 0);
        item->update();
    }
}

void OrgGraphView::validateItemRows() {
    for (int row = 0; row < std::min(modelItems.size(), model->rowCount());
         ++row) {
        QModelIndex index = model->index(row, 0);
        auto        item  = dynamic_cast<OrgGraphElementItem*>(
            modelItems.at(row).get());

        if (qindex_get<bool>(index, OrgGraphModelRoles::IsNodeRole)) {
            auto item = dynamic_cast<OrgNodeItem*>(
                modelItems.at(row).get());
            Q_ASSERT(item != nullptr);

        } else {
            auto item = dynamic_cast<OrgEdgeItem*>(
                modelItems.at(row).get());
            Q_ASSERT(item != nullptr);
        }

        Q_ASSERT_X(
            item->index.row() == index.row(),
            "validateItemRows",
            fmt("item row: {}, index row: {}",
                item->index.row(),
                index.row()));
    }

    Q_ASSERT(modelItems.size() == model->rowCount());
}

void OrgGraphView::onRowsRemoved(
    const QModelIndex& parent,
    int                first,
    int                last) {
    for (int row = first; row <= last; ++row) {
        QModelIndex index = model->index(row, 0, parent);
        resetSceneItem(index.row());
    }

    for (int row = last; first <= row; ++row) {
        modelItems.erase(modelItems.begin() + row);
    }

    onRowsShifted(last);
    validateItemRows();
}

void OrgGraphView::setModel(QAbstractItemModel* model) {
    this->model = model;
    rebuildScene();
    dynamic_cast<OrgBackgroundGridItem*>(background.get())->source = model;
}

void OrgGraphView::rebuildScene() {
    for (int i = 0; i < modelItems.size(); ++i) { resetSceneItem(i); }
    modelItems.clear();

    int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        addItem(model->index(row, 0));
    }
}
