#include <editor/editor_lib/mind_map/org_graph_model.hpp>

using namespace org::mind_map;

GraphLayoutProxy::FullLayout GraphLayoutProxy::getFullLayout() const {
    GraphLayoutIR ir;
    auto          src = sourceModel();
    using V           = VDesc;

    UnorderedMap<V, int> nodeToRect;

    // Build IR content for edges and nodes
    for (int row = 0; row < src->rowCount(); ++row) {
        QModelIndex gi = src->index(row, 0);
        GraphIndex  index{gi};
        // _qfmt(
        //     "row:{} index:{} src-row-count:{} debug:{}",
        //     row,
        //     qdebug_to_str(gi),
        //     src->rowCount(),
        //     index.debug());

        if (index.isNode()) {
            nodeToRect[index.getVDesc()] = ir.rectangles.size();
            auto size                    = config.getNodeSize(gi);
            ir.rectangles.push_back(
                GraphSize(size.width(), size.height()));
        } else {
            auto [source, target] = index.getSourceTarget();

            auto ir_edge = GraphEdge{
                .source = nodeToRect.at(source),
                .target = nodeToRect.at(target),
            };

            ir.edges.push_back(ir_edge);

            if (auto str = index.getDisplay(); !str.isEmpty()) {
                auto size              = config.getEdgeLabelSize(gi);
                ir.edgeLabels[ir_edge] = GraphSize(
                    size.width(), size.height());
            }
        }
    }

    if (config.clusterSubtrees) {
        Func<Opt<GraphLayoutIR::Subgraph>(QModelIndex const&)> rec_cluster;

        // Recursively iterate over sub-nodes and build IR clusters
        rec_cluster =
            [&](QModelIndex const& index) -> Opt<GraphLayoutIR::Subgraph> {
            GraphIndex           cluster_index{index};
            sem::SemId<sem::Org> node = store->getBoxedNode(
                cluster_index.getBox());

            if (node->is(osk::Subtree)) {
                GraphLayoutIR::Subgraph          result;
                Func<void(QModelIndex const& i)> rec_nodes;

                // Recurse over subtree elements -- lists and list items do
                // not form own clusters and are not visible in the tree,
                // but they contain paragraph elements internally, which
                // should be visible.
                rec_nodes = [&](QModelIndex const& i) {
                    GraphIndex sub{i};
                    auto sub_node = store->getBoxedNode(sub.getBox());
                    auto sub_desc = sub.getVDesc();

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

                    } else {
                        if (nodeToRect.contains(sub_desc)) {
                            // Not all subtrees for an entry are guaranted
                            // to be represented in the cluster - nodes can
                            // be filtered prior to layout. List and list
                            // items are not added in the graph, handled
                            // below.
                            result.nodes.push_back(
                                nodeToRect.at(sub_desc));
                        }
                        if (SemSet{osk::List, osk::ListItem}.contains(
                                sub_node->getKind())) {
                            for (auto const& list_element :
                                 sub.getSubnodes()) {
                                rec_nodes(list_element);
                            }
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
            QModelIndex i = src->index(row, 0);
            GraphIndex  index{i};
            if (index.isNode()) {
                if (auto node = store->getBoxedNode(index.getBox());
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
    PERF_MMAP_BEGIN("doGraphvizLayout");
    auto lyt = ir.doGraphvizLayout(gvc, config.graphvizLayout);
    PERF_MMAP_END();

    res.original  = lyt;
    auto conv_lyt = lyt.convert();

    res.bbox = toQRect(conv_lyt.bbox);
    // drop all the content from the layout and set the size from the
    // expected computed layout.
    res.data.clear();
    res.data.resize(
        conv_lyt.fixed.size() + conv_lyt.lines.size()
            + conv_lyt.subgraphPaths.size(),
        ElementLayout{std::monostate{}});

    /// Fill in the node+edge indices from the source model.
    for (int row = 0; row < sourceModel()->rowCount(); ++row) {
        QModelIndex index = src->index(row, 0);
        GraphIndex  gi{index};
        if (gi.isNode()) {
            res.data.at(row) = ElementLayout{
                .data = toQRect(
                    conv_lyt.fixed.at(nodeToRect.at(gi.getVDesc()))),
            };
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
                .bbox = toQRect(conv_lyt.getSubgraph(it.value()).bbox),
            }};
    }


    return res;
}

QVariant GraphLayoutProxy::data(const QModelIndex& index, int role) const {
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
        if (false) {
            Q_ASSERT_X(
                index.row() < sourceModel()->rowCount(),
                "data",
                fmt("additional data rows are created by the proxymodel. "
                    "Index {} has a non-subgraph kind",
                    qdebug_to_str(index)));
        }

        switch (role) {
            case (int)Role::LayoutBBoxRole: {
                return QVariant::fromValue(currentLayout.bbox);
            }

            case (int)OrgGraphRoles::NodeShape: {
                if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
                    return QVariant::fromValue(
                        getElement(index).getNode());
                } else {
                    // _qfmt(
                    //     "index:{} does not provide role:NodeShape",
                    //     index);
                    return QVariant();
                }
            }

            case (int)OrgGraphRoles::EdgeShape: {
                if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
                    // _qfmt(
                    //     "index:{} does not provide role:EdgeShape",
                    //     index);
                    return QVariant();
                } else {
                    return QVariant::fromValue(
                        getElement(index).getEdge());
                }
            }

            default: {
                Q_ASSERT(sourceModel() != nullptr);
                Q_ASSERT(index.isValid());
                Q_ASSERT(index.internalPointer() != nullptr);
                auto mapped = mapToSource(index);
                Q_ASSERT(mapped.isValid());
                return mapped.data(role);
            }
        }
    }
}
