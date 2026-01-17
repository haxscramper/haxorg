#pragma once

#include <org_diagram/src/model/nodes/DiagramTreeNode.hpp>
#include <org_diagram/src/utils/geometry.hpp>

struct DiaLayout {
    hstd::UnorderedMap<DiaUniqId, Size>      sizes;
    hstd::UnorderedMap<DiaUniqId, Point>     relPositions;
    hstd::UnorderedMap<DiaUniqId, DiaUniqId> parents;

    Size  getSize(DiaUniqId const& id) const;
    Point getRelPos(DiaUniqId const& id) const;

    static DiaLayout FromDiagram(DiaAdapter const& a);
};
