#include <sem/SemOrg.hpp>

using namespace sem;


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
