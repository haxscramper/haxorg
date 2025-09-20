#include "DiaSceneItem.hpp"
#include <src/gui/DiaScene.hpp>

hstd::ColText DiaSceneItem::treeRepr(const TreeReprConf& conf) const {
    hstd::ColStream                               os;
    std::function<void(DiaSceneItem const*, int)> aux;
    aux = [&](DiaSceneItem const* item, int level) {
        for (auto const& line : hstd::enumerator(item->formatSelf())) {
            if (line.is_first()) {
                os << os.indent(level * 2) << line.value()
                   << hstd::fmt(
                          " 0x{:X}", reinterpret_cast<uintptr_t>(item))
                   << "\n";
            } else {
                os << os.indent(level * 2) << line.value() << "\n";
            }
        }
        for (auto const& sub : item->subnodes) {
            aux(sub.get(), level + 1);
        }
    };

    aux(this, 0);

    return os;
}

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

void SelfRemDiaScene::operator()(DiaSceneItem* item) {
    item->scene()->removeItem(item);
    HSLOG_TRACE(
        _cat,
        hstd::fmt("Deleting scene item {}", hstd::descObjectPtr(item)));
    delete item;
}
