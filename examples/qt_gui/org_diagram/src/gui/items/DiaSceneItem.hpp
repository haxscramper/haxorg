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
    DiaSceneItem* parent{nullptr};
    QString       name{};
    bool          TraceState = false;

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

    DiaAdapter staleAdapter;

    DiaSceneItem* at(int pos) { return subnodes.at(pos).get(); }
    int           size() const { return subnodes.size(); }

    DiaSceneItem* getItemAtPath(hstd::Vec<int> const& path) const {
        DiaSceneItem* res = const_cast<DiaSceneItem*>(this);
        for (auto const& it : path) { res = res->at(it); }
        return res;
    }

    DiaSceneItem(const QString& nodeName = "Node") : name{nodeName} {}
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

    void setSubnodes(std::vector<UPtr>&& nodes) {
        subnodes = std::move(nodes);
        for (auto const& sub : subnodes) { sub->parent = this; }
    }

    void setSubnode(UPtr&& node, int pos) {
        subnodes[pos] = std::move(node);
    }

    void removeSubnode(int pos) { subnodes.erase(subnodes.begin() + pos); }

    std::vector<UPtr>        moveSubnodes() { return std::move(subnodes); }
    std::vector<UPtr> const& getSubnodes() const { return subnodes; }

  private:
    std::vector<UPtr> subnodes{};
};

struct DiaSceneItemCanvas
    : public DiaSceneItem
    , public hstd::SharedPtrApiDerived<DiaSceneItemCanvas, DiaSceneItem> {
    DiaSceneItemCanvas(const QString& nodeName = "Canvas")
        : DiaSceneItem{nodeName} {}

    hstd::Vec<hstd::ColText> formatSelf() const override {
        return {hstd::ColText{"DiaSceneItemCanvas " + name.toStdString()}};
    }
};

struct DiaSceneItemLayer : public DiaSceneItem {
    DiaSceneItemLayer(const QString& nodeName = "Layer")
        : DiaSceneItem{nodeName} {}

    hstd::Vec<hstd::ColText> formatSelf() const override {
        return {hstd::ColText{"DiaSceneItemLayer " + name.toStdString()}};
    }
};
