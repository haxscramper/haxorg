#include "DiagramView.hpp"
#include <src/utils/common.hpp>

void DiagramView::wheelEvent(QWheelEvent* event) {
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
    int        zoomPercent  = static_cast<int>(newTransform.m11() * 100);
    HSLOG_TRACKED_EMIT(get_tracker(), zoomChanged, zoomPercent);
}

void DiagramView::selectNodes(const QList<DiagramNodeVisual*>& nodes) {

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

void DiagramView::mousePressEvent(QMouseEvent* event) {
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

void DiagramView::mouseMoveEvent(QMouseEvent* event) {
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

void DiagramView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && isPanning) {
        isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void DiagramView::emitSelectionChanged() {
    if (!scene()) { return; }
    QList<DiagramNodeVisual*> selectedNodes;
    QList<QGraphicsItem*>     selectedItems = scene()->selectedItems();

    for (QGraphicsItem* item : selectedItems) {
        DiagramNodeVisual* nodeVisual = dynamic_cast<DiagramNodeVisual*>(
            item);
        if (nodeVisual) { selectedNodes.append(nodeVisual); }
    }

    HSLOG_TRACKED_EMIT(
        get_tracker(), sceneSelectionChanged, selectedNodes);
}
