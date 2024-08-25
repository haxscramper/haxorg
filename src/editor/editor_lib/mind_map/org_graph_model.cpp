#include "qtextoption.h"
#include <editor/editor_lib/mind_map/org_graph_model.hpp>
#include <editor/editor_lib/common/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <boost/graph/graphviz.hpp>
#include <QDebug>
#include <haxorg/exporters/ExporterUltraplain.hpp>
#include <editor/editor_lib/document/org_document_render.hpp>
#include <editor/editor_lib/store/org_exporter_html.hpp>
#include <hstd/stdlib/Set.hpp>
#include <haxorg/exporters/exportertree.hpp>

#pragma clang diagnostic error "-Wswitch"

using slk = sem::Link::Kind;
using namespace org::mind_map;

bool isLinkedDescriptionItem(sem::OrgArg n) {
    return n->is(osk::ListItem)
        && n.as<sem::ListItem>()->isDescriptionItem()
        && rs::any_of(
               n.as<sem::ListItem>()->header.value(),
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
        store->getOrgTree(box)->getParentChain(/*withSelf = */ false),
        [](OrgTreeNode* parent) -> bool {
            return isLinkedDescriptionItem(parent->getBoxedNode());
        });
}

/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(OrgStore* store, CR<OrgBoxId> box) {
    return store->getBoxedNode(box)->is(osk::List)
        && rs::any_of(
               store->getBoxedNode(box)->subnodes,
               [](sem::OrgArg arg) -> bool {
                   return isLinkedDescriptionItem(arg);
               });
}

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInLinkedDescriptionList(OrgStore* store, CR<OrgBoxId> box) {
    return rs::any_of(
        store->getOrgTree(box)->getParentChain(), [](OrgTreeNode* tree) {
            return isLinkedDescriptionItem(tree->getBoxedNode());
        });
}

bool isMmapIgnored(OrgStore* store, CR<OrgBoxId> box) {
    return isInLinkedDescriptionList(store, box)
        || isLinkedDescriptionList(store, box);
}

Opt<OrgGraphNode> Graph::getNodeInsert(CR<OrgBoxId> box) const {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    if (isMmapIgnored(store, box)) { return std::nullopt; }

    if (state.debug) {
        _qfmt(
            "box:{} desc-item:{} desc-list:{} ID:{}",
            box,
            isLinkedDescriptionItem(store, box),
            isLinkedDescriptionList(store, box),
            store->getBoxedNode(box)->original.id);
    }

    OrgGraphNode result{.box = box};

    sem::SemId<sem::Org> node = store->getBoxedNode(box);
    if (auto tree = node.asOpt<sem::Subtree>()) {
        if (tree->treeId) { result.subtreeId = tree->treeId.value(); }
    } else if (auto par = node.asOpt<sem::AnnotatedParagraph>()) {
        if (par->getAnnotationKind()
            == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
            result.footnoteName = par->getFootnote().name;
        }
    }

    auto register_used_links = [&](sem::OrgArg arg) {
        Q_ASSERT(!arg.isNil());
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (arg->is(osk::Link)) {
            auto link = arg.as<sem::Link>();
            if (link->getLinkKind() != slk::Raw) {
                result.unresolved.push_back(GraphLink{
                    .link = arg.as<sem::Link>(),
                    .description //
                    = link->description
                        ? std::make_optional(link->description->asOrg())
                        : std::nullopt,
                });
            }
        }
    };

    if (auto tree = node.asOpt<sem::Subtree>()) {
        // Description lists with links in header are attached as the
        // outgoing link to the parent subtree. It is the only supported
        // way to provide an extensive label between subtree edges.
        for (auto const& list : tree.subAs<sem::List>()) {
            for (auto const& item : list.subAs<sem::ListItem>()) {
                if (isLinkedDescriptionItem(item.asOrg())) {
                    for (auto const& link :
                         item->header->subAs<sem::Link>()) {
                        // Description list header might contain
                        // non-link elements. These are ignored in the
                        // mind map.
                        if (link->getLinkKind() != slk::Raw) {
                            auto description = sem::SemId<
                                sem::StmtList>::New();
                            description->subnodes = item->subnodes;
                            Q_ASSERT(!link.isNil());
                            result.unresolved.push_back(GraphLink{
                                .link        = link,
                                .description = description,
                            });
                        }
                    }
                }
            }
        }
    } else if (!NestedNodes.contains(node->getKind())) {
        sem::eachSubnodeRec(node, register_used_links);
    }

    switch (node->getKind()) {
        case osk::Subtree: {
            result.kind = OrgGraphNode::Kind::Subtree;
            break;
        }

        case osk::AnnotatedParagraph: {
            if (node.as<sem::AnnotatedParagraph>()->getAnnotationKind()
                == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
                result.kind = OrgGraphNode::Kind::Footnote;
            } else {
                result.kind = OrgGraphNode::Kind::Paragraph;
            }
            break;
        }

        case osk::Paragraph: {
            result.kind = OrgGraphNode::Kind::Paragraph;
            break;
        }

        case osk::Document: {
            result.kind = OrgGraphNode::Kind::Document;
            break;
        }

        case osk::List: {
            result.kind = OrgGraphNode::Kind::List;
            break;
        }

        case osk::ListItem: {
            result.kind = OrgGraphNode::Kind::ListItem;
            break;
        }

        default: {
        }
    }

    if (state.debug) {
        _qfmt("box:{} unresolved:{}", box, result.unresolved);
    }

    return result;
}

void Graph::emitChanges(CR<GraphStructureUpdate> upd) {
    if (state.debug) { _qfmt("upd:{}", upd); }

    Q_ASSERT(
        state.nodes.size() + (upd.added_node ? 1 : 0)
            - (upd.removed_node ? 1 : 0)
        == boost::num_vertices(state.g));

    Q_ASSERT(
        state.edges.size() + (upd.added_edges.size())
            - (upd.removed_edges.size())
        == boost::num_edges(state.g));

    for (auto const& e : upd.added_edges) { emit edgeAdded(e); }
    for (auto const& e : upd.removed_edges) { emit edgeRemoved(e); }
    if (upd.added_node) { emit nodeAdded(upd.added_node.value()); }
    if (upd.removed_node) { emit nodeRemoved(upd.removed_node.value()); }

    Vec<int> removed_edge_indices //
        = upd.removed_edges       //
        | rv::transform([&](EDesc const& e) -> int {
              int result = state.edges.indexOf(e);
              Q_ASSERT(result != -1);
              return result;
          })
        | rs::to<Vec>();

    rs::actions::sort(removed_edge_indices);
    rs::actions::reverse(removed_edge_indices);
    int const base_node_count = state.nodes.size();
    for (int idx : removed_edge_indices) {
        if (state.debug) { _qfmt("remove edge at index:{}", idx); }
        beginRemoveRows(
            QModelIndex(), base_node_count + idx, base_node_count + idx);
        state.edges.erase(state.edges.begin() + idx);
        endRemoveRows();
    }

    if (upd.removed_node) {
        int idx = state.nodes.indexOf(*upd.removed_node);
        if (state.debug) { _qfmt("remove node at index:{}", idx); }
        Q_ASSERT(idx != -1);
        beginRemoveRows(QModelIndex(), idx, idx);
        state.nodes.erase(state.nodes.begin() + idx);
        endRemoveRows();
    }

    if (upd.added_node) {
        int row = state.nodes.size();
        if (state.debug) { _qfmt("add node at index:{}", row); }
        state.nodes.push_back(*upd.added_node);
        beginInsertRows(QModelIndex(), row, row);
        endInsertRows();
    }

    if (!upd.added_edges.empty()) {
        int base_size = state.nodes.size() + state.edges.size();
        int max_edge  = base_size + upd.added_edges.size() - 1;
        if (state.debug) {
            _qfmt("add edge at index:{}-{}", base_size, max_edge);
        }
        beginInsertRows(QModelIndex(), base_size, max_edge);
        state.edges.append(upd.added_edges);
        endInsertRows();
    }

    Q_ASSERT(state.nodes.size() == boost::num_vertices(state.g));
    Q_ASSERT(state.edges.size() == boost::num_edges(state.g));
    if (state.debug) {
        _qfmt(
            "nodes:{}/{} edges:{}/{} boost-nodes:{} boost-edges:{} "
            "row-count:{}",
            state.nodes,
            state.nodes.size(),
            state.edges,
            state.edges.size(),
            boost::num_vertices(state.g),
            boost::num_edges(state.g),
            rowCount());
    }
}

Graph::ResolveResult Graph::State::getUnresolvedEdits(
    CR<OrgGraphNode> edit) const {
    Graph::ResolveResult result;
    result.node = edit;
    result.node.unresolved.clear();
    Q_ASSERT_X(
        !unresolved.contains(edit.box),
        "get unresolved",
        fmt("Node edit has with unresolved elements is already listed as "
            "unresolved node: box is {}",
            edit.box));

    if (debug) { _qfmt("unresolved:{}", unresolved); }

    for (auto const& it : edit.unresolved) {
        Opt<ResolvedLink> resolved_edit = getResolveTarget(edit.box, it);
        if (resolved_edit) {
            if (debug) { _qfmt("resolved:{}", *resolved_edit); }
            result.resolved.push_back(*resolved_edit);
        } else {
            result.node.unresolved.push_back(it);
        }
    }

    for (auto const& it : unresolved) {
        Q_ASSERT(it != edit.box);
        for (auto const& link : g[boxToVertex.at(it)].unresolved) {
            Opt<ResolvedLink> resolved_edit = getResolveTarget(it, link);
            if (resolved_edit) {
                if (debug) {
                    _qfmt(
                        "resolved:{} it:{} edit:{}",
                        *resolved_edit,
                        it,
                        edit.box);
                }
                result.resolved.push_back(*resolved_edit);
            }
        }
    }

    if (debug) {
        _qfmt(
            "box:{} resolved:{} unresolved:{}",
            edit.box,
            result.resolved,
            result.node.unresolved);
    }

    for (auto const& r1 : result.resolved) {
        int count = 0;
        for (auto const& r2 : result.resolved) {
            if (r1.target == r2.target && r1.source == r2.source) {
                ++count;
            }
        }

        Q_ASSERT_X(
            count <= 1,
            "resolved duplicates",
            fmt("Resolved link target contains duplicate edges: {}-{}",
                r1.source,
                r1.target));
    }

    return result;
}

Opt<Graph::ResolvedLink> Graph::State::getResolveTarget(
    CR<OrgBoxId>  source,
    CR<GraphLink> it) const {

    Opt<Graph::ResolvedLink> result;

    if (debug) {
        _qfmt(
            "subtreeIds:{} footnoteTargets:{} source:{} link:{}",
            subtreeIds,
            footnoteTargets,
            source,
            ::debug(it.link.asOrg()));
    }

    auto add_edge = [&](OrgGraphEdge::Kind kind, OrgBoxId target) {
        Q_ASSERT(!it.link.isNil());
        result = ResolvedLink{
            .target = target,
            .link   = it,
            .source = source,
        };
    };

    switch (it.link->getLinkKind()) {
        case slk::Id: {
            if (auto target = subtreeIds.get(it.link->getId().text)) {
                add_edge(OrgGraphEdge::Kind::SubtreeId, *target);
            }
            break;
        }

        case slk::Footnote: {
            if (auto target = footnoteTargets.get(
                    it.link->getFootnote().target)) {
                add_edge(OrgGraphEdge::Kind::Footnote, *target);
            }
            break;
        }

        default: {
        }
    }

    return result;
}

std::string Graph::toGraphviz() {
    std::stringstream         os;
    boost::dynamic_properties dp;

    dp //
        .property(
            "node_id",
            make_transform_value_property_map<std::string>(
                [&](OrgGraphNode const& prop) -> std::string {
                    return fmt("{}", prop.box.value);
                },
                get(boost::vertex_bundle, state.g)))
        .property(
            "splines",
            boost::make_constant_property<BoostBase*>(
                std::string("polyline")))
        .property(
            "shape",
            boost::make_constant_property<BoostBase::vertex_descriptor>(
                std::string("rect")))
        .property(
            "node_dump",
            make_transform_value_property_map<std::string>(
                [&](OrgGraphNode const& prop) -> std::string {
                    return fmt1(prop);
                },
                get(boost::vertex_bundle, state.g)))
        .property(
            "edge_dump",
            make_transform_value_property_map<std::string>(
                [&](OrgGraphEdge const& prop) -> std::string {
                    return fmt1(prop);
                },
                get(boost::edge_bundle, state.g)))
        .property(
            "description",
            make_transform_value_property_map<std::string>(
                [&](OrgGraphEdge const& prop) -> std::string {
                    return prop.link.description
                             ? ExporterUltraplain::toStr(
                                   prop.link.description.value())
                             : "";
                },
                get(boost::edge_bundle, state.g)))
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
                get(boost::vertex_bundle, state.g)));


    write_graphviz_dp(os, state.g, dp);

    return os.str();
}

QString Graph::getDisplayText(CR<QModelIndex> index) const {
    sem::SemId<sem::Org> display;
    if (isNode(index)) {
        display = store->getBoxedNode(getBox(index.row()));
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
        if (edge.link.description) {
            display = edge.link.description.value();
        }
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

QVariant Graph::data(const QModelIndex& index, int role) const {
    if (state.debug) {
        // _qfmt(
        //     "index:{} role:{} name:{}",
        //     qdebug_to_str(index),
        //     role,
        //     roleNames().value(role).toStdString());
    }

    if (role == (int)OrgGraphRoles::DebugDisplay) {
        if (!index.isValid()) {
            return QString::fromStdString(
                fmt("invalid index:{}", qdebug_to_str(index)));
        } else if (rowCount() <= index.row()) {
            return QString::fromStdString(fmt(
                "row count:{}, index row:{}", rowCount(), index.row()));
        } else {
            if (isNode(index)) {
                auto box = getBox(index.row());
                return QString::fromStdString(
                    fmt("row:{} box:{} desc:{} path:{}",
                        index.row(),
                        box,
                        getNodeDesc(index.row()),
                        store->getOrgTree(box)->selfPath()));
            } else {
                auto ed = getEdgeDesc(index);
                return QString::fromStdString(
                    fmt("row:{} box:{}-{} desc:{}",
                        index.row(),
                        getBox(getEdgeSource(ed)),
                        getBox(getEdgeTarget(ed)),
                        ed));
            }
        }
    }

    switch (role) {
        case (int)SharedModelRoles::IndexBox: {
            return isNode(index) ? QVariant::fromValue(getBox(index.row()))
                                 : QVariant();
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
                    if (!isMmapIgnored(store, it.value()->boxId)) {
                        result.push_back(this->index(
                            getDescIndex(getBoxDesc(it.value()->boxId))));
                    }
                }

                return QVariant::fromValue(result);
            } else {
                if (state.debug) {
                    _qfmt(
                        "index:{} does not provide role:SubnodeIndices",
                        index);
                }
                return QVariant();
            }
        }

        case (int)OrgGraphRoles::EdgeDesc: {
            if (isNode(index)) {
                if (state.debug) {
                    _qfmt(
                        "index:{} does not provide role:EdgeDesc", index);
                }
                return QVariant();
            } else {
                return QVariant::fromValue(getEdgeDesc(index));
            }
        }

        case (int)OrgGraphRoles::NodeDesc: {
            if (isNode(index)) {
                return QVariant::fromValue(getNodeDesc(index));
            } else {
                if (state.debug) {
                    _qfmt(
                        "index:{} does not provide role:EdgeDesc", index);
                }
                return QVariant();
            }
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

bool GraphFilterProxy::filterAcceptsRow(
    int                source_row,
    const QModelIndex& source_parent) const {
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    bool valid = sourceModel()->hasIndex(source_row, 0, source_parent);

    bool result{};
    if (valid) {
        if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
            result = accept_node(
                qindex_get<VDesc>(index, OrgGraphRoles::NodeDesc));
        } else {
            auto [source, target] = qindex_get<Pair<VDesc, VDesc>>(
                index, OrgGraphRoles::SourceAndTarget);
            // Avoid dangling edges with missing source/target nodes.
            result = accept_node(source) //
                  && accept_node(target)
                  && accept_edge(qindex_get<EDesc>(
                      index, OrgGraphRoles::EdgeDesc));
        }
    } else {
        result = false;
    }

    // _qfmt(
    //     "row count:{} index:{} valid:{} result:{}",
    //     sourceModel()->rowCount(),
    //     index,
    //     valid,
    //     result);

    return result;
}

void GraphFilterProxy::setSourceModel(QAbstractItemModel* sourceModel) {
    // if (this->sourceModel() != nullptr) {
    //     disconnect(this, nullptr, this->sourceModel(), nullptr);
    // }

    // Q_ASSERT(connect(
    //     sourceModel,
    //     &QAbstractItemModel::layoutChanged,
    //     this,
    //     &QSortFilterProxyModel::invalidate,
    //     Qt::UniqueConnection));


    if (this->sourceModel()) {
        disconnect(this->sourceModel(), nullptr, this, nullptr);
    }

    // _qfmt("set source model:{}", qdebug_to_str(sourceModel));

    QSortFilterProxyModel::setSourceModel(sourceModel);

    if (sourceModel) {
        auto dbg = [this](CR<Str> msg) {
            this->sourceModel()->rowCount();
            this->rowCount();
            // _qfmt(
            //     "msg:{}, source row count:{}, this row count:{}",
            //     msg,
            //     this->sourceModel()->rowCount(),
            //     this->rowCount());
        };

        using M = QAbstractItemModel;

        // connect(this, &M::rowsInserted, this, [dbg]() {
        //     dbg("this rowsInserted");
        // });
        // connect(this, &M::rowsRemoved, this, [dbg]() {
        //     dbg("this rowsRemoved");
        // });
        // connect(this, &M::dataChanged, this, [dbg]() {
        //     dbg("this dataChanged");
        // });
        // connect(this, &M::modelAboutToBeReset, this, [dbg]() {
        //     dbg("this modelAboutToBeReset"); //
        // });
        // connect(this, &M::modelReset, this, [dbg]() {
        //     dbg("this modelReset"); //
        // });
        connect(this, &M::layoutChanged, this, [dbg]() {
            dbg("this layoutChanged"); //
        });

        //

        // connect(sourceModel, &M::rowsInserted, this, [dbg]() {
        //     dbg("source rowsInserted");
        // });
        // connect(sourceModel, &M::rowsRemoved, this, [dbg]() {
        //     dbg("source rowsRemoved");
        // });
        // connect(sourceModel, &M::dataChanged, this, [dbg]() {
        //     dbg("source dataChanged");
        // });
        // connect(sourceModel, &M::modelAboutToBeReset, this, [dbg]() {
        //     dbg("source modelAboutToBeReset");
        // });
        // connect(sourceModel, &M::modelReset, this, [dbg]() {
        //     dbg("source modelReset");
        // });
        connect(sourceModel, &M::layoutChanged, this, [dbg]() {
            dbg("source layoutChanged"); //
        });
    }
}
