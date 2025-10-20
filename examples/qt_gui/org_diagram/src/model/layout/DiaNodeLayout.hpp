#pragma once

#include <src/model/nodes/DiagramTreeNode.hpp>

struct DiaLayout {
    hstd::UnorderedMap<DiaUniqId, Size>      sizes;
    hstd::UnorderedMap<DiaUniqId, Point>     relPositions;
    hstd::UnorderedMap<DiaUniqId, DiaUniqId> parents;

    Size  getSize(DiaUniqId const& id) const;
    Point getRelPos(DiaUniqId const& id) const;

    static DiaLayout FromDiagram(DiaAdapter const& a);
};
