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

namespace {
json toJson(org::sem::SemId<org::sem::Org> const& id) {
    auto exp           = org::algo::ExporterJson{};
    exp.skipEmptyLists = true;
    exp.skipLocation   = true;
    exp.skipId         = true;
    exp.skipNullFields = true;
    return exp.eval(id);
}
} // namespace

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

        res.extra.nestingLevel = graph->getParentChain(id).size();

        if (ad.getKind() == DiaNodeKind::Item) {
            auto geometry = ad->as<DiaNodeItem>()->getGeometry();
            if (geometry) {
                HSLOG_DEBUG(
                    "Get node item {} geometry {}",
                    subtree.value()->treeId,
                    geometry);
                res.extra.geometry = geometry.assume_value();
            }
        }

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

        hstd::Vec<org::sem::SemId<org::sem::Org>> directTitle;

        hstd::Vec<org::imm::ImmAdapter> title_seq;
        for (auto const& it : subtree->getTitle()) {
            title_seq.push_back(it);
        }

        int i = 0;


        for (; i < title_seq.size(); ++i) {
            auto const& node = title_seq.at(i);
            if (auto big = node.asOpt<org::imm::ImmBigIdent>();
                big && todo_kwds.contains(big->getText())) {
                res.extra.todoState = big.value()->text;
                if (title_seq.has(i + 1)
                    && title_seq.at(i + 1).getKind()
                           == OrgSemKind::Space) {
                    ++i;
                }
                continue;
            } else {
                break;
            }
        }


        for (; i < title_seq.size(); ++i) {
            auto const& node = title_seq.at(i);
            title.push_back(org::getCleanText(node));
            directTitle.push_back(
                org::imm::sem_from_immer(node.id, *subtree->ctx.lock()));
        }

        {
            auto par      = org::sem::SemId<org::sem::Paragraph>::New();
            par->subnodes = directTitle;
            res.extra.structuredName = toJson(par);
        }

        res.vertexName = hstd::join(" ", title);

        res.extra_type = hstd::value_metadata<SerialSchema>::typeName();

        for (auto const& desc :
             subtree->subAs<org::imm::ImmBlockDynamicFallback>()) {
            auto sem = org::imm::sem_from_immer(desc.id, *desc.ctx.lock());
            res.extra.structuredDescription = toJson(sem);

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

namespace {
bool isAttachedList(org::imm::ImmAdapter const& n) {
    if (auto list = n.asOpt<org::imm::ImmList>(); list) {
        auto attached = list->getListAttrs("attached");
        return attached.has(0) && attached.at(0).getString() == "subtree";
    } else {
        return false;
    }
}
} // namespace

hstd::Vec<org::graph::EdgeID> DiaDescriptionListEdgeCollection::
    addAllOutgoing(const org::graph::VertexID& vert) {
    auto ad  = graph->getAdapter(vert);
    auto imm = ad.getImmAdapter();
    if (!imm.is(OrgSemKind::Subtree)) { return {}; }

    hstd::Vec<org::graph::EdgeID> res;
    auto                          tree = imm.as<org::imm::ImmSubtree>();

    for (auto const& sub : tree.sub(true)) {
        if (!isAttachedList(sub)) { continue; }
        // HSLOG_DEBUG("Found attached description list");
        for (auto const& item : sub.subAs<org::imm::ImmListItem>(true)) {
            auto add_link =
                [&](org::imm::ImmAdapterT<org::imm::ImmLink> const& link,
                    hstd::Opt<org::imm::ImmAdapter> const&          brief,
                    hstd::Vec<org::imm::ImmAdapter> const& detailed) {
                    // HSLOG_DEBUG(
                    //     "Found link in item header, link kind {}",
                    //     link->target.getKind());
                    if (!link->target.isId()) { return; }
                    // HSLOG_DEBUG(
                    //     "Link is targeting ID {}",
                    //     link->target.getId().text);

                    auto targets = tracker->getVertices(
                        DiaSubtreeIdProperty(link->target.getId().text));

                    if (targets.empty()) {
                        HSLOG_WARNING("Could not find matching targets");
                    } else {
                        for (auto const& v : targets) {
                            // HSLOG_TRACE("Found target {}", v);
                            DiaDescriptionListEdge edge{vert, v};
                            edge.edgeBrief    = brief;
                            edge.edgeDetailed = detailed;
                            auto res_id = store.add(edge, getCategory().t);
                            trackEdge(res_id);
                            res.push_back(res_id);
                        }
                    }
                };

            if (org::graph::isDescriptionItem(item)) {
                for (auto const& link : item.pass(item->header->value())
                                            .subAs<org::imm::ImmLink>()) {
                    hstd::Opt<org::imm::ImmAdapter> brief;
                    hstd::Vec<org::imm::ImmAdapter> detailed;
                    if (0 < item->size()) { brief = item.at(0); }
                    if (1 < item.size()) {
                        hstd::Slice<int> rng = hstd::slice1(
                            1, item.size() - 1);
                        SemSet skip{OrgSemKind::Newline};

                        while (skip.contains(item.at(rng.first).getKind())
                               && rng.first < rng.last) {
                            ++rng.first;
                        }


                        while (skip.contains(item.at(rng.last).getKind())
                               && rng.first < rng.last) {
                            --rng.last;
                        }

                        if (rng.first != rng.last
                            || !skip.contains(
                                item.at(rng.first).getKind())) {
                            for (int i = 1; i < item.size(); ++i) {
                                detailed.push_back(item.at(i));
                            }
                        }
                    }


                    add_link(link, brief, detailed);
                }
            } else {
                for (auto const& link :
                     item.at(0).subAs<org::imm::ImmLink>()) {
                    add_link(link, std::nullopt, {});
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

json DiaDescriptionListEdge::getSerialNonRecursive(
    const org::graph::IGraph* graph,
    const org::graph::EdgeID& id) const {
    json result = org::graph::IEdge::getSerialNonRecursive(graph, id);
    result["extra_type"] = hstd::value_metadata<SerialSchema>::typeName();
    auto& extra          = result["extra"];
    if (edgeBrief) {
        auto briefSem = org::imm::sem_from_immer(
            edgeBrief.value().id, *edgeBrief.value().ctx.lock());
        extra["edgeBrief"] = org::algo::ExporterUltraplain::toStr(
            briefSem);
        extra["structuredEdgeBrief"] = toJson(briefSem);
    }

    if (!edgeDetailed.empty()) {
        auto detailedSem = org::sem::SemId<org::sem::StmtList>::New();
        for (auto const& det : edgeDetailed) {
            detailedSem->push_back(
                org::imm::sem_from_immer(det.id, *det.ctx.lock()));
        }

        extra["edgeBrief"] = org::algo::ExporterUltraplain::toStr(
            detailedSem);
        extra["structuredEdgeBrief"] = toJson(detailedSem);
    }

    return result;
}
