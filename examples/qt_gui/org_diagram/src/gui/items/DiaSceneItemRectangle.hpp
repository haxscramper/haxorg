#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QColorDialog>
#include <QPainter>
#include <src/gui/items/DiaSceneItemVisual.hpp>

struct DiaSceneItemRectangle : public DiaSceneItemVisual {
    QColor color{Qt::blue};

    DiaSceneItemRectangle(DiaAdapter const& staleAdapter)
        : DiaSceneItemVisual{staleAdapter} {
        bounds = QRectF{0, 0, 100, 60};
    }

    QRectF boundingRect() const override {
        QRectF rect = bounds;
        rect        = rect.united(getAdditionalBounds());
        return rect.adjusted(-5, -5, 15, 15);
    }

    QWidget* createPropertiesWidget(QWidget* parent) override;

    void paintNode(QPainter* painter) override {
        painter->setPen(QPen{Qt::black, 2});
        painter->setBrush(QBrush{color});
        painter->drawRect(bounds);
    }

    void paint(
        QPainter*                       painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        paintNode(painter);

        if (isSelected()) {
            painter->setPen(QPen{Qt::red, 3});
            painter->drawRect(bounds);
        }

        paintText(painter);
    }
};
