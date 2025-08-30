#pragma once

#include <QObject>
#include <QMainWindow>
#include <QTreeView>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>

#include <src/gui/DiagramScene.hpp>
#include <src/gui/DiagramView.hpp>
#include <src/gui/DiagramTreeModel.hpp>
#include <hstd/stdlib/Debug.hpp>

class DiagramSelectionManager : public QObject {
    Q_OBJECT

  public:
    DiagramSelectionManager(
        DiagramView*      view,
        QTreeView*        treeView,
        DiagramTreeModel* model,
        QObject*          parent = nullptr);

  private slots:
    void onSceneSelectionChanged(
        const QList<DiagramSceneItemVisual*>& selectedNodes);

    void onTreeSelectionChanged(
        const QItemSelection& selected,
        const QItemSelection& deselected);

    void onTreeNodesSelected(const QList<QModelIndex>& indexes);

  private:
    void setupConnections();

  private:
    DiagramView*      diagramView;
    QTreeView*        treeView;
    DiagramTreeModel* treeModel;
    bool updatingSelection{false}; // Prevent infinite recursion
};


struct MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    DiagramScene*            scene{};
    DiagramView*             view{};
    QSpinBox*                gridSnapBox{};
    QPushButton*             addRectButton{};
    QPushButton*             addLayerButton{};
    QPushButton*             addImageButton{};
    QTreeView*               treeView{};
    DiagramTreeModel*        treeModel{};
    QWidget*                 propertiesPanel{};
    QVBoxLayout*             propertiesLayout{};
    QPushButton*             createEdgeButton{};
    QPushButton*             createGroupButton{};
    QCheckBox*               showGridCheck{};
    QPushButton*             gridColorButton{};
    QSlider*                 zoomSlider{};
    QLabel*                  zoomLabel{};
    QPushButton*             zoomFitButton{};
    DiagramSelectionManager* selectionManager{};


    MainWindow(QWidget* parent = nullptr) : QMainWindow{parent} {
        setupUI();
        connectSignals();
    }

    void setupUI();

    void connectSignals();

  private slots:
    void setZoom(int value);
    void updateZoomSlider(int zoomPercent);
    void zoomFit();
    void onNodeSelected(DiagramSceneItemVisual* node);

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};
