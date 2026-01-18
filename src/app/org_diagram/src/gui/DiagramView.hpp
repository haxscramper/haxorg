#pragma once

#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
#include <org_diagram/src/gui/items/DiaSceneItemVisual.hpp>

#define _cat "app.view"

class DiagramView : public QGraphicsView {
    Q_OBJECT

  public:
    DiagramView(QWidget* parent = nullptr) : QGraphicsView{parent} {
        setDragMode(QGraphicsView::RubberBandDrag);
        setRenderHint(QPainter::Antialiasing);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        setInteractive(true);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }

  signals:
    void zoomChanged(int zoomPercent);
    void sceneSelectionChanged(
        const QList<DiaSceneItemVisual*>& selectedNodes);

  public:
    void wheelEvent(QWheelEvent* event) override;

  public slots:
    void selectNodes(const QList<DiaSceneItemVisual*>& nodes);

  private slots:
    void onSceneSelectionChanged() { emitSelectionChanged(); }

  protected:
    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

  private:
    void emitSelectionChanged();

    void connectToScene() {
        if (scene()) {
            connect(
                scene(),
                &QGraphicsScene::selectionChanged,
                this,
                &DiagramView::onSceneSelectionChanged);
        }
    }

  public:
    void setScene(QGraphicsScene* scene) {
        QGraphicsView::setScene(scene);
        connectToScene();
    }

  private:
    bool   isPanning{false};
    QPoint lastPanPoint{};
};
