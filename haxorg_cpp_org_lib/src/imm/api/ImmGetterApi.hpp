#pragma once

#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>
#include <hstd/stdlib/containers/Outcome.hpp>
#include <hstd/stdlib/serde/JsonSerde.hpp>

namespace org::imm {

namespace keywords {
constexpr std::string attached_list_keyword = "attached";
constexpr std::string attached_list_target  = "subtree";
} // namespace keywords


bool isDescriptionItem(org::imm::ImmAdapter const& node);
bool isLinkedDescriptionItemNode(org::imm::ImmAdapter const& n);
bool isLinkedListItemNode(org::imm::ImmAdapter const& n);

/// \brief Check if link matches any of the known internal protocols, or is not an
/// explicitly external link.
bool isInternalLink(org::imm::ImmAdapterT<org::imm::ImmLink> const& link);

/// \brief Check itself is an internal link or has any recursive link subnodes,
/// recurisively.
bool hasAnyInternalLinks(org::imm::ImmAdapter const& n);

hstd::Vec<org::imm::ImmAdapterT<org::imm::ImmLink>> getAllInternalLinks(
    org::imm::ImmAdapter const& n);

/// \brief Check if node is a description list item with internal link in the header.
/// This returns true for any list item that is a part of the linked description list
/// item.
bool isPartOfDescriptionListItem(org::imm::ImmAdapter const& n);
bool isPartOfInternalLinkedListItem(org::imm::ImmAdapter const& n);

/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isInternalLinkedDescriptionList(org::imm::ImmAdapter const& n);

/// \brief Check if the
bool isInternalLinkedRegularList(org::imm::ImmAdapter const& n);

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInSubtreeDescriptionList(org::imm::ImmAdapter const& n);

bool isAttachedSubtreeList(org::imm::ImmAdapter const& n);

template <typename T>
hstd::outcome::result<T, std::string> getStructuredProperty(
    org::imm::ImmAdapter const& node,
    std::string const&          kind) {

    hstd::Opt<sem::NamedProperty> opt_prop;

    if (auto subtree = node.asOpt<org::imm::ImmSubtree>()) {
        opt_prop = subtree->getPropertyByKind("customjson", kind);
    } else if (auto doc = node.asOpt<org::imm::ImmDocument>()) {
        opt_prop = node.ctx.lock()
                       ->adaptUnrooted(doc.value()->options)
                       .as<org::imm::ImmDocumentOptions>()
                       .getPropertyByKind("customjson", kind);
    } else {
        return hstd::fmt("Node {} does not contain subtree", node);
    }

    BOOST_OUTCOME_TRY_OPTIONAL(
        property, opt_prop, hstd::fmt("Property :prop_json:{}: not found", kind));

    BOOST_OUTCOME_TRY_SUB_VARIANT(json_data, property, CustomSubtreeJson);
    try {
        return hstd::from_json_eval<T>(json_data.value.getRef());
    } catch (json::type_error& err) {
        return hstd::fmt(
            "Property :prop_json:{}: JSON did not match the expected "
            "structure. While reading type {}, got error: {}. JSON syntax "
            "is valid, the value is {}",
            kind,
            hstd::value_metadata<T>::typeName(),
            err.what(),
            json_data.value.getRef().dump());
    }
}

} // namespace org::imm
