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

Vec<Prop::Property> Subtree::getProperties(Prop::PropertyKind kind) const {
    Vec<Prop::Property> result;
    for (const auto& prop : properties) {
        std::visit(
            [&](auto const& it) {
                if (it.getKind() == kind) {
                    result.push_back(prop);
                }
            },
            prop);
    }
    return result;
}

Opt<Prop::Property> Subtree::getProperty(Prop::PropertyKind kind) const {
    auto props = getProperties(kind);
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
