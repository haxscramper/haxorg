#pragma once

#include <src/model/nodes/DiagramTreeNode.hpp>
#include <qgraphicsitem.h>
#include <vector>
#include <QString>
#include <haxorg/sem/ImmOrg.hpp>

struct DiaSceneItem {
    std::vector<DiaSceneItem*> subnodes{};
    DiaSceneItem*              parent{nullptr};
    QString                    name{};
    bool                       TraceState = false;

    org::imm::ImmPathStep getRelativeToParent() const {
        return staleAdapter.id.path.path.back();
    }

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

    DiaSceneItem* getItemAtPath(hstd::Vec<int> const& path) const {
        DiaSceneItem* res = const_cast<DiaSceneItem*>(this);
        for (auto const& it : path) { res = res->subnodes.at(it); }
        return res;
    }

    DiaSceneItem(const QString& nodeName = "Node") : name{nodeName} {}
    virtual ~DiaSceneItem() = default;

    void addChild(DiaSceneItem* child) {
        child->parent = this;
        subnodes.push_back(child);
    }
};

struct DiaSceneItemCanvas : public DiaSceneItem {
    DiaSceneItemCanvas(const QString& nodeName = "Canvas")
        : DiaSceneItem{nodeName} {}
};

struct DiaSceneItemLayer : public DiaSceneItem {
    DiaSceneItemLayer(const QString& nodeName = "Layer")
        : DiaSceneItem{nodeName} {}
};
