#include <editor/editor_lib/store/org_document_store.hpp>
#include <hstd/stdlib/Enumerate.hpp>

sem::SemId<sem::Org> OrgTreeNode::getBoxedNode() const {
    return store->getBoxedNode(this->boxId);
}

OrgTreeNode* OrgTreeNode::tree(OrgBoxId id) {
    return store->getOrgTree(id);
}

sem::SemId<sem::Org> OrgTreeNode::toNode() const {
    auto base = store->getBoxedNode(this->boxId);
    if (NestedNodes.contains(base->getKind())) {
        auto result = copy(base);
        result->subnodes.clear();
        for (auto const& it : enumerator(subnodes)) {
            Q_ASSERT(it.value() != nullptr);
            Q_ASSERT(store != nullptr);
            auto it_node = store->getBoxedNode(it.value()->boxId);
            result->subnodes.push_back(it.value()->toNode());
            if (!it.is_last()) {
                if (it_node->is(OrgSemKind::Paragraph)) {
                    auto nl  = sem::SemId<sem::Newline>::New();
                    nl->text = "\n\n";
                    result->subnodes.push_back(nl);
                }
            }
        }
        return result;
    } else {
        return base;
    }
}


void OrgTreeNode::buildTree(OrgTreeNode* parentNode) {
    auto const& node = store->getBoxedNode(parentNode->boxId);
    store->nodeLookup[parentNode->boxId] = parentNode;
    if (NestedNodes.contains(node->getKind())) {
        for (auto& sub : node->subnodes) {
            if (!sub->is(OrgSemKind::Newline)) {
                parentNode->subnodes.push_back(
                    store->addTree(store->add(sub), parentNode));
                buildTree(parentNode->subnodes.back().get());
            }
        }
    }
}

Opt<int> OrgTreeNode::selfRow() const {
    if (parent) {
        return std::find_if(
                   parent->subnodes.begin(),
                   parent->subnodes.end(),
                   [&](CR<UPtr<OrgTreeNode>> node) {
                       return node.get() == this;
                   })
             - parent->subnodes.begin();
    } else {
        return std::nullopt;
    }
}

Vec<int> OrgTreeNode::selfPath() const {
    Vec<int>           result;
    OrgTreeNode const* tmp = this;
    while (tmp->parent != nullptr) {
        if (Opt<int> idx = tmp->selfRow()) {
            result.push_back(idx.value());
        }
        tmp = tmp->parent;
    }

    rs::reverse(result);
    return result;
}


sem::SemId<sem::Org> OrgStore::nodeWithoutNested(CR<OrgBoxId> id) const {
    return nodeWithoutNested(getBoxedNode(id));
}

sem::SemId<sem::Org> OrgStore::nodeWithoutNested(
    CR<sem::SemId<sem::Org>> id) const {
    auto result = copy(id);
    if (NestedNodes.contains(result->getKind())) {
        result->subnodes.clear();
    }
    return result;
}
