#include "DiaSceneItemVisual.hpp"
#include "DiaSceneItemEdge.hpp"

void DiaSceneItemVisual::updateConnectedEdges() {
    auto scene = this->scene();
    if (!scene) { return; }

    for (auto item : scene->items()) {
        if (auto edge = dynamic_cast<DiaSceneItemEdge*>(item)) {
            if (edge->sourceNode == this || edge->targetNode == this) {
                edge->updateBounds();
            }
        }
    }
}
