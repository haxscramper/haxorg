#include "DiaNodeLayout.hpp"
#include <src/model/layout/ElkJsonSerial.hpp>
#include <src/model/layout/ElkLayoutManager.hpp>

Size DiaLayout::getSize(const DiaUniqId& id) const { return sizes.at(id); }

Point DiaLayout::getRelPos(const DiaUniqId& id) const {
    return relPositions.at(id);
}

DiaLayout DiaLayout::FromDiagram(const DiaAdapter& a) {
    DiaLayout res;

    using namespace dia::layout::elk;

    Graph input;
    input.id = "root";

    hstd::UnorderedMap<hstd::Str, DiaUniqId> idMap;

    auto aux_tree_visit = [&](DiaAdapter const&  rec,
                              std::string const& parentId,
                              auto&              self) -> Node {
        Node node;
        node.id = hstd::fmt1(rec.id);
        idMap.insert_or_assign(node.id, rec.id);

        input.edges->push_back(
            Edge{.source = parentId, .target = node.id});

        for (auto const& sub : rec.sub(true)) {
            res.parents.insert_or_assign(sub.id, rec.id);
            node.children->push_back(self(sub, node.id, self));
        }

        return node;
    };

    for (auto const& sub : a.sub(true)) {
        res.parents.insert_or_assign(sub.id, a.id);
        input.children->push_back(
            aux_tree_visit(sub, input.id, aux_tree_visit));
    }

    ElkLayoutManager manager{};
    Graph            output = manager.layoutDiagram(input);

    auto aux_graph_visit = [&](Node const& node, auto&& self) -> void {
        res.relPositions.insert_or_assign(
            idMap.at(node.id),
            ::Point(int(node.x.value()), int(node.y.value())));

        if (node.children) {
            for (auto const& sub : node.children.value()) {
                self(sub, self);
            }
        }
    };

    for (auto const& node : output.children.value()) {
        aux_graph_visit(node, aux_graph_visit);
    }

    return res;
}
