#pragma once

#include <qgraphicsitem.h>
#include <vector>
#include <QString>

struct DiaSceneItem {
    std::vector<DiaSceneItem*> children{};
    DiaSceneItem*              parent{nullptr};
    QString                    name{};
    bool                       TraceState = false;

    DiaSceneItem(const QString& nodeName = "Node") : name{nodeName} {}
    virtual ~DiaSceneItem() = default;

    void addChild(DiaSceneItem* child) {
        child->parent = this;
        children.push_back(child);
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
