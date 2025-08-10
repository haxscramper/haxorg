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


#include "DiagramNode.hpp"
#include "DiagramNodeVisual.hpp"
#include "DiagramNodeEdge.hpp"
#include "DiagramNodeImage.hpp"
#include "DiagramNodeRectangle.hpp"
#include "DiagramNodeGroup.hpp"


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
    DiagramNodeVisual*              selectedNode{nullptr};
    DiagramNodeVisual*              arrowSource{nullptr};
    DiagramTreeModel*               treeModel{nullptr};
    std::vector<DiagramNodeVisual*> selectedNodes{};
    bool                            showGrid{true};
    QColor                          gridColor{Qt::lightGray};

    DiagramScene(QObject* parent = nullptr) : QGraphicsScene{parent} {
        rootNode = new DiagramNodeCanvas{"Canvas"};
        setupExampleDiagram();
    }

    void drawBackground(QPainter* painter, const QRectF& rect) override {
        QGraphicsScene::drawBackground(painter, rect);

        if (!showGrid) { return; }

        painter->setPen(QPen{gridColor, 1});

        // Calculate grid bounds
        int left = static_cast<int>(rect.left())
                 - (static_cast<int>(rect.left()) % gridSnap);
        int top = static_cast<int>(rect.top())
                - (static_cast<int>(rect.top()) % gridSnap);
        int right  = static_cast<int>(rect.right());
        int bottom = static_cast<int>(rect.bottom());

        // Draw vertical lines
        for (int x = left; x <= right; x += gridSnap) {
            painter->drawLine(
                x,
                static_cast<int>(rect.top()),
                x,
                static_cast<int>(rect.bottom()));
        }

        // Draw horizontal lines
        for (int y = top; y <= bottom; y += gridSnap) {
            painter->drawLine(
                static_cast<int>(rect.left()),
                y,
                static_cast<int>(rect.right()),
                y);
        }
    }


    void setupExampleDiagram() {
        auto layer1 = new DiagramNodeLayer{"Layer 1"};

        auto node1 = new DiagramNodeRectangle{"Node 1"};
        node1->setPos(100, 100);
        node1->color = Qt::cyan;
        addItem(node1);

        auto node2 = new DiagramNodeRectangle{"Node 2"};
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
        DiagramNodeVisual* clickedNode = dynamic_cast<DiagramNodeVisual*>(
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
            auto visualNode = dynamic_cast<DiagramNodeVisual*>(
                selectedNode);
            if (visualNode
                && !dynamic_cast<DiagramNodeEdge*>(visualNode)) {
                if (arrowSource == nullptr) {
                    arrowSource = visualNode;
                } else {
                    if (arrowSource != visualNode) {
                        auto edge = new DiagramNodeEdge(
                            arrowSource, visualNode);
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
            DiagramNodeImage* imageNode = dynamic_cast<DiagramNodeImage*>(
                selectedNode);
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

    DiagramNodeLayer* findFirstLayer() {
        for (const auto& child : rootNode->children) {
            if (auto it = dynamic_cast<DiagramNodeLayer*>(child);
                it != nullptr) {
                return it;
            }
        }
        return nullptr;
    }

  public slots:
    void setShowGrid(bool show) {
        showGrid = show;
        invalidate(); // Force redraw
    }

    void setGridColor(const QColor& color) {
        gridColor = color;
        invalidate(); // Force redraw
    }

    void setGridSnap(int snap) { gridSnap = snap; }

    void addEdge(
        DiagramNodeVisual* sourceNode,
        DiagramNodeVisual* targetNode) {
        auto edge = new DiagramNodeEdge{sourceNode, targetNode};
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

        DiagramNodeVisual* sourceNode = selectedNodes.at(0);
        DiagramNodeVisual* targetNode = selectedNodes.at(1);

        if (dynamic_cast<DiagramNodeEdge*>(sourceNode)
            || dynamic_cast<DiagramNodeEdge*>(targetNode)) {
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
        auto node = new DiagramNodeRectangle{"Rectangle"};
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
        auto layer = new DiagramNodeLayer{"New Layer"};
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
            auto node = new DiagramNodeImage{"Image"};
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

    DiagramNodeGroup* findGroupContaining(DiagramNodeVisual* node) {
        for (auto item : items()) {
            if (auto group = dynamic_cast<DiagramNodeGroup*>(item)) {
                if (std::find(
                        group->groupedNodes.begin(),
                        group->groupedNodes.end(),
                        node)
                    != group->groupedNodes.end()) {
                    return group;
                }
            }
        }
        return nullptr;
    }

    std::vector<DiagramNodeVisual*> findCommonParentNodes(
        const std::vector<DiagramNodeVisual*>& nodes) {
        std::vector<DiagramNodeVisual*> result;
        std::set<DiagramNodeVisual*>    processed;

        for (auto node : nodes) {
            if (dynamic_cast<DiagramNodeEdge*>(node)) {
                continue; // Skip edges
            }
            if (processed.count(node)) { continue; }

            auto group = findGroupContaining(node);
            if (group) {
                // Check if all nodes in this group are in the selection
                bool allNodesSelected = true;
                for (auto groupNode : group->groupedNodes) {
                    if (std::find(nodes.begin(), nodes.end(), groupNode)
                        == nodes.end()) {
                        allNodesSelected = false;
                        break;
                    }
                }

                if (allNodesSelected) {
                    result.push_back(group);
                    for (auto groupNode : group->groupedNodes) {
                        processed.insert(groupNode);
                    }
                } else {
                    result.push_back(node);
                    processed.insert(node);
                }
            } else {
                result.push_back(node);
                processed.insert(node);
            }
        }

        return result;
    }

  public slots:
    void createGroupFromSelection() {
        // Filter out edges and get only visual nodes
        std::vector<DiagramNodeVisual*> visualNodes;
        for (auto node : selectedNodes) {
            if (!dynamic_cast<DiagramNodeEdge*>(node)) {
                visualNodes.push_back(node);
            }
        }

        if (visualNodes.size() < 2) {
            QMessageBox::warning(
                nullptr,
                "Error",
                "Please select at least 2 non-edge nodes to create a "
                "group.");
            return;
        }

        // Find common parent nodes
        auto nodesToGroup = findCommonParentNodes(visualNodes);

        if (nodesToGroup.empty()) {
            QMessageBox::warning(
                nullptr, "Error", "No valid nodes to group.");
            return;
        }

        // Remove nodes from their current groups if any
        for (auto node : nodesToGroup) {
            auto currentGroup = findGroupContaining(node);
            if (currentGroup) { currentGroup->removeFromGroup(node); }
        }

        // Create new group
        auto group = new DiagramNodeGroup{"Group"};
        addItem(group);

        // Add nodes to the group
        for (auto node : nodesToGroup) { group->addToGroup(node); }

        group->updateBoundsToFitNodes();

        // Add to scene hierarchy
        auto layer = findFirstLayer();
        if (layer) {
            // Convert to shared_ptr if using shared_ptr management
            layer->addChild(group);
        } else {
            rootNode->addChild(group);
        }

        // Clear selection
        for (auto node : selectedNodes) { node->setSelected(false); }
        selectedNodes.clear();

        updateTreeView();
    }


  signals:
    void nodeSelected(DiagramNodeVisual* node);
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
    QPushButton*      createGroupButton{};
    QCheckBox*        showGridCheck{};
    QPushButton*      gridColorButton{};

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

        showGridCheck = new QCheckBox{"Show Grid"};
        showGridCheck->setChecked(true);

        gridColorButton = new QPushButton{"Grid Color"};
        gridColorButton->setStyleSheet("background-color: lightgray");


        addRectButton     = new QPushButton{"Add Rectangle"};
        addLayerButton    = new QPushButton{"Add Layer"};
        addImageButton    = new QPushButton{"Add Image"};
        createEdgeButton  = new QPushButton{"Create Edge"};
        createGroupButton = new QPushButton{"Create Group"};

        statusLabel = new QLabel{
            "Right-click to create edges. Ctrl+click for multi-selection. "
            "Use Create Edge button for selected nodes."};
        statusLabel->setWordWrap(true);

        treeView = new QTreeView{};
        treeView->setModel(treeModel);
        treeView->setHeaderHidden(true);

        leftLayout->addWidget(gridLabel);
        leftLayout->addWidget(gridSnapBox);
        leftLayout->addWidget(showGridCheck);
        leftLayout->addWidget(gridColorButton);
        leftLayout->addWidget(addRectButton);
        leftLayout->addWidget(addLayerButton);
        leftLayout->addWidget(addImageButton);
        leftLayout->addWidget(createEdgeButton);
        leftLayout->addWidget(createGroupButton);
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
        connect(
            createGroupButton,
            &QPushButton::clicked,
            scene,
            &DiagramScene::createGroupFromSelection);
        connect(
            showGridCheck,
            &QCheckBox::toggled,
            scene,
            &DiagramScene::setShowGrid);
        connect(gridColorButton, &QPushButton::clicked, scene, [this]() {
            QColor newColor = QColorDialog::getColor(scene->gridColor);
            if (newColor.isValid()) {
                scene->setGridColor(newColor);
                gridColorButton->setStyleSheet(
                    QString{"background-color: %1"}.arg(newColor.name()));
            }
        });
    }

  private slots:
    void onNodeSelected(DiagramNodeVisual* node) {
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
