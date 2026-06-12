#include "ImmGetterApi.hpp"
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
        && rs::any_of(
               n.pass(n.as<ImmListItem>()->header.get().value()).subAs<ImmLink>(),
               [](ImmAdapterT<ImmLink> head) -> bool { return !head->target.isRaw(); });
}

bool org::imm::isLinkedDescriptionItem(ImmAdapter const& n) {
    // If any of the parent nodes for this box is a linked description
    // item, ignore the entry as it has already been added as a part of the
    // link descripion.
    return rs::any_of(
        n.getParentChain(/*withSelf = */ false),
        [&](ImmAdapter parent) -> bool { return isLinkedDescriptionItemNode(parent); });
}

bool org::imm::isLinkedDescriptionList(ImmAdapter const& n) {
    return n.is(osk::List) && rs::any_of(n.sub(), [&](ImmAdapter arg) -> bool {
               return isLinkedDescriptionItem(arg);
           });
}

bool org::imm::isInSubtreeDescriptionList(ImmAdapter const& n) {
    return rs::any_of(n.getParentChain(), [](ImmAdapter tree) {
        return isAttachedDescriptionList(tree);
    });
}


bool org::imm::isAttachedDescriptionList(ImmAdapter const& n) {
    if (auto list = n.asOpt<ImmList>(); list && list->isDescriptionList()) {
        auto attached = list->getListAttrs("attached");
        return attached.has(0) && attached.at(0).getString() == "subtree";
    } else {
        return false;
    }
}
