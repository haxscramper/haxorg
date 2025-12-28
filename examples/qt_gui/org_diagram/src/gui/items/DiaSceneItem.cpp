#include "DiaSceneItem.hpp"
#include <src/gui/DiaScene.hpp>
#include <sanitizer/asan_interface.h>

int DiaSceneItem::getSelfIndex() const {
    LOGIC_ASSERTION_CHECK(hasParent(), "");
    for (int i = 0; i < parent->size(); ++i) {
        if (parent->at(i) == this) { return i; }
    }

    throw hstd::logic_assertion_error::init(
        "parent node node does not contain `this` subnode");
}

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
        return org::imm::ImmPath{adapter->id.id};
    } else {
        hstd::Vec<int>      result;
        DiaSceneItem const* root = this;
        while (root->hasParent()) {
            result.push_back(root->getSelfIndex());
            root = root->parent;
        }
        std::reverse(result.begin(), result.end());
        return toImmPath(root->adapter->id.id, result);
    }
}

hstd::Opt<DiaSceneItem*> DiaSceneItem::getItemAtPath(
    const hstd::Vec<int>& path) const {
    DiaSceneItem* res = const_cast<DiaSceneItem*>(this);
    for (auto const& it : path) {
        if (it < res->size()) {
            res = res->at(it);
        } else {
            return std::nullopt;
        }
    }
    hstd::logic_assertion_check_not_nil(res);
    return res;
}

void DiaSceneItem::moveSubnode(int srcIndex, int dstIndex) {
    if (srcIndex < 0 || subnodes.size() <= srcIndex || dstIndex < 0
        || subnodes.size() <= dstIndex) {
        throw hstd::range_error::init(std::format(
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


        LOGIC_ASSERTION_CHECK_FMT(
            parent != nullptr,
            "Non-root node must have the parent assigned. The node {} "
            "with adapter {}",
            hstd::descObjectPtr(this),
            adapter);

        if (__asan_address_is_poisoned(parent)) {
            __asan_describe_address(parent);
        }
        LOGIC_ASSERTION_CHECK(!__asan_address_is_poisoned(parent), "");
    }
    return parent;
}

void SelfRemDiaScene::operator()(DiaSceneItem* item) {
    item->scene()->removeItem(item);
    HSLOG_TRACE(_cat, "Deleting scene item {}", hstd::descObjectPtr(item));
    delete item;
}
