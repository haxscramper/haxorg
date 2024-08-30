#include "ImmOrgGraph.hpp"
#include <hstd/stdlib/Ranges.hpp>

using namespace org::graph;
using osk = OrgSemKind;
using slk = org::ImmLink::Kind;

namespace {

bool isDescriptionItem(org::ImmAdapter node) {
    return node.as<org::ImmListItem>()->header->has_value();
}

bool isLinkedDescriptionItemNode(org::ImmAdapter n) {
    return n.is(osk::ListItem)  //
        && isDescriptionItem(n) //
        && rs::any_of(
               n.pass(n.as<org::ImmListItem>()->header.get().value()),
               [](org::ImmAdapter head) -> bool {
                   return head.is(osk::Link)
                       && head.as<org::ImmLink>()->getLinkKind()
                              != slk::Raw;
               });
}

bool isLinkedDescriptionItem(org::ImmAdapter n) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        n.getParentChain(/*withSelf = */ false),
        [&](org::ImmAdapter parent) -> bool {
            return isLinkedDescriptionItemNode(parent);
        });
}

/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::ImmAdapter n) {
    return n.is(osk::List)
        && rs::any_of(n, [&](org::ImmAdapter arg) -> bool {
               return isLinkedDescriptionItem(arg);
           });
}

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInLinkedDescriptionList(org::ImmAdapter n) {
    return rs::any_of(n.getParentChain(), [](org::ImmAdapter tree) {
        return isLinkedDescriptionItem(tree);
    });
}

bool isMmapIgnored(org::ImmAdapter n) {
    return isInLinkedDescriptionList(n) || isLinkedDescriptionList(n);
}
} // namespace

org::graph::MapGraphState org::graph::addNode(
    MapGraphState const& g,
    org::ImmAdapter      node,
    MapOpsConfig&        conf) {
    return g;
}


Opt<MapNodeProp> getNodeInsert(
    MapGraphState const& s,
    org::ImmAdapter      node,
    MapOpsConfig&        conf) {
    // `- [[link-to-something]] :: Description` is stored as a description
    // field and is collected from the list item. So all boxes with
    // individual list items are dropped here.
    if (isMmapIgnored(node)) { return std::nullopt; }

    if (conf.TraceState) {
        conf.message(
            fmt("box:{} desc-item:{} desc-list:{}",
                node,
                isLinkedDescriptionItem(node),
                isLinkedDescriptionList(node)));
    }

    MapNodeProp result{.id = node};

    auto register_used_links = [&](org::ImmAdapterI arg) {
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
