#include "ImmOrgGraph.hpp"
#include <hstd/stdlib/Ranges.hpp>

using namespace org::graph;
using osk = OrgSemKind;
using slk = sem::Link::Kind;

namespace {

bool isDescriptionItem(org::ContextStore* ctx, org::ImmId id) {
    return ctx->at(id)->as<org::ImmListItem>()->header->has_value();
}

bool isLinkedDescriptionItemNode(org::ContextStore* ctx, org::ImmId n) {
    return ctx->at(n)->is(osk::ListItem) //
        && isDescriptionItem(ctx, n)     //
        && rs::any_of(
               ctx->at(
                      ctx->at_t<org::ImmListItem>(n)->header.get().value())
                   ->subnodes,
               [&](org::ImmId head) -> bool {
                   return ctx->at(head)->is(osk::Link)
                       && ctx->at_t<sem::Link>(head)->getLinkKind()
                              != slk::Raw;
               });
}

bool isLinkedDescriptionItem(org::ContextStore* ctx, org::ImmId box) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        ctx->getParentChain(box, /*withSelf = */ false),
        [&](org::ImmId parent) -> bool {
            return isLinkedDescriptionItemNode(ctx, parent);
        });
}

/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::ContextStore* ctx, org::ImmId box) {
    return ctx->at(box)->is(osk::List)
        && rs::any_of(*ctx->at(box), [&](org::ImmId arg) -> bool {
               return isLinkedDescriptionItem(ctx, arg);
           });
}

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInLinkedDescriptionList(org::ContextStore* ctx, org::ImmId box) {
    return rs::any_of(ctx->getParentChain(box), [&](org::ImmId tree) {
        return isLinkedDescriptionItem(ctx, tree);
    });
}

bool isMmapIgnored(org::ContextStore* ctx, org::ImmId box) {
    return isInLinkedDescriptionList(ctx, box)
        || isLinkedDescriptionList(ctx, box);
}
} // namespace

org::graph::MapGraphState org::graph::addNode(
    const MapGraphState& g,
    ImmId                node,
    MapOpsConfig&        conf) {
    return g;
}


Opt<MapNodeProp> getNodeInsert(
    MapGraphState const& s,
    org::ImmId           node,
    MapOpsConfig&        conf) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    if (isMmapIgnored(store, node)) { return std::nullopt; }

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

    auto register_used_links = [&](org::ImmId arg) {
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
