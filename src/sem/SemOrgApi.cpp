#include <sem/SemOrg.hpp>

using namespace sem;
using osk      = OrgSemKind;
using Property = Subtree::Property;

template <>
sem::Subtree::Period::Kind low() {
    return sem::Subtree::Period::Kind::Clocked;
}

template <>
sem::Subtree::Period::Kind high() {
    return sem::Subtree::Period::Kind::Repeated;
}

OrgVariant asVariant(Ptr<Org> org) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return org->as<__Kind>();

    switch (org->getKind()) { EACH_SEM_ORG_KIND(__case) }

#undef __case
}

Vec<Org*> Org::getParentChain(bool withSelf) const {
    Vec<Org*> result;

    Org const* now = withSelf ? this : getParent();

    while (now != nullptr) {
        result.push_back(const_cast<Org*>(now));
        now = now->getParent();
    }

    return result;
}


Opt<Wrap<Document>> Org::getDocument() const {
    for (const auto& item : getParentChain()) {
        if (item->getKind() == OrgSemKind::Document) {
            return item->as<Document>();
        }
    }
    return std::nullopt;
}

Opt<Wrap<Subtree>> Org::getParentSubtree() const {
    for (const auto& item : getParentChain()) {
        if (item->getKind() == OrgSemKind::Subtree) {
            return item->as<Subtree>();
        }
    }
    return std::nullopt;
}

Vec<Subtree::Period> Subtree::getTimePeriods(IntSet<Period::Kind> kinds) {
    Vec<Period> res;
    for (const auto& it : title->subnodes) {
        if (it->getKind() == osk::Time) {
            res.push_back(Period(it->as<Time>(), Period::Kind::Titled));
        } else if (it->getKind() == osk::TimeRange) {
            res.push_back(
                Period(it->as<TimeRange>(), Period::Kind::Titled));
        }
    }

    for (const auto& prop : properties) {
        std::visit(
            overloaded{
                [&](Property::Created const& cr) {
                    res.push_back(Period(
                        std::make_shared<Time>(cr.time),
                        Period::Kind::Created));
                },
                [](auto const&) {}},
            prop.data);
    }


    return res;
}

Vec<Property> Subtree::getProperties(
    Property::Kind kind,
    CR<QString>    subkind) const {
    Vec<Property> result;
    for (const auto& prop : properties) {
        if (prop.getKind() == kind) {
            result.push_back(prop);
        } else if (
            prop.getKind() == Property::Kind::ExportOptions
            && normalize(prop.getExportOptions().backend)
                   == normalize(subkind)) {
            result.push_back(prop);
        }
    }
    return result;
}

Vec<Property> Subtree::getContextualProperties(
    Property::Kind kind,
    CR<QString>    subkind) const {
    Subtree const* now = this;
    Vec<Property>  result;
    while (now != nullptr) {
        result.append(now->getProperties(kind));
        if (auto sup = now->getParentSubtree()) {
            now = sup.value().get();
        } else {
            now = nullptr;
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bool HashTag::prefixMatch(CR<Vec<Str>> prefix) const {
    if (prefix.empty() || (prefix.size() == 1 && prefix[0] == head)) {
        return true;
    } else if (prefix[0] != head) {
        return false;
    } else {
        Vec<Str> tmp;
        for (const auto& it : prefix[slice(1, 1_B)]) {
            tmp.push_back(it);
        }

        for (const auto& sub : subtags) {
            if (sub->prefixMatch(tmp)) {
                return true;
            }
        }
        return false;
    }
}

Opt<Property> Subtree::getContextualProperty(
    Property::Kind kind,
    CR<QString>    subkind) const {
    Vec<Property> props = getContextualProperties(kind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        switch (props[0].getKind()) {
            case Property::Kind::Nonblocking:
            case Property::Kind::Unnumbered:
            case Property::Kind::Ordered:
            case Property::Kind::Created: return props[0];
            case Property::Kind::ExportOptions: {
                Property::ExportOptions res;
                for (const auto& it : props) {
                    Property::ExportOptions const& tmp = it.getExportOptions();
                    for (auto const& [k, v] : tmp.values) {
                        if (!res.values.contains(k)) {
                            res.values[k] = v;
                        }
                    }
                }
                return Property(res);
            }
        }
    }
}

Opt<Property> Subtree::getProperty(
    Property::Kind kind,
    CR<QString>    subkind) const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}
