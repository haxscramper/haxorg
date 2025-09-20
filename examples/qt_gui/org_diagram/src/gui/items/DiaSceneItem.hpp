#pragma once

#include <src/model/nodes/DiagramTreeNode.hpp>
#include <qgraphicsitem.h>
#include <vector>
#include <QString>
#include <haxorg/sem/ImmOrg.hpp>
#include <QGraphicsItem>

struct DiaSceneItem;

struct SelfRemDiaScene {
    void operator()(DiaSceneItem* item);
};

struct DiaSceneItem : public QGraphicsItem {
    using UPtr = std::unique_ptr<DiaSceneItem, SelfRemDiaScene>;
    QString    name{};
    bool       TraceState = false;
    DiaAdapter staleAdapter;

    bool hasParent() const { return parent != nullptr; }

    QRectF boundingRect() const override { return QRectF{}; }
    void   paint(
          QPainter*                       _painter,
          const QStyleOptionGraphicsItem* option,
          QWidget*                        widget) override {}

    virtual hstd::Vec<hstd::ColText> formatSelf() const {
        return {hstd::ColText{"DiaSceneItem " + name.toStdString()}};
    }

    org::imm::ImmPathStep getRelativeToParent() const {
        return staleAdapter.id.path.path.back();
    }

    template <typename T>
    bool isinstance() const {
        return dynamic_cast<T const*>(this) != nullptr;
    }

    struct TreeReprConf {};

    hstd::ColText treeRepr() const { return treeRepr(TreeReprConf{}); }
    hstd::ColText treeRepr(TreeReprConf const& conf) const;

    hstd::Vec<int> getParentPathFromRoot() const {
        if (parent == nullptr) {
            return {};
        } else {
            return parent->getSelfPathFromRoot();
        }
    }

    hstd::Vec<int> getSelfPathFromRoot() const {
        auto active = getActivePath();
        return asIndexPath(active);
    }

    org::imm::ImmPath getActivePath() const;

    DiaAdapter getActiveAdapter() const {
        return DiaAdapter{
            DiaUniqId{staleAdapter.id.id, getActivePath()},
            staleAdapter.ctx};
    }


    DiaId getDiaId() const {
        hstd::logic_assertion_check_not_nil(staleAdapter.id.id);
        return staleAdapter.id.id;
    }

    DiaSceneItem* at(int pos) { return subnodes.at(pos).get(); }
    int           size() const { return subnodes.size(); }

    DiaSceneItem* getItemAtPath(hstd::Vec<int> const& path) const {
        DiaSceneItem* res = const_cast<DiaSceneItem*>(this);
        for (auto const& it : path) { res = res->at(it); }
        hstd::logic_assertion_check_not_nil(res);
        return res;
    }

    DiaSceneItem(DiaAdapter const& staleAdapter)
        : staleAdapter{staleAdapter} {}

    virtual ~DiaSceneItem() = default;

    template <typename T>
    void add(std::unique_ptr<T, SelfRemDiaScene>&& sub) {
        sub->parent = this;
        subnodes.emplace_back(
            hstd::dynamic_pointer_cast<DiaSceneItem>(std::move(sub)));
    }

    void add(DiaSceneItem::UPtr&& child) {
        child->parent = this;
        subnodes.emplace_back(std::move(child));
    }

    void insertSubnode(UPtr&& node, int pos) {
        subnodes.insert(subnodes.begin() + pos, std::move(node));
    }

    void setSubnodes(std::vector<UPtr>&& nodes) {
        subnodes = std::move(nodes);
        for (auto const& sub : subnodes) { sub->parent = this; }
    }

    void setSubnode(UPtr&& node, int pos) {
        subnodes[pos] = std::move(node);
    }

    void removeSubnode(int pos) { subnodes.erase(subnodes.begin() + pos); }

    UPtr* getMutableUPtr(int pos) { return &subnodes.at(pos); }

    std::vector<UPtr>        moveSubnodes() { return std::move(subnodes); }
    std::vector<UPtr> const& getSubnodes() const { return subnodes; }

    void moveSubnode(int srcIndex, int dstIndex) {
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

    DiaSceneItem* getParent();

  private:
    std::vector<UPtr> subnodes{};
    DiaSceneItem*     parent{nullptr};
};

struct DiaSceneItemCanvas
    : public DiaSceneItem
    , public hstd::SharedPtrApiDerived<DiaSceneItemCanvas, DiaSceneItem> {
    DiaSceneItemCanvas(DiaAdapter const& staleAdapter)
        : DiaSceneItem{staleAdapter} {}

    hstd::Vec<hstd::ColText> formatSelf() const override {
        return {hstd::ColText{"DiaSceneItemCanvas " + name.toStdString()}};
    }
};

struct DiaSceneItemLayer : public DiaSceneItem {
    DiaSceneItemLayer(DiaAdapter const& staleAdapter)
        : DiaSceneItem{staleAdapter} {}

    hstd::Vec<hstd::ColText> formatSelf() const override {
        return {hstd::ColText{"DiaSceneItemLayer " + name.toStdString()}};
    }
};
