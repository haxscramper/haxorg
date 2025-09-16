#include "DiaSceneItem.hpp"

org::imm::ImmPath DiaSceneItem::getActivePath() const {
    if (parent == nullptr) {
        return org::imm::ImmPath{staleAdapter.get()->id.id};
    } else {
        org::imm::ImmPath::Store result;
        auto                     result_transient = result.transient();
        DiaSceneItem*            tmp              = parent;
        DiaSceneItem*            root             = parent;
        while (tmp != nullptr) {
            result_transient.push_back(tmp->getRelativeToParent());
            if (tmp->parent == nullptr) {
                tmp = tmp->parent;
            } else {
                tmp  = tmp->parent;
                root = tmp->parent;
            }
        }
        return org::imm::ImmPath{
            root->staleAdapter.get()->id.id,
            result_transient.persistent()};
    }
}
