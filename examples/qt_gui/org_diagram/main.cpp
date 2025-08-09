#include <QtWidgets>
#include <QApplication>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QFileDialog>
#include <QListWidget>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSplitter>
#include <QAbstractItemModel>
#include <QTreeView>
#include <vector>
#include <QLineEdit>
#include <QColorDialog>
#include "DebugPainter.hpp"

struct DiagramNode {
    std::vector<DiagramNode*> children{};
    DiagramNode*              parent{nullptr};
    QString                   name{};

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

struct CanvasNode : public DiagramNode {
    CanvasNode(const QString& nodeName = "Canvas")
        : DiagramNode{nodeName} {}
    bool isCanvas() const override { return true; }
};

struct LayerNode : public DiagramNode {
    LayerNode(const QString& nodeName = "Layer") : DiagramNode{nodeName} {}
    bool isLayer() const override { return true; }
};

struct VisualDiagramNode
    : public DiagramNode
    , public QGraphicsItem {
    QRectF  bounds{0, 0, 100, 50};
    QPointF dragOffset{};

    VisualDiagramNode(const QString& nodeName = "Node")
        : DiagramNode{nodeName} {
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }

    virtual QWidget* createPropertiesWidget(QWidget* parent) = 0;

    bool isVisual() const override { return true; }

    QRectF boundingRect() const override {
        QRectF rect = bounds;
        rect        = rect.united(getAdditionalBounds());
        return rect.adjusted(-5, -5, 15, 15);
    }

    void paint(
        QPainter*                       _painter,
        const QStyleOptionGraphicsItem* option,
        QWidget*                        widget) override {
        auto painter = std::make_shared<DebugPainter>(
            _painter, "EdgeNode::paint");
        paintNode(_painter);
        paintText(_painter);
    }

    virtual void   paintNode(QPainter* painter) = 0;
    virtual QRectF getAdditionalBounds() const { return QRectF{}; }

    void paintText(QPainter* painter) {
        painter->setPen(QPen{Qt::black});
        painter->drawText(bounds, Qt::AlignCenter, name);
    }


    void setPosition(const QPointF& pos, int gridSnap) {
        int x = (static_cast<int>(pos.x()) / gridSnap) * gridSnap;
        int y = (static_cast<int>(pos.y()) / gridSnap) * gridSnap;
        setPos(x, y);
    }

    void updateConnectedEdges();


    QVariant itemChange(GraphicsItemChange change, const QVariant& value)
        override {
        if (change == ItemPositionHasChanged) { updateConnectedEdges(); }
        return QGraphicsItem::itemChange(change, value);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        if (handleMousePress(event)) { return; }

        dragOffset = event->pos();
        QGraphicsItem::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (handleMouseMove(event)) { return; }

        QGraphicsItem::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        handleMouseRelease(event);
        QGraphicsItem::mouseReleaseEvent(event);
    }

    virtual bool handleMousePress(QGraphicsSceneMouseEvent* event) {
        return false;
    }
    virtual bool handleMouseMove(QGraphicsSceneMouseEvent* event) {
        return false;
    }
    virtual void handleMouseRelease(QGraphicsSceneMouseEvent* event) {}
};

struct EdgeNode : public VisualDiagramNode {
    enum EdgeType
    {
        Orthogonal,
        Polyline,
        Bezier
    };

    VisualDiagramNode*   sourceNode{nullptr};
    VisualDiagramNode*   targetNode{nullptr};
    QPointF              sourceOffset{0, 0};
    QPointF              targetOffset{0, 0};
    std::vector<QPointF> controlPoints{};
    EdgeType             edgeType{Orthogonal};
    QPen                 edgePen{Qt::black, 2};
    QPainterPath         edgePath{};

    EdgeNode(
        VisualDiagramNode* source,
        VisualDiagramNode* target,
        const QString&     nodeName = "Edge")
        : VisualDiagramNode{nodeName}
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
            _painter, "", CALL_LOC());
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
            _painter, "", CALL_LOC());
        QPointF mid{target.x(), source.y()};
        painter->drawLine(source, mid);
        painter->drawLine(mid, target);
    }

    void paintPolyline(
        QPainter*      _painter,
        const QPointF& source,
        const QPointF& target) {
        auto painter = std::make_unique<DebugPainter>(
            _painter, "", CALL_LOC());
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
            _painter, "", CALL_LOC());
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
            _painter, "", CALL_LOC());
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
            _painter, "", CALL_LOC());
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

void VisualDiagramNode::updateConnectedEdges() {
    auto scene = this->scene();
    if (!scene) { return; }

    for (auto item : scene->items()) {
        if (auto edge = dynamic_cast<EdgeNode*>(item)) {
            if (edge->sourceNode == this || edge->targetNode == this) {
                edge->updateBounds();
            }
        }
    }
}


struct RectangleNode : public VisualDiagramNode {
    QColor color{Qt::blue};

    RectangleNode(const QString& nodeName = "Rectangle")
        : VisualDiagramNode{nodeName} {
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

struct ImageNode : public VisualDiagramNode {
    QPixmap image{};
    bool    isResizing{false};
    QPointF lastMousePos{};

    ImageNode(const QString& nodeName = "Image")
        : VisualDiagramNode{nodeName} {
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

struct DiagramTreeModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    DiagramNode* rootNode{};

    DiagramTreeModel(DiagramNode* root, QObject* parent = nullptr)
        : QAbstractItemModel{parent}, rootNode{root} {}

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override {
        if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

        DiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode;
        } else {
            parentNode = static_cast<DiagramNode*>(
                parent.internalPointer());
        }

        if (row < static_cast<int>(parentNode->children.size())) {
            return createIndex(row, column, parentNode->children.at(row));
        }

        return QModelIndex{};
    }

    QModelIndex parent(const QModelIndex& index) const override {
        if (!index.isValid()) { return QModelIndex{}; }

        DiagramNode* childNode = static_cast<DiagramNode*>(
            index.internalPointer());
        DiagramNode* parentNode = childNode->parent;

        if (parentNode == rootNode) { return QModelIndex{}; }

        DiagramNode* grandParent = parentNode->parent;
        if (!grandParent) { return QModelIndex{}; }

        for (int i = 0; i < static_cast<int>(grandParent->children.size());
             ++i) {
            if (grandParent->children.at(i) == parentNode) {
                return createIndex(i, 0, parentNode);
            }
        }

        return QModelIndex{};
    }

    int rowCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        DiagramNode* parentNode{};
        if (!parent.isValid()) {
            parentNode = rootNode;
        } else {
            parentNode = static_cast<DiagramNode*>(
                parent.internalPointer());
        }

        return static_cast<int>(parentNode->children.size());
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return 1;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override {
        if (!index.isValid()) { return QVariant{}; }

        if (role == Qt::DisplayRole) {
            DiagramNode* node = static_cast<DiagramNode*>(
                index.internalPointer());
            return node->name;
        }

        return QVariant{};
    }

    void refresh() {
        beginResetModel();
        endResetModel();
    }
};

struct DiagramScene : public QGraphicsScene {
    Q_OBJECT

  public:
    int                             gridSnap{10};
    DiagramNode*                    rootNode{};
    VisualDiagramNode*              selectedNode{nullptr};
    VisualDiagramNode*              arrowSource{nullptr};
    DiagramTreeModel*               treeModel{nullptr};
    std::vector<VisualDiagramNode*> selectedNodes{};

    DiagramScene(QObject* parent = nullptr) : QGraphicsScene{parent} {
        rootNode = new CanvasNode{"Canvas"};
        setupExampleDiagram();
    }

    void setupExampleDiagram() {
        auto layer1 = new LayerNode{"Layer 1"};

        auto node1 = new RectangleNode{"Node 1"};
        node1->setPos(100, 100);
        node1->color = Qt::cyan;
        addItem(node1);

        auto node2 = new RectangleNode{"Node 2"};
        node2->setPos(250, 150);
        node2->color = Qt::yellow;
        addItem(node2);

        layer1->addChild(node1);
        layer1->addChild(node2);
        rootNode->addChild(layer1);

        addEdge(node1, node2);

        updateTreeView();
    }


    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsItem*     item = itemAt(event->scenePos(), QTransform{});
        VisualDiagramNode* clickedNode = dynamic_cast<VisualDiagramNode*>(
            item);

        if (event->modifiers() & Qt::ControlModifier) {
            // Multi-selection mode
            if (clickedNode
                && std::find(
                       selectedNodes.begin(),
                       selectedNodes.end(),
                       clickedNode)
                       == selectedNodes.end()) {
                selectedNodes.push_back(clickedNode);
                clickedNode->setSelected(true);
            }
        } else {
            // Single selection mode
            for (auto node : selectedNodes) { node->setSelected(false); }
            selectedNodes.clear();

            if (clickedNode) {
                selectedNodes.push_back(clickedNode);
                clickedNode->setSelected(true);
            }

            selectedNode = clickedNode;
            emit nodeSelected(selectedNode);
        }

        if (event->button() == Qt::RightButton && selectedNode) {
            auto visualNode = dynamic_cast<VisualDiagramNode*>(
                selectedNode);
            if (visualNode && !dynamic_cast<EdgeNode*>(visualNode)) {
                if (arrowSource == nullptr) {
                    arrowSource = visualNode;
                } else {
                    if (arrowSource != visualNode) {
                        auto edge = new EdgeNode(arrowSource, visualNode);
                        addItem(edge);

                        auto layer = findFirstLayer();
                        if (layer) {
                            layer->addChild(edge);
                        } else {
                            rootNode->addChild(edge);
                        }
                        updateTreeView();
                    }
                    arrowSource = nullptr;
                }
            }
        } else {
            QGraphicsScene::mousePressEvent(event);
        }
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (selectedNode && (event->buttons() & Qt::LeftButton)) {
            ImageNode* imageNode = dynamic_cast<ImageNode*>(selectedNode);
            if (!imageNode || !imageNode->isResizing) {
                QPointF newPos = event->scenePos()
                               - selectedNode->dragOffset;
                selectedNode->setPosition(newPos, gridSnap);
                return;
            }
        }
        QGraphicsScene::mouseMoveEvent(event);
    }
    void setTreeModel(DiagramTreeModel* model) {
        treeModel = model;
        updateTreeView();
    }

    void updateTreeView() {
        if (treeModel) { treeModel->refresh(); }
    }

    LayerNode* findFirstLayer() {
        for (const auto& child : rootNode->children) {
            if (child->isLayer()) {
                return dynamic_cast<LayerNode*>(child);
            }
        }
        return nullptr;
    }

  public slots:
    void setGridSnap(int snap) { gridSnap = snap; }

    void addEdge(
        VisualDiagramNode* sourceNode,
        VisualDiagramNode* targetNode) {
        auto edge = new EdgeNode{sourceNode, targetNode};
        addItem(edge);

        auto layer = findFirstLayer();
        if (layer) {
            layer->addChild(edge);
        } else {
            rootNode->addChild(edge);
        }
    }

    void createEdgeFromSelection() {
        if (selectedNodes.size() != 2) {
            QMessageBox::warning(
                nullptr,
                "Error",
                "Please select exactly 2 nodes to create an edge.");
            return;
        }

        VisualDiagramNode* sourceNode = selectedNodes.at(0);
        VisualDiagramNode* targetNode = selectedNodes.at(1);

        if (dynamic_cast<EdgeNode*>(sourceNode)
            || dynamic_cast<EdgeNode*>(targetNode)) {
            QMessageBox::warning(
                nullptr,
                "Error",
                "Cannot create edge from or to another edge.");
            return;
        }

        addEdge(sourceNode, targetNode);

        // Clear selection
        for (auto node : selectedNodes) { node->setSelected(false); }
        selectedNodes.clear();
        updateTreeView();
    }


    void addRectangle() {
        auto node = new RectangleNode{"Rectangle"};
        node->setPos(200, 200);
        node->color = Qt::green;
        addItem(node);

        auto layer = findFirstLayer();
        if (layer) {
            layer->addChild(node);
        } else {
            rootNode->addChild(node);
        }
        updateTreeView();
    }

    void addLayer() {
        auto layer = new LayerNode{"New Layer"};
        rootNode->addChild(layer);
        updateTreeView();
    }

    void addImage() {
        QString fileName = QFileDialog::getOpenFileName(
            nullptr,
            "Open Image",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!fileName.isEmpty()) {
            auto node = new ImageNode{"Image"};
            node->setImage(
                QPixmap{fileName}.scaled(100, 100, Qt::KeepAspectRatio));
            node->setPos(150, 300);
            addItem(node);

            auto layer = findFirstLayer();
            if (layer) {
                layer->addChild(node);
            } else {
                rootNode->addChild(node);
            }
            updateTreeView();
        }
    }

  signals:
    void nodeSelected(VisualDiagramNode* node);
};

struct MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    DiagramScene*     scene{};
    QGraphicsView*    view{};
    QSpinBox*         gridSnapBox{};
    QPushButton*      addRectButton{};
    QPushButton*      addLayerButton{};
    QPushButton*      addImageButton{};
    QLabel*           statusLabel{};
    QTreeView*        treeView{};
    DiagramTreeModel* treeModel{};
    QWidget*          propertiesPanel{};
    QVBoxLayout*      propertiesLayout{};
    QPushButton*      createEdgeButton{};

    MainWindow(QWidget* parent = nullptr) : QMainWindow{parent} {
        setupUI();
        connectSignals();
    }

    void setupUI() {
        scene = new DiagramScene{this};
        view  = new QGraphicsView{scene};
        view->setRenderHint(QPainter::Antialiasing);
        view->setDragMode(QGraphicsView::RubberBandDrag);

        treeModel = new DiagramTreeModel{scene->rootNode, this};
        scene->setTreeModel(treeModel);

        auto centralWidget = new QWidget{};
        auto mainLayout    = new QHBoxLayout{centralWidget};

        auto leftPanel = new QWidget{};
        leftPanel->setMaximumWidth(200);
        auto leftLayout = new QVBoxLayout{leftPanel};

        auto gridLabel = new QLabel{"Grid Snap:"};
        gridSnapBox    = new QSpinBox{};
        gridSnapBox->setMinimum(1);
        gridSnapBox->setMaximum(50);
        gridSnapBox->setValue(10);

        addRectButton    = new QPushButton{"Add Rectangle"};
        addLayerButton   = new QPushButton{"Add Layer"};
        addImageButton   = new QPushButton{"Add Image"};
        createEdgeButton = new QPushButton{"Create Edge"};

        statusLabel = new QLabel{
            "Right-click to create edges. Ctrl+click for multi-selection. "
            "Use Create Edge button for selected nodes."};
        statusLabel->setWordWrap(true);

        treeView = new QTreeView{};
        treeView->setModel(treeModel);
        treeView->setHeaderHidden(true);

        leftLayout->addWidget(gridLabel);
        leftLayout->addWidget(gridSnapBox);
        leftLayout->addWidget(addRectButton);
        leftLayout->addWidget(addLayerButton);
        leftLayout->addWidget(addImageButton);
        leftLayout->addWidget(createEdgeButton);
        leftLayout->addWidget(statusLabel);
        leftLayout->addWidget(new QLabel{"Scene Tree:"});
        leftLayout->addWidget(treeView);

        propertiesPanel = new QWidget{};
        propertiesPanel->setMaximumWidth(200);
        propertiesLayout = new QVBoxLayout{propertiesPanel};
        propertiesLayout->addWidget(new QLabel{"Properties"});
        propertiesLayout->addStretch();


        auto splitter = new QSplitter{Qt::Horizontal};
        splitter->addWidget(leftPanel);
        splitter->addWidget(view);
        splitter->addWidget(propertiesPanel);
        splitter->setSizes({200, 600, 200});

        mainLayout->addWidget(splitter);

        setCentralWidget(centralWidget);
        setWindowTitle("Diagram Editor");
        resize(1200, 700);

        treeView->expandAll();
    }

    void connectSignals() {
        connect(
            gridSnapBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            scene,
            &DiagramScene::setGridSnap);
        connect(
            addRectButton,
            &QPushButton::clicked,
            scene,
            &DiagramScene::addRectangle);
        connect(
            addLayerButton,
            &QPushButton::clicked,
            scene,
            &DiagramScene::addLayer);
        connect(
            addImageButton,
            &QPushButton::clicked,
            scene,
            &DiagramScene::addImage);
        connect(
            scene,
            &DiagramScene::nodeSelected,
            this,
            &MainWindow::onNodeSelected);
        connect(
            createEdgeButton,
            &QPushButton::clicked,
            scene,
            &DiagramScene::createEdgeFromSelection);
    }

  private slots:
    void onNodeSelected(VisualDiagramNode* node) {
        // Clear existing properties
        while (propertiesLayout->count() > 1) {
            QLayoutItem* item = propertiesLayout->takeAt(1);
            if (item->widget()) { item->widget()->deleteLater(); }
            delete item;
        }

        if (node) {
            auto propertiesWidget = node->createPropertiesWidget(
                propertiesPanel);
            propertiesLayout->insertWidget(1, propertiesWidget);
        } else {
            propertiesLayout->addStretch();
        }
    }
};

int main(int argc, char* argv[]) {
    QApplication app{argc, argv};
    QLoggingCategory::setFilterRules("qt.qpa.painting.debug=true");

    MainWindow window{};
    window.show();

    return app.exec();
}

#include "main.moc"
