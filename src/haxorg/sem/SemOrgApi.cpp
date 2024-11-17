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

Vec<sem::AttrValue> sem::AttrGroup::getFlatArgs() const {
    Vec<sem::AttrValue> res = positional.items;
    for (auto const& key : sorted(named.keys())) {
        res.append(named.at(key).items);
    }
    return res;
}

Vec<sem::AttrValue> sem::AttrGroup::getAttrs(CR<Opt<Str>> param) const {
    if (param) {
        Vec<sem::AttrValue> res;
        auto                norm = normalize(*param);
        if (named.contains(norm)) {
            for (auto const& it : named.at(norm).items) {
                res.push_back(it);
            }
        }
        return res;
    } else {
        return getFlatArgs();
    }
}

void sem::AttrGroup::setNamedAttr(
    Str const&                 key,
    Vec<sem::AttrValue> const& attr) {
    named.insert_or_assign(normalize(key), sem::AttrList{.items = attr});
}

void sem::AttrGroup::setPositionalAttr(Vec<sem::AttrValue> const& attr) {
    positional.items = attr;
}

bool HashTagText::prefixMatch(CR<Vec<Str>> prefix) const {
    if (prefix.empty() || (prefix.size() == 1 && prefix[0] == head)) {
        return true;
    } else if (prefix[0] != head) {
        return false;
    } else {
        Vec<Str> tmp;
        for (const auto& it : prefix[slice(1, 1_B)]) { tmp.push_back(it); }

        for (const auto& sub : subtags) {
            if (sub.prefixMatch(tmp)) { return true; }
        }
        return false;
    }
}

Vec<Vec<Str>> sem::HashTagText::getFlatHashes(
    bool withIntermediate) const {
    using Res = Vec<Vec<Str>>;
    Func<Res(Vec<Str> const& parents, sem::HashTagText const& tag)> aux;
    UnorderedSet<Vec<Str>> visited;
    aux = [&](Vec<Str> const&         parents,
              sem::HashTagText const& tag) -> Res {
        Res result;
        if (withIntermediate && !parents.empty()
            && !visited.contains(parents)) {
            result.push_back(parents);
            visited.incl(parents);
        }
        if (tag.subtags.empty()) {
            result.push_back(parents);
            result.back().push_back(tag.head);
        } else {
            for (auto const& subtag : tag.subtags) {
                result.append(aux(parents + Vec<Str>{tag.head}, subtag));
            }
        }
        return result;
    };

    return aux({}, *this);
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
    } else if (getKind() == Property::Kind::CustomArgs) {
        return normalize(getCustomArgs().name) == normalize(kind);
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


void Org::push_back(SemId<Org> sub) { subnodes.push_back(sub); }

SemId<Org> Org::as_unref_shared() const {
    SemId<Org> res;
    res.value = std::shared_ptr<Org>(const_cast<Org*>(this), [](Org*) {});
    return res;
}


Str AttrValue::getString() const { return value; }

Opt<bool> AttrValue::getBool() const {
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

Opt<int> AttrValue::getInt() const {
    bool isOk   = false;
    int  result = value.toInt();
    if (isOk) {
        return result;
    } else {
        return std::nullopt;
    }
}
