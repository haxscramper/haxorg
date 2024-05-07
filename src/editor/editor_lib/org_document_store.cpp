#include <editor/editor_lib/org_document_store.hpp>
#include <hstd/stdlib/Enumerate.hpp>

sem::SemId<sem::Org> OrgTreeNode::toNode(OrgStore* store) const {
    auto base = store->node(this->boxId);
    if (NestedNodes.contains(base->getKind())) {
        auto result = copy(base);
        result->subnodes.clear();
        for (auto const& it : enumerator(subnodes)) {
            auto it_node = store->node(it.value()->boxId);
            result->subnodes.push_back(it.value()->toNode(store));
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


void OrgTreeNode::buildTree(OrgTreeNode* parentNode, OrgStore* store) {
    auto const& node = store->node(parentNode->boxId);
    if (NestedNodes.contains(node->getKind())) {
        for (auto& sub : node->subnodes) {
            if (!sub->is(OrgSemKind::Newline)) {
                parentNode->subnodes.push_back(
                    std::make_unique<OrgTreeNode>(
                        store->add(sub), parentNode));
                buildTree(parentNode->subnodes.back().get(), store);
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
