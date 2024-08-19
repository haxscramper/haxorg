#include <editor/editor_lib/mind_map/org_graph_layout.hpp>
#include <editor/editor_lib/common/app_utils.hpp>
#include <QPainterPath>
#include <hstd/stdlib/Set.hpp>


template <typename T>
enumerator_impl<T*> enumerator(T const* it, int size) {
    return enumerator_impl<T*>(it, it + size);
}


QPainterPath toQPainterPath(const GraphPath& path) {
    QPainterPath res;
    if (path.bezier) {
        if (path.startPoint) {
            res.moveTo(toQPoint(*path.startPoint));
            res.lineTo(toQPoint(path.points.at(0)));
        } else {
            res.moveTo(toQPoint(path.points.at(0)));
        }

        for (int i = 1; i < path.points.size(); i += 3) {
            res.cubicTo(
                toQPoint(path.points.at(i)),
                toQPoint(path.points.at(i + 1)),
                toQPoint(path.points.at(i + 2)));
        }

        if (path.endPoint) { res.moveTo(toQPoint(*path.endPoint)); }
    } else {
        for (auto const& point : path.points) {
            res.moveTo(point.x, point.y);
        }
    }
    return res;
}

QPoint toQPoint(const GraphPoint& point) {
    return QPoint(point.x, point.y);
}

QRect toQRect(const GraphRect& rect) {
    return QRect(rect.left, rect.top, rect.width, rect.height);
}
