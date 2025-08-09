#pragma once

#include <vector>
#include <QString>

struct DiagramNode {
    std::vector<DiagramNode*> children{};
    DiagramNode*              parent{nullptr};
    QString                   name{};
    bool                      TraceState = false;

    DiagramNode(const QString& nodeName = "Node") : name{nodeName} {}
    virtual ~DiagramNode() = default;

    void addChild(DiagramNode* child) {
        child->parent = this;
        children.push_back(child);
    }

    virtual bool isVisual() const { return false; }
    virtual bool isCanvas() const { return false; }
    virtual bool isLayer() const { return false; }
};

struct DiagramNodeCanvas : public DiagramNode {
    DiagramNodeCanvas(const QString& nodeName = "Canvas")
        : DiagramNode{nodeName} {}
    bool isCanvas() const override { return true; }
};

struct DiagramNodeLayer : public DiagramNode {
    DiagramNodeLayer(const QString& nodeName = "Layer")
        : DiagramNode{nodeName} {}
    bool isLayer() const override { return true; }
};
