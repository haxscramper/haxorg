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
using namespace org::mind_map;

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

Graph::Edit Graph::getNodeInsertEdits(CR<OrgBoxId> box) const {
    Edit result;
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    if (isLinkedDescriptionItem(store, box)) { return result; }

    sem::SemId<sem::Org> n = store->node(box);
    if (n->is(osk::Subtree)) {
        sem::SemId<sem::Subtree> tree = n.as<sem::Subtree>();
        if (tree->treeId) {
            result.subtrees.push_back(Edit::SubtreeId{
                .box  = box,
                .name = tree->treeId.value(),
            });
        }
    } else if (n->is(osk::AnnotatedParagraph)) {
        sem::SemId<sem::AnnotatedParagraph>
            par = n.as<sem::AnnotatedParagraph>();
        if (par->getAnnotationKind()
            == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
            Str name = par->getFootnote().name;
            result.footnotes.push_back(Edit::FootnoteTarget{
                .name = name,
                .box  = box,
            });
        }
    }

    auto register_used_links = [&](sem::OrgArg arg) {
        Q_ASSERT(!arg.isNil());
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (arg->is(osk::Link)) {
            auto link = arg.as<sem::Link>();
            if (link->getLinkKind() != slk::Raw) {
                result.unresolved.push_back(UnresolvedLink{
                    .origin = box,
                    .link   = arg.as<sem::Link>(),
                    .description //
                    = link->description
                        ? std::make_optional(link->description->asOrg())
                        : std::nullopt,
                });
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

                        Q_ASSERT(!link.isNil());
                        result.unresolved.push_back(UnresolvedLink{
                            .origin      = parent_subtree,
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

    Edit::Vertex vert{.box = box};

    switch (n->getKind()) {
        case osk::Subtree: {
            vert.kind = OrgGraphNode::Kind::Subtree;
            break;
        }

        case osk::AnnotatedParagraph: {
            if (n.as<sem::AnnotatedParagraph>()->getAnnotationKind()
                == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
                vert.kind = OrgGraphNode::Kind::Footnote;
            } else {
                vert.kind = OrgGraphNode::Kind::Paragraph;
            }
            break;
        }

        case osk::Paragraph: {
            vert.kind = OrgGraphNode::Kind::Paragraph;
            break;
        }

        case osk::Document: {
            vert.kind = OrgGraphNode::Kind::Document;
            break;
        }

        case osk::List: {
            vert.kind = OrgGraphNode::Kind::List;
            break;
        }

        case osk::ListItem: {
            vert.kind = OrgGraphNode::Kind::ListItem;
            break;
        }

        default: {
        }
    }

    result.vertices.push_back(vert);


    return getUnresolvedEdits(result);
}

Pair<Graph::Edit, Graph::Edit> Graph::getNodeUpdateEdits(
    CR<OrgBoxId> before,
    CR<OrgBoxId> after) const {
    auto const to_remove = getNodeInsertEdits(before);
    auto const to_add    = getNodeInsertEdits(after);


    return {
        // delete
        Edit{},
        // add
        Edit{},
    };
}

Graph::Edit Graph::getUnresolvedEdits(CR<Edit> edit) const {
    Graph::Edit result = edit;
    result.unresolved.clear();

    for (auto const& it : edit.unresolved) {
        Vec<Edit::ResolveLink> resolved_edit = getResolveTarget(edit, it);
        if (resolved_edit.empty()) {
            result.unresolved.push_back(it);
        } else {
            result.resolved.append(resolved_edit);
        }
    }

    for (auto const& it : this->state.unresolved) {
        Vec<Edit::ResolveLink> resolved_edit = getResolveTarget(edit, it);
        if (!resolved_edit.empty()) {
            result.resolved.append(resolved_edit);
        }
    }

    return result;
}

Vec<Graph::Edit::ResolveLink> Graph::getResolveTarget(
    CR<Edit>           edit,
    CR<UnresolvedLink> it) const {

    Vec<Graph::Edit::ResolveLink> result;

    auto add_edge = [&](OrgGraphEdge::Kind kind, CVec<OrgBoxId> target) {
        for (auto const& box : target) {
            Q_ASSERT(!it.link.isNil());
            result.push_back(Edit::ResolveLink{
                .source   = it.origin,
                .target   = box,
                .original = it,
                .spec     = OrgGraphEdge{
                        .link        = it.link,
                        .description = it.description,
                        .kind        = kind,
                }});
        }
    };

    switch (it.link->getLinkKind()) {
        case slk::Id: {
            if (auto target = state.subtreeIds.get(
                    it.link->getId().text)) {
                add_edge(OrgGraphEdge::Kind::SubtreeId, *target);
            }

            for (auto const& target : edit.subtrees) {
                if (target.name == it.link->getId().text) {
                    add_edge(OrgGraphEdge::Kind::SubtreeId, {target.box});
                }
            }

            break;
        }

        case slk::Footnote: {
            if (auto target = state.footnoteTargets.get(
                    it.link->getFootnote().target)) {
                add_edge(OrgGraphEdge::Kind::Footnote, *target);
            }

            for (auto const& target : edit.footnotes) {
                if (target.name == it.link->getFootnote().target) {
                    add_edge(OrgGraphEdge::Kind::Footnote, {target.box});
                }
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
        .property("node_id", get(boost::vertex_index, state.g))
        .property(
            "splines",
            boost::make_constant_property<BoostBase*>(
                std::string("polyline")))
        .property(
            "shape",
            boost::make_constant_property<BoostBase::vertex_descriptor>(
                std::string("rect")))
        .property(
            "description",
            make_transform_value_property_map<std::string>(
                [&](OrgGraphEdge const& prop) -> std::string {
                    return prop.description ? ExporterUltraplain::toStr(
                               prop.description.value())
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

QVariant Graph::data(const QModelIndex& index, int role) const {
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
