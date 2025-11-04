#include "DiaGraph.hpp"

#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <haxorg/sem/ImmOrgGraph.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/exporters/ExporterUltraplain.hpp>

hstd::Vec<org::graph::EdgeID> DiaHierarchyEdgeCollection::addAllOutgoing(
    const org::graph::VertexID& vert) {
    hstd::Vec<org::graph::EdgeID> res;
    for (auto const& sub :
         DiaAdapter{graph->getVertex(vert).uniq, tree_context}.sub(true)) {
        auto res_id = store.add(
            DiaHierarchyEdge{vert, graph->getID(sub.uniq())},
            getCategory().t);
        trackEdge(res_id);
        res.push_back(res_id);
    }
    HSLOG_DEBUG("get outgoing {}", res);
    return res;
}

org::graph::VertexID DiaGraph::addVertex(const DiaUniqId& id) {
    auto result = vertices.add(DiaGraphVertex{id});
    registerVertex(result);
    return result;
}

org::graph::VertexID DiaGraph::delVertex(const DiaUniqId& id) {
    auto result = vertices.del(DiaGraphVertex(id));
    unregisterVertex(result);
    return result;
}

json DiaGraphVertex::getSerialNonRecursive(
    org::graph::IGraph const*   graph_,
    const org::graph::VertexID& id) const {
    DiaGraph const* graph = dynamic_cast<DiaGraph const*>(graph_);
    auto            ad    = graph->getAdapter(id);

    DiaGraphVertex::SerialSchema res{
        .vertexId   = getStableId(),
        .vertexKind = hstd::fmt1(ad.getKind()),
    };


    if (auto subtree = ad.getImmAdapter().asOpt<org::imm::ImmSubtree>();
        subtree) {

        org::imm::ImmAdapter::TreeReprConf conf;

        conf.withAuxFields = true;

        // HSLOG_TRACE(
        //     "Get vertex serial for subtree:\n{}",
        //     subtree->treeRepr(conf).toString(false));

        hstd::Vec<std::string> title;

        auto todo_kwds = hstd::Vec<hstd::Str>{
            "TODO",
            "DONE",
            "COMPLETED",
            "FAILED",
            "NEXT",
            "WIP",
            "CANCELLED"};

        for (auto const& node : subtree->getTitle()) {
            if (auto big = node.asOpt<org::imm::ImmBigIdent>();
                big && todo_kwds.contains(big->getText())) {
                continue;
            }

            if (node.getKind() == OrgSemKind::Space) { continue; }

            title.push_back(org::getCleanText(node));
        }

        res.vertexName = hstd::join(" ", title);

        res.extra_type = hstd::value_metadata<SerialSchema>::typeName();

        for (auto const& desc :
             subtree->subAs<org::imm::ImmBlockDynamicFallback>()) {
            auto exp           = org::algo::ExporterJson{};
            exp.skipEmptyLists = true;
            exp.skipLocation   = true;
            exp.skipId         = true;
            exp.skipNullFields = true;
            auto sem = org::imm::sem_from_immer(desc.id, *desc.ctx.lock());
            res.extra.structuredDescription = exp.evalTop(sem);

            res.vertexDescription = org::algo::ExporterUltraplain::toStr(
                sem);
        }
    }

    return hstd::to_json_eval(res);
}

void DiaSubtreeIdTracker::trackVertex(const org::graph::VertexID& vertex) {
    auto ad = graph->getAdapter(vertex);
    if (auto subtree = ad.getImmAdapter().asOpt<org::imm::ImmSubtree>();
        subtree && subtree.value()->treeId->has_value()) {
        HSLOG_DEBUG(
            "Tracking {} with ID '{}'",
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

hstd::Vec<org::graph::EdgeID> DiaDescriptionListEdgeCollection::
    addAllOutgoing(const org::graph::VertexID& vert) {
    auto ad  = graph->getAdapter(vert);
    auto imm = ad.getImmAdapter();
    if (!imm.is(OrgSemKind::Subtree)) { return {}; }

    hstd::Vec<org::graph::EdgeID> res;
    auto                          tree = imm.as<org::imm::ImmSubtree>();

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
                HSLOG_DEBUG(
                    "Link is targeting ID {}", link->target.getId().text);

                auto targets = tracker->getVertices(
                    DiaSubtreeIdProperty(link->target.getId().text));

                if (targets.empty()) {
                    HSLOG_WARNING("Could not find matching targets");
                } else {
                    for (auto const& v : targets) {
                        HSLOG_TRACE("Found target {}", v);
                        auto res_id = store.add(
                            DiaDescriptionListEdge{vert, v},
                            getCategory().t);
                        trackEdge(res_id);
                        res.push_back(res_id);
                    }
                }
            }
        }
    }

    return res;
}

std::string DiaGraphVertex::getStableId() const {
    return std::format(
        "{}-{}",
        uniq.target,
        hstd::hash_to_uint16(std::hash<DiaUniqId>{}(uniq)));
}

std::size_t DiaGraphVertex::getHash() const {
    return std::hash<DiaUniqId>{}(uniq);
}

bool DiaGraphVertex::isEqual(const IGraphObjectBase* other) const {
    LOGIC_ASSERTION_CHECK(other->isInstance<DiaGraphVertex>(), "");
    return dynamic_cast<DiaGraphVertex const*>(other)->uniq == this->uniq;
}

std::string DiaGraphVertex::getRepr() const { return hstd::fmt1(uniq); }
