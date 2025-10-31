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
#include <src/gui/DiaSceneItemModel.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <src/model/DiaVersionStore.hpp>

struct StartupArgc {
    DECL_DESCRIBED_ENUM(Mode, Gui, MindMapDump);
    std::string documentPath;
    Mode        mode;
    DESC_FIELDS(StartupArgc, (documentPath, mode));
};

class DiaSelectionManager : public QObject {
    Q_OBJECT

  public:
    DiaSelectionManager(
        DiagramView*       view,
        QTreeView*         treeView,
        DiaSceneItemModel* model,
        QObject*           parent = nullptr);

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
    DiagramView*       diagramView;
    QTreeView*         treeView;
    DiaSceneItemModel* treeModel;
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
    DiaSceneItemModel*           treeModel{};
    QWidget*                     propertiesPanel{};
    QVBoxLayout*                 propertiesLayout{};
    QPushButton*                 createEdgeButton{};
    QPushButton*                 createGroupButton{};
    QPushButton*                 deleteSelectedNodeButton{};
    QCheckBox*                   showGridCheck{};
    QPushButton*                 gridColorButton{};
    QSlider*                     zoomSlider{};
    QLabel*                      zoomLabel{};
    QPushButton*                 zoomFitButton{};
    DiaSelectionManager*         selectionManager{};
    org::imm::ImmAstContext::Ptr imm_context;
    DiaContext::Ptr              dia_context;
    DiaVersionStore::Ptr         version_store;


    MainWindow(StartupArgc const& conf)
        : QMainWindow{nullptr}
        , conf{conf}
        , imm_context{org::imm::ImmAstContext::init_start_context()}
        , dia_context{DiaContext::shared()}
        , version_store{DiaVersionStore::shared(imm_context, dia_context)}
    //
    {
        setupUI();
        connectSignals();
        loadFile(QString::fromStdString(conf.documentPath));
    }

    void setupUI();
    void connectSignals();
    void loadFile(QString const& path);

  private slots:
    void setZoom(int value);
    void updateZoomSlider(int zoomPercent);
    void zoomFit();
    void onNodeSelected(DiaSceneItemVisual* node);

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};
