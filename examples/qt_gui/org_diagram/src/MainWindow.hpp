#pragma once

#include <QObject>
#include <QMainWindow>
#include <QTreeView>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>

#include <src/gui/DiaScene.hpp>
#include <src/gui/DiagramView.hpp>
#include <src/gui/DiaSceneItemsModel.hpp>
#include <hstd/stdlib/Debug.hpp>

struct StartupArgc {
    std::string documentPath;
    DESC_FIELDS(StartupArgc, (documentPath));
};

class DiaSelectionManager : public QObject {
    Q_OBJECT

  public:
    DiaSelectionManager(
        DiagramView*        view,
        QTreeView*          treeView,
        DiaSceneItemsModel* model,
        QObject*            parent = nullptr);

  private slots:
    void onSceneSelectionChanged(
        const QList<DiaSceneItemVisual*>& selectedNodes);

    void onTreeSelectionChanged(
        const QItemSelection& selected,
        const QItemSelection& deselected);

    void onTreeNodesSelected(const QList<QModelIndex>& indexes);

  private:
    void setupConnections();

  private:
    DiagramView*        diagramView;
    QTreeView*          treeView;
    DiaSceneItemsModel* treeModel;
    bool updatingSelection{false}; // Prevent infinite recursion
};


struct MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    StartupArgc                  conf;
    DiaScene*                    scene{};
    DiagramView*                 view{};
    QSpinBox*                    gridSnapBox{};
    QTreeView*                   treeView{};
    DiaSceneItemsModel*          treeModel{};
    QWidget*                     propertiesPanel{};
    QVBoxLayout*                 propertiesLayout{};
    QPushButton*                 createEdgeButton{};
    QPushButton*                 createGroupButton{};
    QCheckBox*                   showGridCheck{};
    QPushButton*                 gridColorButton{};
    QSlider*                     zoomSlider{};
    QLabel*                      zoomLabel{};
    QPushButton*                 zoomFitButton{};
    DiaSelectionManager*         selectionManager{};
    org::imm::ImmAstContext::Ptr context;
    HistoryManager               history_manager;
    hstd::SPtr<DiaContext>       tree_context;


    MainWindow(StartupArgc const& conf)
        : QMainWindow{nullptr}
        , conf{conf}
        , context{org::imm::ImmAstContext::init_start_context()}
        , history_manager{context}
        , tree_context{DiaContext::shared()} {
        setupUI();
        connectSignals();
        loadFile();
    }

    void setupUI();
    void connectSignals();
    void loadFile();

  private slots:
    void setZoom(int value);
    void updateZoomSlider(int zoomPercent);
    void zoomFit();
    void onNodeSelected(DiaSceneItemVisual* node);

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};
