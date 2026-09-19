#include "ImmGetterApi.hpp"
#include "haxorg/api/SemBaseApi.hpp"
#include <hstd/stdlib/Ranges.hpp>

using namespace org::imm;
using namespace hstd;
using osk = OrgSemKind;

bool org::imm::isDescriptionItem(ImmAdapter const& node) {
    return node.as<ImmListItem>()->header->has_value();
}

bool org::imm::isLinkedDescriptionItemNode(ImmAdapter const& n) {
    return n.is(osk::ListItem)  //
        && isDescriptionItem(n) //
        && hasAnyInternalLinks(n.pass(n.as<ImmListItem>()->header.get().value()));
}

bool org::imm::isLinkedListItemNode(org::imm::ImmAdapter const& n) {
    return n.is(osk::ListItem) && hasAnyInternalLinks(n);
}


bool org::imm::isInternalLink(org::imm::ImmAdapterT<ImmLink> const& link) {
    return !link->target.isRaw();
}

bool org::imm::hasAnyInternalLinks(org::imm::ImmAdapter const& n) {
    bool res{};
    org::eachSubnodeRec(n, false, [&](org::imm::ImmAdapter const& it) {
        if (auto const& link = it.asOpt<org::imm::ImmLink>()) {
            res |= isInternalLink(link.value());
        }
    });
    return res;
}

hstd::Vec<org::imm::ImmAdapterT<org::imm::ImmLink>> org::imm::getAllInternalLinks(
    org::imm::ImmAdapter const& n) {
    hstd::Vec<org::imm::ImmAdapterT<org::imm::ImmLink>> res;
    org::eachSubnodeRec(n, true, [&](org::imm::ImmAdapter const& it) {
        if (auto const& link = it.asOpt<org::imm::ImmLink>()) {
            if (isInternalLink(link.value())) { res.push_back(link.value()); }
        }
    });
    return res;
}


bool org::imm::isPartOfDescriptionListItem(ImmAdapter const& n) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        n.getParentChain(/*withSelf=*/false),
        [&](ImmAdapter parent) -> bool { return isLinkedDescriptionItemNode(parent); });
}

bool org::imm::isPartOfInternalLinkedListItem(org::imm::ImmAdapter const& n) {
    return rs::any_of(
        n.getParentChain(/*withSelf=*/false),
        [&](ImmAdapter parent) -> bool { return isLinkedListItemNode(parent); });
}


bool org::imm::isInternalLinkedDescriptionList(ImmAdapter const& n) {
    return n.is(osk::List) && rs::any_of(n.sub(), [&](ImmAdapter arg) -> bool {
               return isPartOfDescriptionListItem(arg);
           });
}

bool org::imm::isInternalLinkedRegularList(org::imm::ImmAdapter const& n) {
    return n.is(osk::List) && rs::any_of(n.sub(), [&](ImmAdapter arg) -> bool {
               return isPartOfDescriptionListItem(arg);
           });
}


bool org::imm::isInSubtreeDescriptionList(ImmAdapter const& n) {
    return rs::any_of(
        n.getParentChain(), [](ImmAdapter tree) { return isAttachedSubtreeList(tree); });
}


bool org::imm::isAttachedSubtreeList(ImmAdapter const& n) {
    if (auto list = n.asOpt<ImmList>(); list) {
        auto attached = list->getListAttrs(org::imm::keywords::attached_list_keyword);
        return attached.has(0)
            && attached.at(0).getString() == keywords::attached_list_target;
    } else {
        return false;
    }
}
