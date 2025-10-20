#include "DiaNodeLayout.hpp"
#include <src/model/layout/ElkJsonSerial.hpp>
#include <src/model/layout/ElkLayoutManager.hpp>

DiaLayout DiaLayout::FromDiagram(const DiaAdapter& a) {
    DiaLayout res;

    using namespace dia::layout::elk;

    Graph input;
    input.id = "root";

    hstd::UnorderedMap<hstd::Str, DiaUniqId> idMap;

    auto aux_tree_visit = [&](DiaAdapter const& rec, auto& self) -> Node {
        Node node;
        node.id = hstd::fmt1(rec.id);
        idMap.insert_or_assign(node.id, rec.id);
        for (auto const& sub : rec.sub(true)) {
            res.parents.insert_or_assign(sub.id, rec.id);
            node.children->push_back(self(sub, self));
        }

        return node;
    };

    for (auto const& sub : a.sub(true)) {
        res.parents.insert_or_assign(sub.id, a.id);
        input.children->push_back(aux_tree_visit(sub, aux_tree_visit));
    }

    ElkLayoutManager manager{};
    Graph            output = manager.layoutDiagram(input);


    return res;
}
