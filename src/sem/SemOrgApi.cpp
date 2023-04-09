#include <sem/SemOrg.hpp>

using namespace sem;
using osk  = OrgSemKind;
using Prop = Subtree::Properties;

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

Opt<Wrap<Time>> Subtree::getStart() const {
    if (scheduled) {
        return scheduled;
    } else if (title->at(0)->getKind() == osk::TimeRange) {
        return title->at(0)->as<TimeRange>()->from;
    } else {
        return std::nullopt;
    }
}

Opt<Wrap<Time>> Subtree::getEnd() const {
    if (title->at(0)->getKind() == osk::TimeRange) {
        return title->at(0)->as<TimeRange>()->to;
    } else {
        return std::nullopt;
    }
}
