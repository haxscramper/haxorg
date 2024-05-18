#include "qtextoption.h"
#include <editor/editor_lib/mind_map/org_graph_model.hpp>
#include <editor/editor_lib/common/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <boost/graph/graphviz.hpp>
#include <QDebug>
#include <exporters/ExporterUltraplain.hpp>
#include <editor/editor_lib/document/org_document_render.hpp>
#include <editor/editor_lib/store/org_exporter_html.hpp>
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

void OrgGraph::insertNewNode(CR<OrgBoxId> box) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
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
        // Description lists with links in header are attached as the
        // outgoing link to the parent subtree. It is the only supported
        // way to provide an extensive label between subtree edges.
        if (isLinkedDescriptionItem(n)) {
            auto desc = n.as<sem::ListItem>();
            for (auto const& head : desc->header.value()->subnodes) {
                // Description list header might contain non-link elements.
                // These are ignored in the mind map.
                if (head->is(osk::Link)) {
                    auto link = head.as<sem::Link>();
                    if (link->getLinkKind() != slk::Raw) {
                        auto description = sem::SemId<
                            sem::StmtList>::New();
                        description->subnodes = n->subnodes;
                        auto parent_subtree   = store->parent(box).value();
                        while (!store->node(parent_subtree)
                                    ->is(osk::Subtree)) {
                            parent_subtree = store->parent(parent_subtree)
                                                 .value();
                        }

                        unresolved[parent_subtree].push_back(
                            UnresolvedLink{
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
}

void OrgGraph::deleteBox(CR<OrgBoxId> deleted) {
    sem::SemId<sem::Org> n    = store->node(deleted);
    auto                 desc = boxToVertex.at(deleted);

    // Find all incoming links targeting this node and return them in
    // unresolved state
    for (EDesc link : in_edges(desc)) {
        this->unresolved[g[getEdgeSource(link)].box].push_back(
            UnresolvedLink{
                .description = g[link].description,
                .link        = g[link].link,
            });
    }

    // Mirror the state drop from the node box addition
    if (auto tree = n.asOpt<sem::Subtree>()) {
        if (tree->treeId) { this->subtreeIds.erase(*tree->treeId); }
    } else if (auto par = n.asOpt<sem::AnnotatedParagraph>()) {
        if (par->getAnnotationKind()
            == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
            this->footnoteTargets.erase(par->getFootnote().name);
        }
    }

    removeVertex(desc);
}

OrgGraph::ResolveResult OrgGraph::updateUnresolved(
    OrgBoxId             unresolved_source,
    CVec<UnresolvedLink> missing_links) const {
    OrgGraph::ResolveResult result;
    auto add_edge = [&](CR<OrgGraphEdge> spec, CVec<OrgBoxId> target) {
        for (auto const& box : target) {
            result.establishedEdges.push_back({
                .source = getBoxDesc(unresolved_source),
                .target = getBoxDesc(box),
                .spec   = spec,
            });
        }
    };

    for (auto const& it : enumerator(missing_links)) {
        bool        found_match = false;
        auto const& link        = it.value().link;


        switch (link->getLinkKind()) {
            case slk::Id: {
                if (auto target = subtreeIds.get(link->getId().text)) {
                    found_match = true;
                    add_edge(
                        OrgGraphEdge{
                            .kind        = OrgGraphEdge::Kind::SubtreeId,
                            .description = it.value().description,
                            .link        = link,
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
                            .kind        = OrgGraphEdge::Kind::Footnote,
                            .description = it.value().description,
                            .link        = link,
                        },
                        *target);
                }
                break;
            }

            default: {
            }
        }

        if (!found_match) { result.missingLinks.push_back(it.value()); }
    }

    return result;
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

        case (int)OrgGraphRoles::ElementKind: {
            return QVariant::fromValue(
                isNode(index) ? OrgGraphElementKind::Node
                              : OrgGraphElementKind::Edge);
        }

        case (int)OrgGraphRoles::IsNode: {
            return isNode(index);
        }

        default: {
            return QVariant();
        }
    }
}

void OrgGraph::removeVertex(VDesc vertex) {
    auto it = std::find(nodes.begin(), nodes.end(), vertex);
    if (it != nodes.end()) {
        int index = std::distance(nodes.begin(), it);
        beginRemoveRows(QModelIndex(), index, index);

        _qdbg(in_edges(vertex).size(), out_edges(vertex).size());

        for (auto const& edge : in_edges(vertex)) {
            emit edgeRemoved(edge);
        }

        for (auto const& edge : out_edges(vertex)) {
            emit edgeRemoved(edge);
        }

        boost::clear_vertex(*it, g);
        boost::remove_vertex(*it, g);

        nodes.erase(it);

        rebuildEdges();
        endRemoveRows();
    }
    emit nodeRemoved(vertex);
}


OrgGraphLayoutProxy::FullLayout OrgGraphLayoutProxy::getFullLayout()
    const {
    GraphLayoutIR ir;
    auto          src = sourceModel();
    using V           = OrgGraph::VDesc;

    UnorderedMap<V, int> nodeToRect;

    // Build IR content for edges and nodes
    for (int row = 0; row < src->rowCount(); ++row) {
        QModelIndex   gi = src->index(row, 0);
        OrgGraphIndex index{gi};
        if (index.isNode()) {
            nodeToRect[index.getVDesc()] = ir.rectangles.size();
            auto size                    = config.getNodeSize(gi);
            ir.rectangles.push_back(QSize(size.width(), size.height()));
        } else {
            auto [source, target] = index.getSourceTarget();
            auto ir_edge          = std::make_pair(
                nodeToRect.at(source), nodeToRect.at(target));
            ir.edges.push_back(ir_edge);

            if (auto str = index.getDisplay(); !str.isEmpty()) {
                ir.edgeLabels[ir_edge] = config.getEdgeLabelSize(gi);
            }
        }
    }

    if (config.clusterSubtrees) {
        Func<Opt<GraphLayoutIR::Subgraph>(QModelIndex const&)> rec_cluster;

        // Recursively iterate over sub-nodes and build IR clusters
        rec_cluster =
            [&](QModelIndex const& index) -> Opt<GraphLayoutIR::Subgraph> {
            OrgGraphIndex        cluster_index{index};
            sem::SemId<sem::Org> node = store->node(
                cluster_index.getBox());

            if (node->is(osk::Subtree)) {
                GraphLayoutIR::Subgraph          result;
                Func<void(QModelIndex const& i)> rec_nodes;

                // Recurse over subtree elements -- lists and list items do
                // not form own clusters and are not visible in the tree,
                // but they contain paragraph elements internally, which
                // should be visible.
                rec_nodes = [&](QModelIndex const& i) {
                    OrgGraphIndex sub{i};
                    auto          sub_node = store->node(sub.getBox());
                    auto          sub_desc = sub.getVDesc();

                    if (sub_node->is(osk::Subtree)) {
                        if (auto sub_cluster = rec_cluster(sub)) {
                            result.subgraphs.push_back(
                                sub_cluster.value());
                        } else {
                            // Subtree can form an empty cluster if it has
                            // no elements of its own. This branch handles
                            // the
                            //
                            // ```
                            // * Top subtree
                            // ** Nested subtree 1
                            // ** Nested subtree 2
                            // ** Nested 3
                            //
                            // Actual content
                            // ```
                            //
                            // All subtrees need to go under the 'Top
                            // Subtree' cluster. Tree 1 and Tree 2 fall
                            // into this branch.
                            result.nodes.push_back(
                                nodeToRect.at(sub_desc));
                        }

                    } else if (nodeToRect.contains(sub_desc)) {
                        // Not all subtrees for an entry are guaranted to
                        // be represented in the cluster - nodes can be
                        // filtered prior to layout. List and list items
                        // are not added in the graph, handled below.
                        result.nodes.push_back(nodeToRect.at(sub_desc));
                    } else if (SemSet{osk::List, osk::ListItem}.contains(
                                   sub_node->getKind())) {
                        for (auto const& list_element :
                             sub.getSubnodes()) {
                            rec_nodes(list_element);
                        }
                    }
                };

                for (auto const& cluster_element :
                     cluster_index.getSubnodes()) {
                    rec_nodes(cluster_element);
                }

                if (result.isEmpty()) {
                    return std::nullopt;
                } else {
                    if (config.getSubgraphMargin) {
                        result.internalMargin = config.getSubgraphMargin
                                                    .value()(index);
                    }

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
    if (true) {
        lyt.writeSvg("/tmp/testQtGraphSceneFullMindMap.svg");
        lyt.writeXDot("/tmp/testQtGraphSceneFullMindMap.xdot");
    }
    res.original  = lyt;
    auto conv_lyt = lyt.convert();
    res.bbox      = conv_lyt.bbox;
    // drop all the content from the layout and set the size from the
    // expected computed layout.
    res.data.clear();
    res.data.resize(
        conv_lyt.fixed.size() + conv_lyt.lines.size()
            + conv_lyt.subgraphPaths.size(),
        ElementLayout{std::monostate{}});

    /// Fill in the node+edge indices from the source model.
    for (int row = 0; row < sourceModel()->rowCount(); ++row) {
        QModelIndex   index = src->index(row, 0);
        OrgGraphIndex gi{index};
        if (gi.isNode()) {
            res.data.at(row) = ElementLayout{
                .data = conv_lyt.fixed.at(nodeToRect.at(gi.getVDesc()))};
        } else {
            auto [source, target] = gi.getSourceTarget();
            res.data.at(row)      = ElementLayout{conv_lyt.lines.at({
                nodeToRect.at(source),
                nodeToRect.at(target),
            })};
        }
    }

    // Top off the [node..., edge...] list with the clusters provided by
    // the layout content.
    for (auto const& it : enumerator(conv_lyt.subgraphPaths)) {
        int row = sourceModel()->rowCount() + it.index();
        Q_ASSERT(
            std::holds_alternative<std::monostate>(res.data.at(row).data));
        res.data.at(row) = ElementLayout{
            .data = Subgraph{
                .bbox = conv_lyt.getSubgraph(it.value()).bbox,
            }};
    }


    return res;
}

QVariant OrgGraphLayoutProxy::data(const QModelIndex& index, int role)
    const {
    auto const& e = getElement(index);

    if (role == (int)OrgGraphRoles::ElementKind) {
        return QVariant::fromValue(e.getKind());
    }

    if (e.getKind() == OrgGraphElementKind::Subgraph) {
        switch (role) {
            case (int)Role::Subgraph: {
                return QVariant::fromValue(e.getSubgraph());
            }
            default: {
                auto err = model_role_not_implemented::init(
                    fmt("Subgraph element for layout proxy does not "
                        "implement {}",
                        roleNames().value(role).toStdString()));
                return QVariant();
            }
        }
    } else {
        Q_ASSERT_X(
            index.row() < sourceModel()->rowCount(),
            "data",
            fmt("additional data rows are created by the proxymodel. "
                "Index {} has a non-subgraph kind",
                qdebug_to_str(index)));

        switch (role) {
            case (int)Role::LayoutBBoxRole: {
                return QVariant::fromValue(currentLayout.bbox);
            }

            case (int)OrgGraphRoles::NodeShape: {
                if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
                    return QVariant::fromValue(
                        getElement(index).getNode());
                } else {
                    return QVariant();
                }
            }

            case (int)OrgGraphRoles::EdgeShape: {
                if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
                    return QVariant();
                } else {
                    return QVariant::fromValue(
                        getElement(index).getEdge());
                }
            }

            default: {
                Q_ASSERT(sourceModel() != nullptr);
                return mapToSource(index).data(role);
            }
        }
    }
}
