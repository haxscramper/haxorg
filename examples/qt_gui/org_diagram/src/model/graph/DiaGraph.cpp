#include "DiaGraph.hpp"

#include <hstd/stdlib/Ranges.hpp>
#include <haxorg/sem/ImmOrgGraph.hpp>

hstd::Vec<org::graph::Edge> DiaHierarchyEdgeCollection::getOutgoing(
    const org::graph::VertexID& vert) {
    hstd::Vec<org::graph::Edge> res;
    for (auto const& sub :
         DiaAdapter{graph->getVertex(vert).uniq, tree_context}.sub(true)) {
        res.push_back(org::graph::Edge(vert, graph->getID(sub.uniq()), 0));
    }
    HSLOG_DEBUG("get outgoing {}", res);
    return res;
}

json DiaHierarchyEdgeCollection::getEdgeSerial(
    const org::graph::EdgeID& id) const {
    auto const& e = getEdge(id);
    return hstd::to_json_eval(SerialSchema{
        .edgeId      = std::format("{}", std::hash<org::graph::Edge>{}(e)),
        .sourceId    = graph->getVertex(e.source).getStableId(),
        .targetId    = graph->getVertex(e.target).getStableId(),
        .bundleIndex = e.bundleIndex,
    });
}

json DiaGraph::getVertexSerial(const org::graph::VertexID& id) const {
    DiaGraph::SerialSchema res{
        .vertexId = getVertex(id).getStableId(),
    };

    auto ad = getAdapter(id);
    if (auto subtree = ad.getImmAdapter().asOpt<org::imm::ImmSubtree>();
        subtree) {
        res.vertexName = subtree->getCleanTitle();
    }

    return hstd::to_json_eval(res);
}

void DiaSubtreeIdTracker::trackVertex(const org::graph::VertexID& vertex) {
    auto ad = graph->getAdapter(vertex);
    if (auto subtree = ad.getImmAdapter().asOpt<org::imm::ImmSubtree>();
        subtree && subtree.value()->treeId->has_value()) {
        HSLOG_DEBUG(
            "Tracking {} with ID",
            vertex,
            subtree.value()->treeId->value());
        map.insert_or_assign(subtree.value()->treeId->value(), vertex);
    }
}

void DiaSubtreeIdTracker::untrackVertex(
    const org::graph::VertexID& vertex) {
    auto ad = graph->getAdapter(vertex);
    if (auto subtree = ad.getImmAdapter().asOpt<org::imm::ImmSubtree>();
        subtree && subtree.value()->treeId->has_value()) {
        auto id = subtree.value()->treeId->value();
        if (map.contains(id)) { map.erase(id); }
    }
}

hstd::Vec<org::graph::VertexID> DiaSubtreeIdTracker::getVertices(
    const org::graph::IProperty& prop) {
    auto id_prop = dynamic_cast<DiaSubtreeIdProperty const*>(&prop);
    hstd::Vec<org::graph::VertexID> res;
    HSLOG_DEBUG("Getting vertices for property ID: {}", id_prop->getId());
    if (id_prop != nullptr && map.contains(id_prop->getId())) {
        res.push_back(map.at(id_prop->getId()));
    }
    return res;
}

hstd::Vec<org::graph::Edge> DiaDescriptionListEdgeCollection::getOutgoing(
    const org::graph::VertexID& vert) {
    auto ad  = graph->getAdapter(vert);
    auto imm = ad.getImmAdapter();
    if (!imm.is(OrgSemKind::Subtree)) { return {}; }

    hstd::Vec<org::graph::Edge> res;
    auto                        tree = imm.as<org::imm::ImmSubtree>();

    for (auto const& sub : tree.sub(true)) {
        if (!org::graph::isAttachedDescriptionList(sub)) { continue; }
        HSLOG_DEBUG("Found attached description list");

        HSLOG_DEBUG("{}", sub.treeReprString());

        for (auto const& item : sub.subAs<org::imm::ImmListItem>(true)) {
            if (!org::graph::isDescriptionItem(item)) { continue; }
            HSLOG_DEBUG("Found description list item");

            for (auto const& link : item.pass(item->header->value())
                                        .subAs<org::imm::ImmLink>()) {
                HSLOG_DEBUG(
                    "Found link in item header, link kind {}",
                    link->target.getKind());
                if (!link->target.isId()) { continue; }
                HSLOG_DEBUG("Link is targeting ID");

                for (auto const& v :
                     tracker->getVertices(DiaSubtreeIdProperty(
                         link->target.getId().text))) {
                    res.push_back(org::graph::Edge{
                        .source = vert,
                        .target = v,
                    });
                }
            }
        }
    }

    return res;
}

json DiaDescriptionListEdgeCollection::getEdgeSerial(
    const org::graph::EdgeID& id) const {
    auto const& e = getEdge(id);
    return hstd::to_json_eval(SerialSchema{
        .edgeId      = std::format("{}", std::hash<org::graph::Edge>{}(e)),
        .sourceId    = graph->getVertex(e.source).getStableId(),
        .targetId    = graph->getVertex(e.target).getStableId(),
        .bundleIndex = e.bundleIndex,
    });
}
