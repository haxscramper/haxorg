#include "ImmOrgGraph.hpp"
#include "haxorg/sem/SemBaseApi.hpp"
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
               n.pass(n.as<org::ImmListItem>()->header.get().value())
                   .subAs<org::ImmLink>(),
               [](org::ImmAdapterT<org::ImmLink> head) -> bool {
                   return head->getLinkKind() != slk::Raw;
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
        && rs::any_of(n.sub(), [&](org::ImmAdapter arg) -> bool {
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


static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::List,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};


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

    auto register_used_links = [&](org::ImmAdapter arg) {
        // Unconditionally register all links as unresolved -- some of
        // them will be converted to edges later on.
        if (arg.is(osk::Link)) {
            auto link = arg.as<org::ImmLink>();
            if (link->getLinkKind() != slk::Raw) {
                result.unresolved.push_back(MapLink{
                    .link = arg.as<org::ImmLink>(),
                    .description //
                    = link->description.get()
                        ? Vec{arg.pass(
                              link->description.get().value().toId())}
                        : Vec<org::ImmAdapter>{},
                });
            }
        }
    };

    if (auto tree = node.asOpt<org::ImmSubtree>()) {
        // Description lists with links in header are attached as the
        // outgoing link to the parent subtree. It is the only supported
        // way to provide an extensive label between subtree edges.
        for (auto const& list : tree->subAs<org::ImmList>()) {
            for (auto const& item : list.subAs<org::ImmListItem>()) {
                if (isLinkedDescriptionItem(item)) {
                    for (auto const& link :
                         item.pass(item->header->value())
                             .subAs<org::ImmLink>()) {
                        // Description list header might contain
                        // non-link elements. These are ignored in the
                        // mind map.
                        if (link->getLinkKind() != slk::Raw) {
                            MapLink map_link{.link = link};
                            for (auto const& sub : item) {
                                map_link.description.push_back(sub);
                            }
                            result.unresolved.push_back(map_link);
                        }
                    }
                }
            }
        }
    } else if (!NestedNodes.contains(node->getKind())) {
        org::eachSubnodeRec(node, register_used_links);
    }

    switch (node->getKind()) {
        case osk::Subtree: {
            result.kind = MapNodeProp::Kind::Subtree;
            break;
        }

        case osk::AnnotatedParagraph: {
            if (node.as<sem::AnnotatedParagraph>()->getAnnotationKind()
                == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
                result.kind = MapNodeProp::Kind::Footnote;
            } else {
                result.kind = MapNodeProp::Kind::Paragraph;
            }
            break;
        }

        case osk::Paragraph: {
            result.kind = MapNodeProp::Kind::Paragraph;
            break;
        }

        case osk::Document: {
            result.kind = MapNodeProp::Kind::Document;
            break;
        }

        case osk::List: {
            result.kind = MapNodeProp::Kind::List;
            break;
        }

        case osk::ListItem: {
            result.kind = MapNodeProp::Kind::ListItem;
            break;
        }

        default: {
        }
    }

    if (conf.TraceState) {
        conf.message(fmt("box:{} unresolved:{}", node, result.unresolved));
    }

    return result;
}
