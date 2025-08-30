#pragma once

#include <vector>
#include <QString>

struct DiagramSceneItem {
    std::vector<DiagramSceneItem*> children{};
    DiagramSceneItem*              parent{nullptr};
    QString                        name{};
    bool                           TraceState = false;

    DiagramSceneItem(const QString& nodeName = "Node") : name{nodeName} {}
    virtual ~DiagramSceneItem() = default;

    void addChild(DiagramSceneItem* child) {
        child->parent = this;
        children.push_back(child);
    }
};

struct DiagramNodeCanvas : public DiagramSceneItem {
    DiagramNodeCanvas(const QString& nodeName = "Canvas")
        : DiagramSceneItem{nodeName} {}
};

struct DiagramNodeLayer : public DiagramSceneItem {
    DiagramNodeLayer(const QString& nodeName = "Layer")
        : DiagramSceneItem{nodeName} {}
};
