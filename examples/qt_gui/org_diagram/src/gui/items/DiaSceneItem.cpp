#include "DiaSceneItem.hpp"
#include <src/gui/DiaScene.hpp>
#include <sanitizer/asan_interface.h>

hstd::ColText DiaSceneItem::treeRepr(const TreeReprConf& conf) const {
    hstd::ColStream                               os;
    std::function<void(DiaSceneItem const*, int)> aux;
    aux = [&](DiaSceneItem const* item, int level) {
        for (auto const& line : hstd::enumerator(item->formatSelf())) {
            if (line.is_first()) {
                os << os.indent(level * 2) << line.value();
                if (true) {
                    os << hstd::fmt(
                        " 0x{:X}", reinterpret_cast<uintptr_t>(item));
                }
                if (item->hasParent()) {
                    os << hstd::fmt(" {}", item->getSelfPathFromRoot());
                } else {
                    os << " <no-parent>";
                }
                os << hstd::fmt(" {}", item->getDiaId());
                os << "\n";
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
        return org::imm::ImmPath{staleAdapter->id.id};
    } else {
        hstd::Vec<org::imm::ImmPathStep> result;
        DiaSceneItem const*              root = this;
        while (root->hasParent()) {
            result.push_back(root->getRelativeToParent());
            root = root->parent;
        }
        std::reverse(result.begin(), result.end());
        return org::imm::ImmPath{root->staleAdapter->id.id, result};
    }
}

void DiaSceneItem::moveSubnode(int srcIndex, int dstIndex) {
    if (srcIndex < 0 || subnodes.size() <= srcIndex || dstIndex < 0
        || subnodes.size() <= dstIndex) {
        throw hstd::RangeError::init(std::format(
            "Index out of bounds: src={}, dst={}, size={}",
            srcIndex,
            dstIndex,
            subnodes.size()));
    }

    if (srcIndex == dstIndex) { return; }

    auto temp = std::move(subnodes.at(srcIndex));

    if (srcIndex < dstIndex) {
        for (int i = srcIndex; i < dstIndex; ++i) {
            subnodes.at(i) = std::move(subnodes.at(i + 1));
        }
    } else {
        for (int i = srcIndex; i > dstIndex; --i) {
            subnodes.at(i) = std::move(subnodes.at(i - 1));
        }
    }

    subnodes.at(dstIndex) = std::move(temp);
}

DiaSceneItem* DiaSceneItem::getParent() const {
    if (!isinstance<DiaSceneItemCanvas>()) {
        LOGIC_ASSERTION_CHECK(this != nullptr, "calling on null object");


        LOGIC_ASSERTION_CHECK(
            parent != nullptr,
            "Non-root node must have the parent assigned. The node {} "
            "with adapter {}",
            hstd::descObjectPtr(this),
            staleAdapter);

        if (__asan_address_is_poisoned(parent)) {
            __asan_describe_address(parent);
        }
        LOGIC_ASSERTION_CHECK(!__asan_address_is_poisoned(parent), "");
    }
    return parent;
}

void SelfRemDiaScene::operator()(DiaSceneItem* item) {
    item->scene()->removeItem(item);
    HSLOG_TRACE(
        _cat,
        hstd::fmt("Deleting scene item {}", hstd::descObjectPtr(item)));
    delete item;
}
