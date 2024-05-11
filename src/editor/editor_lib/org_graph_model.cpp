#include "qtextoption.h"
#include <editor/editor_lib/org_graph_model.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <boost/graph/graphviz.hpp>
#include <QDebug>
#include <exporters/ExporterUltraplain.hpp>
#include <editor/editor_lib/org_document_render.hpp>
#include <editor/editor_lib/org_exporter_html.hpp>
#include <hstd/stdlib/Set.hpp>

#pragma clang diagnostic error "-Wswitch"

using slk = sem::Link::Kind;

bool isLinkedDescriptionItem(sem::OrgArg n) {
    return n->is(osk::ListItem)
        && n.as<sem::ListItem>()->isDescriptionItem()
        && rs::any_of(
               n.as<sem::ListItem>()->header.value()->subnodes,
               [](sem::OrgArg head) {
                   return head->is(osk::Link)
                       && head.as<sem::Link>()->getLinkKind() != slk::Raw;
               });
}

bool isLinkedDescriptionItem(OrgStore* store, CR<OrgBoxId> box) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        store->getOrgTree(box)->parentChain(/*withSelf = */ false),
        [](OrgTreeNode* parent) -> bool {
            return isLinkedDescriptionItem(parent->boxedNode());
        });
}

void OrgGraph::addBox(CR<OrgBoxId> box) {
    if (isLinkedDescriptionItem(store, box)) { return; }


    sem::SemId<sem::Org> n = store->node(box);
    if (n->is(osk::Subtree)) {
        sem::SemId<sem::Subtree> tree = n.as<sem::Subtree>();
        if (tree->treeId) {
            this->subtreeIds[tree->treeId.value()].push_back(box);
        }
    } else if (n->is(osk::AnnotatedParagraph)) {
        sem::SemId<sem::AnnotatedParagraph>
            par = n.as<sem::AnnotatedParagraph>();
        if (par->getAnnotationKind()
            == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
            Str name = par->getFootnote().name;
            this->footnoteTargets[name].push_back(box);
        }
    }

    auto register_used_links = [&](sem::OrgArg arg) {
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (arg->is(osk::Link)) {
            auto link = arg.as<sem::Link>();
            if (link->getLinkKind() != slk::Raw) {
                unresolved[box].push_back(UnresolvedLink{
                    .link = arg.as<sem::Link>(),
                    .description //
                    = link->description
                        ? std::make_optional(link->description->asOrg())
                        : std::nullopt});
            }
        }
    };

    if (NestedNodes.contains(n->getKind())) {
        if (isLinkedDescriptionItem(n)) {
            auto desc = n.as<sem::ListItem>();
            for (auto const& head : desc->header.value()->subnodes) {
                if (head->is(osk::Link)) {
                    auto link = head.as<sem::Link>();
                    if (link->getLinkKind() != slk::Raw) {
                        auto description = sem::SemId<
                            sem::StmtList>::New();
                        description->subnodes = n->subnodes;
                        unresolved[box].push_back(UnresolvedLink{
                            .link        = link,
                            .description = description,
                        });
                    }
                }
            }
        }
    } else {
        sem::eachSubnodeRec(n, register_used_links);
    }

    VDesc v = addVertex(box);

    switch (n->getKind()) {
        case osk::Subtree: {
            g[v].kind = OrgGraphNode::Kind::Subtree;
            break;
        }

        case osk::AnnotatedParagraph: {
            if (n.as<sem::AnnotatedParagraph>()->getAnnotationKind()
                == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
                g[v].kind = OrgGraphNode::Kind::Footnote;
            } else {
                g[v].kind = OrgGraphNode::Kind::Paragraph;
            }
            break;
        }

        case osk::Paragraph: {
            g[v].kind = OrgGraphNode::Kind::Paragraph;
            break;
        }

        case osk::Document: {
            g[v].kind = OrgGraphNode::Kind::Document;
            break;
        }

        case osk::List: {
            g[v].kind = OrgGraphNode::Kind::List;
            break;
        }

        case osk::ListItem: {
            g[v].kind = OrgGraphNode::Kind::ListItem;
            break;
        }

        default: {
        }
    }


    updateUnresolved(v);
}

void OrgGraph::updateUnresolved(VDesc) {
    for (auto const& id : unresolved.keys()) {
        auto add_edge = [&](CR<OrgGraphEdge> spec, CVec<OrgBoxId> target) {
            for (auto const& box : target) {
                auto e = addEdge(getBoxDesc(id), getBoxDesc(box));
                g[e]   = spec;
            }
        };

        Vec<int> resolved;
        auto&    unresolved_list = unresolved[id];
        for (auto const& it : enumerator(unresolved_list)) {
            bool        found_match = false;
            auto const& link        = it.value().link;


            switch (link->getLinkKind()) {
                case slk::Id: {
                    if (auto target = subtreeIds.get(link->getId().text)) {
                        found_match = true;
                        add_edge(
                            OrgGraphEdge{
                                .kind = OrgGraphEdge::Kind::SubtreeId,
                                .description = it.value().description,
                            },
                            *target);
                    }
                    break;
                }

                case slk::Footnote: {
                    if (auto target = footnoteTargets.get(
                            link->getFootnote().target)) {
                        found_match = true;
                        add_edge(
                            OrgGraphEdge{
                                .kind = OrgGraphEdge::Kind::Footnote,
                                .description = it.value().description,
                            },
                            *target);
                    }
                    break;
                }

                default: {
                }
            }

            if (found_match) { resolved.push_back(it.index()); }
        }

        rs::reverse(resolved);
        for (auto const& it : resolved) {
            unresolved_list.erase(unresolved_list.begin() + it);
        }

        if (unresolved_list.empty()) { unresolved.erase(id); }
    }
}

std::string OrgGraph::toGraphviz() {
    std::stringstream         os;
    boost::dynamic_properties dp;

    dp //
        .property("node_id", get(boost::vertex_index, g))
        .property(
            "splines",
            boost::make_constant_property<Graph*>(std::string("polyline")))
        .property(
            "shape",
            boost::make_constant_property<Graph::vertex_descriptor>(
                std::string("rect")))
        .property(
            "description",
            make_transform_value_property_map<std::string>(
                [&](OrgGraphEdge const& prop) -> std::string {
                    return prop.description ? ExporterUltraplain::toStr(
                                                  prop.description.value())
                                            : "";
                },
                get(boost::edge_bundle, g)))
        .property(
            "label",
            make_transform_value_property_map<std::string>(
                [&](OrgGraphNode const& prop) -> std::string {
                    return fmt(
                        "{}-{} [{}]",
                        prop.box,
                        prop.kind,
                        store->getOrgTree(prop.box)->selfPath());
                },
                get(boost::vertex_bundle, g)));


    write_graphviz_dp(os, g, dp);

    return os.str();
}

QString OrgGraph::getDisplayText(CR<QModelIndex> index) const {
    sem::SemId<sem::Org> display;
    if (isNode(index)) {
        display = store->node(getBox(index.row()));
        switch (display->getKind()) {
            case osk::Document: {
                if (auto title = display.as<sem::Document>()->title) {
                    display = title->asOrg();
                } else {
                    display = display.Nil();
                }
                break;
            }
            case osk::Subtree: {
                display = display.as<sem::Subtree>()->title;
                break;
            }
            default:
        }
    } else {
        auto edge = this->getEdgeProp(getEdgeDesc(index));
        if (edge.description) { display = edge.description.value(); }
    }

    if (display.isNil()) {
        return QString("");
    } else {
        ExporterHtml exp;
        exp.newlineToSpace = true;
        auto html_tree     = exp.evalTop(display);

        QTextDocument result;
        return QString::fromStdString(exp.store.toString(html_tree));
    }
}

QVariant OrgGraph::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || rowCount() <= index.row()) {
        return QVariant();
    }

    switch (role) {
        case (int)SharedModelRoles::IndexBox: {
            return isNode(index) ? QVariant::fromValue(getBox(index.row()))
                                 : QVariant();
        }

        case (int)OrgGraphRoles::DebugDisplay: {
            return QVariant();
        }

        case (int)OrgGraphRoles::SubnodeIndices: {
            if (isNode(index)) {
                QList<QModelIndex> result;
                OrgTreeNode* node = store->getOrgTree(getBox(index.row()));
                Q_ASSERT_X(
                    node != nullptr,
                    "data for subnode indices",
                    qdebug_to_str(index));
                for (auto const& it : enumerator(node->subnodes)) {
                    // Not all node boxes are directly mapped to the graph
                    // vertices -- description lists are filtered into edge
                    // properties.
                    if (!isLinkedDescriptionItem(
                            store, it.value()->boxId)) {
                        result.push_back(this->index(
                            getDescIndex(getBoxDesc(it.value()->boxId))));
                    }
                }

                return QVariant::fromValue(result);
            } else {
                return QVariant();
            }
        }

        case (int)OrgGraphRoles::EdgeDesc: {
            return isNode(index) ? QVariant()
                                 : QVariant::fromValue(getEdgeDesc(index));
        }

        case (int)OrgGraphRoles::NodeDesc: {
            return isNode(index) ? QVariant::fromValue(getNodeDesc(index))
                                 : QVariant();
        }

        case (int)OrgGraphRoles::SourceAndTarget: {
            return isNode(index)
                     ? QVariant()
                     : QVariant::fromValue(sourceTargetAt(index));
        }

        case Qt::DisplayRole: {
            return getDisplayText(index);
        }

        case (int)OrgGraphRoles::IsNode: {
            return isNode(index);
        }

        default: {
            return QVariant();
        }
    }
}


OrgGraphLayoutProxy::FullLayout OrgGraphLayoutProxy::getFullLayout()
    const {
    GraphLayoutIR ir;
    auto          src = sourceModel();
    using V           = OrgGraph::VDesc;

    UnorderedMap<V, int> nodeToRect;

    for (int row = 0; row < src->rowCount(); ++row) {
        QModelIndex index = src->index(row, 0);
        if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
            auto desc = qindex_get<V>(index, OrgGraphRoles::NodeDesc);
            nodeToRect[desc] = ir.rectangles.size();
            auto size        = config.getNodeSize(index);
            ir.rectangles.push_back(
                QRect(0, 0, size.width(), size.height()));
        } else {
            auto [source, target] = qindex_get<Pair<V, V>>(
                index, OrgGraphRoles::SourceAndTarget);
            ir.edges.push_back(
                {nodeToRect.at(source), nodeToRect.at(target)});
        }
    }

    if (config.clusterSubtrees) {
        Func<Opt<GraphLayoutIR::Subgraph>(QModelIndex const&)> rec_cluster;

        rec_cluster =
            [&](QModelIndex const& index) -> Opt<GraphLayoutIR::Subgraph> {
            OrgGraphIndex        cluster_index{index};
            sem::SemId<sem::Org> node = store->node(
                cluster_index.getBox());

            if (node->is(osk::Subtree)) {
                GraphLayoutIR::Subgraph result;
                for (auto const& i : cluster_index.getSubnodes()) {
                    OrgGraphIndex sub{i};
                    auto          sub_node = store->node(sub.getBox());
                    auto          sub_desc = sub.getVDesc();

                    if (sub_node->is(osk::Subtree)) {
                        if (auto sub_cluster = rec_cluster(sub)) {
                            result.subgraphs.push_back(
                                sub_cluster.value());
                        }

                    } else {
                        // Not all subtrees for an entry are guaranted to
                        // be represented in the cluster - nodes can be
                        // filtered prior to layout.
                        if (nodeToRect.contains(sub_desc)) {
                            result.nodes.push_back(
                                nodeToRect.at(sub_desc));
                        }
                    }
                }

                if (result.isEmpty()) {
                    return std::nullopt;
                } else {
                    result.nodes.push_back(
                        nodeToRect.at(cluster_index.getVDesc()));
                    return result;
                }

            } else {
                return std::nullopt;
            }
        };

        for (int row = 0; row < src->rowCount(); ++row) {
            QModelIndex   i = src->index(row, 0);
            OrgGraphIndex index{i};
            if (index.isNode()) {
                if (auto node = store->node(index.getBox());
                    node->is(osk::Subtree)
                    && node.as<sem::Subtree>()->level == 1) {
                    if (auto sub = rec_cluster(i)) {
                        ir.subgraphs.push_back(*sub);
                    }
                }
            }
        }
    }


    Graphviz   gvc;
    FullLayout res;
    auto       lyt = ir.doGraphvizLayout(gvc);
    res.original   = lyt;

    lyt.writeSvg("/tmp/testQtGraphSceneFullMindMap_post_cluster.svg");
    lyt.writeXDot("/tmp/testQtGraphSceneFullMindMap_post_cluster.xdot");

    auto conv_lyt = lyt.convert();
    res.bbox      = conv_lyt.bbox;

    for (int row = 0; row < sourceModel()->rowCount(); ++row) {
        QModelIndex index = src->index(row, 0);
        if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
            res.data[row] = ElementLayout{
                .data = conv_lyt.fixed.at(nodeToRect.at(
                    qindex_get<V>(index, OrgGraphRoles::NodeDesc)))};
        } else {
            auto [source, target] = qindex_get<Pair<V, V>>(
                index, OrgGraphRoles::SourceAndTarget);
            res.data[row] = ElementLayout{conv_lyt.lines.at({
                nodeToRect.at(source),
                nodeToRect.at(target),
            })};
        }
    }


    return res;
}

QVariant OrgGraphLayoutProxy::data(const QModelIndex& index, int role)
    const {
    switch (role) {
        case LayoutBBoxRole: {
            return QVariant::fromValue(currentLayout.bbox);
        }

        case (int)OrgGraphRoles::NodeShape: {
            if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
                return QVariant::fromValue(getElement(index).getNode());
            } else {
                return QVariant();
            }
        }

        case (int)OrgGraphRoles::EdgeShape: {
            if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
                return QVariant();
            } else {
                return QVariant::fromValue(getElement(index).getEdge());
            }
        }

        default: {
            Q_ASSERT(sourceModel() != nullptr);
            return mapToSource(index).data(role);
        }
    }
}
