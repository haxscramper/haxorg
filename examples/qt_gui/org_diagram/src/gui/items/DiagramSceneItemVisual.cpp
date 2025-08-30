#include "DiagramSceneItemVisual.hpp"
#include "DiagramSceneItemEdge.hpp"

void DiagramSceneItemVisual::updateConnectedEdges() {
    auto scene = this->scene();
    if (!scene) { return; }

    for (auto item : scene->items()) {
        if (auto edge = dynamic_cast<DiagramSceneItemEdge*>(item)) {
            if (edge->sourceNode == this || edge->targetNode == this) {
                edge->updateBounds();
            }
        }
    }
}
