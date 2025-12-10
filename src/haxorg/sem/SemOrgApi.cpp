#include <haxorg/sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <concepts>
#include <format>
#include <haxorg/exporters/exportertree.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

using namespace hstd;
using namespace org::sem;

#define _define_static(__Kind)                                            \
    const OrgSemKind org::sem::__Kind::staticKind = OrgSemKind::__Kind;

EACH_SEM_ORG_KIND(_define_static)

#undef _define_static


using boost::mp11::mp_for_each;
using namespace boost::describe;

using osk      = OrgSemKind;
using Property = NamedProperty;

template <>
struct value_domain<org::sem::SubtreePeriod::Kind>
    : value_domain_ungapped<
          org::sem::SubtreePeriod::Kind,
          org::sem::SubtreePeriod::Kind::Clocked,
          org::sem::SubtreePeriod::Kind::Repeated> {};

namespace org::sem {
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

} // namespace org::sem

Org::Org() : subnodes({}) {}
Org::Org(CVec<SemId<Org>> subnodes) : subnodes(subnodes) {}

Vec<org::sem::AttrValue> AttrGroup::getFlatArgs() const {
    Vec<AttrValue> res = positional.items;
    for (auto const& key : sorted(named.keys())) {
        res.append(named.at(key).items);
    }
    return res;
}

Vec<AttrValue> AttrGroup::getAttrs(CR<Opt<Str>> param) const {
    if (param) {
        Vec<AttrValue> res;
        auto           norm = normalize(*param);
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

int AttrGroup::getNamedSize() const {
    int result = 0;
    for (auto const& [key, val] : this->named) {
        result += val.items.size();
    }
    return result;
}

int AttrGroup::getPositionalSize() const {
    return positional.items.size();
}

bool AttrGroup::isEmpty() const {
    return getNamedSize() == 0 && getPositionalSize() == 0;
}

AttrValue const& AttrGroup::atPositional(int index) const {
    return this->positional.items.at(index);
}

Opt<AttrValue> AttrGroup::getPositional(int index) const {
    return this->positional.items.get(index);
}

AttrList const& AttrGroup::atNamed(Str const& index) const {
    return this->named.at(index);
}

Opt<AttrList> AttrGroup::getNamed(Str const& index) const {
    return this->named.get(index);
}

AttrValue const& AttrGroup::atFirstNamed(Str const& index) const {
    return this->named.at(index).items.at(0);
}

Opt<AttrValue> AttrGroup::getFirstNamed(Str const& index) const {
    if (named.contains(index)) {
        return this->named.at(index).items.get(0);
    } else {
        return std::nullopt;
    }
}

org::sem::AttrList AttrGroup::getAll() const {
    AttrList result;
    for (auto const& it : positional.items) { result.items.push_back(it); }

    for (auto const& key : sorted(named.keys())) {
        for (auto const& it : named.at(key).items) {
            result.items.push_back(it);
        }
    }

    return result;
}

AttrList AttrGroup::atVarNamed(Str const& index) const {
    AttrList result;
    for (auto const& it : positional.items) {
        if (it.varname && it.varname.value() == index) {
            result.items.push_back(it);
        }
    }

    for (auto const& key : sorted(named.keys())) {
        for (auto const& it : named.at(key).items) {
            if (it.varname && it.varname.value() == index) {
                result.items.push_back(it);
            }
        }
    }

    return result;
}

Opt<AttrList> AttrGroup::getVarNamed(Str const& index) const {
    auto list = atVarNamed(index);
    if (list.items.empty()) {
        return std::nullopt;
    } else {
        return list;
    }
}

AttrValue AttrGroup::atFirstVarNamed(Str const& index) const {
    auto list = atVarNamed(index);
    return list.items.at(0);
}

Opt<AttrValue> AttrGroup::getFirstVarNamed(Str const& index) const {
    auto list = atVarNamed(index);
    return list.items.get(0);
}

void AttrGroup::setNamedAttr(Str const& key, Vec<AttrValue> const& attr) {
    named.insert_or_assign(normalize(key), AttrList{.items = attr});
}

void AttrGroup::setPositionalAttr(Vec<AttrValue> const& attr) {
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

Vec<HashTagFlat> HashTagText::getFlatHashes(bool withIntermediate) const {
    using Res = Vec<HashTagFlat>;
    Func<Res(Vec<Str> const& parents, HashTagText const& tag)> aux;
    UnorderedSet<Vec<Str>>                                     visited;
    aux = [&](Vec<Str> const& parents, HashTagText const& tag) -> Res {
        Res result;
        if (withIntermediate && !parents.empty()
            && !visited.contains(parents)) {
            result.push_back(HashTagFlat{parents});
            visited.incl(parents);
        }
        if (tag.subtags.empty()) {
            result.push_back(HashTagFlat{parents});
            result.back().tags.push_back(tag.head);
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
    auto pk = getKind();
    if (pk == Property::Kind::CustomRaw) {
        return normalize(getCustomRaw().name) == normalize(kind);
    } else if (pk == Property::Kind::CustomArgs) {
        return normalize(getCustomArgs().name) == normalize(kind);
    } else if (
        pk == Property::Kind::CustomSubtreeJson
        && normalize(kind) == normalize("propjson")) {
        return !subkind.has_value()
            || normalize(getCustomSubtreeJson().name)
                   == normalize(subkind.value());
    } else if (
        pk == Property::Kind::CustomSubtreeFlags
        && normalize(kind) == normalize("propargs")) {
        return !subkind.has_value()
            || normalize(getCustomSubtreeFlags().name)
                   == normalize(subkind.value());
    } else if (normalize(fmt1(pk)) == normalize(kind)) {
        return true;
    } else if (
        pk == Property::Kind::ExportOptions && subkind
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

Vec<SemId<Org>> Org::getAllSubnodes() const {
    Vec<SemId<Org>> result;
    // for (auto const& )
    this->visit([&]<IsOrg T>(T const* node) {
        for_each_field_value_with_bases<T>(
            *node,
            overloaded{
                [&]<typename K, typename F>(
                    char const* name, UnorderedMap<K, F> const& values) {
                    for (auto const& [key, value] : values) {
                        result.push_back(value);
                    }
                },
                [&]<typename F>(
                    char const* name, Vec<SemId<F>> const& items) {
                    for (auto const& it : items) {
                        result.push_back(it.asOrg());
                    }
                },
                [&]<typename F>(char const* name, SemId<F> const& id) {
                    result.push_back(id.asOrg());
                },
                [&]<typename F>(char const* name, F const& value) {},
            });
    });


    return result;
}

Str AttrValue::getString() const { return getTextValue().value; }

Opt<double> AttrValue::getDouble() const {
    try {
        return getString().toDouble();
    } catch (std::invalid_argument const& e) { return std::nullopt; }
}

Opt<bool> AttrValue::getBool() const {
    auto const& v = getString();
    if (v == "yes" || v == "true" || v == "on" || v == "t") {
        return true;
    } else if (v == "no" || v == "false" || v == "nil" || v == "off") {
        return false;
    } else {
        return std::nullopt;
    }
}

Opt<int> AttrValue::getInt() const {
    try {
        return getString().toInt();
    } catch (std::invalid_argument const& e) { return std::nullopt; }
}

hstd::Opt<org::sem::OrgCodeEvalInput::Var> org::sem::OrgCodeEvalInput::
    getVariable(hstd::Str const& name) const {
    for (auto const& var : argList) {
        if (var.name == name) { return var; }
    }
    return std::nullopt;
}
