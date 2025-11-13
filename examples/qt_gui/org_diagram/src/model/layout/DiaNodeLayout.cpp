#include "DiaNodeLayout.hpp"
#include <src/model/layout/ElkJsonSerial.hpp>
#include <src/model/layout/ElkLayoutManager.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

Size DiaLayout::getSize(const DiaUniqId& id) const { return sizes.at(id); }

Point DiaLayout::getRelPos(const DiaUniqId& id) const {
    return relPositions.at(id);
}

namespace {
template <typename T>
std::string hash_fmt(T const& value) {
    return hstd::fmt1(std::hash<T>{}(value));
}
} // namespace

DiaLayout DiaLayout::FromDiagram(const DiaAdapter& a) {
    DiaLayout res;

    using namespace dia::layout::elk;

    Graph input;
    input.id = "root";

    input.layoutOptions = json::object({
        {"elk.algorithm", "layered"},
        {"elk.layered.feedbackEdges", true},
        {"elk.hierarchyHandling", "SEPARATE_CHILDREN"},
        {"elk.alignment", "RIGHT"},
        {"elk.direction", "RIGHT"},
        {"elk.aspectRatio", 10},
        {"elk.edgeRouting", "ORTHOGONAL"},
        {"elk.layered.nodePlacement.bk.fixedAlignment", "BALANCED"},
        {"elk.layered.allowNonFlowPortsToSwitchSides", true},
        {"elk.spacing.edgeNode", 30},
        {"elk.spacing.nodeNode", 10},
        {"partitioning.activate", true},
        {"nodeFlexibility", "NODE_SIZE"},
    });

    hstd::UnorderedMap<hstd::Str, DiaUniqId> idMap;

    auto aux_tree_visit = [&](DiaAdapter const&                 rec,
                              std::optional<std::string> const& parentId,
                              auto& self) -> hstd::Opt<Node> {
        auto pred = isSubtreeItem(
            rec.getImmAdapter().as<org::imm::ImmSubtree>());
        hstd::Opt<Node> result;
        if (pred) {
            auto geom_res = rec.getStructuredSubtreeProperty<
                DiaNodeItem::Geometry>(DiaPropertyNames::diagramGeometry);

            Node node;
            node.id = hash_fmt(rec.id);

            auto geom = geom_res.assume_value();

            node.width  = geom.size->width();
            node.height = geom.size->height();

            idMap.insert_or_assign(node.id, rec.id);

            if (!input.edges) { input.edges.emplace(); }
            if (parentId) {
                input.edges.value().push_back(Edge{
                    .id = hstd::fmt("{}-{}", parentId.value(), node.id),
                    .source = parentId.value(),
                    .target = node.id,
                });
            }

            result = node;
        } else {
            HSLOG_DEBUG("aux tree {}", pred.assume_error());
        }

        for (auto const& sub : rec.sub(true)) {
            res.parents.insert_or_assign(sub.id, rec.id);
            auto tmp = self(
                sub,
                result.has_value() ? std::optional<std::string>{result->id}
                                   : std::nullopt,
                self);
            if (tmp) { input.children.push_back(tmp.value()); }
        }

        return result;
    };

    for (auto const& sub : a.sub(true)) {
        res.parents.insert_or_assign(sub.id, a.id);
        auto tmp = aux_tree_visit(sub, std::nullopt, aux_tree_visit);
        if (tmp) { input.children.push_back(tmp.value()); }
    }

    ElkLayoutManager manager{};
    Graph            output = manager.layoutDiagram(input);

    auto aux_graph_visit = [&](Node const& node, auto&& self) -> void {
        res.relPositions.insert_or_assign(
            idMap.at(node.id),
            ::Point(int(node.x.value()), int(node.y.value())));

        for (auto const& sub : node.children) { self(sub, self); }
    };

    for (auto const& node : output.children) {
        aux_graph_visit(node, aux_graph_visit);
    }

    return res;
}
