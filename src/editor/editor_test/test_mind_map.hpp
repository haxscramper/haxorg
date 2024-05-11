#pragma once
#include "test_utils.hpp"

class TestMindMap
    : public QObject
    , public TestBase {
    Q_OBJECT
  private slots:
    void initTestCase() { init_test_base(); }
    void cleanupTestCase() { cleanup_test_base(); }

    void testLibcolaApi1();
    void testLibcolaIr1();
    void testGraphvizIr1();
    void testGraphvizIrClusters();
    void testGraphConstruction();
    void testGraphConstructionSubtreeId1();
    void testGraphConstructionFootnoteId();
    void testFullMindMapGraph();
    void testQtGraphModel1();
    void testQtGraphScene1();
    void testQtGraphSceneFullMindMap();
};
