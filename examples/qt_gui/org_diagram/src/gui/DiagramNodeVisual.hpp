#pragma once

#include "DiagramNode.hpp"
#include <QGraphicsScene>
#include <QRectF>
#include <QGraphicsRectItem>
#include "DebugPainter.hpp"
#include <QGraphicsSceneMouseEvent>

struct DiagramNodeVisual
    : public DiagramNode
    , public QGraphicsItem {
    QRectF  bounds{0, 0, 100, 50};
    QPointF dragOffset{};

    DiagramNodeVisual(const QString& nodeName = "Node")
        : DiagramNode{nodeName} {
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }

    virtual QWidget* createPropertiesWidget(QWidget* parent) = 0;

    QRectF boundingRect() const override {
        QRectF rect = bounds;
        rect        = rect.united(getAdditionalBounds());
        return rect.adjusted(-5, -5, 15, 15);
    }

    void paint(
        QPainter*                       _painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        auto painter = std::make_shared<DebugPainter>(
            _painter, TraceState, "EdgeNode::paint", CALL_LOC());
        paintNode(_painter);
        paintText(_painter);
    }

    virtual void   paintNode(QPainter* painter) = 0;
    virtual QRectF getAdditionalBounds() const { return QRectF{}; }

    void paintText(QPainter* painter) {
        painter->setPen(QPen{Qt::black});
        painter->drawText(bounds, Qt::AlignCenter, name);
    }


    void setPosition(const QPointF& pos, int gridSnap) {
        int x = (static_cast<int>(pos.x()) / gridSnap) * gridSnap;
        int y = (static_cast<int>(pos.y()) / gridSnap) * gridSnap;
        setPos(x, y);
    }

    void updateConnectedEdges();


    QVariant itemChange(GraphicsItemChange change, const QVariant& value)
        override {
        if (change == ItemPositionHasChanged) { updateConnectedEdges(); }
        return QGraphicsItem::itemChange(change, value);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        if (handleMousePress(event)) { return; }

        dragOffset = event->pos();
        QGraphicsItem::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (handleMouseMove(event)) { return; }

        QGraphicsItem::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        handleMouseRelease(event);
        QGraphicsItem::mouseReleaseEvent(event);
    }

    virtual bool handleMousePress(QGraphicsSceneMouseEvent* event) {
        return false;
    }
    virtual bool handleMouseMove(QGraphicsSceneMouseEvent* event) {
        return false;
    }
    virtual void handleMouseRelease(QGraphicsSceneMouseEvent* event) {}
};
