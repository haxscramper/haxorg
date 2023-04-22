#include <sem/SemOrg.hpp>

using namespace sem;
using osk  = OrgSemKind;
using Prop = Subtree::Properties;

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
                [&](Prop::Created const& cr) {
                    res.push_back(Period(
                        std::make_shared<Time>(cr.time),
                        Period::Kind::Created));
                },
                [](auto const&) {}},
            prop);
    }


    return res;
}

Vec<Prop::Property> Subtree::getProperties(
    Prop::PropertyKind kind,
    CR<QString>        subkind) const {
    Vec<Prop::Property> result;
    for (const auto& prop : properties) {
        std::visit(
            overloaded{
                [&](Prop::ExportOptions& it) {
                    if (it.getKind() == kind
                        && normalize(it.backend) == normalize(subkind)) {
                        result.push_back(prop);
                    }
                },
                [&](auto const& it) {
                    if (it.getKind() == kind) {
                        result.push_back(prop);
                    }
                }},
            prop);
    }
    return result;
}

Vec<Prop::Property> Subtree::getContextualProperties(
    Prop::PropertyKind kind,
    CR<QString>        subkind) const {
    Subtree const*      now = this;
    Vec<Prop::Property> result;
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

Opt<Prop::Property> Subtree::getContextualProperty(
    Prop::PropertyKind kind,
    CR<QString>        subkind) const {
    Vec<Prop::Property> props = getContextualProperties(kind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        switch (Prop::kind(props[0])) {
            case PropKind::Nonblocking:
            case PropKind::Unnumbered:
            case PropKind::Ordered:
            case PropKind::Created: return props[0];
            case PropKind::ExportOptions: {
                Prop::ExportOptions res;
                for (const auto& it : props) {
                    Prop::ExportOptions const& tmp = Properties::as<
                        Prop::ExportOptions>(it);
                    for (auto const& [k, v] : tmp.values) {
                        if (!res.values.contains(k)) {
                            res.values[k] = v;
                        }
                    }
                }
                return res;
            }
        }
    }
}

Opt<Prop::Property> Subtree::getProperty(
    Prop::PropertyKind kind,
    CR<QString>        subkind) const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}
