#pragma once

#include "DiagramNodeVisual.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QColorDialog>

struct DiagramNodeRectangle : public DiagramNodeVisual {
    QColor color{Qt::blue};

    DiagramNodeRectangle(const QString& nodeName = "Rectangle")
        : DiagramNodeVisual{nodeName} {
        bounds = QRectF{0, 0, 100, 60};
    }

    QRectF boundingRect() const override {
        QRectF rect = bounds;
        rect        = rect.united(getAdditionalBounds());
        return rect.adjusted(-5, -5, 15, 15);
    }

    QWidget* createPropertiesWidget(QWidget* parent) override {
        auto widget = new QWidget{parent};
        auto layout = new QVBoxLayout{widget};

        layout->addWidget(new QLabel{"Rectangle Properties"});

        auto nameEdit = new QLineEdit{name};
        layout->addWidget(new QLabel{"Name:"});
        layout->addWidget(nameEdit);

        auto colorButton = new QPushButton{"Change Color"};
        colorButton->setStyleSheet(
            std::format("background-color: {}", color.name().toStdString())
                .c_str());
        layout->addWidget(new QLabel{"Color:"});
        layout->addWidget(colorButton);

        auto widthSpin = new QSpinBox{};
        widthSpin->setRange(10, 500);
        widthSpin->setValue(static_cast<int>(bounds.width()));
        layout->addWidget(new QLabel{"Width:"});
        layout->addWidget(widthSpin);

        auto heightSpin = new QSpinBox{};
        heightSpin->setRange(10, 500);
        heightSpin->setValue(static_cast<int>(bounds.height()));
        layout->addWidget(new QLabel{"Height:"});
        layout->addWidget(heightSpin);

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
                QColor newColor = QColorDialog::getColor(color);
                if (newColor.isValid()) {
                    color = newColor;
                    colorButton->setStyleSheet(
                        std::format(
                            "background-color: {}",
                            color.name().toStdString())
                            .c_str());
                    update();
                }
            });

        QObject::connect(
            widthSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            widget,
            [this](int value) {
                bounds.setWidth(value);
                update();
            });

        QObject::connect(
            heightSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            widget,
            [this](int value) {
                bounds.setHeight(value);
                update();
            });

        layout->addStretch();
        return widget;
    }

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
