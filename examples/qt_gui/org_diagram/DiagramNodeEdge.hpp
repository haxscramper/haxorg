#pragma once

#include "DiagramNode.hpp"
#include "DiagramNodeVisual.hpp"
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QColorDialog>
#include <QLabel>
#include <QVBoxLayout>

struct DiagramNodeEdge : public DiagramNodeVisual {
    enum EdgeType
    {
        Orthogonal,
        Polyline,
        Bezier
    };

    DiagramNodeVisual*   sourceNode{nullptr};
    DiagramNodeVisual*   targetNode{nullptr};
    QPointF              sourceOffset{0, 0};
    QPointF              targetOffset{0, 0};
    std::vector<QPointF> controlPoints{};
    EdgeType             edgeType{Orthogonal};
    QPen                 edgePen{Qt::black, 2};
    QPainterPath         edgePath{};

    DiagramNodeEdge(
        DiagramNodeVisual* source,
        DiagramNodeVisual* target,
        const QString&     nodeName = "Edge")
        : DiagramNodeVisual{nodeName}
        , sourceNode{source}
        , targetNode{target} {
        setFlag(QGraphicsItem::ItemIsMovable, false);
        updateBounds();
    }

    QPointF getSourcePoint() const {
        if (!sourceNode) { return QPointF{}; }
        return sourceNode->pos() + sourceNode->bounds.center()
             + sourceOffset;
    }

    QPointF getTargetPoint() const {
        if (!targetNode) { return QPointF{}; }
        return targetNode->pos() + targetNode->bounds.center()
             + targetOffset;
    }

    QPainterPath shape() const override {
        QPainterPath path;
        if (!sourceNode || !targetNode) { return path; }

        QPointF source = getSourcePoint();
        QPointF target = getTargetPoint();

        QPainterPathStroker stroker;
        stroker.setWidth(10);

        switch (edgeType) {
            case Orthogonal: {
                QPainterPath edgePath;
                QPointF      mid{target.x(), source.y()};
                edgePath.moveTo(source);
                edgePath.lineTo(mid);
                edgePath.lineTo(target);
                path = stroker.createStroke(edgePath);
                break;
            }
            case Polyline: {
                QPainterPath edgePath;
                edgePath.moveTo(source);
                if (controlPoints.empty()) {
                    edgePath.lineTo(target);
                } else {
                    for (const auto& point : controlPoints) {
                        edgePath.lineTo(point);
                    }
                    edgePath.lineTo(target);
                }
                path = stroker.createStroke(edgePath);
                break;
            }
            case Bezier: {
                QPainterPath edgePath;
                edgePath.moveTo(source);
                if (controlPoints.size() >= 2) {
                    for (int i = 0;
                         i < static_cast<int>(controlPoints.size()) - 1;
                         i += 2) {
                        QPointF cp1 = controlPoints.at(i);
                        QPointF cp2 = (i + 1 < static_cast<int>(
                                           controlPoints.size()))
                                        ? controlPoints.at(i + 1)
                                        : target;
                        QPointF end = (i + 2 < static_cast<int>(
                                           controlPoints.size()))
                                        ? controlPoints.at(i + 2)
                                        : target;
                        edgePath.cubicTo(cp1, cp2, end);
                    }
                } else {
                    QPointF cp1 = source + QPointF{50, 0};
                    QPointF cp2 = target - QPointF{50, 0};
                    edgePath.cubicTo(cp1, cp2, target);
                }
                path = stroker.createStroke(edgePath);
                break;
            }
        }

        return path;
    }

    void updateBounds() {
        if (!sourceNode || !targetNode) { return; }

        QPointF source = getSourcePoint();
        QPointF target = getTargetPoint();

        QRectF newBounds{source, target};
        for (const auto& point : controlPoints) {
            newBounds = newBounds.united(QRectF{point, point});
        }

        bounds = newBounds.normalized().adjusted(-10, -10, 10, 10);
        setPos(0, 0);
        update();
    }

    QRectF boundingRect() const override {
        if (!sourceNode || !targetNode) { return QRectF{}; }

        QPointF source = getSourcePoint();
        QPointF target = getTargetPoint();

        QRectF rect{source, target};
        for (const auto& point : controlPoints) {
            rect = rect.united(QRectF{point, point});
        }

        return rect.normalized().adjusted(-15, -15, 15, 15);
    }

    void paintNode(QPainter* _painter) override {
        auto painter = std::make_unique<DebugPainter>(
            _painter, TraceState, "", CALL_LOC());
        if (!sourceNode || !targetNode) { return; }

        QPointF source = getSourcePoint();
        QPointF target = getTargetPoint();

        if (isSelected()) {
            QPen highlightPen = edgePen;
            highlightPen.setColor(Qt::red);
            highlightPen.setWidth(edgePen.width() + 2);
            painter->setPen(highlightPen);

            switch (edgeType) {
                case Orthogonal:
                    paintOrthogonal(_painter, source, target);
                    break;
                case Polyline:
                    paintPolyline(_painter, source, target);
                    break;
                case Bezier: paintBezier(_painter, source, target); break;
            }
        }

        painter->setPen(edgePen);

        switch (edgeType) {
            case Orthogonal:
                paintOrthogonal(_painter, source, target);
                break;
            case Polyline: paintPolyline(_painter, source, target); break;
            case Bezier: paintBezier(_painter, source, target); break;
        }

        paintArrowHead(_painter, target);
        paintControlPoints(_painter);
    }

    void paintOrthogonal(
        QPainter*      _painter,
        const QPointF& source,
        const QPointF& target) {
        auto painter = std::make_unique<DebugPainter>(
            _painter, TraceState, "", CALL_LOC());
        QPointF mid{target.x(), source.y()};
        painter->drawLine(source, mid);
        painter->drawLine(mid, target);
    }

    void paintPolyline(
        QPainter*      _painter,
        const QPointF& source,
        const QPointF& target) {
        auto painter = std::make_unique<DebugPainter>(
            _painter, TraceState, "", CALL_LOC());
        if (controlPoints.empty()) {
            painter->drawLine(source, target);
            return;
        }

        QPointF current = source;
        for (const auto& point : controlPoints) {
            painter->drawLine(current, point);
            current = point;
        }
        painter->drawLine(current, target);
    }

    void paintBezier(
        QPainter*      _painter,
        const QPointF& source,
        const QPointF& target) {
        auto painter = std::make_unique<DebugPainter>(
            _painter, TraceState, "", CALL_LOC());
        QPainterPath path{source};

        if (controlPoints.size() >= 2) {
            for (int i = 0; i < static_cast<int>(controlPoints.size()) - 1;
                 i += 2) {
                QPointF cp1 = controlPoints.at(i);
                QPointF cp2 = (i + 1
                               < static_cast<int>(controlPoints.size()))
                                ? controlPoints.at(i + 1)
                                : target;
                QPointF end = (i + 2
                               < static_cast<int>(controlPoints.size()))
                                ? controlPoints.at(i + 2)
                                : target;
                path.cubicTo(cp1, cp2, end);
            }
        } else {
            QPointF cp1 = source + QPointF{50, 0};
            QPointF cp2 = target - QPointF{50, 0};
            path.cubicTo(cp1, cp2, target);
        }

        painter->drawPath(path);
    }

    void paintArrowHead(QPainter* _painter, const QPointF& target) {
        auto painter = std::make_unique<DebugPainter>(
            _painter, TraceState, "", CALL_LOC());
        QPointF direction{};

        if (!controlPoints.empty()) {
            direction = target - controlPoints.back();
        } else if (sourceNode) {
            direction = target - getSourcePoint();
        }

        if (direction.x() == 0 && direction.y() == 0) { return; }

        direction = direction
                  / std::sqrt(
                        direction.x() * direction.x()
                        + direction.y() * direction.y());
        QPointF arrowHead1 = target - direction * 10
                           + QPointF{
                               -direction.y() * 5, direction.x() * 5};
        QPointF arrowHead2 = target - direction * 10
                           + QPointF{
                               direction.y() * 5, -direction.x() * 5};
        painter->drawLine(target, arrowHead1);
        painter->drawLine(target, arrowHead2);
    }

    void paintControlPoints(QPainter* _painter) {
        auto painter = std::make_unique<DebugPainter>(
            _painter, TraceState, "", CALL_LOC());
        if (!isSelected()) { return; }

        painter->setPen(QPen{Qt::red, 1});
        painter->setBrush(QBrush{Qt::red});

        for (const auto& point : controlPoints) {
            painter->drawEllipse(point, 4, 4);
        }
    }

    void addControlPoint(const QPointF& point) {
        controlPoints.push_back(point);
        updateBounds();
    }

    void removeControlPoint(int index) {
        if (index >= 0 && index < static_cast<int>(controlPoints.size())) {
            controlPoints.erase(controlPoints.begin() + index);
            updateBounds();
        }
    }

    int findControlPoint(const QPointF& point) const {
        for (int i = 0; i < static_cast<int>(controlPoints.size()); ++i) {
            QRectF handle{
                controlPoints.at(i) - QPointF{4, 4}, QSizeF{8, 8}};
            if (handle.contains(point)) { return i; }
        }
        return -1;
    }

    bool handleMousePress(QGraphicsSceneMouseEvent* event) override {
        int controlIndex = findControlPoint(event->scenePos());
        if (controlIndex != -1) {
            draggedControlPoint = controlIndex;
            return true;
        }

        if (event->modifiers() & Qt::ControlModifier) {
            addControlPoint(event->scenePos());
            return true;
        }

        return false;
    }

    bool handleMouseMove(QGraphicsSceneMouseEvent* event) override {
        if (draggedControlPoint >= 0) {
            controlPoints.at(draggedControlPoint) = event->scenePos();
            updateBounds();
            return true;
        }
        return false;
    }

    void handleMouseRelease(QGraphicsSceneMouseEvent* event) override {
        draggedControlPoint = -1;
    }

    QWidget* createPropertiesWidget(QWidget* parent) override {
        auto widget = new QWidget{parent};
        auto layout = new QVBoxLayout{widget};

        layout->addWidget(new QLabel{"Edge Properties"});

        auto nameEdit = new QLineEdit{name};
        layout->addWidget(new QLabel{"Name:"});
        layout->addWidget(nameEdit);

        auto typeCombo = new QComboBox{};
        typeCombo->addItems({"Orthogonal", "Polyline", "Bezier"});
        typeCombo->setCurrentIndex(static_cast<int>(edgeType));
        layout->addWidget(new QLabel{"Type:"});
        layout->addWidget(typeCombo);

        auto widthSpin = new QSpinBox{};
        widthSpin->setRange(1, 10);
        widthSpin->setValue(edgePen.width());
        layout->addWidget(new QLabel{"Width:"});
        layout->addWidget(widthSpin);

        auto colorButton = new QPushButton{"Change Color"};
        colorButton->setStyleSheet(
            std::format(
                "background-color: {}",
                edgePen.color().name().toStdString())
                .c_str());
        layout->addWidget(new QLabel{"Color:"});
        layout->addWidget(colorButton);

        // Source offset controls
        layout->addWidget(new QLabel{"Source Offset:"});
        auto sourceXSpin = new QSpinBox{};
        sourceXSpin->setRange(-100, 100);
        sourceXSpin->setValue(static_cast<int>(sourceOffset.x()));
        sourceXSpin->setPrefix("X: ");
        layout->addWidget(sourceXSpin);

        auto sourceYSpin = new QSpinBox{};
        sourceYSpin->setRange(-100, 100);
        sourceYSpin->setValue(static_cast<int>(sourceOffset.y()));
        sourceYSpin->setPrefix("Y: ");
        layout->addWidget(sourceYSpin);

        // Target offset controls
        layout->addWidget(new QLabel{"Target Offset:"});
        auto targetXSpin = new QSpinBox{};
        targetXSpin->setRange(-100, 100);
        targetXSpin->setValue(static_cast<int>(targetOffset.x()));
        targetXSpin->setPrefix("X: ");
        layout->addWidget(targetXSpin);

        auto targetYSpin = new QSpinBox{};
        targetYSpin->setRange(-100, 100);
        targetYSpin->setValue(static_cast<int>(targetOffset.y()));
        targetYSpin->setPrefix("Y: ");
        layout->addWidget(targetYSpin);

        QObject::connect(
            nameEdit,
            &QLineEdit::textChanged,
            widget,
            [this](const QString& text) {
                name = text;
                update();
            });

        QObject::connect(
            typeCombo,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            widget,
            [this](int index) {
                edgeType = static_cast<EdgeType>(index);
                updateBounds();
            });

        QObject::connect(
            widthSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            widget,
            [this](int value) {
                edgePen.setWidth(value);
                update();
            });

        QObject::connect(
            colorButton,
            &QPushButton::clicked,
            widget,
            [this, colorButton]() {
                QColor newColor = QColorDialog::getColor(edgePen.color());
                if (newColor.isValid()) {
                    edgePen.setColor(newColor);
                    colorButton->setStyleSheet(
                        std::format(
                            "background-color: {}",
                            newColor.name().toStdString())
                            .c_str());
                    update();
                }
            });

        QObject::connect(
            sourceXSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            widget,
            [this](int value) {
                sourceOffset.setX(value);
                updateBounds();
            });

        QObject::connect(
            sourceYSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            widget,
            [this](int value) {
                sourceOffset.setY(value);
                updateBounds();
            });

        QObject::connect(
            targetXSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            widget,
            [this](int value) {
                targetOffset.setX(value);
                updateBounds();
            });

        QObject::connect(
            targetYSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            widget,
            [this](int value) {
                targetOffset.setY(value);
                updateBounds();
            });

        layout->addStretch();
        return widget;
    }

  private:
    int draggedControlPoint{-1};
};
