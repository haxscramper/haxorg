#include "MainWindow.hpp"
#include <QSlider>
#include <QSplitter>
#include <qstatusbar.h>

DiaSelectionManager::DiaSelectionManager(
    DiagramView*        view,
    QTreeView*          treeView,
    DiaSceneItemsModel* model,
    QObject*            parent)
    : QObject{parent}
    , diagramView{view}
    , treeView{treeView}
    , treeModel{model} {

    hstd::logic_assertion_check_not_nil(view);
    hstd::logic_assertion_check_not_nil(treeView);
    hstd::logic_assertion_check_not_nil(model);

    setupConnections();
}

void DiaSelectionManager::onSceneSelectionChanged(
    const QList<DiaSceneItemVisual*>& selectedNodes) {
    TRACKED_SLOT("onSceneSelectionChanged", selectedNodes);
    if (updatingSelection) { return; }
    updatingSelection = true;

    // Update tree selection
    treeModel->selectNodes(selectedNodes);

    updatingSelection = false;
}

void DiaSelectionManager::onTreeSelectionChanged(
    const QItemSelection& selected,
    const QItemSelection& deselected) {
    TRACKED_SLOT("onTreeSelectionChanged", selected, deselected);
    Q_UNUSED(deselected)
    if (updatingSelection) { return; }
    updatingSelection = true;

    // Get selected nodes from tree
    QList<DiaSceneItemVisual*> visualNodes;
    QModelIndexList            selectedIndexes = selected.indexes();

    for (const QModelIndex& index : selectedIndexes) {
        if (index.isValid()) {
            DiaSceneItem* node = static_cast<DiaSceneItem*>(
                index.internalPointer());
            DiaSceneItemVisual* visualNode = dynamic_cast<
                DiaSceneItemVisual*>(node);
            if (visualNode) { visualNodes.append(visualNode); }
        }
    }

    // Update scene selection
    diagramView->selectNodes(visualNodes);

    updatingSelection = false;
}

void DiaSelectionManager::onTreeNodesSelected(
    const QList<QModelIndex>& indexes) {
    TRACKED_SLOT("onTreeNodesSelected", indexes);

    // if (updatingSelection) { return; }

    // Update tree view selection
    QItemSelectionModel* selectionModel = treeView->selectionModel();
    if (selectionModel) {
        selectionModel->clear();
        for (const QModelIndex& index : indexes) {
            selectionModel->select(index, QItemSelectionModel::Select);
        }
    }
}

void DiaSelectionManager::setupConnections() {
    // Scene to tree
    connect(
        diagramView,
        &DiagramView::sceneSelectionChanged,
        this,
        &DiaSelectionManager::onSceneSelectionChanged);

    // Tree to scene
    connect(
        treeView->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this,
        &DiaSelectionManager::onTreeSelectionChanged);

    // Model selection updates
    connect(
        treeModel,
        &DiaSceneItemsModel::nodesSelected,
        this,
        &DiaSelectionManager::onTreeNodesSelected);
}

void MainWindow::setupUI() {
    treeModel = new DiaSceneItemsModel{this};
    scene     = new DiaScene{treeModel, this};
    view      = new DiagramView{};
    view->setScene(scene);

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


    createEdgeButton  = new QPushButton{"Create Edge"};
    createGroupButton = new QPushButton{"Create Group"};

    treeView = new QTreeView{};
    treeView->setModel(treeModel);
    treeView->setHeaderHidden(true);

    leftLayout->addWidget(gridLabel);
    leftLayout->addWidget(gridSnapBox);
    leftLayout->addWidget(showGridCheck);
    leftLayout->addWidget(gridColorButton);
    leftLayout->addWidget(new QLabel{"Zoom:"});

    zoomSlider = new QSlider{Qt::Horizontal};
    zoomSlider->setMinimum(10);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(100);
    zoomSlider->setTickPosition(QSlider::TicksBelow);
    zoomSlider->setTickInterval(50);
    leftLayout->addWidget(zoomSlider);

    zoomLabel = new QLabel{"100%"};
    zoomLabel->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(zoomLabel);

    auto zoomButtonLayout = new QHBoxLayout{};
    zoomFitButton         = new QPushButton{"Fit"};

    zoomButtonLayout->addWidget(zoomFitButton);
    leftLayout->addLayout(zoomButtonLayout);
    leftLayout->addWidget(createEdgeButton);
    leftLayout->addWidget(createGroupButton);
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

    selectionManager = new DiaSelectionManager(
        view, treeView, treeModel, this);

    QPushButton* dumpDiagram = new QPushButton("DEBUG TRACKER", this);
    connect(dumpDiagram, &QPushButton::clicked, dumpDiagram, []() {
        get_tracker_graph().render("/tmp/graph.png");
    });
    statusBar()->addWidget(dumpDiagram);
}

void MainWindow::connectSignals() {
    connect(
        gridSnapBox,
        QOverload<int>::of(&QSpinBox::valueChanged),
        scene,
        &DiaScene::setGridSnap);
    connect(
        scene, &DiaScene::nodeSelected, this, &MainWindow::onNodeSelected);
    connect(
        createGroupButton,
        &QPushButton::clicked,
        scene,
        &DiaScene::createGroupFromSelection);
    connect(
        showGridCheck, &QCheckBox::toggled, scene, &DiaScene::setShowGrid);
    connect(gridColorButton, &QPushButton::clicked, scene, [this]() {
        QColor newColor = QColorDialog::getColor(scene->gridColor);
        if (newColor.isValid()) {
            scene->setGridColor(newColor);
            gridColorButton->setStyleSheet(
                QString{"background-color: %1"}.arg(newColor.name()));
        }
    });

    connect(
        zoomSlider, &QSlider::valueChanged, this, &MainWindow::setZoom);
    connect(
        zoomFitButton, &QPushButton::clicked, this, &MainWindow::zoomFit);

    connect(
        view,
        &DiagramView::zoomChanged,
        this,
        &MainWindow::updateZoomSlider);
}

void MainWindow::setZoom(int value) {
    TRACKED_SLOT("setZoom", value);
    qreal scale = value / 100.0;
    view->setTransform(QTransform::fromScale(scale, scale));
    zoomLabel->setText(QString{"%1%"}.arg(value));
}

void MainWindow::updateZoomSlider(int zoomPercent) {
    TRACKED_SLOT("updateZoomSlider", zoomPercent);
    zoomPercent = qBound(
        zoomSlider->minimum(), zoomPercent, zoomSlider->maximum());

    zoomSlider->blockSignals(true);
    zoomSlider->setValue(zoomPercent);
    zoomSlider->blockSignals(false);
    zoomLabel->setText(QString{"%1%"}.arg(zoomPercent));
}

void MainWindow::zoomFit() {
    TRACKED_SLOT("zoomFit");
    QRectF itemsBounds = scene->itemsBoundingRect();
    if (!itemsBounds.isEmpty()) {
        view->fitInView(itemsBounds, Qt::KeepAspectRatio);

        // Update slider to reflect actual zoom level
        QTransform transform   = view->transform();
        qreal      scale       = transform.m11(); // Get scale factor
        int        zoomPercent = static_cast<int>(scale * 100);
        zoomPercent            = qBound(
            zoomSlider->minimum(), zoomPercent, zoomSlider->maximum());

        zoomSlider->blockSignals(true);
        zoomSlider->setValue(zoomPercent);
        zoomSlider->blockSignals(false);
        zoomLabel->setText(QString{"%1%"}.arg(zoomPercent));
    }
}

void MainWindow::onNodeSelected(DiaSceneItemVisual* node) {
    TRACKED_SLOT("onNodeSelected", node);
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

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == view && event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
        if (wheelEvent->modifiers()) {
            const int degrees = wheelEvent->angleDelta().y() / 8;
            const int steps   = degrees / 15;

            int currentValue = zoomSlider->value();
            int newValue     = currentValue + (steps * 10);
            newValue         = qBound(
                zoomSlider->minimum(), newValue, zoomSlider->maximum());
            zoomSlider->setValue(newValue);

            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}


void MainWindow::loadFile() {
    TRACKED_FUNCTION("loadFile");
    HSLOG_INFO(_cat, "Loading document from ", conf.documentPath);
    {
        HSLOG_INFO(_cat, "Add document to history manager");
        HSLOG_DEPTH_SCOPE_ANON();
        history_manager.addDocument(hstd::readFile(conf.documentPath));
    }
    DiaAdapter adapter;
    {
        HSLOG_INFO(_cat, "Convert document to dia adapter");
        HSLOG_DEPTH_SCOPE_ANON();
        adapter = FromDocument(
            tree_context, history_manager.getActiveRoot());
    }
    {
        HSLOG_INFO(_cat, "Set root adapter to scene");
        HSLOG_DEPTH_SCOPE_ANON();
        scene->setRootAdapter(adapter);
    }
}
