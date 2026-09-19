#pragma once


#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgBase.hpp>
#include <hstd/stdlib/strutils.hpp>

hstd::fmt_iter fmt::formatter<hstd::ext::ImmBox<std::string>>::format(
    hstd::ext::ImmBox<std::string> const& p,
    format_context&                       ctx) const {
    hstd::fmt_ctx("Box{", ctx);
    hstd::fmt_ctx(hstd::escape_literal(p.get()), ctx);
    return hstd::fmt_ctx("}", ctx);
}

hstd::fmt_iter fmt::formatter<hstd::ext::ImmBox<hstd::Str>>::format(
    hstd::ext::ImmBox<hstd::Str> const& p,
    fmt::format_context&                ctx) const {
    hstd::fmt_ctx("Box{", ctx);
    hstd::fmt_ctx(hstd::escape_literal(p.get()), ctx);
    return hstd::fmt_ctx("}", ctx);
}

hstd::Str org::imm::ImmReflFieldId::getName() const {
    if (typeId.has_value()) {
        return hstd::get_registered_field_name(typeId.value(), index);
    } else {
        return hstd::fmt("field_{}", index);
    }
}

org::imm::ImmReflFieldId org::imm::ImmReflFieldId::FromIdParts(
    std::optional<std::type_index> typeId,
    offset_type                    index) {
    ImmReflFieldId res{};
    res.typeId = typeId;
    res.index  = index;
    return res;
}


org::imm::ImmReflFieldId org::imm::ImmReflFieldId::fromSerializableId(std::uint64_t id) {
    return ImmReflFieldId::FromIdParts(
        std::nullopt, static_cast<offset_type>(id & 0xFFFFFFFF));
}

org::imm::ImmId::NodeIdxT org::imm::ImmId::getNodeIdx(IdType id) {
    return NodeIdxT((id & NodeIdxMask) >> NodeIdxOffset);
}

OrgSemKind org::imm::ImmId::getKind(IdType id) {
    return OrgSemKind((id & NodeKindMask) >> NodeKindOffset);
}

OrgSemKind org::imm::ImmId::getKind() const { return ImmId::getKind(value); }

bool org::imm::ImmId::is(OrgSemKind kind) const { return getKind() == kind; }

bool org::imm::ImmId::operator!=(Id other) const noexcept {
    return getValue() != other.getValue();
}

bool org::imm::ImmId::operator==(Id other) const noexcept {
    return getValue() == other.getValue();
}

bool org::imm::ImmId::operator<=(Id other) const noexcept {
    return getValue() <= other.getValue();
}

bool org::imm::ImmId::operator<(Id other) const noexcept {
    return getValue() < other.getValue();
}

org::imm::ImmId::NodeIdxT org::imm::ImmId::getNodeIndex() const {
    return ImmId::getNodeIdx(value);
}

org::imm::ImmId org::imm::ImmId::FromValue(hstd::u64 value) {
    return ImmId{ImmIdBase::FromValue(value)};
}

org::imm::ImmId org::imm::ImmOrg::at(int pos) const { return subnodes.at(pos); }

hstd::ext::ImmVec<org::imm::ImmId>::iterator org::imm::ImmOrg::begin() const {
    return subnodes.begin();
}

hstd::ext::ImmVec<org::imm::ImmId>::iterator org::imm::ImmOrg::end() const {
    return subnodes.end();
}

int org::imm::ImmOrg::size() const { return subnodes.size(); }

int org::imm::ImmOrg::indexOf(org::imm::ImmId subnode) const {
    for (int i = 0; i < subnodes.size(); ++i) {
        if (subnodes.at(i) == subnode) { return i; }
    }
    return -1;
}

bool org::imm::ImmOrg::is(SemSet const& kind) const { return kind.contains(getKind()); }

bool org::imm::ImmOrg::is(OrgSemKind kind) const { return getKind() == kind; }


template <typename T>
const T* org::imm::ImmOrg::as() const {
    auto res = dyn_cast<T>();
    if (res == nullptr) {
        if constexpr (std::is_abstract_v<T>) {
            throw std::logic_error(
                hstd::fmt("Cannot cast node of kind {}", this->getKind()));
        } else {
            throw std::logic_error(
                hstd::fmt(
                    "Cannot cast node of kind {} to kind {}",
                    this->getKind(),
                    T::staticKind));
        }
    }
    return res;
}

template <typename T>
const T* org::imm::ImmOrg::dyn_cast() const {
    return dynamic_cast<T const*>(this);
}

#define _kind(__It, __Base)                                                              \
    template org::imm::Imm##__It const* org::imm::ImmOrg::as<org::imm::Imm##__It>()      \
        const;                                                                           \
    template org::imm::Imm##__It const*                                                  \
        org::imm::ImmOrg::dyn_cast<org::imm::Imm##__It>() const;

EACH_SEM_ORG_TYPE_BASE(_kind)

_kind(Org, Org);

#undef _kind
