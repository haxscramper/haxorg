#include "DiagramNodeVisual.hpp"
#include "DiagramNodeEdge.hpp"

void DiagramNodeVisual::updateConnectedEdges() {
    auto scene = this->scene();
    if (!scene) { return; }

    for (auto item : scene->items()) {
        if (auto edge = dynamic_cast<DiagramNodeEdge*>(item)) {
            if (edge->sourceNode == this || edge->targetNode == this) {
                edge->updateBounds();
            }
        }
    }
}
