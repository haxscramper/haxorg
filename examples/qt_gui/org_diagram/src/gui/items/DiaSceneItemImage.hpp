#pragma once

#include "DiaSceneItemVisual.hpp"
#include <QPixmap>
#include <QPointF>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>


struct DiaSceneItemImage : public DiaSceneItemVisual {
    QPixmap image{};
    bool    isResizing{false};
    QPointF lastMousePos{};

    DiaSceneItemImage(DiaAdapter const& adapter)
        : DiaSceneItemVisual{adapter} {
        bounds = QRectF{0, 0, 100, 100};
    }

    QRectF getResizeHandle() const {
        if (image.isNull()) { return QRectF{}; }
        return QRectF{bounds.right() - 8, bounds.bottom() - 8, 8, 8};
    }

    QRectF getAdditionalBounds() const override {
        if (!image.isNull()) { return getResizeHandle(); }
        return QRectF{};
    }

    QWidget* createPropertiesWidget(QWidget* parent) override {
        auto widget = new QWidget{parent};
        auto layout = new QVBoxLayout{widget};

        layout->addWidget(new QLabel{"Image Properties"});

        auto nameEdit = new QLineEdit{name};
        layout->addWidget(new QLabel{"Name:"});
        layout->addWidget(nameEdit);

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

        auto changeImageButton = new QPushButton{"Change Image"};
        layout->addWidget(changeImageButton);

        QObject::connect(
            nameEdit,
            &QLineEdit::textChanged,
            widget,
            [this](const QString& text) {
                name = text;
                update();
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

        QObject::connect(
            changeImageButton, &QPushButton::clicked, widget, [this]() {
                QString fileName = QFileDialog::getOpenFileName(
                    nullptr,
                    "Open Image",
                    "",
                    "Images (*.png *.jpg *.jpeg *.bmp)");
                if (!fileName.isEmpty()) {
                    setImage(QPixmap{fileName}.scaled(
                        static_cast<int>(bounds.width()),
                        static_cast<int>(bounds.height()),
                        Qt::KeepAspectRatio));
                }
            });

        layout->addStretch();
        return widget;
    }


    void paintNode(QPainter* painter) override {
        if (!image.isNull()) {
            painter->drawPixmap(bounds.toRect(), image);

            painter->setPen(QPen{Qt::blue, 1});
            painter->setBrush(QBrush{Qt::blue});
            painter->drawRect(getResizeHandle());
        } else {
            painter->setPen(QPen{Qt::black, 2});
            painter->setBrush(QBrush{Qt::lightGray});
            painter->drawRect(bounds);
        }
    }

    bool handleMousePress(QGraphicsSceneMouseEvent* event) override {
        if (!image.isNull() && getResizeHandle().contains(event->pos())) {
            isResizing   = true;
            lastMousePos = event->pos();
            setCursor(Qt::SizeFDiagCursor);
            return true;
        }

        setCursor(Qt::ArrowCursor);
        return false;
    }

    bool handleMouseMove(QGraphicsSceneMouseEvent* event) override {
        if (isResizing && !image.isNull()) {
            QPointF delta     = event->pos() - lastMousePos;
            qreal   newWidth  = bounds.width() + delta.x();
            qreal   newHeight = bounds.height() + delta.y();

            if (newWidth >= 20 && newHeight >= 20) {
                bounds.setSize(QSizeF{newWidth, newHeight});
                lastMousePos = event->pos();
                update();
            }
            return true;
        }

        return false;
    }

    void handleMouseRelease(QGraphicsSceneMouseEvent* event) override {
        isResizing = false;
        setCursor(Qt::ArrowCursor);
    }

    void setImage(const QPixmap& pixmap) {
        image = pixmap;
        update();
    }
};
