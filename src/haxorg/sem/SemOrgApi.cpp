#include <haxorg/sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <concepts>
#include <format>
#include <haxorg/exporters/exportertree.hpp>

#define _define_static(__Kind)                                            \
    const OrgSemKind sem::__Kind::staticKind = OrgSemKind::__Kind;

EACH_SEM_ORG_KIND(_define_static)

#undef _define_static


using boost::mp11::mp_for_each;
using namespace boost::describe;

using namespace sem;
using osk      = OrgSemKind;
using Property = NamedProperty;

template <>
struct value_domain<sem::SubtreePeriod::Kind>
    : value_domain_ungapped<
          sem::SubtreePeriod::Kind,
          sem::SubtreePeriod::Kind::Clocked,
          sem::SubtreePeriod::Kind::Repeated> {};

namespace sem {
sem::OrgIdVariant asVariant(SemId<Org> in) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return in.as<__Kind>();

    switch (in->getKind()) { EACH_SEM_ORG_KIND(__case) }

#undef __case
}

sem::OrgPtrVariant asVariant(Org* in) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return dynamic_cast<__Kind*>(in);
    switch (in->getKind()) { EACH_SEM_ORG_KIND(__case) }
#undef __case
}

} // namespace sem

Org::Org() : subnodes({}) {}
Org::Org(OrgAdapter original) : original(original), subnodes({}) {}
Org::Org(CVec<SemId<Org>> subnodes) : subnodes(subnodes) {}


bool HashTag::prefixMatch(CR<Vec<Str>> prefix) const {
    if (prefix.empty() || (prefix.size() == 1 && prefix[0] == head)) {
        return true;
    } else if (prefix[0] != head) {
        return false;
    } else {
        Vec<Str> tmp;
        for (const auto& it : prefix[slice(1, 1_B)]) { tmp.push_back(it); }

        for (const auto& sub : subtags) {
            if (sub->prefixMatch(tmp)) { return true; }
        }
        return false;
    }
}

void Subtree::setPropertyStrValue(
    Str const&   value,
    Str const&   kind,
    CR<Opt<Str>> subkind) {
    if (normalize(kind) == "id") {
        this->treeId = value;
    } else {
        removeProperty(kind, subkind);
        Property::CustomRaw prop;
        prop.name  = kind;
        prop.value = value;
        properties.push_back(Property{prop});
    }
}

void Subtree::setProperty(Property const& value) {
    removeProperty(value.getName(), value.getSubKind());
    properties.push_back(value);
}


void Subtree::removeProperty(const Str& kind, const Opt<Str>& subkind) {
    for (int i = properties.high(); 0 <= i; --i) {
        if (properties.at(i).getName() == kind
            && properties.at(i).getSubKind() == subkind) {
            properties.erase(properties.begin() + i);
        }
    }
}

Str NamedProperty::getName() const {
    if (getKind() == Kind::CustomRaw) {
        return getCustomRaw().name;
    } else {
        return fmt1(getKind());
    }
}

Opt<Str> NamedProperty::getSubKind() const {
    if (getKind() == Kind::ExportOptions) {
        return getExportOptions().backend;
    } else {
        return std::nullopt;
    }
}

bool NamedProperty::isMatching(Str const& kind, CR<Opt<Str>> subkind)
    const {
    if (getKind() == Property::Kind::CustomRaw) {
        return normalize(getCustomRaw().name) == normalize(kind);
    } else if (normalize(fmt1(getKind())) == normalize(kind)) {
        return true;
    } else if (
        getKind() == Property::Kind::ExportOptions && subkind
        && normalize(getExportOptions().backend) == normalize(*subkind)) {
        return true;
    } else {
        return false;
    }
}

Vec<NamedProperty> DocumentOptions::getProperties(
    Str const&   kind,
    CR<Opt<Str>> subkind) const {
    Vec<NamedProperty> result;
    for (const auto& prop : properties) {
        if (prop.isMatching(kind, subkind)) { result.push_back(prop); }
    }
    return result;
}

Opt<NamedProperty> DocumentOptions::getProperty(
    CR<Str>      kind,
    CR<Opt<Str>> subkind) const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}

Vec<NamedProperty> Document::getProperties(
    CR<Str>      kind,
    CR<Opt<Str>> subkind) const {
    if (options.isNil()) {
        return {};
    } else {
        return options->getProperties(kind, subkind);
    }
}

Opt<NamedProperty> Document::getProperty(
    CR<Str>      kind,
    CR<Opt<Str>> subkind) const {
    if (options.isNil()) {
        return std::nullopt;
    } else {
        return options->getProperty(kind, subkind);
    }
}

bool List::isDescriptionList() const {
    for (const auto& sub : subnodes) {
        if (sub->is(osk::ListItem)) {
            if (sub.as<ListItem>()->isDescriptionItem()) { return true; }
        }
    }
    return false;
}

bool List::isNumberedList() const {
    for (const auto& sub : subAs<sem::ListItem>()) {
        if (sub->bullet.has_value()) { return true; }
    }

    return false;
}

Vec<sem::SemId<sem::Org>> Stmt::getAttached(CR<Opt<Str>> kind) const {
    Vec<SemId<Org>> result;
    for (const auto& sub : attached) {
        if (kind) {
            auto k = *kind;
            if (auto attr = sub.getAs<sem::CmdAttr>()) {
                if (normalize("attr_" + attr->target) == k) {
                    result.push_back(sub);
                }
            } else if (auto cap = sub.getAs<sem::CmdCaption>();
                       cap && normalize(k) == "caption") {
                result.push_back(sub);
            }
        } else {
            result.push_back(sub);
        }
    }

    return result;
}




void Org::push_back(SemId<Org> sub) {
    auto dat = subnodes.data();
    subnodes.push_back(sub);
}


Str CmdArgumentValue::getString() const { return value; }

Opt<bool> CmdArgumentValue::getBool() const {
    if (value == "yes" || value == "true" || value == "on"
        || value == "t") {
        return true;
    } else if (
        value == "no" || value == "false" || value == "nil"
        || value == "off") {
        return false;
    } else {
        return std::nullopt;
    }
}

Opt<int> CmdArgumentValue::getInt() const {
    bool isOk   = false;
    int  result = value.toInt();
    if (isOk) {
        return result;
    } else {
        return std::nullopt;
    }
}
