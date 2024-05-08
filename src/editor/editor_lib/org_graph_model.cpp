#include <editor/editor_lib/org_graph_model.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <boost/graph/graphviz.hpp>
#include <QDebug>
#include <exporters/ExporterUltraplain.hpp>
#include <editor/editor_lib/org_document_render.hpp>

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

void OrgGraph::addBox(CR<OrgBoxId> box) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    if (rs::any_of(
            store->tree(box)->parentChain(/*withSelf = */ false),
            [](OrgTreeNode* parent) -> bool {
                return isLinkedDescriptionItem(parent->boxedNode());
            })) {
        return;
    }


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
            qDebug() << "Found description item";

            for (auto const& head : desc->header.value()->subnodes) {
                qDebug() << "Header subnode" << debug(head);
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

    VDesc v  = boost::add_vertex(g);
    g[v].box = box;

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

    boxToVertex[box] = v;
    updateUnresolved(v);
}

void OrgGraph::updateUnresolved(VDesc) {
    for (auto const& id : unresolved.keys()) {
        auto add_edge = [&](CR<OrgGraphEdge> spec, CVec<OrgBoxId> target) {
            for (auto const& box : target) {
                boost::add_edge(desc(id), desc(box), spec, g);
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
                        store->tree(prop.box)->selfPath());
                },
                get(boost::vertex_bundle, g)));


    write_graphviz_dp(os, g, dp);

    return os.str();
}

QVariant OrgGraphModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || rowCount() <= index.row()) {
        return QVariant();
    }

    switch (role) {
        case SharedModelRoles::IndexBoxRole: {
            if (isNode(index)) {
                return QVariant::fromValue(boxAt(index.row()));
            } else {
                return QVariant();
            }
        }

        case Qt::DisplayRole: {
            if (isNode(index)) {
                auto sem = g->store->nodeWithoutNested(boxAt(index.row()));
                return QString::fromStdString(
                    fmt("NODE[{}] \"{}\"",
                        boxAt(index.row()),
                        ExporterUltraplain::toStr(sem)));

            } else {
                return QString::fromStdString(
                    fmt("EDGE[{}-{}]",
                        g->node(g->source(edgeAt(index))).box,
                        g->node(g->target(edgeAt(index))).box));
            }
        }

        case OrgGraphModelRoles::IsNodeRole: {
            return isNode(index);
        }

        default: {
            return QVariant();
        }
    }
}

QSize OrgGraphModel::nodeSize(const QModelIndex& index) const {
    Q_ASSERT(isNode(index));
    auto label = make_label(
        g->store->nodeWithoutNested(boxAt(index.row())));

    return get_width_fit(label.get(), 200);
}

OrgGraphLayoutProxy::FullLayout OrgGraphLayoutProxy::getFullLayout()
    const {
    GraphLayoutIR        ir;
    OrgGraphModel const* src = graphModel();

    UnorderedMap<OrgGraph::VDesc, int> nodeToRect;

    for (int row = 0; row < src->rowCount(); ++row) {
        QModelIndex index = src->index(row, 0);
        if (src->isNode(index)) {
            auto desc        = src->nodeAt(index);
            nodeToRect[desc] = ir.rectangles.size();
            auto size        = src->nodeSize(index);
            ir.rectangles.push_back(
                QRect(0, 0, size.width(), size.height()));
        } else {
            auto [source, target] = src->sourceTargetAt(index);
            ir.edges.push_back(
                {nodeToRect.at(source), nodeToRect.at(target)});
        }
    }

    Graphviz gvc;
    auto     lyt = ir.doGraphvizLayout(gvc);

    lyt.writeSvg("/tmp/getFullLayout.svg");
    lyt.writeXDot("/tmp/getFullLayout.xdot");

    auto conv_lyt = lyt.convert();

    FullLayout res;
    for (int row = 0; row < sourceModel()->rowCount(); ++row) {
        QModelIndex index = src->index(row, 0);
        if (src->isNode(index)) {
            res.data[index] = ElementLayout{
                .data = conv_lyt.fixed.at(
                    nodeToRect.at(src->nodeAt(index)))};
        } else {
            auto [source, target] = src->sourceTargetAt(index);
            res.data[index]       = ElementLayout{conv_lyt.lines.at({
                nodeToRect.at(source),
                nodeToRect.at(target),
            })};
        }
    }


    return res;
}

QVariant OrgGraphLayoutProxy::data(const QModelIndex& index, int role)
    const {
    auto isNodeVar = sourceModel()->data(
        mapToSource(index), OrgGraphModelRoles::IsNodeRole);
    bool isNode = isNodeVar.toBool();
    switch (role) {
        case OrgGraphModelRoles::NodeShapeRole: {
            if (isNode) {
                return QVariant::fromValue(getElement(index).getNode());
            } else {
                return QVariant();
            }
        }

        case OrgGraphModelRoles::EdgeShapeRole: {
            if (isNode) {
                return QVariant();
            } else {
                return QVariant::fromValue(getElement(index).getEdge());
            }
        }

        default: {
            return sourceModel()->data(mapToSource(index), role);
        }
    }
}
