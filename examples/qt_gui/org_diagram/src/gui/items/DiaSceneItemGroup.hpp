#pragma once
#include <QColor>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

#include "DiaSceneItemVisual.hpp"

struct DiaSceneItemGroup : public DiaSceneItemVisual {
    QColor                           groupColor{Qt::lightGray};
    std::vector<DiaSceneItemVisual*> groupedNodes{};

    DiaSceneItemGroup(const QString& nodeName = "Group")
        : DiaSceneItemVisual{nodeName} {
        bounds = QRectF{0, 0, 200, 150};
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setZValue(-1);
    }

    void addToGroup(DiaSceneItemVisual* node) {
        if (node
            && std::find(groupedNodes.begin(), groupedNodes.end(), node)
                   == groupedNodes.end()) {
            groupedNodes.push_back(node);
            updateBoundsToFitNodes();
        }
    }

    void removeFromGroup(DiaSceneItemVisual* node) {
        auto it = std::find(
            groupedNodes.begin(), groupedNodes.end(), node);
        if (it != groupedNodes.end()) {
            groupedNodes.erase(it);
            updateBoundsToFitNodes();
        }
    }

    void updateBoundsToFitNodes() {
        if (groupedNodes.empty()) { return; }

        QRectF combinedBounds;
        bool   first = true;

        for (auto node : groupedNodes) {
            QRectF nodeBounds = node->boundingRect().translated(
                node->pos());
            if (first) {
                combinedBounds = nodeBounds;
                first          = false;
            } else {
                combinedBounds = combinedBounds.united(nodeBounds);
            }
        }

        bounds = combinedBounds.adjusted(-10, -10, 10, 10);
        setPos(0, 0);
        update();
    }

    void paintNode(QPainter* painter) override {
        painter->setPen(QPen{Qt::darkGray, 2, Qt::DashLine});
        painter->setBrush(QBrush{groupColor, Qt::SolidPattern});
        painter->setOpacity(0.3);
        painter->drawRect(bounds);
        painter->setOpacity(1.0);
    }

    QWidget* createPropertiesWidget(QWidget* parent) override {
        auto widget = new QWidget{parent};
        auto layout = new QVBoxLayout{widget};

        layout->addWidget(new QLabel{"Group Properties"});

        auto nameEdit = new QLineEdit{name};
        layout->addWidget(new QLabel{"Name:"});
        layout->addWidget(nameEdit);

        auto colorButton = new QPushButton{"Change Color"};
        colorButton->setStyleSheet(
            QString{"background-color: %1"}.arg(groupColor.name()));
        layout->addWidget(new QLabel{"Color:"});
        layout->addWidget(colorButton);

        auto nodeCountLabel = new QLabel{
            QString{"Nodes: %1"}.arg(groupedNodes.size())};
        layout->addWidget(nodeCountLabel);

        QObject::connect(
            nameEdit,
            &QLineEdit::textChanged,
            widget,
            [this](const QString& text) {
                name = text;
                update();
            });

        QObject::connect(
            colorButton,
            &QPushButton::clicked,
            widget,
            [this, colorButton]() {
                QColor newColor = QColorDialog::getColor(groupColor);
                if (newColor.isValid()) {
                    groupColor = newColor;
                    colorButton->setStyleSheet(
                        QString{"background-color: %1"}.arg(
                            newColor.name()));
                    update();
                }
            });

        layout->addStretch();
        return widget;
    }

    QVariant itemChange(GraphicsItemChange change, const QVariant& value)
        override {
        if (change == ItemPositionHasChanged) {
            updateConnectedEdges();
            // Move grouped nodes with the group
            QPointF delta = pos() - lastPos;
            for (auto node : groupedNodes) {
                node->setPos(node->pos() + delta);
            }
            lastPos = pos();
        }
        return DiaSceneItemVisual::itemChange(change, value);
    }

  private:
    QPointF lastPos{};
};
