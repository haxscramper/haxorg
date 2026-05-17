#pragma once

#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>

namespace org::imm {
bool isDescriptionItem(org::imm::ImmAdapter const& node);
bool isLinkedDescriptionItemNode(org::imm::ImmAdapter const& n);

bool isLinkedDescriptionItem(org::imm::ImmAdapter const& n);
/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::imm::ImmAdapter const& n);

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInSubtreeDescriptionList(org::imm::ImmAdapter const& n);

bool isAttachedDescriptionList(org::imm::ImmAdapter const& n);
} // namespace org::imm
