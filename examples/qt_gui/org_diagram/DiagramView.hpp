#pragma once

#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
#include "DiagramNodeVisual.hpp"
#include "common.hpp"

#define _cat "app.view"

class DiagramView : public QGraphicsView {
    Q_OBJECT

  public:
    DiagramView(QWidget* parent = nullptr) : QGraphicsView{parent} {
        setDragMode(QGraphicsView::RubberBandDrag);
        setRenderHint(QPainter::Antialiasing);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        setInteractive(true);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }

  signals:
    void zoomChanged(int zoomPercent);
    void sceneSelectionChanged(
        const QList<DiagramNodeVisual*>& selectedNodes);

  public:
    void wheelEvent(QWheelEvent* event) override {
        const int degrees = event->angleDelta().y() / 8;
        const int steps   = degrees / 15;

        const qreal scaleFactor = 1.15;
        qreal       factor      = qPow(scaleFactor, steps);

        QTransform currentTransform = transform();
        qreal      currentScale     = currentTransform.m11();
        qreal      newScale         = currentScale * factor;

        const qreal minScale = 0.1;
        const qreal maxScale = 5.0;

        if (newScale < minScale) {
            factor = minScale / currentScale;
        } else if (newScale > maxScale) {
            factor = maxScale / currentScale;
        }

        scale(factor, factor);

        QTransform newTransform = transform();
        int  zoomPercent = static_cast<int>(newTransform.m11() * 100);
        emit zoomChanged(zoomPercent);
    }

  public slots:
    void selectNodes(const QList<DiagramNodeVisual*>& nodes) {
        if (!scene()) { return; }

        // Block signals to prevent infinite recursion
        blockSignals(true);

        // Clear current selection
        scene()->clearSelection();

        // Select the specified nodes
        for (DiagramNodeVisual* node : nodes) {
            if (node) { node->setSelected(true); }
        }

        blockSignals(false);
    }

  private slots:
    void onSceneSelectionChanged() { emitSelectionChanged(); }

  protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton
            && event->modifiers() & Qt::ControlModifier) {
            isPanning    = true;
            lastPanPoint = event->position().toPoint();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
        } else {
            QGraphicsView::mousePressEvent(event);
            emitSelectionChanged();
        }
    }


    void mouseMoveEvent(QMouseEvent* event) override {
        if (isPanning) {
            // Calculate the difference in screen coordinates
            QPoint delta = event->position().toPoint() - lastPanPoint;

            // Update scrollbars directly (note the sign reversal)
            horizontalScrollBar()->setValue(
                horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(
                verticalScrollBar()->value() - delta.y());

            lastPanPoint = event->position().toPoint();
            event->accept();
        } else {
            QGraphicsView::mouseMoveEvent(event);
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton && isPanning) {
            isPanning = false;
            setCursor(Qt::ArrowCursor);
            event->accept();
        } else {
            QGraphicsView::mouseReleaseEvent(event);
        }
    }

  private:
    void emitSelectionChanged() {
        if (!scene()) { return; }
        QList<DiagramNodeVisual*> selectedNodes;
        QList<QGraphicsItem*>     selectedItems = scene()->selectedItems();

        for (QGraphicsItem* item : selectedItems) {
            DiagramNodeVisual* nodeVisual = dynamic_cast<
                DiagramNodeVisual*>(item);
            if (nodeVisual) {
                HSLOG_DEBUG(
                    _cat, "Selected node ", nodeVisual->name.toStdString());
                selectedNodes.append(nodeVisual);
            }
        }

        emit sceneSelectionChanged(selectedNodes);
    }

    void connectToScene() {
        if (scene()) {
            connect(
                scene(),
                &QGraphicsScene::selectionChanged,
                this,
                &DiagramView::onSceneSelectionChanged);
        }
    }

  public:
    void setScene(QGraphicsScene* scene) {
        QGraphicsView::setScene(scene);
        connectToScene();
    }

  private:
    bool   isPanning{false};
    QPoint lastPanPoint{};
};
